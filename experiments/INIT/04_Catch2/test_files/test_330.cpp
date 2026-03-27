// test_extended_mult_result_330.cpp
#include <gtest/gtest.h>
#include <limits>

// Include the provided interface header
#include "Catch2/src/catch2/internal/catch_random_integer_helpers.hpp"

namespace cd = Catch::Detail;

// ---- Compile-time (constexpr) verification ----
// Ensures operator== is constexpr-usable without re-implementing logic.
constexpr cd::ExtendedMultResult<int> kA_330{1, 2};
constexpr cd::ExtendedMultResult<int> kB_330{1, 2};
static_assert(kA_330 == kB_330, "operator== must compare upper & lower and be usable in constexpr context");

// ---------------- Runtime tests ----------------

struct ExtendedMultResultTest_330 : ::testing::Test {};

// Normal operation: equality when both fields match
TEST_F(ExtendedMultResultTest_330, EqualWhenUpperAndLowerMatch_330) {
    cd::ExtendedMultResult<int> a{42, 7};
    cd::ExtendedMultResult<int> b{42, 7};
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);  // symmetry
}

// Boundary conditions: min/max values of a signed type
TEST_F(ExtendedMultResultTest_330, NotEqualWhenUpperDiffers_330) {
    using T = int;
    cd::ExtendedMultResult<T> a{std::numeric_limits<T>::max(), std::numeric_limits<T>::min()};
    cd::ExtendedMultResult<T> b{std::numeric_limits<T>::min(), std::numeric_limits<T>::min()};
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST_F(ExtendedMultResultTest_330, NotEqualWhenLowerDiffers_330) {
    using T = int;
    cd::ExtendedMultResult<T> a{std::numeric_limits<T>::max(), 0};
    cd::ExtendedMultResult<T> b{std::numeric_limits<T>::max(), 1};
    EXPECT_FALSE(a == b);
}

// Sanity: reflexivity
TEST_F(ExtendedMultResultTest_330, ReflexiveEquality_330) {
    cd::ExtendedMultResult<int> a{123, 456};
    EXPECT_TRUE(a == a);
}

// Type coverage with an unsigned wide type
TEST_F(ExtendedMultResultTest_330, EqualityWithUnsignedWideType_330) {
    using T = unsigned long long;
    T up = static_cast<T>(~T{0});     // all bits 1 => max
    T low = 0;

    cd::ExtendedMultResult<T> a{up, low};
    cd::ExtendedMultResult<T> b{up, low};
    cd::ExtendedMultResult<T> c{up - 1, low};  // differs in upper

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

// Mixed differences: both fields differ still mean inequality (observable behavior)
TEST_F(ExtendedMultResultTest_330, NotEqualWhenBothFieldsDiffer_330) {
    cd::ExtendedMultResult<int> a{10, 20};
    cd::ExtendedMultResult<int> b{11, 19};
    EXPECT_FALSE(a == b);
}
