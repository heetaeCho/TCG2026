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



class XMLUnknownTest_208 : public ::testing::Test {

protected:

    MockXMLVisitor mockVisitor;

    XMLDocument doc;

    XMLUnknown unknown;



    XMLUnknownTest_208() : unknown(&doc) {}

};



TEST_F(XMLUnknownTest_208, AcceptCallsVisitOnMockVisitor_208) {

    EXPECT_CALL(mockVisitor, Visit(_)).WillOnce(Return(true));

    bool result = unknown.Accept(&mockVisitor);

    EXPECT_TRUE(result);

}



TEST_F(XMLUnknownTest_208, AcceptReturnsFalseIfMockVisitorFails_208) {

    EXPECT_CALL(mockVisitor, Visit(_)).WillOnce(Return(false));

    bool result = unknown.Accept(&mockVisitor);

    EXPECT_FALSE(result);

}
