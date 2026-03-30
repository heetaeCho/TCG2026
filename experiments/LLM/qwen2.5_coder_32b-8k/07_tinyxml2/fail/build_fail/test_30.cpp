#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, Visit, (const XMLDeclaration& declaration), (override));

};



TEST_F(MockXMLVisitorTest_30, NormalVisit_ReturnsTrue_30) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(::testing::_)).WillOnce(Return(true));



    XMLDeclaration decl;

    bool result = mockVisitor.Visit(decl);

    EXPECT_TRUE(result);

}



TEST_F(MockXMLVisitorTest_30, NormalVisit_ReturnsFalse_30) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(::testing::_)).WillOnce(Return(false));



    XMLDeclaration decl;

    bool result = mockVisitor.Visit(decl);

    EXPECT_FALSE(result);

}



TEST_F(MockXMLVisitorTest_30, MultipleVisits_ReturnsTrue_30) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(::testing::_)).WillRepeatedly(Return(true));



    XMLDeclaration decl1, decl2;

    bool result1 = mockVisitor.Visit(decl1);

    bool result2 = mockVisitor.Visit(decl2);

    EXPECT_TRUE(result1);

    EXPECT_TRUE(result2);

}



TEST_F(MockXMLVisitorTest_30, MultipleVisits_ReturnsFalse_30) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, Visit(::testing::_)).WillRepeatedly(Return(false));



    XMLDeclaration decl1, decl2;

    bool result1 = mockVisitor.Visit(decl1);

    bool result2 = mockVisitor.Visit(decl2);

    EXPECT_FALSE(result1);

    EXPECT_FALSE(result2);

}
