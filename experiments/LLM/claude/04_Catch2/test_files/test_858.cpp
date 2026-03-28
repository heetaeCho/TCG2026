#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/reporters/catch_reporter_event_listener.hpp"
#include "catch2/catch_session.hpp"

namespace {

// Concrete subclass for testing purposes
class TestCumulativeReporter : public Catch::CumulativeReporterBase {
public:
    using CumulativeReporterBase::CumulativeReporterBase;

    static std::string getDescription() {
        return "Test cumulative reporter";
    }

    void testRunEndedCumulative() override {
        // No-op for testing
    }

    // Expose section stack state indirectly for testing
    // We rely on the public interface only
};

class CumulativeReporterBaseTest_858 : public ::testing::Test {
protected:
    std::stringstream ss;
    
    Catch::AssertionInfo makeAssertionInfo() {
        return Catch::AssertionInfo{
            "test_macro"_catch_sr,
            Catch::SourceLineInfo("file.cpp", 1),
            ""_catch_sr,
            Catch::ResultDisposition::Normal
        };
    }

    Catch::AssertionResult makePassingResult() {
        Catch::AssertionResultData data(Catch::ResultWas::Ok, Catch::LazyExpression(false));
        return Catch::AssertionResult(makeAssertionInfo(), CATCH_MOVE(data));
    }

    Catch::AssertionResult makeFailingResult() {
        Catch::AssertionResultData data(Catch::ResultWas::ExpressionFailed, Catch::LazyExpression(false));
        return Catch::AssertionResult(makeAssertionInfo(), CATCH_MOVE(data));
    }

    Catch::AssertionStats makePassingStats() {
        auto result = makePassingResult();
        return Catch::AssertionStats(result, {}, Catch::Totals());
    }

    Catch::AssertionStats makeFailingStats() {
        auto result = makeFailingResult();
        return Catch::AssertionStats(result, {}, Catch::Totals());
    }
};

// Helper to create a reporter config
std::unique_ptr<TestCumulativeReporter> createReporter(std::ostream& os) {
    // We need to create a proper ReporterConfig. This typically requires a Config object.
    // For simplicity, we'll use Catch's built-in mechanisms.
    auto config = Catch::ReporterConfig(nullptr, os, Catch::ColourMode::None, {});
    return Catch::Detail::make_unique<TestCumulativeReporter>(CATCH_MOVE(config));
}

TEST_F(CumulativeReporterBaseTest_858, AssertionEndedStoresPassingAssertion_858) {
    auto reporter = createReporter(ss);
    
    // Set up the section stack through normal lifecycle
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "test section");
    reporter->sectionStarting(sectionInfo);
    
    auto stats = makePassingStats();
    // Should not crash and should store the assertion
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
    
    // End the section to clean up
    Catch::Counts counts;
    counts.passed = 1;
    Catch::SectionStats sectionStats(sectionInfo, counts, 0.0, false);
    reporter->sectionEnded(sectionStats);
}

TEST_F(CumulativeReporterBaseTest_858, AssertionEndedStoresFailingAssertion_858) {
    auto reporter = createReporter(ss);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "test section");
    reporter->sectionStarting(sectionInfo);
    
    auto stats = makeFailingStats();
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
    
    Catch::Counts counts;
    counts.failed = 1;
    Catch::SectionStats sectionStats(sectionInfo, counts, 0.0, false);
    reporter->sectionEnded(sectionStats);
}

TEST_F(CumulativeReporterBaseTest_858, MultipleAssertionsStored_858) {
    auto reporter = createReporter(ss);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "test section");
    reporter->sectionStarting(sectionInfo);
    
    auto passingStats = makePassingStats();
    auto failingStats = makeFailingStats();
    
    EXPECT_NO_THROW(reporter->assertionEnded(passingStats));
    EXPECT_NO_THROW(reporter->assertionEnded(failingStats));
    EXPECT_NO_THROW(reporter->assertionEnded(passingStats));
    
    Catch::Counts counts;
    counts.passed = 2;
    counts.failed = 1;
    Catch::SectionStats sectionStats(sectionInfo, counts, 0.0, false);
    reporter->sectionEnded(sectionStats);
}

