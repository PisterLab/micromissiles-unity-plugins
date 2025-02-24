#include "assignment/covered_assignment.h"

#include <stdexcept>
#include <vector>

#include "absl/strings/str_format.h"
#include "assignment/assignment.h"
#include "base/logging.h"
#include "ortools/sat/cp_model.h"
#include "ortools/sat/cp_model.pb.h"
#include "ortools/sat/cp_model_solver.h"

namespace assignment {

std::vector<Assignment::AssignmentItem> CoveredAssignment::Assign() const {
  // Create the constraint programming model.
  operations_research::sat::CpModelBuilder cp_model;

  // Define the variables.
  // x[i][j] is an array of boolean variables, such that x[i][j] is true if
  // agent i is assigned to task j.
  std::vector<std::vector<operations_research::sat::BoolVar>> x(
      num_agents_, std::vector<operations_research::sat::BoolVar>(num_tasks_));
  for (int i = 0; i < num_agents_; ++i) {
    for (int j = 0; j < num_tasks_; ++j) {
      x[i][j] = cp_model.NewBoolVar();
    }
  }

  // Define the constraints.
  // Each agent is assigned to one task.
  for (int i = 0; i < num_agents_; ++i) {
    cp_model.AddExactlyOne(x[i]);
  }
  // Each task is assigned to at least one agent.
  for (int j = 0; j < num_tasks_; ++j) {
    std::vector<operations_research::sat::BoolVar> tasks;
    for (int i = 0; i < num_agents_; ++i) {
      tasks.push_back(x[i][j]);
    }
    cp_model.AddAtLeastOne(tasks);
  }

  // Define the objective function.
  operations_research::sat::DoubleLinearExpr total_cost;
  for (int i = 0; i < num_agents_; ++i) {
    for (int j = 0; j < num_tasks_; ++j) {
      total_cost = total_cost.AddTerm(x[i][j], costs_[i][j]);
    }
  }
  cp_model.Minimize(total_cost);

  // Solve the assignment problem.
  const operations_research::sat::CpSolverResponse response =
      Solve(cp_model.Build());

  // Check the feasibility of the solution.
  if (response.status() ==
      operations_research::sat::CpSolverStatus::INFEASIBLE) {
    LOG(ERROR) << "Covered assignment problem is infeasible.";
    return std::vector<AssignmentItem>();
  }

  // Record the assignemnts.
  std::vector<AssignmentItem> assignments;
  assignments.reserve(num_agents_);
  for (int i = 0; i < num_agents_; ++i) {
    for (int j = 0; j < num_tasks_; ++j) {
      if (SolutionBooleanValue(response, x[i][j])) {
        assignments.emplace_back(i, j);
        break;
      }
    }
  }
  return assignments;
}

void CoveredAssignment::Validate() const {
  // Check that there are at least as many agents as tasks to cover all tasks.
  if (num_agents_ < num_tasks_) {
    throw std::invalid_argument(
        absl::StrFormat("There are fewer agents than tasks: %d vs. %d.",
                        num_agents_, num_tasks_));
  }
}

}  // namespace assignment
