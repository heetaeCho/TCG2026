// File: is_empty_matcher_tests_231.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include <stack>
#include <initializer_list>
#include <type_traits>

// Include the header under test
#include "Catch2/src/catch2/matchers/catch_matchers_container_properties.hpp"

using Catch::Matchers::IsEmptyMatcher;

namespace {

// A minimal custom "range-like" type with a conforming empty() member.
// This lets std::empty(obj) resolve to obj.empty() without relying on internals.
struct CustomRange {
    bool is_empty = true;
    bool empty() const noexcept { return is_empty; }
};

} // namespace

// ---------- Normal operation on common containers ----------

TEST(IsEmptyMatcherTest_231, ReturnsTrueForEmptyVector_231) {
    IsEmptyMatcher m;
    std::vector<int> v;
    EXPECT_TRUE(m.match(v));
}

TEST(IsEmptyMatcherTest_231, ReturnsFalseForNonEmptyVector_231) {
    IsEmptyMatcher m;
    std::vector<int> v = {1, 2, 3};
    EXPECT_FALSE(m.match(v));
}

TEST(IsEmptyMatcherTest_231, ReturnsTrueForEmptyString_231) {
    IsEmptyMatcher m;
    std::string s;
    EXPECT_TRUE(m.match(s));
}

TEST(IsEmptyMatcherTest_231, ReturnsFalseForNonEmptyString_231) {
    IsEmptyMatcher m;
    std::string s = "catch2";
    EXPECT_FALSE(m.match(s));
}

// ---------- Boundary / edge cases ----------

TEST(IsEmptyMatcherTest_231, ReturnsTrueForZeroSizedStdArray_231) {
    IsEmptyMatcher m;
    std::array<int, 0> a{};
    EXPECT_TRUE(m.match(a));
}

TEST(IsEmptyMatcherTest_231, WorksWithCBuiltInArray_231) {
    IsEmptyMatcher m;
    // Built-in arrays are not zero-sized in standard C++, so only non-empty check applies.
    int arr[3] = {1, 2, 3};
    EXPECT_FALSE(m.match(arr));
}

TEST(IsEmptyMatcherTest_231, AcceptsRvalueTemporaryContainer_231) {
    IsEmptyMatcher m;
    // rvalue temporary should be accepted by the forwarding reference parameter
    EXPECT_TRUE(m.match(std::vector<int>{}));
    EXPECT_FALSE(m.match(std::vector<int>{1}));
}

// ---------- Other range-like types supported by std::empty ----------

TEST(IsEmptyMatcherTest_231, WorksWithStdStackAdapter_231) {
    IsEmptyMatcher m;
    std::stack<int> st;
    EXPECT_TRUE(m.match(st));
    st.push(42);
    EXPECT_FALSE(m.match(st));
}

TEST(IsEmptyMatcherTest_231, WorksWithInitializerList_231) {
    IsEmptyMatcher m;
    EXPECT_TRUE(m.match(std::initializer_list<int>{}));
    EXPECT_FALSE(m.match(std::initializer_list<int>{10}));
}

// ---------- Custom type with empty() member (ADL via std::empty) ----------

TEST(IsEmptyMatcherTest_231, WorksWithCustomRangeHavingEmptyMember_231) {
    IsEmptyMatcher m;
    CustomRange r1{true};
    CustomRange r2{false};
    EXPECT_TRUE(m.match(r1));
    EXPECT_FALSE(m.match(r2));
}
