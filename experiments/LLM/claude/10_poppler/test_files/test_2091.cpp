#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <fstream>

class PopplerAnnotTextGetIconTest_2091 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal PDF in memory with a text annotation
        doc_ = nullptr;
        annot_ = nullptr;
    }

    void TearDown() override {
        if (annot_) {
            g_object_unref(annot_);
            annot_ = nullptr;
        }
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerDocument *createSimplePDF() {
        // Create a minimal valid PDF in a temp file
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\nstartxref\n210\n%%EOF\n";

        gchar *tmp_path = nullptr;
        GError *error = nullptr;
        gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmp_path, &error);
        if (fd == -1) {
            g_free(tmp_path);
            return nullptr;
        }
        write(fd, pdf_content, strlen(pdf_content));
        close(fd);

        gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        
        g_free(uri);
        tmp_path_ = tmp_path;
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *doc_;
    PopplerAnnot *annot_;
    gchar *tmp_path_ = nullptr;
};

TEST_F(PopplerAnnotTextGetIconTest_2091, NullAnnotReturnsNull_2091)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    // Note: g_return_val_if_fail with NULL will produce a warning but return NULL
    gchar *icon = poppler_annot_text_get_icon(nullptr);
    EXPECT_EQ(icon, nullptr);
}

TEST_F(PopplerAnnotTextGetIconTest_2091, NewAnnotTextHasDefaultIcon_2091)
{
    doc_ = createSimplePDF();
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect;
    rect.x1 = 100;
    rect.y1 = 100;
    rect.x2 = 200;
    rect.y2 = 200;

    annot_ = poppler_annot_text_new(doc_, &rect);
    ASSERT_NE(annot_, nullptr);

    gchar *icon = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    // A newly created text annotation typically has a default icon like "Note"
    // or could be NULL/empty. We just test the function doesn't crash and returns
    // a valid result.
    if (icon != nullptr) {
        EXPECT_GT(strlen(icon), 0u);
        g_free(icon);
    }

    g_object_unref(page);
    if (tmp_path_) {
        g_unlink(tmp_path_);
        g_free(tmp_path_);
        tmp_path_ = nullptr;
    }
}

TEST_F(PopplerAnnotTextGetIconTest_2091, SetIconThenGetIcon_2091)
{
    doc_ = createSimplePDF();
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect;
    rect.x1 = 100;
    rect.y1 = 100;
    rect.x2 = 200;
    rect.y2 = 200;

    annot_ = poppler_annot_text_new(doc_, &rect);
    ASSERT_NE(annot_, nullptr);

    // Set icon to "Comment"
    poppler_annot_text_set_icon(POPPLER_ANNOT_TEXT(annot_), "Comment");
    gchar *icon = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Comment");
    g_free(icon);

    g_object_unref(page);
    if (tmp_path_) {
        g_unlink(tmp_path_);
        g_free(tmp_path_);
        tmp_path_ = nullptr;
    }
}

TEST_F(PopplerAnnotTextGetIconTest_2091, SetIconToNote_2091)
{
    doc_ = createSimplePDF();
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect;
    rect.x1 = 50;
    rect.y1 = 50;
    rect.x2 = 150;
    rect.y2 = 150;

    annot_ = poppler_annot_text_new(doc_, &rect);
    ASSERT_NE(annot_, nullptr);

    poppler_annot_text_set_icon(POPPLER_ANNOT_TEXT(annot_), "Note");
    gchar *icon = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Note");
    g_free(icon);

    g_object_unref(page);
    if (tmp_path_) {
        g_unlink(tmp_path_);
        g_free(tmp_path_);
        tmp_path_ = nullptr;
    }
}

TEST_F(PopplerAnnotTextGetIconTest_2091, SetIconToCustomString_2091)
{
    doc_ = createSimplePDF();
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect;
    rect.x1 = 10;
    rect.y1 = 10;
    rect.x2 = 50;
    rect.y2 = 50;

    annot_ = poppler_annot_text_new(doc_, &rect);
    ASSERT_NE(annot_, nullptr);

    poppler_annot_text_set_icon(POPPLER_ANNOT_TEXT(annot_), "Help");
    gchar *icon = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Help");
    g_free(icon);

    g_object_unref(page);
    if (tmp_path_) {
        g_unlink(tmp_path_);
        g_free(tmp_path_);
        tmp_path_ = nullptr;
    }
}

TEST_F(PopplerAnnotTextGetIconTest_2091, GetIconReturnsCopyNotSamePointer_2091)
{
    doc_ = createSimplePDF();
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect;
    rect.x1 = 100;
    rect.y1 = 100;
    rect.x2 = 200;
    rect.y2 = 200;

    annot_ = poppler_annot_text_new(doc_, &rect);
    ASSERT_NE(annot_, nullptr);

    poppler_annot_text_set_icon(POPPLER_ANNOT_TEXT(annot_), "Key");

    gchar *icon1 = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    gchar *icon2 = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));

    ASSERT_NE(icon1, nullptr);
    ASSERT_NE(icon2, nullptr);
    // Each call should return a new copy (different pointers)
    EXPECT_NE(icon1, icon2);
    // But same content
    EXPECT_STREQ(icon1, icon2);

    g_free(icon1);
    g_free(icon2);

    g_object_unref(page);
    if (tmp_path_) {
        g_unlink(tmp_path_);
        g_free(tmp_path_);
        tmp_path_ = nullptr;
    }
}

TEST_F(PopplerAnnotTextGetIconTest_2091, ChangeIconMultipleTimes_2091)
{
    doc_ = createSimplePDF();
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PopplerPage *page = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page, nullptr);

    PopplerRectangle rect;
    rect.x1 = 100;
    rect.y1 = 100;
    rect.x2 = 200;
    rect.y2 = 200;

    annot_ = poppler_annot_text_new(doc_, &rect);
    ASSERT_NE(annot_, nullptr);

    // Set to "Note"
    poppler_annot_text_set_icon(POPPLER_ANNOT_TEXT(annot_), "Note");
    gchar *icon = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Note");
    g_free(icon);

    // Change to "Comment"
    poppler_annot_text_set_icon(POPPLER_ANNOT_TEXT(annot_), "Comment");
    icon = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Comment");
    g_free(icon);

    // Change to "Paragraph"
    poppler_annot_text_set_icon(POPPLER_ANNOT_TEXT(annot_), "Paragraph");
    icon = poppler_annot_text_get_icon(POPPLER_ANNOT_TEXT(annot_));
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Paragraph");
    g_free(icon);

    g_object_unref(page);
    if (tmp_path_) {
        g_unlink(tmp_path_);
        g_free(tmp_path_);
        tmp_path_ = nullptr;
    }
}
