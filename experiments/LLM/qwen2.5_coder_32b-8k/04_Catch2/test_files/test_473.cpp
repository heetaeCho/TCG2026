#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::HasSubstr;



class XmlWriterTest_473 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter writer;



    XmlWriterTest_473() : writer(oss) {}

};



TEST_F(XmlWriterTest_473, StartElementWritesCorrectTag_473) {

    writer.startElement("test", XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test");

}



TEST_F(XmlWriterTest_473, StartElementWithIndentationWritesIndentedTag_473) {

    writer.startElement("root", XmlFormatting::Indent);

    writer.startElement("child", XmlFormatting::Indent);

    EXPECT_THAT(oss.str(), HasSubstr("  <child"));

}



TEST_F(XmlWriterTest_473, StartElementDoesNotClosePreviousTagIfNotNeeded_473) {

    writer.startElement("root", XmlFormatting::None);

    oss << "/>";

    writer.startElement("child", XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<root/><child");

}



TEST_F(XmlWriterTest_473, StartElementClosesPreviousTagIfNecessary_473) {

    writer.startElement("root", XmlFormatting::Indent);

    writer.startElement("child", XmlFormatting::Indent);

    writer.endElement(XmlFormatting::None);

    EXPECT_THAT(oss.str(), HasSubstr("</child>"));

}



TEST_F(XmlWriterTest_473, StartElementWithEmptyNameDoesNotThrow_473) {

    ASSERT_NO_THROW(writer.startElement("", XmlFormatting::None));

}
