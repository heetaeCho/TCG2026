#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class XmlWriterTest_472 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter writer;



    XmlWriterTest_472() : writer(oss) {}

};



TEST_F(XmlWriterTest_472, ConstructorInitializesStream_472) {

    // No direct observable behavior to test except through subsequent operations

}



TEST_F(XmlWriterTest_472, StartElementWritesTag_472) {

    writer.startElement("test", XmlFormatting::None);

    EXPECT_TRUE(oss.str().find("<test>") != std::string::npos);

}



TEST_F(XmlWriterTest_472, EndElementClosesTag_472) {

    writer.startElement("test", XmlFormatting::None).endElement(XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_472, WriteAttributeAddsAttribute_472) {

    writer.startElement("test", XmlFormatting::None)

        .writeAttribute("attr", "value")

        .endElement(XmlFormatting::None);

    EXPECT_TRUE(oss.str().find("<test attr=\"value\"></test>") != std::string::npos);

}



TEST_F(XmlWriterTest_472, WriteTextAddsContent_472) {

    writer.startElement("test", XmlFormatting::None)

        .writeText("content", XmlFormatting::None)

        .endElement(XmlFormatting::None);

    EXPECT_TRUE(oss.str().find("<test>content</test>") != std::string::npos);

}



TEST_F(XmlWriterTest_472, WriteCommentAddsComment_472) {

    writer.writeComment("comment", XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<!--comment-->");

}



TEST_F(XmlWriterTest_472, NestedElementsProperlyClosed_472) {

    writer.startElement("outer", XmlFormatting::None)

        .startElement("inner", XmlFormatting::None)

        .endElement(XmlFormatting::None)

        .endElement(XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<outer><inner></inner></outer>");

}



TEST_F(XmlWriterTest_472, DestructorClosesAllTags_472) {

    writer.startElement("test", XmlFormatting::None);

    // Destructor will close the tag

    EXPECT_EQ(writer.~XmlWriter(), void());

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_472, WriteStylesheetRefAddsPI_472) {

    writer.writeStylesheetRef("style.xsl");

    EXPECT_TRUE(oss.str().find("<?xml-stylesheet href=\"style.xsl\"?>") != std::string::npos);

}



TEST_F(XmlWriterTest_472, EnsureTagClosedClosesOpenTag_472) {

    writer.startElement("test", XmlFormatting::None).ensureTagClosed();

    EXPECT_TRUE(oss.str().find("<test></test>") != std::string::npos);

}
