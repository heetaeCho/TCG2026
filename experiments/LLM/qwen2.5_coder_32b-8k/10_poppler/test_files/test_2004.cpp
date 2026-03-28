#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/poppler/annot_stamp_departmental.h"

}



class PDFDocMock : public PDFDoc {

public:

    MOCK_METHOD(XRef*, getXRef, (), (override));

};



TEST(getDepartmentalStampExtGStateDictTest_2004, NormalOperation_2004) {

    // Arrange

    PDFDocMock pdfDoc;

    XRef* mockXRef = new XRef();

    EXPECT_CALL(pdfDoc, getXRef()).WillRepeatedly(testing::Return(mockXRef));



    // Act

    Dict* extGStateDict = getDepartmentalStampExtGStateDict(&pdfDoc);



    // Assert

    ASSERT_NE(extGStateDict, nullptr);

    EXPECT_EQ(extGStateDict->getLength(), 2);



    const Object& a0Obj = extGStateDict->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());



    const Dict* a0Dict = a0Obj.getDict();

    ASSERT_NE(a0Dict, nullptr);

    EXPECT_EQ(a0Dict->getLength(), 2);

    EXPECT_DOUBLE_EQ(a0Dict->lookupNF("CA").getNum(), 0.588235);

    EXPECT_DOUBLE_EQ(a0Dict->lookupNF("ca").getNum(), 0.588235);



    const Object& a1Obj = extGStateDict->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());



    const Dict* a1Dict = a1Obj.getDict();

    ASSERT_NE(a1Dict, nullptr);

    EXPECT_EQ(a1Dict->getLength(), 2);

    EXPECT_DOUBLE_EQ(a1Dict->lookupNF("CA").getNum(), 1.0);

    EXPECT_DOUBLE_EQ(a1Dict->lookupNF("ca").getNum(), 1.0);



    delete extGStateDict;

    delete mockXRef;

}



TEST(getDepartmentalStampExtGStateDictTest_2004, XRefNullptrHandling_2004) {

    // Arrange

    PDFDocMock pdfDoc;

    EXPECT_CALL(pdfDoc, getXRef()).WillRepeatedly(testing::Return(nullptr));



    // Act & Assert

    EXPECT_THROW(getDepartmentalStampExtGStateDict(&pdfDoc), std::exception);

}



TEST(getDepartmentalStampExtGStateDictTest_2004, MemoryLeakCheck_2004) {

    // Arrange

    PDFDocMock pdfDoc;

    XRef* mockXRef = new XRef();

    EXPECT_CALL(pdfDoc, getXRef()).WillRepeatedly(testing::Return(mockXRef));



    // Act

    Dict* extGStateDict = getDepartmentalStampExtGStateDict(&pdfDoc);



    // Assert

    ASSERT_NE(extGStateDict, nullptr);

    delete extGStateDict;

    delete mockXRef;

}
