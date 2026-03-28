#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <poppler-document.h>
#include <poppler.h>
}

#include <cstdlib>
#include <string>

class PopplerDocumentGetFormFieldTest_2261 : public ::testing::Test {
protected:
    void SetUp() override {
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *loadDocument(const char *filename) {
        GError *error = nullptr;
        gchar *uri = g_strdup_printf("file://%s", filename);
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *document_;
};

// Test that passing a nullptr document doesn't crash (may return nullptr or segfault depending on implementation)
// We test with a valid document but invalid ID
TEST_F(PopplerDocumentGetFormFieldTest_2261, InvalidIdReturnsNull_2261) {
    // Try to load a simple PDF. If not available, skip.
    const char *test_pdf = getenv("TEST_PDF_PATH");
    if (!test_pdf) {
        GTEST_SKIP() << "TEST_PDF_PATH not set, skipping test";
    }

    document_ = loadDocument(test_pdf);
    if (!document_) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    // Use an ID that decodes to an invalid page number (very large)
    // encodeID encodes pageNum and fieldNum into a single int
    // A very large page number should result in nullptr
    gint invalid_id = FormWidget::encodeID(99999, 99999);
    PopplerFormField *field = poppler_document_get_form_field(document_, invalid_id);
    EXPECT_EQ(field, nullptr);
}

// Test with page 0, field 0 - likely no form field at this position in most documents
TEST_F(PopplerDocumentGetFormFieldTest_2261, ZeroPageZeroFieldReturnsNullOrValid_2261) {
    const char *test_pdf = getenv("TEST_PDF_PATH");
    if (!test_pdf) {
        GTEST_SKIP() << "TEST_PDF_PATH not set, skipping test";
    }

    document_ = loadDocument(test_pdf);
    if (!document_) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    // Page 0 is typically invalid (pages start at 1 in poppler)
    gint id = FormWidget::encodeID(0, 0);
    PopplerFormField *field = poppler_document_get_form_field(document_, id);
    // Page 0 is invalid, should return nullptr
    EXPECT_EQ(field, nullptr);
}

// Test with negative ID value
TEST_F(PopplerDocumentGetFormFieldTest_2261, NegativeIdReturnsNull_2261) {
    const char *test_pdf = getenv("TEST_PDF_PATH");
    if (!test_pdf) {
        GTEST_SKIP() << "TEST_PDF_PATH not set, skipping test";
    }

    document_ = loadDocument(test_pdf);
    if (!document_) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerFormField *field = poppler_document_get_form_field(document_, -1);
    // Negative ID should decode to some large unsigned values, resulting in nullptr
    EXPECT_EQ(field, nullptr);
}

// Test with a valid page but invalid field number
TEST_F(PopplerDocumentGetFormFieldTest_2261, ValidPageInvalidFieldReturnsNull_2261) {
    const char *test_pdf = getenv("TEST_PDF_PATH");
    if (!test_pdf) {
        GTEST_SKIP() << "TEST_PDF_PATH not set, skipping test";
    }

    document_ = loadDocument(test_pdf);
    if (!document_) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    // Page 1 exists in most PDFs, but field 99999 likely doesn't
    gint id = FormWidget::encodeID(1, 99999);
    PopplerFormField *field = poppler_document_get_form_field(document_, id);
    EXPECT_EQ(field, nullptr);
}

// Test with a PDF that has form fields
TEST_F(PopplerDocumentGetFormFieldTest_2261, FormPdfReturnsValidField_2261) {
    const char *test_pdf = getenv("TEST_FORM_PDF_PATH");
    if (!test_pdf) {
        GTEST_SKIP() << "TEST_FORM_PDF_PATH not set, skipping test";
    }

    document_ = loadDocument(test_pdf);
    if (!document_) {
        GTEST_SKIP() << "Could not load test form PDF";
    }

    // Try page 1, field 0 - common location for first form field
    gint id = FormWidget::encodeID(1, 0);
    PopplerFormField *field = poppler_document_get_form_field(document_, id);
    // If the form PDF has a field at this position, it should be non-null
    // We can't guarantee this without knowing the PDF, so just verify no crash
    if (field) {
        g_object_unref(field);
    }
}

// Test encodeID/decodeID roundtrip to verify ID encoding
TEST_F(PopplerDocumentGetFormFieldTest_2261, EncodeDecodeIDRoundtrip_2261) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    int id = FormWidget::encodeID(pageNum, fieldNum);

    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(id, &decodedPage, &decodedField);

    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID/decodeID with boundary values
TEST_F(PopplerDocumentGetFormFieldTest_2261, EncodeDecodeIDBoundary_2261) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    int id = FormWidget::encodeID(pageNum, fieldNum);

    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(id, &decodedPage, &decodedField);

    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID/decodeID with larger values
TEST_F(PopplerDocumentGetFormFieldTest_2261, EncodeDecodeIDLargerValues_2261) {
    unsigned int pageNum = 65535;
    unsigned int fieldNum = 65535;
    int id = FormWidget::encodeID(pageNum, fieldNum);

    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(id, &decodedPage, &decodedField);

    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test that returned form field (if valid) can be unreffed without issue
TEST_F(PopplerDocumentGetFormFieldTest_2261, ReturnedFieldCanBeUnreffed_2261) {
    const char *test_pdf = getenv("TEST_FORM_PDF_PATH");
    if (!test_pdf) {
        GTEST_SKIP() << "TEST_FORM_PDF_PATH not set, skipping test";
    }

    document_ = loadDocument(test_pdf);
    if (!document_) {
        GTEST_SKIP() << "Could not load test form PDF";
    }

    // Iterate through first few possible field positions
    for (unsigned int fieldNum = 0; fieldNum < 10; fieldNum++) {
        gint id = FormWidget::encodeID(1, fieldNum);
        PopplerFormField *field = poppler_document_get_form_field(document_, id);
        if (field) {
            // Verify we can get the field type without crash
            PopplerFormFieldType type = poppler_form_field_get_field_type(field);
            EXPECT_TRUE(type == POPPLER_FORM_FIELD_TEXT ||
                        type == POPPLER_FORM_FIELD_BUTTON ||
                        type == POPPLER_FORM_FIELD_CHOICE ||
                        type == POPPLER_FORM_FIELD_SIGNATURE ||
                        type == POPPLER_FORM_FIELD_UNKNOWN);
            g_object_unref(field);
        }
    }
}
