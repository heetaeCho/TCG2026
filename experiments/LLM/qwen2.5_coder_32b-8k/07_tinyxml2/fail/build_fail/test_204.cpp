#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::NiceMock;

using ::testing::Return;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, VisitEnter, (const XMLDocument&), (override));

    MOCK_METHOD(bool, VisitExit, (const XMLDocument&), (override));

    MOCK_METHOD(bool, VisitEnter, (const XMLElement&, const XMLAttribute*), (override));

    MOCK_METHOD(bool, VisitExit, (const XMLElement&), (override));

    MOCK_METHOD(bool, Visit, (const XMLDeclaration&), (override));

    MOCK_METHOD(bool, Visit, (const XMLText&), (override));

    MOCK_METHOD(bool, Visit, (const XMLComment&), (override));

    MOCK_METHOD(bool, Visit, (const XMLUnknown&), (override));

};



class XMLDeclarationTest_204 : public ::testing::Test {

protected:

    MockXMLVisitor mockVisitor;

    XMLDocument doc;

    XMLDeclaration declaration;



    XMLDeclarationTest_204() : declaration(&doc) {}

};



TEST_F(XMLDeclarationTest_204, AcceptCallsVisitOnVisitor_204) {

    EXPECT_CALL(mockVisitor, Visit(::testing::Ref(declaration))).WillOnce(Return(true));

    bool result = declaration.Accept(&mockVisitor);

    EXPECT_TRUE(result);

}



TEST_F(XMLDeclarationTest_204, AcceptReturnsFalseIfVisitorVisitFails_204) {

    EXPECT_CALL(mockVisitor, Visit(::testing::Ref(declaration))).WillOnce(Return(false));

    bool result = declaration.Accept(&mockVisitor);

    EXPECT_FALSE(result);

}



TEST_F(XMLDeclarationTest_204, AcceptThrowsExceptionIfNullVisitorPassed_204) {

    EXPECT_THROW(declaration.Accept(nullptr), std::exception);

}
