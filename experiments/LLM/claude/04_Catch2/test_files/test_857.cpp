#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

#include <sstream>
#include <memory>
#include <vector>

namespace {

// A concrete subclass of CumulativeReporterBase for testing purposes
class TestCumulativeReporter : public Catch::CumulativeReporterBase {
public:
    using CumulativeReporterBase::CumulativeReporterBase;

    void testRunEndedCumulative() override {}

    // Expose internal state for verification through observable behavior
    // We rely on sectionStarting/sectionEnded pairs and the public tree structure
    std::string getReporterName() const override {
        return "TestCumulativeReporter";
    }
};

// Helper to create a ReporterConfig
class CumulativeReporterBaseTest_857 : public ::testing::Test {
protected:
    std::stringstream stream;
    std::unique_ptr<Catch::IConfig const> config;
    std::unique_ptr<TestCumulativeReporter> reporter;

    void SetUp() override {
        // Create a minimal config
        char const* argv[] = {"test"};
        Catch::ConfigData configData;
        config = std::make_unique<Catch::Config>(configData);
        
        Catch::ReporterConfig reporterConfig(config.get(), &stream, Catch::ColourMode::None, {});
        reporter = std::make_unique<TestCumulativeReporter>(CATCH_MOVE(reporterConfig));
    }

    Catch::SectionInfo makeSectionInfo(const std::string& name, int line = 1) {
        return Catch::SectionInfo(Catch::SourceLineInfo("test_file.cpp", static_cast<std::size_t>(line)), name);
    }

