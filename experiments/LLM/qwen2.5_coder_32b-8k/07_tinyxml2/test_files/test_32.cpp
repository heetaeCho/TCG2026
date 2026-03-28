#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, Visit, (const XMLComment& comment), (override));

};



TEST_F(MockXMLVisitorTest_32, VisitDefaultBehavior_32) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(::testing::_)).WillOnce(Return(true));



    XMLComment dummyComment;

    bool result = mockVisitor.Visit(dummyComment);

    EXPECT_TRUE(result);

}



TEST_F(MockXMLVisitorTest_32, VisitFalseReturn_32) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(::testing::_)).WillOnce(Return(false));



    XMLComment dummyComment;

    bool result = mockVisitor.Visit(dummyComment);

    EXPECT_FALSE(result);

}
