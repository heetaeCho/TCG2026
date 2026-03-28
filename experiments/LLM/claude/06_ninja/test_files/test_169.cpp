#include "gtest/gtest.h"
#include "jobserver.h"

// Test fixture for Jobserver::Slot tests
class JobserverSlotTest_169 : public ::testing::Test {
protected:
};

// Test default constructor creates an invalid slot
TEST_F(JobserverSlotTest_169, DefaultConstructorCreatesInvalidSlot_169) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateImplicit creates a valid implicit slot
TEST_F(JobserverSlotTest_169, CreateImplicitCreatesValidImplicitSlot_169) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateExplicit creates a valid explicit slot
TEST_F(JobserverSlotTest_169, CreateExplicitCreatesValidExplicitSlot_169) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
}

// Test GetExplicitValue returns the correct value for explicit slot
TEST_F(JobserverSlotTest_169, GetExplicitValueReturnsCorrectValue_169) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(100);
  EXPECT_EQ(slot.GetExplicitValue(), 100);
}

// Test GetExplicitValue with boundary value 0
TEST_F(JobserverSlotTest_169, CreateExplicitWithZeroValue_169) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(0);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(slot.GetExplicitValue(), 0);
}

// Test GetExplicitValue with boundary value 255 (max uint8_t)
TEST_F(JobserverSlotTest_169, CreateExplicitWithMaxValue_169) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(255);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(slot.GetExplicitValue(), 255);
}

// Test move constructor transfers validity
TEST_F(JobserverSlotTest_169, MoveConstructorTransfersValidity_169) {
  Jobserver::Slot original = Jobserver::Slot::CreateExplicit(50);
  EXPECT_TRUE(original.IsValid());

  Jobserver::Slot moved(std::move(original));
  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsExplicit());
  EXPECT_EQ(moved.GetExplicitValue(), 50);

  // Original should be invalidated after move
  EXPECT_FALSE(original.IsValid());
}

// Test move constructor with implicit slot
TEST_F(JobserverSlotTest_169, MoveConstructorWithImplicitSlot_169) {
  Jobserver::Slot original = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(original.IsValid());
  EXPECT_TRUE(original.IsImplicit());

  Jobserver::Slot moved(std::move(original));
  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsImplicit());

  EXPECT_FALSE(original.IsValid());
}

// Test move constructor with default (invalid) slot
TEST_F(JobserverSlotTest_169, MoveConstructorWithInvalidSlot_169) {
  Jobserver::Slot original;
  EXPECT_FALSE(original.IsValid());

  Jobserver::Slot moved(std::move(original));
  EXPECT_FALSE(moved.IsValid());
  EXPECT_FALSE(original.IsValid());
}

// Test move assignment operator
TEST_F(JobserverSlotTest_169, MoveAssignmentOperator_169) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(77);
  Jobserver::Slot slot2;

  EXPECT_TRUE(slot1.IsValid());
  EXPECT_FALSE(slot2.IsValid());

  slot2 = std::move(slot1);

  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsExplicit());
  EXPECT_EQ(slot2.GetExplicitValue(), 77);
  EXPECT_FALSE(slot1.IsValid());
}

// Test move assignment with implicit slot
TEST_F(JobserverSlotTest_169, MoveAssignmentWithImplicitSlot_169) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot slot2;

  slot2 = std::move(slot1);

  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsImplicit());
  EXPECT_FALSE(slot1.IsValid());
}

// Test move assignment replaces existing value
TEST_F(JobserverSlotTest_169, MoveAssignmentReplacesExistingValue_169) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(20);

  slot2 = std::move(slot1);

  EXPECT_TRUE(slot2.IsValid());
  EXPECT_EQ(slot2.GetExplicitValue(), 10);
  EXPECT_FALSE(slot1.IsValid());
}

// Test that implicit and explicit slots are mutually exclusive
TEST_F(JobserverSlotTest_169, ImplicitAndExplicitAreMutuallyExclusive_169) {
  Jobserver::Slot implicit = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(implicit.IsImplicit());
  EXPECT_FALSE(implicit.IsExplicit());

  Jobserver::Slot explicit_slot = Jobserver::Slot::CreateExplicit(1);
  EXPECT_TRUE(explicit_slot.IsExplicit());
  EXPECT_FALSE(explicit_slot.IsImplicit());
}

// Test default slot is neither implicit nor explicit
TEST_F(JobserverSlotTest_169, DefaultSlotIsNeitherImplicitNorExplicit_169) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsValid());
}

// Test multiple explicit slots with different values
TEST_F(JobserverSlotTest_169, MultipleExplicitSlotsWithDifferentValues_169) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(0);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(128);
  Jobserver::Slot slot3 = Jobserver::Slot::CreateExplicit(255);

  EXPECT_EQ(slot1.GetExplicitValue(), 0);
  EXPECT_EQ(slot2.GetExplicitValue(), 128);
  EXPECT_EQ(slot3.GetExplicitValue(), 255);
}

// Test chained moves
TEST_F(JobserverSlotTest_169, ChainedMoves_169) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(33);
  Jobserver::Slot slot2(std::move(slot1));
  Jobserver::Slot slot3(std::move(slot2));

  EXPECT_FALSE(slot1.IsValid());
  EXPECT_FALSE(slot2.IsValid());
  EXPECT_TRUE(slot3.IsValid());
  EXPECT_EQ(slot3.GetExplicitValue(), 33);
}

// Test move assignment to self-like scenario (different objects)
TEST_F(JobserverSlotTest_169, MoveAssignmentFromInvalidToInvalid_169) {
  Jobserver::Slot slot1;
  Jobserver::Slot slot2;

  slot2 = std::move(slot1);

  EXPECT_FALSE(slot1.IsValid());
  EXPECT_FALSE(slot2.IsValid());
}
