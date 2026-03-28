#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, VisitExit, (const XMLDocument& doc), (override));

};



class XMLVisitorTest_27 : public ::testing::Test {

protected:

    XMLDocument document;

    MockXMLVisitor mockVisitor;

};



TEST_F(XMLVisitorTest_27, VisitExit_DefaultReturnTrue_27) {

    EXPECT_CALL(mockVisitor, VisitExit(::testing::_)).WillOnce(::testing::Return(true));

    bool result = mockVisitor.VisitExit(document);

    EXPECT_TRUE(result);

}



TEST_F(XMLVisitorTest_27, VisitExit_CustomReturnFalse_27) {

    EXPECT_CALL(mockVisitor, VisitExit(::testing::_)).WillOnce(::testing::Return(false));

    bool result = mockVisitor.VisitExit(document);

    EXPECT_FALSE(result);

}
