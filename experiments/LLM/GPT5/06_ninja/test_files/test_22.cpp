#include <gtest/gtest.h>

#include "jobserver.h"
#include <utility>  // for std::move

// Fixture for Jobserver::Slot tests (TEST_ID = 22)
class JobserverSlotTest_22 : public ::testing::Test {
protected:
    Jobserver::Slot MakeExplicit(uint8_t value) {
        return Jobserver::Slot::CreateExplicit(value);
    }

    Jobserver::Slot MakeImplicit() {
        return Jobserver::Slot::CreateImplicit();
    }
};

// Normal operation: move-assign from explicit to default-constructed slot.
TEST_F(JobserverSlotTest_22, MoveAssign_ExplicitToDefault_DestinationGetsValue_SourceInvalid_22) {
    Jobserver::Slot source = Jobserver::Slot::CreateExplicit(7);
    Jobserver::Slot dest;  // default constructed

    // Precondition checks (based on public interface).
    EXPECT_TRUE(source.IsValid());
    EXPECT_TRUE(source.IsExplicit());
    EXPECT_EQ(7u, source.GetExplicitValue());

    // dest is expected to be invalid by default (since value_ starts as -1).
    EXPECT_FALSE(dest.IsValid());

    dest = std::move(source);

    // Destination should now hold the explicit value.
    EXPECT_TRUE(dest.IsValid());
    EXPECT_TRUE(dest.IsExplicit());
    EXPECT_EQ(7u, dest.GetExplicitValue());

    // Source should become invalid after move assignment.
    EXPECT_FALSE(source.IsValid());
    EXPECT_FALSE(source.IsExplicit());
    EXPECT_FALSE(source.IsImplicit());
}

// Normal operation: move-assign from implicit to default-constructed slot.
TEST_F(JobserverSlotTest_22, MoveAssign_ImplicitToDefault_DestinationImplicit_SourceInvalid_22) {
    Jobserver::Slot source = Jobserver::Slot::CreateImplicit();
    Jobserver::Slot dest;  // default constructed

    // Precondition checks.
    EXPECT_TRUE(source.IsValid());
    EXPECT_TRUE(source.IsImplicit());
    EXPECT_FALSE(source.IsExplicit());
    EXPECT_FALSE(dest.IsValid());

    dest = std::move(source);

    // Destination should now represent an implicit valid slot.
    EXPECT_TRUE(dest.IsValid());
    EXPECT_TRUE(dest.IsImplicit());
    EXPECT_FALSE(dest.IsExplicit());

    // Source should become invalid after move assignment.
    EXPECT_FALSE(source.IsValid());
    EXPECT_FALSE(source.IsImplicit());
    EXPECT_FALSE(source.IsExplicit());
}

// Boundary: self move-assignment must be safe and leave the object unchanged.
TEST_F(JobserverSlotTest_22, MoveAssign_SelfAssignment_KeepsState_22) {
    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(5);

    // Precondition checks.
    EXPECT_TRUE(slot.IsValid());
    EXPECT_TRUE(slot.IsExplicit());
    EXPECT_EQ(5u, slot.GetExplicitValue());

    // Self move-assignment: operator= has a self-check (this != &o).
    slot = std::move(slot);

    // State should be unchanged.
    EXPECT_TRUE(slot.IsValid());
    EXPECT_TRUE(slot.IsExplicit());
    EXPECT_EQ(5u, slot.GetExplicitValue());
}

// Normal/overwrite case: destination already holds a value and is overwritten.
TEST_F(JobserverSlotTest_22, MoveAssign_OverwritesExistingDestinationValue_22) {
    Jobserver::Slot source = Jobserver::Slot::CreateExplicit(9);
    Jobserver::Slot dest = Jobserver::Slot::CreateExplicit(3);

    // Precondition checks.
    EXPECT_TRUE(source.IsValid());
    EXPECT_TRUE(source.IsExplicit());
    EXPECT_EQ(9u, source.GetExplicitValue());

    EXPECT_TRUE(dest.IsValid());
    EXPECT_TRUE(dest.IsExplicit());
    EXPECT_EQ(3u, dest.GetExplicitValue());

    dest = std::move(source);

    // Destination should now have source's explicit value.
    EXPECT_TRUE(dest.IsValid());
    EXPECT_TRUE(dest.IsExplicit());
    EXPECT_EQ(9u, dest.GetExplicitValue());

    // Source should be invalidated.
    EXPECT_FALSE(source.IsValid());
    EXPECT_FALSE(source.IsExplicit());
    EXPECT_FALSE(source.IsImplicit());
}

// Boundary/error-ish case: move-assign from an invalid (default-constructed) slot.
TEST_F(JobserverSlotTest_22, MoveAssign_FromInvalidSource_MakesDestinationInvalid_22) {
    Jobserver::Slot source;  // invalid by default
    Jobserver::Slot dest = Jobserver::Slot::CreateExplicit(4);

    // Precondition checks.
    EXPECT_FALSE(source.IsValid());

    EXPECT_TRUE(dest.IsValid());
    EXPECT_TRUE(dest.IsExplicit());
    EXPECT_EQ(4u, dest.GetExplicitValue());

    dest = std::move(source);

    // After move, dest should now reflect the (invalid) state of source.
    EXPECT_FALSE(dest.IsValid());
    EXPECT_FALSE(dest.IsExplicit());
    EXPECT_FALSE(dest.IsImplicit());

    // Source should remain invalid after move.
    EXPECT_FALSE(source.IsValid());
    EXPECT_FALSE(source.IsExplicit());
    EXPECT_FALSE(source.IsImplicit());
}
