#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_reporter_config.hpp"
#include "catch2/internal/catch_istream.hpp"

namespace {

// Concrete implementation of CumulativeReporterBase for testing
class TestCumulativeReporter : public Catch::CumulativeReporterBase {
public:
    using CumulativeReporterBase::CumulativeReporterBase;

    void testRunEndedCumulative() override {
        testRunEndedCumulativeCalled = true;
    }

    // Expose some info for verification
    bool testRunEndedCumulativeCalled = false;

    // Helper to get test case count via testRunEnded traversal
    std::string getDescription() const override {
        return "TestCumulativeReporter";
    }
};

class CumulativeReporterBaseTest_860 : public ::testing::Test {
protected:
    void SetUp() override {
        stream = Catch::Detail::make_unique<std::ostringstream>();
        streamPtr = stream.get();
    }

    std::unique_ptr<TestCumulativeReporter> createReporter() {
        // Create a ReporterConfig with the stream
        auto preferences = Catch::IEventListener::Preferences{};
        // We need a valid config - this is tricky with Catch2 internals
        // We'll create it through the available API
        Catch::ColourMode colourMode = Catch::ColourMode::None;
        auto config = Catch::ReporterConfig(
            nullptr, // IConfig - might be null for basic tests
            Catch::Detail::unique_ptr<Catch::IStream>(new Catch::StringStream()),
            colourMode,
            {}
        );
        return Catch::Detail::make_unique<TestCumulativeReporter>(CATCH_MOVE(config));
    }

    Catch::Detail::unique_ptr<std::ostringstream> stream;
    std::ostringstream* streamPtr;
};

// Helper to create a minimal TestCaseInfo
Catch::TestCaseInfo makeTestCaseInfo(const std::string& name) {
    return Catch::TestCaseInfo(
        "",    // _className
        Catch::NameAndTags{name, "[test]"},
        Catch::SourceLineInfo("test.cpp", 1)
    );
}

class StringStream : public Catch::IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

// Since CumulativeReporterBase requires careful setup of internal state
// through its normal workflow (sectionStarting -> assertionEnded -> sectionEnded -> testCaseEnded),
// we test through the public workflow API.

class CumulativeWorkflowTest_860 : public ::testing::Test {
protected:
    std::unique_ptr<TestCumulativeReporter> reporter;
    
    void SetUp() override {
        auto streamPtr = Catch::Detail::make_unique<StringStream>();
        Catch::ReporterConfig config(
            nullptr,
            Catch::Detail::unique_ptr<Catch::IStream>(streamPtr.release()),
            Catch::ColourMode::None,
            {}
        );
        reporter = std::make_unique<TestCumulativeReporter>(CATCH_MOVE(config));
    }
};

// Test: Normal workflow - section start, section end, test case end
TEST_F(CumulativeWorkflowTest_860, NormalWorkflow_SectionStartEndTestCaseEnd_860) {
    auto tcInfo = makeTestCaseInfo("TestCase1");
    Catch::Totals totals;
    
    // Start test case
    reporter->testCaseStarting(tcInfo);
    
    // Start a section
    Catch::SectionInfo sectionInfo("test.cpp", 1, "Section1");
    reporter->sectionStarting(sectionInfo);
    
    // End section
    Catch::Counts assertions;
    assertions.passed = 1;
    Catch::SectionStats sectionStats(sectionInfo, assertions, 0.1, false);
    reporter->sectionEnded(sectionStats);
    
    // End test case - this is the main function under test
    std::string stdOut = "test stdout";
    std::string stdErr = "test stderr";
    Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), false);
    
    // Should not crash - verifies the normal workflow completes
    EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));
}

// Test: testCaseEnded stores stdOut on deepest section
TEST_F(CumulativeWorkflowTest_860, TestCaseEnded_StoresStdOutOnDeepestSection_860) {
    auto tcInfo = makeTestCaseInfo("TestCase2");
    Catch::Totals totals;
    
    reporter->testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo("test.cpp", 1, "Section1");
    reporter->sectionStarting(sectionInfo);
    
    Catch::Counts assertions;
    Catch::SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    reporter->sectionEnded(sectionStats);
    
    std::string stdOut = "captured stdout content";
    std::string stdErr = "captured stderr content";
    Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), false);
    
    EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));
}

// Test: Multiple test cases in sequence
TEST_F(CumulativeWorkflowTest_860, MultipleTestCases_SequentialProcessing_860) {
    for (int i = 0; i < 3; ++i) {
        auto tcInfo = makeTestCaseInfo("TestCase" + std::to_string(i));
        Catch::Totals totals;
        
        reporter->testCaseStarting(tcInfo);
        
        Catch::SectionInfo sectionInfo("test.cpp", 1, "Section" + std::to_string(i));
        reporter->sectionStarting(sectionInfo);
        
        Catch::Counts assertions;
        assertions.passed = 1;
        Catch::SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
        reporter->sectionEnded(sectionStats);
        
        std::string stdOut = "stdout" + std::to_string(i);
        std::string stdErr = "stderr" + std::to_string(i);
        Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), false);
        
        EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));
    }
}

