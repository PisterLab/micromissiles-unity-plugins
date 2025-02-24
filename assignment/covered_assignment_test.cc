#include "assignment/covered_assignment.h"

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

#include "assignment/assignment.h"

namespace assignment {
namespace {

TEST(CoveredAssignmentTest, AssignUnique) {
  constexpr int kNumAgents = 5;
  constexpr int kNumTasks = 4;
  const std::vector<std::vector<double>> costs{
      {90, 80, 75, 70},   {35, 85, 55, 65},   {125, 95, 90, 95},
      {45, 110, 95, 115}, {50, 100, 90, 100},
  };
  CoveredAssignment assignment(kNumAgents, kNumTasks, costs);
  const auto assignments = assignment.Assign();
  std::unordered_map<int, int> expected_assignments{
      {0, 3}, {1, 2}, {2, 1}, {3, 0}, {4, 0}};
  for (const auto& [agent_index, task_index] : assignments) {
    EXPECT_EQ(expected_assignments[agent_index], task_index)
        << "Agent " << agent_index << " was assigned to task " << task_index
        << " but expected task " << expected_assignments[agent_index] << ".";
  }
}

TEST(CoveredAssignmentTest, AssignMultiple) {
  constexpr int kNumAgents = 3;
  constexpr int kNumTasks = 2;
  const std::vector<std::vector<double>> costs{
      {1, 3},
      {4, 3},
      {2, 2},
  };
  CoveredAssignment assignment(kNumAgents, kNumTasks, costs);
  const auto assignments = assignment.Assign();
  std::unordered_map<int, int> expected_assignments{{0, 0}, {1, 1}, {2, 1}};
  for (const auto& [agent_index, task_index] : assignments) {
    EXPECT_EQ(expected_assignments[agent_index], task_index)
        << "Agent " << agent_index << " was assigned to task " << task_index
        << " but expected task " << expected_assignments[agent_index] << ".";
  }
}

}  // namespace
}  // namespace assignment
