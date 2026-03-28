// File: jobserver_slot_test_23.cc

#include "gtest/gtest.h"
#include "jobserver.h"

#include <type_traits>
#include <cstdint>

using JobserverSlot = Jobserver::Slot;

// Compile-time checks for move-only semantics.
static_assert(!std::is_copy_constructible<JobserverSlot>::value,
              "Jobserver::Slot should not be copy constructible");
static_assert(!std::is_copy_assignable<JobserverSlot>::value,
              "Jobserver::Slot should not be copy assignable");
static_assert(std::is_move_constructible<JobserverSlot>::value,
              "Jobserver::Slot should be move constructible");
static_assert(std::is_move_assignable<JobserverSlot>::value,
              "Jobserver::Slot should be move assignable");

class JobserverSlotTest_23 : public ::testing::Test {};

// Default-constructed slot should be invalid.
TEST_F(JobserverSlotTest_23, DefaultConstructorCreatesInvalidSlot_23) {
  JobserverSlot slot;

  EXPECT_FALSE(slot.IsValid());
  // Do not call GetExplicitValue() on an invalid slot; behavior is unspecified.
}

// CreateExplicit should return a valid explicit slot with the given value.
TEST_F(JobserverSlotTest_23, CreateExplicitProducesValidExplicitSlot_23) {
  const uint8_t expected_value = 5u;

  JobserverSlot slot = JobserverSlot::CreateExplicit(expected_value);

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_EQ(expected_value, slot.GetExplicitValue());
}

// CreateImplicit should return a valid implicit, non-explicit slot.
TEST_F(JobserverSlotTest_23, CreateImplicitProducesValidImplicitSlot_23) {
  JobserverSlot slot = JobserverSlot::CreateImplicit();

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
  // Do not call GetExplicitValue() on an implicit slot; behavior is unspecified.
}

// Move constructor should preserve slot "kind" and explicit value.
TEST_F(JobserverSlotTest_23, MoveConstructorPreservesExplicitSlot_23) {
  JobserverSlot original = JobserverSlot::CreateExplicit(42u);
  ASSERT_TRUE(original.IsValid());
  ASSERT_TRUE(original.IsExplicit());
  const uint8_t original_value = original.GetExplicitValue();

  JobserverSlot moved(std::move(original));

  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsExplicit());
  EXPECT_EQ(original_value, moved.GetExplicitValue());
  // Do not assert anything about 'original' after move; its state is unspecified.
}

// Move assignment should preserve slot "kind" and explicit value.
TEST_F(JobserverSlotTest_23, MoveAssignmentPreservesExplicitSlot_23) {
  JobserverSlot target;  // Initially invalid.
  JobserverSlot source = JobserverSlot::CreateExplicit(7u);

  ASSERT_TRUE(source.IsValid());
  ASSERT_TRUE(source.IsExplicit());

  target = std::move(source);

  EXPECT_TRUE(target.IsValid());
  EXPECT_TRUE(target.IsExplicit());
  EXPECT_EQ(7u, target.GetExplicitValue());
  // Do not assert anything about 'source' after move; its state is unspecified.
}

// Boundary check: CreateExplicit should handle minimum and maximum uint8_t values.
TEST_F(JobserverSlotTest_23, CreateExplicitBoundaryValues_23) {
  // Minimum explicit value
  JobserverSlot min_slot = JobserverSlot::CreateExplicit(static_cast<uint8_t>(0));
  EXPECT_TRUE(min_slot.IsValid());
  EXPECT_TRUE(min_slot.IsExplicit());
  EXPECT_FALSE(min_slot.IsImplicit());
  EXPECT_EQ(static_cast<uint8_t>(0), min_slot.GetExplicitValue());

  // Maximum explicit value
  JobserverSlot max_slot = JobserverSlot::CreateExplicit(static_cast<uint8_t>(255));
  EXPECT_TRUE(max_slot.IsValid());
  EXPECT_TRUE(max_slot.IsExplicit());
  EXPECT_FALSE(max_slot.IsImplicit());
  EXPECT_EQ(static_cast<uint8_t>(255), max_slot.GetExplicitValue());
}
