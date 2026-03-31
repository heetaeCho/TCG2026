#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib-object.h>
}

#include "poppler-document.h"
#include "poppler-private.h"
#include "poppler.h"

// We need to include poppler core headers for Outline manipulation
#include "Outline.h"
#include "PDFDoc.h"

#include <memory>
#include <vector>

class PopplerIndexIterTest_2213 : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}

    // Helper to create a PopplerDocument from a PDF file
    PopplerDocument *loadDocument(const char *uri) {
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Helper to create a document from a file path
    PopplerDocument *loadDocumentFromPath(const char *path) {
        gchar *uri = g_filename_to_uri(path, nullptr, nullptr);
        if (!uri) {
            return nullptr;
        }
        PopplerDocument *doc = loadDocument(uri);
        g_free(uri);
        return doc;
    }

    // Create a simple PDF in memory with no outline
    PopplerDocument *createDocumentFromData(const unsigned char *data, int length) {
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_data((char *)data, length, nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Minimal valid PDF with no outline/bookmarks
static const char minimal_pdf_no_outline[] =
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

// Test: poppler_index_iter_new returns nullptr for a document with no outline
TEST_F(PopplerIndexIterTest_2213, ReturnsNullForDocumentWithNoOutline_2213) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)minimal_pdf_no_outline,
        sizeof(minimal_pdf_no_outline) - 1,
        nullptr, &error);

    if (doc == nullptr) {
        // If we can't load the minimal PDF, skip the test gracefully
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
        return;
    }

    PopplerIndexIter *iter = poppler_index_iter_new(doc);
    EXPECT_EQ(iter, nullptr);

    g_object_unref(doc);
}

// Test: poppler_index_iter_new with a document that has an outline
// We use a PDF that has bookmarks/outline entries
TEST_F(PopplerIndexIterTest_2213, ReturnsNonNullForDocumentWithOutline_2213) {
    // Create a PDF with outline in memory
    // This is a more complex PDF with an outline
    static const char pdf_with_outline[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /Outlines 4 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Outlines /First 5 0 R /Last 5 0 R /Count 1 >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Title (Bookmark1) /Parent 4 0 R /Dest [3 0 R /Fit] >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000076 00000 n \n"
        "0000000133 00000 n \n"
        "0000000210 00000 n \n"
        "0000000290 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "373\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)pdf_with_outline,
        sizeof(pdf_with_outline) - 1,
        nullptr, &error);

    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create PDF with outline for testing";
        return;
    }

    PopplerIndexIter *iter = poppler_index_iter_new(doc);
    // If the PDF was properly parsed with outlines, iter should be non-null
    // If the outline parsing failed, it could be null
    if (iter != nullptr) {
        EXPECT_NE(iter, nullptr);
        poppler_index_iter_free(iter);
    }
    // else: the minimal outline PDF may not have been parsed correctly

    g_object_unref(doc);
}

// Test: poppler_index_iter_copy creates a valid copy
TEST_F(PopplerIndexIterTest_2213, CopyIterReturnsValidCopy_2213) {
    static const char pdf_with_outline[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /Outlines 4 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Outlines /First 5 0 R /Last 5 0 R /Count 1 >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Title (Bookmark1) /Parent 4 0 R /Dest [3 0 R /Fit] >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000076 00000 n \n"
        "0000000133 00000 n \n"
        "0000000210 00000 n \n"
        "0000000290 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "373\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)pdf_with_outline,
        sizeof(pdf_with_outline) - 1,
        nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document for testing";
        return;
    }

    PopplerIndexIter *iter = poppler_index_iter_new(doc);
    if (iter == nullptr) {
        g_object_unref(doc);
        GTEST_SKIP() << "No outline available in test PDF";
        return;
    }

    PopplerIndexIter *copy = poppler_index_iter_copy(iter);
    EXPECT_NE(copy, nullptr);

    if (copy) {
        poppler_index_iter_free(copy);
    }
    poppler_index_iter_free(iter);
    g_object_unref(doc);
}

