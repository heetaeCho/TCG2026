#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_string_ref.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_istream.hpp>
#include <catch2/catch_reporter_registrars.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_test_run_info.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <string>

namespace {

// Helper to create a ConsoleReporter with a captured output stream
class ConsoleReporterTest_764 : public ::testing::Test {
protected:
    std::stringstream ss;
    
    struct StringStream : public Catch::IStream {
        std::ostream& m_os;
        StringStream(std::ostream& os) : m_os(os) {}
        std::ostream& stream() override { return m_os; }
    };

    std::unique_ptr<Catch::ConsoleReporter> makeReporter() {
        // We need to construct a ReporterConfig. This requires some Catch2 internals.
        // Use a minimal config setup.
        
        // Create a simple config
        Catch::ConfigData configData;
        configData.showDurations = Catch::ShowDurations::DefaultForReporter;
        
        auto config = Catch::Detail::make_unique<Catch::Config>(configData);
        
        auto stream = Catch::Detail::make_unique<StringStream>(ss);
        
        Catch::ReporterConfig reporterConfig(
            config.get(),
            CATCH_MOVE(stream),
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );
        
        auto reporter = std::make_unique<Catch::ConsoleReporter>(CATCH_MOVE(reporterConfig));
        
        // Store config to keep it alive
        m_config = std::move(config);
        
        return reporter;
    }
    
    Catch::Detail::unique_ptr<Catch::Config> m_config;
};

// Test reportInvalidTestSpec outputs expected message
TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_OutputsInvalidFilter_764) {
    auto reporter = makeReporter();
    
    reporter->reportInvalidTestSpec("some-bad-filter");
    
    std::string output = ss.str();
    EXPECT_NE(output.find("Invalid Filter:"), std::string::npos);
    EXPECT_NE(output.find("some-bad-filter"), std::string::npos);
}

// Test reportInvalidTestSpec with empty string
TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_EmptyArg_764) {
    auto reporter = makeReporter();
    
    reporter->reportInvalidTestSpec("");
    
    std::string output = ss.str();
    EXPECT_NE(output.find("Invalid Filter:"), std::string::npos);
}

// Test noMatchingTestCases outputs expected message
TEST_F(ConsoleReporterTest_764, NoMatchingTestCases_OutputsMessage_764) {
    auto reporter = makeReporter();
    
    reporter->noMatchingTestCases("nonexistent-test");
    
    std::string output = ss.str();
    EXPECT_NE(output.find("nonexistent-test"), std::string::npos);
}

// Test getDescription returns non-empty string
TEST_F(ConsoleReporterTest_764, GetDescription_ReturnsNonEmpty_764) {
    std::string desc = Catch::ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test assertionStarting does not crash (it's typically a no-op)
TEST_F(ConsoleReporterTest_764, AssertionStarting_DoesNotCrash_764) {
    auto reporter = makeReporter();
    
    Catch::AssertionInfo info;
    info.lineInfo = Catch::SourceLineInfo("test.cpp", 1);
    info.macroName = "REQUIRE"_catch_sr;
    
    EXPECT_NO_THROW(reporter->assertionStarting(info));
}

// Test reportInvalidTestSpec with special characters
TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_SpecialChars_764) {
    auto reporter = makeReporter();
    
    reporter->reportInvalidTestSpec("[special*chars?]");
    
    std::string output = ss.str();
    EXPECT_NE(output.find("[special*chars?]"), std::string::npos);
}

// Test multiple calls to reportInvalidTestSpec
TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_MultipleCalls_764) {
    auto reporter = makeReporter();
    
    reporter->reportInvalidTestSpec("filter1");
    reporter->reportInvalidTestSpec("filter2");
    
    std::string output = ss.str();
    EXPECT_NE(output.find("filter1"), std::string::npos);
    EXPECT_NE(output.find("filter2"), std::string::npos);
}

// Test noMatchingTestCases with empty spec
TEST_F(ConsoleReporterTest_764, NoMatchingTestCases_EmptySpec_764) {
    auto reporter = makeReporter();
    
    EXPECT_NO_THROW(reporter->noMatchingTestCases(""));
}

// Test testRunStarting produces output
TEST_F(ConsoleReporterTest_764, TestRunStarting_DoesNotCrash_764) {
    auto reporter = makeReporter();
    
    Catch::TestRunInfo testRunInfo("TestRunName");
    EXPECT_NO_THROW(reporter->testRunStarting(testRunInfo));
}

// Test testRunEnded produces summary output
TEST_F(ConsoleReporterTest_764, TestRunEnded_ProducesOutput_764) {
    auto reporter = makeReporter();
    
    Catch::TestRunInfo testRunInfo("TestRunName");
    reporter->testRunStarting(testRunInfo);
    
    Catch::Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 0;
    totals.testCases.passed = 1;
    totals.testCases.failed = 0;
    
    Catch::TestRunStats testRunStats(testRunInfo, totals, false);
    
    reporter->testRunEnded(testRunStats);
    
    std::string output = ss.str();
    // Should have some summary output
    EXPECT_FALSE(output.empty());
}

// Test reportInvalidTestSpec with very long string
TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_LongString_764) {
    auto reporter = makeReporter();
    
    std::string longFilter(1000, 'x');
    reporter->reportInvalidTestSpec(Catch::StringRef(longFilter));
    
    std::string output = ss.str();
    EXPECT_NE(output.find("Invalid Filter:"), std::string::npos);
    EXPECT_NE(output.find(longFilter), std::string::npos);
}

} // anonymous namespace
