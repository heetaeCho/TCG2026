#include "gtest/gtest.h"
#include "jobserver.h"

// Test that a default-constructed Slot is not valid
TEST(JobserverSlotTest_23, DefaultConstructedSlotIsNotValid_23) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsValid());
}

// Test that CreateImplicit returns a valid slot
TEST(JobserverSlotTest_23, CreateImplicitReturnsValidSlot_23) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsValid());
}

// Test that CreateExplicit returns a valid slot
TEST(JobserverSlotTest_23, CreateExplicitReturnsValidSlot_23) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(0);
  EXPECT_TRUE(slot.IsValid());
}

// Test that CreateExplicit with various values returns valid slots
TEST(JobserverSlotTest_23, CreateExplicitWithDifferentValues_23) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(0);
  EXPECT_TRUE(slot1.IsValid());

  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(42);
  EXPECT_TRUE(slot2.IsValid());

  Jobserver::Slot slot3 = Jobserver::Slot::CreateExplicit(255);
  EXPECT_TRUE(slot3.IsValid());
}

// Test that an implicit slot is implicit and not explicit
TEST(JobserverSlotTest_23, ImplicitSlotIsImplicit_23) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test that an explicit slot is explicit and not implicit
TEST(JobserverSlotTest_23, ExplicitSlotIsExplicit_23) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(100);
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
}

// Test that a default-constructed slot is neither implicit nor explicit
TEST(JobserverSlotTest_23, DefaultSlotIsNeitherImplicitNorExplicit_23) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test that GetExplicitValue returns the correct value for an explicit slot
TEST(JobserverSlotTest_23, GetExplicitValueReturnsCorrectValue_23) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_EQ(42, slot.GetExplicitValue());
}

// Test GetExplicitValue with boundary values
TEST(JobserverSlotTest_23, GetExplicitValueBoundaryValues_23) {
  Jobserver::Slot slot0 = Jobserver::Slot::CreateExplicit(0);
  EXPECT_EQ(0, slot0.GetExplicitValue());

  Jobserver::Slot slot255 = Jobserver::Slot::CreateExplicit(255);
  EXPECT_EQ(255, slot255.GetExplicitValue());
}

// Test move constructor - source slot becomes invalid after move
TEST(JobserverSlotTest_23, MoveConstructorTransfersOwnership_23) {
  Jobserver::Slot original = Jobserver::Slot::CreateExplicit(77);
  EXPECT_TRUE(original.IsValid());

  Jobserver::Slot moved(std::move(original));
  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsExplicit());
  EXPECT_EQ(77, moved.GetExplicitValue());
  // After move, original should be invalidated
  EXPECT_FALSE(original.IsValid());
}

// Test move assignment operator
TEST(JobserverSlotTest_23, MoveAssignmentTransfersOwnership_23) {
  Jobserver::Slot original = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(original.IsValid());
  EXPECT_TRUE(original.IsImplicit());

  Jobserver::Slot target;
  EXPECT_FALSE(target.IsValid());

  target = std::move(original);
  EXPECT_TRUE(target.IsValid());
  EXPECT_TRUE(target.IsImplicit());
  // After move, original should be invalidated
  EXPECT_FALSE(original.IsValid());
}

// Test move constructor with default (invalid) slot
TEST(JobserverSlotTest_23, MoveConstructorFromInvalidSlot_23) {
  Jobserver::Slot invalid;
  EXPECT_FALSE(invalid.IsValid());

  Jobserver::Slot moved(std::move(invalid));
  EXPECT_FALSE(moved.IsValid());
}

// Test move assignment with explicit slot
TEST(JobserverSlotTest_23, MoveAssignmentExplicitSlot_23) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(20);

  slot1 = std::move(slot2);
  EXPECT_TRUE(slot1.IsValid());
  EXPECT_EQ(20, slot1.GetExplicitValue());
  EXPECT_FALSE(slot2.IsValid());
}

// Test self move assignment (defensive)
TEST(JobserverSlotTest_23, SelfMoveAssignment_23) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(55);
  Jobserver::Slot& ref = slot;
  slot = std::move(ref);
  // Behavior after self-move is implementation-defined, but should not crash
  // We just verify it doesn't crash; validity may or may not hold
}

// Test that multiple CreateImplicit slots are all valid and implicit
TEST(JobserverSlotTest_23, MultipleImplicitSlots_23) {
  Jobserver::Slot s1 = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot s2 = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(s1.IsValid());
  EXPECT_TRUE(s2.IsValid());
  EXPECT_TRUE(s1.IsImplicit());
  EXPECT_TRUE(s2.IsImplicit());
}
