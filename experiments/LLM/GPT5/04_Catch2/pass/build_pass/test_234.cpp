// File: size_matches_matcher_describe_tests_234.cpp
#include <gtest/gtest.h>

// Include the header under test (path from your project root may differ)
#include "catch2/matchers/catch_matchers_container_properties.hpp"

namespace {

// A minimal external collaborator used only for its public describe() method.
// This is NOT simulating internal behavior of SizeMatchesMatcher; it’s a
// stand-in Matcher that provides an observable description string.
struct StubMatcher {
    std::string desc;
    std::string describe() const { return desc; }
};

} // namespace

// Normal operation: concatenates the prefix with the collaborator's description
TEST(SizeMatchesMatcher_234, DescribeConcatenatesPrefixAndInnerDescription_234) {
    using Catch::Matchers::SizeMatchesMatcher;

    StubMatcher inner{ "be 3" };
    SizeMatchesMatcher<StubMatcher> uut(inner);

    EXPECT_EQ(uut.describe(), "size matches be 3");
}

// Boundary: inner description is empty -> expect only the fixed prefix
TEST(SizeMatchesMatcher_234, DescribeHandlesEmptyInnerDescription_234) {
    using Catch::Matchers::SizeMatchesMatcher;

    StubMatcher inner{ "" };
    SizeMatchesMatcher<StubMatcher> uut(inner);

    EXPECT_EQ(uut.describe(), "size matches ");
}

// Unicode / non-ASCII content should be passed through unchanged
TEST(SizeMatchesMatcher_234, DescribePreservesUnicodeInnerDescription_234) {
    using Catch::Matchers::SizeMatchesMatcher;

    StubMatcher inner{ u8"길이가 5" };
    SizeMatchesMatcher<StubMatcher> uut(inner);

    EXPECT_EQ(uut.describe(), u8"size matches 길이가 5");
}

// Special characters are preserved literally (no escaping/formatting inferred)
TEST(SizeMatchesMatcher_234, DescribePreservesSpecialCharacters_234) {
    using Catch::Matchers::SizeMatchesMatcher;

    StubMatcher inner{ R"(exactly [0..3] items?)" };
    SizeMatchesMatcher<StubMatcher> uut(inner);

    EXPECT_EQ(uut.describe(), R"(size matches exactly [0..3] items?)");
}

// Multiple instances with different inner matchers should reflect their own descriptions
TEST(SizeMatchesMatcher_234, DescribeReflectsPerInstanceInnerMatcher_234) {
    using Catch::Matchers::SizeMatchesMatcher;

    StubMatcher innerA{ "== 0" };
    StubMatcher innerB{ ">= 10" };
    SizeMatchesMatcher<StubMatcher> uutA(innerA);
    SizeMatchesMatcher<StubMatcher> uutB(innerB);

    EXPECT_EQ(uutA.describe(), "size matches == 0");
    EXPECT_EQ(uutB.describe(), "size matches >= 10");
}
