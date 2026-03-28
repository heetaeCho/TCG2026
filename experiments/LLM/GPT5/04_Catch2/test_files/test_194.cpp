// File: describe_multi_matcher_tests_194.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <array>

// Use the public StringRef type from Catch2.
#include "catch2/internal/catch_stringref.hpp"

// Forward declaration of the function under test (no implementation here).
namespace Catch { namespace Matchers { namespace Detail {
    std::string describe_multi_matcher(Catch::StringRef combine,
                                       std::string const* descriptions_begin,
                                       std::string const* descriptions_end);
}}}

// Test fixture with a small helper to call the function under test.
class DescribeMultiMatcherTest_194 : public ::testing::Test {
protected:
    static std::string Call(Catch::StringRef combine,
                            const std::vector<std::string>& descs) {
        const std::string* begin = descs.data();
        const std::string* end   = descs.data() + descs.size();
        return Catch::Matchers::Detail::describe_multi_matcher(combine, begin, end);
    }

    template <size_t N>
    static std::string Call(Catch::StringRef combine,
                            const std::array<std::string, N>& descs) {
        const std::string* begin = descs.data();
        const std::string* end   = descs.data() + descs.size();
        return Catch::Matchers::Detail::describe_multi_matcher(combine, begin, end);
    }
};

// Normal operation: two items joined by ", "
TEST_F(DescribeMultiMatcherTest_194, JoinsTwoDescriptionsWithCommaSpace_194) {
    std::vector<std::string> descs = {"one", "two"};
    auto out = Call(Catch::StringRef(", "), descs);
    EXPECT_EQ(out, "( one, two )");
}

// Normal operation: single item should not be preceded/followed by the combiner (beyond outer spaces)
TEST_F(DescribeMultiMatcherTest_194, SingleDescriptionNoExtraneousCombiner_194) {
    std::vector<std::string> descs = {"only"};
    auto out = Call(Catch::StringRef(", "), descs);
    EXPECT_EQ(out, "( only )");
}

// Normal operation: three items with a multi-character combiner
TEST_F(DescribeMultiMatcherTest_194, JoinsThreeWithPipeCombiner_194) {
    std::vector<std::string> descs = {"a", "b", "c"};
    auto out = Call(Catch::StringRef(" | "), descs);
    EXPECT_EQ(out, "( a | b | c )");
}

// Boundary: empty combiner (default-constructed StringRef) — items should be directly concatenated
TEST_F(DescribeMultiMatcherTest_194, EmptyCombinerConcatenates_194) {
    std::vector<std::string> descs = {"alpha", "beta"};
    Catch::StringRef empty; // default-constructed -> empty string
    auto out = Call(empty, descs);
    // Expect only the outer spaces and parentheses from the function
    EXPECT_EQ(out, "( alphabeta )");
}

// Boundary: empty description list — expect minimal wrapper "( )"
TEST_F(DescribeMultiMatcherTest_194, EmptyDescriptionsProduceMinimalParens_194) {
    // Use std::array with 0 elements to safely provide begin==end pointers
    const std::array<std::string, 0> descs{};
    auto out = Call(Catch::StringRef(", "), descs);
    EXPECT_EQ(out, "( )");
}

// Boundary: non-ASCII (UTF-8) inputs should be preserved and joined correctly
TEST_F(DescribeMultiMatcherTest_194, NonAsciiDescriptionsArePreserved_194) {
    std::vector<std::string> descs = {"가", "나", "다"};
    auto out = Call(Catch::StringRef(" + "), descs);
    EXPECT_EQ(out, "( 가 + 나 + 다 )");
}

// Stress-ish: larger set to ensure formatting holds for many entries (observable output only)
TEST_F(DescribeMultiMatcherTest_194, ManyEntriesFormattedCorrectly_194) {
    std::vector<std::string> descs;
    for (int i = 1; i <= 10; ++i) descs.push_back("x" + std::to_string(i));
    const Catch::StringRef combiner(";");
    auto out = Call(combiner, descs);

    // Build expected output purely from the public behavior (join + wrapper)
    std::string expected = "( ";
    for (size_t i = 0; i < descs.size(); ++i) {
        if (i > 0) expected += ";";
        expected += descs[i];
    }
    expected += " )";

    EXPECT_EQ(out, expected);
}
