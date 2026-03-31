#include "gtest/gtest.h"
#include "jobserver.h"

// Test fixture for Jobserver::Slot
class JobserverSlotTest_25 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction creates an invalid slot
TEST_F(JobserverSlotTest_25, DefaultConstructedSlotIsNotValid_25) {
    Jobserver::Slot slot;
    EXPECT_FALSE(slot.IsValid());
}

// Test default constructed slot is not explicit
TEST_F(JobserverSlotTest_25, DefaultConstructedSlotIsNotExplicit_25) {
    Jobserver::Slot slot;
    EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateImplicit creates a valid slot
TEST_F(JobserverSlotTest_25, ImplicitSlotIsValid_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
    EXPECT_TRUE(slot.IsValid());
}

// Test CreateImplicit creates an implicit slot
TEST_F(JobserverSlotTest_25, ImplicitSlotIsImplicit_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
    EXPECT_TRUE(slot.IsImplicit());
}

// Test CreateImplicit slot is not explicit
TEST_F(JobserverSlotTest_25, ImplicitSlotIsNotExplicit_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
    EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateExplicit creates a valid slot
TEST_F(JobserverSlotTest_25, ExplicitSlotIsValid_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
    EXPECT_TRUE(slot.IsValid());
}

// Test CreateExplicit creates a slot that is explicit
TEST_F(JobserverSlotTest_25, ExplicitSlotIsExplicit_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
    EXPECT_TRUE(slot.IsExplicit());
}

// Test CreateExplicit creates a slot that is not implicit
TEST_F(JobserverSlotTest_25, ExplicitSlotIsNotImplicit_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
    EXPECT_FALSE(slot.IsImplicit());
}

// Test GetExplicitValue returns the value passed to CreateExplicit
TEST_F(JobserverSlotTest_25, ExplicitSlotReturnsCorrectValue_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
    EXPECT_EQ(42, slot.GetExplicitValue());
}

// Test CreateExplicit with value 0
TEST_F(JobserverSlotTest_25, ExplicitSlotWithZeroValue_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(0);
    EXPECT_TRUE(slot.IsValid());
    EXPECT_TRUE(slot.IsExplicit());
    EXPECT_EQ(0, slot.GetExplicitValue());
}

// Test CreateExplicit with max uint8_t value (255)
TEST_F(JobserverSlotTest_25, ExplicitSlotWithMaxValue_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(255);
    EXPECT_TRUE(slot.IsValid());
    EXPECT_TRUE(slot.IsExplicit());
    EXPECT_EQ(255, slot.GetExplicitValue());
}

// Test move constructor transfers state
TEST_F(JobserverSlotTest_25, MoveConstructorTransfersExplicitSlot_25) {
    Jobserver::Slot original = Jobserver::Slot::CreateExplicit(100);
    Jobserver::Slot moved(std::move(original));
    EXPECT_TRUE(moved.IsValid());
    EXPECT_TRUE(moved.IsExplicit());
    EXPECT_EQ(100, moved.GetExplicitValue());
}

// Test move constructor from implicit slot
TEST_F(JobserverSlotTest_25, MoveConstructorTransfersImplicitSlot_25) {
    Jobserver::Slot original = Jobserver::Slot::CreateImplicit();
    Jobserver::Slot moved(std::move(original));
    EXPECT_TRUE(moved.IsValid());
    EXPECT_TRUE(moved.IsImplicit());
    EXPECT_FALSE(moved.IsExplicit());
}

// Test move constructor from default slot
TEST_F(JobserverSlotTest_25, MoveConstructorFromDefaultSlot_25) {
    Jobserver::Slot original;
    Jobserver::Slot moved(std::move(original));
    EXPECT_FALSE(moved.IsValid());
}

// Test move assignment operator with explicit slot
TEST_F(JobserverSlotTest_25, MoveAssignmentExplicitSlot_25) {
    Jobserver::Slot original = Jobserver::Slot::CreateExplicit(77);
    Jobserver::Slot target;
    target = std::move(original);
    EXPECT_TRUE(target.IsValid());
    EXPECT_TRUE(target.IsExplicit());
    EXPECT_EQ(77, target.GetExplicitValue());
}

// Test move assignment operator with implicit slot
TEST_F(JobserverSlotTest_25, MoveAssignmentImplicitSlot_25) {
    Jobserver::Slot original = Jobserver::Slot::CreateImplicit();
    Jobserver::Slot target;
    target = std::move(original);
    EXPECT_TRUE(target.IsValid());
    EXPECT_TRUE(target.IsImplicit());
}

// Test move assignment replaces existing value
TEST_F(JobserverSlotTest_25, MoveAssignmentReplacesExistingValue_25) {
    Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
    Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(20);
    slot1 = std::move(slot2);
    EXPECT_TRUE(slot1.IsValid());
    EXPECT_TRUE(slot1.IsExplicit());
    EXPECT_EQ(20, slot1.GetExplicitValue());
}

// Test IsExplicit logic: IsValid() && !IsImplicit()
// For an explicit slot, IsValid should be true and IsImplicit should be false
TEST_F(JobserverSlotTest_25, IsExplicitConsistencyCheck_25) {
    Jobserver::Slot explicit_slot = Jobserver::Slot::CreateExplicit(1);
    EXPECT_TRUE(explicit_slot.IsValid());
    EXPECT_FALSE(explicit_slot.IsImplicit());
    EXPECT_TRUE(explicit_slot.IsExplicit());

    Jobserver::Slot implicit_slot = Jobserver::Slot::CreateImplicit();
    EXPECT_TRUE(implicit_slot.IsValid());
    EXPECT_TRUE(implicit_slot.IsImplicit());
    EXPECT_FALSE(implicit_slot.IsExplicit());

    Jobserver::Slot default_slot;
    EXPECT_FALSE(default_slot.IsValid());
    EXPECT_FALSE(default_slot.IsExplicit());
}

// Test CreateExplicit with value 1
TEST_F(JobserverSlotTest_25, ExplicitSlotWithValue1_25) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(1);
    EXPECT_TRUE(slot.IsExplicit());
    EXPECT_EQ(1, slot.GetExplicitValue());
}

// Test multiple explicit slots with different values
TEST_F(JobserverSlotTest_25, MultipleExplicitSlotsIndependent_25) {
    Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
    Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(20);
    Jobserver::Slot slot3 = Jobserver::Slot::CreateExplicit(30);

    EXPECT_EQ(10, slot1.GetExplicitValue());
    EXPECT_EQ(20, slot2.GetExplicitValue());
    EXPECT_EQ(30, slot3.GetExplicitValue());
}

// Test that after move, source slot becomes invalid (or at least target is valid)
TEST_F(JobserverSlotTest_25, MoveConstructorInvalidatesSource_25) {
    Jobserver::Slot original = Jobserver::Slot::CreateExplicit(50);
    Jobserver::Slot moved(std::move(original));
    // The moved-to object should be valid
    EXPECT_TRUE(moved.IsValid());
    // After move, original should typically be in an invalid/default state
    EXPECT_FALSE(original.IsValid());
}

// Test that after move assignment, source slot becomes invalid
TEST_F(JobserverSlotTest_25, MoveAssignmentInvalidatesSource_25) {
    Jobserver::Slot original = Jobserver::Slot::CreateImplicit();
    Jobserver::Slot target;
    target = std::move(original);
    EXPECT_TRUE(target.IsValid());
    EXPECT_FALSE(original.IsValid());
}
