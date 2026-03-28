#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/utils/pdfinfo.cc"

#include "./TestProjects/poppler/poppler/PDFDoc.h"

#include "./TestProjects/poppler/poppler/UnicodeMap.h"

#include <memory>



using namespace testing;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(Object, getDocInfo, (), (const));

    MOCK_METHOD(PDFSubtype, getPDFSubtype, (), (const));

    MOCK_METHOD(PDFSubtypePart, getPDFSubtypePart, (), (const));

    MOCK_METHOD(PDFSubtypeConformance, getPDFSubtypeConformance, (), (const));

};



class MockUnicodeMap : public UnicodeMap {

public:

    using UnicodeMap::UnicodeMap;

    MOCK_METHOD(int, mapUnicode, (Unicode u, char * buf, int bufSize), (const override));

};



TEST_F(TestFixture_2673, printPdfSubtype_NullType_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(Object::null()));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypeNull));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_TRUE(output.empty());

}



TEST_F(TestFixture_2673, printPdfSubtype_NoneType_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(Object::null()));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypeNone));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_TRUE(output.empty());

}



TEST_F(TestFixture_2673, printPdfSubtype_PDFA_Type1_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    Object docInfo = Object::dict();

    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(docInfo));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypePDFA));

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(Return(subtypePart1));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_THAT(output, HasSubstr("Title: "));

}



TEST_F(TestFixture_2673, printPdfSubtype_PDFA_Type8_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    Object docInfo = Object::dict();

    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(docInfo));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypePDFA));

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(Return(subtypePart8));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_THAT(output, HasSubstr("Title: "));

}



TEST_F(TestFixture_2673, printPdfSubtype_PDFE_Type1_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    Object docInfo = Object::dict();

    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(docInfo));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypePDFE));

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(Return(subtypePart1));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_THAT(output, HasSubstr("Title: "));

}



TEST_F(TestFixture_2673, printPdfSubtype_PDFUA_Type1_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    Object docInfo = Object::dict();

    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(docInfo));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypePDFUA));

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(Return(subtypePart1));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_THAT(output, HasSubstr("Title: "));

}



TEST_F(TestFixture_2673, printPdfSubtype_PDFVT_Type1_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    Object docInfo = Object::dict();

    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(docInfo));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypePDFVT));

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(Return(subtypePart1));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_THAT(output, HasSubstr("Title: "));

}



TEST_F(TestFixture_2673, printPdfSubtype_PDFX_Type1_ConfA_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    Object docInfo = Object::dict();

    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(docInfo));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypePDFX));

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(Return(subtypePart1));

    EXPECT_CALL(mockDoc, getPDFSubtypeConformance()).WillOnce(Return(subtypeConfA));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_THAT(output, HasSubstr("Title: "));

}



TEST_F(TestFixture_2673, printPdfSubtype_PDFX_Type8_ConfU_2673) {

    MockPDFDoc mockDoc;

    MockUnicodeMap mockUnicodeMap("UTF-8", true);



    Object docInfo = Object::dict();

    EXPECT_CALL(mockDoc, getDocInfo()).WillOnce(Return(docInfo));

    EXPECT_CALL(mockDoc, getPDFSubtype()).WillRepeatedly(Return(subtypePDFX));

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(Return(subtypePart8));

    EXPECT_CALL(mockDoc, getPDFSubtypeConformance()).WillOnce(Return(subtypeConfU));



    testing::internal::CaptureStdout();

    printPdfSubtype(&mockDoc, &mockUnicodeMap);

    std::string output = testing::internal::GetCapturedStdout();



    ASSERT_THAT(output, HasSubstr("Title: "));

}
