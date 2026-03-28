#include <catch2/reporters/catch_reporter_json.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_list.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>
#include <catch2/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_context.hpp>
#include <catch2/internal/catch_config_wchar.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/catch_tag_alias_autoregistrar.hpp>
#include <catch2/internal/catch_stream.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

using namespace Catch;

namespace {

// Helper to create a JsonReporter with a stringstream for output capture
class JsonReporterTest_875 : public ::testing::Test {
protected:
    std::stringstream ss;
    std::unique_ptr<JsonReporter> reporter;

    void SetUp() override {
        auto prefs = ReporterConfig( nullptr, ss, ColourMode::None, {} );
        reporter = std::make_unique<JsonReporter>( std::move(prefs) );
    }

    std::string getOutput() const {
        return ss.str();
    }
};

} // anonymous namespace

TEST_F(JsonReporterTest_875, GetDescription_ReturnsNonEmpty_875) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JsonReporterTest_875, ListListeners_EmptyVector_875) {
    std::vector<ListenerDescription> empty;
    reporter->listListeners(empty);
    std::string output = getOutput();
    // Should contain "listeners" key with empty array
    EXPECT_NE(output.find("listeners"), std::string::npos);
}

TEST_F(JsonReporterTest_875, ListListeners_SingleListener_875) {
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "test_listener"_sr;
    desc.description = "A test listener"_sr;
    descriptions.push_back(desc);

    reporter->listListeners(descriptions);
    std::string output = getOutput();

    EXPECT_NE(output.find("listeners"), std::string::npos);
    EXPECT_NE(output.find("test_listener"), std::string::npos);
    EXPECT_NE(output.find("A test listener"), std::string::npos);
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("description"), std::string::npos);
}

TEST_F(JsonReporterTest_875, ListListeners_MultipleListeners_875) {
    std::vector<ListenerDescription> descriptions;
    
    ListenerDescription desc1;
    desc1.name = "listener_one"_sr;
    desc1.description = "First listener"_sr;
    descriptions.push_back(desc1);

    ListenerDescription desc2;
    desc2.name = "listener_two"_sr;
    desc2.description = "Second listener"_sr;
    descriptions.push_back(desc2);

    reporter->listListeners(descriptions);
    std::string output = getOutput();

    EXPECT_NE(output.find("listener_one"), std::string::npos);
    EXPECT_NE(output.find("First listener"), std::string::npos);
    EXPECT_NE(output.find("listener_two"), std::string::npos);
    EXPECT_NE(output.find("Second listener"), std::string::npos);
}

TEST_F(JsonReporterTest_875, ListReporters_EmptyVector_875) {
    std::vector<ReporterDescription> empty;
    reporter->listReporters(empty);
    std::string output = getOutput();
    EXPECT_NE(output.find("reporters"), std::string::npos);
}

TEST_F(JsonReporterTest_875, ListReporters_SingleReporter_875) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "json"_sr;
    desc.description = "JSON reporter"_sr;
    descriptions.push_back(desc);

    reporter->listReporters(descriptions);
    std::string output = getOutput();

    EXPECT_NE(output.find("reporters"), std::string::npos);
    EXPECT_NE(output.find("json"), std::string::npos);
    EXPECT_NE(output.find("JSON reporter"), std::string::npos);
}

TEST_F(JsonReporterTest_875, ListTags_EmptyVector_875) {
    std::vector<TagInfo> empty;
    reporter->listTags(empty);
    std::string output = getOutput();
    EXPECT_NE(output.find("tags"), std::string::npos);
}

TEST_F(JsonReporterTest_875, TestRunStarting_ProducesOutput_875) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    std::string output = getOutput();
    // Should produce some JSON output for the test run
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_875, TestRunStartingAndEnding_ProducesValidJson_875) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    // Should contain the run name
    EXPECT_NE(output.find("test_run"), std::string::npos);
}

TEST_F(JsonReporterTest_875, ListListeners_EmptyNameAndDescription_875) {
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = ""_sr;
    desc.description = ""_sr;
    descriptions.push_back(desc);

    reporter->listListeners(descriptions);
    std::string output = getOutput();

    EXPECT_NE(output.find("listeners"), std::string::npos);
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("description"), std::string::npos);
}

TEST_F(JsonReporterTest_875, ListListeners_SpecialCharactersInName_875) {
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "listener with \"quotes\" and \\backslashes"_sr;
    desc.description = "desc with\nnewline"_sr;
    descriptions.push_back(desc);

    // Should not crash and should produce output
    reporter->listListeners(descriptions);
    std::string output = getOutput();
    EXPECT_NE(output.find("listeners"), std::string::npos);
}

TEST_F(JsonReporterTest_875, AssertionStarting_DoesNotCrash_875) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);

    SourceLineInfo lineInfo("file.cpp", 42);
    AssertionInfo info("test", lineInfo, ""_sr, ResultDisposition::Normal);
    
    // Should not crash
    EXPECT_NO_THROW(reporter->assertionStarting(info));
}
