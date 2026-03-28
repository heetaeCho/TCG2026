#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"

#include "Object.h"



using namespace testing;



// Mock Object for testing purposes

class MockObject : public Object {

public:

    MOCK_METHOD0(isDict, bool());

    MOCK_METHOD1(dictLookupNF, Object(const char* key));

};



TEST_F(LinkLaunchTest_291, IsOk_ReturnsTrue_WhenFileNameIsNotNull_291) {

    MockObject mockActionObj;

    EXPECT_CALL(mockActionObj, isDict()).WillOnce(Return(true));



    LinkLaunch link(&mockActionObj);

    EXPECT_TRUE(link.isOk());

}



TEST_F(LinkLaunchTest_291, IsOk_ReturnsFalse_WhenFileNameIsNull_291) {

    MockObject mockActionObj;

    EXPECT_CALL(mockActionObj, isDict()).WillOnce(Return(false));



    LinkLaunch link(&mockActionObj);

    EXPECT_FALSE(link.isOk());

}



TEST_F(LinkLaunchTest_291, GetKind_ReturnsLinkActionKind_Launch_291) {

    MockObject mockActionObj;

    LinkLaunch link(&mockActionObj);



    EXPECT_EQ(link.getKind(), LinkActionKind::launch);

}



TEST_F(LinkLaunchTest_291, GetFileName_ReturnsValidGooStringPointer_WhenFileNameIsSet_291) {

    MockObject mockActionObj;

    EXPECT_CALL(mockActionObj, isDict()).WillOnce(Return(true));



    LinkLaunch link(&mockActionObj);

    ASSERT_NE(link.getFileName(), nullptr);

}



TEST_F(LinkLaunchTest_291, GetParams_ReturnsValidGooStringPointer_WhenParamsAreSet_291) {

    MockObject mockActionObj;

    EXPECT_CALL(mockActionObj, isDict()).WillOnce(Return(true));



    LinkLaunch link(&mockActionObj);

    ASSERT_NE(link.getParams(), nullptr);

}



TEST_F(LinkLaunchTest_291, GetFileName_ReturnsNullPointer_WhenFileNameIsNotSet_291) {

    MockObject mockActionObj;

    EXPECT_CALL(mockActionObj, isDict()).WillOnce(Return(false));



    LinkLaunch link(&mockActionObj);

    EXPECT_EQ(link.getFileName(), nullptr);

}



TEST_F(LinkLaunchTest_291, GetParams_ReturnsNullPointer_WhenParamsAreNotSet_291) {

    MockObject mockActionObj;

    EXPECT_CALL(mockActionObj, isDict()).WillOnce(Return(false));



    LinkLaunch link(&mockActionObj);

    EXPECT_EQ(link.getParams(), nullptr);

}
