// TEST_ID: 27
// File: jobserver_slot_test_27.cc

#include "jobserver.h"

#include <gtest/gtest.h>

using Jobserver::Slot;

class JobserverSlotTest_27 : public ::testing::Test {};

// Default-constructed slot should be invalid.
TEST_F(JobserverSlotTest_27, DefaultConstructedSlotIsInvalid_27) {
  Slot slot;
  EXPECT_FALSE(slot.IsValid());
}

// CreateExplicit should produce a valid explicit slot with the given value.
TEST_F(JobserverSlotTest_27, CreateExplicitProducesValidExplicitSlot_27) {
  const uint8_t value = 5;
  Slot slot = Slot::CreateExplicit(value);

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_EQ(value, slot.GetExplicitValue());
}

// CreateExplicit should correctly handle boundary uint8_t values (0 and 255).
TEST_F(JobserverSlotTest_27, CreateExplicitBoundaryValues_27) {
  // Lower boundary
  Slot slot_min = Slot::CreateExplicit(0);
  EXPECT_TRUE(slot_min.IsValid());
  EXPECT_TRUE(slot_min.IsExplicit());
  EXPECT_FALSE(slot_min.IsImplicit());
  EXPECT_EQ(static_cast<uint8_t>(0), slot_min.GetExplicitValue());

  // Upper boundary
  Slot slot_max = Slot::CreateExplicit(255);
  EXPECT_TRUE(slot_max.IsValid());
  EXPECT_TRUE(slot_max.IsExplicit());
  EXPECT_FALSE(slot_max.IsImplicit());
  EXPECT_EQ(static_cast<uint8_t>(255), slot_max.GetExplicitValue());
}

// CreateImplicit should produce a valid implicit slot.
TEST_F(JobserverSlotTest_27, CreateImplicitProducesValidImplicitSlot_27) {
  Slot slot = Slot::CreateImplicit();

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
  // Intentionally do NOT call GetExplicitValue() here, since it is only
  // meaningful for explicit slots based on the interface naming.
}

// Move construction from an explicit slot should preserve explicitness and value.
TEST_F(JobserverSlotTest_27, MoveConstructFromExplicitSlot_27) {
  const uint8_t value = 42;
  Slot original = Slot::CreateExplicit(value);

  Slot moved(std::move(original));

  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsExplicit());
  EXPECT_FALSE(moved.IsImplicit());
  EXPECT_EQ(value, moved.GetExplicitValue());
  // We deliberately avoid asserting anything about 'original' after move.
}

// Move assignment from an explicit slot into a default-constructed slot.
TEST_F(JobserverSlotTest_27, MoveAssignFromExplicitIntoDefaultSlot_27) {
  const uint8_t value = 13;
  Slot source = Slot::CreateExplicit(value);
  Slot dest;  // default-constructed (invalid)

  dest = std::move(source);

  EXPECT_TRUE(dest.IsValid());
  EXPECT_TRUE(dest.IsExplicit());
  EXPECT_FALSE(dest.IsImplicit());
  EXPECT_EQ(value, dest.GetExplicitValue());
  // No assumptions about 'source' after move.
}

// Move assignment should overwrite an existing explicit slot's value/flags.
TEST_F(JobserverSlotTest_27, MoveAssignOverExistingExplicitSlot_27) {
  const uint8_t initial_value = 7;
  const uint8_t new_value = 99;

  Slot dest = Slot::CreateExplicit(initial_value);
  Slot source = Slot::CreateExplicit(new_value);

  dest = std::move(source);

  EXPECT_TRUE(dest.IsValid());
  EXPECT_TRUE(dest.IsExplicit());
  EXPECT_FALSE(dest.IsImplicit());
  EXPECT_EQ(new_value, dest.GetExplicitValue());
}

// Move construction from an implicit slot should preserve implicitness.
TEST_F(JobserverSlotTest_27, MoveConstructFromImplicitSlot_27) {
  Slot original = Slot::CreateImplicit();

  Slot moved(std::move(original));

  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsImplicit());
  EXPECT_FALSE(moved.IsExplicit());
  // Again, we avoid calling GetExplicitValue() for an implicit slot.
}
