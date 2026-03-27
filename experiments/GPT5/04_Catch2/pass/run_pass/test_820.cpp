// File: tests/ReporterHelpers_LineOfChars_820.tests.cpp

// Force a deterministic console width for the test TU so expectations are stable.
// We only depend on the public configuration knob; no internal logic is inferred.
#ifndef CATCH_CONFIG_CONSOLE_WIDTH
#  define CATCH_CONFIG_CONSOLE_WIDTH 8  // expect (width - 1) = 7 characters written
#endif

#include <gtest/gtest.h>
#include <sstream>

// Public interface under test
#include "Catch2/src/catch2/reporters/catch_reporter_helpers.hpp"

using Catch::lineOfChars;

class LineOfCharsTest_820 : public ::testing::Test {
protected:
    static constexpr std::size_t kExpectedCount = CATCH_CONFIG_CONSOLE_WIDTH - 1;
};

// [Normal] Writes exactly (CATCH_CONFIG_CONSOLE_WIDTH - 1) copies of the provided char
TEST_F(LineOfCharsTest_820, WritesExpectedCount_820) {
    std::ostringstream oss;
    oss << lineOfChars('=');

    const std::string out = oss.str();
    ASSERT_EQ(out.size(), kExpectedCount) << "Must write exactly width-1 characters";

    // All characters should be the provided one
    for (char ch : out) {
        EXPECT_EQ(ch, '=') << "All written characters must match the provided char";
    }
}

// [Normal] Returns the same ostream reference (enables chaining)
TEST_F(LineOfCharsTest_820, StreamIsReturned_820) {
    std::ostringstream oss;
    std::ostream& ret = (oss << lineOfChars('#'));
    EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss)) << "Operator<< must return the same stream reference";
}

// [Normal] Appends to existing content without clobbering prior data; no newline implied
TEST_F(LineOfCharsTest_820, AppendsToExistingContent_820) {
    std::ostringstream oss;
    oss << 'X';  // pre-existing content
    oss << lineOfChars('.');

    const std::string out = oss.str();
    ASSERT_EQ(out.size(), 1 + kExpectedCount);
    EXPECT_EQ(out.front(), 'X');
    // The suffix should be all '.'
    for (std::size_t i = 1; i < out.size(); ++i) {
        EXPECT_EQ(out[i], '.');
    }
}

// [Boundary/Character variety] Handles whitespace characters (space) identically
TEST_F(LineOfCharsTest_820, WritesSpacesAsProvided_820) {
    std::ostringstream oss;
    oss << lineOfChars(' ');

    const std::string out = oss.str();
    ASSERT_EQ(out.size(), kExpectedCount);
    for (char ch : out) {
        EXPECT_EQ(ch, ' ') << "Space characters should be written as-is";
    }
}

// [Boundary/Character variety] Handles control characters (e.g., newline) as raw chars
TEST_F(LineOfCharsTest_820, WritesControlCharsVerbatim_820) {
    std::ostringstream oss;
    oss << lineOfChars('\n');

    const std::string out = oss.str();
    ASSERT_EQ(out.size(), kExpectedCount);
    // In-memory representation should contain exactly kExpectedCount '\n' bytes
    for (char ch : out) {
        EXPECT_EQ(ch, '\n') << "Control characters should be written verbatim";
    }
}
