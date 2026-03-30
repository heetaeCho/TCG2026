#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "poppler-document.h"

}



class PopplerFontsIterTest_2228 : public ::testing::Test {

protected:

    void SetUp() override {

        iter = reinterpret_cast<PopplerFontsIter*>(malloc(sizeof(PopplerFontsIter)));

        iter->index = 0;

        iter->items.size = 3;  // Simulating 3 items for testing

    }



    void TearDown() override {

        free(iter);

    }



    PopplerFontsIter* iter;

};



TEST_F(PopplerFontsIterTest_2228, InitialIndexIsZero_2228) {

    EXPECT_EQ(iter->index, 0);

}



TEST_F(PopplerFontsIterTest_2228, NextReturnsTrueForFirstItem_2228) {

    EXPECT_TRUE(poppler_fonts_iter_next(iter));

    EXPECT_EQ(iter->index, 1);

}



TEST_F(PopplerFontsIterTest_2228, IteratesThroughAllItems_2228) {

    for (int i = 0; i < iter->items.size - 1; ++i) {

        EXPECT_TRUE(poppler_fonts_iter_next(iter));

    }

    EXPECT_FALSE(poppler_fonts_iter_next(iter));

}



TEST_F(PopplerFontsIterTest_2228, ReturnsFalseWhenNoMoreItems_2228) {

    for (int i = 0; i < iter->items.size; ++i) {

        poppler_fonts_iter_next(iter);

    }

    EXPECT_FALSE(poppler_fonts_iter_next(iter));

}



TEST_F(PopplerFontsIterTest_2228, HandlesNullPointer_2228) {

    EXPECT_FALSE(poppler_fonts_iter_next(nullptr));

}
