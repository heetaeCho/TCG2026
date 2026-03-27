#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::InSequence;



class XmlWriterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter writer;



    XmlWriterTest() : writer(oss) {}

};



TEST_F(XmlWriterTest_475, EndElementClosesTagProperly_475) {

    writer.startElement("test", XmlFormatting::None);

    writer.endElement(XmlFormatting::None);



    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_475, EndElementReducesIndentation_475) {

    writer.startElement("root", XmlFormatting::Indented);

    writer.startElement("child", XmlFormatting::Indented);

    writer.endElement(XmlFormatting::Indented);



    EXPECT_EQ(oss.str(), "<root>\n  <child></child>\n</root>");

}



TEST_F(XmlWriterTest_475, EndElementHandlesSelfClosingTag_475) {

    writer.startElement("test", XmlFormatting::None);

    writer.endElement(XmlFormatting::NoIndent);



    EXPECT_EQ(oss.str(), "<test/>");

}



TEST_F(XmlWriterTest_475, EndElementAppliesFormatting_475) {

    writer.startElement("test", XmlFormatting::Indented);

    writer.endElement(XmlFormatting::NewLine);



    EXPECT_EQ(oss.str(), "<test>\n</test>\n");

}



TEST_F(XmlWriterTest_475, EndElementWithEmptyTagStackDoesNothing_475) {

    writer.endElement(XmlFormatting::None);



    EXPECT_EQ(oss.str(), "");

}
