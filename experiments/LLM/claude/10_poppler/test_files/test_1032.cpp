#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler-page.h"
#include "poppler-page-private.h"
#include "poppler-document.h"
#include "poppler-document-private.h"

#include <string>
#include <memory>
#include <vector>

namespace {

// Helper to create a document from a valid PDF for testing purposes
class PagePrivateTest_1032 : public ::testing::Test {
protected:
    void SetUp() override {
        // Try to load a simple PDF document for testing
        // We'll use a minimal in-memory PDF if possible
        doc = nullptr;
        page_obj = nullptr;
    }

    void TearDown() override {
        delete page_obj;
        delete doc;
    }

    poppler::document *doc;
    poppler::page *page_obj;

    bool loadTestDocument(const std::string &path) {
        doc = poppler::document::load_from_file(path);
        if (doc && doc->pages() > 0) {
            page_obj = doc->create_page(0);
            return page_obj != nullptr;
        }
        return false;
    }

    // Create a minimal PDF in memory
    bool loadMinimalDocument() {
        // Minimal PDF content
        const char pdf_content[] =
            "%PDF-1.0\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        doc = poppler::document::load_from_raw_data(pdf_content, sizeof(pdf_content) - 1);
        if (doc && doc->pages() > 0) {
            page_obj = doc->create_page(0);
            return page_obj != nullptr;
        }
        return false;
    }
};

// Test that page_private::get returns a non-null pointer for a valid page
TEST_F(PagePrivateTest_1032, GetReturnsNonNullForValidPage_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv = poppler::page_private::get(page_obj);
    ASSERT_NE(priv, nullptr);
}

// Test that page_private::get returns consistent results on multiple calls
TEST_F(PagePrivateTest_1032, GetReturnsConsistentPointer_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv1 = poppler::page_private::get(page_obj);
    poppler::page_private *priv2 = poppler::page_private::get(page_obj);
    ASSERT_EQ(priv1, priv2);
}

// Test that page_private::get works with a const page pointer
TEST_F(PagePrivateTest_1032, GetWorksWithConstPagePointer_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    const poppler::page *const_page = page_obj;
    poppler::page_private *priv = poppler::page_private::get(const_page);
    ASSERT_NE(priv, nullptr);
}

// Test that the page_private has a valid doc pointer
TEST_F(PagePrivateTest_1032, PrivateHasValidDocPointer_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv = poppler::page_private::get(page_obj);
    ASSERT_NE(priv, nullptr);
    EXPECT_NE(priv->doc, nullptr);
}

// Test that the page_private has a valid page pointer
TEST_F(PagePrivateTest_1032, PrivateHasValidPagePointer_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv = poppler::page_private::get(page_obj);
    ASSERT_NE(priv, nullptr);
    EXPECT_NE(priv->page, nullptr);
}

// Test that font_info_cache_initialized defaults to false
TEST_F(PagePrivateTest_1032, FontInfoCacheInitializedDefaultsFalse_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv = poppler::page_private::get(page_obj);
    ASSERT_NE(priv, nullptr);
    // The default value should be false as specified in the header
    EXPECT_FALSE(priv->font_info_cache_initialized);
}

// Test that transition defaults to nullptr
TEST_F(PagePrivateTest_1032, TransitionDefaultsToNullptr_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv = poppler::page_private::get(page_obj);
    ASSERT_NE(priv, nullptr);
    // For a minimal PDF without transitions, transition should be nullptr
    EXPECT_EQ(priv->transition, nullptr);
}

// Test page orientation for a basic page
TEST_F(PagePrivateTest_1032, PageOrientationBasic_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    // Just verify it doesn't crash and returns a valid enum value
    poppler::page::orientation_enum orient = page_obj->orientation();
    // A standard portrait page should have 0-degree rotation typically
    EXPECT_GE(static_cast<int>(orient), 0);
}

// Test page duration for a page without duration
TEST_F(PagePrivateTest_1032, PageDurationDefault_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    double duration = page_obj->duration();
    // A page without explicit duration should return a negative value or 0
    // typically -1 means no duration set
    EXPECT_LE(duration, 0.0);
}

// Test page_rect returns valid rectangle
TEST_F(PagePrivateTest_1032, PageRectReturnsValidRect_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::rectf rect = page_obj->page_rect();
    // Our minimal PDF defines MediaBox [0 0 612 792]
    EXPECT_GE(rect.width(), 0);
    EXPECT_GE(rect.height(), 0);
}

// Test page transition for a page without transition
TEST_F(PagePrivateTest_1032, PageTransitionNullForBasicPage_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    const poppler::page_transition *trans = page_obj->transition();
    // A basic page without transition effects should return nullptr
    EXPECT_EQ(trans, nullptr);
}

// Test text extraction on an empty page
TEST_F(PagePrivateTest_1032, TextOnEmptyPage_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::rectf rect;
    poppler::ustring text = page_obj->text(rect);
    // An empty page should return empty text
    EXPECT_TRUE(text.empty());
}

// Test text_list on an empty page
TEST_F(PagePrivateTest_1032, TextListOnEmptyPage_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    std::vector<poppler::text_box> boxes = page_obj->text_list();
    // An empty page should return no text boxes
    EXPECT_TRUE(boxes.empty());
}

// Test init_font_info_cache changes the flag
TEST_F(PagePrivateTest_1032, InitFontInfoCacheSetsFlag_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv = poppler::page_private::get(page_obj);
    ASSERT_NE(priv, nullptr);
    EXPECT_FALSE(priv->font_info_cache_initialized);

    priv->init_font_info_cache();
    EXPECT_TRUE(priv->font_info_cache_initialized);
}

// Test that calling init_font_info_cache multiple times is safe
TEST_F(PagePrivateTest_1032, InitFontInfoCacheIdempotent_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::page_private *priv = poppler::page_private::get(page_obj);
    ASSERT_NE(priv, nullptr);

    priv->init_font_info_cache();
    EXPECT_TRUE(priv->font_info_cache_initialized);

    // Calling again should not crash
    priv->init_font_info_cache();
    EXPECT_TRUE(priv->font_info_cache_initialized);
}

// Test search on empty page returns false
TEST_F(PagePrivateTest_1032, SearchOnEmptyPageReturnsFalse_1032) {
    if (!loadMinimalDocument()) {
        GTEST_SKIP() << "Could not load minimal test document";
    }

    poppler::ustring search_text = poppler::ustring::from_latin1("hello");
    poppler::rectf rect;
    bool found = page_obj->search(search_text, rect,
                                   poppler::page::search_from_top,
                                   poppler::page::case_sensitive,
                                   poppler::page::rotate_0);
    EXPECT_FALSE(found);
}

} // namespace
