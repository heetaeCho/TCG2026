#include <gtest/gtest.h>

#include "catch_reporter_cumulative_base.hpp"

#include "catch_section_info.hpp"



using namespace Catch;



class CumulativeReporterBaseTest_857 : public ::testing::Test {

protected:

    ReporterConfig config;

    CumulativeReporterBase reporter;



    CumulativeReporterBaseTest_857() : reporter(CATCH_MOVE(config)) {}



    SectionInfo createSectionInfo(const std::string& name, const SourceLineInfo& lineInfo) {

        return SectionInfo(lineInfo, name);

    }

};



TEST_F(CumulativeReporterBaseTest_857, SectionStarting_NewRootSection_857) {

    SectionInfo sectionInfo = createSectionInfo("RootSection", SourceLineInfo("", 0));

    reporter.sectionStarting(sectionInfo);



    // Verify that m_rootSection is set and m_sectionStack has one element

    EXPECT_NE(reporter.m_rootSection.get(), nullptr);

    EXPECT_EQ(reporter.m_sectionStack.size(), 1);

}



TEST_F(CumulativeReporterBaseTest_857, SectionStarting_NewChildSection_857) {

    SectionInfo parentSection = createSectionInfo("ParentSection", SourceLineInfo("", 0));

    reporter.sectionStarting(parentSection);



    SectionInfo childSection = createSectionInfo("ChildSection", SourceLineInfo("", 1));

    reporter.sectionStarting(childSection);



    // Verify that the new section is added as a child to the parent

    EXPECT_EQ(reporter.m_sectionStack.size(), 2);

    EXPECT_EQ(reporter.m_rootSection->childSections.size(), 1);

}



TEST_F(CumulativeReporterBaseTest_857, SectionStarting_SameChildSectionTwice_857) {

    SectionInfo parentSection = createSectionInfo("ParentSection", SourceLineInfo("", 0));

    reporter.sectionStarting(parentSection);



    SectionInfo childSection = createSectionInfo("ChildSection", SourceLineInfo("", 1));

    reporter.sectionStarting(childSection);

    reporter.sectionStarting(childSection);



    // Verify that the same section is not added twice

    EXPECT_EQ(reporter.m_sectionStack.size(), 2);

    EXPECT_EQ(reporter.m_rootSection->childSections.size(), 1);

}



TEST_F(CumulativeReporterBaseTest_857, SectionStarting_NestedSections_857) {

    SectionInfo parentSection = createSectionInfo("ParentSection", SourceLineInfo("", 0));

    reporter.sectionStarting(parentSection);



    SectionInfo childSection1 = createSectionInfo("ChildSection1", SourceLineInfo("", 1));

    reporter.sectionStarting(childSection1);



    SectionInfo childSection2 = createSectionInfo("ChildSection2", SourceLineInfo("", 2));

    reporter.sectionStarting(childSection2);



    // Verify that nested sections are correctly added

    EXPECT_EQ(reporter.m_sectionStack.size(), 3);

    EXPECT_EQ(reporter.m_rootSection->childSections.size(), 1);

    EXPECT_EQ(reporter.m_rootSection->childSections[0]->childSections.size(), 1);

}



TEST_F(CumulativeReporterBaseTest_857, SectionStarting_ReturnsToParentAfterChildEnd_857) {

    SectionInfo parentSection = createSectionInfo("ParentSection", SourceLineInfo("", 0));

    reporter.sectionStarting(parentSection);



    SectionInfo childSection = createSectionInfo("ChildSection", SourceLineInfo("", 1));

    reporter.sectionStarting(childSection);

    // Assuming there's a way to end the section, simulate it

    reporter.m_sectionStack.pop_back();



    // Verify that after ending the child section, we return to the parent

    EXPECT_EQ(reporter.m_sectionStack.size(), 1);

    EXPECT_EQ(reporter.m_deepestSection, reporter.m_rootSection.get());

}
