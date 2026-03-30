#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_cumulative_base.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_source_line_info.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_section_info.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;



namespace {



class CumulativeReporterBaseSectionNodeTest : public ::testing::Test {

protected:

    SourceLineInfo sourceLineInfo1 = {"test_file.cpp", 10};

    SourceLineInfo sourceLineInfo2 = {"test_file.cpp", 20};

    SectionInfo sectionInfo1 = {sourceLineInfo1, "section1"};

    SectionStats sectionStats1 = {std::move(sectionInfo1), Counts(), 0.1, false};



    CumulativeReporterBase::SectionNode node1 = CumulativeReporterBase::SectionNode(sectionStats1);

};



TEST_F(CumulativeReporterBaseSectionNodeTest, HasNoAssertions_565) {

    EXPECT_FALSE(node1.hasAnyAssertions());

}



TEST_F(CumulativeReporterBaseSectionNodeTest, HasAssertions_565) {

    node1.assertionsAndBenchmarks.push_back(AssertionOrBenchmarkResult{});

    EXPECT_TRUE(node1.hasAnyAssertions());

}



TEST_F(CumulativeReporterBaseSectionNodeTest, EqualNodesSameStats_565) {

    CumulativeReporterBase::SectionNode node2 = CumulativeReporterBase::SectionNode(sectionStats1);

    EXPECT_EQ(node1, node2);

}



TEST_F(CumulativeReporterBaseSectionNodeTest, NotEqualNodesDifferentFiles_565) {

    SectionInfo sectionInfo2 = {sourceLineInfo2, "section1"};

    SectionStats sectionStats2 = {std::move(sectionInfo2), Counts(), 0.1, false};

    CumulativeReporterBase::SectionNode node2 = CumulativeReporterBase::SectionNode(sectionStats2);

    EXPECT_NE(node1, node2);

}



TEST_F(CumulativeReporterBaseSectionNodeTest, NotEqualNodesDifferentLines_565) {

    SourceLineInfo sourceLineInfo3 = {"test_file.cpp", 30};

    SectionInfo sectionInfo3 = {sourceLineInfo3, "section1"};

    SectionStats sectionStats3 = {std::move(sectionInfo3), Counts(), 0.1, false};

    CumulativeReporterBase::SectionNode node2 = CumulativeReporterBase::SectionNode(sectionStats3);

    EXPECT_NE(node1, node2);

}



TEST_F(CumulativeReporterBaseSectionNodeTest, NotEqualNodesDifferentNames_565) {

    SectionInfo sectionInfo4 = {sourceLineInfo1, "section2"};

    SectionStats sectionStats4 = {std::move(sectionInfo4), Counts(), 0.1, false};

    CumulativeReporterBase::SectionNode node2 = CumulativeReporterBase::SectionNode(sectionStats4);

    EXPECT_NE(node1, node2);

}



}  // namespace
