// poppler_annot_ink_get_ink_list_test_2132.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace {

constexpr double kEps = 1e-9;

static void FreeInkList(PopplerPath **list, gsize n_paths)
{
    if (!list) {
        return;
    }
    for (gsize i = 0; i < n_paths; ++i) {
        if (list[i]) {
            poppler_path_free(list[i]);
        }
    }
    g_free(list);
}

static void ExpectPointsEq(const PopplerPoint &a, const PopplerPoint &b)
{
    EXPECT_NEAR(a.x, b.x, kEps);
    EXPECT_NEAR(a.y, b.y, kEps);
}

// Build a minimal, valid PDF in-memory for PopplerDocument creation.
static std::string BuildMinimalPdfOneBlankPage()
{
    std::string pdf;
    pdf.reserve(1024);

    auto append = [&](const std::string &s) { pdf += s; };
    auto appendln = [&](const std::string &s) {
        pdf += s;
        pdf += "\n";
    };

    // PDF header
    append("%PDF-1.4\n");
    // Comment with binary chars recommended by spec
    append("%\xE2\xE3\xCF\xD3\n");

    // Track object offsets (index = obj number), 0 is special.
    std::vector<size_t> offsets(5, 0);

    // 1 0 obj (Catalog)
    offsets[1] = pdf.size();
    appendln("1 0 obj");
    appendln("<< /Type /Catalog /Pages 2 0 R >>");
    appendln("endobj");

    // 2 0 obj (Pages)
    offsets[2] = pdf.size();
    appendln("2 0 obj");
    appendln("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
    appendln("endobj");

    // 3 0 obj (Page)
    offsets[3] = pdf.size();
    appendln("3 0 obj");
    appendln("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] /Contents 4 0 R >>");
    appendln("endobj");

    // 4 0 obj (Empty contents stream)
    offsets[4] = pdf.size();
    appendln("4 0 obj");
    appendln("<< /Length 0 >>");
    appendln("stream");
    appendln("endstream");
    appendln("endobj");

    // xref
    const size_t xref_offset = pdf.size();
    appendln("xref");
    appendln("0 5");
    // entry 0 (free)
    appendln("0000000000 65535 f ");
    // entries 1..4
    for (int obj = 1; obj <= 4; ++obj) {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%010zu 00000 n ", offsets[obj]);
        appendln(buf);
    }

    // trailer
    appendln("trailer");
    appendln("<< /Size 5 /Root 1 0 R >>");
    appendln("startxref");
    appendln(std::to_string(xref_offset));
    appendln("%%EOF");

    return pdf;
}

class PopplerAnnotInkGetInkListTest_2132 : public ::testing::Test {
protected:
    void SetUp() override
    {
        const std::string pdf = BuildMinimalPdfOneBlankPage();

        GError *error = nullptr;
        doc_ = poppler_document_new_from_data(pdf.c_str(),
                                             static_cast<int>(pdf.size()),
                                             /*password=*/nullptr,
                                             &error);
        ASSERT_NE(doc_, nullptr);
        ASSERT_EQ(error, nullptr);
    }

    void TearDown() override
    {
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerDocument *doc_ = nullptr;
};

TEST_F(PopplerAnnotInkGetInkListTest_2132, SetInkListThenGetReturnsSamePointsAndCounts_2132)
{
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 10;
    rect.y2 = 10;

    PopplerAnnot *base = poppler_annot_ink_new(doc_, &rect);
    ASSERT_NE(base, nullptr);
    ASSERT_TRUE(POPPLER_IS_ANNOT(base));
    ASSERT_TRUE(POPPLER_IS_ANNOT_INK(base));

    // Build two paths with different point counts.
    PopplerPoint p1_arr[] = { {1.0, 2.0}, {3.0, 4.0} };
    PopplerPoint p2_arr[] = { {5.0, 6.0} };

    PopplerPath *path1 = poppler_path_new_from_array(p1_arr, 2);
    PopplerPath *path2 = poppler_path_new_from_array(p2_arr, 1);
    ASSERT_NE(path1, nullptr);
    ASSERT_NE(path2, nullptr);

    PopplerPath *ink_list_in[] = { path1, path2 };

    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(base), ink_list_in, 2);

    gsize n_paths_out = 999;
    PopplerPath **ink_list_out = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(base), &n_paths_out);

    EXPECT_EQ(n_paths_out, static_cast<gsize>(2));
    ASSERT_NE(ink_list_out, nullptr);

    // Validate path 1 points.
    gsize n_points1 = 0;
    PopplerPoint *points1 = poppler_path_get_points(ink_list_out[0], &n_points1);
    ASSERT_NE(points1, nullptr);
    EXPECT_EQ(n_points1, static_cast<gsize>(2));
    ExpectPointsEq(points1[0], p1_arr[0]);
    ExpectPointsEq(points1[1], p1_arr[1]);
    g_free(points1);

    // Validate path 2 points.
    gsize n_points2 = 0;
    PopplerPoint *points2 = poppler_path_get_points(ink_list_out[1], &n_points2);
    ASSERT_NE(points2, nullptr);
    EXPECT_EQ(n_points2, static_cast<gsize>(1));
    ExpectPointsEq(points2[0], p2_arr[0]);
    g_free(points2);

    // Cleanup
    FreeInkList(ink_list_out, n_paths_out);
    poppler_path_free(path1);
    poppler_path_free(path2);
    g_object_unref(base);
}

