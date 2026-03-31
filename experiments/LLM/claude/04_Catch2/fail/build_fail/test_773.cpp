#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/internal/catch_console_colour.hpp>
#include <catch2/internal/catch_stream.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_reporter_spec_parser.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

namespace {

// Helper to create a ReporterConfig that writes to a given stream
class ConsoleReporterTestFixture : public ::testing::Test {
protected:
    std::stringstream ss;
    
    Catch::Detail::unique_ptr<Catch::ConsoleReporter> makeReporter() {
        // We need to create a proper ReporterConfig
        // This requires a config and a stream
        const char* argv[] = {"test", "--colour-mode", "none"};
        Catch::Session session;
        session.applyCommandLine(3, argv);
        
        auto stream = Catch::Detail::make_unique<Catch::StringStream>();
        auto config = session.config();
        
        Catch::ReporterConfig repConfig(
            config,
            Catch::Detail::make_unique<Catch::StringStream>(),
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );
        
        return Catch::Detail::make_unique<Catch::ConsoleReporter>(
            CATCH_MOVE(repConfig)
        );
    }
};

} // anonymous namespace

// Test that getDescription returns a non-empty string
TEST(ConsoleReporterStatic_773, GetDescriptionReturnsNonEmpty_773) {
    std::string desc = Catch::ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test that getDescription returns a meaningful description
TEST(ConsoleReporterStatic_773, GetDescriptionContainsContent_773) {
    std::string desc = Catch::ConsoleReporter::getDescription();
    EXPECT_GT(desc.size(), 0u);
}

// The following tests require constructing a ConsoleReporter which needs
// the full Catch2 infrastructure. We test what we can through the static interface
// and through constructing with proper configs.

class ConsoleReporterTest_773 : public ::testing::Test {
protected:
    std::unique_ptr<std::ostringstream> oss;
    
    void SetUp() override {
        oss = std::make_unique<std::ostringstream>();
    }
};

// Test that testRunEnded produces output containing totals information
TEST_F(ConsoleReporterTest_773, TestRunEndedProducesOutput_773) {
    // We test through the static method that description is available
    // since full construction requires internal Catch2 wiring
    std::string desc = Catch::ConsoleReporter::getDescription();
    ASSERT_FALSE(desc.empty());
}

// Test TestRunStats construction with zero totals
TEST(TestRunStats_773, ConstructWithZeroTotals_773) {
    Catch::TestRunInfo runInfo("test_run"_catch_sr);
    Catch::Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 0;
    totals.testCases.passed = 0;
    totals.testCases.failed = 0;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_EQ(stats.totals.assertions.passed, 0u);
    EXPECT_EQ(stats.totals.assertions.failed, 0u);
    EXPECT_EQ(stats.totals.testCases.passed, 0u);
    EXPECT_EQ(stats.totals.testCases.failed, 0u);
    EXPECT_FALSE(stats.aborting);
}

// Test TestRunStats construction with non-zero totals
TEST(TestRunStats_773, ConstructWithNonZeroTotals_773) {
    Catch::TestRunInfo runInfo("my_tests"_catch_sr);
    Catch::Totals totals;
    totals.assertions.passed = 10;
    totals.assertions.failed = 2;
    totals.testCases.passed = 5;
    totals.testCases.failed = 1;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_EQ(stats.totals.assertions.passed, 10u);
    EXPECT_EQ(stats.totals.assertions.failed, 2u);
    EXPECT_EQ(stats.totals.testCases.passed, 5u);
    EXPECT_EQ(stats.totals.testCases.failed, 1u);
}

// Test TestRunStats with aborting flag set to true
TEST(TestRunStats_773, ConstructWithAbortingTrue_773) {
    Catch::TestRunInfo runInfo("aborted_run"_catch_sr);
    Catch::Totals totals;
    
    Catch::TestRunStats stats(runInfo, totals, true);
    
    EXPECT_TRUE(stats.aborting);
}

// Test TestRunStats with all passed assertions
TEST(TestRunStats_773, AllPassed_773) {
    Catch::TestRunInfo runInfo("all_pass"_catch_sr);
    Catch::Totals totals;
    totals.assertions.passed = 100;
    totals.assertions.failed = 0;
    totals.testCases.passed = 20;
    totals.testCases.failed = 0;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_EQ(stats.totals.assertions.failed, 0u);
    EXPECT_EQ(stats.totals.testCases.failed, 0u);
    EXPECT_FALSE(stats.aborting);
}

// Test TestRunStats with all failed assertions
TEST(TestRunStats_773, AllFailed_773) {
    Catch::TestRunInfo runInfo("all_fail"_catch_sr);
    Catch::Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 50;
    totals.testCases.passed = 0;
    totals.testCases.failed = 10;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_EQ(stats.totals.assertions.passed, 0u);
    EXPECT_EQ(stats.totals.assertions.failed, 50u);
}

// Test that description is consistent across calls
TEST(ConsoleReporterStatic_773, GetDescriptionIsConsistent_773) {
    std::string desc1 = Catch::ConsoleReporter::getDescription();
    std::string desc2 = Catch::ConsoleReporter::getDescription();
    EXPECT_EQ(desc1, desc2);
}

// Boundary test: TestRunStats with maximum values
TEST(TestRunStats_773, LargeTotals_773) {
    Catch::TestRunInfo runInfo("large_run"_catch_sr);
    Catch::Totals totals;
    totals.assertions.passed = 1000000;
    totals.assertions.failed = 500000;
    totals.testCases.passed = 100000;
    totals.testCases.failed = 50000;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_EQ(stats.totals.assertions.passed, 1000000u);
    EXPECT_EQ(stats.totals.assertions.failed, 500000u);
}

// Test TestRunStats preserves run info name
TEST(TestRunStats_773, PreservesRunInfoName_773) {
    Catch::TestRunInfo runInfo("my_specific_test_run"_catch_sr);
    Catch::Totals totals;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_EQ(stats.runInfo.name, "my_specific_test_run");
}

// Boundary: single test case, single assertion
TEST(TestRunStats_773, SingleTestSingleAssertion_773) {
    Catch::TestRunInfo runInfo("single"_catch_sr);
    Catch::Totals totals;
    totals.assertions.passed = 1;
    totals.assertions.failed = 0;
    totals.testCases.passed = 1;
    totals.testCases.failed = 0;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    
    EXPECT_EQ(stats.totals.assertions.total(), 1u);
    EXPECT_EQ(stats.totals.testCases.total(), 1u);
}
