// The assignment plugin includes various assignment algorithms.

#include <vector>

#include "assignment/cover_assignment.h"
#include "assignment/even_assignment.h"

namespace {
// Create the cost matrix.
std::vector<std::vector<double>> CreateCostMatrix(const int num_agents,
                                                  const int num_tasks,
                                                  const float* costs) {
  std::vector<std::vector<double>> cost_matrix(num_agents,
                                               std::vector<double>(num_tasks));
  for (int i = 0; i < num_agents; ++i) {
    for (int j = 0; j < num_tasks; ++j) {
      cost_matrix[i][j] = *(costs + num_tasks * i + j);
    }
  }
  return cost_matrix;
}
}  // namespace

extern "C" {
// Assign the agents to the tasks using a cover assignment.
int Assignment_CoverAssignment_Assign(const int num_agents, const int num_tasks,
                                      const float* costs, int* assigned_agents,
                                      int* assigned_tasks) {
  // Create the cost matrix.
  const auto cost_matrix = CreateCostMatrix(num_agents, num_tasks, costs);

  // Perform the assignment.
  assignment::CoverAssignment assignment(num_agents, num_tasks, cost_matrix);
  const auto assignments = assignment.Assign();

  // Record the assignments.
  for (int i = 0; i < assignments.size(); ++i) {
    assigned_agents[i] = assignments[i].first;
    assigned_tasks[i] = assignments[i].second;
  }
  return assignments.size();
}

// Assign the agents to the tasks using an even assignment.
int Assignment_EvenAssignment_Assign(const int num_agents, const int num_tasks,
                                     const float* costs, int* assigned_agents,
                                     int* assigned_tasks) {
  // Create the cost matrix.
  const auto cost_matrix = CreateCostMatrix(num_agents, num_tasks, costs);

  // Perform the assignment.
  assignment::EvenAssignment assignment(num_agents, num_tasks, cost_matrix);
  const auto assignments = assignment.Assign();

  // Record the assignments.
  for (int i = 0; i < assignments.size(); ++i) {
    assigned_agents[i] = assignments[i].first;
    assigned_tasks[i] = assignments[i].second;
  }
  return assignments.size();
}
}
