#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-document.h"

}



class PopplerLayersIterTest_2252 : public ::testing::Test {

protected:

    void SetUp() override {

        iter = static_cast<PopplerLayersIter*>(g_malloc0(sizeof(PopplerLayersIter)));

        iter->items = g_list_append(iter->items, nullptr);

        iter->items = g_list_append(iter->items, nullptr);

        iter->index = 0;

    }



    void TearDown() override {

        g_list_free(iter->items);

        g_free(iter);

    }



    PopplerLayersIter* iter;

};



TEST_F(PopplerLayersIterTest_2252, InitialIndexIsZero_2252) {

    EXPECT_EQ(iter->index, 0);

}



TEST_F(PopplerLayersIterTest_2252, NextIncrementsIndex_2252) {

    EXPECT_TRUE(poppler_layers_iter_next(iter));

    EXPECT_EQ(iter->index, 1);

}



TEST_F(PopplerLayersIterTest_2252, NextReturnsTrueForValidNextItem_2252) {

    EXPECT_TRUE(poppler_layers_iter_next(iter));

}



TEST_F(PopplerLayersIterTest_2252, NextReturnsFalseWhenAtEnd_2252) {

    poppler_layers_iter_next(iter);

    poppler_layers_iter_next(iter);

    EXPECT_FALSE(poppler_layers_iter_next(iter));

}



TEST_F(PopplerLayersIterTest_2252, NextDoesNotIncrementPastEnd_2252) {

    poppler_layers_iter_next(iter);

    poppler_layers_iter_next(iter);

    EXPECT_FALSE(poppler_layers_iter_next(iter));

    EXPECT_EQ(iter->index, 2);

}



TEST_F(PopplerLayersIterTest_2252, NullIterReturnsFalse_2252) {

    EXPECT_FALSE(poppler_layers_iter_next(nullptr));

}
