#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/annot_stamp_top_secret.h"

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include "TestProjects/poppler/poppler/Dict.h"



class AnnotStampTopSecretTest_2012 : public ::testing::Test {

protected:

    PDFDoc* mockPdfDoc;

    XRef* mockXRef;



    void SetUp() override {

        mockXRef = new XRef();

        mockPdfDoc = new PDFDoc(mockXRef);

    }



    void TearDown() override {

        delete mockPdfDoc;

        delete mockXRef;

    }

};



TEST_F(AnnotStampTopSecretTest_2012, GetTopSecretStampExtGStateDict_ReturnsValidDict_2012) {

    Dict* extGStateDict = getTopSecretStampExtGStateDict(mockPdfDoc);



    ASSERT_NE(extGStateDict, nullptr);

}



TEST_F(AnnotStampTopSecretTest_2012, GetTopSecretStampExtGStateDict_HasCorrectSubDicts_2012) {

    Dict* extGStateDict = getTopSecretStampExtGStateDict(mockPdfDoc);



    const Object& a0Obj = extGStateDict->lookupNF("a0");

    const Object& a1Obj = extGStateDict->lookupNF("a1");



    EXPECT_TRUE(a0Obj.isDict());

    EXPECT_TRUE(a1Obj.isDict());



    Dict* a0Dict = a0Obj.getDict();

    Dict* a1Dict = a1Obj.getDict();



    ASSERT_NE(a0Dict, nullptr);

    ASSERT_NE(a1Dict, nullptr);



    delete extGStateDict;

}



TEST_F(AnnotStampTopSecretTest_2012, GetTopSecretStampExtGStateDict_HasCorrectValuesInA0Dict_2012) {

    Dict* extGStateDict = getTopSecretStampExtGStateDict(mockPdfDoc);



    const Object& a0Obj = extGStateDict->lookupNF("a0");

    Dict* a0Dict = a0Obj.getDict();



    ASSERT_NE(a0Dict, nullptr);



    const Object& caObj = a0Dict->lookupNF("CA");

    const Object& caLowerObj = a0Dict->lookupNF("ca");



    EXPECT_TRUE(caObj.isNum());

    EXPECT_TRUE(caLowerObj.isNum());



    EXPECT_DOUBLE_EQ(caObj.getNum(), 0.588235);

    EXPECT_DOUBLE_EQ(caLowerObj.getNum(), 0.588235);



    delete extGStateDict;

}



TEST_F(AnnotStampTopSecretTest_2012, GetTopSecretStampExtGStateDict_HasCorrectValuesInA1Dict_2012) {

    Dict* extGStateDict = getTopSecretStampExtGStateDict(mockPdfDoc);



    const Object& a1Obj = extGStateDict->lookupNF("a1");

    Dict* a1Dict = a1Obj.getDict();



    ASSERT_NE(a1Dict, nullptr);



    const Object& caObj = a1Dict->lookupNF("CA");

    const Object& caLowerObj = a1Dict->lookupNF("ca");



    EXPECT_TRUE(caObj.isNum());

    EXPECT_TRUE(caLowerObj.isNum());



    EXPECT_DOUBLE_EQ(caObj.getNum(), 1);

    EXPECT_DOUBLE_EQ(caLowerObj.getNum(), 1);



    delete extGStateDict;

}



TEST_F(AnnotStampTopSecretTest_2012, GetTopSecretStampExtGStateDict_DoesNotModifyPdfDoc_2012) {

    Dict* initialCatalog = mockPdfDoc->getCatalog()->copy(mockXRef);

    Dict* extGStateDict = getTopSecretStampExtGStateDict(mockPdfDoc);



    Dict* finalCatalog = mockPdfDoc->getCatalog();



    EXPECT_EQ(*initialCatalog, *finalCatalog);



    delete extGStateDict;

    delete initialCatalog;

}
