#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



class PopplerFontsIterTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a sample PopplerFontsIter for testing

        iter = static_cast<PopplerFontsIter*>(g_slice_alloc(sizeof(PopplerFontsIter)));

        iter->items.resize(3);  // Example size

        for (std::size_t i = 0; i < iter->items.size(); ++i) {

            iter->items[i] = new FontInfo();

        }

    }



    void TearDown() override {

        // Clean up allocated memory

        for (FontInfo* info : iter->items) {

            delete info;

        }

        g_slice_free(PopplerFontsIter, iter);

    }



    PopplerFontsIter* iter;

};



TEST_F(PopplerFontsIterTest_2229, CopyNonNullIter_2229) {

    PopplerFontsIter* new_iter = poppler_fonts_iter_copy(iter);

    ASSERT_NE(new_iter, nullptr);



    EXPECT_EQ(new_iter->items.size(), iter->items.size());

    for (std::size_t i = 0; i < new_iter->items.size(); ++i) {

        EXPECT_NE(new_iter->items[i], iter->items[i]); // Different pointers

    }



    // Clean up the copied iterator

    for (FontInfo* info : new_iter->items) {

        delete info;

    }

    g_slice_free(PopplerFontsIter, new_iter);

}



TEST_F(PopplerFontsIterTest_2229, CopyNullIter_2229) {

    PopplerFontsIter* null_iter = nullptr;

    PopplerFontsIter* new_iter = poppler_fonts_iter_copy(null_iter);

    EXPECT_EQ(new_iter, nullptr);

}
