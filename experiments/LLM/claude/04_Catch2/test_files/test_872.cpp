#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

// Include the necessary Catch2 headers
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_istream.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig for testing
class JsonReporterTestFixture_872 : public ::testing::Test {
protected:
    std::stringstream stream;
    
    std::unique_ptr<JsonReporter> createReporter() {
        auto config = std::make_shared<ConfigData>();
        auto catchConfig = std::make_shared<Config>(*config);
        
        auto streamPtr = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(stream);
        
        ReporterConfig reporterConfig(catchConfig.get(), std::move(streamPtr), ColourMode::None, {});
        
        auto reporter = std::make_unique<JsonReporter>(std::move(reporterConfig));
        // Store config to keep it alive
        m_config = catchConfig;
        return reporter;
    }
    
    std::shared_ptr<Config> m_config;
};

} // anonymous namespace

// Test that getDescription returns a non-empty string
TEST(JsonReporterStaticTest_872, GetDescriptionReturnsNonEmpty_872) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test that getDescription returns a meaningful description containing "JSON"
TEST(JsonReporterStaticTest_872, GetDescriptionContainsJson_872) {
    std::string desc = JsonReporter::getDescription();
    // The description should mention JSON in some form
    bool containsJson = desc.find("JSON") != std::string::npos || 
                         desc.find("json") != std::string::npos ||
                         desc.find("Json") != std::string::npos;
    EXPECT_TRUE(containsJson);
}

// Test benchmarkPreparing with an empty name doesn't crash
TEST_F(JsonReporterTestFixture_872, BenchmarkPreparingEmptyName_872) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(StringRef("")));
}

// Test benchmarkPreparing with a valid name doesn't crash
TEST_F(JsonReporterTestFixture_872, BenchmarkPreparingValidName_872) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(StringRef("test_benchmark")));
}

// Test benchmarkFailed with an error string doesn't crash
TEST_F(JsonReporterTestFixture_872, BenchmarkFailedWithError_872) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->benchmarkFailed(StringRef("some error")));
}

// Test benchmarkFailed with empty error doesn't crash
TEST_F(JsonReporterTestFixture_872, BenchmarkFailedEmptyError_872) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->benchmarkFailed(StringRef("")));
}

// Test assertionStarting doesn't crash
TEST_F(JsonReporterTestFixture_872, AssertionStartingDoesNotCrash_872) {
    auto reporter = createReporter();
    AssertionInfo info{"test", SourceLineInfo("file.cpp", 1), StringRef("expression"), ResultDisposition::Normal};
    EXPECT_NO_THROW(reporter->assertionStarting(info));
}

// Test that testRunStarting produces some JSON output  
TEST_F(JsonReporterTestFixture_872, TestRunStartingProducesOutput_872) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
    // Some output should be generated
    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

// Test full lifecycle: testRunStarting -> testRunEnded
TEST_F(JsonReporterTestFixture_872, FullRunLifecycle_872) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    EXPECT_NO_THROW(reporter->testRunEnded(runStats));
    
    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

// Test listReporters with empty vector
TEST_F(JsonReporterTestFixture_872, ListReportersEmpty_872) {
    auto reporter = createReporter();
    std::vector<ReporterDescription> descriptions;
    EXPECT_NO_THROW(reporter->listReporters(descriptions));
}

// Test listListeners with empty vector
TEST_F(JsonReporterTestFixture_872, ListListenersEmpty_872) {
    auto reporter = createReporter();
    std::vector<ListenerDescription> descriptions;
    EXPECT_NO_THROW(reporter->listListeners(descriptions));
}

// Test listTags with empty vector
TEST_F(JsonReporterTestFixture_872, ListTagsEmpty_872) {
    auto reporter = createReporter();
    std::vector<TagInfo> tags;
    EXPECT_NO_THROW(reporter->listTags(tags));
}

// Test listTests with empty vector
TEST_F(JsonReporterTestFixture_872, ListTestsEmpty_872) {
    auto reporter = createReporter();
    std::vector<TestCaseHandle> tests;
    EXPECT_NO_THROW(reporter->listTests(tests));
}

// Test listReporters with some entries
TEST_F(JsonReporterTestFixture_872, ListReportersWithEntries_872) {
    auto reporter = createReporter();
    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"reporter1", "Description 1"});
    descriptions.push_back({"reporter2", "Description 2"});
    EXPECT_NO_THROW(reporter->listReporters(descriptions));
    
    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

// Test destructor doesn't crash
TEST_F(JsonReporterTestFixture_872, DestructorDoesNotCrash_872) {
    {
        auto reporter = createReporter();
        // Reporter goes out of scope here
    }
    SUCCEED();
}

// Test output contains valid JSON-like structure after a run
TEST_F(JsonReporterTestFixture_872, OutputContainsJsonStructure_872) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("json_test");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = stream.str();
    // JSON output should contain braces
    EXPECT_NE(output.find("{"), std::string::npos);
}

// Test benchmarkPreparing with special characters in name
TEST_F(JsonReporterTestFixture_872, BenchmarkPreparingSpecialChars_872) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->benchmarkPreparing(StringRef("bench\"mark\\special/chars")));
}

// Test benchmarkFailed with special characters
TEST_F(JsonReporterTestFixture_872, BenchmarkFailedSpecialChars_872) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->benchmarkFailed(StringRef("error: \"unexpected\" failure\n")));
}
