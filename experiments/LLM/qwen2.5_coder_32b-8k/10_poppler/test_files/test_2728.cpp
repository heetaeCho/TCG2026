#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pdftotext.cc"

#include "PDFDoc.h"

#include "TextOutputDev.h"



using namespace testing;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(int, getNumPages, (), (override));

    MOCK_METHOD(Page*, getPage, (int page), (override));

    MOCK_METHOD(double, getPageMediaWidth, (int page), (const, override));

    MOCK_METHOD(double, getPageMediaHeight, (int page), (const, override));

    MOCK_METHOD(double, getPageCropWidth, (int page), (const, override));

    MOCK_METHOD(double, getPageCropHeight, (int page), (const, override));

    MOCK_METHOD(void, displayPage, (OutputDev* out, int page, double hDPI, double vDPI, int rotate, bool useMediaBox, bool crop, bool printing), (override));

};



class MockTextOutputDev : public TextOutputDev {

public:

    MOCK_METHOD(std::unique_ptr<TextWordList>, makeWordList, (), (override));

};



TEST_F(TestFixture_2728, PrintWordBBox_NormalOperation_2728) {

    MockPDFDoc mockPdfDoc;

    MockTextOutputDev mockTextOutputDev;



    EXPECT_CALL(mockPdfDoc, getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(mockPdfDoc, getPageMediaWidth(1)).WillOnce(Return(595.0));

    EXPECT_CALL(mockPdfDoc, getPageMediaHeight(1)).WillOnce(Return(842.0));

    EXPECT_CALL(mockTextOutputDev, makeWordList())

        .WillOnce(Return(ByMove(std::make_unique<TextWordList>(nullptr, false))));



    ::testing::internal::CaptureStdout();

    printWordBBox(stdout, &mockPdfDoc, &mockTextOutputDev, 1, 1);

    std::string output = ::testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "<doc>\n <page width=\"595\" height=\"842\">\n no word list\n </page>\n</doc>\n");

}



TEST_F(TestFixture_2728, PrintWordBBox_BoundaryConditions_SinglePage_2728) {

    MockPDFDoc mockPdfDoc;

    MockTextOutputDev mockTextOutputDev;



    EXPECT_CALL(mockPdfDoc, getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(mockPdfDoc, getPageMediaWidth(1)).WillOnce(Return(595.0));

    EXPECT_CALL(mockPdfDoc, getPageMediaHeight(1)).WillOnce(Return(842.0));

    EXPECT_CALL(mockTextOutputDev, makeWordList())

        .WillOnce(Return(ByMove(std::make_unique<TextWordList>(nullptr, false))));



    ::testing::internal::CaptureStdout();

    printWordBBox(stdout, &mockPdfDoc, &mockTextOutputDev, 1, 1);

    std::string output = ::testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "<doc>\n <page width=\"595\" height=\"842\">\n no word list\n </page>\n</doc>\n");

}



TEST_F(TestFixture_2728, PrintWordBBox_BoundaryConditions_MultiplePages_2728) {

    MockPDFDoc mockPdfDoc;

    MockTextOutputDev mockTextOutputDev;



    EXPECT_CALL(mockPdfDoc, getNumPages()).WillOnce(Return(3));

    EXPECT_CALL(mockPdfDoc, getPageMediaWidth(1)).WillOnce(Return(595.0));

    EXPECT_CALL(mockPdfDoc, getPageMediaHeight(1)).WillOnce(Return(842.0));

    EXPECT_CALL(mockTextOutputDev, makeWordList())

        .WillOnce(Return(ByMove(std::make_unique<TextWordList>(nullptr, false))));

    EXPECT_CALL(mockPdfDoc, getPageMediaWidth(2)).WillOnce(Return(595.0));

    EXPECT_CALL(mockPdfDoc, getPageMediaHeight(2)).WillOnce(Return(842.0));

    EXPECT_CALL(mockTextOutputDev, makeWordList())

        .WillOnce(Return(ByMove(std::make_unique<TextWordList>(nullptr, false))));

    EXPECT_CALL(mockPdfDoc, getPageMediaWidth(3)).WillOnce(Return(595.0));

    EXPECT_CALL(mockPdfDoc, getPageMediaHeight(3)).WillOnce(Return(842.0));

    EXPECT_CALL(mockTextOutputDev, makeWordList())

        .WillOnce(Return(ByMove(std::make_unique<TextWordList>(nullptr, false))));



    ::testing::internal::CaptureStdout();

    printWordBBox(stdout, &mockPdfDoc, &mockTextOutputDev, 1, 3);

    std::string output = ::testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "<doc>\n <page width=\"595\" height=\"842\">\n no word list\n </page>\n <page width=\"595\" height=\"842\">\n no word list\n </page>\n <page width=\"595\" height=\"842\">\n no word list\n </page>\n</doc>\n");

}



TEST_F(TestFixture_2728, PrintWordBBox_Exceptional_NoPages_2728) {

    MockPDFDoc mockPdfDoc;

    MockTextOutputDev mockTextOutputDev;



    EXPECT_CALL(mockPdfDoc, getNumPages()).WillOnce(Return(0));



    ::testing::internal::CaptureStdout();

    printWordBBox(stdout, &mockPdfDoc, &mockTextOutputDev, 1, 1);

    std::string output = ::testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "<doc>\n</doc>\n");

}



TEST_F(TestFixture_2728, PrintWordBBox_Exceptional_PageNotFound_2728) {

    MockPDFDoc mockPdfDoc;

    MockTextOutputDev mockTextOutputDev;



    EXPECT_CALL(mockPdfDoc, getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(mockPdfDoc, getPageMediaWidth(2)).WillOnce(Return(595.0));

    EXPECT_CALL(mockPdfDoc, getPageMediaHeight(2)).WillOnce(Return(842.0));



    ::testing::internal::CaptureStdout();

    printWordBBox(stdout, &mockPdfDoc, &mockTextOutputDev, 2, 2);

    std::string output = ::testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "<doc>\n</doc>\n");

}
