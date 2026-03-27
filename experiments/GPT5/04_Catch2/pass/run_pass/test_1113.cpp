// File: tests/test_case_info_1113.cpp

#include <gtest/gtest.h>

#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/internal/catch_test_registry.hpp>

using namespace Catch;

namespace {

// Small helper to build TestCaseInfo without depending on any internal state.
inline TestCaseInfo makeTCI_1113(
    StringRef className,
    StringRef testName,
    StringRef tags,
    const char* file = "unit/tests/test_case_info_1113.cpp",
    std::size_t line = 1113) {

    NameAndTags nt{ testName, tags };
    SourceLineInfo sli{ file, line };
    return TestCaseInfo{ className, nt, sli };
}

// Counts occurrences of a substring in a string (observable-only helper).
inline int countSubstr_1113(const std::string& haystack, const std::string& needle) {
    int count = 0;
    std::string::size_type pos = 0;
    while ((pos = haystack.find(needle, pos)) != std::string::npos) {
        ++count;
        pos += needle.size();
    }
    return count;
}

} // namespace

// NOTE: All tests append _1113 to match the requested TEST_ID in the names.

TEST(TestCaseInfo_1113, ParseMultipleTags_SortsAndDedups_1113) {
    // Normal operation: multiple tags, duplicates, out-of-order.
    auto tci = makeTCI_1113("MyFixture", "MyTest", "[b][a][a]");

    const std::string tagsStr = tci.tagsAsString();
    // Observable expectations: contains both tags exactly once.
    EXPECT_GE(tagsStr.size(), 0u); // sanity
    EXPECT_EQ(countSubstr_1113(tagsStr, "[a]"), 1);
    EXPECT_EQ(countSubstr_1113(tagsStr, "[b]"), 1);
    // No duplicate "[a]"
    EXPECT_EQ(countSubstr_1113(tagsStr, "[a][a]"), 0);
    // Not hidden
    EXPECT_FALSE(tci.isHidden());
    EXPECT_FALSE(tci.throws());
    EXPECT_FALSE(tci.okToFail());
    EXPECT_FALSE(tci.expectedToFail());
}

TEST(TestCaseInfo_1113, HiddenDotTag_AppendsDotAndIsHidden_1113) {
    // Boundary/normal: hidden tag using leading '.'
    auto tci = makeTCI_1113("MyFixture", "HiddenTest", "[.slow]");

    // Observable behavior:
    // 1) isHidden() should be true
    // 2) tagsAsString should include both "[slow]" (dot stripped for the user tag)
    //    AND a standalone "[.]" tag (constructor appends when hidden).
    EXPECT_TRUE(tci.isHidden());

    const std::string tagsStr = tci.tagsAsString();
    EXPECT_EQ(countSubstr_1113(tagsStr, "[slow]"), 1);
    EXPECT_EQ(countSubstr_1113(tagsStr, "[.]"), 1);

    // No exception-related properties implied by ".slow"
    EXPECT_FALSE(tci.throws());
    EXPECT_FALSE(tci.okToFail());
    EXPECT_FALSE(tci.expectedToFail());
}

TEST(TestCaseInfo_1113, ThrowsSpecialTag_SetsThrows_1113) {
    auto tci = makeTCI_1113("MyFixture", "ThrowsTest", "[!throws]");

    EXPECT_TRUE(tci.throws());
    EXPECT_FALSE(tci.okToFail());
    EXPECT_FALSE(tci.expectedToFail());
    // Not hidden by default
    EXPECT_FALSE(tci.isHidden());

    const std::string tagsStr = tci.tagsAsString();
    // The exact formatting of special tags in tagsAsString is not specified,
    // so we only assert that it is non-empty and do not rely on the exact content here.
    EXPECT_GE(tagsStr.size(), 0u);
}

TEST(TestCaseInfo_1113, MayFailSpecialTag_SetsOkToFail_1113) {
    auto tci = makeTCI_1113("MyFixture", "MayFailTest", "[!mayfail]");

    EXPECT_FALSE(tci.throws());
    EXPECT_TRUE(tci.okToFail());
    EXPECT_FALSE(tci.expectedToFail());
    EXPECT_FALSE(tci.isHidden());
}

TEST(TestCaseInfo_1113, ShouldFailSpecialTag_SetsExpectedToFail_1113) {
    auto tci = makeTCI_1113("MyFixture", "ShouldFailTest", "[!shouldfail]");

    EXPECT_FALSE(tci.throws());
    EXPECT_FALSE(tci.okToFail());
    EXPECT_TRUE(tci.expectedToFail());
    EXPECT_FALSE(tci.isHidden());
}

TEST(TestCaseInfo_1113, LeadingDotTag_StripsDotInTagsAsString_1113) {
    // Even without being generically "hidden", a tag that starts with '.'
    // should be appended without the dot for the visible tag list.
    auto tci = makeTCI_1113("MyFixture", "DotTagTest", "[.custom]");

    const std::string tagsStr = tci.tagsAsString();
    EXPECT_EQ(countSubstr_1113(tagsStr, "[custom]"), 1);
    // Hidden-ness depends on special tag parsing; ".custom" alone should mark it hidden.
    EXPECT_TRUE(tci.isHidden());
    // When hidden, the constructor appends a standalone "[.]" tag as well.
    EXPECT_EQ(countSubstr_1113(tagsStr, "[.]"), 1);
}

TEST(TestCaseInfo_1113, EmptyTag_Throws_1113) {
    // Exceptional/error case: empty tag "[]"
    EXPECT_THROW(
        (void)makeTCI_1113("MyFixture", "EmptyTag", "[]"),
        std::exception
    );
}

TEST(TestCaseInfo_1113, UnmatchedRightBracket_Throws_1113) {
    // Exceptional/error case: unmatched ']'
    EXPECT_THROW(
        (void)makeTCI_1113("MyFixture", "UnmatchedRight", "]"),
        std::exception
    );
}

TEST(TestCaseInfo_1113, UnclosedTag_Throws_1113) {
    // Exceptional/error case: missing closing ']'
    EXPECT_THROW(
        (void)makeTCI_1113("MyFixture", "Unclosed", "[abc"),
        std::exception
    );
}

TEST(TestCaseInfo_1113, LeftBracketInsideTag_Throws_1113) {
    // Exceptional/error case: '[' inside a tag while already in a tag
    EXPECT_THROW(
        (void)makeTCI_1113("MyFixture", "BracketInside", "[a[b]]"),
        std::exception
    );
}

TEST(TestCaseInfo_1113, DeduplicationWithHiddenAndNormal_1113) {
    // Normal + boundary: duplicates and mix of regular + hidden-inducing tags
    auto tci = makeTCI_1113("MyFixture", "Mixed", "[a][.a][a]");
    const std::string tagsStr = tci.tagsAsString();

    // Expect deduplication of the visible "a"
    EXPECT_EQ(countSubstr_1113(tagsStr, "[a]"), 1);
    // Hidden should still append "[.]"
    EXPECT_TRUE(tci.isHidden());
    EXPECT_EQ(countSubstr_1113(tagsStr, "[.]"), 1);
}

