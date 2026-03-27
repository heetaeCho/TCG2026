#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.h"



// Assuming poppler_dest_free is available for cleanup

extern "C" void poppler_dest_free(PopplerDest *dest);



class PopplerDestTest_2283 : public ::testing::Test {

protected:

    void SetUp() override {

        original_dest = static_cast<PopplerDest*>(g_slice_alloc0(sizeof(PopplerDest)));

        original_dest->type = POPPLER_DEST_XYZ;

        original_dest->page_num = 1;

        original_dest->named_dest = g_strdup("example_dest");

        original_dest->change_left = 100;

        original_dest->change_top = 200;

        original_dest->change_zoom = 1.5;

    }



    void TearDown() override {

        poppler_dest_free(original_dest);

        if (copied_dest) {

            poppler_dest_free(copied_dest);

        }

    }



    PopplerDest *original_dest = nullptr;

    PopplerDest *copied_dest = nullptr;

};



TEST_F(PopplerDestTest_2283, CopyPreservesAllFields_2283) {

    copied_dest = poppler_dest_copy(original_dest);



    EXPECT_EQ(copied_dest->type, original_dest->type);

    EXPECT_EQ(copied_dest->page_num, original_dest->page_num);

    EXPECT_STREQ(copied_dest->named_dest, original_dest->named_dest);

    EXPECT_EQ(copied_dest->change_left, original_dest->change_left);

    EXPECT_EQ(copied_dest->change_top, original_dest->change_top);

    EXPECT_FLOAT_EQ(copied_dest->change_zoom, original_dest->change_zoom);

}



TEST_F(PopplerDestTest_2283, CopyWithNullNamedDest_2283) {

    g_free(original_dest->named_dest);

    original_dest->named_dest = nullptr;



    copied_dest = poppler_dest_copy(original_dest);



    EXPECT_EQ(copied_dest->type, original_dest->type);

    EXPECT_EQ(copied_dest->page_num, original_dest->page_num);

    EXPECT_EQ(copied_dest->named_dest, original_dest->named_dest); // Both should be nullptr

    EXPECT_EQ(copied_dest->change_left, original_dest->change_left);

    EXPECT_EQ(copied_dest->change_top, original_dest->change_top);

    EXPECT_FLOAT_EQ(copied_dest->change_zoom, original_dest->change_zoom);

}



TEST_F(PopplerDestTest_2283, CopyWithEmptyNamedDest_2283) {

    g_free(original_dest->named_dest);

    original_dest->named_dest = g_strdup("");



    copied_dest = poppler_dest_copy(original_dest);



    EXPECT_EQ(copied_dest->type, original_dest->type);

    EXPECT_EQ(copied_dest->page_num, original_dest->page_num);

    EXPECT_STREQ(copied_dest->named_dest, original_dest->named_dest); // Both should be ""

    EXPECT_EQ(copied_dest->change_left, original_dest->change_left);

    EXPECT_EQ(copied_dest->change_top, original_dest->change_top);

    EXPECT_FLOAT_EQ(copied_dest->change_zoom, original_dest->change_zoom);

}
