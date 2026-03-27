#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "annot_stamp_sold.h"

#include "Dict.h"

#include "PDFDoc.h"



class GetSoldStampExtGStateDictTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockPDFDoc = new PDFDoc();

        EXPECT_CALL(*mockPDFDoc, getXRef()).WillRepeatedly(::testing::Return(&xrefMock));

        doc.reset(mockPDFDoc);

    }



    void TearDown() override {

        delete mockPDFDoc;

    }



    std::unique_ptr<PDFDoc> doc;

    PDFDoc* mockPDFDoc;

    XRef xrefMock;

};



TEST_F(GetSoldStampExtGStateDictTest, ReturnsNonNullPtr_2011) {

    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());

    EXPECT_NE(extGStateDict, nullptr);

}



TEST_F(GetSoldStampExtGStateDictTest, CorrectSubDictsAdded_2011) {

    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());



    EXPECT_TRUE(extGStateDict->hasKey("a0"));

    EXPECT_TRUE(extGStateDict->hasKey("a1"));



    const Object a0Obj = extGStateDict->lookupNF("a0");

    const Object a1Obj = extGStateDict->lookupNF("a1");



    EXPECT_EQ(a0Obj.getType(), objDict);

    EXPECT_EQ(a1Obj.getType(), objDict);



    const Dict *a0Dict = a0Obj.getDict();

    const Dict *a1Dict = a1Obj.getDict();



    EXPECT_TRUE(a0Dict->hasKey("CA"));

    EXPECT_TRUE(a0Dict->hasKey("ca"));



    EXPECT_TRUE(a1Dict->hasKey("CA"));

    EXPECT_TRUE(a1Dict->hasKey("ca"));

}



TEST_F(GetSoldStampExtGStateDictTest, CorrectValuesAddedToSubDicts_2011) {

    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());



    const Object a0Obj = extGStateDict->lookupNF("a0");

    const Object a1Obj = extGStateDict->lookupNF("a1");



    const Dict *a0Dict = a0Obj.getDict();

    const Dict *a1Dict = a1Obj.getDict();



    const Object caA0Obj = a0Dict->lookupNF("CA");

    const Object caA1Obj = a1Dict->lookupNF("CA");



    EXPECT_EQ(caA0Obj.getNum(), 0.588235);

    EXPECT_EQ(caA1Obj.getNum(), 1);



    const Object caa0Obj = a0Dict->lookupNF("ca");

    const Object caa1Obj = a1Dict->lookupNF("ca");



    EXPECT_EQ(caa0Obj.getNum(), 0.588235);

    EXPECT_EQ(caa1Obj.getNum(), 1);

}



TEST_F(GetSoldStampExtGStateDictTest, CorrectNumberOfEntriesInSubDicts_2011) {

    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());



    const Object a0Obj = extGStateDict->lookupNF("a0");

    const Object a1Obj = extGStateDict->lookupNF("a1");



    const Dict *a0Dict = a0Obj.getDict();

    const Dict *a1Dict = a1Obj.getDict();



    EXPECT_EQ(a0Dict->getLength(), 2);

    EXPECT_EQ(a1Dict->getLength(), 2);

}



TEST_F(GetSoldStampExtGStateDictTest, CorrectNumberOfEntriesInMainDict_2011) {

    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());



    EXPECT_EQ(extGStateDict->getLength(), 2);

}
