#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include "poppler-annot.h"

#include <glib.h>
#include <gio/gio.h>
#include <cstdio>
#include <cstring>
#include <string>

class PopplerAnnotStampGetIconTest_2119 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory
        const char *minimal_pdf =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n";

        GError *error = nullptr;
        gsize len = strlen(minimal_pdf);

        // Write to a temp file
        gchar *tmpfile = nullptr;
        gint fd = g_file_open_tmp("test_annot_XXXXXX.pdf", &tmpfile, &error);
        if (fd >= 0) {
            write(fd, minimal_pdf, len);
            close(fd);

            gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (doc) {
                page = poppler_document_get_page(doc, 0);
            }
            g_free(tmpfile);
        }
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerAnnotStamp *createStampAnnot() {
        if (!page) return nullptr;
        PopplerRectangle rect = {100, 100, 200, 200};
        PopplerAnnot *annot = poppler_annot_stamp_new(doc, &rect);
        return POPPLER_ANNOT_STAMP(annot);
    }
};

TEST_F(PopplerAnnotStampGetIconTest_2119, DefaultIcon_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    // Default stamp icon - the default may vary, just check it returns a valid enum value
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_GE(icon, POPPLER_ANNOT_STAMP_ICON_UNKNOWN);
    EXPECT_LE(icon, POPPLER_ANNOT_STAMP_ICON_NONE);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetApproved_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_APPROVED);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetAsIs_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_AS_IS);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_AS_IS);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetConfidential_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetFinal_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_FINAL);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_FINAL);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetExperimental_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetExpired_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetNotApproved_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetNotForPublicRelease_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetSold_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_SOLD);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_SOLD);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetDepartmental_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetForComment_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetForPublicRelease_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetTopSecret_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetNone_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_NONE);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_NONE);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetAndGetUnknown_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_UNKNOWN);
    // Setting unknown - the behavior depends on what string is set internally
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_GE(icon, POPPLER_ANNOT_STAMP_ICON_UNKNOWN);
    EXPECT_LE(icon, POPPLER_ANNOT_STAMP_ICON_NONE);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, SetIconTwiceReturnSecond_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_APPROVED);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    g_object_unref(stamp);
}

TEST_F(PopplerAnnotStampGetIconTest_2119, GetIconCalledMultipleTimes_2119) {
    if (!doc || !page) GTEST_SKIP() << "Could not create test document";
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_SOLD);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_SOLD);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_SOLD);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_SOLD);
    g_object_unref(stamp);
}
