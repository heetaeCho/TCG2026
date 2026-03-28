#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include poppler headers
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "PDFDoc.h"
#include "Annot.h"

// We need to create actual PopplerAnnotStamp objects for testing.
// The most reliable way is to create a PDF document with stamp annotations.
// However, since we're testing the GLib wrapper, we'll use the poppler GLib API.

class PopplerAnnotStampTest_2120 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a simple PDF in memory to work with
        // We'll use poppler_document_new_from_data or from file
        // For testing, we need a minimal approach - create from a temp file
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerAnnotStamp *createStampAnnot() {
        // Create a stamp annotation using the GLib API
        PopplerRectangle rect;
        rect.x1 = 0;
        rect.y1 = 0;
        rect.x2 = 100;
        rect.y2 = 100;
        
        PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
            poppler_annot_stamp_new(doc, &rect));
        return POPPLER_ANNOT_STAMP(annot);
    }

    void loadTestDocument() {
        GError *error = nullptr;
        // Create a minimal PDF in memory
        const char *pdf_content = 
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

        GBytes *bytes = g_bytes_new_static(pdf_content, strlen(pdf_content));
        doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
        g_bytes_unref(bytes);

        if (error) {
            g_error_free(error);
            doc = nullptr;
            return;
        }
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }
};

// Test setting icon to APPROVED
TEST_F(PopplerAnnotStampTest_2120, SetIconApproved_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    
    g_object_unref(stamp);
}

// Test setting icon to AS_IS
TEST_F(PopplerAnnotStampTest_2120, SetIconAsIs_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_AS_IS);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_AS_IS);
    
    g_object_unref(stamp);
}

// Test setting icon to CONFIDENTIAL
TEST_F(PopplerAnnotStampTest_2120, SetIconConfidential_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    
    g_object_unref(stamp);
}

// Test setting icon to FINAL
TEST_F(PopplerAnnotStampTest_2120, SetIconFinal_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_FINAL);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_FINAL);
    
    g_object_unref(stamp);
}

// Test setting icon to EXPERIMENTAL
TEST_F(PopplerAnnotStampTest_2120, SetIconExperimental_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL);
    
    g_object_unref(stamp);
}

// Test setting icon to EXPIRED
TEST_F(PopplerAnnotStampTest_2120, SetIconExpired_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    
    g_object_unref(stamp);
}

// Test setting icon to NOT_APPROVED
TEST_F(PopplerAnnotStampTest_2120, SetIconNotApproved_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED);
    
    g_object_unref(stamp);
}

// Test setting icon to NOT_FOR_PUBLIC_RELEASE
TEST_F(PopplerAnnotStampTest_2120, SetIconNotForPublicRelease_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE);
    
    g_object_unref(stamp);
}

// Test setting icon to SOLD
TEST_F(PopplerAnnotStampTest_2120, SetIconSold_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_SOLD);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_SOLD);
    
    g_object_unref(stamp);
}

// Test setting icon to DEPARTMENTAL
TEST_F(PopplerAnnotStampTest_2120, SetIconDepartmental_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL);
    
    g_object_unref(stamp);
}

// Test setting icon to FOR_COMMENT
TEST_F(PopplerAnnotStampTest_2120, SetIconForComment_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT);
    
    g_object_unref(stamp);
}

// Test setting icon to FOR_PUBLIC_RELEASE
TEST_F(PopplerAnnotStampTest_2120, SetIconForPublicRelease_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE);
    
    g_object_unref(stamp);
}

// Test setting icon to TOP_SECRET
TEST_F(PopplerAnnotStampTest_2120, SetIconTopSecret_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);
    
    g_object_unref(stamp);
}

// Test setting icon to NONE (clears the icon)
TEST_F(PopplerAnnotStampTest_2120, SetIconNone_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    // First set to something known
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    
    // Now set to NONE
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_NONE);
    icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_NONE);
    
    g_object_unref(stamp);
}

