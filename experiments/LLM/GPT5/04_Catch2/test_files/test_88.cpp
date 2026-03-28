// File: range_to_string_tests_88.cpp

#include <gtest/gtest.h>
#include <vector>
#include <forward_list>
#include <string>

// Include the header under test (path based on the prompt)
#include "Catch2/src/catch2/catch_tostring.hpp"

using Catch::Detail::rangeToString;

namespace {

// Simple streamable type to verify interaction with stream insertion
struct Box {
    int v;
};

std::ostream& operator<<(std::ostream& os, const Box& b) {
    return os << "Box(" << b.v << ")";
}

} // namespace

// [Behavior] Empty range produces just braces with spacing: "{ }"
TEST(RangeToStringTest_88, EmptyRange_YieldsBracesOnly_88) {
    std::vector<int> v; // empty

    const std::string s = rangeToString(v.begin(), v.end());

    EXPECT_EQ(s, "{ }");
}

// [Behavior] Single element range has no comma, spaces preserved: "{ 42 }"
TEST(RangeToStringTest_88, SingleElement_NoComma_88) {
    std::vector<int> v{42};

    const std::string s = rangeToString(v.begin(), v.end());

    EXPECT_EQ(s, "{ 42 }");
}

// [Behavior] Multiple elements are comma-separated with a space after comma
TEST(RangeToStringTest_88, MultipleElements_CommaSeparated_88) {
    std::vector<int> v{1, 2, 3};

    const std::string s = rangeToString(v.begin(), v.end());

    EXPECT_EQ(s, "{ 1, 2, 3 }");
}

// [Behavior] Works with forward iterators (e.g., std::forward_list)
TEST(RangeToStringTest_88, ForwardIteratorCategory_Supported_88) {
    std::forward_list<int> fl{10, 20, 30};

    const std::string s = rangeToString(fl.begin(), fl.end());

    EXPECT_EQ(s, "{ 10, 20, 30 }");
}

// [Behavior] Accepts raw pointer iterator ranges (array begin/end)
TEST(RangeToStringTest_88, RawPointerIterators_ArrayRange_88) {
    int arr[] = {7, 8, 9};
    const std::string s = rangeToString(std::begin(arr), std::end(arr));

    EXPECT_EQ(s, "{ 7, 8, 9 }");
}

// [Behavior] Elements are stringified via stream insertion when available
TEST(RangeToStringTest_88, StreamableCustomType_UsesOstreamInsertion_88) {
    std::vector<Box> boxes{{1}, {2}};
    const std::string s = rangeToString(boxes.begin(), boxes.end());

    // Expect the custom operator<< format to appear
    EXPECT_EQ(s, "{ Box(1), Box(2) }");
}

