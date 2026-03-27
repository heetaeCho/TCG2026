#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::HasSubstr;



TEST_F(XmlWriterTest_479, WriteText_NormalOperation_479) {

    std::ostringstream oss;

    XmlWriter writer(oss);

    writer.startElement("test", XmlFormatting::None);

    writer.writeText(StringRef("Hello, World!"), XmlFormatting::None);

    EXPECT_THAT(oss.str(), HasSubstr("Hello, World!"));

}



TEST_F(XmlWriterTest_479, WriteText_BoundaryEmptyText_479) {

    std::ostringstream oss;

    XmlWriter writer(oss);

    writer.startElement("test", XmlFormatting::None);

    writer.writeText(StringRef(""), XmlFormatting::None);

    EXPECT_EQ(oss.str(), "<test></test>");

}



TEST_F(XmlWriterTest_479, WriteText_ExceptionTopLevelElement_479) {

    std::ostringstream oss;

    XmlWriter writer(oss);

    EXPECT_THROW(writer.writeText(StringRef("Hello"), XmlFormatting::None), Catch::Detail::EnforceException);

}



TEST_F(XmlWriterTest_479, WriteText_VerifyIndentation_479) {

    std::ostringstream oss;

    XmlWriter writer(oss);

    writer.startElement("test", XmlFormatting::NewLine);

    writer.writeText(StringRef("Hello"), XmlFormatting::None);

    EXPECT_THAT(oss.str(), HasSubstr("\n  Hello"));

}



TEST_F(XmlWriterTest_479, WriteText_VerifyXmlEncoding_479) {

    std::ostringstream oss;

    XmlWriter writer(oss);

    writer.startElement("test", XmlFormatting::None);

    writer.writeText(StringRef("<>&\"'"), XmlFormatting::None);

    EXPECT_THAT(oss.str(), HasSubstr("&lt;&gt;&amp;\"'"));

}
