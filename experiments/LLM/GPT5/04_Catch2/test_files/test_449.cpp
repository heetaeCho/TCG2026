// File: tests/session_show_help_449_tests.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Include the real Catch2 session header used by your project.
// Adjust the include path if needed.
#include "catch2/catch_session.hpp"

using namespace ::testing;

class SessionShowHelpTest_449 : public ::testing::Test {
protected:
    std::streambuf* oldCoutBuf = nullptr;
    std::ostringstream capture;

    void SetUp() override {
        // Redirect std::cout so we can observe what showHelp() writes.
        oldCoutBuf = std::cout.rdbuf(capture.rdbuf());
    }
    void TearDown() override {
        // Restore original buffer.
        std::cout.rdbuf(oldCoutBuf);
    }
};

// [Normal] Prints version header and docs hint
TEST_F(SessionShowHelpTest_449, PrintsVersionAndDocsHint_449) {
    Catch::Session s;

    ASSERT_NO_THROW(s.showHelp()); // observable: should not throw
    const std::string out = capture.str();

    // Observable substrings; do not rely on exact version or CLI contents.
    EXPECT_NE(out.find("\nCatch2 v"), std::string::npos)
        << "Help text should contain the 'Catch2 v' header.";
    EXPECT_NE(out.find("For more detailed usage"), std::string::npos)
        << "Help text should point users to more detailed docs.";
}

// [Boundary] Calling twice appends help twice (idempotent behavior not assumed, just observable accumulation)
TEST_F(SessionShowHelpTest_449, CallingTwiceAppendsOutput_449) {
    Catch::Session s;

    s.showHelp();
    s.showHelp();
    const std::string out = capture.str();

    // Count occurrences of the header marker to verify it appeared twice.
    size_t count = 0;
    for (size_t pos = out.find("\nCatch2 v"); pos != std::string::npos; pos = out.find("\nCatch2 v", pos + 1)) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// [Boundary/Formatting] Output ends with two newlines as printed by showHelp()
TEST_F(SessionShowHelpTest_449, EndsWithTwoNewlines_449) {
    Catch::Session s;

    s.showHelp();
    const std::string out = capture.str();

    // The implementation writes "\n\n" before flushing.
    ASSERT_GE(out.size(), 2u);
    EXPECT_EQ(out.substr(out.size() - 2), std::string("\n\n"));
}

// [Exceptional or error case observable through interface]
// There is no documented error path; ensure it never throws under default state.
TEST_F(SessionShowHelpTest_449, DoesNotThrow_449) {
    Catch::Session s;
    EXPECT_NO_THROW(s.showHelp());
}
