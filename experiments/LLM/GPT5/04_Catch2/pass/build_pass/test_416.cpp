// optional_equal_tests_416.cpp
#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/internal/catch_optional.hpp"

using Catch::Optional;

// A small helper type to verify that Optional<T>'s equality forwards to T::operator==
struct ComparableSpy {
    int id{};
    // Count how many times == is invoked
    static int eq_calls;

    bool operator==(const ComparableSpy& other) const {
        ++eq_calls;
        return id == other.id;
    }
};
int ComparableSpy::eq_calls = 0;

// -------------------- Tests --------------------

TEST(OptionalEqualTest_416, BothNoneAreEqual_416) {
    Optional<int> a;  // none
    Optional<int> b;  // none
    EXPECT_TRUE(a == b);
}

TEST(OptionalEqualTest_416, BothSomeEqual_Int_416) {
    Optional<int> a{42};
    Optional<int> b{42};
    EXPECT_TRUE(a == b);
}

TEST(OptionalEqualTest_416, BothSomeNotEqual_Int_416) {
    Optional<int> a{41};
    Optional<int> b{42};
    EXPECT_FALSE(a == b);
}

TEST(OptionalEqualTest_416, NoneVsSome_LeftNoneRightSome_416) {
    Optional<int> a;       // none
    Optional<int> b{7};    // some
    EXPECT_FALSE(a == b);
}

TEST(OptionalEqualTest_416, NoneVsSome_LeftSomeRightNone_416) {
    Optional<int> a{7};    // some
    Optional<int> b;       // none
    EXPECT_FALSE(a == b);
}

TEST(OptionalEqualTest_416, WorksWithStdString_Equal_416) {
    Optional<std::string> a{std::string("hello")};
    Optional<std::string> b{std::string("hello")};
    EXPECT_TRUE(a == b);
}

TEST(OptionalEqualTest_416, WorksWithStdString_NotEqual_416) {
    Optional<std::string> a{std::string("hello")};
    Optional<std::string> b{std::string("world")};
    EXPECT_FALSE(a == b);
}

TEST(OptionalEqualTest_416, UsesUnderlyingEqualityOperator_Forwarded_416) {
    ComparableSpy::eq_calls = 0;

    Optional<ComparableSpy> a{ComparableSpy{5}};
    Optional<ComparableSpy> b{ComparableSpy{5}};

    EXPECT_TRUE(a == b);                 // should invoke ComparableSpy::operator==
    EXPECT_EQ(1, ComparableSpy::eq_calls);
}

TEST(OptionalEqualTest_416, ReflexiveForSome_416) {
    Optional<int> a{123};
    EXPECT_TRUE(a == a);
}

TEST(OptionalEqualTest_416, ReflexiveForNone_416) {
    Optional<int> a; // none
    EXPECT_TRUE(a == a);
}

TEST(OptionalEqualTest_416, Symmetry_416) {
    Optional<int> a{10};
    Optional<int> b{10};
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);

    Optional<int> c{11};
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(c == a);
}

TEST(OptionalEqualTest_416, TransitivityForEqualValues_416) {
    Optional<int> a{7};
    Optional<int> b{7};
    Optional<int> c{7};
    // If a==b and b==c, then a==c (for equal underlying values)
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == c);
    EXPECT_TRUE(a == c);
}
