#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLVisitorMock : public XMLVisitor {

public:

    MOCK_METHOD1(VisitExit, bool(const XMLElement& element));

};



TEST_F(XMLVisitorTest_29, VisitExit_DefaultReturnTrue_29) {

    XMLVisitor visitor;

    XMLElement element; // Assuming XMLElement is default constructible

    EXPECT_TRUE(visitor.VisitExit(element));

}



TEST_F(XMLVisitorTest_29, VisitExit_MockCalledOnce_29) {

    XMLVisitorMock mockVisitor;

    XMLElement element;



    EXPECT_CALL(mockVisitor, VisitExit(::testing::_)).Times(1);

    mockVisitor.VisitExit(element);

}
