// poppler_structure_element_is_block_test_2526.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>
#include <poppler-document.h>
#include <poppler-structure-element.h>

namespace {

class PopplerStructureElementIsBlockTest_2526 : public ::testing::Test {
protected:
    static gchar *FileToUri(const char *path)
    {
        if (!path) {
            return nullptr;
        }
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, /*hostname=*/nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return uri;
    }

    static PopplerDocument *TryOpenDoc(const char *path)
    {
        g_autofree gchar *uri = FileToUri(path);
        if (!uri) {
            return nullptr;
        }
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Attempts to find any PDF on the system that yields a non-null structure iterator element.
    // If none is found, callers should skip.
    static PopplerStructureElement *GetAnyStructureElementFromSomePdf(PopplerDocument **out_doc,
                                                                      PopplerStructureElementIter **out_iter)
    {
        if (out_doc) {
            *out_doc = nullptr;
        }
        if (out_iter) {
            *out_iter = nullptr;
        }

        // Common system PDFs (may or may not be tagged). We try a few; if none work, we skip.
        const char *candidates[] = {
            // TeX/ConTeXt docs commonly present on many Linux images.
            "/usr/share/texmf/context/data/scite/context/documents/scite-context-readme.pdf",
            "/usr/share/texmf/context/data/scite/context/documents/scite-context-visual.pdf",
            "/usr/share/texmf/doc/context/presentations/context/2020/context-2020-concepts.pdf",
        };

        for (const char *path : candidates) {
            PopplerDocument *doc = TryOpenDoc(path);
            if (!doc) {
                continue;
            }

            PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
            if (!iter) {
                g_object_unref(doc);
                continue;
            }

            PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
            if (!elem) {
                poppler_structure_element_iter_free(iter);
                g_object_unref(doc);
                continue;
            }

            if (out_doc) {
                *out_doc = doc;
            } else {
                g_object_unref(doc);
            }

            if (out_iter) {
                *out_iter = iter;
            } else {
                poppler_structure_element_iter_free(iter);
            }

            return elem;
        }

        return nullptr;
    }
};

TEST_F(PopplerStructureElementIsBlockTest_2526, NullptrReturnsFalse_2526)
{
    EXPECT_FALSE(poppler_structure_element_is_block(nullptr));
}

TEST_F(PopplerStructureElementIsBlockTest_2526, InvalidTypeReturnsFalse_2526)
{
    // Pass a valid GObject instance of the wrong type; the type check should fail and return FALSE.
    g_autoptr(GObject) obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(obj, nullptr);

    PopplerStructureElement *as_structure = reinterpret_cast<PopplerStructureElement *>(obj);
    EXPECT_FALSE(poppler_structure_element_is_block(as_structure));
}

TEST_F(PopplerStructureElementIsBlockTest_2526, ValidInstanceWithNullElemReturnsFalse_2526)
{
    // Create a PopplerStructureElement instance (GObject) without associating a backing StructElement.
    // The function under test should fail the null-elem guard and return FALSE.
    g_autoptr(GObject) obj = G_OBJECT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    ASSERT_NE(obj, nullptr);

    PopplerStructureElement *structure = POPPLER_STRUCTURE_ELEMENT(obj);
    ASSERT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(structure));

    EXPECT_FALSE(poppler_structure_element_is_block(structure));
}

TEST_F(PopplerStructureElementIsBlockTest_2526, StructuredElementCallIsStableAcrossRepeatedCalls_2526)
{
    PopplerDocument *doc = nullptr;
    PopplerStructureElementIter *iter = nullptr;
    PopplerStructureElement *elem = GetAnyStructureElementFromSomePdf(&doc, &iter);
    if (!elem) {
        GTEST_SKIP() << "No system PDF produced a usable PopplerStructureElement via PopplerStructureElementIter.";
    }
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(iter, nullptr);
    ASSERT_NE(elem, nullptr);

    const gboolean first = poppler_structure_element_is_block(elem);
    const gboolean second = poppler_structure_element_is_block(elem);
    EXPECT_EQ(first, second);

    poppler_structure_element_iter_free(iter);
    g_object_unref(doc);
}

TEST_F(PopplerStructureElementIsBlockTest_2526, IteratingElementsDoesNotCrashAndReturnsGboolean_2526)
{
    PopplerDocument *doc = nullptr;
    PopplerStructureElementIter *iter = nullptr;
    PopplerStructureElement *elem = GetAnyStructureElementFromSomePdf(&doc, &iter);
    if (!elem) {
        GTEST_SKIP() << "No system PDF produced a usable PopplerStructureElement via PopplerStructureElementIter.";
    }
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(iter, nullptr);

    // Exercise multiple elements (if available) to cover a broader set of structure nodes.
    // We only assert that the function returns a valid gboolean and does not crash.
    int visited = 0;
    for (; visited < 50; ++visited) {
        PopplerStructureElement *cur = poppler_structure_element_iter_get_element(iter);
        if (!cur) {
            break;
        }

        const gboolean v = poppler_structure_element_is_block(cur);
        // gboolean is typically an int; ensure it is normalized to TRUE/FALSE.
        EXPECT_TRUE(v == TRUE || v == FALSE);

        if (!poppler_structure_element_iter_next(iter)) {
            break;
        }
    }
    EXPECT_GE(visited, 0);

    poppler_structure_element_iter_free(iter);
    g_object_unref(doc);
}

} // namespace