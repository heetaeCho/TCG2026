#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_111 : public ::testing::Test {

protected:

    XMLDocument doc;

    

    XMLDocumentTest_111() : doc(true, Whitespace::preserve) {}

};



TEST_F(XMLDocumentTest_111, SetBOM_DefaultValue_111) {

    EXPECT_FALSE(doc.HasBOM());

}



TEST_F(XMLDocumentTest_111, SetBOM_EnableBOM_111) {

    doc.SetBOM(true);

    EXPECT_TRUE(doc.HasBOM());

}



TEST_F(XMLDocumentTest_111, SetBOM_DisableBOM_111) {

    doc.SetBOM(false);

    EXPECT_FALSE(doc.HasBOM());

}



TEST_F(XMLDocumentTest_111, SetBOM_ToggleMultipleTimes_111) {

    doc.SetBOM(true);

    EXPECT_TRUE(doc.HasBOM());



    doc.SetBOM(false);

    EXPECT_FALSE(doc.HasBOM());



    doc.SetBOM(true);

    EXPECT_TRUE(doc.HasBOM());

}



TEST_F(XMLDocumentTest_111, ProcessEntities_DefaultValue_111) {

    EXPECT_TRUE(doc.ProcessEntities());

}



TEST_F(XMLDocumentTest_111, WhitespaceMode_DefaultValue_111) {

    EXPECT_EQ(doc.WhitespaceMode(), Whitespace::preserve);

}
