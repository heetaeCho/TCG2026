#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Poppler headers
#include "poppler-annot.h"
#include "poppler-private.h"
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// GLib/GObject headers
#include <glib-object.h>

class PopplerAnnotFreeTextTest_2044 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize global params if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF buffer that contains a free text annotation
    std::unique_ptr<PDFDoc> createDocWithFreeTextAnnot() {
        // We need a real PDF document with a free text annotation
        // This is a minimal PDF with a FreeText annotation
        static const char *minimalPdf =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /AcroForm << /DR << /Font << /Helv 5 0 R >> >> >> >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
            "   /Annots [4 0 R] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Annot /Subtype /FreeText /Rect [100 100 300 200]\n"
            "   /DA (/Helv 12 Tf 0 0 0 rg) /Contents (Test) >>\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000115 00000 n \n"
            "0000000172 00000 n \n"
            "0000000274 00000 n \n"
            "0000000415 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "492\n"
            "%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

// Test that creating a free text annotation from a valid annotation returns non-null
TEST_F(PopplerAnnotFreeTextTest_2044, CreatesNonNullAnnot_2044) {
    auto doc = createDocWithFreeTextAnnot();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);
    ASSERT_GT(annots->getNumAnnots(), 0);

    std::shared_ptr<Annot> annot(annots->getAnnot(0));
    // Only proceed if it's actually a FreeText annotation
    if (annot->getType() == Annot::typeFreeText) {
        PopplerAnnot *poppler_annot = _poppler_annot_free_text_new(annot);
        ASSERT_NE(poppler_annot, nullptr);

        // Verify it's the correct type
        EXPECT_TRUE(POPPLER_IS_ANNOT_FREE_TEXT(poppler_annot));

        g_object_unref(poppler_annot);
    }
}

// Test that the returned annot is of type POPPLER_ANNOT_FREE_TEXT
TEST_F(PopplerAnnotFreeTextTest_2044, ReturnsCorrectAnnotType_2044) {
    auto doc = createDocWithFreeTextAnnot();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);

    if (annots->getNumAnnots() > 0) {
        std::shared_ptr<Annot> annot(annots->getAnnot(0));
        if (annot->getType() == Annot::typeFreeText) {
            PopplerAnnot *poppler_annot = _poppler_annot_free_text_new(annot);
            ASSERT_NE(poppler_annot, nullptr);

            PopplerAnnotType type = poppler_annot_get_annot_type(poppler_annot);
            EXPECT_EQ(type, POPPLER_ANNOT_FREE_TEXT);

            g_object_unref(poppler_annot);
        }
    }
}

// Test that font description is populated when DA string contains font info
TEST_F(PopplerAnnotFreeTextTest_2044, FontDescriptionPopulated_2044) {
    auto doc = createDocWithFreeTextAnnot();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);

    if (annots->getNumAnnots() > 0) {
        std::shared_ptr<Annot> annot(annots->getAnnot(0));
        if (annot->getType() == Annot::typeFreeText) {
            PopplerAnnot *poppler_annot = _poppler_annot_free_text_new(annot);
            ASSERT_NE(poppler_annot, nullptr);

            PopplerAnnotFreeText *ft_annot = POPPLER_ANNOT_FREE_TEXT(poppler_annot);
            // The DA string "/Helv 12 Tf" should produce a font description
            if (ft_annot->font_desc != nullptr) {
                EXPECT_NE(ft_annot->font_desc->font_name, nullptr);
                EXPECT_DOUBLE_EQ(ft_annot->font_desc->size_pt, 12.0);
            }

            g_object_unref(poppler_annot);
        }
    }
}

