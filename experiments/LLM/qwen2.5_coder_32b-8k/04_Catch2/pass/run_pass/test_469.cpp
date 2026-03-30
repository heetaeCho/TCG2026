#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;



class XmlWriterTest_469 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter writer{oss};

};



TEST_F(XmlWriterTest_469, StartElementWritesTag_469) {

    writer.startElement("test", XmlFormatting::None);

    EXPECT_THAT(oss.str(), testing::HasSubstr("<test"));

}



TEST_F(XmlWriterTest_469, EndElementClosesTag_469) {

    writer.startElement("test", XmlFormatting::None);

    writer.endElement(XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_469, ScopedElementAutoClosesTagOnDestruction_469) {

    {

        auto element = writer.scopedElement("test", XmlFormatting::None);

    }

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_469, WriteAttributeIncludesAttributeInTag_469) {

    writer.startElement("test", XmlFormatting::None).writeAttribute("attr", "value");

    writer.endElement(XmlFormatting::None);

    EXPECT_THAT(oss.str(), testing::HasSubstr("<test attr=\"value\"></test>"));

}



TEST_F(XmlWriterTest_469, WriteTextIncludesTextInTag_469) {

    writer.startElement("test", XmlFormatting::None).writeText("content", XmlFormatting::None);

    writer.endElement(XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test>content</test>");

}



TEST_F(XmlWriterTest_469, WriteCommentIncludesComment_469) {

    writer.writeComment("This is a comment", XmlFormatting::None);

    EXPECT_THAT(oss.str(), testing::HasSubstr("<!-- This is a comment -->"));

}



TEST_F(XmlWriterTest_469, WriteStylesheetRefIncludesPI_469) {

    writer.writeStylesheetRef("http://example.com/style.xsl");

    EXPECT_EQ(oss.str(), "<?xml-stylesheet href=\"http://example.com/style.xsl\"?>\n");

}
