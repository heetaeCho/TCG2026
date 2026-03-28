// File: poppler-annot-ink-get-draw-below-test-2134.cc
#include <gtest/gtest.h>

#include <poppler/glib/poppler.h>
#include <glib.h>

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

extern "C" {
// Not (currently) declared in the public poppler-glib headers in some builds.
gboolean poppler_annot_ink_get_draw_below(PopplerAnnotInk *annot);
}

namespace {

std::string BuildMinimalOnePagePdfBytes()
{
    // Build a tiny valid PDF with correct xref offsets (no content drawing needed).
    //
    // Objects:
    //  1 0: Catalog
    //  2 0: Pages
    //  3 0: Page
    //  4 0: Contents (empty stream)
    //
    // This is purely a test fixture generator; it does not depend on Poppler internals.
    struct Obj {
        int num;
        std::string body;
    };

    const std::vector<Obj> objs = {
        { 1, "<< /Type /Catalog /Pages 2 0 R >>" },
        { 2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>" },
        { 3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Resources << >> /Contents 4 0 R >>" },
        { 4, "<< /Length 0 >>\nstream\n\nendstream" },
    };

    std::ostringstream out;
    out << "%PDF-1.4\n";

    // offsets[i] corresponds to object number i (0 unused).
    std::vector<std::size_t> offsets(5, 0);

    for (const auto &o : objs) {
        offsets[o.num] = static_cast<std::size_t>(out.tellp());
        out << o.num << " 0 obj\n" << o.body << "\nendobj\n";
    }

    const std::size_t xref_pos = static_cast<std::size_t>(out.tellp());
    out << "xref\n";
    out << "0 5\n";
    out << "0000000000 65535 f \n";
    for (int i = 1; i <= 4; ++i) {
        out << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
    }

    out << "trailer\n";
    out << "<< /Size 5 /Root 1 0 R >>\n";
    out << "startxref\n";
    out << xref_pos << "\n";
    out << "%%EOF\n";
    return out.str();
}

PopplerDocument *CreateDocumentFromPdfBytes(const std::string &pdf_bytes)
{
    GError *error = nullptr;
    PopplerDocument *doc =
        poppler_document_new_from_data(pdf_bytes.data(),
                                       static_cast<int>(pdf_bytes.size()),
                                       /*password=*/nullptr,
                                       &error);
    if (!doc) {
        std::string msg = "poppler_document_new_from_data failed";
        if (error && error->message) {
            msg += ": ";
            msg += error->message;
        }
        if (error) {
            g_error_free(error);
        }
        ADD_FAILURE() << msg;
        return nullptr;
    }
    if (error) {
        g_error_free(error);
    }
    return doc;
}

class PopplerAnnotInkGetDrawBelowTest_2134 : public ::testing::Test {
protected:
    void SetUp() override
    {
        pdf_bytes_ = BuildMinimalOnePagePdfBytes();
        doc_ = CreateDocumentFromPdfBytes(pdf_bytes_);
        ASSERT_NE(doc_, nullptr);
    }

    void TearDown() override
    {
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerAnnot *CreateInkAnnot(const PopplerRectangle &rect)
    {
        PopplerRectangle r = rect;
        PopplerAnnot *annot = poppler_annot_ink_new(doc_, &r);
        EXPECT_NE(annot, nullptr);
        if (annot) {
            EXPECT_TRUE(POPPLER_IS_ANNOT(annot));
            // Some builds expose PopplerAnnotInk type; ensure we got the right kind when possible.
            EXPECT_TRUE(POPPLER_IS_ANNOT_INK(annot));
        }
        return annot;
    }

    std::string pdf_bytes_;
    PopplerDocument *doc_ = nullptr;
};

TEST_F(PopplerAnnotInkGetDrawBelowTest_2134, ReturnsBooleanAndIsStableAcrossCalls_2134)
{
    PopplerRectangle rect;
    rect.x1 = 10;
    rect.y1 = 10;
    rect.x2 = 20;
    rect.y2 = 20;

    PopplerAnnot *base = CreateInkAnnot(rect);
    ASSERT_NE(base, nullptr);

    auto *ink = POPPLER_ANNOT_INK(base);
    ASSERT_NE(ink, nullptr);

    const gboolean v1 = poppler_annot_ink_get_draw_below(ink);
    const gboolean v2 = poppler_annot_ink_get_draw_below(ink);

    // Observable behavior: must be a gboolean (0 or 1), and repeated reads should be consistent.
    EXPECT_TRUE(v1 == FALSE || v1 == TRUE);
    EXPECT_TRUE(v2 == FALSE || v2 == TRUE);
    EXPECT_EQ(v1, v2);

    g_object_unref(base);
}

TEST_F(PopplerAnnotInkGetDrawBelowTest_2134, WorksWithDegenerateRectangleBoundary_2134)
{
    // Boundary: zero-area rectangle (x1==x2 and y1==y2). poppler_annot_ink_new may accept or reject.
    PopplerRectangle rect;
    rect.x1 = 5;
    rect.y1 = 5;
    rect.x2 = 5;
    rect.y2 = 5;

    PopplerAnnot *base = poppler_annot_ink_new(doc_, &rect);
    ASSERT_NE(doc_, nullptr);

    if (!base) {
        // If the constructor rejects degenerate rectangles, that's an observable boundary outcome.
        SUCCEED() << "poppler_annot_ink_new returned NULL for degenerate rectangle (acceptable boundary behavior).";
        return;
    }

    ASSERT_TRUE(POPPLER_IS_ANNOT_INK(base));
    auto *ink = POPPLER_ANNOT_INK(base);

    const gboolean v = poppler_annot_ink_get_draw_below(ink);
    EXPECT_TRUE(v == FALSE || v == TRUE);

    g_object_unref(base);
}

TEST_F(PopplerAnnotInkGetDrawBelowTest_2134, DrawBelowUnaffectedByInkListUpdates_2134)
{
    // We do not assume the actual value of draw-below.
    // We only verify it's readable and remains consistent after observable ink-list operations.
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    PopplerAnnot *base = CreateInkAnnot(rect);
    ASSERT_NE(base, nullptr);
    auto *ink = POPPLER_ANNOT_INK(base);

    const gboolean before = poppler_annot_ink_get_draw_below(ink);
    EXPECT_TRUE(before == FALSE || before == TRUE);

    // Update ink list with zero paths (boundary input).
    poppler_annot_ink_set_ink_list(ink, /*ink_list=*/nullptr, /*n_paths=*/0);

    // Fetch list back (should not crash; behavior depends on implementation).
    gsize n_paths = 999;
    PopplerPath **paths = poppler_annot_ink_get_ink_list(ink, &n_paths);
    (void)paths; // We don't assume ownership rules here.
    // n_paths should be a valid size.
    EXPECT_LE(n_paths, static_cast<gsize>(G_MAXSIZE));

    const gboolean after = poppler_annot_ink_get_draw_below(ink);
    EXPECT_TRUE(after == FALSE || after == TRUE);

    // The getter should be consistent for the same object; if ink list changes draw-below in this build,
    // this expectation might be too strong. However, draw-below is not part of the ink list API, so
    // treating it as stable is a reasonable black-box expectation.
    EXPECT_EQ(before, after);

    g_object_unref(base);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerAnnotInkGetDrawBelowTest_2134, DeathOnNullAnnotPointer_2134)
{
    // Exceptional/error case: passing NULL is invalid for this API as implemented (it dereferences).
    // We verify this is a hard failure rather than silent success.
    EXPECT_DEATH(
        {
            (void)poppler_annot_ink_get_draw_below(nullptr);
        },
        ".*");
}
#endif

} // namespace