#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class XmlWriterTest_471 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter writer{oss};

};



TEST_F(XmlWriterTest_471, WriteAttributeWithStringRef_471) {

    StringRef name("name");

    StringRef attribute("value");



    writer.writeAttribute(name, attribute);



    EXPECT_THAT(oss.str(), testing::HasSubstr(R"(name="value")"));

}



TEST_F(XmlWriterTest_471, WriteAttributeWithBoolTrue_471) {

    StringRef name("visible");



    writer.writeAttribute(name, true);



    EXPECT_THAT(oss.str(), testing::HasSubstr(R"(visible="true")"));

}



TEST_F(XmlWriterTest_471, WriteAttributeWithBoolFalse_471) {

    StringRef name("visible");



    writer.writeAttribute(name, false);



    EXPECT_THAT(oss.str(), testing::HasSubstr(R"(visible="false")"));

}



TEST_F(XmlWriterTest_471, WriteAttributeWithCharPtr_471) {

    StringRef name("type");

    const char* attribute = "text";



    writer.writeAttribute(name, attribute);



    EXPECT_THAT(oss.str(), testing::HasSubstr(R"(type="text")"));

}



TEST_F(XmlWriterTest_471, WriteAttributeWithEmptyStringRef_471) {

    StringRef name;

    StringRef attribute;



    writer.writeAttribute(name, attribute);



    EXPECT_EQ(oss.str(), "");

}



TEST_F(XmlWriterTest_471, ScopedElementWriteAttributeWithStringRef_471) {

    XmlWriter::ScopedElement element = writer.scopedElement("element", XmlFormatting::None);

    StringRef name("name");

    StringRef attribute("value");



    element.writeAttribute(name, attribute);



    EXPECT_THAT(oss.str(), testing::HasSubstr(R"(<element name="value">)"));

}



TEST_F(XmlWriterTest_471, ScopedElementWriteMultipleAttributes_471) {

    XmlWriter::ScopedElement element = writer.scopedElement("element", XmlFormatting::None);

    StringRef name1("name");

    StringRef attribute1("value");

    StringRef name2("type");

    const char* attribute2 = "text";



    element.writeAttribute(name1, attribute1).writeAttribute(name2, attribute2);



    EXPECT_THAT(oss.str(), testing::HasSubstr(R"(<element name="value" type="text">)"));

}
