#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_istream.hpp"

namespace {

// A mock or stub for IConfig since we need to pass it to ReporterConfig
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
};

// Helper to create a simple IStream
Catch::Detail::unique_ptr<Catch::IStream> makeStream() {
    return Catch::Detail::make_unique<Catch::StringStream>();
}

class ReporterConfigTest_112 : public ::testing::Test {
protected:
    MockConfig mockConfig;
};

TEST_F(ReporterConfigTest_112, FullConfigReturnsProvidedConfig_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    EXPECT_EQ(config.fullConfig(), &mockConfig);
}

TEST_F(ReporterConfigTest_112, FullConfigWithNullptr_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    Catch::ReporterConfig config(nullptr, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    EXPECT_EQ(config.fullConfig(), nullptr);
}

TEST_F(ReporterConfigTest_112, ColourModeReturnsPlatformDefault_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::PlatformDefault);
}

TEST_F(ReporterConfigTest_112, ColourModeReturnsAnsiColours_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, options);

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::ANSI);
}

TEST_F(ReporterConfigTest_112, ColourModeReturnsNone_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::None, options);

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::None);
}

TEST_F(ReporterConfigTest_112, CustomOptionsEmpty_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    EXPECT_TRUE(config.customOptions().empty());
}

TEST_F(ReporterConfigTest_112, CustomOptionsWithSingleEntry_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    options["key1"] = "value1";
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    auto const& result = config.customOptions();
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.at("key1"), "value1");
}

TEST_F(ReporterConfigTest_112, CustomOptionsWithMultipleEntries_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    options["key1"] = "value1";
    options["key2"] = "value2";
    options["key3"] = "value3";
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    auto const& result = config.customOptions();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result.at("key1"), "value1");
    EXPECT_EQ(result.at("key2"), "value2");
    EXPECT_EQ(result.at("key3"), "value3");
}

TEST_F(ReporterConfigTest_112, TakeStreamReturnsNonNull_112) {
    auto stream = makeStream();
    auto* rawPtr = stream.get();
    std::map<std::string, std::string> options;
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    auto taken = std::move(config).takeStream();
    EXPECT_NE(taken.get(), nullptr);
    EXPECT_EQ(taken.get(), rawPtr);
}

TEST_F(ReporterConfigTest_112, MoveConstructor_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    options["test"] = "data";
    Catch::ReporterConfig config1(&mockConfig, std::move(stream), Catch::ColourMode::ANSI, options);

    Catch::ReporterConfig config2(std::move(config1));

    EXPECT_EQ(config2.fullConfig(), &mockConfig);
    EXPECT_EQ(config2.colourMode(), Catch::ColourMode::ANSI);
    ASSERT_EQ(config2.customOptions().size(), 1u);
    EXPECT_EQ(config2.customOptions().at("test"), "data");
}

TEST_F(ReporterConfigTest_112, MoveAssignment_112) {
    auto stream1 = makeStream();
    auto stream2 = makeStream();
    std::map<std::string, std::string> options1;
    options1["a"] = "b";
    std::map<std::string, std::string> options2;

    MockConfig anotherConfig;

    Catch::ReporterConfig config1(&mockConfig, std::move(stream1), Catch::ColourMode::ANSI, options1);
    Catch::ReporterConfig config2(&anotherConfig, std::move(stream2), Catch::ColourMode::None, options2);

    config2 = std::move(config1);

    EXPECT_EQ(config2.fullConfig(), &mockConfig);
    EXPECT_EQ(config2.colourMode(), Catch::ColourMode::ANSI);
    ASSERT_EQ(config2.customOptions().size(), 1u);
    EXPECT_EQ(config2.customOptions().at("a"), "b");
}

TEST_F(ReporterConfigTest_112, CustomOptionsWithEmptyKeyAndValue_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    options[""] = "";
    Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);

    auto const& result = config.customOptions();
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.at(""), "");
}

TEST_F(ReporterConfigTest_112, DestructorDoesNotCrash_112) {
    auto stream = makeStream();
    std::map<std::string, std::string> options;
    {
        Catch::ReporterConfig config(&mockConfig, std::move(stream), Catch::ColourMode::PlatformDefault, options);
        // config goes out of scope, destructor called
    }
    // If we reach here, destructor didn't crash
    SUCCEED();
}

} // anonymous namespace
