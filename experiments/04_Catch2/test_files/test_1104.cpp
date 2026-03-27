#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const));

    MOCK_METHOD(StringRef, name, (), (const));

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const));

    MOCK_METHOD(bool, shouldDebugBreak, (), (const));

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const));

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const));

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const));

    MOCK_METHOD(int, abortAfter, (), (const));

    MOCK_METHOD(bool, showInvisibles, (), (const));

    MOCK_METHOD(ShowDurations, showDurations, (), (const));

    MOCK_METHOD(double, minDuration, (), (const));

    MOCK_METHOD(const TestSpec&, testSpec, (), (const));

    MOCK_METHOD(bool, hasTestFilters, (), (const));

    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const));

    MOCK_METHOD(TestRunOrder, runOrder, (), (const));

    MOCK_METHOD(uint32_t, rngSeed, (), (const));

    MOCK_METHOD(unsigned int, shardCount, (), (const));

    MOCK_METHOD(unsigned int, shardIndex, (), (const));

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const));

    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const));

    MOCK_METHOD(Verbosity, verbosity, (), (const));

    MOCK_METHOD(bool, skipBenchmarks, (), (const));

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const));

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const));

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const));

};



class JsonReporterTest : public ::testing::Test {

protected:

    MockIConfig mock_config;

    ReporterConfig config{&mock_config, std::make_unique<std::stringstream>(), ColourMode::None, {}};

    JsonReporter reporter{std::move(config)};

};



TEST_F(JsonReporterTest_1104, InitializesWithCorrectPreferences_1104) {

    EXPECT_TRUE(reporter.getPreferences().shouldRedirectStdOut);

    EXPECT_TRUE(reporter.getPreferences().shouldReportAllAssertions);

}



TEST_F(JsonReporterTest_1104, WritesVersionAndMetadata_1104) {

    auto& stream = *static_cast<std::stringstream*>(reporter.m_wrapped_stream->getStreamPtr());

    std::string expected_output = "{\"version\":1,\"metadata\":{\"name\":\"\",\"rng-seed\":0,\"catch2-version\":\"\",\"filters\":[]}}";

    EXPECT_EQ(stream.str().find(expected_output), 0);

}



TEST_F(JsonReporterTest_1104, WritesMetadataWithFiltersIfPresent_1104) {

    auto& mock_test_spec = reporter.m_config->testSpec();

    std::vector<Filter> filters;

    filters.emplace_back("filter_name");

    EXPECT_CALL(mock_test_spec, hasFilters()).WillOnce(Return(true));

    EXPECT_CALL(mock_test_spec, serializeTo(_)).Times(1);

    reporter.JsonReporter::JsonReporter(std::move(config));

}



TEST_F(JsonReporterTest_1104, WritesLibraryVersionCorrectly_1104) {

    auto& stream = *static_cast<std::stringstream*>(reporter.m_wrapped_stream->getStreamPtr());

    std::string expected_version_key = "\"catch2-version\":\"";

    EXPECT_NE(stream.str().find(expected_version_key), std::string::npos);

}



TEST_F(JsonReporterTest_1104, HandlesNoFiltersCorrectly_1104) {

    auto& mock_test_spec = reporter.m_config->testSpec();

    EXPECT_CALL(mock_test_spec, hasFilters()).WillOnce(Return(false));

    reporter.JsonReporter::JsonReporter(std::move(config));

}



TEST_F(JsonReporterTest_1104, WritesRngSeedCorrectly_1104) {

    auto& mock_config = *reporter.m_config;

    uint32_t rng_seed_value = 12345;

    EXPECT_CALL(mock_config, rngSeed()).WillOnce(Return(rng_seed_value));

    reporter.JsonReporter::JsonReporter(std::move(config));

    auto& stream = *static_cast<std::stringstream*>(reporter.m_wrapped_stream->getStreamPtr());

    std::string expected_output = "\"rng-seed\":" + std::to_string(rng_seed_value);

    EXPECT_NE(stream.str().find(expected_output), std::string::npos);

}



TEST_F(JsonReporterTest_1104, WritesNameCorrectly_1104) {

    auto& mock_config = *reporter.m_config;

    StringRef name_value("test_name");

    EXPECT_CALL(mock_config, name()).WillOnce(Return(name_value));

    reporter.JsonReporter::JsonReporter(std::move(config));

    auto& stream = *static_cast<std::stringstream*>(reporter.m_wrapped_stream->getStreamPtr());

    std::string expected_output = "\"name\":\"" + name_value.toString() + "\"";

    EXPECT_NE(stream.str().find(expected_output), std::string::npos);

}
