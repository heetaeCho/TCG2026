#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
#include "poppler.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "poppler-annot.h"

#include <cstring>
#include <cstdlib>

class PopplerAnnotLineNewTest_2054 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Create a minimal valid PDF document in memory for testing
        // We need a valid PopplerDocument to pass to poppler_annot_line_new
        GError *error = nullptr;

        // Try to create a document from a minimal PDF in memory
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
        GBytes *bytes = g_bytes_new(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

        if (error) {
            g_error_free(error);
            error = nullptr;
        }

        g_object_unref(stream);
        g_bytes_unref(bytes);

        // If stream-based creation failed, try data-based
        if (!doc) {
            doc = poppler_document_new_from_data((char *)minimal_pdf, (int)len, nullptr, &error);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

TEST_F(PopplerAnnotLineNewTest_2054, CreateLineAnnotReturnsNonNull_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 100.0;
    rect.y1 = 200.0;
    rect.x2 = 300.0;
    rect.y2 = 400.0;

    PopplerPoint start;
    start.x = 100.0;
    start.y = 200.0;

    PopplerPoint end;
    end.x = 300.0;
    end.y = 400.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, AnnotTypeIsLine_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 30.0;
    rect.y2 = 40.0;

    PopplerPoint start;
    start.x = 10.0;
    start.y = 20.0;

    PopplerPoint end;
    end.x = 30.0;
    end.y = 40.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    PopplerAnnotType type = poppler_annot_get_annot_type(annot);
    EXPECT_EQ(type, POPPLER_ANNOT_LINE);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, IsInstanceOfPopplerAnnotLine_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    PopplerPoint start;
    start.x = 0.0;
    start.y = 0.0;

    PopplerPoint end;
    end.x = 100.0;
    end.y = 100.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, ZeroSizeRect_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 0.0;
    rect.y2 = 0.0;

    PopplerPoint start;
    start.x = 0.0;
    start.y = 0.0;

    PopplerPoint end;
    end.x = 0.0;
    end.y = 0.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, NegativeCoordinates_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -50.0;
    rect.x2 = 50.0;
    rect.y2 = 50.0;

    PopplerPoint start;
    start.x = -50.0;
    start.y = -50.0;

    PopplerPoint end;
    end.x = 50.0;
    end.y = 50.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, LargeCoordinates_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 100000.0;
    rect.y2 = 100000.0;

    PopplerPoint start;
    start.x = 0.0;
    start.y = 0.0;

    PopplerPoint end;
    end.x = 100000.0;
    end.y = 100000.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, StartAndEndSamePoint_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    PopplerPoint start;
    start.x = 50.0;
    start.y = 50.0;

    PopplerPoint end;
    end.x = 50.0;
    end.y = 50.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, MultipleAnnotsIndependent_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect1;
    rect1.x1 = 10.0;
    rect1.y1 = 10.0;
    rect1.x2 = 50.0;
    rect1.y2 = 50.0;

    PopplerPoint start1, end1;
    start1.x = 10.0;
    start1.y = 10.0;
    end1.x = 50.0;
    end1.y = 50.0;

    PopplerRectangle rect2;
    rect2.x1 = 100.0;
    rect2.y1 = 100.0;
    rect2.x2 = 200.0;
    rect2.y2 = 200.0;

    PopplerPoint start2, end2;
    start2.x = 100.0;
    start2.y = 100.0;
    end2.x = 200.0;
    end2.y = 200.0;

    PopplerAnnot *annot1 = poppler_annot_line_new(doc, &rect1, &start1, &end1);
    PopplerAnnot *annot2 = poppler_annot_line_new(doc, &rect2, &start2, &end2);

    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    EXPECT_NE(annot1, annot2);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot1));
    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot2));

    g_object_unref(annot1);
    g_object_unref(annot2);
}

TEST_F(PopplerAnnotLineNewTest_2054, InvertedRectCoordinates_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    // x1 > x2, y1 > y2 (inverted rectangle)
    PopplerRectangle rect;
    rect.x1 = 300.0;
    rect.y1 = 400.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    PopplerPoint start;
    start.x = 300.0;
    start.y = 400.0;

    PopplerPoint end;
    end.x = 100.0;
    end.y = 200.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, IsAlsoPopplerAnnot_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 110.0;
    rect.y2 = 120.0;

    PopplerPoint start;
    start.x = 10.0;
    start.y = 20.0;

    PopplerPoint end;
    end.x = 110.0;
    end.y = 120.0;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    // It should also be a PopplerAnnot (base class)
    EXPECT_TRUE(POPPLER_IS_ANNOT(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotLineNewTest_2054, FractionalCoordinates_2054) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerRectangle rect;
    rect.x1 = 10.5;
    rect.y1 = 20.75;
    rect.x2 = 110.25;
    rect.y2 = 120.125;

    PopplerPoint start;
    start.x = 10.5;
    start.y = 20.75;

    PopplerPoint end;
    end.x = 110.25;
    end.y = 120.125;

    PopplerAnnot *annot = poppler_annot_line_new(doc, &rect, &start, &end);
    ASSERT_NE(annot, nullptr);

    EXPECT_TRUE(POPPLER_IS_ANNOT_LINE(annot));

    g_object_unref(annot);
}
