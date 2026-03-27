#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"

#include "catch2/internal/catch_xmlwriter.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::InSequence;



class MockXmlWriter : public XmlWriter {

public:

    MockXmlWriter(std::ostream& os) : XmlWriter(os) {}



    MOCK_METHOD(void, writeAttribute, (StringRef name, StringRef attribute), (override));

    MOCK_METHOD(void, writeAttribute, (StringRef name, bool attribute), (override));

    MOCK_METHOD(XmlWriter&, scopedElement, (const std::string & name, XmlFormatting fmt), (override));

};



class SonarQubeReporterTest : public ::testing::Test {

protected:

    void SetUp() override {

        os.str("");

        xmlWriter = new MockXmlWriter(os);

        reporter = new SonarQubeReporter(ReporterConfig{});

        reporter->xml = *xmlWriter;

    }



    void TearDown() override {

        delete reporter;

        delete xmlWriter;

    }



    std::ostringstream os;

    MockXmlWriter* xmlWriter;

    SonarQubeReporter* reporter;

};



TEST_F(SonarQubeReporterTest_830, WriteSection_NoAssertionsNoOutput_830) {

    SectionInfo sectionInfo(SourceLineInfo{"dummy.cpp", 1}, "section");

    SectionStats stats{CATCH_MOVE(sectionInfo), Counts{}, 1.23, false};

    SectionNode sectionNode(stats);



    EXPECT_CALL(*xmlWriter, scopedElement(_, _)).Times(0);

    reporter->writeSection("", sectionNode, true);

}



TEST_F(SonarQubeReporterTest_830, WriteSection_WithAssertions_830) {

    InSequence seq;

    SectionInfo sectionInfo(SourceLineInfo{"dummy.cpp", 1}, "section");

    Counts assertions{.passed = 1};

    SectionStats stats{CATCH_MOVE(sectionInfo), assertions, 1.23, false};

    SectionNode sectionNode(stats);



    EXPECT_CALL(*xmlWriter, scopedElement("testCase", _));

    EXPECT_CALL(*xmlWriter, writeAttribute("name"_sr, "section"_sr));

    EXPECT_CALL(*xmlWriter, writeAttribute("duration"_sr, 1230L));

    reporter->writeSection("", sectionNode, true);

}



TEST_F(SonarQubeReporterTest_830, WriteSection_WithStdOut_830) {

    InSequence seq;

    SectionInfo sectionInfo(SourceLineInfo{"dummy.cpp", 1}, "section");

    SectionStats stats{CATCH_MOVE(sectionInfo), Counts{}, 1.23, false};

    SectionNode sectionNode(stats);

    sectionNode.stdOut = "stdout message";



    EXPECT_CALL(*xmlWriter, scopedElement("testCase", _));

    EXPECT_CALL(*xmlWriter, writeAttribute("name"_sr, "section"_sr));

    EXPECT_CALL(*xmlWriter, writeAttribute("duration"_sr, 1230L));

    reporter->writeSection("", sectionNode, true);

}



TEST_F(SonarQubeReporterTest_830, WriteSection_WithStdErr_830) {

    InSequence seq;

    SectionInfo sectionInfo(SourceLineInfo{"dummy.cpp", 1}, "section");

    SectionStats stats{CATCH_MOVE(sectionInfo), Counts{}, 1.23, false};

    SectionNode sectionNode(stats);

    sectionNode.stdErr = "stderr message";



    EXPECT_CALL(*xmlWriter, scopedElement("testCase", _));

    EXPECT_CALL(*xmlWriter, writeAttribute("name"_sr, "section"_sr));

    EXPECT_CALL(*xmlWriter, writeAttribute("duration"_sr, 1230L));

    reporter->writeSection("", sectionNode, true);

}



TEST_F(SonarQubeReporterTest_830, WriteSection_WithRootName_830) {

    InSequence seq;

    SectionInfo sectionInfo(SourceLineInfo{"dummy.cpp", 1}, "section");

    SectionStats stats{CATCH_MOVE(sectionInfo), Counts{}, 1.23, false};

    SectionNode sectionNode(stats);



    EXPECT_CALL(*xmlWriter, scopedElement("testCase", _));

    EXPECT_CALL(*xmlWriter, writeAttribute("name"_sr, "root/section"_sr));

    EXPECT_CALL(*xmlWriter, writeAttribute("duration"_sr, 1230L));

    reporter->writeSection("root", sectionNode, true);

}



TEST_F(SonarQubeReporterTest_830, WriteSection_ChildSections_830) {

    InSequence seq;

    SectionInfo parentSectionInfo(SourceLineInfo{"dummy.cpp", 1}, "parent");

    Counts assertions{.passed = 1};

    SectionStats parentStats{CATCH_MOVE(parentSectionInfo), assertions, 1.23, false};

    SectionNode parentNode(parentStats);



    SectionInfo childSectionInfo(SourceLineInfo{"dummy.cpp", 2}, "child");

    SectionStats childStats{CATCH_MOVE(childSectionInfo), Counts{}, 0.56, false};

    SectionNode childNode(childStats);

    parentNode.childSections.push_back(Detail::unique_ptr<SectionNode>{new SectionNode(childNode)});



    EXPECT_CALL(*xmlWriter, scopedElement("testCase", _));

    EXPECT_CALL(*xmlWriter, writeAttribute("name"_sr, "parent"_sr));

    EXPECT_CALL(*xmlWriter, writeAttribute("duration"_sr, 1230L));



    EXPECT_CALL(*xmlWriter, scopedElement("testCase", _)).Times(1);

    EXPECT_CALL(*xmlWriter, writeAttribute("name"_sr, "parent/child"_sr));

    EXPECT_CALL(*xmlWriter, writeAttribute("duration"_sr, 560L));



    reporter->writeSection("", parentNode, true);

}
