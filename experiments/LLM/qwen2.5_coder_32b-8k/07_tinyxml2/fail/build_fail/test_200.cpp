#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;

using ::testing::_;



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



class XMLCommentTest_200 : public ::testing::Test {

protected:

    MockXMLVisitor mockVisitor;

    XMLDocument doc;

    XMLComment xmlComment{&doc};

};



TEST_F(XMLCommentTest_200, AcceptCallsVisitOnVisitor_200) {

    EXPECT_CALL(mockVisitor, Visit(_)).WillOnce(Return(true));

    bool result = xmlComment.Accept(&mockVisitor);

    EXPECT_TRUE(result);

}



TEST_F(XMLCommentTest_200, AcceptReturnsFalseWhenVisitFails_200) {

    EXPECT_CALL(mockVisitor, Visit(_)).WillOnce(Return(false));

    bool result = xmlComment.Accept(&mockVisitor);

    EXPECT_FALSE(result);

}



TEST_F(XMLCommentTest_200, AcceptDoesNotCallOtherVisitMethods_200) {

    EXPECT_CALL(mockVisitor, Visit(_)).WillOnce(Return(true));

    EXPECT_CALL(mockVisitor, VisitEnter(_, _)).Times(0);

    EXPECT_CALL(mockVisitor, VisitExit(_)).Times(0);

    EXPECT_CALL(mockVisitor, Visit(_)).Times(1);  // Only Visit should be called

    bool result = xmlComment.Accept(&mockVisitor);

    EXPECT_TRUE(result);

}



TEST_F(XMLCommentTest_200, AcceptHandlesNullVisitor_200) {

    XMLVisitor* nullVisitor = nullptr;

    EXPECT_FALSE(xmlComment.Accept(nullVisitor));

}
