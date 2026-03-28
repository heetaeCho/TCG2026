#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLVisitorMock : public XMLVisitor {

public:

    MOCK_METHOD1(VisitEnter, bool(const XMLDocument& doc));

};



TEST_F(XMLVisitorTest_26, VisitEnter_DefaultReturnTrue_26) {

    XMLVisitorMock visitor;

    EXPECT_CALL(visitor, VisitEnter(::testing::_))

        .WillOnce(::testing::Return(true));



    XMLDocument doc;

    bool result = visitor.VisitEnter(doc);

    EXPECT_TRUE(result);

}



TEST_F(XMLVisitorTest_26, VisitEnter_DefaultReturnFalse_26) {

    XMLVisitorMock visitor;

    EXPECT_CALL(visitor, VisitEnter(::testing::_))

        .WillOnce(::testing::Return(false));



    XMLDocument doc;

    bool result = visitor.VisitEnter(doc);

    EXPECT_FALSE(result);

}
