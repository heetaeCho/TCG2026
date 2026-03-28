// File: jobserver_slot_test_25.cc

#include <gtest/gtest.h>

#include "jobserver.h"

class JobserverSlotTest_25 : public ::testing::Test {
 protected:
  using Slot = Jobserver::Slot;
};

// TEST_ID: 25
// Verify that a default-constructed Slot is invalid and neither implicit nor explicit.
TEST_F(JobserverSlotTest_25, DefaultConstructedSlotIsInvalidAndNotImplicitOrExplicit_25) {
  Slot slot;

  EXPECT_FALSE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// TEST_ID: 25
// Verify that CreateExplicit produces a valid, explicit, non-implicit slot
// and that GetExplicitValue returns the value used to create it.
TEST_F(JobserverSlotTest_25, CreateExplicitProducesValidExplicitSlotWithStoredValue_25) {
  const uint8_t value = 42;

  Slot slot = Slot::CreateExplicit(value);

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_EQ(value, slot.GetExplicitValue());
}

// TEST_ID: 25
// Verify that CreateImplicit produces a valid, implicit, non-explicit slot.
TEST_F(JobserverSlotTest_25, CreateImplicitProducesValidImplicitSlot_25) {
  Slot slot = Slot::CreateImplicit();

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// TEST_ID: 25
// Verify that CreateExplicit correctly handles boundary values for uint8_t
// (e.g., 0 and 255) and that the explicit value is preserved.
TEST_F(JobserverSlotTest_25, CreateExplicitHandlesBoundaryValues_25) {
  const uint8_t min_value = 0;
  const uint8_t max_value = 255;

  Slot min_slot = Slot::CreateExplicit(min_value);
  Slot max_slot = Slot::CreateExplicit(max_value);

  EXPECT_TRUE(min_slot.IsValid());
  EXPECT_TRUE(min_slot.IsExplicit());
  EXPECT_FALSE(min_slot.IsImplicit());
  EXPECT_EQ(min_value, min_slot.GetExplicitValue());

  EXPECT_TRUE(max_slot.IsValid());
  EXPECT_TRUE(max_slot.IsExplicit());
  EXPECT_FALSE(max_slot.IsImplicit());
  EXPECT_EQ(max_value, max_slot.GetExplicitValue());
}

// TEST_ID: 25
// Verify that move construction from an explicit slot preserves its observable state
// (valid, explicit, non-implicit, and stored explicit value).
TEST_F(JobserverSlotTest_25, MoveConstructionPreservesExplicitSlotState_25) {
  const uint8_t value = 7;
  Slot original = Slot::CreateExplicit(value);

  Slot moved(std::move(original));

  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsExplicit());
  EXPECT_FALSE(moved.IsImplicit());
  EXPECT_EQ(value, moved.GetExplicitValue());
  // No assumptions are made about the moved-from 'original' slot.
}

// TEST_ID: 25
// Verify that move assignment from an explicit slot preserves its observable state
// (valid, explicit, non-implicit, and stored explicit value).
TEST_F(JobserverSlotTest_25, MoveAssignmentPreservesExplicitSlotState_25) {
  const uint8_t value = 13;
  Slot source = Slot::CreateExplicit(value);
  Slot target = Slot::CreateImplicit();  // Start from a different valid state.

  target = std::move(source);

  EXPECT_TRUE(target.IsValid());
  EXPECT_TRUE(target.IsExplicit());
  EXPECT_FALSE(target.IsImplicit());
  EXPECT_EQ(value, target.GetExplicitValue());
  // No assumptions are made about the moved-from 'source' slot.
}
