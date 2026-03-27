#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;

using ::testing::_;

using ::testing::Return;



class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, VisitEnter, (const XMLElement& element, const XMLAttribute* firstAttribute), (override));

};



TEST_F(MockXMLVisitorTest_28, NormalOperation_ReturnsTrue_28) {

    MockXMLVisitor visitor;

    XMLElement mockElement;

    XMLAttribute mockAttribute;



    EXPECT_CALL(visitor, VisitEnter(_, _)).WillOnce(Return(true));



    bool result = visitor.VisitEnter(mockElement, &mockAttribute);

    EXPECT_TRUE(result);

}



TEST_F(MockXMLVisitorTest_28, NormalOperation_ReturnsFalse_28) {

    MockXMLVisitor visitor;

    XMLElement mockElement;

    XMLAttribute mockAttribute;



    EXPECT_CALL(visitor, VisitEnter(_, _)).WillOnce(Return(false));



    bool result = visitor.VisitEnter(mockElement, &mockAttribute);

    EXPECT_FALSE(result);

}



TEST_F(MockXMLVisitorTest_28, NullFirstAttribute_ReturnsTrue_28) {

    MockXMLVisitor visitor;

    XMLElement mockElement;



    EXPECT_CALL(visitor, VisitEnter(_, _)).WillOnce(Return(true));



    bool result = visitor.VisitEnter(mockElement, nullptr);

    EXPECT_TRUE(result);

}



TEST_F(MockXMLVisitorTest_28, NullFirstAttribute_ReturnsFalse_28) {

    MockXMLVisitor visitor;

    XMLElement mockElement;



    EXPECT_CALL(visitor, VisitEnter(_, _)).WillOnce(Return(false));



    bool result = visitor.VisitEnter(mockElement, nullptr);

    EXPECT_FALSE(result);

}
