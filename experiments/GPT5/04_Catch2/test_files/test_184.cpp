// File: any_true_matcher_test_184.cpp
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <initializer_list>

// Include the provided header
#include "Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"

using Catch::Matchers::AnyTrueMatcher;

namespace {

struct Truthy {
    int v;
    explicit operator bool() const { return v != 0; }
};

} // namespace

// Normal operation: empty range -> false
TEST(AnyTrueMatcherTest_184, EmptyRangeReturnsFalse_184) {
    AnyTrueMatcher m;
    std::vector<bool> input; // empty
    EXPECT_FALSE(m.match(input));
}

// Boundary: single-element (true) -> true
TEST(AnyTrueMatcherTest_184, SingleTrueReturnsTrue_184) {
    AnyTrueMatcher m;
    std::vector<bool> input = {true};
    EXPECT_TRUE(m.match(input));
}

// Boundary: single-element (false) -> false
TEST(AnyTrueMatcherTest_184, SingleFalseReturnsFalse_184) {
    AnyTrueMatcher m;
    std::vector<bool> input = {false};
    EXPECT_FALSE(m.match(input));
}

// Normal: mixture with at least one true -> true
TEST(AnyTrueMatcherTest_184, MixedValuesReturnsTrue_184) {
    AnyTrueMatcher m;
    std::vector<bool> input = {false, false, true, false};
    EXPECT_TRUE(m.match(input));
}

// Normal: all false -> false
TEST(AnyTrueMatcherTest_184, AllFalseReturnsFalse_184) {
    AnyTrueMatcher m;
    std::list<bool> input = {false, false, false};
    EXPECT_FALSE(m.match(input));
}

// Normal: all true -> true
TEST(AnyTrueMatcherTest_184, AllTrueReturnsTrue_184) {
    AnyTrueMatcher m;
    std::list<bool> input = {true, true, true};
    EXPECT_TRUE(m.match(input));
}

// Range compatibility: std::initializer_list
TEST(AnyTrueMatcherTest_184, WorksWithInitializerList_184) {
    AnyTrueMatcher m;
    EXPECT_TRUE(m.match({false, 0, 1, false})); // int literals are convertible to bool
    EXPECT_FALSE(m.match({0, 0, 0}));
}

// Range compatibility: C-style array wrapped in std::array
TEST(AnyTrueMatcherTest_184, WorksWithArray_184) {
    AnyTrueMatcher m;
    std::array<int, 5> a{{0, 0, 0, 0, 0}};
    EXPECT_FALSE(m.match(a));
    std::array<int, 3> b{{0, 2, 0}};
    EXPECT_TRUE(m.match(b));
}

// Type compatibility: non-bool elements convertible to bool
TEST(AnyTrueMatcherTest_184, WorksWithNonBoolConvertibleTypes_184) {
    AnyTrueMatcher m;
    std::vector<int> ints = {0, 0, 5, 0};
    EXPECT_TRUE(m.match(ints));

    std::vector<int> zeros = {0, 0, 0};
    EXPECT_FALSE(m.match(zeros));
}

// Type compatibility: user-defined type with explicit bool conversion
TEST(AnyTrueMatcherTest_184, WorksWithUserDefinedBoolConversion_184) {
    AnyTrueMatcher m;
    std::vector<Truthy> vals = {Truthy{0}, Truthy{0}, Truthy{3}};
    EXPECT_TRUE(m.match(vals));

    std::vector<Truthy> all_zero = {Truthy{0}, Truthy{0}};
    EXPECT_FALSE(m.match(all_zero));
}

// Value category support: rvalue range (temporary container)
TEST(AnyTrueMatcherTest_184, AcceptsRvalueRange_184) {
    AnyTrueMatcher m;
    EXPECT_TRUE(m.match(std::vector<int>{0, 0, 1}));
    EXPECT_FALSE(m.match(std::vector<int>{0, 0, 0}));
}
