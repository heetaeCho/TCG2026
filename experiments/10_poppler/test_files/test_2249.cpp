#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the following declarations based on the provided partial code and typical usage patterns.

extern "C" {

    struct PopplerLayersIter;

    struct PopplerDocument;



    PopplerLayersIter* poppler_layers_iter_get_child(PopplerLayersIter *parent);

}



namespace {



class PopplerLayersIterTest_2249 : public ::testing::Test {

protected:

    PopplerLayersIter parent;

    PopplerLayersIter child;



    void SetUp() override {

        // Initialize the parent iterator as needed for testing

        parent.items = nullptr; // Assuming items is a pointer to some internal list structure

        parent.index = 0;       // Assuming index is used to track the current position in the list

        parent.document = reinterpret_cast<PopplerDocument*>(0x1); // Mock document pointer

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(PopplerLayersIterTest_2249, GetChild_ReturnsNullForEmptyKids_2249) {

    parent.items = nullptr; // No items available

    EXPECT_EQ(poppler_layers_iter_get_child(&parent), nullptr);

}



TEST_F(PopplerLayersIterTest_2249, GetChild_ReturnsNullWhenIndexOutOfRange_2249) {

    parent.items = g_list_prepend(parent.items, reinterpret_cast<gpointer>(0x1)); // One item

    parent.index = 1; // Index out of range

    EXPECT_EQ(poppler_layers_iter_get_child(&parent), nullptr);

}



TEST_F(PopplerLayersIterTest_2249, GetChild_ReturnsNullWhenKidsIsNull_2249) {

    Layer layer;

    layer.kids = nullptr; // No kids available

    parent.items = g_list_prepend(parent.items, &layer);

    EXPECT_EQ(poppler_layers_iter_get_child(&parent), nullptr);

}



TEST_F(PopplerLayersIterTest_2249, GetChild_ReturnsValidPointerForValidKids_2249) {

    Layer layer;

    layer.kids = g_list_prepend(layer.kids, reinterpret_cast<gpointer>(0x1)); // One kid available

    parent.items = g_list_prepend(parent.items, &layer);

    EXPECT_NE(poppler_layers_iter_get_child(&parent), nullptr);

}



TEST_F(PopplerLayersIterTest_2249, GetChild_ReturnsNullForNullParent_2249) {

    EXPECT_EQ(poppler_layers_iter_get_child(nullptr), nullptr);

}



}  // namespace
