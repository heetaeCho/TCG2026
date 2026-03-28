// File: tests/all_true_matcher_test_182.cpp
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <array>
#include <initializer_list>
#include <cstddef>

#include "Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"

using Catch::Matchers::AllTrueMatcher;

namespace {

// A simple type that is explicitly convertible to bool to validate
// the matcher works with non-bool, user-defined "truthy" elements.
struct TruthyThing {
    bool v;
    explicit TruthyThing(bool vv) : v(vv) {}
    explicit operator bool() const { return v; }
};

} // namespace

// Normal operation: all elements true -> true
TEST(AllTrueMatcherTest_182, ReturnsTrueForAllTrueBoolVector_182) {
    AllTrueMatcher m;
    std::vector<bool> v{true, true, true};
    EXPECT_TRUE(m.match(v));
}

// Normal operation: any false element -> false
TEST(AllTrueMatcherTest_182, ReturnsFalseWhenAnyFalseBoolVector_182) {
    AllTrueMatcher m;
    std::vector<bool> v{true, false, true};
    EXPECT_FALSE(m.match(v));
}

// Boundary: empty range should result in true (no falsy elements observed)
TEST(AllTrueMatcherTest_182, ReturnsTrueForEmptyRange_182) {
    AllTrueMatcher m;
    std::vector<bool> empty;
    EXPECT_TRUE(m.match(empty));
}

// Works with initializer_list as a RangeLike
TEST(AllTrueMatcherTest_182, WorksWithInitializerList_182) {
    AllTrueMatcher m;
    EXPECT_TRUE(m.match({true, true}));
    EXPECT_FALSE(m.match({true, false, true}));
}

// Works with non-bool integral types (0 => false, non-zero => true)
TEST(AllTrueMatcherTest_182, WorksWithNonBoolIntegralTypes_182) {
    AllTrueMatcher m;
    std::vector<int> all_nonzero{1, 2, -3, 4};
    std::vector<int> has_zero{1, 0, 2};

    EXPECT_TRUE(m.match(all_nonzero));
    EXPECT_FALSE(m.match(has_zero));
}

// Works with pointer types (nullptr => false, non-null => true)
TEST(AllTrueMatcherTest_182, WorksWithPointerTypes_182) {
    AllTrueMatcher m;
    int a = 1, b = 2;
    std::vector<int*> all_non_null{&a, &b};
    std::vector<int*> has_null{&a, nullptr, &b};

    EXPECT_TRUE(m.match(all_non_null));
    EXPECT_FALSE(m.match(has_null));
}

// Accepts rvalue (temporary) ranges
TEST(AllTrueMatcherTest_182, AcceptsRvalueRange_182) {
    AllTrueMatcher m;
    EXPECT_TRUE(m.match(std::vector<bool>{true, true}));
    EXPECT_FALSE(m.match(std::vector<bool>{true, false}));
}

// Works with different STL containers (array, list)
TEST(AllTrueMatcherTest_182, WorksWithArrayAndList_182) {
    AllTrueMatcher m;
    std::array<bool, 3> arr{{true, true, true}};
    std::list<bool> lst{true, false, true};

    EXPECT_TRUE(m.match(arr));
    EXPECT_FALSE(m.match(lst));
}

// Works with user-defined types that are convertible to bool
TEST(AllTrueMatcherTest_182, WorksWithUserDefinedTruthyType_182) {
    AllTrueMatcher m;
    std::vector<TruthyThing> all_true{TruthyThing(true), TruthyThing(true)};
    std::vector<TruthyThing> has_false{TruthyThing(true), TruthyThing(false)};

    EXPECT_TRUE(m.match(all_true));
    EXPECT_FALSE(m.match(has_false));
}
