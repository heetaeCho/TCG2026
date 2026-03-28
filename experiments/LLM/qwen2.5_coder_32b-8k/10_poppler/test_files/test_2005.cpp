#include <gtest/gtest.h>

#include "poppler/annot_stamp_final.h"

#include "poppler/PDFDoc.h"

#include "poppler/Dict.h"



// Mock class for XRef to satisfy the Dict constructor requirement.

class MockXRef : public XRef {

public:

    MOCK_METHOD(int, incRef, (), (override));

    MOCK_METHOD(int, decRef, (), (override));

};



// Test fixture for getFinalStampExtGStateDict

class GetFinalStampExtGStateDictTest_2005 : public ::testing::Test {

protected:

    void SetUp() override {

        xref = new MockXRef();

        pdfDoc = new PDFDoc(nullptr, std::nullopt, std::nullopt, [](){});

        pdfDoc->setXRef(xref);

    }



    void TearDown() override {

        delete pdfDoc;

        delete xref;

    }



    MockXRef* xref;

    PDFDoc* pdfDoc;

};



TEST_F(GetFinalStampExtGStateDictTest_2005, ReturnsNonNullPtr_2005) {

    Dict *result = getFinalStampExtGStateDict(pdfDoc);

    EXPECT_NE(result, nullptr);

}



TEST_F(GetFinalStampExtGStateDictTest_2005, ContainsA0KeyWithCorrectValues_2005) {

    Dict *result = getFinalStampExtGStateDict(pdfDoc);

    const Object& a0Obj = result->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());

    

    const Dict* a0Dict = a0Obj.getDict();

    const Object& caObj = a0Dict->lookupNF("CA");

    const Object& caValue = caObj.getNum();

    EXPECT_EQ(caValue, 0.588235);



    const Object& caAlphaObj = a0Dict->lookupNF("ca");

    const Object& caAlphaValue = caAlphaObj.getNum();

    EXPECT_EQ(caAlphaValue, 0.588235);

}



TEST_F(GetFinalStampExtGStateDictTest_2005, ContainsA1KeyWithCorrectValues_2005) {

    Dict *result = getFinalStampExtGStateDict(pdfDoc);

    const Object& a1Obj = result->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());

    

    const Dict* a1Dict = a1Obj.getDict();

    const Object& caObj = a1Dict->lookupNF("CA");

    const Object& caValue = caObj.getNum();

    EXPECT_EQ(caValue, 1);



    const Object& caAlphaObj = a1Dict->lookupNF("ca");

    const Object& caAlphaValue = caAlphaObj.getNum();

    EXPECT_EQ(caAlphaValue, 1);

}



TEST_F(GetFinalStampExtGStateDictTest_2005, A0AndA1AreDistinctObjects_2005) {

    Dict *result = getFinalStampExtGStateDict(pdfDoc);

    const Object& a0Obj = result->lookupNF("a0");

    const Object& a1Obj = result->lookupNF("a1");

    EXPECT_NE(a0Obj.getDict(), a1Obj.getDict());

}



TEST_F(GetFinalStampExtGStateDictTest_2005, CorrectNumberOfEntriesInRootDict_2005) {

    Dict *result = getFinalStampExtGStateDict(pdfDoc);

    EXPECT_EQ(result->getLength(), 2);

}
