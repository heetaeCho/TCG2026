#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch_xmlwriter.hpp"



using namespace Catch;

using namespace testing;



class XmlWriterTest_1072 : public Test {

protected:

    std::ostringstream oss;

    XmlWriter xmlWriter;



    XmlWriterTest_1072() : xmlWriter(oss) {}

};



TEST_F(XmlWriterTest_1072, ConstructorWritesDeclaration_1072) {

    EXPECT_NE(std::string(), oss.str());

}



TEST_F(XmlWriterTest_1072, StartElementOpensTag_1072) {

    xmlWriter.startElement("test", XmlFormatting::None);

    EXPECT_THAT(oss.str(), Contains("<test>"));

}



TEST_F(XmlWriterTest_1072, EndElementClosesTag_1072) {

    xmlWriter.startElement("test", XmlFormatting::None);

    xmlWriter.endElement(XmlFormatting::None);

    EXPECT_THAT(oss.str(), Contains("</test>"));

}



TEST_F(XmlWriterTest_1072, WriteAttributeAddsAttribute_1072) {

    xmlWriter.startElement("test", XmlFormatting::None);

    xmlWriter.writeAttribute("attr", "value");

    xmlWriter.endElement(XmlFormatting::None);

    EXPECT_THAT(oss.str(), Contains("<test attr=\"value\">"));

}



TEST_F(XmlWriterTest_1072, WriteTextAddsText_1072) {

    xmlWriter.startElement("test", XmlFormatting::None);

    xmlWriter.writeText("text", XmlFormatting::None);

    xmlWriter.endElement(XmlFormatting::None);

    EXPECT_THAT(oss.str(), Contains("<test>text</test>"));

}



TEST_F(XmlWriterTest_1072, WriteCommentAddsComment_1072) {

    xmlWriter.writeComment("comment", XmlFormatting::None);

    EXPECT_THAT(oss.str(), Contains("<!--comment-->"));

}



TEST_F(XmlWriterTest_1072, WriteStylesheetRefAddsLink_1072) {

    xmlWriter.writeStylesheetRef("style.xsl");

    EXPECT_THAT(oss.str(), Contains("<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>"));

}



TEST_F(XmlWriterTest_1072, EnsureTagClosedClosesOpenTag_1072) {

    xmlWriter.startElement("test", XmlFormatting::None);

    xmlWriter.ensureTagClosed();

    EXPECT_THAT(oss.str(), Contains("</test>"));

}
