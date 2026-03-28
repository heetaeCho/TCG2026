// File: tests/compact_reporter_get_description_812.cpp

#include <gtest/gtest.h>

// Include the implementation unit under test so the minimal class definition is available.
// (In your build, adjust the relative path as needed.)
#include "Catch2/src/catch2/reporters/catch_reporter_compact.cpp"

using Catch::CompactReporter;

// -----------------------------------------------------------------------------
// TEST_ID: 812
// -----------------------------------------------------------------------------

TEST(CompactReporterTest_812, GetDescription_ReturnsExactExpectedText_812) {
    CompactReporter reporter;
    const std::string expected =
        "Reports test results on a single line, suitable for IDEs";

    EXPECT_EQ(reporter.getDescription(), expected);
}

TEST(CompactReporterTest_812, GetDescription_IsStableAcrossMultipleCalls_812) {
    CompactReporter reporter;
    const std::string first = reporter.getDescription();
    const std::string second = reporter.getDescription();

    EXPECT_EQ(first, second);
}

TEST(CompactReporterTest_812, GetDescription_NoThrowAndNonEmpty_812) {
    CompactReporter reporter;

    std::string desc;
    EXPECT_NO_THROW(desc = reporter.getDescription());
    EXPECT_FALSE(desc.empty());
}

TEST(CompactReporterTest_812, GetDescription_NotAffectedByCallerModifications_812) {
    CompactReporter reporter;
    const std::string original = reporter.getDescription();

    // Caller modifies its own copy
    std::string mutated = original;
    mutated.append(" (mutated)");

    // Subsequent calls should be unaffected
    const std::string after = reporter.getDescription();
    EXPECT_EQ(after, original);
}
