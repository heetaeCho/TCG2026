// ReporterSpec_colourMode_tests_421.cpp
#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the header under test
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;

class ReporterSpecTest_421 : public ::testing::Test {
protected:
    // Small helpers to keep tests tidy
    static ReporterSpec MakeSpec(
        const std::string& name,
        Optional<std::string> output,
        Optional<ColourMode> colour,
        std::map<std::string, std::string> options = {}
    ) {
        return ReporterSpec{name, output, colour, options};
    }
};

// Normal operation: when colour mode is provided, it should be visible via the accessor.
TEST_F(ReporterSpecTest_421, ColourMode_ReturnsValueWhenSet_421) {
    ReporterSpec spec = MakeSpec(
        "console",
        Optional<std::string>{},              // no output redirection
        Optional<ColourMode>{ ColourMode::ANSI }, // explicitly set colour
        {}                                    // no custom options
    );

    const auto& cm = spec.colourMode();
    EXPECT_TRUE(static_cast<bool>(cm)) << "Expected colourMode() to contain a value";
    // Verify the actual value is what we passed in
    EXPECT_EQ(*cm, ColourMode::ANSI);
}

// Boundary: when no colour mode is provided, accessor should report empty optional.
TEST_F(ReporterSpecTest_421, ColourMode_ReturnsEmptyWhenNotSet_421) {
    ReporterSpec spec = MakeSpec(
        "console",
        Optional<std::string>{},
        Optional<ColourMode>{}, // not set
        {}
    );

    const auto& cm = spec.colourMode();
    EXPECT_FALSE(static_cast<bool>(cm)) << "Expected colourMode() to be empty when not provided";
}

// Interface property: accessor returns a stable reference (same reference on repeated calls).
TEST_F(ReporterSpecTest_421, ColourMode_ReturnsSameReference_421) {
    ReporterSpec spec = MakeSpec(
        "console",
        Optional<std::string>{},
        Optional<ColourMode>{ ColourMode::PlatformDefault },
        {}
    );

    const auto& ref1 = spec.colourMode();
    const auto& ref2 = spec.colourMode();
    // Taking addresses of the referenced objects to ensure the same reference is returned
    EXPECT_EQ(&ref1, &ref2) << "colourMode() should return the same reference on repeated calls";
    // Sanity check content as well
    EXPECT_TRUE(static_cast<bool>(ref1));
    EXPECT_EQ(*ref1, ColourMode::PlatformDefault);
}

// Equality should account for colourMode differences (observable via operator==).
TEST_F(ReporterSpecTest_421, EqualityAccountsForColourMode_421) {
    ReporterSpec a = MakeSpec(
        "console",
        Optional<std::string>{},                     // same output
        Optional<ColourMode>{ ColourMode::ANSI },    // colour = ANSI
        {{"k1", "v1"}}                               // same options
    );

    ReporterSpec b = MakeSpec(
        "console",
        Optional<std::string>{},                     // same output
        Optional<ColourMode>{ ColourMode::None },    // colour = None (different)
        {{"k1", "v1"}}                               // same options
    );

    EXPECT_FALSE(a == b) << "Specs differing in colourMode should not be equal";
}

// Control: when all fields (incl. colourMode) match, operator== should report equality.
TEST_F(ReporterSpecTest_421, EqualityWhenAllFieldsMatch_421) {
    ReporterSpec a = MakeSpec(
        "console",
        Optional<std::string>{"out.txt"},
        Optional<ColourMode>{ ColourMode::ANSI },
        {{"k1", "v1"}, {"k2", "v2"}}
    );

    ReporterSpec b = MakeSpec(
        "console",
        Optional<std::string>{"out.txt"},
        Optional<ColourMode>{ ColourMode::ANSI },
        {{"k1", "v1"}, {"k2", "v2"}}
    );

    EXPECT_TRUE(a == b) << "Specs with identical fields (incl. colourMode) should be equal";
}
