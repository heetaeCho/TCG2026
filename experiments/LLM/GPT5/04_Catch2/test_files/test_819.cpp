// File: tests/reporter_helpers_serialize_filters_819_tests.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// We only declare the interface; the test binary must link against
// Catch2/src/catch2/reporters/catch_reporter_helpers.cpp
namespace Catch {
    std::string serializeFilters(std::vector<std::string> const& filters);
}

using Catch::serializeFilters;

class SerializeFiltersTest_819 : public ::testing::Test {};

// Normal operation: single element => returned verbatim (no extra spaces)
TEST_F(SerializeFiltersTest_819, SingleFilter_ReturnsSame_819) {
    std::vector<std::string> in = {"tag1"};
    EXPECT_EQ(serializeFilters(in), "tag1");
}

// Normal operation: multiple elements => joined with a single space between
TEST_F(SerializeFiltersTest_819, MultipleFilters_JoinedWithSingleSpaces_819) {
    std::vector<std::string> in = {"tag1", "[slow]", "~foo"};
    EXPECT_EQ(serializeFilters(in), "tag1 [slow] ~foo");
}

// Boundary condition: preserves internal whitespace inside elements (no trimming)
TEST_F(SerializeFiltersTest_819, PreservesInternalWhitespace_819) {
    std::vector<std::string> in = {"alpha beta", "gamma  delta", "eps"};
    // Internal spaces are preserved; only a single space is inserted between elements
    EXPECT_EQ(serializeFilters(in), "alpha beta gamma  delta eps");
}

// Boundary condition: Unicode / UTF-8 content is preserved byte-for-byte
TEST_F(SerializeFiltersTest_819, PreservesUnicodeContent_819) {
    std::vector<std::string> in = {"태그A", "빠름", "테스트"};
    EXPECT_EQ(serializeFilters(in), "태그A 빠름 테스트");
}

// Boundary condition: ensures no trailing space when multiple elements exist
TEST_F(SerializeFiltersTest_819, NoTrailingSpaceAndCorrectOrder_819) {
    std::vector<std::string> in = {"a", "b", "c"};
    std::string out = serializeFilters(in);
    EXPECT_EQ(out, "a b c");
    ASSERT_FALSE(out.empty());
    EXPECT_NE(out.back(), ' ');
}

// Exceptional case (observable through interface): empty input
// The provided implementation computes size_t(filters.size() - 1) and then
// reserves that capacity, which on standard libraries results in
// std::length_error for empty input. We assert that a standard exception is thrown.
// If your standard library reliably throws std::length_error here, you can
// narrow this to EXPECT_THROW(..., std::length_error).
TEST_F(SerializeFiltersTest_819, EmptyInput_Throws_819) {
    std::vector<std::string> in;
#if defined(__GLIBCXX__) || defined(_LIBCPP_VERSION)
    EXPECT_THROW(serializeFilters(in), std::length_error);
#else
    EXPECT_THROW(serializeFilters(in), std::exception);
#endif
}
