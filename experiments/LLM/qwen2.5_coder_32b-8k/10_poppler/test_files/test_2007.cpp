#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/annot_stamp_experimental.h"

#include "TestProjects/poppler/poppler/PDFDoc.h"



class GetExperimentalStampExtGStateDictTest : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdf_doc;



    void SetUp() override {

        // Create a mock PDFDoc object or use a real one if possible

        pdf_doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::nullopt, std::nullopt, []{});

    }

};



TEST_F(GetExperimentalStampExtGStateDictTest_2007, ReturnsValidDictPointer_2007) {

    Dict* extGStateDict = getExperimentalStampExtGStateDict(pdf_doc.get());

    EXPECT_NE(extGStateDict, nullptr);

}



TEST_F(GetExperimentalStampExtGStateDictTest_2007, ContainsA0DictWithCorrectValues_2007) {

    Dict* extGStateDict = getExperimentalStampExtGStateDict(pdf_doc.get());

    const Object& a0Obj = extGStateDict->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());



    Dict* a0Dict = a0Obj.getDict();

    const Object& caA0Obj = a0Dict->lookupNF("CA");

    const Object& caA1Obj = a0Dict->lookupNF("ca");



    EXPECT_TRUE(caA0Obj.isNum());

    EXPECT_DOUBLE_EQ(caA0Obj.getNum(), 0.588235);

    EXPECT_TRUE(caA1Obj.isNum());

    EXPECT_DOUBLE_EQ(caA1Obj.getNum(), 0.588235);

}



TEST_F(GetExperimentalStampExtGStateDictTest_2007, ContainsA1DictWithCorrectValues_2007) {

    Dict* extGStateDict = getExperimentalStampExtGStateDict(pdf_doc.get());

    const Object& a1Obj = extGStateDict->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());



    Dict* a1Dict = a1Obj.getDict();

    const Object& caA0Obj = a1Dict->lookupNF("CA");

    const Object& caA1Obj = a1Dict->lookupNF("ca");



    EXPECT_TRUE(caA0Obj.isNum());

    EXPECT_DOUBLE_EQ(caA0Obj.getNum(), 1.0);

    EXPECT_TRUE(caA1Obj.isNum());

    EXPECT_DOUBLE_EQ(caA1Obj.getNum(), 1.0);

}



TEST_F(GetExperimentalStampExtGStateDictTest_2007, CorrectNumberOfKeysInRootDict_2007) {

    Dict* extGStateDict = getExperimentalStampExtGStateDict(pdf_doc.get());

    EXPECT_EQ(extGStateDict->getLength(), 2);

}



TEST_F(GetExperimentalStampExtGStateDictTest_2007, CorrectXRefReferenceUsed_2007) {

    XRef* xref = pdf_doc->getXRef();

    Dict* extGStateDict = getExperimentalStampExtGStateDict(pdf_doc.get());



    EXPECT_EQ(extGStateDict->getXRef(), xref);

}