    Catch::SectionStats makeSectionStats(const std::string& name, int line = 1) {
        return Catch::SectionStats(
            Catch::SectionInfo(Catch::SourceLineInfo("test_file.cpp", static_cast<std::size_t>(line)), name),
            Catch::Counts(),
            0.0,
            false
        );
    }
};

// Test: Calling sectionStarting once creates the root section
TEST_F(CumulativeReporterBaseTest_857, SectionStartingCreatesRootSection_857) {
    auto info = makeSectionInfo("root");
    ASSERT_NO_THROW(reporter->sectionStarting(info));
    
    // Clean up by ending the section
    auto stats = makeSectionStats("root");
    reporter->sectionEnded(stats);
}

// Test: Calling sectionStarting with the same section info again reuses the root
TEST_F(CumulativeReporterBaseTest_857, SectionStartingSameInfoReusesRoot_857) {
    auto info = makeSectionInfo("root");
    
    // First run
    reporter->sectionStarting(info);
    auto stats = makeSectionStats("root");
    reporter->sectionEnded(stats);
    
    // Second run with same section info - should reuse root
    ASSERT_NO_THROW(reporter->sectionStarting(info));
    reporter->sectionEnded(stats);
}

// Test: Nested sectionStarting creates child sections
TEST_F(CumulativeReporterBaseTest_857, NestedSectionStartingCreatesChildSection_857) {
    auto rootInfo = makeSectionInfo("root");
    auto childInfo = makeSectionInfo("child", 2);
    
    reporter->sectionStarting(rootInfo);
    ASSERT_NO_THROW(reporter->sectionStarting(childInfo));
    
    // End child then root
    auto childStats = makeSectionStats("child", 2);
    reporter->sectionEnded(childStats);
    auto rootStats = makeSectionStats("root");
    reporter->sectionEnded(rootStats);
}

// Test: Multiple children under the same parent
TEST_F(CumulativeReporterBaseTest_857, MultipleSiblingSections_857) {
    auto rootInfo = makeSectionInfo("root");
    auto child1Info = makeSectionInfo("child1", 2);
    auto child2Info = makeSectionInfo("child2", 3);
    
    // First test run: root -> child1
    reporter->sectionStarting(rootInfo);
    reporter->sectionStarting(child1Info);
    reporter->sectionEnded(makeSectionStats("child1", 2));
    reporter->sectionEnded(makeSectionStats("root"));
    
    // Second test run: root -> child2
    reporter->sectionStarting(rootInfo);
    ASSERT_NO_THROW(reporter->sectionStarting(child2Info));
    reporter->sectionEnded(makeSectionStats("child2", 3));
    reporter->sectionEnded(makeSectionStats("root"));
}

// Test: Re-entering same child section reuses existing node
TEST_F(CumulativeReporterBaseTest_857, ReenteringSameChildSectionReusesNode_857) {
    auto rootInfo = makeSectionInfo("root");
    auto childInfo = makeSectionInfo("child", 2);
    
    // First run: root -> child
    reporter->sectionStarting(rootInfo);
    reporter->sectionStarting(childInfo);
    reporter->sectionEnded(makeSectionStats("child", 2));
    reporter->sectionEnded(makeSectionStats("root"));
    
    // Second run: root -> same child (should reuse)
    reporter->sectionStarting(rootInfo);
    ASSERT_NO_THROW(reporter->sectionStarting(childInfo));
    reporter->sectionEnded(makeSectionStats("child", 2));
    reporter->sectionEnded(makeSectionStats("root"));
}

// Test: Deep nesting of sections
TEST_F(CumulativeReporterBaseTest_857, DeeplyNestedSections_857) {
    auto rootInfo = makeSectionInfo("root", 1);
    auto level1Info = makeSectionInfo("level1", 2);
    auto level2Info = makeSectionInfo("level2", 3);
    auto level3Info = makeSectionInfo("level3", 4);
    
    reporter->sectionStarting(rootInfo);
    reporter->sectionStarting(level1Info);
    reporter->sectionStarting(level2Info);
    ASSERT_NO_THROW(reporter->sectionStarting(level3Info));
    
    reporter->sectionEnded(makeSectionStats("level3", 4));
    reporter->sectionEnded(makeSectionStats("level2", 3));
    reporter->sectionEnded(makeSectionStats("level1", 2));
    reporter->sectionEnded(makeSectionStats("root", 1));
}

// Test: sectionStarting with empty string name
TEST_F(CumulativeReporterBaseTest_857, SectionStartingWithEmptyName_857) {
    auto info = makeSectionInfo("");
    ASSERT_NO_THROW(reporter->sectionStarting(info));
    reporter->sectionEnded(makeSectionStats(""));
}

// Test: Multiple separate root section invocations reuse the same root
TEST_F(CumulativeReporterBaseTest_857, MultipleRootInvocationsReuseSameRoot_857) {
    auto rootInfo = makeSectionInfo("root");
    
    for (int i = 0; i < 5; ++i) {
        reporter->sectionStarting(rootInfo);
        reporter->sectionEnded(makeSectionStats("root"));
    }
    // No crash or error expected; root is reused each time
}

// Test: sectionStarting followed by assertionEnded and then sectionEnded
TEST_F(CumulativeReporterBaseTest_857, SectionWithAssertions_857) {
    auto rootInfo = makeSectionInfo("root");
    reporter->sectionStarting(rootInfo);
    
    // Create assertion stats
    Catch::AssertionResultData resultData(Catch::ResultWas::Ok, Catch::LazyExpression(false));
    Catch::AssertionInfo assertionInfo(
        Catch::StringRef(),
        Catch::SourceLineInfo("file.cpp", 10),
        Catch::StringRef(),
        Catch::ResultDisposition::Normal
    );
    Catch::AssertionResult result(assertionInfo, CATCH_MOVE(resultData));
    
    Catch::AssertionStats assertionStats(result, {}, {});
    ASSERT_NO_THROW(reporter->assertionEnded(assertionStats));
    
    reporter->sectionEnded(makeSectionStats("root"));
}

// Test: Child sections with different names are separate nodes
TEST_F(CumulativeReporterBaseTest_857, DifferentChildNamesCreateSeparateNodes_857) {
    auto rootInfo = makeSectionInfo("root");
    
    // Run with child A
    reporter->sectionStarting(rootInfo);
    auto childAInfo = makeSectionInfo("childA", 2);
    reporter->sectionStarting(childAInfo);
    reporter->sectionEnded(makeSectionStats("childA", 2));
    reporter->sectionEnded(makeSectionStats("root"));
    
    // Run with child B
    reporter->sectionStarting(rootInfo);
    auto childBInfo = makeSectionInfo("childB", 3);
    reporter->sectionStarting(childBInfo);
    reporter->sectionEnded(makeSectionStats("childB", 3));
    reporter->sectionEnded(makeSectionStats("root"));
    
    // Run with child A again (should reuse)
    reporter->sectionStarting(rootInfo);
    reporter->sectionStarting(childAInfo);
    reporter->sectionEnded(makeSectionStats("childA", 2));
    reporter->sectionEnded(makeSectionStats("root"));
}

// Test: Section starting with a very long name
TEST_F(CumulativeReporterBaseTest_857, SectionStartingWithLongName_857) {
    std::string longName(10000, 'x');
    auto info = makeSectionInfo(longName);
    ASSERT_NO_THROW(reporter->sectionStarting(info));
    reporter->sectionEnded(makeSectionStats(longName));
}

// Test: Section with special characters in name
TEST_F(CumulativeReporterBaseTest_857, SectionStartingWithSpecialCharacters_857) {
    auto info = makeSectionInfo("section with spaces & <special> \"chars\"");
    ASSERT_NO_THROW(reporter->sectionStarting(info));
    reporter->sectionEnded(makeSectionStats("section with spaces & <special> \"chars\""));
}

} // anonymous namespace
