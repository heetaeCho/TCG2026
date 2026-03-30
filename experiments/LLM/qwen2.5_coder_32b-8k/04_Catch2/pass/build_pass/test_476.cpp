#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::HasSubstr;



class XmlWriterTest_476 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter writer{oss};



    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(XmlWriterTest_476, WriteAttribute_NormalOperation_476) {

    writer.writeAttribute("name", "value");

    EXPECT_THAT(oss.str(), HasSubstr(" name=\"value\""));

}



TEST_F(XmlWriterTest_476, WriteAttribute_EmptyName_476) {

    writer.writeAttribute("", "value");

    EXPECT_EQ(oss.str(), "");

}



TEST_F(XmlWriterTest_476, WriteAttribute_EmptyValue_476) {

    writer.writeAttribute("name", "");

    EXPECT_EQ(oss.str(), "");

}



TEST_F(XmlWriterTest_476, WriteAttribute_BoolTrue_476) {

    writer.writeAttribute("active", true);

    EXPECT_THAT(oss.str(), HasSubstr(" active=\"true\""));

}



TEST_F(XmlWriterTest_476, WriteAttribute_BoolFalse_476) {

    writer.writeAttribute("active", false);

    EXPECT_THAT(oss.str(), HasSubstr(" active=\"false\""));

}



TEST_F(XmlWriterTest_476, WriteAttribute_CharPtr_476) {

    writer.writeAttribute("name", "value");

    EXPECT_THAT(oss.str(), HasSubstr(" name=\"value\""));

}



TEST_F(XmlWriterTest_476, WriteAttribute_Templated_476) {

    writer.writeAttribute("count", 5);

    EXPECT_THAT(oss.str(), HasSubstr(" count=\"5\""));

}
