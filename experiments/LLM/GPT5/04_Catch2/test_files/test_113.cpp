// ReporterConfig_colourMode_tests_113.cpp
#include <gtest/gtest.h>
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using namespace Catch;

class ReporterConfigTest_113 : public ::testing::Test {
protected:
    // Helper to construct ReporterConfig with minimal collaborators.
    // We pass nullptrs for IConfig and IStream because these collaborators
    // are not exercised by colourMode() and the interface allows it.
    ReporterConfig makeConfig(ColourMode mode,
                              std::map<std::string, std::string> options = {}) {
        return ReporterConfig(
            /*_fullConfig=*/nullptr,
            /*_stream=*/Detail::unique_ptr<IStream>{}, // null stream
            /*colourMode=*/mode,
            /*customOptions=*/std::move(options));
    }
};

// [Normal] Returns the same ColourMode that was provided to the constructor.
TEST_F(ReporterConfigTest_113, ReturnsCtorColourMode_113) {
    // Choose two distinct enum values if available at compile-time.
    // If the exact enumerators differ across versions, these casts are still valid.
    const auto mode = static_cast<ColourMode>(0);
    ReporterConfig cfg = makeConfig(mode);

    EXPECT_EQ(cfg.colourMode(), mode);
}

// [Boundary] Distinguishes between different ColourMode values.
TEST_F(ReporterConfigTest_113, DistinguishesDifferentModes_113) {
    const auto modeA = static_cast<ColourMode>(0);
    const auto modeB = static_cast<ColourMode>(1);

    ReporterConfig cfgA = makeConfig(modeA);
    ReporterConfig cfgB = makeConfig(modeB);

    EXPECT_NE(cfgA.colourMode(), cfgB.colourMode());
}

// [Const-correctness] colourMode() is callable on a const object and returns the same value.
TEST_F(ReporterConfigTest_113, ColourModeIsConstCallable_113) {
    const auto mode = static_cast<ColourMode>(0);
    const ReporterConfig cfg = makeConfig(mode);

    // Method under test is declared const; verify observable behavior.
    EXPECT_EQ(cfg.colourMode(), mode);
}

// [Move semantics] After moving, colourMode() should still report the originally configured value.
TEST_F(ReporterConfigTest_113, MoveConstructedPreservesMode_113) {
    const auto mode = static_cast<ColourMode>(1);
    ReporterConfig original = makeConfig(mode);

    ReporterConfig moved(std::move(original)); // rely on public move ctor
    EXPECT_EQ(moved.colourMode(), mode);
}

// [Independence from other ctor args] Custom options do not affect colourMode().
TEST_F(ReporterConfigTest_113, CustomOptionsDoNotAffectColourMode_113) {
    const auto mode = static_cast<ColourMode>(0);
    std::map<std::string, std::string> opts{
        {"theme", "solarized"},
        {"verbosity", "high"}
    };

    ReporterConfig cfg = makeConfig(mode, opts);
    EXPECT_EQ(cfg.colourMode(), mode);
}
