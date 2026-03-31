#include <gtest/gtest.h>
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using namespace Catch;

class SectionNodeTest_565 : public ::testing::Test {
protected:
    SectionStats makeSectionStats(const char* file, std::size_t line, const std::string& name) {
        SectionInfo info(SourceLineInfo(file, line), std::string(name));
        Counts counts;
        return SectionStats(std::move(info), counts, 0.0, false);
    }
};

// Test that two SectionNodes with the same file and line are equal
TEST_F(SectionNodeTest_565, EqualityWithSameLineInfo_565) {
    SectionStats stats1 = makeSectionStats("test.cpp", 10, "section1");
    SectionStats stats2 = makeSectionStats("test.cpp", 10, "section2");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_TRUE(node1 == node2);
}

// Test that two SectionNodes with different lines are not equal
TEST_F(SectionNodeTest_565, InequalityWithDifferentLine_565) {
    SectionStats stats1 = makeSectionStats("test.cpp", 10, "section1");
    SectionStats stats2 = makeSectionStats("test.cpp", 20, "section1");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_FALSE(node1 == node2);
}

// Test that two SectionNodes with different files are not equal
TEST_F(SectionNodeTest_565, InequalityWithDifferentFile_565) {
    SectionStats stats1 = makeSectionStats("file1.cpp", 10, "section1");
    SectionStats stats2 = makeSectionStats("file2.cpp", 10, "section1");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_FALSE(node1 == node2);
}

// Test that two SectionNodes with different files and lines are not equal
TEST_F(SectionNodeTest_565, InequalityWithDifferentFileAndLine_565) {
    SectionStats stats1 = makeSectionStats("file1.cpp", 10, "section1");
    SectionStats stats2 = makeSectionStats("file2.cpp", 20, "section2");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_FALSE(node1 == node2);
}

// Test that a SectionNode is equal to itself (reflexive)
TEST_F(SectionNodeTest_565, EqualityReflexive_565) {
    SectionStats stats = makeSectionStats("test.cpp", 42, "mysection");
    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_TRUE(node == node);
}

// Test that same file different line yields inequality
TEST_F(SectionNodeTest_565, SameFileDifferentLineNotEqual_565) {
    SectionStats stats1 = makeSectionStats("test.cpp", 1, "name");
    SectionStats stats2 = makeSectionStats("test.cpp", 2, "name");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_FALSE(node1 == node2);
}

// Test hasAnyAssertions returns false when no assertions or benchmarks
TEST_F(SectionNodeTest_565, HasAnyAssertionsEmptyNode_565) {
    SectionStats stats = makeSectionStats("test.cpp", 10, "section");
    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_FALSE(node.hasAnyAssertions());
}

// Test that SectionNode construction preserves stats
TEST_F(SectionNodeTest_565, ConstructionPreservesStats_565) {
    SectionStats stats = makeSectionStats("myfile.cpp", 99, "my_section");
    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_EQ(node.stats.sectionInfo.lineInfo.line, 99u);
    EXPECT_STREQ(node.stats.sectionInfo.lineInfo.file, "myfile.cpp");
}

// Test that childSections is initially empty
TEST_F(SectionNodeTest_565, ChildSectionsInitiallyEmpty_565) {
    SectionStats stats = makeSectionStats("test.cpp", 1, "section");
    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_TRUE(node.childSections.empty());
}

// Test that assertionsAndBenchmarks is initially empty
TEST_F(SectionNodeTest_565, AssertionsAndBenchmarksInitiallyEmpty_565) {
    SectionStats stats = makeSectionStats("test.cpp", 1, "section");
    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_TRUE(node.assertionsAndBenchmarks.empty());
}

// Test equality with same name but different line info (should not be equal)
TEST_F(SectionNodeTest_565, SameNameDifferentLineInfoNotEqual_565) {
    SectionStats stats1 = makeSectionStats("a.cpp", 5, "same_name");
    SectionStats stats2 = makeSectionStats("b.cpp", 5, "same_name");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_FALSE(node1 == node2);
}

// Test boundary: line number 0
TEST_F(SectionNodeTest_565, LineNumberZero_565) {
    SectionStats stats1 = makeSectionStats("test.cpp", 0, "section");
    SectionStats stats2 = makeSectionStats("test.cpp", 0, "other");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_TRUE(node1 == node2);
}

// Test boundary: very large line number
TEST_F(SectionNodeTest_565, VeryLargeLineNumber_565) {
    std::size_t largeLine = std::numeric_limits<std::size_t>::max();
    SectionStats stats1 = makeSectionStats("test.cpp", largeLine, "section");
    SectionStats stats2 = makeSectionStats("test.cpp", largeLine, "section");

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);

    EXPECT_TRUE(node1 == node2);
}

// Test missingAssertions flag preserved
TEST_F(SectionNodeTest_565, MissingAssertionsFlagPreserved_565) {
    SectionInfo info(SourceLineInfo("test.cpp", 10), std::string("section"));
    Counts counts;
    SectionStats stats(std::move(info), counts, 1.5, true);

    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_TRUE(node.stats.missingAssertions);
}

// Test durationInSeconds preserved
TEST_F(SectionNodeTest_565, DurationPreserved_565) {
    SectionInfo info(SourceLineInfo("test.cpp", 10), std::string("section"));
    Counts counts;
    SectionStats stats(std::move(info), counts, 3.14, false);

    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_DOUBLE_EQ(node.stats.durationInSeconds, 3.14);
}
