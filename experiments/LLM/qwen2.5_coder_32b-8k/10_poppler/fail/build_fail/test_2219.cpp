#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies if needed (not required in this case as there are no callbacks or external collaborators)

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-document.h"

}



struct _PopplerIndexIter { public const int * items; public size_t index; };



class PopplerIndexIterTest_2219 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PopplerIndexIterTest_2219, FreeNullPointer_2219) {

    poppler_index_iter_free(nullptr);

    // No observable effect to verify, but this should not crash

}



TEST_F(PopplerIndexIterTest_2219, FreeValidPointer_2219) {

    PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);

    iter->document = reinterpret_cast<GObject*>(g_object_new(G_TYPE_OBJECT, nullptr));

    poppler_index_iter_free(iter);

    // No observable effect to verify directly, but this should not crash

}



TEST_F(PopplerIndexIterTest_2219, FreePointerWithNullDocument_2219) {

    PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);

    iter->document = nullptr;

    poppler_index_iter_free(iter);

    // No observable effect to verify directly, but this should not crash

}



TEST_F(PopplerIndexIterTest_2219, FreePointerWithValidDocument_2219) {

    PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);

    iter->document = reinterpret_cast<GObject*>(g_object_new(G_TYPE_OBJECT, nullptr));

    poppler_index_iter_free(iter);

    // No observable effect to verify directly, but this should not crash

}
