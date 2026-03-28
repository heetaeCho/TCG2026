#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-private.h"
#include "poppler-page.h"

#include <memory>
#include <cstring>

class PopplerAnnotCircleNewTest_2056 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    PopplerDocument *createTestDocument(const char *uri) {
        GError *error = nullptr;
        // Create a simple PDF document for testing
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Test that creating a circle annotation with valid parameters returns non-null
TEST_F(PopplerAnnotCircleNewTest_2056, ValidParamsReturnsNonNull_2056) {
    // We need a valid document - create a minimal one from a data buffer
    // Use a minimal PDF in memory
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, &error);

    if (doc == nullptr) {
        // If we can't create a doc from stream, try from data
        if (error) g_error_free(error);
        error = nullptr;
        doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
    }

    if (doc != nullptr) {
        PopplerRectangle rect;
        rect.x1 = 100.0;
        rect.y1 = 100.0;
        rect.x2 = 200.0;
        rect.y2 = 200.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);
        ASSERT_NE(annot, nullptr);

        // Verify it's a circle annotation
        PopplerAnnotType type = poppler_annot_get_annot_type(annot);
        EXPECT_EQ(type, POPPLER_ANNOT_CIRCLE);

        g_object_unref(annot);
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with zero-area rectangle (boundary condition)
TEST_F(PopplerAnnotCircleNewTest_2056, ZeroAreaRectangle_2056) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        error = nullptr;
        doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
    }

    if (doc != nullptr) {
        PopplerRectangle rect;
        rect.x1 = 0.0;
        rect.y1 = 0.0;
        rect.x2 = 0.0;
        rect.y2 = 0.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);
        ASSERT_NE(annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(annot);
        EXPECT_EQ(type, POPPLER_ANNOT_CIRCLE);

        g_object_unref(annot);
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with negative coordinates
TEST_F(PopplerAnnotCircleNewTest_2056, NegativeCoordinates_2056) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        error = nullptr;
        doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
    }

    if (doc != nullptr) {
        PopplerRectangle rect;
        rect.x1 = -50.0;
        rect.y1 = -50.0;
        rect.x2 = 50.0;
        rect.y2 = 50.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);
        ASSERT_NE(annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(annot);
        EXPECT_EQ(type, POPPLER_ANNOT_CIRCLE);

        g_object_unref(annot);
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with large coordinates
TEST_F(PopplerAnnotCircleNewTest_2056, LargeCoordinates_2056) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        error = nullptr;
        doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
    }

    if (doc != nullptr) {
        PopplerRectangle rect;
        rect.x1 = 0.0;
        rect.y1 = 0.0;
        rect.x2 = 100000.0;
        rect.y2 = 100000.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);
        ASSERT_NE(annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(annot);
        EXPECT_EQ(type, POPPLER_ANNOT_CIRCLE);

        g_object_unref(annot);
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that the annotation preserves rectangle coordinates
TEST_F(PopplerAnnotCircleNewTest_2056, RectanglePreserved_2056) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        error = nullptr;
        doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
    }

    if (doc != nullptr) {
        PopplerRectangle rect;
        rect.x1 = 10.0;
        rect.y1 = 20.0;
        rect.x2 = 300.0;
        rect.y2 = 400.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);
        ASSERT_NE(annot, nullptr);

        // Verify the annotation type
        EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_CIRCLE);

        // Try to get the rectangle back
        PopplerRectangle out_rect;
        poppler_annot_get_rectangle(annot, &out_rect);
        EXPECT_DOUBLE_EQ(out_rect.x1, 10.0);
        EXPECT_DOUBLE_EQ(out_rect.y1, 20.0);
        EXPECT_DOUBLE_EQ(out_rect.x2, 300.0);
        EXPECT_DOUBLE_EQ(out_rect.y2, 400.0);

        g_object_unref(annot);
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with inverted rectangle (x1 > x2, y1 > y2)
TEST_F(PopplerAnnotCircleNewTest_2056, InvertedRectangle_2056) {
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj<</Pages 2 0 R/Type/Catalog>>endobj\n"
        "2 0 obj<</Count 1/Kids[3 0 R]/Type/Pages>>endobj\n"
        "3 0 obj<</MediaBox[0 0 612 792]/Parent 2 0 R/Type/Page>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Root 1 0 R/Size 4>>\nstartxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        error = nullptr;
        doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
    }

    if (doc != nullptr) {
        PopplerRectangle rect;
        rect.x1 = 200.0;
        rect.y1 = 200.0;
        rect.x2 = 100.0;
        rect.y2 = 100.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc, &rect);
        ASSERT_NE(annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(annot);
        EXPECT_EQ(type, POPPLER_ANNOT_CIRCLE);

        g_object_unref(annot);
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test document";
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
