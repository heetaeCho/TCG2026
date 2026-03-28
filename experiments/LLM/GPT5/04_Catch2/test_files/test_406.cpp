// Optional_copy_assignment_tests_406.cpp
#include <gtest/gtest.h>

// Adjust include path as needed for your project layout.
#include "catch2/internal/catch_optional.hpp"

using Catch::Optional;

namespace {

// Simple type without default constructor to ensure no accidental default-inits.
struct NoDefault {
    int v;
    explicit NoDefault(int x) : v(x) {}
    bool operator==(const NoDefault& other) const { return v == other.v; }
    bool operator!=(const NoDefault& other) const { return !(*this == other); }
};

} // namespace

class OptionalCopyAssignTest_406 : public ::testing::Test {};

// Assigning from engaged -> disengaged makes destination engaged with same value
TEST_F(OptionalCopyAssignTest_406, AssignFromEngagedToDisengaged_406) {
    Optional<NoDefault> src{ NoDefault{42} };
    Optional<NoDefault> dst; // disengaged

    dst = src;

    EXPECT_TRUE(dst.some());
    EXPECT_TRUE(src.some());
    EXPECT_EQ((*dst).v, 42);
    EXPECT_EQ((*src).v, 42);
}

// Assigning from disengaged -> engaged makes destination disengaged
TEST_F(OptionalCopyAssignTest_406, AssignFromDisengagedToEngaged_406) {
    Optional<NoDefault> src; // disengaged
    Optional<NoDefault> dst{ NoDefault{7} }; // engaged

    dst = src;

    EXPECT_TRUE(dst.none());
    EXPECT_TRUE(src.none());
}

// Assigning between engaged optionals overwrites the destination's value
TEST_F(OptionalCopyAssignTest_406, AssignBetweenEngagedOverwritesValue_406) {
    Optional<NoDefault> a{ NoDefault{1} };
    Optional<NoDefault> b{ NoDefault{99} };

    a = b;

    ASSERT_TRUE(a.some());
    ASSERT_TRUE(b.some());
    EXPECT_EQ((*a).v, 99);
    EXPECT_EQ((*b).v, 99);
}

// Self-assignment on engaged optional leaves state unchanged
TEST_F(OptionalCopyAssignTest_406, SelfAssignmentEngaged_406) {
    Optional<NoDefault> o{ NoDefault{123} };

    // Take address to compare later and ensure the contained object persists.
    NoDefault* before_addr = &(*o);

    o = o; // self-assign

    ASSERT_TRUE(o.some());
    EXPECT_EQ((*o).v, 123);
    // Still pointing to a valid object, and value not changed
    EXPECT_EQ(&(*o), before_addr);
}

// Self-assignment on disengaged optional remains disengaged
TEST_F(OptionalCopyAssignTest_406, SelfAssignmentDisengaged_406) {
    Optional<NoDefault> o;

    o = o; // self-assign

    EXPECT_TRUE(o.none());
}

// Copy assignment returns self reference
TEST_F(OptionalCopyAssignTest_406, AssignmentReturnsSelfReference_406) {
    Optional<NoDefault> a{ NoDefault{5} };
    Optional<NoDefault> b{ NoDefault{6} };

    Optional<NoDefault>& ret = (a = b);

    EXPECT_EQ(&ret, &a);  // should return *this
    ASSERT_TRUE(a.some());
    EXPECT_EQ((*a).v, 6);
}

// Deep copy: after assignment, modifying source does not affect destination
TEST_F(OptionalCopyAssignTest_406, DeepCopyIndependence_406) {
    Optional<NoDefault> src{ NoDefault{10} };
    Optional<NoDefault> dst;

    dst = src;

    // Addresses of contained values must differ (via public operator*)
    ASSERT_TRUE(src.some());
    ASSERT_TRUE(dst.some());
    EXPECT_NE(&(*src), &(*dst));

    // Change source's contained value; destination should remain unchanged
    *src = NoDefault{77};  // uses Optional::operator=(T const&)
    EXPECT_EQ((*dst).v, 10);
    EXPECT_EQ((*src).v, 77);
}
