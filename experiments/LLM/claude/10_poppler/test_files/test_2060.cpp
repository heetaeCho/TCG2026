#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <memory>
#include <cstring>

// Internal headers needed for the function under test
#include "poppler-annot.h"
#include "poppler-private.h"
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PopplerAnnotStampNewTest_2060 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal PDF document in memory to get valid Annot objects
        const char *pdfContent =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

        GError *error = nullptr;
        gsize len = strlen(pdfContent);
        doc = poppler_document_new_from_data(pdfContent, len, nullptr, &error);
        if (error) {
            g_error_free(error);
            doc = nullptr;
        }
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument *doc = nullptr;
};

TEST_F(PopplerAnnotStampNewTest_2060, ReturnsNonNullForValidAnnot_2060) {
    // Create a stamp annotation using the public Poppler GLib API if possible,
    // or test through document page annotations
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    // Create a stamp annot via the public API
    PopplerRectangle rect = { 100.0, 100.0, 200.0, 200.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);

    ASSERT_NE(annot, nullptr);
    EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_STAMP);

    g_object_unref(annot);
    g_object_unref(page);
}

TEST_F(PopplerAnnotStampNewTest_2060, AnnotTypeIsStamp_2060) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect = { 0.0, 0.0, 100.0, 100.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);

    ASSERT_NE(annot, nullptr);
    EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_STAMP);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotStampNewTest_2060, IsGObjectType_2060) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect = { 10.0, 10.0, 50.0, 50.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);

    ASSERT_NE(annot, nullptr);
    EXPECT_TRUE(POPPLER_IS_ANNOT(annot));
    EXPECT_TRUE(POPPLER_IS_ANNOT_STAMP(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotStampNewTest_2060, BoundaryRectZeroSize_2060) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect = { 0.0, 0.0, 0.0, 0.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);

    ASSERT_NE(annot, nullptr);
    EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_STAMP);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotStampNewTest_2060, LargeRectangle_2060) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect = { 0.0, 0.0, 10000.0, 10000.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);

    ASSERT_NE(annot, nullptr);
    EXPECT_EQ(poppler_annot_get_annot_type(annot), POPPLER_ANNOT_STAMP);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotStampNewTest_2060, RefCountManagement_2060) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect = { 10.0, 10.0, 100.0, 100.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);

    ASSERT_NE(annot, nullptr);

    // Ref and unref should work properly as GObject
    g_object_ref(annot);
    g_object_unref(annot);
    
    // Should still be valid
    EXPECT_TRUE(POPPLER_IS_ANNOT_STAMP(annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotStampNewTest_2060, MultipleStampAnnotsIndependent_2060) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerRectangle rect1 = { 10.0, 10.0, 50.0, 50.0 };
    PopplerRectangle rect2 = { 60.0, 60.0, 100.0, 100.0 };

    PopplerAnnot *annot1 = poppler_annot_stamp_new(doc, &rect1);
    PopplerAnnot *annot2 = poppler_annot_stamp_new(doc, &rect2);

    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    EXPECT_NE(annot1, annot2);

    EXPECT_EQ(poppler_annot_get_annot_type(annot1), POPPLER_ANNOT_STAMP);
    EXPECT_EQ(poppler_annot_get_annot_type(annot2), POPPLER_ANNOT_STAMP);

    g_object_unref(annot1);
    g_object_unref(annot2);
}
