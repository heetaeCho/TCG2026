#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include <glib-object.h>



// Mocking the PopplerDocument for testing purposes

class MockPopplerDocument : public GObject {

public:

    MockPopplerDocument() : GObject() {}

};



TEST_F(PopplerStructureElementIterTest_2535, CopyNullPointer_2535) {

    PopplerStructureElementIter* iter = nullptr;

    PopplerStructureElementIter* new_iter = poppler_structure_element_iter_copy(iter);

    EXPECT_EQ(new_iter, nullptr);

}



TEST_F(PopplerStructureElementIterTest_2535, CopyValidIterator_2535) {

    PopplerDocument* mock_document = reinterpret_cast<PopplerDocument*>(g_object_new(G_TYPE_OBJECT, nullptr));

    PopplerStructureElementIter iter;

    iter.is_root = 1;

    iter.index = 0;

    iter.document = mock_document;



    PopplerStructureElementIter* new_iter = poppler_structure_element_iter_copy(&iter);

    

    EXPECT_NE(new_iter, nullptr);

    EXPECT_EQ(new_iter->is_root, iter.is_root);

    EXPECT_EQ(new_iter->index, iter.index);

    EXPECT_EQ(new_iter->document, mock_document);



    // Clean up

    g_object_unref(mock_document);

    g_slice_free(PopplerStructureElementIter, new_iter);

}



TEST_F(PopplerStructureElementIterTest_2535, CopyBoundaryConditions_2535) {

    PopplerDocument* mock_document = reinterpret_cast<PopplerDocument*>(g_object_new(G_TYPE_OBJECT, nullptr));

    

    // Test with max values

    PopplerStructureElementIter iter;

    iter.is_root = 1;

    iter.index = UINT_MAX;

    iter.document = mock_document;



    PopplerStructureElementIter* new_iter_max = poppler_structure_element_iter_copy(&iter);

    

    EXPECT_NE(new_iter_max, nullptr);

    EXPECT_EQ(new_iter_max->is_root, iter.is_root);

    EXPECT_EQ(new_iter_max->index, iter.index);

    EXPECT_EQ(new_iter_max->document, mock_document);



    // Test with min values

    iter.is_root = 0;

    iter.index = 0;

    PopplerStructureElementIter* new_iter_min = poppler_structure_element_iter_copy(&iter);

    

    EXPECT_NE(new_iter_min, nullptr);

    EXPECT_EQ(new_iter_min->is_root, iter.is_root);

    EXPECT_EQ(new_iter_min->index, iter.index);

    EXPECT_EQ(new_iter_min->document, mock_document);



    // Clean up

    g_object_unref(mock_document);

    g_slice_free(PopplerStructureElementIter, new_iter_max);

    g_slice_free(PopplerStructureElementIter, new_iter_min);

}
