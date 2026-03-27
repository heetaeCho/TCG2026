// File: jobserver_slot_test_169.cc

#include "gtest/gtest.h"
#include "jobserver.h"

#include <utility>  // for std::move

// TEST_ID: 169

// Verifies default-constructed slot is invalid and has no category flags set.
TEST(JobserverSlotTest_169, DefaultInvalidAndCategoryFlags_169) {
  Jobserver::Slot slot;

  EXPECT_FALSE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Verifies that CreateImplicit() returns a valid implicit slot.
TEST(JobserverSlotTest_169, CreateImplicitProducesValidImplicitSlot_169) {
  Jobserver::Slot implicit = Jobserver::Slot::CreateImplicit();

  EXPECT_TRUE(implicit.IsValid());
  EXPECT_TRUE(implicit.IsImplicit());
  EXPECT_FALSE(implicit.IsExplicit());
}

// Verifies that CreateExplicit() produces valid explicit slots for boundary values.
TEST(JobserverSlotTest_169, CreateExplicitProducesValidExplicitSlotsAtBoundaries_169) {
  // Lower boundary (0).
  Jobserver::Slot slot0 = Jobserver::Slot::CreateExplicit(0u);
  EXPECT_TRUE(slot0.IsValid());
  EXPECT_FALSE(slot0.IsImplicit());
  EXPECT_TRUE(slot0.IsExplicit());
  EXPECT_EQ(0u, slot0.GetExplicitValue());

  // Middle value.
  Jobserver::Slot slot42 = Jobserver::Slot::CreateExplicit(42u);
  EXPECT_TRUE(slot42.IsValid());
  EXPECT_FALSE(slot42.IsImplicit());
  EXPECT_TRUE(slot42.IsExplicit());
  EXPECT_EQ(42u, slot42.GetExplicitValue());

  // Upper boundary (255).
  Jobserver::Slot slot255 = Jobserver::Slot::CreateExplicit(255u);
  EXPECT_TRUE(slot255.IsValid());
  EXPECT_FALSE(slot255.IsImplicit());
  EXPECT_TRUE(slot255.IsExplicit());
  EXPECT_EQ(255u, slot255.GetExplicitValue());
}

// Verifies that the move constructor transfers the slot value
// and invalidates the source, for both explicit and implicit slots.
TEST(JobserverSlotTest_169, MoveConstructorTransfersAndInvalidatesSource_169) {
  // Explicit slot move.
  Jobserver::Slot explicit_src = Jobserver::Slot::CreateExplicit(7u);
  Jobserver::Slot explicit_dst(std::move(explicit_src));

  EXPECT_FALSE(explicit_src.IsValid());
  EXPECT_TRUE(explicit_dst.IsValid());
  EXPECT_TRUE(explicit_dst.IsExplicit());
  EXPECT_EQ(7u, explicit_dst.GetExplicitValue());

  // Implicit slot move.
  Jobserver::Slot implicit_src = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot implicit_dst(std::move(implicit_src));

  EXPECT_FALSE(implicit_src.IsValid());
  EXPECT_TRUE(implicit_dst.IsValid());
  EXPECT_TRUE(implicit_dst.IsImplicit());
  EXPECT_FALSE(implicit_dst.IsExplicit());
}

// Verifies that move assignment transfers the slot value
// and invalidates the source, including overwriting an existing destination.
TEST(JobserverSlotTest_169, MoveAssignmentTransfersAndInvalidatesSource_169) {
  // Move from explicit to explicit.
  Jobserver::Slot src = Jobserver::Slot::CreateExplicit(10u);
  Jobserver::Slot dst = Jobserver::Slot::CreateExplicit(99u);

  dst = std::move(src);

  EXPECT_FALSE(src.IsValid());
  EXPECT_TRUE(dst.IsValid());
  EXPECT_TRUE(dst.IsExplicit());
  EXPECT_EQ(10u, dst.GetExplicitValue());

  // Move from implicit to a previously explicit slot.
  Jobserver::Slot implicit_src = Jobserver::Slot::CreateImplicit();
  dst = std::move(implicit_src);

  EXPECT_FALSE(implicit_src.IsValid());
  EXPECT_TRUE(dst.IsValid());
  EXPECT_TRUE(dst.IsImplicit());
  EXPECT_FALSE(dst.IsExplicit());
}

// Verifies that self move-assignment is safe and keeps the slot unchanged.
TEST(JobserverSlotTest_169, SelfMoveAssignmentKeepsSlotUnchanged_169) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(13u);

  // Self move: operator= should guard against this and keep the value.
  slot = std::move(slot);

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_EQ(13u, slot.GetExplicitValue());
}

// Verifies that moving from an invalid slot results in an invalid destination.
TEST(JobserverSlotTest_169, MoveFromInvalidProducesInvalidDestination_169) {
  Jobserver::Slot invalid;  // default-constructed -> invalid
  Jobserver::Slot dst = Jobserver::Slot::CreateExplicit(1u);

  dst = std::move(invalid);

  EXPECT_FALSE(invalid.IsValid());
  EXPECT_FALSE(dst.IsValid());
  EXPECT_FALSE(dst.IsImplicit());
  EXPECT_FALSE(dst.IsExplicit());
}
