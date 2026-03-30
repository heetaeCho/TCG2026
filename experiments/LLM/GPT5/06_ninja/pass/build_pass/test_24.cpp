// File: jobserver_slot_test_24.cc

#include <gtest/gtest.h>
#include <type_traits>

#include "jobserver.h"  // Adjust include path if needed

class JobserverSlotTest_24 : public ::testing::Test {
protected:
    using Slot = Jobserver::Slot;
};

// Optional: compile-time checks for move-only semantics.
static_assert(!std::is_copy_constructible<Jobserver::Slot>::value,
              "Jobserver::Slot must not be copy constructible");
static_assert(!std::is_copy_assignable<Jobserver::Slot>::value,
              "Jobserver::Slot must not be copy assignable");
static_assert(std::is_move_constructible<Jobserver::Slot>::value,
              "Jobserver::Slot must be move constructible");
static_assert(std::is_move_assignable<Jobserver::Slot>::value,
              "Jobserver::Slot must be move assignable");

// Default-constructed Slot should be invalid and neither implicit nor explicit.
TEST_F(JobserverSlotTest_24,
       DefaultConstructedSlot_IsInvalidAndNotImplicitOrExplicit_24) {
    Slot s;

    EXPECT_FALSE(s.IsValid());
    EXPECT_FALSE(s.IsImplicit());
    EXPECT_FALSE(s.IsExplicit());
}

// CreateImplicit should produce a valid implicit Slot that is not explicit.
TEST_F(JobserverSlotTest_24,
       CreateImplicitSlot_IsValidImplicitAndNotExplicit_24) {
    Slot s = Slot::CreateImplicit();

    EXPECT_TRUE(s.IsValid());
    EXPECT_TRUE(s.IsImplicit());
    EXPECT_FALSE(s.IsExplicit());
}

// CreateExplicit should produce a valid explicit Slot that is not implicit
// and GetExplicitValue should return the value used during creation.
TEST_F(JobserverSlotTest_24,
       CreateExplicitSlot_IsValidExplicitAndReturnsGivenValue_24) {
    const uint8_t explicit_value = 5;
    Slot s = Slot::CreateExplicit(explicit_value);

    EXPECT_TRUE(s.IsValid());
    EXPECT_TRUE(s.IsExplicit());
    EXPECT_FALSE(s.IsImplicit());
    EXPECT_EQ(explicit_value, s.GetExplicitValue());
}

// Boundary values for explicit slots (0 and 255) should be preserved
// by GetExplicitValue and keep the Slot explicit and valid.
TEST_F(JobserverSlotTest_24,
       CreateExplicitSlot_PreservesBoundaryExplicitValues_24) {
    // Lower boundary: 0
    {
        const uint8_t value = 0;
        Slot s = Slot::CreateExplicit(value);

        EXPECT_TRUE(s.IsValid());
        EXPECT_TRUE(s.IsExplicit());
        EXPECT_FALSE(s.IsImplicit());
        EXPECT_EQ(value, s.GetExplicitValue());
    }

    // Upper boundary: 255
    {
        const uint8_t value = 255;
        Slot s = Slot::CreateExplicit(value);

        EXPECT_TRUE(s.IsValid());
        EXPECT_TRUE(s.IsExplicit());
        EXPECT_FALSE(s.IsImplicit());
        EXPECT_EQ(value, s.GetExplicitValue());
    }
}

// Move construction should preserve the observable state of the Slot
// being moved-from (we only assert about the moved-to object, since
// the moved-from state is unspecified by the interface).
TEST_F(JobserverSlotTest_24,
       MoveConstruction_PreservesExplicitStateInDestination_24) {
    const uint8_t explicit_value = 42;
    Slot original = Slot::CreateExplicit(explicit_value);

    Slot moved(std::move(original));

    EXPECT_TRUE(moved.IsValid());
    EXPECT_TRUE(moved.IsExplicit());
    EXPECT_FALSE(moved.IsImplicit());
    EXPECT_EQ(explicit_value, moved.GetExplicitValue());

    // Do not assert anything about `original` after move; its state is unspecified.
}

// Move assignment should preserve the observable state from the source
// in the destination Slot. We again do not assert about the moved-from object.
TEST_F(JobserverSlotTest_24,
       MoveAssignment_PreservesExplicitStateInDestination_24) {
    const uint8_t src_value = 100;
    Slot src = Slot::CreateExplicit(src_value);
    Slot dest = Slot::CreateImplicit();  // some different initial state

    dest = std::move(src);

    EXPECT_TRUE(dest.IsValid());
    EXPECT_TRUE(dest.IsExplicit());
    EXPECT_FALSE(dest.IsImplicit());
    EXPECT_EQ(src_value, dest.GetExplicitValue());

    // No checks on `src` after move assignment (state unspecified).
}

// Type trait test via Google Test: verify observable move-only semantics.
TEST_F(JobserverSlotTest_24,
       TypeTraits_IndicateMoveOnlySemantics_24) {
    EXPECT_FALSE(std::is_copy_constructible<Slot>::value);
    EXPECT_FALSE(std::is_copy_assignable<Slot>::value);
    EXPECT_TRUE(std::is_move_constructible<Slot>::value);
    EXPECT_TRUE(std::is_move_assignable<Slot>::value);
}
