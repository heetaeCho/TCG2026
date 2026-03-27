#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpTextValueTest_838 : public ::testing::Test {

protected:

    XmpTextValue xmpTextValue;

};



TEST_F(XmpTextValueTest_838, WriteDefaultState_838) {

    std::ostringstream os;

    xmpTextValue.write(os);

    EXPECT_EQ("", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithValueOnly_838) {

    XmpTextValue value("test");

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("test", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithXmpArrayTypeAlt_838) {

    xmpTextValue.setXmpArrayType(XmpValue::xaAlt);

    std::ostringstream os;

    xmpTextValue.write(os);

    EXPECT_EQ("type=\"Alt\" ", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithXmpArrayTypeBag_838) {

    xmpTextValue.setXmpArrayType(XmpValue::xaBag);

    std::ostringstream os;

    xmpTextValue.write(os);

    EXPECT_EQ("type=\"Bag\" ", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithXmpArrayTypeSeq_838) {

    xmpTextValue.setXmpArrayType(XmpValue::xaSeq);

    std::ostringstream os;

    xmpTextValue.write(os);

    EXPECT_EQ("type=\"Seq\" ", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithXmpStructStruct_838) {

    xmpTextValue.setXmpStruct(XmpValue::xsStruct);

    std::ostringstream os;

    xmpTextValue.write(os);

    EXPECT_EQ("type=\"Struct\" ", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithXmpArrayTypeAndValue_838) {

    xmpTextValue.setXmpArrayType(XmpValue::xaSeq);

    XmpTextValue value("test");

    value.setXmpArrayType(XmpValue::xaSeq);

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("type=\"Seq\" test", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithXmpStructAndValue_838) {

    xmpTextValue.setXmpStruct(XmpValue::xsStruct);

    XmpTextValue value("test");

    value.setXmpStruct(XmpValue::xsStruct);

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("type=\"Struct\" test", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithBothXmpArrayTypeAndXmpStruct_838) {

    XmpTextValue value("test");

    value.setXmpArrayType(XmpValue::xaSeq);

    value.setXmpStruct(XmpValue::xsStruct);

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("type=\"Seq\" test"); // XmpArrayType takes precedence

}



TEST_F(XmpTextValueTest_838, WriteWithEmptyValueAndXmpArrayTypeAlt_838) {

    xmpTextValue.setXmpArrayType(XmpValue::xaAlt);

    std::ostringstream os;

    xmpTextValue.write(os);

    EXPECT_EQ("type=\"Alt\" ", os.str());

}



TEST_F(XmpTextValueTest_838, WriteWithEmptyValueAndXmpStructStruct_838) {

    xmpTextValue.setXmpStruct(XmpValue::xsStruct);

    std::ostringstream os;

    xmpTextValue.write(os);

    EXPECT_EQ("type=\"Struct\" ", os.str());

}
