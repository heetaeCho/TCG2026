#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pdfseparate.cc"

#include "PDFDoc.h"

#include "Error.h"



using namespace testing;



class PDFDocMock : public PDFDoc {

public:

    MOCK_METHOD(bool, isOk, (), (const));

    MOCK_METHOD(int, getNumPages, (), ());

    MOCK_METHOD(int, savePageAs, (const std::string &, int), ());

};



TEST_F(PDFDocTest_2736, ExtractPages_ValidSinglePage_2736) {

    PDFDocMock mockDoc;

    EXPECT_CALL(mockDoc, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(mockDoc, savePageAs(_, 1)).WillOnce(Return(errNone));



    firstPage = 1;

    lastPage = 1;



    bool result = extractPages("input.pdf", "output%d.png");

    EXPECT_TRUE(result);

}



TEST_F(PDFDocTest_2736, ExtractPages_ValidMultiplePages_2736) {

    PDFDocMock mockDoc;

    EXPECT_CALL(mockDoc, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, getNumPages()).WillRepeatedly(Return(5));

    EXPECT_CALL(mockDoc, savePageAs(_, 1)).WillOnce(Return(errNone));

    EXPECT_CALL(mockDoc, savePageAs(_, 2)).WillOnce(Return(errNone));

    EXPECT_CALL(mockDoc, savePageAs(_, 3)).WillOnce(Return(errNone));

    EXPECT_CALL(mockDoc, savePageAs(_, 4)).WillOnce(Return(errNone));

    EXPECT_CALL(mockDoc, savePageAs(_, 5)).WillOnce(Return(errNone));



    firstPage = 1;

    lastPage = 5;



    bool result = extractPages("input.pdf", "output%d.png");

    EXPECT_TRUE(result);

}



TEST_F(PDFDocTest_2736, ExtractPages_DamagedFile_2736) {

    PDFDocMock mockDoc;

    EXPECT_CALL(mockDoc, isOk()).WillOnce(Return(false));



    firstPage = 1;

    lastPage = 1;



    bool result = extractPages("input.pdf", "output%d.png");

    EXPECT_FALSE(result);

}



TEST_F(PDFDocTest_2736, ExtractPages_WrongPageRange_2736) {

    PDFDocMock mockDoc;

    EXPECT_CALL(mockDoc, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, getNumPages()).WillRepeatedly(Return(5));



    firstPage = 5;

    lastPage = 1;



    bool result = extractPages("input.pdf", "output%d.png");

    EXPECT_FALSE(result);

}



TEST_F(PDFDocTest_2736, ExtractPages_MissingPatternInDestFileName_2736) {

    PDFDocMock mockDoc;

    EXPECT_CALL(mockDoc, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, getNumPages()).WillRepeatedly(Return(5));



    firstPage = 1;

    lastPage = 2;



    bool result = extractPages("input.pdf", "output.png");

    EXPECT_FALSE(result);

}



TEST_F(PDFDocTest_2736, ExtractPages_MultiplePatternsInDestFileName_2736) {

    PDFDocMock mockDoc;

    EXPECT_CALL(mockDoc, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, getNumPages()).WillRepeatedly(Return(5));



    firstPage = 1;

    lastPage = 2;



    bool result = extractPages("input.pdf", "output%d%d.png");

    EXPECT_FALSE(result);

}



TEST_F(PDFDocTest_2736, ExtractPages_ErrorSavingPage_2736) {

    PDFDocMock mockDoc;

    EXPECT_CALL(mockDoc, isOk()).WillOnce(Return(true));

    EXPECT_CALL(mockDoc, getNumPages()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockDoc, savePageAs(_, 1)).WillOnce(Return(errSyntaxError));



    firstPage = 1;

    lastPage = 1;



    bool result = extractPages("input.pdf", "output%d.png");

    EXPECT_FALSE(result);

}
