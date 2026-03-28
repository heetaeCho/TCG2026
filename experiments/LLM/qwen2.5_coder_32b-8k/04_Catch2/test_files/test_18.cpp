#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::HasSubstr;



class XmlWriterTest_18 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter xmlWriter{oss};



    void SetUp() override {

        // Set up any state here if needed

    }



    void TearDown() override {

        // Clean up any state here if needed

    }

};



TEST_F(XmlWriterTest_18, WriteAttributeWithStringRef_18) {

    StringRef name("name");

    StringRef attribute("value");



    xmlWriter.writeAttribute(name, attribute);



    EXPECT_THAT(oss.str(), HasSubstr(R"(name="value")"));

}



TEST_F(XmlWriterTest_18, WriteAttributeWithBoolTrue_18) {

    StringRef name("active");



    xmlWriter.writeAttribute(name, true);



    EXPECT_THAT(oss.str(), HasSubstr(R"(active="true")"));

}



TEST_F(XmlWriterTest_18, WriteAttributeWithBoolFalse_18) {

    StringRef name("active");



    xmlWriter.writeAttribute(name, false);



    EXPECT_THAT(oss.str(), HasSubstr(R"(active="false")"));

}



TEST_F(XmlWriterTest_18, WriteAttributeWithCString_18) {

    StringRef name("type");

    const char* attribute = "text";



    xmlWriter.writeAttribute(name, attribute);



    EXPECT_THAT(oss.str(), HasSubstr(R"(type="text")"));

}



TEST_F(XmlWriterTest_18, WriteAttributeWithTemplateType_18) {

    StringRef name("count");

    int value = 42;



    xmlWriter.writeAttribute(name, value);



    EXPECT_THAT(oss.str(), HasSubstr(R"(count="42")"));

}



TEST_F(XmlWriterTest_18, WriteMultipleAttributes_18) {

    StringRef name1("name");

    StringRef attribute1("value");

    StringRef name2("active");

    bool attribute2 = true;



    xmlWriter.writeAttribute(name1, attribute1);

    xmlWriter.writeAttribute(name2, attribute2);



    EXPECT_THAT(oss.str(), HasSubstr(R"(name="value" active="true")"));

}



TEST_F(XmlWriterTest_18, WriteAttributeWithEmptyName_18) {

    StringRef name("");

    StringRef attribute("value");



    xmlWriter.writeAttribute(name, attribute);



    // Since the name is empty, it should not appear in the output

    EXPECT_EQ(oss.str(), "");

}



TEST_F(XmlWriterTest_18, WriteAttributeWithEmptyValue_18) {

    StringRef name("name");

    StringRef attribute("");



    xmlWriter.writeAttribute(name, attribute);



    EXPECT_THAT(oss.str(), HasSubstr(R"(name="")"));

}
