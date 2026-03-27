#include <gtest/gtest.h>

#include "poppler-document.h"

#include "gmock/gmock.h"



using namespace testing;



// Mock class for PopplerDocument to simulate external collaborators if needed.

class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD(void, getPDFMajorVersion, (), (const));

    MOCK_METHOD(void, getPDFMinorVersion, (), (const));

};



TEST_F(PopplerDocumentTest_2171, GetPdfVersion_NormalOperation_2171) {

    MockPopplerDocument mockDoc;

    guint major_version = 0;

    guint minor_version = 0;



    EXPECT_CALL(mockDoc, getPDFMajorVersion()).WillOnce(Return(1));

    EXPECT_CALL(mockDoc, getPDFMinorVersion()).WillOnce(Return(7));



    poppler_document_get_pdf_version(&mockDoc, &major_version, &minor_version);



    EXPECT_EQ(major_version, 1);

    EXPECT_EQ(minor_version, 7);

}



TEST_F(PopplerDocumentTest_2171, GetPdfVersion_NullMajorVersion_2171) {

    MockPopplerDocument mockDoc;

    guint minor_version = 0;



    EXPECT_CALL(mockDoc, getPDFMinorVersion()).WillOnce(Return(7));



    poppler_document_get_pdf_version(&mockDoc, nullptr, &minor_version);



    EXPECT_EQ(minor_version, 7);

}



TEST_F(PopplerDocumentTest_2171, GetPdfVersion_NullMinorVersion_2171) {

    MockPopplerDocument mockDoc;

    guint major_version = 0;



    EXPECT_CALL(mockDoc, getPDFMajorVersion()).WillOnce(Return(1));



    poppler_document_get_pdf_version(&mockDoc, &major_version, nullptr);



    EXPECT_EQ(major_version, 1);

}



TEST_F(PopplerDocumentTest_2171, GetPdfVersion_NullBothVersions_2171) {

    MockPopplerDocument mockDoc;



    poppler_document_get_pdf_version(&mockDoc, nullptr, nullptr);



    // No expectations since both pointers are null.

}
