#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_streaming_base.hpp"

#include "catch2/catch_section_info.hpp"



using namespace Catch;



class StreamingReporterBaseTest_563 : public ::testing::Test {

protected:

    StreamingReporterBase reporter{ReporterConfig{}};

};



TEST_F(StreamingReporterBaseTest_563, SectionStarting_AddsSectionToStack_563) {

    SourceLineInfo lineInfo("file.cpp", 10);

    SectionInfo sectionInfo(lineInfo, "section_name");



    reporter.sectionStarting(sectionInfo);



    EXPECT_EQ(reporter.m_sectionStack.size(), 1);

    EXPECT_EQ(reporter.m_sectionStack.back().name, "section_name");

}



TEST_F(StreamingReporterBaseTest_563, SectionStarting_MultipleSections_563) {

    SourceLineInfo lineInfo("file.cpp", 10);

    SectionInfo sectionInfo1(lineInfo, "section_name_1");

    SectionInfo sectionInfo2(lineInfo, "section_name_2");



    reporter.sectionStarting(sectionInfo1);

    reporter.sectionStarting(sectionInfo2);



    EXPECT_EQ(reporter.m_sectionStack.size(), 2);

    EXPECT_EQ(reporter.m_sectionStack[0].name, "section_name_1");

    EXPECT_EQ(reporter.m_sectionStack[1].name, "section_name_2");

}



TEST_F(StreamingReporterBaseTest_563, SectionStarting_EmptySectionName_563) {

    SourceLineInfo lineInfo("file.cpp", 10);

    SectionInfo sectionInfo(lineInfo, "");



    reporter.sectionStarting(sectionInfo);



    EXPECT_EQ(reporter.m_sectionStack.size(), 1);

    EXPECT_EQ(reporter.m_sectionStack.back().name, "");

}



TEST_F(StreamingReporterBaseTest_563, SectionStarting_DifferentLineNumbers_563) {

    SourceLineInfo lineInfo1("file.cpp", 10);

    SourceLineInfo lineInfo2("file.cpp", 20);

    SectionInfo sectionInfo1(lineInfo1, "section_name_1");

    SectionInfo sectionInfo2(lineInfo2, "section_name_2");



    reporter.sectionStarting(sectionInfo1);

    reporter.sectionStarting(sectionInfo2);



    EXPECT_EQ(reporter.m_sectionStack.size(), 2);

    EXPECT_EQ(reporter.m_sectionStack[0].lineInfo.lineNumber, 10);

    EXPECT_EQ(reporter.m_sectionStack[1].lineInfo.lineNumber, 20);

}
