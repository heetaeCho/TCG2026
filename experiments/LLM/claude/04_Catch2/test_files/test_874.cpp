#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_get_random_seed.hpp"
#include "catch2/internal/catch_reusable_string_stream.hpp"

using namespace Catch;

namespace {

class MockConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    bool hasTestFilters() const override { return false; }
    std::ostream& stream() const override { return const_cast<std::ostream&>(static_cast<std::ostream const&>(m_stream)); }
    
    mutable std::ostringstream m_stream;
};

// Helper to create a JsonReporter with a captured output stream
class JsonReporterTest_874 : public ::testing::Test {
protected:
    void SetUp() override {
        m_oss = std::make_unique<std::ostringstream>();
        m_config = std::make_shared<MockConfig>();
        
        auto config = ReporterConfig(m_config.get(), *m_oss, ColourMode::None, {});
        m_reporter = std::make_unique<JsonReporter>(std::move(config));
    }

    void TearDown() override {
        m_reporter.reset();
    }

    std::string getOutput() const {
        return m_oss->str();
    }

    std::unique_ptr<std::ostringstream> m_oss;
    std::shared_ptr<MockConfig> m_config;
    std::unique_ptr<JsonReporter> m_reporter;
};

} // anonymous namespace

// Test: getDescription returns a non-empty string
TEST_F(JsonReporterTest_874, GetDescription_ReturnsNonEmpty_874) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test: listReporters with empty list produces valid JSON with empty reporters array
TEST_F(JsonReporterTest_874, ListReportersEmpty_874) {
    std::vector<ReporterDescription> empty;
    m_reporter->listReporters(empty);
    m_reporter.reset(); // flush/destroy to finalize output

    std::string output = getOutput();
    // Should contain "reporters" key
    EXPECT_NE(output.find("reporters"), std::string::npos);
    // With an empty list, should have empty array brackets
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// Test: listReporters with one reporter produces correct JSON output
TEST_F(JsonReporterTest_874, ListReportersSingleEntry_874) {
    std::vector<ReporterDescription> descriptions;
    ReporterDescription desc;
    desc.name = "console";
    desc.description = "A console reporter";
    descriptions.push_back(desc);

    m_reporter->listReporters(descriptions);
    m_reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("reporters"), std::string::npos);
    EXPECT_NE(output.find("console"), std::string::npos);
    EXPECT_NE(output.find("A console reporter"), std::string::npos);
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("description"), std::string::npos);
}

// Test: listReporters with multiple reporters
TEST_F(JsonReporterTest_874, ListReportersMultipleEntries_874) {
    std::vector<ReporterDescription> descriptions;
    
    ReporterDescription desc1;
    desc1.name = "console";
    desc1.description = "Console reporter";
    descriptions.push_back(desc1);

    ReporterDescription desc2;
    desc2.name = "json";
    desc2.description = "JSON reporter";
    descriptions.push_back(desc2);

    ReporterDescription desc3;
    desc3.name = "xml";
    desc3.description = "XML reporter";
    descriptions.push_back(desc3);

    m_reporter->listReporters(descriptions);
    m_reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("reporters"), std::string::npos);
    EXPECT_NE(output.find("console"), std::string::npos);
    EXPECT_NE(output.find("json"), std::string::npos);
    EXPECT_NE(output.find("xml"), std::string::npos);
    EXPECT_NE(output.find("Console reporter"), std::string::npos);
    EXPECT_NE(output.find("JSON reporter"), std::string::npos);
    EXPECT_NE(output.find("XML reporter"), std::string::npos);
}

// Test: listReporters with special characters in name/description
TEST_F(JsonReporterTest_874, ListReportersSpecialCharacters_874) {
    std::vector<ReporterDescription> descriptions;
    
    ReporterDescription desc;
    desc.name = "test-reporter";
    desc.description = "A reporter with \"quotes\" and \\backslash";
    descriptions.push_back(desc);

    m_reporter->listReporters(descriptions);
    m_reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("test-reporter"), std::string::npos);
    EXPECT_NE(output.find("reporters"), std::string::npos);
}

