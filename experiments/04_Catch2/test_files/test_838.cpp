#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_xml.hpp"

#include "catch2/internal/catch_xmlwriter.hpp"

#include "catch2/catch_section_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockXmlWriter : public XmlWriter {

public:

    MockXmlWriter(std::ostream &os) : XmlWriter(os) {}

    MOCK_METHOD(XmlWriter&, startElement, (const std::string &, XmlFormatting), (override));

    MOCK_METHOD(XmlWriter&, writeAttribute, (StringRef, StringRef), (override));

    MOCK_METHOD(void, ensureTagClosed, (), (override));

};



class XmlReporterTest_838 : public ::testing::Test {

protected:

    NiceMock<MockXmlWriter> mockXmlWriter;

    XmlReporter xmlReporter{ReporterConfig{}};

    

    XmlReporterTest_838() : xmlReporter(ReporterConfig{}) {

        xmlReporter.m_xml = std::move(mockXmlWriter);

    }

};



TEST_F(XmlReporterTest_838, SectionStarting_DoesNotCallStartElement_OnFirstSection_838) {

    SectionInfo sectionInfo{SourceLineInfo{"file", 1}, "section"};

    EXPECT_CALL(mockXmlWriter, startElement(_, _)).Times(0);

    xmlReporter.sectionStarting(sectionInfo);

}



TEST_F(XmlReporterTest_838, SectionStarting_CallsStartElement_OnNestedSections_838) {

    SectionInfo sectionInfo{SourceLineInfo{"file", 1}, "section"};

    xmlReporter.m_sectionDepth = 1; // Simulate that a section has already started

    EXPECT_CALL(mockXmlWriter, startElement("Section", _)).Times(1);

    xmlReporter.sectionStarting(sectionInfo);

}



TEST_F(XmlReporterTest_838, SectionStarting_WritesAttributeNameCorrectly_838) {

    SectionInfo sectionInfo{SourceLineInfo{"file", 1}, "section"};

    xmlReporter.m_sectionDepth = 1; // Simulate that a section has already started

    EXPECT_CALL(mockXmlWriter, writeAttribute("name"_sr, StringRef("section"))).Times(1);

    xmlReporter.sectionStarting(sectionInfo);

}



TEST_F(XmlReporterTest_838, SectionStarting_CallsEnsureTagClosed_AfterWritingAttributes_838) {

    SectionInfo sectionInfo{SourceLineInfo{"file", 1}, "section"};

    xmlReporter.m_sectionDepth = 1; // Simulate that a section has already started

    EXPECT_CALL(mockXmlWriter, ensureTagClosed()).Times(1);

    xmlReporter.sectionStarting(sectionInfo);

}
