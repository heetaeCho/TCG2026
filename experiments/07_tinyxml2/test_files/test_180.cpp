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

};



class XMLDocumentTest_180 : public ::testing::Test {

protected:

    XMLDocument doc;

    MockXMLVisitor visitor;



    XMLDocumentTest_180() : doc(false, Whitespace::COLLAPSE_WHITESPACE) {}

};



TEST_F(XMLDocumentTest_180, AcceptCallsVisitEnterAndVisitExitOnEmptyDocument_180) {

    EXPECT_CALL(visitor, VisitEnter(_)).WillOnce(Return(true));

    EXPECT_CALL(visitor, VisitExit(_)).WillOnce(Return(true));



    bool result = doc.Accept(&visitor);

    EXPECT_TRUE(result);

}



TEST_F(XMLDocumentTest_180, AcceptStopsTraversalIfVisitEnterReturnsFalse_180) {

    EXPECT_CALL(visitor, VisitEnter(_)).WillOnce(Return(false));

    EXPECT_CALL(visitor, VisitExit(_)).Times(0);



    bool result = doc.Accept(&visitor);

    EXPECT_FALSE(result);

}



TEST_F(XMLDocumentTest_180, AcceptContinuesTraversalIfVisitEnterReturnsTrue_180) {

    // Assuming the document has some children that would be visited

    EXPECT_CALL(visitor, VisitEnter(_)).WillOnce(Return(true));

    EXPECT_CALL(visitor, VisitExit(_)).WillOnce(Return(true));



    bool result = doc.Accept(&visitor);

    EXPECT_TRUE(result);

}



TEST_F(XMLDocumentTest_180, AcceptCallsVisitExitEvenIfTraversalStops_180) {

    // Assuming the document has some children that would be visited

    EXPECT_CALL(visitor, VisitEnter(_)).WillOnce(Return(false));

    EXPECT_CALL(visitor, VisitExit(_)).WillOnce(Return(true));



    bool result = doc.Accept(&visitor);

    EXPECT_FALSE(result);

}



TEST_F(XMLDocumentTest_180, AcceptPropagatesFalseFromChildTraversal_180) {

    // Assuming the document has some children that would be visited

    EXPECT_CALL(visitor, VisitEnter(_)).WillOnce(Return(true));

    EXPECT_CALL(visitor, VisitExit(_)).WillOnce(Return(false));



    bool result = doc.Accept(&visitor);

    EXPECT_FALSE(result);

}
