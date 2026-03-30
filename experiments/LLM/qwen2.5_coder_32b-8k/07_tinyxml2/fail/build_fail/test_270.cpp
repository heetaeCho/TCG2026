#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_270 : public ::testing::Test {

protected:

    XMLDocument doc;

};



TEST_F(XMLDocumentTest_270, ClearEmptiesUnlinkedArray_270) {

    // Arrange

    XMLElement* elem = doc.NewElement("test");

    doc._unlinked.Push(elem);



    // Act

    doc.Clear();



    // Assert

    EXPECT_TRUE(doc._unlinked.Empty());

}



TEST_F(XMLDocumentTest_270, ClearResetsParsingDepth_270) {

    // Arrange

    doc._parsingDepth = 5;



    // Act

    doc.Clear();



    // Assert

    EXPECT_EQ(0, doc._parsingDepth);

}



TEST_F(XMLDocumentTest_270, ClearDeletesCharBuffer_270) {

    // Arrange

    doc._charBuffer = new char[10];

    

    // Act

    doc.Clear();

    

    // Assert

    EXPECT_EQ(nullptr, doc._charBuffer);

}



TEST_F(XMLDocumentTest_270, ClearDoesNotThrowOnEmptyState_270) {

    // Arrange & Act & Assert (no exception should be thrown)

    EXPECT_NO_THROW(doc.Clear());

}
