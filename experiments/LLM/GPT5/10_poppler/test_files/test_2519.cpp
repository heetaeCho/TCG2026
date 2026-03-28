// poppler-structure-element-get-kind-test.cc
// Unit tests for poppler_structure_element_get_kind()
// TEST_ID: 2519

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>
#include <poppler-structure-element.h>

#include <cstdio>
#include <cstring>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerStructureElementGetKindTest_2519 : public ::testing::Test {
protected:
    void SetUp() override
    {
        tmp_dir_ = g_dir_make_tmp("poppler-structure-element-kind-XXXXXX", nullptr);
        ASSERT_NE(tmp_dir_, nullptr);

        pdf_path_ = g_build_filename(tmp_dir_, "tagged-structure-2519.pdf", nullptr);
        ASSERT_NE(pdf_path_, nullptr);

        ASSERT_TRUE(WriteMinimalTaggedPdf_2519(pdf_path_)) << "Failed to write test PDF";
    }

    void TearDown() override
    {
        if (pdf_path_) {
            g_remove(pdf_path_);
            g_free(pdf_path_);
            pdf_path_ = nullptr;
        }
        if (tmp_dir_) {
            g_rmdir(tmp_dir_);
            g_free(tmp_dir_);
            tmp_dir_ = nullptr;
        }
    }

    static bool WriteFileAll_2519(const char *path, const std::string &bytes)
    {
        FILE *f = g_fopen(path, "wb");
        if (!f) {
            return false;
        }
        const size_t n = fwrite(bytes.data(), 1, bytes.size(), f);
        fclose(f);
        return n == bytes.size();
    }

    // Build a minimal tagged PDF containing a StructTreeRoot and several StructElem nodes
    // with different /S values, so Poppler can expose PopplerStructureElement(s) via the
    // iterator API.
    static bool WriteMinimalTaggedPdf_2519(const char *path)
    {
        struct Obj {
            int num;
            std::string body; // between "obj" and "endobj"
        };

        // Object numbers:
        // 1: Catalog
        // 2: StructTreeRoot
        // 3: Pages
        // 4: StructElem Document (root)
        // 5: StructElem P
        // 6: StructElem H1
        // 7: StructElem L
        // 8: StructElem Table
        // 9: StructElem Figure
        // 10: StructElem Span
        // 11: Page
        // 12: Contents stream (empty)
        std::vector<Obj> objs;

        objs.push_back({1,
                        "<< /Type /Catalog\n"
                        "   /Pages 3 0 R\n"
                        "   /StructTreeRoot 2 0 R\n"
                        "   /MarkInfo << /Marked true >>\n"
                        ">>\n"});
        objs.push_back({2,
                        "<< /Type /StructTreeRoot\n"
                        "   /K [ 4 0 R ]\n"
                        ">>\n"});
        objs.push_back({3,
                        "<< /Type /Pages\n"
                        "   /Kids [ 11 0 R ]\n"
                        "   /Count 1\n"
                        ">>\n"});
        objs.push_back({4,
                        "<< /Type /StructElem\n"
                        "   /S /Document\n"
                        "   /P 2 0 R\n"
                        "   /K [ 5 0 R 6 0 R 7 0 R 8 0 R 9 0 R 10 0 R ]\n"
                        ">>\n"});
        objs.push_back({5,
                        "<< /Type /StructElem\n"
                        "   /S /P\n"
                        "   /P 4 0 R\n"
                        "   /Pg 11 0 R\n"
                        ">>\n"});
        objs.push_back({6,
                        "<< /Type /StructElem\n"
                        "   /S /H1\n"
                        "   /P 4 0 R\n"
                        "   /Pg 11 0 R\n"
                        ">>\n"});
        objs.push_back({7,
                        "<< /Type /StructElem\n"
                        "   /S /L\n"
                        "   /P 4 0 R\n"
                        "   /Pg 11 0 R\n"
                        ">>\n"});
        objs.push_back({8,
                        "<< /Type /StructElem\n"
                        "   /S /Table\n"
                        "   /P 4 0 R\n"
                        "   /Pg 11 0 R\n"
                        ">>\n"});
        objs.push_back({9,
                        "<< /Type /StructElem\n"
                        "   /S /Figure\n"
                        "   /P 4 0 R\n"
                        "   /Pg 11 0 R\n"
                        ">>\n"});
        objs.push_back({10,
                        "<< /Type /StructElem\n"
                        "   /S /Span\n"
                        "   /P 4 0 R\n"
                        "   /Pg 11 0 R\n"
                        ">>\n"});
        objs.push_back({11,
                        "<< /Type /Page\n"
                        "   /Parent 3 0 R\n"
                        "   /MediaBox [ 0 0 200 200 ]\n"
                        "   /Resources << >>\n"
                        "   /Contents 12 0 R\n"
                        ">>\n"});
        objs.push_back({12,
                        "<< /Length 0 >>\n"
                        "stream\n"
                        "endstream\n"});

        std::ostringstream out;
        out << "%PDF-1.7\n";
        out << "%\xE2\xE3\xCF\xD3\n";

        // Offsets: xref requires byte offsets from beginning.
        // We will place a dummy entry for object 0 and then each object in order.
        std::vector<long> offsets;
        offsets.resize(13, 0);

        auto current_offset = [&]() -> long {
            const std::string s = out.str();
            return static_cast<long>(s.size());
        };

        for (const auto &o : objs) {
            offsets[o.num] = current_offset();
            out << o.num << " 0 obj\n";
            out << o.body;
            out << "endobj\n";
        }

        const long xref_offset = current_offset();
        out << "xref\n";
        out << "0 13\n";
        out << "0000000000 65535 f \n";
        for (int i = 1; i <= 12; ++i) {
            // Each entry: 10-digit offset, 5-digit generation, n/f, newline
            char buf[64];
            std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
            out << buf;
        }

        out << "trailer\n";
        out << "<< /Size 13\n";
        out << "   /Root 1 0 R\n";
        out << ">>\n";
        out << "startxref\n";
        out << xref_offset << "\n";
        out << "%%EOF\n";

        return WriteFileAll_2519(path, out.str());
    }

    static void CollectKindsDfs_2519(PopplerStructureElementIter *iter, std::set<PopplerStructureElementKind> &kinds)
    {
        if (!iter) {
            return;
        }

        do {
            PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
            if (elem) {
                kinds.insert(poppler_structure_element_get_kind(elem));
                PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
                if (child) {
                    CollectKindsDfs_2519(child, kinds);
                    poppler_structure_element_iter_free(child);
                }
                g_object_unref(elem);
            }
        } while (poppler_structure_element_iter_next(iter));
    }

    static PopplerDocument *OpenDocFromPath_2519(const char *pdf_path)
    {
        GError *error = nullptr;
        GFile *file = g_file_new_for_path(pdf_path);
        if (!file) {
            return nullptr;
        }
        char *uri = g_file_get_uri(file);
        g_object_unref(file);
        if (!uri) {
            return nullptr;
        }

        PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
        g_free(uri);

        if (!doc) {
            if (error) {
                g_error_free(error);
            }
            return nullptr;
        }
        if (error) {
            g_error_free(error);
        }
        return doc;
    }

    char *tmp_dir_ = nullptr;
    char *pdf_path_ = nullptr;
};

