// File: tests/UnorderedRangeEqualsMatcher_describe_959.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the amalgamated Catch2 header that contains the matcher under test.
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::HasSubstr;

namespace {

// A simple type whose stringification we fully control via StringMaker.
// This lets us verify that `describe()` uses Catch's stringify on m_desired
// without relying on Catch2's built-in formatting for STL containers, etc.
struct DummyRange {};
struct EmptyPrintable {};

// Provide Catch2 stringification for our custom types.
} // namespace

namespace Catch {

// Specialization returning a fixed token so we can compare exactly.
template<>
struct StringMaker<DummyRange> {
    static std::string convert(const DummyRange&) {
        return "DUMMY";
    }
};

// Specialization returning an empty string to test boundary behavior.
template<>
struct StringMaker<EmptyPrintable> {
    static std::string convert(const EmptyPrintable&) {
        return ""; // boundary: empty stringify
    }
};

} // namespace Catch

// Convenience aliases to the template under test.
template <typename Desired, typename Eq>
using UREM = Catch::Matchers::UnorderedRangeEqualsMatcher<Desired, Eq>;

//
// TESTS
//

// Verifies that describe() prefixes with the fixed text and uses Catch::Detail::stringify on m_desired.
TEST(UnorderedRangeEqualsMatcherTest_959, DescribeUsesStringifyWithCustomType_959) {
    DummyRange desired{};
    auto eq = std::equal_to<int>{};

    UREM<DummyRange, decltype(eq)> matcher(desired, eq);

    EXPECT_EQ("unordered elements are DUMMY", matcher.describe());
}

// Boundary: When stringify(m_desired) is empty, describe() should still return the prefix unchanged + empty tail.
TEST(UnorderedRangeEqualsMatcherTest_959, DescribeWithEmptyStringifiedDesired_959) {
    EmptyPrintable desired{};
    auto eq = std::equal_to<int>{};

    UREM<EmptyPrintable, decltype(eq)> matcher(desired, eq);

    EXPECT_EQ("unordered elements are ", matcher.describe());
}

// Sanity: Using a standard container should still include the prefix and (non-exact) signals of the content,
// without depending on Catch2's exact formatting of containers.
TEST(UnorderedRangeEqualsMatcherTest_959, DescribeIncludesPrefixAndHintsOfContent_959) {
    std::vector<int> desired{1, 2, 1};
    auto eq = std::equal_to<int>{};

    UREM<decltype(desired), decltype(eq)> matcher(desired, eq);

    const std::string desc = matcher.describe();
    EXPECT_THAT(desc, HasSubstr("unordered elements are "));
    // Avoid relying on exact container formatting; just ensure content is represented.
    EXPECT_THAT(desc, HasSubstr("1"));
    EXPECT_THAT(desc, HasSubstr("2"));
}

// Verify that describe() output depends only on m_desired (observable via constructor arguments),
// not on the equality predicate value/type.
TEST(UnorderedRangeEqualsMatcherTest_959, DescribeIndependentOfPredicate_959) {
    DummyRange desired{};

    auto eq_true  = [](int, int){ return true; };
    auto eq_false = [](int, int){ return false; };

    UREM<DummyRange, decltype(eq_true)>  m1(desired, eq_true);
    UREM<DummyRange, decltype(eq_false)> m2(desired, eq_false);

    EXPECT_EQ(m1.describe(), m2.describe());
    EXPECT_EQ("unordered elements are DUMMY", m1.describe());
}
