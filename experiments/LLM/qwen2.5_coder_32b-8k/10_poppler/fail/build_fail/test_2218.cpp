#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking the necessary structures and functions for testing.

struct _PopplerIndexIter {

    const int * items;

    size_t index;

};



extern "C" gboolean poppler_index_iter_next(PopplerIndexIter *iter);



class PopplerIndexIterTest_2218 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a sample array for testing.

        static const int sampleItems[] = {1, 2, 3};

        iter.items = sampleItems;

        iter.index = 0;

    }



    PopplerIndexIter iter;

};



TEST_F(PopplerIndexIterTest_2218, NextReturnsTrueForFirstItem_2218) {

    EXPECT_TRUE(poppler_index_iter_next(&iter));

}



TEST_F(PopplerIndexIterTest_2218, NextIncrementsIndex_2218) {

    poppler_index_iter_next(&iter);

    EXPECT_EQ(iter.index, 1);

}



TEST_F(PopplerIndexIterTest_2218, NextReturnsTrueForSecondItem_2218) {

    poppler_index_iter_next(&iter);

    EXPECT_TRUE(poppler_index_iter_next(&iter));

}



TEST_F(PopplerIndexIterTest_2218, NextReturnsFalseWhenAtEnd_2218) {

    poppler_index_iter_next(&iter);

    poppler_index_iter_next(&iter);

    poppler_index_iter_next(&iter);

    EXPECT_FALSE(poppler_index_iter_next(&iter));

}



TEST_F(PopplerIndexIterTest_2218, NextDoesNotIncrementPastEnd_2218) {

    poppler_index_iter_next(&iter);

    poppler_index_iter_next(&iter);

    poppler_index_iter_next(&iter);

    EXPECT_FALSE(poppler_index_iter_next(&iter));

    EXPECT_EQ(iter.index, 3);

}



TEST_F(PopplerIndexIterTest_2218, NullIteratorReturnsFalse_2218) {

    PopplerIndexIter* nullIter = nullptr;

    EXPECT_FALSE(poppler_index_iter_next(nullIter));

}
