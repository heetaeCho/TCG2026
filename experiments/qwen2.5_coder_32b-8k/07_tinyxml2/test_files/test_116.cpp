#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_116 : public ::testing::Test {

protected:

    XMLDocument doc;

};



TEST_F(XMLDocumentTest_116, ShallowClone_ReturnsNullptr_116) {

    // Arrange

    XMLDocument newDoc;



    // Act

    XMLNode* clonedNode = doc.ShallowClone(&newDoc);



    // Assert

    EXPECT_EQ(clonedNode, nullptr);

}



TEST_F(XMLDocumentTest_116, ShallowClone_NullptrArgument_116) {

    // Arrange



    // Act

    XMLNode* clonedNode = doc.ShallowClone(nullptr);



    // Assert

    EXPECT_EQ(clonedNode, nullptr);

}
