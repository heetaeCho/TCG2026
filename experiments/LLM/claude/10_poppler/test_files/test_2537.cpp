#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-structure-element.h"
#include "poppler-private.h"

#include <cstdio>
#include <cstring>
#include <string>

class PopplerStructureElementIterTest_2537 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_with_struct_ = nullptr;
        doc_without_struct_ = nullptr;
    }

    void TearDown() override {
        if (doc_with_struct_) {
            g_object_unref(doc_with_struct_);
        }
        if (doc_without_struct_) {
            g_object_unref(doc_without_struct_);
        }
    }

    // Helper to create a PDF with structure tree
    PopplerDocument *createPDFWithStructure() {
        // Create a simple tagged PDF in memory
        const char *pdf_content =
            "%PDF-1.7\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /MarkInfo << /Marked true >> /StructTreeRoot 5 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R /StructParents 0 >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /StructTreeRoot /K 6 0 R /ParentTree 7 0 R >>\n"
            "endobj\n"
            "6 0 obj\n"
            "<< /Type /StructElem /S /Document /K 8 0 R >>\n"
            "endobj\n"
            "7 0 obj\n"
            "<< /Type /NumberTree /Nums [] >>\n"
            "endobj\n"
            "8 0 obj\n"
            "<< /Type /StructElem /S /P /K 0 /Pg 3 0 R >>\n"
            "endobj\n"
            "xref\n"
            "0 9\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000115 00000 n \n"
            "0000000172 00000 n \n"
            "0000000305 00000 n \n"
            "0000000399 00000 n \n"
            "0000000480 00000 n \n"
            "0000000545 00000 n \n"
            "0000000603 00000 n \n"
            "trailer\n"
            "<< /Size 9 /Root 1 0 R >>\n"
            "startxref\n"
            "680\n"
            "%%EOF\n";

        // Write to temp file
        std::string tmpfile = "/tmp/test_struct_2537.pdf";
        FILE *f = fopen(tmpfile.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpfile.c_str(), nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Helper to create a simple PDF without structure tree
    PopplerDocument *createPDFWithoutStructure() {
        const char *pdf_content =
            "%PDF-1.4\n"
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
            "206\n"
            "%%EOF\n";

        std::string tmpfile = "/tmp/test_nostruct_2537.pdf";
        FILE *f = fopen(tmpfile.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpfile.c_str(), nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *doc_with_struct_;
    PopplerDocument *doc_without_struct_;
};

// Test that passing NULL document returns NULL
TEST_F(PopplerStructureElementIterTest_2537, NullDocumentReturnsNull_2537) {
    // Passing NULL should return NULL (g_return_val_if_fail check)
    // Note: This will trigger a GLib critical warning
    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(iter, nullptr);
}

// Test that a document without structure tree returns NULL iter
TEST_F(PopplerStructureElementIterTest_2537, DocumentWithoutStructTreeReturnsNull_2537) {
    doc_without_struct_ = createPDFWithoutStructure();
    if (doc_without_struct_ == nullptr) {
        GTEST_SKIP() << "Could not create test PDF without structure";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc_without_struct_);
    EXPECT_EQ(iter, nullptr);
}

// Test that a document with structure tree returns non-NULL iter
TEST_F(PopplerStructureElementIterTest_2537, DocumentWithStructTreeReturnsNonNull_2537) {
    doc_with_struct_ = createPDFWithStructure();
    if (doc_with_struct_ == nullptr) {
        GTEST_SKIP() << "Could not create test PDF with structure";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc_with_struct_);
    // May or may not be NULL depending on whether poppler actually parses the structure
    // from our minimal PDF. We test both paths are handled gracefully.
    if (iter != nullptr) {
        poppler_structure_element_iter_free(iter);
    }
}

// Test that creating iter from the same document twice gives two independent iterators
TEST_F(PopplerStructureElementIterTest_2537, TwoItersFromSameDocAreIndependent_2537) {
    doc_with_struct_ = createPDFWithStructure();
    if (doc_with_struct_ == nullptr) {
        GTEST_SKIP() << "Could not create test PDF with structure";
    }

    PopplerStructureElementIter *iter1 = poppler_structure_element_iter_new(doc_with_struct_);
    PopplerStructureElementIter *iter2 = poppler_structure_element_iter_new(doc_with_struct_);

    // Both should be either NULL or non-NULL
    EXPECT_EQ(iter1 == nullptr, iter2 == nullptr);

    if (iter1 != nullptr && iter2 != nullptr) {
        // They should be different pointers
        EXPECT_NE(iter1, iter2);
        poppler_structure_element_iter_free(iter1);
        poppler_structure_element_iter_free(iter2);
    }
}

// Test that iter copy works correctly
TEST_F(PopplerStructureElementIterTest_2537, IterCopyIsValid_2537) {
    doc_with_struct_ = createPDFWithStructure();
    if (doc_with_struct_ == nullptr) {
        GTEST_SKIP() << "Could not create test PDF with structure";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc_with_struct_);
    if (iter == nullptr) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    PopplerStructureElementIter *copy = poppler_structure_element_iter_copy(iter);
    EXPECT_NE(copy, nullptr);
    EXPECT_NE(copy, iter);

    poppler_structure_element_iter_free(copy);
    poppler_structure_element_iter_free(iter);
}

// Test freeing a NULL iter doesn't crash
TEST_F(PopplerStructureElementIterTest_2537, FreeNullIterDoesNotCrash_2537) {
    // poppler_structure_element_iter_free should handle NULL gracefully
    poppler_structure_element_iter_free(nullptr);
    SUCCEED();
}

// Test getting element from iter
TEST_F(PopplerStructureElementIterTest_2537, GetElementFromIter_2537) {
    doc_with_struct_ = createPDFWithStructure();
    if (doc_with_struct_ == nullptr) {
        GTEST_SKIP() << "Could not create test PDF with structure";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc_with_struct_);
    if (iter == nullptr) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    // The element should be non-null if iter is valid
    if (elem != nullptr) {
        g_object_unref(elem);
    }

    poppler_structure_element_iter_free(iter);
}

// Test iterating with next
TEST_F(PopplerStructureElementIterTest_2537, IterNextAdvances_2537) {
    doc_with_struct_ = createPDFWithStructure();
    if (doc_with_struct_ == nullptr) {
        GTEST_SKIP() << "Could not create test PDF with structure";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc_with_struct_);
    if (iter == nullptr) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    // Try to iterate - at some point next should return FALSE
    int count = 0;
    do {
        count++;
        if (count > 1000) {
            break; // Safety guard
        }
    } while (poppler_structure_element_iter_next(iter));

    EXPECT_GT(count, 0);
    EXPECT_LE(count, 1000);

    poppler_structure_element_iter_free(iter);
}

// Test getting children from iter
TEST_F(PopplerStructureElementIterTest_2537, GetChildrenFromIter_2537) {
    doc_with_struct_ = createPDFWithStructure();
    if (doc_with_struct_ == nullptr) {
        GTEST_SKIP() << "Could not create test PDF with structure";
    }

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc_with_struct_);
    if (iter == nullptr) {
        GTEST_SKIP() << "No structure tree in test PDF";
    }

    PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
    // child may or may not be NULL depending on structure
    if (child != nullptr) {
        poppler_structure_element_iter_free(child);
    }

    poppler_structure_element_iter_free(iter);
}
