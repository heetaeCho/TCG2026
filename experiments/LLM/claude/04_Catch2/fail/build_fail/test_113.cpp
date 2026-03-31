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
// We'll use a minimal mock
namespace {

class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(Catch::TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<Catch::ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(Catch::RngSeed const&, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
};

// Helper to create a stream for ReporterConfig
Catch::Detail::unique_ptr<Catch::IStream> makeStream() {
    return Catch::Detail::make_unique<Catch::StringStream>();
}

} // anonymous namespace

class ReporterConfigTest_113 : public ::testing::Test {
protected:
    MockConfig mockConfig;
};

TEST_F(ReporterConfigTest_113, ColourModeReturnsConstructedValue_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::ANSI);
}

TEST_F(ReporterConfigTest_113, ColourModeNone_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::None, std::move(opts));

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::None);
}

TEST_F(ReporterConfigTest_113, ColourModePlatformDefault_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, std::move(opts));

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::PlatformDefault);
}

TEST_F(ReporterConfigTest_113, FullConfigReturnsPassedPointer_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    EXPECT_EQ(config.fullConfig(), &mockConfig);
}

TEST_F(ReporterConfigTest_113, FullConfigNullPointer_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    Catch::ReporterConfig config(nullptr, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    EXPECT_EQ(config.fullConfig(), nullptr);
}

TEST_F(ReporterConfigTest_113, CustomOptionsEmpty_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    EXPECT_TRUE(config.customOptions().empty());
}

TEST_F(ReporterConfigTest_113, CustomOptionsWithEntries_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    opts["key1"] = "value1";
    opts["key2"] = "value2";
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    const auto& customOpts = config.customOptions();
    EXPECT_EQ(customOpts.size(), 2u);
    EXPECT_EQ(customOpts.at("key1"), "value1");
    EXPECT_EQ(customOpts.at("key2"), "value2");
}

TEST_F(ReporterConfigTest_113, CustomOptionsSingleEntry_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    opts["only_key"] = "only_value";
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::None, std::move(opts));

    const auto& customOpts = config.customOptions();
    EXPECT_EQ(customOpts.size(), 1u);
    EXPECT_EQ(customOpts.at("only_key"), "only_value");
}

TEST_F(ReporterConfigTest_113, TakeStreamReturnsNonNull_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    auto taken = std::move(config).takeStream();
    EXPECT_NE(taken.get(), nullptr);
}

TEST_F(ReporterConfigTest_113, MoveConstructor_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    opts["foo"] = "bar";
    Catch::ReporterConfig config1(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    Catch::ReporterConfig config2(std::move(config1));

    EXPECT_EQ(config2.fullConfig(), &mockConfig);
    EXPECT_EQ(config2.colourMode(), Catch::ColourMode::ANSI);
    EXPECT_EQ(config2.customOptions().size(), 1u);
    EXPECT_EQ(config2.customOptions().at("foo"), "bar");
}

TEST_F(ReporterConfigTest_113, MoveAssignment_113) {
    auto stream1 = makeStream();
    auto stream2 = makeStream();
    std::map<std::string, std::string> opts1;
    opts1["a"] = "1";
    std::map<std::string, std::string> opts2;
    opts2["b"] = "2";

    Catch::ReporterConfig config1(&mockConfig, std::move(stream1), Catch::ColourMode::ANSI, std::move(opts1));
    Catch::ReporterConfig config2(nullptr, std::move(stream2), Catch::ColourMode::None, std::move(opts2));

    config2 = std::move(config1);

    EXPECT_EQ(config2.fullConfig(), &mockConfig);
    EXPECT_EQ(config2.colourMode(), Catch::ColourMode::ANSI);
    EXPECT_EQ(config2.customOptions().at("a"), "1");
}

TEST_F(ReporterConfigTest_113, CustomOptionsWithEmptyStrings_113) {
    auto stream = makeStream();
    std::map<std::string, std::string> opts;
    opts[""] = "";
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));

    const auto& customOpts = config.customOptions();
    EXPECT_EQ(customOpts.size(), 1u);
    EXPECT_EQ(customOpts.at(""), "");
}

TEST_F(ReporterConfigTest_113, DestructorDoesNotCrash_113) {
    {
        auto stream = makeStream();
        std::map<std::string, std::string> opts;
        Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, std::move(opts));
        // config goes out of scope and destructor is called
    }
    SUCCEED();
}