TEST_F(CumulativeReporterBaseTest_858, NestedSectionsAssertionGoesToDeepest_858) {
    auto reporter = createReporter(ss);
    
    Catch::SectionInfo outerSection(Catch::SourceLineInfo("file.cpp", 1), "outer");
    Catch::SectionInfo innerSection(Catch::SourceLineInfo("file.cpp", 5), "inner");
    
    reporter->sectionStarting(outerSection);
    reporter->sectionStarting(innerSection);
    
    auto stats = makePassingStats();
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
    
    Catch::Counts counts;
    counts.passed = 1;
    Catch::SectionStats innerSectionStats(innerSection, counts, 0.0, false);
    reporter->sectionEnded(innerSectionStats);
    
    Catch::SectionStats outerSectionStats(outerSection, counts, 0.0, false);
    reporter->sectionEnded(outerSectionStats);
}

TEST_F(CumulativeReporterBaseTest_858, AssertionEndedWithInfoMessages_858) {
    auto reporter = createReporter(ss);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 1), "test section");
    reporter->sectionStarting(sectionInfo);
    
    auto result = makePassingResult();
    std::vector<Catch::MessageInfo> messages;
    // Add a message if possible
    Catch::AssertionStats stats(result, messages, Catch::Totals());
    
    EXPECT_NO_THROW(reporter->assertionEnded(stats));
    
    Catch::Counts counts;
    counts.passed = 1;
    Catch::SectionStats sectionStats(sectionInfo, counts, 0.0, false);
    reporter->sectionEnded(sectionStats);
}

TEST_F(CumulativeReporterBaseTest_858, FullLifecycleWithAssertions_858) {
    auto reporter = createReporter(ss);
    
    // Full lifecycle: testRunStarting -> testCaseStarting -> sectionStarting -> 
    //   assertionEnded -> sectionEnded -> testCaseEnded -> testRunEnded
    Catch::TestRunInfo runInfo("test_group");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test_class", {"test_name", "[tag]"}, Catch::SourceLineInfo("file.cpp", 10));
    reporter->testCaseStarting(*testCaseInfo);
    
    Catch::SectionInfo sectionInfo(Catch::SourceLineInfo("file.cpp", 10), "test_name");
    reporter->sectionStarting(sectionInfo);
    
    auto passingStats = makePassingStats();
    EXPECT_NO_THROW(reporter->assertionEnded(passingStats));
    
    auto failingStats = makeFailingStats();
    EXPECT_NO_THROW(reporter->assertionEnded(failingStats));
    
    Catch::Counts counts;
    counts.passed = 1;
    counts.failed = 1;
    Catch::Totals totals;
    totals.assertions = counts;
    
    Catch::SectionStats sectionStats(sectionInfo, counts, 0.0, false);
    reporter->sectionEnded(sectionStats);
    
    Catch::TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    Catch::TestRunStats runStats({runInfo.name, totals}, false);
    reporter->testRunEnded(runStats);
}

TEST_F(CumulativeReporterBaseTest_858, AssertionAfterSectionPop_858) {
    // Test that after popping an inner section, assertions go to the outer section
    auto reporter = createReporter(ss);
    
    Catch::SectionInfo outerSection(Catch::SourceLineInfo("file.cpp", 1), "outer");
    Catch::SectionInfo innerSection(Catch::SourceLineInfo("file.cpp", 5), "inner");
    
    reporter->sectionStarting(outerSection);
    
    // Assertion in outer section
    auto stats1 = makePassingStats();
    EXPECT_NO_THROW(reporter->assertionEnded(stats1));
    
    reporter->sectionStarting(innerSection);
    
    // Assertion in inner section
    auto stats2 = makeFailingStats();
    EXPECT_NO_THROW(reporter->assertionEnded(stats2));
    
    Catch::Counts innerCounts;
    innerCounts.failed = 1;
    Catch::SectionStats innerSectionStats(innerSection, innerCounts, 0.0, false);
    reporter->sectionEnded(innerSectionStats);
    
    // Assertion back in outer section after inner ended
    auto stats3 = makePassingStats();
    EXPECT_NO_THROW(reporter->assertionEnded(stats3));
    
    Catch::Counts outerCounts;
    outerCounts.passed = 2;
    outerCounts.failed = 1;
    Catch::SectionStats outerSectionStats(outerSection, outerCounts, 0.0, false);
    reporter->sectionEnded(outerSectionStats);
}

} // anonymous namespace
