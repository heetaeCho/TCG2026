#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-optcontent-private.h"

#include "Object.h"

#include "Array.h"



using namespace Poppler;

using ::testing::NiceMock;



class MockArray : public Array {

public:

    MOCK_METHOD(int, getLength, (), (const));

    MOCK_METHOD(Object, get, (int i, int recursion), (const));

};



TEST_F(OptContentModelPrivateTest_1274, ParseRBGroupsArray_NullInput_1274) {

    OptContentModel model;

    OptContentModelPrivate optContentModelPrivate(&model, nullptr);

    optContentModelPrivate.parseRBGroupsArray(nullptr);

    EXPECT_EQ(optContentModelPrivate.m_rbgroups, 0);

}



TEST_F(OptContentModelPrivateTest_1274, ParseRBGroupsArray_EmptyArray_1274) {

    OptContentModel model;

    OptContentModelPrivate optContentModelPrivate(&model, nullptr);



    MockArray mockArray;

    EXPECT_CALL(mockArray, getLength()).WillOnce(::testing::Return(0));



    optContentModelPrivate.parseRBGroupsArray(&mockArray);

    EXPECT_EQ(optContentModelPrivate.m_rbgroups, 0);

}



TEST_F(OptContentModelPrivateTest_1274, ParseRBGroupsArray_SingleInnerArray_1274) {

    OptContentModel model;

    OptContentModelPrivate optContentModelPrivate(&model, nullptr);



    MockArray mockArray;

    EXPECT_CALL(mockArray, getLength()).WillOnce(::testing::Return(1));



    Object innerObject(new Array(nullptr));

    EXPECT_CALL(mockArray, get(0, ::testing::_)).WillOnce(::testing::Return(innerObject));



    optContentModelPrivate.parseRBGroupsArray(&mockArray);

    EXPECT_EQ(optContentModelPrivate.m_rbgroups, 1);

}



TEST_F(OptContentModelPrivateTest_1274, ParseRBGroupsArray_MultipleInnerArrays_1274) {

    OptContentModel model;

    OptContentModelPrivate optContentModelPrivate(&model, nullptr);



    MockArray mockArray;

    EXPECT_CALL(mockArray, getLength()).WillOnce(::testing::Return(3));



    Object innerObject1(new Array(nullptr));

    Object innerObject2(new Array(nullptr));

    Object innerObject3(new Array(nullptr));



    EXPECT_CALL(mockArray, get(0, ::testing::_)).WillOnce(::testing::Return(innerObject1));

    EXPECT_CALL(mockArray, get(1, ::testing::_)).WillOnce(::testing::Return(innerObject2));

    EXPECT_CALL(mockArray, get(2, ::testing::_)).WillOnce(::testing::Return(innerObject3));



    optContentModelPrivate.parseRBGroupsArray(&mockArray);

    EXPECT_EQ(optContentModelPrivate.m_rbgroups, 3);

}



TEST_F(OptContentModelPrivateTest_1274, ParseRBGroupsArray_NonArrayElement_1274) {

    OptContentModel model;

    OptContentModelPrivate optContentModelPrivate(&model, nullptr);



    MockArray mockArray;

    EXPECT_CALL(mockArray, getLength()).WillOnce(::testing::Return(1));



    Object nonArrayObject(Object::null());

    EXPECT_CALL(mockArray, get(0, ::testing::_)).WillOnce(::testing::Return(nonArrayObject));



    testing::internal::CaptureStderr();

    optContentModelPrivate.parseRBGroupsArray(&mockArray);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_EQ(optContentModelPrivate.m_rbgroups, 0);

    EXPECT_THAT(output, ::testing::HasSubstr("expected inner array, got: null"));

}
