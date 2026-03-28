#include "gtest/gtest.h"
#include "jobserver.h"

// Test fixture for Jobserver::Slot tests
class JobserverSlotTest_22 : public ::testing::Test {
protected:
};

// Test default constructed Slot is invalid
TEST_F(JobserverSlotTest_22, DefaultConstructedSlotIsInvalid_22) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsValid());
}

// Test default constructed Slot is neither implicit nor explicit
TEST_F(JobserverSlotTest_22, DefaultConstructedSlotIsNotImplicit_22) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsImplicit());
}

TEST_F(JobserverSlotTest_22, DefaultConstructedSlotIsNotExplicit_22) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateImplicit creates a valid implicit slot
TEST_F(JobserverSlotTest_22, CreateImplicitIsValid_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsValid());
}

TEST_F(JobserverSlotTest_22, CreateImplicitIsImplicit_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsImplicit());
}

TEST_F(JobserverSlotTest_22, CreateImplicitIsNotExplicit_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateExplicit creates a valid explicit slot
TEST_F(JobserverSlotTest_22, CreateExplicitIsValid_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_TRUE(slot.IsValid());
}

TEST_F(JobserverSlotTest_22, CreateExplicitIsExplicit_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_TRUE(slot.IsExplicit());
}

TEST_F(JobserverSlotTest_22, CreateExplicitIsNotImplicit_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_FALSE(slot.IsImplicit());
}

// Test GetExplicitValue returns the correct value
TEST_F(JobserverSlotTest_22, CreateExplicitGetValue_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_EQ(42, slot.GetExplicitValue());
}

TEST_F(JobserverSlotTest_22, CreateExplicitValueZero_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(0);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(0, slot.GetExplicitValue());
}

TEST_F(JobserverSlotTest_22, CreateExplicitValueMax_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(255);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(255, slot.GetExplicitValue());
}

// Test move constructor transfers ownership and invalidates source
TEST_F(JobserverSlotTest_22, MoveConstructorTransfersValidity_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(99);
  Jobserver::Slot slot2(std::move(slot1));
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsExplicit());
  EXPECT_EQ(99, slot2.GetExplicitValue());
}

TEST_F(JobserverSlotTest_22, MoveConstructorInvalidatesSource_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(99);
  Jobserver::Slot slot2(std::move(slot1));
  EXPECT_FALSE(slot1.IsValid());
}

TEST_F(JobserverSlotTest_22, MoveConstructorImplicitSlot_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot slot2(std::move(slot1));
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsImplicit());
  EXPECT_FALSE(slot1.IsValid());
}

// Test move assignment operator transfers ownership and invalidates source
TEST_F(JobserverSlotTest_22, MoveAssignmentTransfersValidity_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(77);
  Jobserver::Slot slot2;
  slot2 = std::move(slot1);
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsExplicit());
  EXPECT_EQ(77, slot2.GetExplicitValue());
}

TEST_F(JobserverSlotTest_22, MoveAssignmentInvalidatesSource_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(77);
  Jobserver::Slot slot2;
  slot2 = std::move(slot1);
  EXPECT_FALSE(slot1.IsValid());
}

// Test self-assignment doesn't invalidate the slot
TEST_F(JobserverSlotTest_22, SelfMoveAssignmentDoesNotInvalidate_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(55);
  Jobserver::Slot& ref = slot;
  slot = std::move(ref);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(55, slot.GetExplicitValue());
}

// Test move assignment from implicit slot
TEST_F(JobserverSlotTest_22, MoveAssignmentImplicitSlot_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot slot2;
  slot2 = std::move(slot1);
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsImplicit());
  EXPECT_FALSE(slot1.IsValid());
}

// Test move assignment from invalid slot to valid slot
TEST_F(JobserverSlotTest_22, MoveAssignmentFromInvalidSlot_22) {
  Jobserver::Slot slot1;
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(10);
  slot2 = std::move(slot1);
  EXPECT_FALSE(slot2.IsValid());
  EXPECT_FALSE(slot1.IsValid());
}

// Test move assignment between two invalid slots
TEST_F(JobserverSlotTest_22, MoveAssignmentBothInvalid_22) {
  Jobserver::Slot slot1;
  Jobserver::Slot slot2;
  slot2 = std::move(slot1);
  EXPECT_FALSE(slot2.IsValid());
  EXPECT_FALSE(slot1.IsValid());
}

// Test multiple moves in chain
TEST_F(JobserverSlotTest_22, ChainedMoves_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(123);
  Jobserver::Slot slot2(std::move(slot1));
  Jobserver::Slot slot3;
  slot3 = std::move(slot2);
  EXPECT_FALSE(slot1.IsValid());
  EXPECT_FALSE(slot2.IsValid());
  EXPECT_TRUE(slot3.IsValid());
  EXPECT_TRUE(slot3.IsExplicit());
  EXPECT_EQ(123, slot3.GetExplicitValue());
}

// Test various explicit values
TEST_F(JobserverSlotTest_22, CreateExplicitValue1_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(1);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(1, slot.GetExplicitValue());
}

TEST_F(JobserverSlotTest_22, CreateExplicitValue128_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(128);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(128, slot.GetExplicitValue());
}

// Test that moved-from default slot stays invalid
TEST_F(JobserverSlotTest_22, MoveFromDefaultSlotStaysInvalid_22) {
  Jobserver::Slot slot1;
  Jobserver::Slot slot2(std::move(slot1));
  EXPECT_FALSE(slot1.IsValid());
  EXPECT_FALSE(slot2.IsValid());
}

// Test overwriting a valid slot with another valid slot via move assignment
TEST_F(JobserverSlotTest_22, MoveAssignmentOverwritesExistingSlot_22) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(20);
  slot1 = std::move(slot2);
  EXPECT_TRUE(slot1.IsValid());
  EXPECT_EQ(20, slot1.GetExplicitValue());
  EXPECT_FALSE(slot2.IsValid());
}

// Test self-assignment with implicit slot
TEST_F(JobserverSlotTest_22, SelfMoveAssignmentImplicit_22) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot& ref = slot;
  slot = std::move(ref);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsImplicit());
}
