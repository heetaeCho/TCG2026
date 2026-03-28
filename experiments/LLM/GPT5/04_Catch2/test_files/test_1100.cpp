// File: tests/config_constructor_tests_1100.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <chrono>

// Catch2 public headers used only for *interfaces* / public types
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp" // ReporterSpec
#include "catch2/internal/catch_optional.hpp"             // Optional

using namespace Catch;

class ConfigTest_1100 : public ::testing::Test {
protected:
    static ReporterSpec makeReporterWithNoOutput(const std::string& name) {
        // No output file specified -> Optional<std::string>() default-constructed (none)
        return ReporterSpec{name, Optional<std::string>{}, Optional<ColourMode>{}, {}};
    }
    static ReporterSpec makeReporterWithOutput(const std::string& name,
                                               const std::string& out) {
        return ReporterSpec{name, Optional<std::string>{out}, Optional<ColourMode>{}, {}};
    }
};

// --- Normal operation: trimming of inputs ---

TEST_F(ConfigTest_1100, TrimsTestsOrTags_1100) {
    ConfigData data;
    data.testsOrTags = { "  [fast]  ", "\tcaseA  " };
    Config cfg{data};

    // The constructor trims m_data.testsOrTags; verify via getter
    const auto& got = cfg.getTestsOrTags();
    ASSERT_EQ(got.size(), 2u);
    EXPECT_EQ(got[0], "[fast]");
    EXPECT_EQ(got[1], "caseA");
}

TEST_F(ConfigTest_1100, TrimsSectionsToRun_1100) {
    ConfigData data;
    data.sectionsToRun = { "  root/child  ", "\nalpha  " };
    Config cfg{data};

    const auto& got = cfg.getSectionsToRun();
    ASSERT_EQ(got.size(), 2u);
    EXPECT_EQ(got[0], "root/child");
    EXPECT_EQ(got[1], "alpha");
}

// --- Filters & TestSpec interaction (observable via public API) ---

TEST_F(ConfigTest_1100, HasTestFiltersReflectsPresence_1100) {
    // No filters -> false
    {
        ConfigData empty;
        Config cfg{empty};
        EXPECT_FALSE(cfg.hasTestFilters());
        // sanity: TestSpec available via public API
        EXPECT_FALSE(cfg.testSpec().hasFilters());
    }
    // With at least one testsOrTags entry -> true
    {
        ConfigData withFilter;
        withFilter.testsOrTags = { "[tag1]" };
        Config cfg{withFilter};
        EXPECT_TRUE(cfg.hasTestFilters());
        EXPECT_TRUE(cfg.testSpec().hasFilters());
    }
}

// --- Default reporter behavior ---

TEST_F(ConfigTest_1100, InsertsDefaultReporterWhenNoneProvided_1100) {
    ConfigData data;
    // No reporterSpecifications provided
    Config cfg{data};

    // Constructor must populate data.reporterSpecifications with a default
    const auto& specs = cfg.getReporterSpecs();
    ASSERT_FALSE(specs.empty());
    // We do not assert the exact reporter name to avoid coupling to internals;
    // presence is sufficient as observable behavior.
}

// --- Error/exceptional behavior (observable) ---

TEST_F(ConfigTest_1100, MultipleDefaultOutputsAreRejected_1100) {
    ConfigData data;
    // Two reporters without explicit output files means both would attempt to use
    // the "default output", which the constructor forbids.
    data.reporterSpecifications.push_back(makeReporterWithNoOutput("console"));
    data.reporterSpecifications.push_back(makeReporterWithNoOutput("junit"));

    // Expect some exception to be thrown (exact type is an internal detail)
    EXPECT_ANY_THROW({
        Config cfg{data};
        (void)cfg;
    });
}

// --- Boundary/edge: exactly one default-output + one explicit output is okay ---

TEST_F(ConfigTest_1100, OneDefaultOutputPlusOneExplicitOutputIsAllowed_1100) {
    ConfigData data;
    data.defaultOutputFilename = "default-out.txt";
    data.reporterSpecifications.push_back(makeReporterWithNoOutput("console"));         // uses default output
    data.reporterSpecifications.push_back(makeReporterWithOutput("junit", "j.xml"));    // explicit output

    // Should construct without throwing
    EXPECT_NO_THROW({
        Config cfg{data};
        // We can at least observe both specs survived (no exception).
        const auto& specs = cfg.getReporterSpecs();
        ASSERT_EQ(specs.size(), 2u);
    });
}

// --- Basic passthrough of configuration values via public getters ---

TEST_F(ConfigTest_1100, GettersMirrorProvidedConfigData_1100) {
    ConfigData data;
    data.listTests = true;
    data.listTags = true;
    data.listReporters = true;
    data.listListeners = true;
    data.showSuccessfulTests = true;
    data.noThrow = false;
    data.showHelp = false;
    data.showInvisibles = true;
    data.verbosity = Verbosity::Quiet;
    data.abortAfter = 42;
    data.rngSeed = 123456u;
    data.shardCount = 3u;
    data.shardIndex = 1u;
    data.defaultColourMode = ColourMode::Dark;
    data.runOrder = TestRunOrder::LexicographicallySorted;
    data.showDurations = ShowDurations::Always;
    data.minDuration = 0.5;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.benchmarkSamples = 7u;
    data.benchmarkConfidenceInterval = 0.90;
    data.benchmarkResamples = 101u;
    data.benchmarkWarmupTime = std::chrono::milliseconds{250}.count();
    data.processName = "proc";

    Config cfg{data};

    EXPECT_TRUE(cfg.listTests());
    EXPECT_TRUE(cfg.listTags());
    EXPECT_TRUE(cfg.listReporters());
    EXPECT_TRUE(cfg.listListeners());
    EXPECT_TRUE(cfg.includeSuccessfulResults());        // showSuccessfulTests
    EXPECT_FALSE(cfg.allowThrows());                    // noThrow=false -> allowThrows depends on IConfig, observable via API
    EXPECT_TRUE(cfg.showInvisibles());
    EXPECT_EQ(cfg.verbosity(), Verbosity::Quiet);
    EXPECT_EQ(cfg.abortAfter(), 42);
    EXPECT_EQ(cfg.rngSeed(), 123456u);
    EXPECT_EQ(cfg.shardCount(), 3u);
    EXPECT_EQ(cfg.shardIndex(), 1u);
    EXPECT_EQ(cfg.defaultColourMode(), ColourMode::Dark);
    EXPECT_EQ(cfg.runOrder(), TestRunOrder::LexicographicallySorted);
    EXPECT_EQ(cfg.showDurations(), ShowDurations::Always);
    EXPECT_DOUBLE_EQ(cfg.minDuration(), 0.5);
    EXPECT_TRUE(cfg.skipBenchmarks());
    EXPECT_TRUE(cfg.benchmarkNoAnalysis());
    EXPECT_EQ(cfg.benchmarkSamples(), 7u);
    EXPECT_DOUBLE_EQ(cfg.benchmarkConfidenceInterval(), 0.90);
    EXPECT_EQ(cfg.benchmarkResamples(), 101u);
    EXPECT_EQ(cfg.benchmarkWarmupTime(), std::chrono::milliseconds{250});
}
