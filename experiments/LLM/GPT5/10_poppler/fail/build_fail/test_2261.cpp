// poppler_document_get_form_field_test_2261.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "poppler.h"
}

#include "poppler-document.h"

// We treat poppler_document_get_form_field as a black box and
// only validate observable behavior via the public API.

class PopplerDocumentGetFormFieldTest_2261 : public ::testing::Test {
protected:
    void SetUp() override {
        // Load a valid PDF document with known form fields.
        // The actual test environment is expected to provide
        // a test PDF with at least one form field.
        GError *error = nullptr;
        document = poppler_document_new_from_file("file://test_form.pdf", nullptr, &error);
        ASSERT_NE(document, nullptr);
        ASSERT_EQ(error, nullptr);
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }

    PopplerDocument *document = nullptr;
};

// Normal operation: valid form field ID should return non-null field
TEST_F(PopplerDocumentGetFormFieldTest_2261, ValidFormFieldReturnsField_2261) {
    // Assume page 0, field 0 exists in test PDF
    int encodedId = FormWidget::encodeID(0, 0);

    PopplerFormField *field = poppler_document_get_form_field(document, encodedId);

    EXPECT_NE(field, nullptr);

    if (field) {
        g_object_unref(field);
    }
}

// Boundary condition: very large ID that likely maps to non-existent page
TEST_F(PopplerDocumentGetFormFieldTest_2261, NonExistentPageReturnsNull_2261) {
    int encodedId = FormWidget::encodeID(9999, 0);

    PopplerFormField *field = poppler_document_get_form_field(document, encodedId);

    EXPECT_EQ(field, nullptr);
}

// Boundary condition: valid page but invalid field index
TEST_F(PopplerDocumentGetFormFieldTest_2261, NonExistentFieldReturnsNull_2261) {
    // Assume page 0 exists but field index is invalid
    int encodedId = FormWidget::encodeID(0, 9999);

    PopplerFormField *field = poppler_document_get_form_field(document, encodedId);

    EXPECT_EQ(field, nullptr);
}

// Exceptional case: null document pointer
TEST(PopplerDocumentGetFormFieldEdgeTest_2261, NullDocumentReturnsNull_2261) {
    int encodedId = FormWidget::encodeID(0, 0);

    PopplerFormField *field = poppler_document_get_form_field(nullptr, encodedId);

    EXPECT_EQ(field, nullptr);
}

// Boundary case: negative ID (treated as large unsigned when decoded)
TEST_F(PopplerDocumentGetFormFieldTest_2261, NegativeIdReturnsNull_2261) {
    int encodedId = -1;

    PopplerFormField *field = poppler_document_get_form_field(document, encodedId);

    EXPECT_EQ(field, nullptr);
}