// Test with a FreeText annotation that has no default appearance font name
TEST_F(PopplerAnnotFreeTextTest_2044, NoFontNameInDA_2044) {
    // Create a PDF with a FreeText annotation with empty DA
    static const char *pdfNoFont =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "   /Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /FreeText /Rect [100 100 300 200]\n"
        "   /DA () /Contents (Test) >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000062 00000 n \n"
        "0000000119 00000 n \n"
        "0000000221 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "340\n"
        "%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfNoFont), 0, strlen(pdfNoFont), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                std::shared_ptr<Annot> annot(annots->getAnnot(0));
                if (annot->getType() == Annot::typeFreeText) {
                    PopplerAnnot *poppler_annot = _poppler_annot_free_text_new(annot);
                    ASSERT_NE(poppler_annot, nullptr);

                    PopplerAnnotFreeText *ft_annot = POPPLER_ANNOT_FREE_TEXT(poppler_annot);
                    // With empty DA, font_desc should be null
                    EXPECT_EQ(ft_annot->font_desc, nullptr);

                    g_object_unref(poppler_annot);
                }
            }
        }
    }
}

// Test font color is extracted from DA string
TEST_F(PopplerAnnotFreeTextTest_2044, FontColorExtracted_2044) {
    auto doc = createDocWithFreeTextAnnot();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);

    if (annots->getNumAnnots() > 0) {
        std::shared_ptr<Annot> annot(annots->getAnnot(0));
        if (annot->getType() == Annot::typeFreeText) {
            PopplerAnnot *poppler_annot = _poppler_annot_free_text_new(annot);
            ASSERT_NE(poppler_annot, nullptr);

            PopplerAnnotFreeText *ft_annot = POPPLER_ANNOT_FREE_TEXT(poppler_annot);
            // DA string "0 0 0 rg" means black color
            // The font_color should have been set
            // Black = (0, 0, 0) which in PopplerColor is (0, 0, 0)
            EXPECT_EQ(ft_annot->font_color.red, 0);
            EXPECT_EQ(ft_annot->font_color.green, 0);
            EXPECT_EQ(ft_annot->font_color.blue, 0);

            g_object_unref(poppler_annot);
        }
    }
}

// Test with colored font in DA
TEST_F(PopplerAnnotFreeTextTest_2044, FontColorRed_2044) {
    static const char *pdfRedFont =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /AcroForm << /DR << /Font << /Helv 5 0 R >> >> >> >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "   /Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /FreeText /Rect [100 100 300 200]\n"
        "   /DA (/Helv 12 Tf 1 0 0 rg) /Contents (Red text) >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000115 00000 n \n"
        "0000000172 00000 n \n"
        "0000000274 00000 n \n"
        "0000000421 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "498\n"
        "%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfRedFont), 0, strlen(pdfRedFont), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Page *page = doc->getPage(1);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots && annots->getNumAnnots() > 0) {
                std::shared_ptr<Annot> annot(annots->getAnnot(0));
                if (annot->getType() == Annot::typeFreeText) {
                    PopplerAnnot *poppler_annot = _poppler_annot_free_text_new(annot);
                    ASSERT_NE(poppler_annot, nullptr);

                    PopplerAnnotFreeText *ft_annot = POPPLER_ANNOT_FREE_TEXT(poppler_annot);
                    // "1 0 0 rg" means red color, PopplerColor uses 16-bit values (0-65535)
                    EXPECT_GT(ft_annot->font_color.red, 0);

                    g_object_unref(poppler_annot);
                }
            }
        }
    }
}

// Test that the created annotation is a proper GObject and can be ref/unref'd
TEST_F(PopplerAnnotFreeTextTest_2044, GObjectRefCounting_2044) {
    auto doc = createDocWithFreeTextAnnot();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Annots *annots = page->getAnnots();
    ASSERT_NE(annots, nullptr);

    if (annots->getNumAnnots() > 0) {
        std::shared_ptr<Annot> annot(annots->getAnnot(0));
        if (annot->getType() == Annot::typeFreeText) {
            PopplerAnnot *poppler_annot = _poppler_annot_free_text_new(annot);
            ASSERT_NE(poppler_annot, nullptr);

            // Ref count should be 1 (floating ref sunk)
            g_object_ref(poppler_annot);
            // Now ref count is 2
            g_object_unref(poppler_annot);
            // Back to 1
            g_object_unref(poppler_annot);
            // Freed - should not crash
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