TEST_F(PopplerStructureElementGetKindTest_2519, NullElementReturnsContent_2519)
{
    // Error/exceptional case: NULL input should not crash and should return the documented fallback.
    EXPECT_EQ(poppler_structure_element_get_kind(nullptr), POPPLER_STRUCTURE_ELEMENT_CONTENT);
}

TEST_F(PopplerStructureElementGetKindTest_2519, FreshInstanceWithNoElemReturnsContent_2519)
{
    // Boundary/error case: valid GObject instance but with no underlying StructElement (if any).
    // We don't rely on internal fields; only observe return value.
    PopplerStructureElement *elem =
        POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(poppler_structure_element_get_kind(elem), POPPLER_STRUCTURE_ELEMENT_CONTENT);

    g_object_unref(elem);
}

TEST_F(PopplerStructureElementGetKindTest_2519, TaggedPdfKindsIncludeExpectedMappings_2519)
{
    // Normal operation: obtain real structure elements from a tagged PDF and verify
    // the kind mapping returns the expected PopplerStructureElementKind values.
    PopplerDocument *doc = OpenDocFromPath_2519(pdf_path_);
    ASSERT_NE(doc, nullptr);

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    ASSERT_NE(iter, nullptr);

    std::set<PopplerStructureElementKind> kinds;
    CollectKindsDfs_2519(iter, kinds);

    poppler_structure_element_iter_free(iter);
    g_object_unref(doc);

    // The generated PDF includes these structure element types:
    // Document, P, H1, L, Table, Figure, Span
    EXPECT_TRUE(kinds.find(POPPLER_STRUCTURE_ELEMENT_DOCUMENT) != kinds.end());
    EXPECT_TRUE(kinds.find(POPPLER_STRUCTURE_ELEMENT_PARAGRAPH) != kinds.end());
    EXPECT_TRUE(kinds.find(POPPLER_STRUCTURE_ELEMENT_HEADING_1) != kinds.end());
    EXPECT_TRUE(kinds.find(POPPLER_STRUCTURE_ELEMENT_LIST) != kinds.end());
    EXPECT_TRUE(kinds.find(POPPLER_STRUCTURE_ELEMENT_TABLE) != kinds.end());
    EXPECT_TRUE(kinds.find(POPPLER_STRUCTURE_ELEMENT_FIGURE) != kinds.end());
    EXPECT_TRUE(kinds.find(POPPLER_STRUCTURE_ELEMENT_SPAN) != kinds.end());
}

TEST_F(PopplerStructureElementGetKindTest_2519, TaggedPdfKindsAreStableAcrossMultipleCalls_2519)
{
    // Boundary: calling get_kind repeatedly on the same element should be stable/consistent.
    PopplerDocument *doc = OpenDocFromPath_2519(pdf_path_);
    ASSERT_NE(doc, nullptr);

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    ASSERT_NE(iter, nullptr);

    // Take the first element from the iterator and call multiple times.
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    ASSERT_NE(elem, nullptr);

    PopplerStructureElementKind k1 = poppler_structure_element_get_kind(elem);
    PopplerStructureElementKind k2 = poppler_structure_element_get_kind(elem);
    PopplerStructureElementKind k3 = poppler_structure_element_get_kind(elem);

    EXPECT_EQ(k1, k2);
    EXPECT_EQ(k2, k3);

    g_object_unref(elem);
    poppler_structure_element_iter_free(iter);
    g_object_unref(doc);
}

} // namespace