// Test setting icon to UNKNOWN (should not change the icon - early return)
TEST_F(PopplerAnnotStampTest_2120, SetIconUnknown_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    // First set a known icon
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    
    // Setting UNKNOWN should not change the icon (early return in code)
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_UNKNOWN);
    icon = poppler_annot_stamp_get_icon(stamp);
    EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    
    g_object_unref(stamp);
}

// Test changing icon from one value to another
TEST_F(PopplerAnnotStampTest_2120, ChangeIconBetweenValues_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_APPROVED);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_APPROVED);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_SOLD);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_SOLD);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);
    
    g_object_unref(stamp);
}

// Test setting icon with invalid enum value (boundary beyond defined range)
TEST_F(PopplerAnnotStampTest_2120, SetIconInvalidValue_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    // Set a known icon first
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_FINAL);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_FINAL);
    
    // Try setting an out-of-range value (cast an integer beyond enum range)
    // This should hit the else branch and return without modifying
    poppler_annot_stamp_set_icon(stamp, static_cast<PopplerAnnotStampIcon>(99));
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_FINAL);
    
    g_object_unref(stamp);
}

// Test setting NONE then back to a valid icon
TEST_F(PopplerAnnotStampTest_2120, SetNoneThenValidIcon_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_NONE);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_NONE);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_EXPIRED);
    
    g_object_unref(stamp);
}

// Test all icons in sequence
TEST_F(PopplerAnnotStampTest_2120, SetAllIconsInSequence_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    struct IconTest {
        PopplerAnnotStampIcon icon;
        PopplerAnnotStampIcon expected;
    };
    
    std::vector<IconTest> tests = {
        {POPPLER_ANNOT_STAMP_ICON_APPROVED, POPPLER_ANNOT_STAMP_ICON_APPROVED},
        {POPPLER_ANNOT_STAMP_ICON_AS_IS, POPPLER_ANNOT_STAMP_ICON_AS_IS},
        {POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL},
        {POPPLER_ANNOT_STAMP_ICON_FINAL, POPPLER_ANNOT_STAMP_ICON_FINAL},
        {POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL, POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL},
        {POPPLER_ANNOT_STAMP_ICON_EXPIRED, POPPLER_ANNOT_STAMP_ICON_EXPIRED},
        {POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED, POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED},
        {POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE, POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE},
        {POPPLER_ANNOT_STAMP_ICON_SOLD, POPPLER_ANNOT_STAMP_ICON_SOLD},
        {POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL, POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL},
        {POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT, POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT},
        {POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE, POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE},
        {POPPLER_ANNOT_STAMP_ICON_TOP_SECRET, POPPLER_ANNOT_STAMP_ICON_TOP_SECRET},
        {POPPLER_ANNOT_STAMP_ICON_NONE, POPPLER_ANNOT_STAMP_ICON_NONE},
    };
    
    for (const auto &t : tests) {
        poppler_annot_stamp_set_icon(stamp, t.icon);
        EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), t.expected)
            << "Failed for icon value: " << static_cast<int>(t.icon);
    }
    
    g_object_unref(stamp);
}

// Test setting same icon twice
TEST_F(PopplerAnnotStampTest_2120, SetSameIconTwice_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
    
    g_object_unref(stamp);
}

// Test negative enum value (boundary)
TEST_F(PopplerAnnotStampTest_2120, SetIconNegativeValue_2120) {
    loadTestDocument();
    if (!doc) GTEST_SKIP() << "Could not create test document";
    
    PopplerAnnotStamp *stamp = createStampAnnot();
    ASSERT_NE(stamp, nullptr);
    
    poppler_annot_stamp_set_icon(stamp, POPPLER_ANNOT_STAMP_ICON_SOLD);
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_SOLD);
    
    // Negative value should not be a valid icon, should not change
    poppler_annot_stamp_set_icon(stamp, static_cast<PopplerAnnotStampIcon>(-1));
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_SOLD);
    
    g_object_unref(stamp);
}
