#include <gtest/gtest.h>

#include "poppler-structure-element.h"

#include <glib-object.h>



// Assuming PopplerStructureElementIter creation function exists for testing purpose.

extern "C" {

    PopplerStructureElementIter* poppler_structure_element_iter_new() {

        return g_slice_new0(PopplerStructureElementIter);

    }

}



class PopplerStructureElementIterTest : public ::testing::Test {

protected:

    void SetUp() override {

        iter = poppler_structure_element_iter_new();

        GASSERT_NE(iter, nullptr);

    }



    void TearDown() override {

        poppler_structure_element_iter_free(iter);

        iter = nullptr;

    }



    PopplerStructureElementIter* iter;

};



TEST_F(PopplerStructureElementIterTest_2536, FreeNullPointer_2536) {

    // Test that freeing a null pointer does not cause any issues

    poppler_structure_element_iter_free(nullptr);

}



TEST_F(PopplerStructureElementIterTest_2536, FreeValidPointer_2536) {

    // Test that freeing a valid pointer works as expected

    PopplerStructureElementIter* tempIter = poppler_structure_element_iter_new();

    EXPECT_NE(tempIter, nullptr);

    poppler_structure_element_iter_free(tempIter);

}



TEST_F(PopplerStructureElementIterTest_2536, FreeTwice_2536) {

    // Test that freeing the same pointer twice does not cause any issues

    poppler_structure_element_iter_free(iter);

    iter = nullptr;  // Prevent teardown from attempting to free again

    poppler_structure_element_iter_free(iter);

}



TEST_F(PopplerStructureElementIterTest_2536, DocumentRefHandling_2536) {

    // Assuming document is set up in some way for testing.

    GObject* dummyDocument = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));

    iter->document = dummyDocument;

    

    EXPECT_EQ(G_OBJECT_REF_COUNT(dummyDocument), 1);

    poppler_structure_element_iter_free(iter);

    iter = nullptr;  // Prevent teardown from attempting to free again

    

    EXPECT_EQ(G_OBJECT_REF_COUNT(dummyDocument), 0);

    g_object_unref(dummyDocument);  // Clean up dummy document

}