// Test: listReporters with empty name and description
TEST_F(JsonReporterTest_874, ListReportersEmptyNameAndDescription_874) {
    std::vector<ReporterDescription> descriptions;
    
    ReporterDescription desc;
    desc.name = "";
    desc.description = "";
    descriptions.push_back(desc);

    m_reporter->listReporters(descriptions);
    m_reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("reporters"), std::string::npos);
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("description"), std::string::npos);
}

// Test: listListeners with empty list
TEST_F(JsonReporterTest_874, ListListenersEmpty_874) {
    std::vector<ListenerDescription> empty;
    m_reporter->listListeners(empty);
    m_reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("listeners"), std::string::npos);
}

// Test: listListeners with entries
TEST_F(JsonReporterTest_874, ListListenersWithEntries_874) {
    std::vector<ListenerDescription> descriptions;
    ListenerDescription desc;
    desc.name = "my-listener";
    desc.description = "A test listener";
    descriptions.push_back(desc);

    m_reporter->listListeners(descriptions);
    m_reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("listeners"), std::string::npos);
    EXPECT_NE(output.find("my-listener"), std::string::npos);
    EXPECT_NE(output.find("A test listener"), std::string::npos);
}

// Test: listTags with empty list
TEST_F(JsonReporterTest_874, ListTagsEmpty_874) {
    std::vector<TagInfo> empty;
    m_reporter->listTags(empty);
    m_reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("tags"), std::string::npos);
}

// Test: testRunStarting and testRunEnded produce valid JSON structure
TEST_F(JsonReporterTest_874, TestRunStartingAndEnding_874) {
    TestRunInfo runInfo("test-run");
    m_reporter->testRunStarting(runInfo);
    
    Totals totals;
    totals.assertions.passed = 1;
    totals.assertions.failed = 0;
    totals.testCases.passed = 1;
    totals.testCases.failed = 0;
    
    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);
    m_reporter.reset();

    std::string output = getOutput();
    // Should contain test run related information
    EXPECT_FALSE(output.empty());
}

// Test: assertionStarting does not crash (it's documented as a no-op in many reporters)
TEST_F(JsonReporterTest_874, AssertionStartingNoOp_874) {
    SourceLineInfo lineInfo("test.cpp", 42);
    AssertionInfo info("expression", lineInfo, "original_expression"_sr, ResultDisposition::Normal);
    // Should not throw
    EXPECT_NO_THROW(m_reporter->assertionStarting(info));
}

// Test: Constructor and destructor work without crash
TEST_F(JsonReporterTest_874, ConstructorDestructor_874) {
    // If we get here, setup succeeded. Just verify reporter exists.
    EXPECT_NE(m_reporter, nullptr);
}

// Test: listReporters output contains proper JSON array structure  
TEST_F(JsonReporterTest_874, ListReportersJsonArrayStructure_874) {
    std::vector<ReporterDescription> descriptions;
    
    ReporterDescription desc1;
    desc1.name = "first";
    desc1.description = "First reporter";
    descriptions.push_back(desc1);

    ReporterDescription desc2;
    desc2.name = "second";
    desc2.description = "Second reporter";
    descriptions.push_back(desc2);

    m_reporter->listReporters(descriptions);
    m_reporter.reset();

    std::string output = getOutput();
    
    // The output should contain JSON array notation for reporters
    // Both entries should appear in order
    auto pos1 = output.find("first");
    auto pos2 = output.find("second");
    EXPECT_NE(pos1, std::string::npos);
    EXPECT_NE(pos2, std::string::npos);
    // "first" should appear before "second" in the output
    EXPECT_LT(pos1, pos2);
}

// Test: listReporters with very long name and description
TEST_F(JsonReporterTest_874, ListReportersLongStrings_874) {
    std::vector<ReporterDescription> descriptions;
    
    ReporterDescription desc;
    desc.name = std::string(1000, 'a');
    desc.description = std::string(5000, 'b');
    descriptions.push_back(desc);

    EXPECT_NO_THROW({
        m_reporter->listReporters(descriptions);
        m_reporter.reset();
    });

    std::string output = getOutput();
    EXPECT_NE(output.find("reporters"), std::string::npos);
}
