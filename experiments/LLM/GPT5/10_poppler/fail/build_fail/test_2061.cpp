#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-private.h"
#include "poppler-page.h"
#include "PDFRectangle.h"

class MockPopplerDocument : public PopplerDocument {
public:
    MOCK_METHOD(PopplerDocument*, doc, (), (const));
};

class MockPopplerRectangle : public _PopplerRectangle {
public:
    MOCK_METHOD(int, x2, (), (const));
    MOCK_METHOD(int, y2, (), (const));
};

// TEST_ID 2061: Testing poppler_annot_stamp_new with a normal case
TEST_F(PopplerAnnotTest_2061, CreateAnnotStampWithValidRect_2061) {
    PopplerDocument doc;
    PopplerRectangle rect{0, 0, 100, 100};  // Valid rectangle
    PopplerAnnot* annot = poppler_annot_stamp_new(&doc, &rect);

    ASSERT_NE(annot, nullptr);  // Ensure annotation is created
    // Further assertions can be done based on the implementation, like checking if the pdf_rect was correctly passed or tested
}

// TEST_ID 2062: Testing poppler_annot_stamp_new with boundary conditions
TEST_F(PopplerAnnotTest_2062, CreateAnnotStampWithEmptyRect_2062) {
    PopplerDocument doc;
    PopplerRectangle rect{0, 0, 0, 0};  // Empty rectangle
    PopplerAnnot* annot = poppler_annot_stamp_new(&doc, &rect);

    ASSERT_NE(annot, nullptr);  // Annotation creation should still succeed, even for empty rectangle
}

// TEST_ID 2063: Testing poppler_annot_stamp_new with invalid rectangle (negative size)
TEST_F(PopplerAnnotTest_2063, CreateAnnotStampWithInvalidRect_2063) {
    PopplerDocument doc;
    PopplerRectangle rect{-10, -10, -5, -5};  // Invalid rectangle (negative size)
    PopplerAnnot* annot = poppler_annot_stamp_new(&doc, &rect);

    ASSERT_EQ(annot, nullptr);  // Expecting no annotation to be created due to invalid rectangle
}

// TEST_ID 2064: Verifying external interactions (mocking PopplerDocument)
TEST_F(PopplerAnnotTest_2064, CreateAnnotStampWithMockDocument_2064) {
    MockPopplerDocument mockDoc;
    PopplerRectangle rect{0, 0, 100, 100};  // Valid rectangle

    // Setting up the mock document to return a specific value for the doc() method
    EXPECT_CALL(mockDoc, doc()).WillOnce(testing::Return(&mockDoc));

    PopplerAnnot* annot = poppler_annot_stamp_new(&mockDoc, &rect);

    ASSERT_NE(annot, nullptr);  // Ensure annotation is created with the mocked document
}

// TEST_ID 2065: Testing poppler_annot_stamp_new with a nullptr document
TEST_F(PopplerAnnotTest_2065, CreateAnnotStampWithNullDocument_2065) {
    PopplerRectangle rect{0, 0, 100, 100};  // Valid rectangle
    PopplerAnnot* annot = poppler_annot_stamp_new(nullptr, &rect);

    ASSERT_EQ(annot, nullptr);  // Expecting no annotation to be created due to null document
}

// TEST_ID 2066: Boundary condition testing with large rectangle
TEST_F(PopplerAnnotTest_2066, CreateAnnotStampWithLargeRect_2066) {
    PopplerDocument doc;
    PopplerRectangle rect{0, 0, 1000000, 1000000};  // Large rectangle
    PopplerAnnot* annot = poppler_annot_stamp_new(&doc, &rect);

    ASSERT_NE(annot, nullptr);  // Ensure annotation is created with large rectangle
}

// TEST_ID 2067: Exceptional case with invalid input (null rectangle)
TEST_F(PopplerAnnotTest_2067, CreateAnnotStampWithNullRect_2067) {
    PopplerDocument doc;
    PopplerAnnot* annot = poppler_annot_stamp_new(&doc, nullptr);

    ASSERT_EQ(annot, nullptr);  // Expecting no annotation to be created due to null rectangle
}