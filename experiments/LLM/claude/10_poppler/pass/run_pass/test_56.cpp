#include <gtest/gtest.h>
#include "Object.h"

// Test that INVALID() returns a Ref with num == -1 and gen == -1
TEST(RefTest_56, InvalidRefHasNegativeOneNum_56) {
    constexpr Ref invalidRef = Ref::INVALID();
    EXPECT_EQ(invalidRef.num, -1);
}

TEST(RefTest_56, InvalidRefHasNegativeOneGen_56) {
    constexpr Ref invalidRef = Ref::INVALID();
    EXPECT_EQ(invalidRef.gen, -1);
}

// Test that INVALID() is constexpr and can be used at compile time
TEST(RefTest_56, InvalidRefIsConstexpr_56) {
    static_assert(Ref::INVALID().num == -1, "INVALID num should be -1");
    static_assert(Ref::INVALID().gen == -1, "INVALID gen should be -1");
}

// Test that two calls to INVALID() return the same values
TEST(RefTest_56, InvalidRefIsConsistent_56) {
    Ref r1 = Ref::INVALID();
    Ref r2 = Ref::INVALID();
    EXPECT_EQ(r1.num, r2.num);
    EXPECT_EQ(r1.gen, r2.gen);
}

// Test that a default-constructed or custom Ref can have different values
TEST(RefTest_56, RefCanHaveCustomValues_56) {
    Ref r;
    r.num = 5;
    r.gen = 10;
    EXPECT_EQ(r.num, 5);
    EXPECT_EQ(r.gen, 10);
}

// Test that a Ref with num=0 and gen=0 is not the same as INVALID
TEST(RefTest_56, ZeroRefIsNotInvalid_56) {
    Ref r;
    r.num = 0;
    r.gen = 0;
    Ref inv = Ref::INVALID();
    EXPECT_NE(r.num, inv.num);
    EXPECT_NE(r.gen, inv.gen);
}

// Test boundary: Ref with num=-1 but gen=0 is not fully INVALID
TEST(RefTest_56, PartialInvalidNum_56) {
    Ref r;
    r.num = -1;
    r.gen = 0;
    Ref inv = Ref::INVALID();
    EXPECT_EQ(r.num, inv.num);
    EXPECT_NE(r.gen, inv.gen);
}

// Test boundary: Ref with num=0 but gen=-1 is not fully INVALID
TEST(RefTest_56, PartialInvalidGen_56) {
    Ref r;
    r.num = 0;
    r.gen = -1;
    Ref inv = Ref::INVALID();
    EXPECT_NE(r.num, inv.num);
    EXPECT_EQ(r.gen, inv.gen);
}

// Test that Ref fields can hold large positive values
TEST(RefTest_56, RefLargePositiveValues_56) {
    Ref r;
    r.num = 2147483647; // INT_MAX
    r.gen = 2147483647;
    EXPECT_EQ(r.num, 2147483647);
    EXPECT_EQ(r.gen, 2147483647);
}

// Test that a Ref matching INVALID values exactly
TEST(RefTest_56, RefMatchingInvalidValues_56) {
    Ref r;
    r.num = -1;
    r.gen = -1;
    Ref inv = Ref::INVALID();
    EXPECT_EQ(r.num, inv.num);
    EXPECT_EQ(r.gen, inv.gen);
}
