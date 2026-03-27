#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_109 : public ::testing::Test {

protected:

    XMLDocument doc;

    

    XMLDocumentTest_109() : doc(false, COLLAPSE_WHITESPACE) {}

};



TEST_F(XMLDocumentTest_109, WhitespaceMode_CollapseWhitespace_109) {

    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);

}



TEST_F(XMLDocumentTest_109, WhitespaceMode_PreserveWhitespace_109) {

    XMLDocument docWithPreserve(false, PRESERVE_WHITESPACE);

    EXPECT_EQ(docWithPreserve.WhitespaceMode(), PRESERVE_WHITESPACE);

}



TEST_F(XMLDocumentTest_109, ProcessEntities_False_109) {

    EXPECT_FALSE(doc.ProcessEntities());

}



TEST_F(XMLDocumentTest_109, ProcessEntities_True_109) {

    XMLDocument docWithEntities(true, COLLAPSE_WHITESPACE);

    EXPECT_TRUE(docWithEntities.ProcessEntities());

}



TEST_F(XMLDocumentTest_109, HasBOM_DefaultFalse_109) {

    EXPECT_FALSE(doc.HasBOM());

}



TEST_F(XMLDocumentTest_109, SetBOM_True_109) {

    doc.SetBOM(true);

    EXPECT_TRUE(doc.HasBOM());

}



TEST_F(XMLDocumentTest_109, SetBOM_False_109) {

    doc.SetBOM(false);

    EXPECT_FALSE(doc.HasBOM());

}



TEST_F(XMLDocumentTest_109, RootElement_DefaultNull_109) {

    EXPECT_EQ(doc.RootElement(), nullptr);

}



TEST_F(XMLDocumentTest_109, Error_NoErrorInitially_109) {

    EXPECT_FALSE(doc.Error());

    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

    EXPECT_STREQ(doc.ErrorStr(), "");

    EXPECT_STREQ(doc.ErrorName(), "XML_SUCCESS");

}



TEST_F(XMLDocumentTest_109, ErrorLineNum_DefaultZero_109) {

    EXPECT_EQ(doc.ErrorLineNum(), 0);

}