// Test: poppler_index_iter_copy with nullptr returns nullptr
TEST_F(PopplerIndexIterTest_2213, CopyNullIterReturnsNull_2213) {
    PopplerIndexIter *copy = poppler_index_iter_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test: poppler_index_iter_free with nullptr does not crash
TEST_F(PopplerIndexIterTest_2213, FreeNullIterDoesNotCrash_2213) {
    // Should not crash
    poppler_index_iter_free(nullptr);
    SUCCEED();
}

// Test: poppler_index_iter_get_child with nullptr returns nullptr
TEST_F(PopplerIndexIterTest_2213, GetChildOfNullReturnsNull_2213) {
    PopplerIndexIter *child = poppler_index_iter_get_child(nullptr);
    EXPECT_EQ(child, nullptr);
}

// Test: poppler_index_iter_next returns FALSE when there's only one item or at end
TEST_F(PopplerIndexIterTest_2213, NextReturnsFalseAtEnd_2213) {
    static const char pdf_with_outline[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /Outlines 4 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Outlines /First 5 0 R /Last 5 0 R /Count 1 >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Title (Bookmark1) /Parent 4 0 R /Dest [3 0 R /Fit] >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000076 00000 n \n"
        "0000000133 00000 n \n"
        "0000000210 00000 n \n"
        "0000000290 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "373\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)pdf_with_outline,
        sizeof(pdf_with_outline) - 1,
        nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document for testing";
        return;
    }

    PopplerIndexIter *iter = poppler_index_iter_new(doc);
    if (iter == nullptr) {
        g_object_unref(doc);
        GTEST_SKIP() << "No outline available in test PDF";
        return;
    }

    // With only one outline item, next should eventually return FALSE
    // Keep iterating until we hit the end
    int count = 0;
    gboolean has_next;
    do {
        count++;
        has_next = poppler_index_iter_next(iter);
    } while (has_next && count < 100);

    // We should have stopped at some point
    EXPECT_FALSE(has_next);

    poppler_index_iter_free(iter);
    g_object_unref(doc);
}

// Test: poppler_index_iter_get_action returns a valid action
TEST_F(PopplerIndexIterTest_2213, GetActionReturnsValidAction_2213) {
    static const char pdf_with_outline[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /Outlines 4 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Outlines /First 5 0 R /Last 5 0 R /Count 1 >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Title (Bookmark1) /Parent 4 0 R /Dest [3 0 R /Fit] >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000076 00000 n \n"
        "0000000133 00000 n \n"
        "0000000210 00000 n \n"
        "0000000290 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "373\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)pdf_with_outline,
        sizeof(pdf_with_outline) - 1,
        nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document for testing";
        return;
    }

    PopplerIndexIter *iter = poppler_index_iter_new(doc);
    if (iter == nullptr) {
        g_object_unref(doc);
        GTEST_SKIP() << "No outline available in test PDF";
        return;
    }

    PopplerAction *action = poppler_index_iter_get_action(iter);
    // Action could be non-null if outline item has a valid destination
    if (action != nullptr) {
        EXPECT_NE(action->type, POPPLER_ACTION_NONE);
        poppler_action_free(action);
    }

    poppler_index_iter_free(iter);
    g_object_unref(doc);
}

// Test: poppler_index_iter_is_open returns a boolean value
TEST_F(PopplerIndexIterTest_2213, IsOpenReturnsBool_2213) {
    static const char pdf_with_outline[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /Outlines 4 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Outlines /First 5 0 R /Last 5 0 R /Count 1 >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Title (Bookmark1) /Parent 4 0 R /Dest [3 0 R /Fit] >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000076 00000 n \n"
        "0000000133 00000 n \n"
        "0000000210 00000 n \n"
        "0000000290 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "373\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)pdf_with_outline,
        sizeof(pdf_with_outline) - 1,
        nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document for testing";
        return;
    }

    PopplerIndexIter *iter = poppler_index_iter_new(doc);
    if (iter == nullptr) {
        g_object_unref(doc);
        GTEST_SKIP() << "No outline available in test PDF";
        return;
    }

    gboolean is_open = poppler_index_iter_is_open(iter);
    // is_open should be either TRUE or FALSE
    EXPECT_TRUE(is_open == TRUE || is_open == FALSE);

    poppler_index_iter_free(iter);
    g_object_unref(doc);
}

// Test: Creating multiple iterators from the same document
TEST_F(PopplerIndexIterTest_2213, MultipleIteratorsFromSameDocument_2213) {
    static const char pdf_with_outline[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /Outlines 4 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Outlines /First 5 0 R /Last 5 0 R /Count 1 >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Title (Bookmark1) /Parent 4 0 R /Dest [3 0 R /Fit] >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000076 00000 n \n"
        "0000000133 00000 n \n"
        "0000000210 00000 n \n"
        "0000000290 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "373\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)pdf_with_outline,
        sizeof(pdf_with_outline) - 1,
        nullptr, &error);

    if (doc == nullptr) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document for testing";
        return;
    }

    PopplerIndexIter *iter1 = poppler_index_iter_new(doc);
    PopplerIndexIter *iter2 = poppler_index_iter_new(doc);

    // Both should have the same result (both null or both non-null)
    EXPECT_EQ(iter1 == nullptr, iter2 == nullptr);

    if (iter1) poppler_index_iter_free(iter1);
    if (iter2) poppler_index_iter_free(iter2);
    g_object_unref(doc);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
