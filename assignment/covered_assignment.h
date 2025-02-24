// The covered assignment assigns one task to each agent under the condition
// that all tasks are assigned to at least one agent.

#pragma once

#include <vector>

#include "assignment/assignment.h"

namespace assignment {

// Covered assignment.
class CoveredAssignment : public Assignment {
 public:
  CoveredAssignment(int num_agents, int num_tasks,
                    std::vector<std::vector<double>> costs)
      : Assignment(num_agents, num_tasks, std::move(costs)) {}

  CoveredAssignment(const CoveredAssignment&) = default;
  CoveredAssignment& operator=(const CoveredAssignment&) = default;

  // Assign the agents to the tasks.
  std::vector<AssignmentItem> Assign() const override;
};

}  // namespace assignment
