#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"

#include "poppler-structure-element.h"



using ::testing::_;

using ::testing::Return;

using ::testing::InSequence;



class MockObject : public Object {

public:

    MOCK_METHOD(int, arrayGetLength, (), (const));

    MOCK_METHOD(Object, arrayGet, (int), (const));

    MOCK_METHOD(bool, isArray, (), (const));

};



TEST(convert_border_style_2553, SingleElementArray_2553) {

    MockObject mockObject;

    PopplerStructureBorderStyle values[4];



    EXPECT_CALL(mockObject, isArray()).WillOnce(Return(true));

    EXPECT_CALL(mockObject, arrayGetLength()).WillOnce(Return(1));

    EXPECT_CALL(mockObject, arrayGet(0)).WillOnce(Return(Object("solid")));



    convert_border_style(&mockObject, values);



    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(values[i], PopplerStructureBorderStyle::SOLID);

    }

}



TEST(convert_border_style_2553, FourElementArray_2553) {

    MockObject mockObject;

    PopplerStructureBorderStyle values[4];



    EXPECT_CALL(mockObject, isArray()).WillOnce(Return(true));

    EXPECT_CALL(mockObject, arrayGetLength()).WillOnce(Return(4));

    EXPECT_CALL(mockObject, arrayGet(0)).WillOnce(Return(Object("solid")));

    EXPECT_CALL(mockObject, arrayGet(1)).WillOnce(Return(Object("dashed")));

    EXPECT_CALL(mockObject, arrayGet(2)).WillOnce(Return(Object("beveled")));

    EXPECT_CALL(mockObject, arrayGet(3)).WillOnce(Return(Object("inset")));



    convert_border_style(&mockObject, values);



    EXPECT_EQ(values[0], PopplerStructureBorderStyle::SOLID);

    EXPECT_EQ(values[1], PopplerStructureBorderStyle::DASHED);

    EXPECT_EQ(values[2], PopplerStructureBorderStyle::BEVELED);

    EXPECT_EQ(values[3], PopplerStructureBorderStyle::INSET);

}



TEST(convert_border_style_2553, NonArrayObject_2553) {

    MockObject mockObject;

    PopplerStructureBorderStyle values[4];



    EXPECT_CALL(mockObject, isArray()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, getTypeName()).WillOnce(Return("name"));



    convert_border_style(&mockObject, values);



    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(values[i], PopplerStructureBorderStyle::UNKNOWN);

    }

}



TEST(convert_border_style_2553, NullObject_2553) {

    MockObject mockObject;

    PopplerStructureBorderStyle values[4];



    EXPECT_CALL(mockObject, isArray()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, isNull()).WillOnce(Return(true));



    convert_border_style(&mockObject, values);



    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(values[i], PopplerStructureBorderStyle::UNKNOWN);

    }

}



TEST(convert_border_style_2553, ErrorObject_2553) {

    MockObject mockObject;

    PopplerStructureBorderStyle values[4];



    EXPECT_CALL(mockObject, isArray()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, isError()).WillOnce(Return(true));



    convert_border_style(&mockObject, values);



    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(values[i], PopplerStructureBorderStyle::UNKNOWN);

    }

}



TEST(convert_border_style_2553, EofObject_2553) {

    MockObject mockObject;

    PopplerStructureBorderStyle values[4];



    EXPECT_CALL(mockObject, isArray()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, isEOF()).WillOnce(Return(true));



    convert_border_style(&mockObject, values);



    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(values[i], PopplerStructureBorderStyle::UNKNOWN);

    }

}



TEST(convert_border_style_2553, NoneObject_2553) {

    MockObject mockObject;

    PopplerStructureBorderStyle values[4];



    EXPECT_CALL(mockObject, isArray()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, isNone()).WillOnce(Return(true));



    convert_border_style(&mockObject, values);



    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(values[i], PopplerStructureBorderStyle::UNKNOWN);

    }

}
