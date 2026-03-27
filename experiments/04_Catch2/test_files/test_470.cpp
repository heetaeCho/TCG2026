#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using namespace testing;



class XmlWriterTest : public Test {

protected:

    std::ostringstream oss;

    XmlWriter writer{oss};

};



TEST_F(XmlWriterTest_470, WriteText_NormalOperation_470) {

    StringRef text("Hello, World!");

    XmlFormatting fmt = XmlFormatting::None;

    writer.writeText(text, fmt);

    EXPECT_EQ(oss.str(), "Hello, World!");

}



TEST_F(XmlWriterTest_470, WriteText_BoundaryCondition_EmptyString_470) {

    StringRef text("");

    XmlFormatting fmt = XmlFormatting::Indent;

    writer.writeText(text, fmt);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(XmlWriterTest_470, ScopedElement_WriteText_NormalOperation_470) {

    StringRef text("Hello, World!");

    XmlFormatting fmt = XmlFormatting::None;

    writer.scopedElement("test", fmt).writeText(text, fmt);

    EXPECT_EQ(oss.str(), "<test>Hello, World!</test>");

}



TEST_F(XmlWriterTest_470, ScopedElement_WriteText_BoundaryCondition_EmptyString_470) {

    StringRef text("");

    XmlFormatting fmt = XmlFormatting::Indent;

    writer.scopedElement("test", fmt).writeText(text, fmt);

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_470, WriteAttribute_NormalOperation_StringRef_470) {

    StringRef name("attr");

    StringRef value("value");

    XmlFormatting fmt = XmlFormatting::None;

    writer.startElement("test", fmt).writeAttribute(name, value);

    EXPECT_EQ(oss.str(), "<test attr=\"value\">");

}



TEST_F(XmlWriterTest_470, WriteAttribute_NormalOperation_Bool_470) {

    StringRef name("attr");

    bool value = true;

    XmlFormatting fmt = XmlFormatting::None;

    writer.startElement("test", fmt).writeAttribute(name, value);

    EXPECT_EQ(oss.str(), "<test attr=\"true\">");

}



TEST_F(XmlWriterTest_470, WriteAttribute_NormalOperation_CharPtr_470) {

    StringRef name("attr");

    const char* value = "value";

    XmlFormatting fmt = XmlFormatting::None;

    writer.startElement("test", fmt).writeAttribute(name, value);

    EXPECT_EQ(oss.str(), "<test attr=\"value\">");

}



TEST_F(XmlWriterTest_470, WriteComment_NormalOperation_470) {

    StringRef text("This is a comment.");

    XmlFormatting fmt = XmlFormatting::None;

    writer.writeComment(text, fmt);

    EXPECT_EQ(oss.str(), "<!--This is a comment.-->");

}



TEST_F(XmlWriterTest_470, WriteStylesheetRef_NormalOperation_470) {

    StringRef url("http://example.com/style.xsl");

    writer.writeStylesheetRef(url);

    EXPECT_EQ(oss.str(), "<?xml-stylesheet type=\"text/xsl\" href=\"http://example.com/style.xsl\"?>\n");

}



TEST_F(XmlWriterTest_470, EnsureTagClosed_NormalOperation_470) {

    XmlFormatting fmt = XmlFormatting::None;

    writer.startElement("test", fmt);

    writer.ensureTagClosed();

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_470, StartElement_EndElement_NormalOperation_470) {

    XmlFormatting fmt = XmlFormatting::None;

    writer.startElement("test", fmt).endElement(fmt);

    EXPECT_EQ(oss.str(), "<test></test>");

}