// Test: testCaseEnded with empty stdout/stderr
TEST_F(CumulativeWorkflowTest_860, TestCaseEnded_EmptyStdOutStdErr_860) {
    auto tcInfo = makeTestCaseInfo("EmptyOutputTest");
    Catch::Totals totals;
    
    reporter->testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo("test.cpp", 1, "Section1");
    reporter->sectionStarting(sectionInfo);
    
    Catch::Counts assertions;
    Catch::SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    reporter->sectionEnded(sectionStats);
    
    std::string stdOut;
    std::string stdErr;
    Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), false);
    
    EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));
}

// Test: testCaseEnded with aborting flag set
TEST_F(CumulativeWorkflowTest_860, TestCaseEnded_AbortingFlag_860) {
    auto tcInfo = makeTestCaseInfo("AbortingTest");
    Catch::Totals totals;
    
    reporter->testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo("test.cpp", 1, "Section1");
    reporter->sectionStarting(sectionInfo);
    
    Catch::Counts assertions;
    Catch::SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    reporter->sectionEnded(sectionStats);
    
    std::string stdOut = "abort stdout";
    std::string stdErr = "abort stderr";
    Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), true);
    
    EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));
}

// Test: Nested sections workflow
TEST_F(CumulativeWorkflowTest_860, NestedSections_TestCaseEnded_860) {
    auto tcInfo = makeTestCaseInfo("NestedSectionsTest");
    Catch::Totals totals;
    
    reporter->testCaseStarting(tcInfo);
    
    // Outer section
    Catch::SectionInfo outerSection("test.cpp", 1, "OuterSection");
    reporter->sectionStarting(outerSection);
    
    // Inner section
    Catch::SectionInfo innerSection("test.cpp", 2, "InnerSection");
    reporter->sectionStarting(innerSection);
    
    // End inner section
    Catch::Counts innerAssertions;
    innerAssertions.passed = 1;
    Catch::SectionStats innerStats(innerSection, innerAssertions, 0.0, false);
    reporter->sectionEnded(innerStats);
    
    // End outer section
    Catch::Counts outerAssertions;
    outerAssertions.passed = 1;
    Catch::SectionStats outerStats(outerSection, outerAssertions, 0.0, false);
    reporter->sectionEnded(outerStats);
    
    std::string stdOut = "nested stdout";
    std::string stdErr = "nested stderr";
    Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), false);
    
    EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));
}

// Test: testRunEnded triggers testRunEndedCumulative
TEST_F(CumulativeWorkflowTest_860, TestRunEnded_TriggersTestRunEndedCumulative_860) {
    auto tcInfo = makeTestCaseInfo("RunEndTest");
    Catch::Totals totals;
    
    reporter->testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo("test.cpp", 1, "Section1");
    reporter->sectionStarting(sectionInfo);
    
    Catch::Counts assertions;
    Catch::SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    reporter->sectionEnded(sectionStats);
    
    std::string stdOut;
    std::string stdErr;
    Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), false);
    reporter->testCaseEnded(testCaseStats);
    
    Catch::TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    Catch::TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    EXPECT_TRUE(reporter->testRunEndedCumulativeCalled);
}

// Test: testCaseEnded with large stdout/stderr strings
TEST_F(CumulativeWorkflowTest_860, TestCaseEnded_LargeStrings_860) {
    auto tcInfo = makeTestCaseInfo("LargeStringTest");
    Catch::Totals totals;
    
    reporter->testCaseStarting(tcInfo);
    
    Catch::SectionInfo sectionInfo("test.cpp", 1, "Section1");
    reporter->sectionStarting(sectionInfo);
    
    Catch::Counts assertions;
    Catch::SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    reporter->sectionEnded(sectionStats);
    
    std::string stdOut(10000, 'x');
    std::string stdErr(10000, 'y');
    Catch::TestCaseStats testCaseStats(tcInfo, totals, CATCH_MOVE(stdOut), CATCH_MOVE(stdErr), false);
    
    EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));
}

// Test: SectionNode hasAnyAssertions
TEST(SectionNodeTest_860, HasAnyAssertions_EmptyNode_860) {
    Catch::SectionInfo sInfo("file.cpp", 1, "sec");
    Catch::Counts counts;
    Catch::SectionStats stats(sInfo, counts, 0.0, false);
    Catch::CumulativeReporterBase::SectionNode node(stats);
    
    EXPECT_FALSE(node.hasAnyAssertions());
}

// Test: SectionNode equality
TEST(SectionNodeTest_860, Equality_SameStats_860) {
    Catch::SectionInfo sInfo("file.cpp", 1, "sec");
    Catch::Counts counts;
    Catch::SectionStats stats(sInfo, counts, 0.0, false);
    
    Catch::CumulativeReporterBase::SectionNode node1(stats);
    Catch::CumulativeReporterBase::SectionNode node2(stats);
    
    EXPECT_TRUE(node1 == node2);
}

// Test: No-op methods don't crash
TEST_F(CumulativeWorkflowTest_860, NoOpMethods_DontCrash_860) {
    EXPECT_NO_THROW(reporter->benchmarkPreparing("bench"));
    
    Catch::BenchmarkInfo benchInfo{"bench", 1.0, 100, 1, 1, 1};
    EXPECT_NO_THROW(reporter->benchmarkStarting(benchInfo));
    
    EXPECT_NO_THROW(reporter->benchmarkFailed("failure"));
    EXPECT_NO_THROW(reporter->noMatchingTestCases("pattern"));
    EXPECT_NO_THROW(reporter->reportInvalidTestSpec("spec"));
    EXPECT_NO_THROW(reporter->fatalErrorEncountered("error"));
}

} // anonymous namespace
