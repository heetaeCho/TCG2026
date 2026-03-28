// SPDX-License-Identifier: GPL-2.0-or-later
// File: poppler-structure-element-get-text-align-test_2568.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include "poppler-private.h" // for _PopplerStructureElement definition

// Function under test (should be declared by poppler headers; this is here only as a fallback).
extern "C" PopplerStructureTextAlign
poppler_structure_element_get_text_align(PopplerStructureElement *poppler_structure_element);

namespace {

class PopplerStructureElementGetTextAlignTest_2568 : public ::testing::Test {
protected:
    static bool IsValidTextAlignEnum(PopplerStructureTextAlign v)
    {
        // Validate the returned value maps to a registered GEnum value.
        const GType type = poppler_structure_text_align_get_type();
        if (type == G_TYPE_INVALID)
            return false;

        auto *enum_class = static_cast<GEnumClass *>(g_type_class_ref(type));
        if (!enum_class)
            return false;

        const GEnumValue *found = g_enum_get_value(enum_class, static_cast<gint>(v));
        g_type_class_unref(enum_class);
        return found != nullptr;
    }

    static std::string FindFirstExistingPdfPath()
    {
        // Best-effort: try common testdata environment variables and a few likely filenames.
        const char *dirs[] = {
            g_getenv("TESTDATADIR"),
            g_getenv("TOP_SRCDIR"),
            g_getenv("SRCDIR"),
            g_getenv("srcdir"),
        };

        const char *files[] = {
            "structure.pdf",
            "tagged.pdf",
            "TaggedPDF.pdf",
            "tagged-structure.pdf",
            "test.pdf",
        };

        for (const char *d : dirs) {
            if (!d || !*d)
                continue;

            for (const char *f : files) {
                // Try both "<dir>/<file>" and "<dir>/testdata/<file>" and "<dir>/data/<file>"
                const gchar *candidates[] = {
                    g_build_filename(d, f, nullptr),
                    g_build_filename(d, "testdata", f, nullptr),
                    g_build_filename(d, "data", f, nullptr),
                };

                for (const gchar *p : candidates) {
                    if (p && g_file_test(p, G_FILE_TEST_IS_REGULAR)) {
                        std::string out = p;
                        g_free(const_cast<gchar *>(p));
                        // Free any other built strings (best-effort; ignore duplicates)
                        // Note: We only free the one we used; the others are leaked in this rare path,
                        // but this helper is only best-effort and used for skipping. Keep it simple.
                        return out;
                    }
                    if (p)
                        g_free(const_cast<gchar *>(p));
                }
            }
        }

#ifdef TESTDATADIR
        // If the build system provides TESTDATADIR as a macro, try it too.
        for (const char *f : files) {
            gchar *p = g_build_filename(TESTDATADIR, f, nullptr);
            if (p && g_file_test(p, G_FILE_TEST_IS_REGULAR)) {
                std::string out = p;
                g_free(p);
                return out;
            }
            if (p)
                g_free(p);
        }
#endif

        return {};
    }

    static PopplerDocument *LoadDocOrNull(const std::string &path)
    {
        if (path.empty())
            return nullptr;

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
        if (!uri) {
            if (error)
                g_error_free(error);
            return nullptr;
        }

        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);

        if (!doc) {
            if (error)
                g_error_free(error);
            return nullptr;
        }

        if (error)
            g_error_free(error);
        return doc;
    }
};

TEST_F(PopplerStructureElementGetTextAlignTest_2568, NonBlockNullElemReturnsDefault_2568)
{
    // Create a minimal PopplerStructureElement with a null underlying StructElement.
    // This should be treated as "not a block" by poppler_structure_element_is_block(),
    // causing the g_return_val_if_fail() path to return the default enum value.
    _PopplerStructureElement raw {};
    raw.elem = nullptr;

    auto *se = reinterpret_cast<PopplerStructureElement *>(&raw);

    PopplerStructureTextAlign v1 = poppler_structure_element_get_text_align(se);
    PopplerStructureTextAlign v2 = poppler_structure_element_get_text_align(se);

    // Stable and a valid enum value (even for defaults).
    EXPECT_EQ(v1, v2);
    EXPECT_TRUE(IsValidTextAlignEnum(v1));
}

TEST_F(PopplerStructureElementGetTextAlignTest_2568, TwoDistinctNullElemsReturnSameDefault_2568)
{
    _PopplerStructureElement raw1 {};
    raw1.elem = nullptr;
    _PopplerStructureElement raw2 {};
    raw2.elem = nullptr;

    auto *se1 = reinterpret_cast<PopplerStructureElement *>(&raw1);
    auto *se2 = reinterpret_cast<PopplerStructureElement *>(&raw2);

    PopplerStructureTextAlign d1 = poppler_structure_element_get_text_align(se1);
    PopplerStructureTextAlign d2 = poppler_structure_element_get_text_align(se2);

    EXPECT_EQ(d1, d2);
    EXPECT_TRUE(IsValidTextAlignEnum(d1));
}

TEST_F(PopplerStructureElementGetTextAlignTest_2568, BlockElementFromRealDocumentReturnsValidEnum_2568)
{
    const std::string pdf_path = FindFirstExistingPdfPath();
    if (pdf_path.empty())
        GTEST_SKIP() << "No suitable structured PDF test file found via env vars (e.g., TESTDATADIR/TOP_SRCDIR).";

    PopplerDocument *doc = LoadDocOrNull(pdf_path);
    if (!doc)
        GTEST_SKIP() << "Failed to open test PDF: " << pdf_path;

    PopplerStructureElement *root = poppler_document_get_structure_tree(doc);
    if (!root) {
        g_object_unref(doc);
        GTEST_SKIP() << "Document has no structure tree: " << pdf_path;
    }

    // This API is guarded by poppler_structure_element_is_block(). If the root is not a block,
    // we can't safely assert "normal operation" without traversing. Skip in that case.
    if (!poppler_structure_element_is_block(root)) {
        g_object_unref(doc);
        GTEST_SKIP() << "Structure tree root is not a block element in: " << pdf_path;
    }

    PopplerStructureTextAlign v1 = poppler_structure_element_get_text_align(root);
    PopplerStructureTextAlign v2 = poppler_structure_element_get_text_align(root);

    EXPECT_TRUE(IsValidTextAlignEnum(v1));
    EXPECT_EQ(v1, v2);

    g_object_unref(doc);
}

} // namespace