#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class XmlWriterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter xmlWriter{oss};



    void SetUp() override {

        // Clear the output stream before each test

        oss.str("");

        oss.clear();

    }

};



TEST_F(XmlWriterTest_468, StartElementWritesCorrectTag_468) {

    xmlWriter.startElement("test", XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test>");

}



TEST_F(XmlWriterTest_468, EndElementClosesTag_468) {

    xmlWriter.startElement("test", XmlFormatting::None).endElement(XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_468, WriteAttributeAddsAttributeToCurrentTag_468) {

    xmlWriter.startElement("test", XmlFormatting::None)

           .writeAttribute("attr", "value")

           .endElement(XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test attr=\"value\"></test>");

}



TEST_F(XmlWriterTest_468, WriteTextAddsTextToCurrentTag_468) {

    xmlWriter.startElement("test", XmlFormatting::None)

           .writeText("sample text", XmlFormatting::None)

           .endElement(XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test>sample text</test>");

}



TEST_F(XmlWriterTest_468, WriteCommentAddsCommentToStream_468) {

    xmlWriter.writeComment("This is a comment", XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<!-- This is a comment -->");

}



TEST_F(XmlWriterTest_468, ScopedElementAutomaticallyClosesTag_468) {

    {

        auto scoped = xmlWriter.scopedElement("test", XmlFormatting::None);

        scoped.writeText("scoped text", XmlFormatting::None);

    }

    EXPECT_EQ(oss.str(), "<test>scoped text</test>");

}



TEST_F(XmlWriterTest_468, ScopedElementMoveAssignmentClosesPreviousTag_468) {

    XmlWriter::ScopedElement scoped1 = xmlWriter.scopedElement("first", XmlFormatting::None);

    XmlWriter::ScopedElement scoped2 = xmlWriter.scopedElement("second", XmlFormatting::None);

    scoped1 = std::move(scoped2);

    EXPECT_EQ(oss.str(), "<first><second></second>");

}



TEST_F(XmlWriterTest_468, WriteStylesheetRefAddsLinkToStylesheet_468) {

    xmlWriter.writeStylesheetRef("style.css");

    EXPECT_EQ(oss.str(), "<?xml-stylesheet href=\"style.css\" type=\"text/css\"?>");

}
