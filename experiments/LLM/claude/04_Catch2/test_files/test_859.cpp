#include <catch2/reporters/catch_reporter_cumulative_base.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <memory>

using namespace Catch;

// Test SectionNode directly since it's a public nested struct
class SectionNodeTest_859 : public ::testing::Test {
protected:
    SectionInfo makeSectionInfo(std::string name) {
        return SectionInfo{ SourceLineInfo("file", 1), CATCH_MOVE(name) };
    }

    SectionStats makeSectionStats(std::string name, Counts assertions = Counts(), double duration = 0.0, bool missing = false) {
        return SectionStats{ makeSectionInfo(CATCH_MOVE(name)), assertions, duration, missing };
    }
};

TEST_F(SectionNodeTest_859, ConstructFromSectionStats_859) {
    auto stats = makeSectionStats("TestSection");
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_EQ(node.stats.sectionInfo.name, "TestSection");
}

TEST_F(SectionNodeTest_859, HasAnyAssertionsReturnsFalseWhenEmpty_859) {
    auto stats = makeSectionStats("EmptySection");
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_FALSE(node.hasAnyAssertions());
}

TEST_F(SectionNodeTest_859, EqualityOperatorSameSection_859) {
    auto stats1 = makeSectionStats("Section1");
    auto stats2 = makeSectionStats("Section1");
    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);
    EXPECT_TRUE(node1 == node2);
}

TEST_F(SectionNodeTest_859, EqualityOperatorDifferentSection_859) {
    auto stats1 = makeSectionStats("Section1");
    auto stats2 = makeSectionStats("Section2");
    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);
    EXPECT_FALSE(node1 == node2);
}

TEST_F(SectionNodeTest_859, StatsAreStoredCorrectly_859) {
    Counts counts;
    counts.passed = 5;
    counts.failed = 2;
    auto stats = makeSectionStats("StatsSection", counts, 1.5, true);
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_EQ(node.stats.assertions.passed, 5);
    EXPECT_EQ(node.stats.assertions.failed, 2);
    EXPECT_DOUBLE_EQ(node.stats.durationInSeconds, 1.5);
    EXPECT_TRUE(node.stats.missingAssertions);
}

TEST_F(SectionNodeTest_859, ChildSectionsInitiallyEmpty_859) {
    auto stats = makeSectionStats("ParentSection");
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_TRUE(node.childSections.empty());
}

TEST_F(SectionNodeTest_859, AssertionsAndBenchmarksInitiallyEmpty_859) {
    auto stats = makeSectionStats("Section");
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_TRUE(node.assertionsAndBenchmarks.empty());
}

TEST_F(SectionNodeTest_859, MissingAssertionsFalseByDefault_859) {
    auto stats = makeSectionStats("Section", Counts(), 0.0, false);
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_FALSE(node.stats.missingAssertions);
}

TEST_F(SectionNodeTest_859, ZeroDuration_859) {
    auto stats = makeSectionStats("Section", Counts(), 0.0, false);
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_DOUBLE_EQ(node.stats.durationInSeconds, 0.0);
}

TEST_F(SectionNodeTest_859, SectionInfoNamePreserved_859) {
    auto stats = makeSectionStats("A Very Long Section Name With Special Characters !@#$%");
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_EQ(node.stats.sectionInfo.name, "A Very Long Section Name With Special Characters !@#$%");
}

TEST_F(SectionNodeTest_859, EmptySectionName_859) {
    auto stats = makeSectionStats("");
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_EQ(node.stats.sectionInfo.name, "");
}
