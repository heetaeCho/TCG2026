#include <gtest/gtest.h>

#include "poppler-document.h"



// Assuming PopplerIndexIter and related functions are declared in poppler-document.h



class PopplerIndexIterTest_2212 : public ::testing::Test {

protected:

    PopplerDocument* document;

    PopplerIndexIter* iter;



    void SetUp() override {

        // Initialize a mock or dummy document

        document = reinterpret_cast<PopplerDocument*>(g_slice_alloc0(sizeof(PopplerDocument)));

        g_object_ref(document);



        // Create an initial index iterator for testing

        iter = g_slice_alloc0(sizeof(PopplerIndexIter));

        iter->document = document;

    }



    void TearDown() override {

        // Clean up the copied iterators and original document

        poppler_index_iter_free(iter);

        g_object_unref(document);

        g_slice_free(PopplerDocument, document);

    }

};



TEST_F(PopplerIndexIterTest_2212, CopyCreatesNewInstance_2212) {

    PopplerIndexIter* new_iter = poppler_index_iter_copy(iter);

    EXPECT_NE(new_iter, iter);

    poppler_index_iter_free(new_iter);

}



TEST_F(PopplerIndexIterTest_2212, CopyPreservesDocumentReference_2212) {

    PopplerIndexIter* new_iter = poppler_index_iter_copy(iter);

    EXPECT_EQ(new_iter->document, iter->document);

    poppler_index_iter_free(new_iter);

}



TEST_F(PopplerIndexIterTest_2212, NullInputReturnsNull_2212) {

    PopplerIndexIter* new_iter = poppler_index_iter_copy(nullptr);

    EXPECT_EQ(new_iter, nullptr);

}



TEST_F(PopplerIndexIterTest_2212, CopyIncreasesDocumentReferenceCount_2212) {

    guint initial_ref_count = G_OBJECT(document)->ref_count;

    PopplerIndexIter* new_iter = poppler_index_iter_copy(iter);

    guint final_ref_count = G_OBJECT(document)->ref_count;



    EXPECT_EQ(final_ref_count, initial_ref_count + 1);



    poppler_index_iter_free(new_iter);

}
