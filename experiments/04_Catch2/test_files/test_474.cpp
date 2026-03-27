#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::InSequence;



class XmlWriterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter writer{oss};



    XmlFormatting fmt = XmlFormatting::Default;

};



TEST_F(XmlWriterTest_474, StartElementWritesToStream_474) {

    writer.startElement("test", fmt);

    EXPECT_TRUE(oss.str().find("<test") != std::string::npos);

}



TEST_F(XmlWriterTest_474, EndElementClosesTagProperly_474) {

    writer.startElement("test", fmt);

    writer.endElement(fmt);

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_474, WriteAttributeAddsAttributeToTag_474) {

    writer.startElement("test", fmt).writeAttribute("attr", "value");

    writer.endElement(fmt);

    EXPECT_TRUE(oss.str().find("<test attr=\"value\">") != std::string::npos);

}



TEST_F(XmlWriterTest_474, WriteTextIncludesTextInTag_474) {

    writer.startElement("test", fmt).writeText("content", fmt);

    writer.endElement(fmt);

    EXPECT_TRUE(oss.str().find("<test>content</test>") != std::string::npos);

}



TEST_F(XmlWriterTest_474, WriteCommentIncludesCommentInOutput_474) {

    writer.writeComment("comment");

    EXPECT_TRUE(oss.str().find("<!--comment-->") != std::string::npos);

}



TEST_F(XmlWriterTest_474, ScopedElementAutoClosesTagOnDestruction_474) {

    {

        auto scoped = writer.scopedElement("test", fmt);

    }

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_474, MultipleElementsProperlyNested_474) {

    auto outerScoped = writer.scopedElement("outer", fmt);

    auto innerScoped = writer.scopedElement("inner", fmt);

    EXPECT_TRUE(oss.str().find("<outer><inner></inner>") != std::string::npos);

}



TEST_F(XmlWriterTest_474, WriteStylesheetRefIncludesPiInOutput_474) {

    writer.writeStylesheetRef("style.xsl");

    EXPECT_TRUE(oss.str().find("<?xml-stylesheet href=\"style.xsl\"?>") != std::string::npos);

}
