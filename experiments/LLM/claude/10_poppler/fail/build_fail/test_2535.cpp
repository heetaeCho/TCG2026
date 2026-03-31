#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib.h>
#include <poppler.h>
}

class PopplerStructureElementIterCopyTest_2535 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    
    void SetUp() override {
        // Create a simple PDF document for testing
        // We need a valid document to work with structure elements
        GError *error = nullptr;
        
        // Try to create a minimal document from a file or data
        // For testing purposes, we'll try to find a test PDF
        // If unavailable, some tests will be skipped
    }
    
    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
    
    PopplerDocument* loadTestDocument() {
        GError *error = nullptr;
        // Try loading a simple PDF for testing
        // First try a common test location
        const char *test_paths[] = {
            "test.pdf",
            "/tmp/test.pdf",
            nullptr
        };
        
        for (int i = 0; test_paths[i] != nullptr; i++) {
            gchar *uri = g_filename_to_uri(test_paths[i], nullptr, nullptr);
            if (uri) {
                PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
                if (doc) return doc;
                if (error) {
                    g_error_free(error);
                    error = nullptr;
                }
            }
        }
        return nullptr;
    }
};

// Test that copying a NULL iterator returns NULL
TEST_F(PopplerStructureElementIterCopyTest_2535, CopyNullIterReturnsNull_2535) {
    // g_return_val_if_fail should cause NULL return for NULL input
    // Note: This may trigger a g_warning, which is expected
    PopplerStructureElementIter *result = poppler_structure_element_iter_copy(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that copying a valid iterator returns a non-NULL iterator
TEST_F(PopplerStructureElementIterCopyTest_2535, CopyValidIterReturnsNonNull_2535) {
    document = loadTestDocument();
    if (!document) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElementIter *copy = poppler_structure_element_iter_copy(iter);
    ASSERT_NE(copy, nullptr);
    
    // The copy should be a distinct object
    EXPECT_NE(copy, iter);
    
    poppler_structure_element_iter_free(copy);
    poppler_structure_element_iter_free(iter);
}

// Test that a copied iterator can be freed independently
TEST_F(PopplerStructureElementIterCopyTest_2535, CopiedIterCanBeFreedIndependently_2535) {
    document = loadTestDocument();
    if (!document) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElementIter *copy = poppler_structure_element_iter_copy(iter);
    ASSERT_NE(copy, nullptr);
    
    // Free the copy first, original should still be valid
    poppler_structure_element_iter_free(copy);
    
    // Original iterator should still be usable - get element from it
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    if (elem) {
        g_object_unref(elem);
    }
    
    poppler_structure_element_iter_free(iter);
}

// Test that freeing original doesn't affect the copy
TEST_F(PopplerStructureElementIterCopyTest_2535, FreeOriginalDoesNotAffectCopy_2535) {
    document = loadTestDocument();
    if (!document) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElementIter *copy = poppler_structure_element_iter_copy(iter);
    ASSERT_NE(copy, nullptr);
    
    // Free the original first
    poppler_structure_element_iter_free(iter);
    
    // Copy should still be usable
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(copy);
    if (elem) {
        g_object_unref(elem);
    }
    
    poppler_structure_element_iter_free(copy);
}

// Test that copied iterator yields the same element as the original
TEST_F(PopplerStructureElementIterCopyTest_2535, CopiedIterYieldsSameElement_2535) {
    document = loadTestDocument();
    if (!document) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElementIter *copy = poppler_structure_element_iter_copy(iter);
    ASSERT_NE(copy, nullptr);
    
    PopplerStructureElement *elem_orig = poppler_structure_element_iter_get_element(iter);
    PopplerStructureElement *elem_copy = poppler_structure_element_iter_get_element(copy);
    
    if (elem_orig && elem_copy) {
        // Both should refer to the same kind of element
        PopplerStructureElementKind kind_orig = poppler_structure_element_get_kind(elem_orig);
        PopplerStructureElementKind kind_copy = poppler_structure_element_get_kind(elem_copy);
        EXPECT_EQ(kind_orig, kind_copy);
    }
    
    if (elem_orig) g_object_unref(elem_orig);
    if (elem_copy) g_object_unref(elem_copy);
    
    poppler_structure_element_iter_free(copy);
    poppler_structure_element_iter_free(iter);
}

// Test multiple copies of the same iterator
TEST_F(PopplerStructureElementIterCopyTest_2535, MultipleCopiesAreIndependent_2535) {
    document = loadTestDocument();
    if (!document) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElementIter *copy1 = poppler_structure_element_iter_copy(iter);
    PopplerStructureElementIter *copy2 = poppler_structure_element_iter_copy(iter);
    
    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);
    EXPECT_NE(copy1, iter);
    EXPECT_NE(copy2, iter);
    
    poppler_structure_element_iter_free(copy1);
    poppler_structure_element_iter_free(copy2);
    poppler_structure_element_iter_free(iter);
}

// Test copy of an iterator after advancing it
TEST_F(PopplerStructureElementIterCopyTest_2535, CopyAfterNextPreservesPosition_2535) {
    document = loadTestDocument();
    if (!document) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    // Advance the iterator if possible
    gboolean has_next = poppler_structure_element_iter_next(iter);
    
    if (has_next) {
        PopplerStructureElementIter *copy = poppler_structure_element_iter_copy(iter);
        ASSERT_NE(copy, nullptr);
        
        // Both should point to the same element after advancing
        PopplerStructureElement *elem_orig = poppler_structure_element_iter_get_element(iter);
        PopplerStructureElement *elem_copy = poppler_structure_element_iter_get_element(copy);
        
        if (elem_orig && elem_copy) {
            PopplerStructureElementKind kind_orig = poppler_structure_element_get_kind(elem_orig);
            PopplerStructureElementKind kind_copy = poppler_structure_element_get_kind(elem_copy);
            EXPECT_EQ(kind_orig, kind_copy);
        }
        
        if (elem_orig) g_object_unref(elem_orig);
        if (elem_copy) g_object_unref(elem_copy);
        
        poppler_structure_element_iter_free(copy);
    }
    
    poppler_structure_element_iter_free(iter);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
