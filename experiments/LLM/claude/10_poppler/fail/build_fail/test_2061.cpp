#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include "poppler-document.h"
#include "poppler-annot.h"
#include "poppler-page.h"
}

#include "poppler-private.h"

#include <memory>

class PopplerAnnotStampTest_2061 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Create a minimal PDF document for testing
        GError *error = nullptr;
        // We need a valid PopplerDocument; create one from a minimal PDF in memory
        const char *minimal_pdf =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        gsize len = strlen(minimal_pdf);
        GBytes *bytes = g_bytes_new_static(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        if (!doc) {
            // Try alternative approach
            // Write to a temp file and load
            char tmpfile[] = "/tmp/poppler_test_XXXXXX.pdf";
            int fd = mkstemps(tmpfile, 4);
            if (fd >= 0) {
                write(fd, minimal_pdf, len);
                close(fd);
                gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
                unlink(tmpfile);
            }
        }
        if (error) {
            g_error_free(error);
        }
        g_object_unref(stream);
        g_bytes_unref(bytes);
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that poppler_annot_stamp_new returns a non-null annotation with valid parameters
TEST_F(PopplerAnnotStampTest_2061, CreatesNonNullAnnot_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 200.0;
    rect.y2 = 200.0;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    g_object_unref(annot);
}

// Test that the returned annotation is of type STAMP
TEST_F(PopplerAnnotStampTest_2061, AnnotTypeIsStamp_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 50.0;
    rect.y1 = 50.0;
    rect.x2 = 150.0;
    rect.y2 = 150.0;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_STAMP);

    g_object_unref(annot);
}

// Test with zero-area rectangle
TEST_F(PopplerAnnotStampTest_2061, ZeroAreaRectangle_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 100.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    g_object_unref(annot);
}

// Test with negative coordinates
TEST_F(PopplerAnnotStampTest_2061, NegativeCoordinates_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -50.0;
    rect.x2 = 50.0;
    rect.y2 = 50.0;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    g_object_unref(annot);
}

// Test with large coordinates
TEST_F(PopplerAnnotStampTest_2061, LargeCoordinates_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 100000.0;
    rect.y2 = 100000.0;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    g_object_unref(annot);
}

// Test that the rectangle is preserved in the annotation
TEST_F(PopplerAnnotStampTest_2061, RectangleIsPreserved_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 300.0;
    rect.y2 = 400.0;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    PopplerRectangle out_rect;
    poppler_annot_get_rectangle(annot, &out_rect);

    EXPECT_DOUBLE_EQ(out_rect.x1, 10.0);
    EXPECT_DOUBLE_EQ(out_rect.y1, 20.0);
    EXPECT_DOUBLE_EQ(out_rect.x2, 300.0);
    EXPECT_DOUBLE_EQ(out_rect.y2, 400.0);

    g_object_unref(annot);
}

// Test with swapped coordinates (x1 > x2, y1 > y2)
TEST_F(PopplerAnnotStampTest_2061, SwappedCoordinates_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 200.0;
    rect.y1 = 200.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    g_object_unref(annot);
}

// Test creating multiple stamp annotations
TEST_F(PopplerAnnotStampTest_2061, MultipleAnnotations_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect1 = {10.0, 10.0, 50.0, 50.0};
    PopplerRectangle rect2 = {60.0, 60.0, 100.0, 100.0};

    PopplerAnnot *annot1 = poppler_annot_stamp_new(doc, &rect1);
    PopplerAnnot *annot2 = poppler_annot_stamp_new(doc, &rect2);

    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    EXPECT_NE(annot1, annot2);

    g_object_unref(annot1);
    g_object_unref(annot2);
}

// Test that the annotation is a GObject (can be ref/unref)
TEST_F(PopplerAnnotStampTest_2061, IsGObject_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect = {0.0, 0.0, 100.0, 100.0};

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(G_IS_OBJECT(annot));

    g_object_unref(annot);
}

// Test with fractional coordinates
TEST_F(PopplerAnnotStampTest_2061, FractionalCoordinates_2061) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 10.5;
    rect.y1 = 20.75;
    rect.x2 = 300.25;
    rect.y2 = 400.125;

    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
    ASSERT_NE(annot, nullptr);

    PopplerRectangle out_rect;
    poppler_annot_get_rectangle(annot, &out_rect);

    EXPECT_DOUBLE_EQ(out_rect.x1, 10.5);
    EXPECT_DOUBLE_EQ(out_rect.y1, 20.75);
    EXPECT_DOUBLE_EQ(out_rect.x2, 300.25);
    EXPECT_DOUBLE_EQ(out_rect.y2, 400.125);

    g_object_unref(annot);
}
