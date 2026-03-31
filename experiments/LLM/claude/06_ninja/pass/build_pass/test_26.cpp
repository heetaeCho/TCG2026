#include "gtest/gtest.h"
#include "jobserver.h"

// Test default constructor creates an invalid slot
TEST(JobserverSlotTest_26, DefaultConstructorCreatesInvalidSlot_26) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsValid());
}

// Test CreateExplicit creates a valid slot
TEST(JobserverSlotTest_26, CreateExplicitCreatesValidSlot_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_TRUE(slot.IsValid());
}

// Test CreateExplicit creates an explicit slot (not implicit)
TEST(JobserverSlotTest_26, CreateExplicitIsExplicit_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_FALSE(slot.IsImplicit());
}

// Test CreateExplicit preserves the value
TEST(JobserverSlotTest_26, CreateExplicitPreservesValue_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(99);
  EXPECT_EQ(99, slot.GetExplicitValue());
}

// Test CreateExplicit with value 0
TEST(JobserverSlotTest_26, CreateExplicitWithZero_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(0);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(0, slot.GetExplicitValue());
}

// Test CreateExplicit with max uint8_t value
TEST(JobserverSlotTest_26, CreateExplicitWithMaxValue_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(255);
  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(255, slot.GetExplicitValue());
}

// Test CreateImplicit creates a valid slot
TEST(JobserverSlotTest_26, CreateImplicitCreatesValidSlot_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsValid());
}

// Test CreateImplicit creates an implicit slot (not explicit)
TEST(JobserverSlotTest_26, CreateImplicitIsImplicit_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test default constructed slot is neither implicit nor explicit
TEST(JobserverSlotTest_26, DefaultSlotIsNeitherImplicitNorExplicit_26) {
  Jobserver::Slot slot;
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

// Test move constructor transfers validity
TEST(JobserverSlotTest_26, MoveConstructorTransfersValidity_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
  EXPECT_TRUE(slot1.IsValid());

  Jobserver::Slot slot2(std::move(slot1));
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsExplicit());
  EXPECT_EQ(10, slot2.GetExplicitValue());
}

// Test move constructor invalidates source
TEST(JobserverSlotTest_26, MoveConstructorInvalidatesSource_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
  Jobserver::Slot slot2(std::move(slot1));
  EXPECT_FALSE(slot1.IsValid());
}

// Test move assignment transfers validity
TEST(JobserverSlotTest_26, MoveAssignmentTransfersValidity_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(77);
  Jobserver::Slot slot2;
  
  slot2 = std::move(slot1);
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsExplicit());
  EXPECT_EQ(77, slot2.GetExplicitValue());
}

// Test move assignment invalidates source
TEST(JobserverSlotTest_26, MoveAssignmentInvalidatesSource_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(77);
  Jobserver::Slot slot2;
  
  slot2 = std::move(slot1);
  EXPECT_FALSE(slot1.IsValid());
}

// Test move constructor with implicit slot
TEST(JobserverSlotTest_26, MoveConstructorWithImplicitSlot_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot slot2(std::move(slot1));
  
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsImplicit());
  EXPECT_FALSE(slot1.IsValid());
}

// Test move assignment with implicit slot
TEST(JobserverSlotTest_26, MoveAssignmentWithImplicitSlot_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot slot2;
  
  slot2 = std::move(slot1);
  EXPECT_TRUE(slot2.IsValid());
  EXPECT_TRUE(slot2.IsImplicit());
  EXPECT_FALSE(slot1.IsValid());
}

// Test multiple CreateExplicit with different values
TEST(JobserverSlotTest_26, MultipleCreateExplicitDifferentValues_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(1);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(128);
  Jobserver::Slot slot3 = Jobserver::Slot::CreateExplicit(255);
  
  EXPECT_EQ(1, slot1.GetExplicitValue());
  EXPECT_EQ(128, slot2.GetExplicitValue());
  EXPECT_EQ(255, slot3.GetExplicitValue());
}

// Test move assignment overwrites existing valid slot
TEST(JobserverSlotTest_26, MoveAssignmentOverwritesExistingSlot_26) {
  Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
  Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(20);
  
  slot1 = std::move(slot2);
  EXPECT_TRUE(slot1.IsValid());
  EXPECT_EQ(20, slot1.GetExplicitValue());
  EXPECT_FALSE(slot2.IsValid());
}

// Test that default constructed slot moved from remains invalid
TEST(JobserverSlotTest_26, MoveFromDefaultSlotRemainsInvalid_26) {
  Jobserver::Slot slot1;
  Jobserver::Slot slot2(std::move(slot1));
  
  EXPECT_FALSE(slot1.IsValid());
  EXPECT_FALSE(slot2.IsValid());
}
