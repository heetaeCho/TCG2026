#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_283 : public ::testing::Test {

protected:

    XMLDocument doc;

};



TEST_F(XMLDocumentTest_283, ParseValidXML_283) {

    const char* xml = "<root></root>";

    XMLError result = doc.Parse(xml);

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_283, ParseEmptyString_283) {

    const char* xml = "";

    XMLError result = doc.Parse(xml);

    EXPECT_EQ(result, XML_ERROR_EMPTY_DOCUMENT);

}



TEST_F(XMLDocumentTest_283, ParseNullPointer_283) {

    const char* xml = nullptr;

    XMLError result = doc.Parse(xml);

    EXPECT_EQ(result, XML_ERROR_EMPTY_DOCUMENT);

}



TEST_F(XMLDocumentTest_283, ParseInvalidXML_283) {

    const char* xml = "<root></roo>";

    XMLError result = doc.Parse(xml);

    EXPECT_NE(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_283, ParseWithSizeZero_283) {

    const char* xml = "<root></root>";

    XMLError result = doc.Parse(xml, 0);

    EXPECT_EQ(result, XML_ERROR_EMPTY_DOCUMENT);

}



TEST_F(XMLDocumentTest_283, ParseWithNegativeOneSize_283) {

    const char* xml = "<root></root>";

    XMLError result = doc.Parse(xml, static_cast<size_t>(-1));

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_283, ParseWithExactSize_283) {

    const char* xml = "<root></root>";

    size_t nBytes = strlen(xml);

    XMLError result = doc.Parse(xml, nBytes);

    EXPECT_EQ(result, XML_SUCCESS);

}
