// tests/reporter_spec_name_tests_419.cpp

#include <gtest/gtest.h>
#include <string>
#include <map>

// Include the interface under test
#include "catch2/internal/catch_reporter_spec_parser.hpp"

namespace {

using Catch::ReporterSpec;

// If the project exposes Optional/ColourMode in Catch namespace, these
// forward uses should compile with the real types. We only *use* them
// as empty optionals so we do not rely on their internals.
using Catch::Optional;
using Catch::ColourMode;

class ReporterSpecTest_419 : public ::testing::Test {
protected:
    // Helper to build a ReporterSpec with minimal collaborators.
    ReporterSpec makeSpec(const std::string& name,
                          Optional<std::string> output = Optional<std::string>{},
                          Optional<ColourMode> colour = Optional<ColourMode>{},
                          std::map<std::string, std::string> custom = {}) {
        return ReporterSpec(name, output, colour, std::move(custom));
    }
};

// [Normal] name() returns the same logical value that was provided
TEST_F(ReporterSpecTest_419, NameReturnsProvidedValue_419) {
    auto spec = makeSpec("console");
    EXPECT_EQ(spec.name(), "console");
}

// [Boundary] name() handles an empty string
TEST_F(ReporterSpecTest_419, NameHandlesEmptyString_419) {
    auto spec = makeSpec("");
    EXPECT_TRUE(spec.name().empty());
    EXPECT_EQ(spec.name().size(), 0u);
}

// [Behavioral] name() returns a stable reference (same address across calls)
// This does not assume anything about internals; it only checks that the
// returned reference consistently refers to the same string object.
TEST_F(ReporterSpecTest_419, NameReferenceStableAcrossCalls_419) {
    auto spec = makeSpec("stable");
    const std::string& ref1 = spec.name();
    const std::string& ref2 = spec.name();
    EXPECT_EQ(&ref1, &ref2);
}

// [Boundary/Stress] name() supports long strings without truncation
TEST_F(ReporterSpecTest_419, NameSupportsLongStrings_419) {
    std::string longName(10000, 'x');  // 10k characters
    auto spec = makeSpec(longName);

    // Observe length and a couple of positions to ensure no modification.
    EXPECT_EQ(spec.name().size(), longName.size());
    EXPECT_EQ(spec.name().front(), 'x');
    EXPECT_EQ(spec.name().back(), 'x');
    // Spot-check a middle position
    EXPECT_EQ(spec.name()[5000], 'x');
}

} // namespace
