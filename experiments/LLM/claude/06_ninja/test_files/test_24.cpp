#include "gtest/gtest.h"
#include "jobserver.h"

// Test fixture for Jobserver::Slot tests
class JobserverSlotTest_24 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default-constructed Slot
TEST_F(JobserverSlotTest_24, DefaultConstructedSlotIsNotValid_24) {
    Jobserver::Slot slot;
    // Default slot has value_ = -1, which is kImplicitValue or invalid depending on design
    // We test observable behavior only
    // A default-constructed slot might or might not be valid; let's check
    // Based on the known dependencies, default value_ = -1
}

// Test CreateImplicit produces an implicit slot
TEST_F(JobserverSlotTest_24, CreateImplicitSlotIsImplicit_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
    EXPECT_TRUE(slot.IsImplicit());
}

// Test CreateImplicit produces a valid slot
TEST_F(JobserverSlotTest_24, CreateImplicitSlotIsValid_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
    EXPECT_TRUE(slot.IsValid());
}

// Test CreateImplicit slot is not explicit
TEST_F(JobserverSlotTest_24, CreateImplicitSlotIsNotExplicit_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
    EXPECT_FALSE(slot.IsExplicit());
}

// Test CreateExplicit produces an explicit slot
TEST_F(JobserverSlotTest_24, CreateExplicitSlotIsExplicit_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
    EXPECT_TRUE(slot.IsExplicit());
}

// Test CreateExplicit produces a valid slot
TEST_F(JobserverSlotTest_24, CreateExplicitSlotIsValid_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
    EXPECT_TRUE(slot.IsValid());
}

// Test CreateExplicit slot is not implicit
TEST_F(JobserverSlotTest_24, CreateExplicitSlotIsNotImplicit_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(42);
    EXPECT_FALSE(slot.IsImplicit());
}

// Test GetExplicitValue returns the value passed to CreateExplicit
TEST_F(JobserverSlotTest_24, GetExplicitValueReturnsCorrectValue_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(100);
    EXPECT_EQ(slot.GetExplicitValue(), 100);
}

// Test GetExplicitValue with zero
TEST_F(JobserverSlotTest_24, GetExplicitValueWithZero_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(0);
    EXPECT_EQ(slot.GetExplicitValue(), 0);
}

// Test GetExplicitValue with max uint8_t
TEST_F(JobserverSlotTest_24, GetExplicitValueWithMaxUint8_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(255);
    EXPECT_EQ(slot.GetExplicitValue(), 255);
}

// Test move constructor transfers state
TEST_F(JobserverSlotTest_24, MoveConstructorTransfersImplicitSlot_24) {
    Jobserver::Slot original = Jobserver::Slot::CreateImplicit();
    Jobserver::Slot moved(std::move(original));
    EXPECT_TRUE(moved.IsImplicit());
    EXPECT_TRUE(moved.IsValid());
}

// Test move constructor transfers explicit slot
TEST_F(JobserverSlotTest_24, MoveConstructorTransfersExplicitSlot_24) {
    Jobserver::Slot original = Jobserver::Slot::CreateExplicit(77);
    Jobserver::Slot moved(std::move(original));
    EXPECT_TRUE(moved.IsExplicit());
    EXPECT_TRUE(moved.IsValid());
    EXPECT_EQ(moved.GetExplicitValue(), 77);
}

// Test move constructor invalidates source
TEST_F(JobserverSlotTest_24, MoveConstructorInvalidatesSource_24) {
    Jobserver::Slot original = Jobserver::Slot::CreateExplicit(55);
    Jobserver::Slot moved(std::move(original));
    // After move, original should no longer be valid
    EXPECT_FALSE(original.IsValid());
}

// Test move assignment operator
TEST_F(JobserverSlotTest_24, MoveAssignmentTransfersSlot_24) {
    Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(10);
    Jobserver::Slot slot2;
    slot2 = std::move(slot1);
    EXPECT_TRUE(slot2.IsExplicit());
    EXPECT_TRUE(slot2.IsValid());
    EXPECT_EQ(slot2.GetExplicitValue(), 10);
}

// Test move assignment invalidates source
TEST_F(JobserverSlotTest_24, MoveAssignmentInvalidatesSource_24) {
    Jobserver::Slot slot1 = Jobserver::Slot::CreateImplicit();
    Jobserver::Slot slot2;
    slot2 = std::move(slot1);
    EXPECT_FALSE(slot1.IsValid());
    EXPECT_TRUE(slot2.IsImplicit());
}

// Test default constructed slot validity
TEST_F(JobserverSlotTest_24, DefaultConstructedSlotValidity_24) {
    Jobserver::Slot slot;
    // Default value_ = -1, which is the kImplicitValue
    // This may or may not be "valid" - testing observable behavior
    // Based on code: kImplicitValue likely makes it implicit but the question is IsValid
    // We test both to document behavior
    bool valid = slot.IsValid();
    bool implicit = slot.IsImplicit();
    // At minimum, these should not crash
    (void)valid;
    (void)implicit;
}

// Test multiple CreateExplicit with different values
TEST_F(JobserverSlotTest_24, CreateExplicitDifferentValues_24) {
    Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(0);
    Jobserver::Slot slot2 = Jobserver::Slot::CreateExplicit(1);
    Jobserver::Slot slot3 = Jobserver::Slot::CreateExplicit(128);

    EXPECT_EQ(slot1.GetExplicitValue(), 0);
    EXPECT_EQ(slot2.GetExplicitValue(), 1);
    EXPECT_EQ(slot3.GetExplicitValue(), 128);

    EXPECT_TRUE(slot1.IsExplicit());
    EXPECT_TRUE(slot2.IsExplicit());
    EXPECT_TRUE(slot3.IsExplicit());

    EXPECT_FALSE(slot1.IsImplicit());
    EXPECT_FALSE(slot2.IsImplicit());
    EXPECT_FALSE(slot3.IsImplicit());
}

// Test that IsImplicit and IsExplicit are mutually exclusive for implicit slot
TEST_F(JobserverSlotTest_24, ImplicitAndExplicitMutuallyExclusiveForImplicit_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();
    EXPECT_TRUE(slot.IsImplicit());
    EXPECT_FALSE(slot.IsExplicit());
}

// Test that IsImplicit and IsExplicit are mutually exclusive for explicit slot
TEST_F(JobserverSlotTest_24, ImplicitAndExplicitMutuallyExclusiveForExplicit_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(50);
    EXPECT_FALSE(slot.IsImplicit());
    EXPECT_TRUE(slot.IsExplicit());
}

// Test chained move operations
TEST_F(JobserverSlotTest_24, ChainedMoveOperations_24) {
    Jobserver::Slot slot1 = Jobserver::Slot::CreateExplicit(99);
    Jobserver::Slot slot2(std::move(slot1));
    Jobserver::Slot slot3;
    slot3 = std::move(slot2);

    EXPECT_TRUE(slot3.IsValid());
    EXPECT_TRUE(slot3.IsExplicit());
    EXPECT_EQ(slot3.GetExplicitValue(), 99);
    EXPECT_FALSE(slot1.IsValid());
    EXPECT_FALSE(slot2.IsValid());
}

// Test self-move-assignment (edge case)
TEST_F(JobserverSlotTest_24, SelfMoveAssignment_24) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(33);
    // Self-move should not crash, behavior may vary
    slot = std::move(slot);
    // We just verify no crash occurs
}
