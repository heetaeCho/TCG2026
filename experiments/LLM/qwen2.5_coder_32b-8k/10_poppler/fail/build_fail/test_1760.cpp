#include <gtest/gtest.h>

#include "Object.h"



// Mock class for Object if needed, but not used in this case as we are treating it as a black box.

// class MockObject : public Object {

// public:

//     MOCK_METHOD(bool, isNum, (), (const));

// };



TEST(IsNumberTest_1760, IntegerObjectIsNumber_1760) {

    Object intObj(42);

    EXPECT_TRUE(isNumber(&intObj));

}



TEST(IsNumberTest_1760, RealObjectIsNumber_1760) {

    Object realObj(3.14);

    EXPECT_TRUE(isNumber(&realObj));

}



TEST(IsNumberTest_1760, StringObjectIsNotNumber_1760) {

    Object stringObj("Hello");

    EXPECT_FALSE(isNumber(&stringObj));

}



TEST(IsNumberTest_1760, NameObjectIsNotNumber_1760) {

    Object nameObj(Object::nameType, "Name");

    EXPECT_FALSE(isNumber(&nameObj));

}



TEST(IsNumberTest_1760, ArrayObjectIsNotNumber_1760) {

    Object arrayObj(new Array());

    EXPECT_FALSE(isNumber(&arrayObj));

}



TEST(IsNumberTest_1760, DictObjectIsNotNumber_1760) {

    Object dictObj(new Dict());

    EXPECT_FALSE(isNumber(&dictObj));

}



TEST(IsNumberTest_1760, NullObjectIsNotNumber_1760) {

    Object nullObj = Object::null();

    EXPECT_FALSE(isNumber(&nullObj));

}



TEST(IsNumberTest_1760, BoolObjectIsNotNumber_1760) {

    Object boolObj(true);

    EXPECT_FALSE(isNumber(&boolObj));

}
