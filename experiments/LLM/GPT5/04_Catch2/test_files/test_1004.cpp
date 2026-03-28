// File: test_tag_pattern_matches_1004.cpp
#include <gtest/gtest.h>

#include <catch2/catch_test_spec.hpp>
#include <catch2/catch_test_case_info.hpp>

using namespace Catch;

namespace {

// Minimal helper to build a TestCaseInfo with controllable public fields
TestCaseInfo makeTestCaseInfo(const std::vector<Tag>& seedTags = {}) {
    NameAndTags nt;
    nt.name = "dummy";
    nt.tags = ""; // we won't rely on parsing; we’ll populate tags directly

    // A harmless, fake source location
    SourceLineInfo sli{"dummy.cpp", 123};

    // Construct and then set public fields we care about
    TestCaseInfo tci(StringRef{}, nt, sli);
    // Directly manipulate the public `tags` vector (allowed by interface)
    tci.tags = seedTags;
    return tci;
}

} // namespace

//------------------------------------------------------------------------------
// Normal operation: tag present -> matches == true
//------------------------------------------------------------------------------
TEST(TagPatternMatches_1004, ReturnsTrueWhenExactTagPresent_1004) {
    // Arrange
    TestSpec::TagPattern pattern(/*tag*/"fast", /*filterString*/"[fast]");

    TestCaseInfo tci = makeTestCaseInfo({
        Tag("slow"),
        Tag("fast"),   // the one we expect to match
        Tag("db")
    });

    // Act
    const bool result = pattern.matches(tci);

    // Assert
    EXPECT_TRUE(result);
}

//------------------------------------------------------------------------------
// Normal operation: tag absent -> matches == false
//------------------------------------------------------------------------------
TEST(TagPatternMatches_1004, ReturnsFalseWhenTagAbsent_1004) {
    // Arrange
    TestSpec::TagPattern pattern("network", "[network]");

    TestCaseInfo tci = makeTestCaseInfo({
        Tag("fast"),
        Tag("db"),
        Tag("io")
    });

    // Act
    const bool result = pattern.matches(tci);

    // Assert
    EXPECT_FALSE(result);
}

//------------------------------------------------------------------------------
// Boundary condition: no tags in the test case -> matches == false
//------------------------------------------------------------------------------
TEST(TagPatternMatches_1004, ReturnsFalseWhenNoTags_1004) {
    // Arrange
    TestSpec::TagPattern pattern("anything", "[anything]");

    TestCaseInfo tci = makeTestCaseInfo(/*seedTags=*/{});

    // Act
    const bool result = pattern.matches(tci);

    // Assert
    EXPECT_FALSE(result);
}

//------------------------------------------------------------------------------
// Multiple tags including the target -> matches == true (single positive hit)
//------------------------------------------------------------------------------
TEST(TagPatternMatches_1004, ReturnsTrueWithMultipleTagsWhenTargetPresent_1004) {
    // Arrange
    TestSpec::TagPattern pattern("db", "[db]");

    TestCaseInfo tci = makeTestCaseInfo({
        Tag("unit"),
        Tag("db"),     // match
        Tag("linux"),
        Tag("slow")
    });

    // Act
    const bool result = pattern.matches(tci);

    // Assert
    EXPECT_TRUE(result);
}

//------------------------------------------------------------------------------
// Similar-but-different tag should not match (no assumptions about case rules)
//------------------------------------------------------------------------------
TEST(TagPatternMatches_1004, ReturnsFalseForSimilarButDifferentTag_1004) {
    // NOTE: We avoid asserting any specific normalization logic and only
    // check straightforward, observable behavior using distinct strings.
    TestSpec::TagPattern pattern("Fast", "[Fast]"); // distinct from "fast"

    TestCaseInfo tci = makeTestCaseInfo({
        Tag("fast"),
        Tag("io")
    });

    const bool result = pattern.matches(tci);

    EXPECT_FALSE(result);
}
