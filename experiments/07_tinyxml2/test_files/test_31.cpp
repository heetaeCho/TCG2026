#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/tinyxml2/tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD1(Visit, bool(const XMLText& text));

};



TEST_F(MockXMLVisitorTest_31, VisitDefaultReturnTrue_31) {

    MockXMLVisitor visitor;

    EXPECT_CALL(visitor, Visit(::testing::_)).WillOnce(Return(true));



    XMLText mockText;

    bool result = visitor.Visit(mockText);

    EXPECT_TRUE(result);

}



TEST_F(MockXMLVisitorTest_31, VisitMockReturnFalse_31) {

    MockXMLVisitor visitor;

    EXPECT_CALL(visitor, Visit(::testing::_)).WillOnce(Return(false));



    XMLText mockText;

    bool result = visitor.Visit(mockText);

    EXPECT_FALSE(result);

}
