// File: console_colour_operator_insertion_tests_426.cpp

#include <gtest/gtest.h>
#include <sstream>

// Use the public interface only.
#include <catch2/internal/catch_console_colour.hpp>

namespace {

// Helper: obtain a neutral/placeholder colour code without depending on a named enumerator.
// The concrete value is irrelevant for these interface-level tests.
static inline Catch::Colour::Code Code0() {
    return static_cast<Catch::Colour::Code>(0);
}

static bool StartsWith(const std::string& s, const std::string& prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}
static bool EndsWith(const std::string& s, const std::string& suffix) {
    return s.size() >= suffix.size() &&
           s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

struct ConsoleColourTest_426 : ::testing::Test {
    std::ostringstream os;
};

} // namespace

// Verifies that streaming a colour manipulator returns the SAME ostream reference,
// so further << operations continue on the same stream.
TEST_F(ConsoleColourTest_426, OperatorReturnsSameStreamReference_426) {
    auto& ret = (os << Code0());
    EXPECT_EQ(&ret, &os);
}

// Verifies chaining: after inserting the colour manipulator, subsequent text is
// written to the stream as usual. We only assert the observable suffix.
TEST_F(ConsoleColourTest_426, AllowsChainingAndWritesFollowingContent_426) {
    os << Code0() << "hello";
    EXPECT_TRUE(EndsWith(os.str(), "hello"));
}

// Pre-existing content stays intact at the front; we do not assert anything
// about the exact bytes produced by the colour engagement between prefix/suffix.
TEST_F(ConsoleColourTest_426, PreservesExistingPrefixAndAppendsSuffix_426) {
    os << "pre:";
    os << Code0() << "post";
    const std::string s = os.str();
    EXPECT_TRUE(StartsWith(s, "pre:"));
    EXPECT_TRUE(EndsWith(s, "post"));
}

// Multiple consecutive colour manipulators remain chainable and do not
// interfere with subsequent normal streaming.
TEST_F(ConsoleColourTest_426, MultipleManipulatorsRemainChainable_426) {
    os << "A";
    os << Code0() << Code0() << "Z";
    const std::string s = os.str();
    EXPECT_TRUE(StartsWith(s, "A"));
    EXPECT_TRUE(EndsWith(s, "Z"));
}

// Inserting the manipulator should not mutate ostream formatting flags
// (observable property of the stream), so normal formatting settings persist.
TEST_F(ConsoleColourTest_426, DoesNotAlterOstreamFlags_426) {
    // Set a non-default basefield to detect unintended changes.
    os.setf(std::ios::hex, std::ios::basefield);
    const auto flags_before = os.flags();

    os << Code0();

    const auto flags_after = os.flags();
    EXPECT_EQ(flags_before, flags_after);
}

// The insertion should be exception-safe from the caller’s perspective (no throw).
TEST_F(ConsoleColourTest_426, InsertionIsNoThrowFromCallerPerspective_426) {
    EXPECT_NO_THROW( static_cast<void>(os << Code0()) );
}
