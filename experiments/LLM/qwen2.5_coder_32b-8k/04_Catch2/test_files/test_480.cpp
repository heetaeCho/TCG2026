#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::HasSubstr;



class XmlWriterTest_480 : public ::testing::Test {

protected:

    std::ostringstream stream;

    XmlWriter writer{stream};

};



TEST_F(XmlWriterTest_480, WriteComment_NormalOperation_480) {

    writer.writeComment("This is a comment", XmlFormatting::None);

    EXPECT_EQ(stream.str(), "<!-- This is a comment -->");

}



TEST_F(XmlWriterTest_480, WriteComment_EmptyString_480) {

    writer.writeComment("", XmlFormatting::None);

    EXPECT_EQ(stream.str(), "<!--  -->");

}



TEST_F(XmlWriterTest_480, WriteComment_SpecialCharacters_480) {

    writer.writeComment("<>&\"'", XmlFormatting::None);

    EXPECT_EQ(stream.str(), "<!-- <>&\"' -->");

}



TEST_F(XmlWriterTest_480, WriteComment_BoundaryCondition_480) {

    writer.writeComment("a", XmlFormatting::None);

    EXPECT_EQ(stream.str(), "<!-- a -->");

}



TEST_F(XmlWriterTest_480, WriteComment_WithIndentation_480) {

    writer.writeComment("indented comment", XmlFormatting::Indented);

    EXPECT_THAT(stream.str(), HasSubstr("  <!-- indented comment -->"));

}
