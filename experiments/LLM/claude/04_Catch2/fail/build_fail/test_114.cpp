#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_stream.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <map>
#include <string>
#include <sstream>

// We need a mock or stub for IConfig since ReporterConfig takes a pointer to it
// and a stub for IStream since it needs a unique_ptr<IStream>

namespace {

// Minimal stub for IConfig - we only need a pointer, not full functionality
class StubConfig : public Catch::IConfig {
public:
    bool allowThrows() const override { return true; }
    std::ostream& stream() const override { static std::ostringstream os; return os; }
    Catch::StringRef name() const override { return "stub"; }
    bool includeSuccessfulResults() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    Catch::TestSpec const& testSpec() const override { static Catch::TestSpec ts; return ts; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
};

// Helper to create a stream for ReporterConfig
Catch::Detail::unique_ptr<Catch::IStream> makeStream() {
    return Catch::Detail::unique_ptr<Catch::IStream>(
        Catch::makeStream("-").release()
    );
}

} // anonymous namespace

class ReporterConfigTest_114 : public ::testing::Test {
protected:
    StubConfig stubConfig;
};

// Test that customOptions returns the same options that were passed in construction
TEST_F(ReporterConfigTest_114, CustomOptionsReturnsPassedOptions_114) {
    std::map<std::string, std::string> options;
    options["key1"] = "value1";
    options["key2"] = "value2";

    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        options
    );

    auto const& result = config.customOptions();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result.at("key1"), "value1");
    EXPECT_EQ(result.at("key2"), "value2");
}

// Test that customOptions returns empty map when no options are provided
TEST_F(ReporterConfigTest_114, CustomOptionsEmptyWhenNoneProvided_114) {
    std::map<std::string, std::string> options;

    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        options
    );

    auto const& result = config.customOptions();
    EXPECT_TRUE(result.empty());
}

// Test that fullConfig returns the config pointer passed in construction
TEST_F(ReporterConfigTest_114, FullConfigReturnsPassedConfig_114) {
    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    EXPECT_EQ(config.fullConfig(), &stubConfig);
}

// Test that fullConfig returns nullptr when nullptr is passed
TEST_F(ReporterConfigTest_114, FullConfigReturnsNullptrWhenNullPassed_114) {
    Catch::ReporterConfig config(
        nullptr,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    EXPECT_EQ(config.fullConfig(), nullptr);
}

// Test that colourMode returns the mode passed in construction
TEST_F(ReporterConfigTest_114, ColourModeReturnsPlatformDefault_114) {
    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::PlatformDefault);
}

// Test that colourMode returns ANSI when ANSI is passed
TEST_F(ReporterConfigTest_114, ColourModeReturnsAnsi_114) {
    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::ANSI,
        {}
    );

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::ANSI);
}

// Test that colourMode returns None when None is passed
TEST_F(ReporterConfigTest_114, ColourModeReturnsNone_114) {
    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::None,
        {}
    );

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::None);
}

// Test that customOptions with a single entry works
TEST_F(ReporterConfigTest_114, CustomOptionsSingleEntry_114) {
    std::map<std::string, std::string> options;
    options["only_key"] = "only_value";

    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        options
    );

    auto const& result = config.customOptions();
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result.at("only_key"), "only_value");
}

// Test that customOptions with empty string keys/values works
TEST_F(ReporterConfigTest_114, CustomOptionsEmptyStringKeyAndValue_114) {
    std::map<std::string, std::string> options;
    options[""] = "";

    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        options
    );

    auto const& result = config.customOptions();
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result.at(""), "");
}

// Test move construction works and preserves data
TEST_F(ReporterConfigTest_114, MoveConstructionPreservesCustomOptions_114) {
    std::map<std::string, std::string> options;
    options["moveKey"] = "moveValue";

    Catch::ReporterConfig config1(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::ANSI,
        options
    );

    Catch::ReporterConfig config2(std::move(config1));

    auto const& result = config2.customOptions();
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result.at("moveKey"), "moveValue");
    EXPECT_EQ(config2.fullConfig(), &stubConfig);
    EXPECT_EQ(config2.colourMode(), Catch::ColourMode::ANSI);
}

// Test move assignment works and preserves data
TEST_F(ReporterConfigTest_114, MoveAssignmentPreservesData_114) {
    std::map<std::string, std::string> options1;
    options1["key1"] = "val1";

    std::map<std::string, std::string> options2;
    options2["key2"] = "val2";

    Catch::ReporterConfig config1(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::ANSI,
        options1
    );

    Catch::ReporterConfig config2(
        nullptr,
        makeStream(),
        Catch::ColourMode::None,
        options2
    );

    config2 = std::move(config1);

    EXPECT_EQ(config2.customOptions().size(), 1u);
    EXPECT_EQ(config2.customOptions().at("key1"), "val1");
    EXPECT_EQ(config2.fullConfig(), &stubConfig);
    EXPECT_EQ(config2.colourMode(), Catch::ColourMode::ANSI);
}

// Test customOptions with many entries
TEST_F(ReporterConfigTest_114, CustomOptionsManyEntries_114) {
    std::map<std::string, std::string> options;
    for (int i = 0; i < 100; ++i) {
        options["key" + std::to_string(i)] = "value" + std::to_string(i);
    }

    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        options
    );

    auto const& result = config.customOptions();
    EXPECT_EQ(result.size(), 100u);
    EXPECT_EQ(result.at("key0"), "value0");
    EXPECT_EQ(result.at("key99"), "value99");
}

// Test takeStream returns a valid stream and is callable on rvalue
TEST_F(ReporterConfigTest_114, TakeStreamReturnsNonNull_114) {
    Catch::ReporterConfig config(
        &stubConfig,
        makeStream(),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    auto stream = std::move(config).takeStream();
    EXPECT_NE(stream.get(), nullptr);
}
