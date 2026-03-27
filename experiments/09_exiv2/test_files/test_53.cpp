#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpdatumTest_53 : public ::testing::Test {

protected:

    XmpKey key;

    Value* pValue = nullptr;

    Xmpdatum xmpDatum;



    XmpdatumTest_53() : key("Xmp.test.key"), xmpDatum(key, pValue) {}

};



TEST_F(XmpdatumTest_53, AssignBoolTrueToString_53) {

    xmpDatum = true;

    EXPECT_EQ(xmpDatum.toString(), "True");

}



TEST_F(XmpdatumTest_53, AssignBoolFalseToString_53) {

    xmpDatum = false;

    EXPECT_EQ(xmpDatum.toString(), "False");

}



TEST_F(XmpdatumTest_53, AssignStringDirectly_53) {

    xmpDatum = std::string("testValue");

    EXPECT_EQ(xmpDatum.toString(), "testValue");

}



TEST_F(XmpdatumTest_53, AssignCStyleStringDirectly_53) {

    xmpDatum = "testValue";

    EXPECT_EQ(xmpDatum.toString(), "testValue");

}



TEST_F(XmpdatumTest_53, AssignIntegerToString_53) {

    xmpDatum = 123;

    EXPECT_EQ(xmpDatum.toString(), "123");

}



TEST_F(XmpdatumTest_53, AssignFloatToString_53) {

    xmpDatum = 123.456f;

    EXPECT_EQ(xmpDatum.toString(), "123.456");

}



// Assuming Value is a class that can be constructed and assigned

class MockValue : public Value {

public:

    MOCK_METHOD(void, setValue, (const std::string& value), (override));

};



TEST_F(XmpdatumTest_53, AssignValueObject_53) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, setValue(testing::_)).Times(1);

    xmpDatum = mockValue;

}



// Assuming Rational is a class that can be constructed and assigned

class MockRational : public Rational {

public:

    MOCK_METHOD(void, setValue, (const std::string& value), (override));

};



TEST_F(XmpdatumTest_53, AssignRationalToString_53) {

    MockRational mockRational;

    EXPECT_CALL(mockRational, setValue(testing::_)).Times(1);

    xmpDatum = mockRational;

}
