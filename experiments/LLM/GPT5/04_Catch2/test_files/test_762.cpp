// File: tests/console_reporter_getDescription_762.cpp
#include <gtest/gtest.h>
#include <string>

// Forward declare only the public surface we exercise, to avoid relying on internals.
// This must match the implementation signature.
namespace Catch {
    class ConsoleReporter {
    public:
        std::string getDescription();
    };
}

class ConsoleReporterTest_762 : public ::testing::Test {
protected:
    Catch::ConsoleReporter reporter_;
};

// [Normal] Exact text match to the documented description.
TEST_F(ConsoleReporterTest_762, ReturnsExpectedLiteral_762) {
    const std::string expected = "Reports test results as plain lines of text";
    EXPECT_EQ(reporter_.getDescription(), expected);
}

// [Normal] Multiple instances produce identical observable results.
TEST_F(ConsoleReporterTest_762, StableAcrossInstances_762) {
    Catch::ConsoleReporter a;
    Catch::ConsoleReporter b;

    const auto descA = a.getDescription();
    const auto descB = b.getDescription();

    EXPECT_EQ(descA, descB);
}

// [Boundary-ish] Repeated calls are idempotent (no observable changes).
TEST_F(ConsoleReporterTest_762, IdempotentOnRepeatedCalls_762) {
    const auto first  = reporter_.getDescription();
    const auto second = reporter_.getDescription();
    const auto third  = reporter_.getDescription();

    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// [Sanity/Boundary] Non-empty and no leading/trailing whitespace (observable property).
TEST_F(ConsoleReporterTest_762, NonEmptyAndNoSurroundingWhitespace_762) {
    const auto desc = reporter_.getDescription();

    ASSERT_FALSE(desc.empty()) << "Description should not be empty";

    // Check no leading/trailing whitespace without inferring internals
    // (purely string property of the returned value).
    EXPECT_FALSE(std::isspace(static_cast<unsigned char>(desc.front())));
    EXPECT_FALSE(std::isspace(static_cast<unsigned char>(desc.back())));
}

// [Sanity] Length is as expected for the published description.
TEST_F(ConsoleReporterTest_762, LengthMatchesExpected_762) {
    const auto desc = reporter_.getDescription();
    EXPECT_EQ(desc.size(), std::size_t{43}); // "Reports test results as plain lines of text"
}

// [Exceptional interface] The call should not throw.
TEST_F(ConsoleReporterTest_762, DoesNotThrow_762) {
    EXPECT_NO_THROW({
        auto s = reporter_.getDescription();
        (void)s;
    });
}
