// ReporterSpec_operator_not_equal_tests_418.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_reporter_spec_parser.hpp"

using Catch::ReporterSpec;
using Catch::Optional;
using Catch::ColourMode;

namespace {

// Helper to build a baseline ReporterSpec with minimal fields engaged.
ReporterSpec MakeBaselineSpec(
    const std::string& name = "console",
    Optional<std::string> out = Optional<std::string>{},
    Optional<ColourMode> colour = Optional<ColourMode>{},
    const std::map<std::string, std::string>& opts = {}) {
    return ReporterSpec{name, out, colour, opts};
}

} // namespace

// Verifies that two identical specs compare equal, thus != returns false.
TEST(ReporterSpecInequalityTest_418, Equal_WhenAllFieldsEqual_418) {
    auto a = MakeBaselineSpec();
    auto b = MakeBaselineSpec();

    // operator!= must be the logical negation of operator==
    EXPECT_EQ(a != b, !(a == b));
    EXPECT_FALSE(a != b);
}

// Changing only the reporter name should trigger inequality.
TEST(ReporterSpecInequalityTest_418, NotEqual_WhenNamesDiffer_418) {
    auto a = MakeBaselineSpec("console");
    auto b = MakeBaselineSpec("junit"); // different name

    EXPECT_EQ(a != b, !(a == b));
    EXPECT_TRUE(a != b);
    // Symmetry
    EXPECT_TRUE(b != a);
}

// Presence vs absence of output file should trigger inequality.
TEST(ReporterSpecInequalityTest_418, NotEqual_WhenOutputFilePresenceDiffers_418) {
    auto a = MakeBaselineSpec("console", Optional<std::string>{});          // no file
    auto b = MakeBaselineSpec("console", Optional<std::string>{"out.txt"}); // has file

    EXPECT_EQ(a != b, !(a == b));
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(b != a);
}

// Different engaged output file values should trigger inequality.
TEST(ReporterSpecInequalityTest_418, NotEqual_WhenOutputFileValuesDiffer_418) {
    auto a = MakeBaselineSpec("console", Optional<std::string>{"a.txt"});
    auto b = MakeBaselineSpec("console", Optional<std::string>{"b.txt"});

    EXPECT_EQ(a != b, !(a == b));
    EXPECT_TRUE(a != b);
}

// Differences in custom options should trigger inequality.
TEST(ReporterSpecInequalityTest_418, NotEqual_WhenCustomOptionsDiffer_418) {
    std::map<std::string, std::string> optsA{{"key", "value"}};
    std::map<std::string, std::string> optsB{{"key", "other"}};

    auto a = MakeBaselineSpec("console", Optional<std::string>{}, Optional<ColourMode>{}, optsA);
    auto b = MakeBaselineSpec("console", Optional<std::string>{}, Optional<ColourMode>{}, optsB);

    EXPECT_EQ(a != b, !(a == b));
    EXPECT_TRUE(a != b);
}

// (Optional) Sanity: identical maps & empty optionals keep inequality false even with empty strings.
TEST(ReporterSpecInequalityTest_418, Equal_WithEmptyStringsAndEmptyOptionals_418) {
    auto a = MakeBaselineSpec("", Optional<std::string>{}, Optional<ColourMode>{}, {});
    auto b = MakeBaselineSpec("", Optional<std::string>{}, Optional<ColourMode>{}, {});

    EXPECT_EQ(a != b, !(a == b));
    EXPECT_FALSE(a != b);
}
