// The assignment plugin includes various assignment algorithms.

#include <vector>

#include "assignment/covered_assignment.h"

extern "C" {
// Assign the agents to the tasks using a covered assignment.
int Assignment_CoveredAssignment_Assign(const int num_agents,
                                        const int num_tasks, const float* costs,
                                        int* assigned_agents,
                                        int* assigned_tasks) {
  // Create the cost matrix.
  std::vector<std::vector<double>> cost_matrix(num_agents,
                                               std::vector<double>(num_tasks));
  for (int i = 0; i < num_agents; ++i) {
    for (int j = 0; j < num_tasks; ++j) {
      cost_matrix[i][j] = *(costs + num_tasks * i + j);
    }
  }

  // Perform the assignment.
  assignment::CoveredAssignment assignment(num_agents, num_tasks, cost_matrix);
  const auto assignments = assignment.Assign();

  // Record the assignments.
  for (int i = 0; i < assignments.size(); ++i) {
    assigned_agents[i] = assignments[i].first;
    assigned_tasks[i] = assignments[i].second;
  }
  return assignments.size();
}
}
