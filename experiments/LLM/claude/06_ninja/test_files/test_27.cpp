#include "gtest/gtest.h"
#include "jobserver.h"

// Test default constructor creates an invalid slot
TEST(JobserverSlotTest_27, DefaultConstructorCreatesInvalidSlot_27) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateImplicit creates a valid implicit slot
TEST(JobserverSlotTest_27, CreateImplicitCreatesValidImplicitSlot_27) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateExplicit creates a valid explicit slot
TEST(JobserverSlotTest_27, CreateExplicitCreatesValidExplicitSlot_27) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_TRUE(slot.IsExplicit());
}

// Test GetExplicitValue returns the value passed to CreateExplicit
TEST(JobserverSlotTest_27, GetExplicitValueReturnsCorrectValue_27) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(99);
  EXPECT_EQ(slot.GetExplicitValue(), 99);
}

// Test CreateExplicit with value 0
TEST(JobserverSlotTest_27, CreateExplicitWithZeroValue_27) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(0);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_EQ(slot.GetExplicitValue(), 0);
}

// Test CreateExplicit with max uint8_t value
TEST(JobserverSlotTest_27, CreateExplicitWithMaxUint8Value_27) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(255);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(slot.GetExplicitValue(), 255);
}

// Test move constructor transfers ownership
TEST(JobserverSlotTest_27, MoveConstructorTransfersOwnership_27) {
  Jobserver::Slot original = Jobserver::Slot::CreateExplicit(77);
  Jobserver::Slot moved(std::move(original));
  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsExplicit());
  EXPECT_EQ(moved.GetExplicitValue(), 77);
  // After move, original should be invalid
  EXPECT_FALSE(original.IsValid());
}

// Test move constructor with implicit slot
TEST(JobserverSlotTest_27, MoveConstructorWithImplicitSlot_27) {
  Jobserver::Slot original = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot moved(std::move(original));
  EXPECT_TRUE(moved.IsValid());
  EXPECT_TRUE(moved.IsImplicit());
  EXPECT_FALSE(original.IsValid());
}

// Test move assignment operator
TEST(JobserverSlotTest_27, MoveAssignmentOperator_27) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsValid());
  slot = Jobserver::Slot::CreateExplicit(50);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(slot.GetExplicitValue(), 50);
}

// Test move assignment invalidates source
TEST(JobserverSlotTest_27, MoveAssignmentInvalidatesSource_27) {
  Jobserver::Slot source = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot dest;
  dest = std::move(source);
  EXPECT_TRUE(dest.IsValid());
  EXPECT_TRUE(dest.IsImplicit());
  EXPECT_FALSE(source.IsValid());
}

// Test move assignment overwriting a valid slot
TEST(JobserverSlotTest_27, MoveAssignmentOverwritesExistingSlot_27) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(20);
  slot1 = std::move(slot2);
  EXPECT_TRUE(slot1.IsValid());
  EXPECT_EQ(slot1.GetExplicitValue(), 20);
  EXPECT_FALSE(slot2.IsValid());
}

// Test default slot is not implicit and not explicit
TEST(JobserverSlotTest_27, DefaultSlotIsNeitherImplicitNorExplicit_27) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test multiple CreateExplicit calls with different values
TEST(JobserverSlotTest_27, MultipleExplicitSlotsHaveDifferentValues_27) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(1);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(2);
  Jobserver::Slot slot3 = Jobserver::Slot::CreateExplicit(128);
  EXPECT_EQ(slot1.GetExplicitValue(), 1);
  EXPECT_EQ(slot2.GetExplicitValue(), 2);
  EXPECT_EQ(slot3.GetExplicitValue(), 128);
}

// Test move constructor from default (invalid) slot
TEST(JobserverSlotTest_27, MoveConstructorFromDefaultSlot_27) {
  Jobserver::Slot original;
  Jobserver::Slot moved(std::move(original));
  EXPECT_FALSE(moved.IsValid());
  EXPECT_FALSE(original.IsValid());
}

// Test move assignment from default (invalid) slot
TEST(JobserverSlotTest_27, MoveAssignmentFromDefaultSlot_27) {
  Jobserver::Slot dest = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot source;
  dest = std::move(source);
  EXPECT_FALSE(dest.IsValid());
}
