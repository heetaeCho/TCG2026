#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/annot_stamp_expired.h"

#include "poppler/PDFDoc.h"

#include "poppler/Dict.h"



using namespace testing;



class PDFDocMock : public PDFDoc {

public:

    MOCK_METHOD(XRef*, getXRef, (), (const, override));

};



TEST(getExpiredStampExtGStateDictTest_2008, NormalOperation_2008) {

    Mock<XRef> mockXRef;

    EXPECT_CALL(mockXRef, getXRef()).WillRepeatedly(Return(&mockXRef));



    PDFDocMock pdfDoc;

    ON_CALL(pdfDoc, getXRef()).WillByDefault(Return(&mockXRef));



    Dict* result = getExpiredStampExtGStateDict(&pdfDoc);

    ASSERT_NE(result, nullptr);



    const Object a0Obj = result->lookupNF("a0");

    ASSERT_TRUE(a0Obj.isDict());



    const Object caA0Obj = a0Obj.getDict()->lookupNF("CA");

    EXPECT_DOUBLE_EQ(caA0Obj.getNum(), 0.588235);

    

    const Object ca1A0Obj = a0Obj.getDict()->lookupNF("ca");

    EXPECT_DOUBLE_EQ(ca1A0Obj.getNum(), 0.588235);



    const Object a1Obj = result->lookupNF("a1");

    ASSERT_TRUE(a1Obj.isDict());



    const Object caA1Obj = a1Obj.getDict()->lookupNF("CA");

    EXPECT_DOUBLE_EQ(caA1Obj.getNum(), 1);

    

    const Object ca1A1Obj = a1Obj.getDict()->lookupNF("ca");

    EXPECT_DOUBLE_EQ(ca1A1Obj.getNum(), 1);



    delete result;

}



TEST(getExpiredStampExtGStateDictTest_2008, VerifyMemoryAllocation_2008) {

    Mock<XRef> mockXRef;

    EXPECT_CALL(mockXRef, getXRef()).WillRepeatedly(Return(&mockXRef));



    PDFDocMock pdfDoc;

    ON_CALL(pdfDoc, getXRef()).WillByDefault(Return(&mockXRef));



    int initialAllocations = _CrtMemCheckpoint(&s1);

    Dict* result = getExpiredStampExtGStateDict(&pdfDoc);



    _CrtMemState s2, s3;

    _CrtMemCheckpoint(&s2);



    delete result;



    _CrtMemCheckpoint(&s3);

    EXPECT_EQ(_CrtMemDifference(&s3, &s2, &s1), 0);

}



TEST(getExpiredStampExtGStateDictTest_2008, VerifyReturnNotNull_2008) {

    Mock<XRef> mockXRef;

    EXPECT_CALL(mockXRef, getXRef()).WillRepeatedly(Return(&mockXRef));



    PDFDocMock pdfDoc;

    ON_CALL(pdfDoc, getXRef()).WillByDefault(Return(&mockXRef));



    Dict* result = getExpiredStampExtGStateDict(&pdfDoc);

    ASSERT_NE(result, nullptr);



    delete result;

}



TEST(getExpiredStampExtGStateDictTest_2008, VerifySubDictEntries_2008) {

    Mock<XRef> mockXRef;

    EXPECT_CALL(mockXRef, getXRef()).WillRepeatedly(Return(&mockXRef));



    PDFDocMock pdfDoc;

    ON_CALL(pdfDoc, getXRef()).WillByDefault(Return(&mockXRef));



    Dict* result = getExpiredStampExtGStateDict(&pdfDoc);

    ASSERT_NE(result, nullptr);



    const Object a0Obj = result->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());



    const Object a1Obj = result->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());



    delete result;

}



TEST(getExpiredStampExtGStateDictTest_2008, VerifyExactValuesInSubDicts_2008) {

    Mock<XRef> mockXRef;

    EXPECT_CALL(mockXRef, getXRef()).WillRepeatedly(Return(&mockXRef));



    PDFDocMock pdfDoc;

    ON_CALL(pdfDoc, getXRef()).WillByDefault(Return(&mockXRef));



    Dict* result = getExpiredStampExtGStateDict(&pdfDoc);

    ASSERT_NE(result, nullptr);



    const Object a0Obj = result->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());



    const Object caA0Obj = a0Obj.getDict()->lookupNF("CA");

    EXPECT_DOUBLE_EQ(caA0Obj.getNum(), 0.588235);

    

    const Object ca1A0Obj = a0Obj.getDict()->lookupNF("ca");

    EXPECT_DOUBLE_EQ(ca1A0Obj.getNum(), 0.588235);



    const Object a1Obj = result->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());



    const Object caA1Obj = a1Obj.getDict()->lookupNF("CA");

    EXPECT_DOUBLE_EQ(caA1Obj.getNum(), 1);

    

    const Object ca1A1Obj = a1Obj.getDict()->lookupNF("ca");

    EXPECT_DOUBLE_EQ(ca1A1Obj.getNum(), 1);



    delete result;

}
