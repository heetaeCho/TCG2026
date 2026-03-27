// File: ./TestProjects/yaml-cpp/test/settingchanges_move_assignment_test_439.cpp

#include <gtest/gtest.h>

#include <atomic>
#include <memory>
#include <type_traits>
#include <utility>

// Adjust include path if your test target already has include dirs set up.
#include "setting.h"

namespace {

class SettingChangesTest_439 : public ::testing::Test {
protected:
  // A minimal test double that lets us observe lifetime/destruction via a counter.
  // This relies only on push(std::unique_ptr<SettingChangeBase>) and the fact
  // that SettingChangeBase is deletable via a base pointer (virtual dtor).
  struct TrackingChange final : YAML::SettingChangeBase {
    explicit TrackingChange(int tag) : tag_(tag) {}

    ~TrackingChange() override {
      ++dtor_count;
      last_destroyed_tag.store(tag_, std::memory_order_relaxed);
    }

    int tag_;
    static std::atomic<int> dtor_count;
    static std::atomic<int> last_destroyed_tag;
  };

  void SetUp() override {
    TrackingChange::dtor_count.store(0, std::memory_order_relaxed);
    TrackingChange::last_destroyed_tag.store(-1, std::memory_order_relaxed);
  }
};

std::atomic<int> SettingChangesTest_439::TrackingChange::dtor_count{0};
std::atomic<int> SettingChangesTest_439::TrackingChange::last_destroyed_tag{-1};

TEST_F(SettingChangesTest_439, MoveAssignmentIsNoexcept_439) {
  static_assert(noexcept(std::declval<YAML::SettingChanges&>() =
                             std::declval<YAML::SettingChanges&&>()),
                "SettingChanges move-assignment should be noexcept per interface.");
}

TEST_F(SettingChangesTest_439, SelfMoveAssignmentDoesNothing_439) {
  YAML::SettingChanges changes;
  changes.push(std::make_unique<TrackingChange>(1));

  // Self-move assignment should short-circuit and not clear/destroy contents.
  changes = std::move(changes);

  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 0);

  // Now clear to ensure the held change still exists and is destroyable.
  changes.clear();
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 1);
  EXPECT_EQ(TrackingChange::last_destroyed_tag.load(std::memory_order_relaxed), 1);
}

TEST_F(SettingChangesTest_439, MoveAssignmentClearsLhsBeforeTakingRhs_439) {
  YAML::SettingChanges lhs;
  YAML::SettingChanges rhs;

  lhs.push(std::make_unique<TrackingChange>(10));
  rhs.push(std::make_unique<TrackingChange>(20));

  // According to the provided implementation, operator= does:
  //   if self -> return
  //   clear() on lhs
  //   swap(lhs.m_settingChanges, rhs.m_settingChanges)
  lhs = std::move(rhs);

  // LHS clear should have destroyed the original LHS change (tag 10).
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 1);
  EXPECT_EQ(TrackingChange::last_destroyed_tag.load(std::memory_order_relaxed), 10);

  // After move assignment, rhs should be empty (it swapped with a cleared lhs).
  // Clearing rhs should not destroy anything further.
  rhs.clear();
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 1);

  // Clearing lhs should now destroy the moved-in change (tag 20).
  lhs.clear();
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 2);
  EXPECT_EQ(TrackingChange::last_destroyed_tag.load(std::memory_order_relaxed), 20);
}

TEST_F(SettingChangesTest_439, MoveAssignmentIntoEmptyLhsTransfersOwnership_439) {
  YAML::SettingChanges lhs;
  YAML::SettingChanges rhs;

  rhs.push(std::make_unique<TrackingChange>(7));

  lhs = std::move(rhs);

  // No prior lhs content, so nothing should be destroyed during assignment.
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 0);

  // rhs is expected to be empty post-move (swap with cleared lhs).
  rhs.clear();
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 0);

  // lhs should now own the change.
  lhs.clear();
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 1);
  EXPECT_EQ(TrackingChange::last_destroyed_tag.load(std::memory_order_relaxed), 7);
}

TEST_F(SettingChangesTest_439, MoveAssignmentFromEmptyRhsClearsLhs_439) {
  YAML::SettingChanges lhs;
  YAML::SettingChanges rhs;

  lhs.push(std::make_unique<TrackingChange>(99));
  // rhs remains empty.

  lhs = std::move(rhs);

  // LHS was cleared during assignment, so tag 99 should be destroyed.
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 1);
  EXPECT_EQ(TrackingChange::last_destroyed_tag.load(std::memory_order_relaxed), 99);

  // lhs should now be empty (since rhs was empty).
  lhs.clear();
  EXPECT_EQ(TrackingChange::dtor_count.load(std::memory_order_relaxed), 1);
}

}  // namespace