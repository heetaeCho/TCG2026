#include <gtest/gtest.h>

#include "poppler/annot_stamp_approved.h"

#include "poppler/PDFDoc.h"

#include "poppler/Dict.h"



using namespace std;



class ApprovedStampExtGStateDictTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock PDFDoc object

        xrefMock = new XRef();

        pdfDocMock = new PDFDoc(nullptr, nullopt, nullopt, nullptr);

        pdfDocMock->xref = xrefMock;

    }



    void TearDown() override {

        delete pdfDocMock;

        delete xrefMock;

    }



    XRef* xrefMock;

    PDFDoc* pdfDocMock;

};



TEST_F(ApprovedStampExtGStateDictTest, ReturnsNonNullPointer_2001) {

    Dict* result = getApprovedStampExtGStateDict(pdfDocMock);

    EXPECT_NE(result, nullptr);

}



TEST_F(ApprovedStampExtGStateDictTest, ContainsA0DictWithCorrectValues_2001) {

    Dict* result = getApprovedStampExtGStateDict(pdfDocMock);

    const Object& a0Object = result->lookupNF("a0");

    EXPECT_TRUE(a0Object.isDict());



    const Dict* a0Dict = a0Object.getDict();

    const Object& caA0Object = a0Dict->lookupNF("CA");

    const Object& caa0Object = a0Dict->lookupNF("ca");



    EXPECT_TRUE(caA0Object.isNum());

    EXPECT_TRUE(caa0Object.isNum());



    EXPECT_FLOAT_EQ(caA0Object.getNum(), 0.588235);

    EXPECT_FLOAT_EQ(caa0Object.getNum(), 0.588235);



    delete result;

}



TEST_F(ApprovedStampExtGStateDictTest, ContainsA1DictWithCorrectValues_2001) {

    Dict* result = getApprovedStampExtGStateDict(pdfDocMock);

    const Object& a1Object = result->lookupNF("a1");

    EXPECT_TRUE(a1Object.isDict());



    const Dict* a1Dict = a1Object.getDict();

    const Object& caA1Object = a1Dict->lookupNF("CA");

    const Object& caa1Object = a1Dict->lookupNF("ca");



    EXPECT_TRUE(caA1Object.isNum());

    EXPECT_TRUE(caa1Object.isNum());



    EXPECT_FLOAT_EQ(caA1Object.getNum(), 1.0);

    EXPECT_FLOAT_EQ(caa1Object.getNum(), 1.0);



    delete result;

}



TEST_F(ApprovedStampExtGStateDictTest, ContainsExactlyTwoEntries_2001) {

    Dict* result = getApprovedStampExtGStateDict(pdfDocMock);

    EXPECT_EQ(result->getLength(), 2);



    delete result;

}
