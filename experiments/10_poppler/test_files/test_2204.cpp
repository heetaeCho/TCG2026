#include <gtest/gtest.h>

#include "poppler-document.h"



// Mocking PopplerDocument structure for testing purposes

class MockPopplerDocument : public _PopplerDocument {

public:

    MOCK_METHOD(PopplerPDFPart, getPDFSubtypePart, (), (const));

};



TEST(PopplerDocumentTest_2204, GetPdfPartReturnsCorrectValueForValidDocument_2204) {

    MockPopplerDocument mockDoc;

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(testing::Return(POPPLER_PDF_SUBTYPE_PART_1));



    PopplerDocument* document = reinterpret_cast<PopplerDocument*>(&mockDoc);

    PopplerPDFPart result = poppler_document_get_pdf_part(document);



    EXPECT_EQ(result, POPPLER_PDF_SUBTYPE_PART_1);

}



TEST(PopplerDocumentTest_2204, GetPdfPartReturnsNoneForInvalidDocument_2204) {

    PopplerDocument* document = nullptr;

    PopplerPDFPart result = poppler_document_get_pdf_part(document);



    EXPECT_EQ(result, POPPLER_PDF_SUBTYPE_PART_NONE);

}



TEST(PopplerDocumentTest_2204, GetPdfPartBoundaryConditionsWithValidDocument_2204) {

    MockPopplerDocument mockDoc;

    EXPECT_CALL(mockDoc, getPDFSubtypePart()).WillOnce(testing::Return(POPPLER_PDF_SUBTYPE_PART_NONE));



    PopplerDocument* document = reinterpret_cast<PopplerDocument*>(&mockDoc);

    PopplerPDFPart result = poppler_document_get_pdf_part(document);



    EXPECT_EQ(result, POPPLER_PDF_SUBTYPE_PART_NONE);

}