TEST_F(PopplerAnnotInkGetInkListTest_2132, SetEmptyInkListThenGetReportsZeroPaths_2132)
{
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 10;
    rect.y2 = 10;

    PopplerAnnot *base = poppler_annot_ink_new(doc_, &rect);
    ASSERT_NE(base, nullptr);
    ASSERT_TRUE(POPPLER_IS_ANNOT_INK(base));

    // Set empty list (boundary case).
    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(base), /*ink_list=*/nullptr, /*n_paths=*/0);

    gsize n_paths_out = 123;
    PopplerPath **ink_list_out = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(base), &n_paths_out);

    EXPECT_EQ(n_paths_out, static_cast<gsize>(0));

    // Implementation may return NULL or a non-NULL pointer for a zero-sized allocation.
    // Both are acceptable as long as the caller can handle it.
    FreeInkList(ink_list_out, n_paths_out);

    g_object_unref(base);
}

TEST_F(PopplerAnnotInkGetInkListTest_2132, FreeReturnedListDoesNotAffectSubsequentGets_2132)
{
    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 10;
    rect.y2 = 10;

    PopplerAnnot *base = poppler_annot_ink_new(doc_, &rect);
    ASSERT_NE(base, nullptr);
    ASSERT_TRUE(POPPLER_IS_ANNOT_INK(base));

    PopplerPoint p_arr[] = { {7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0} };
    PopplerPath *path = poppler_path_new_from_array(p_arr, 3);
    ASSERT_NE(path, nullptr);

    PopplerPath *ink_list_in[] = { path };
    poppler_annot_ink_set_ink_list(POPPLER_ANNOT_INK(base), ink_list_in, 1);

    // First get + free.
    gsize n1 = 0;
    PopplerPath **out1 = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(base), &n1);
    ASSERT_EQ(n1, static_cast<gsize>(1));
    ASSERT_NE(out1, nullptr);
    FreeInkList(out1, n1);

    // Second get should still work and return the same points.
    gsize n2 = 0;
    PopplerPath **out2 = poppler_annot_ink_get_ink_list(POPPLER_ANNOT_INK(base), &n2);
    ASSERT_EQ(n2, static_cast<gsize>(1));
    ASSERT_NE(out2, nullptr);

    gsize n_points = 0;
    PopplerPoint *points = poppler_path_get_points(out2[0], &n_points);
    ASSERT_NE(points, nullptr);
    EXPECT_EQ(n_points, static_cast<gsize>(3));
    ExpectPointsEq(points[0], p_arr[0]);
    ExpectPointsEq(points[1], p_arr[1]);
    ExpectPointsEq(points[2], p_arr[2]);
    g_free(points);

    FreeInkList(out2, n2);

    poppler_path_free(path);
    g_object_unref(base);
}

} // namespace