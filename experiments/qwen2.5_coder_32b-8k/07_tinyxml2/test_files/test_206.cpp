#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUnknownTest : public ::testing::Test {

protected:

    XMLDocument* document;

    XMLUnknown* unknownNode;



    virtual void SetUp() {

        document = new XMLDocument();

        unknownNode = new XMLUnknown(document);

    }



    virtual void TearDown() {

        delete unknownNode;

        delete document;

    }

};



TEST_F(XMLUnknownTest_NormalOperation_206, ShallowCloneReturnsNonNull_206) {

    XMLNode* clonedNode = unknownNode->ShallowClone(document);

    EXPECT_NE(clonedNode, nullptr);

}



TEST_F(XMLUnknownTest_BoundaryConditions_206, ShallowCloneWithNullDocumentUsesInternalDocument_206) {

    XMLNode* clonedNode = unknownNode->ShallowClone(nullptr);

    EXPECT_NE(clonedNode, nullptr);

}



TEST_F(XMLUnknownTest_ExceptionalCases_206, ShallowCloneWithInvalidDocumentDoesNotCrash_206) {

    XMLDocument invalidDoc(false, Whitespace::COLLAPSE_WHITESPACE);

    XMLNode* clonedNode = unknownNode->ShallowClone(&invalidDoc);

    EXPECT_NE(clonedNode, nullptr);

}



TEST_F(XMLUnknownTest_VerifyExternalInteractions_206, ShallowCloneCallsNewUnknownOnDocument_206) {

    EXPECT_CALL(*document, NewUnknown(_)).Times(1);

    XMLNode* clonedNode = unknownNode->ShallowClone(document);

}
