#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;

using ::testing::_;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, VisitEnter, (const XMLElement&, const XMLAttribute*), (override));

    MOCK_METHOD(bool, VisitExit, (const XMLElement&), (override));

};



class XMLElementTest_267 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement element{ &doc };

    MockXMLVisitor mock_visitor;

};



TEST_F(XMLElementTest_267, AcceptCallsVisitEnterAndExit_267) {

    EXPECT_CALL(mock_visitor, VisitEnter(_, _)).WillOnce(Return(true));

    EXPECT_CALL(mock_visitor, VisitExit(_)).WillOnce(Return(true));



    bool result = element.Accept(&mock_visitor);



    EXPECT_TRUE(result);

}



TEST_F(XMLElementTest_267, AcceptReturnsFalseIfVisitEnterFails_267) {

    EXPECT_CALL(mock_visitor, VisitEnter(_, _)).WillOnce(Return(false));

    EXPECT_CALL(mock_visitor, VisitExit(_)).Times(0);



    bool result = element.Accept(&mock_visitor);



    EXPECT_FALSE(result);

}



TEST_F(XMLElementTest_267, AcceptReturnsFalseIfVisitExitFails_267) {

    EXPECT_CALL(mock_visitor, VisitEnter(_, _)).WillOnce(Return(true));

    EXPECT_CALL(mock_visitor, VisitExit(_)).WillOnce(Return(false));



    bool result = element.Accept(&mock_visitor);



    EXPECT_FALSE(result);

}



TEST_F(XMLElementTest_267, AcceptHandlesNullVisitor_267) {

    XMLVisitor* null_visitor = nullptr;



    bool result = element.Accept(null_visitor);



    EXPECT_FALSE(result);

}
