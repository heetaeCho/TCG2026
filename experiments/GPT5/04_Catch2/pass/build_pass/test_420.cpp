// ReporterSpec_outputFile_tests_420.cpp
#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the production header
#include "catch2/internal/catch_reporter_spec_parser.hpp"

namespace {

using Catch::ReporterSpec;
using Catch::Optional;
using Catch::ColourMode;

class ReporterSpecOutputFileTest_420 : public ::testing::Test {
protected:
    // Helper to build a ReporterSpec with minimal required args
    ReporterSpec makeSpec(
        const std::string& name,
        const Optional<std::string>& outputFile,
        const Optional<ColourMode>& colour = Optional<ColourMode>{},
        const std::map<std::string, std::string>& opts = {}
    ) {
        return ReporterSpec{name, outputFile, colour, opts};
    }
};

// Normal case: when an output file is provided, outputFile() returns a set Optional with that value.
TEST_F(ReporterSpecOutputFileTest_420, ReturnsProvidedOutputFileName_420) {
    ReporterSpec spec = makeSpec("console", Optional<std::string>{"out.txt"});

    auto const& out = spec.outputFile();

    // Observable behavior only: Optional engaged and value matches.
    EXPECT_TRUE(static_cast<bool>(out));
    EXPECT_EQ(out.valueOr("fallback.txt"), std::string("out.txt"));
}

// Boundary case: when no output file is provided, outputFile() returns an empty/none Optional.
TEST_F(ReporterSpecOutputFileTest_420, ReturnsNoneWhenNotProvided_420) {
    ReporterSpec spec = makeSpec("console", Optional<std::string>{});

    auto const& out = spec.outputFile();

    EXPECT_FALSE(static_cast<bool>(out));    // Optional disengaged
    EXPECT_EQ(out.valueOr("default.txt"), std::string("default.txt")); // valueOr path observable
}

// Boundary case: distinguish between an explicitly provided empty string and no value.
TEST_F(ReporterSpecOutputFileTest_420, DistinguishesEmptyStringFromNone_420) {
    ReporterSpec withEmpty = makeSpec("console", Optional<std::string>{std::string("")});
    ReporterSpec without   = makeSpec("console", Optional<std::string>{});

    auto const& outEmpty = withEmpty.outputFile();
    auto const& outNone  = without.outputFile();

    ASSERT_TRUE(static_cast<bool>(outEmpty));
    // If set to empty string, valueOr should return the contained empty value, not the fallback.
    EXPECT_EQ(outEmpty.valueOr("fallback"), std::string(""));
    EXPECT_TRUE(outEmpty.valueOr("fallback").empty());

    EXPECT_FALSE(static_cast<bool>(outNone));
    EXPECT_EQ(outNone.valueOr("fallback"), std::string("fallback"));
}

// API consistency: outputFile() returns a stable reference (same address) across calls.
TEST_F(ReporterSpecOutputFileTest_420, ReturnsStableReferenceAcrossCalls_420) {
    ReporterSpec spec = makeSpec("console", Optional<std::string>{"out.txt"});

    auto const& ref1 = spec.outputFile();
    auto const& ref2 = spec.outputFile();

    // We don't inspect internals; we only verify the API consistently returns the same reference.
    EXPECT_EQ(&ref1, &ref2);
}

// Regression-style check: unrelated constructor args (colourMode/customOptions) do not affect outputFile().
TEST_F(ReporterSpecOutputFileTest_420, UnrelatedCtorArgsDoNotAffectOutputFile_420) {
    std::map<std::string, std::string> opts{{"key", "val"}};
    Optional<ColourMode> colour{}; // not setting any specific colour mode

    ReporterSpec spec = ReporterSpec{
        "xml",
        Optional<std::string>{"report.xml"},
        colour,
        opts
    };

    auto const& out = spec.outputFile();
    EXPECT_TRUE(static_cast<bool>(out));
    EXPECT_EQ(out.valueOr("missing.xml"), std::string("report.xml"));
}

} // namespace
