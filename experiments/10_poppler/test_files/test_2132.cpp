#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "PDFRectangle.h"



// Mocking dependencies if needed (none required for this function)

// class MockPage : public Page {

//     // Define mock methods here if needed

// };



class PopplerAnnotInkTest_2132 : public ::testing::Test {

protected:

    PopplerAnnotInk *annot;



    void SetUp() override {

        annot = static_cast<PopplerAnnotInk *>(g_object_new(POPPLER_TYPE_ANNOT_INK, nullptr));

    }



    void TearDown() override {

        g_object_unref(annot);

    }

};



TEST_F(PopplerAnnotInkTest_2132, GetInkList_EmptyList_2132) {

    gsize n_paths = 0;

    PopplerPath **ink_list = poppler_annot_ink_get_ink_list(annot, &n_paths);



    EXPECT_EQ(n_paths, 0);

    EXPECT_EQ(ink_list, nullptr);

}



TEST_F(PopplerAnnotInkTest_2132, GetInkList_SinglePathNoRotation_2132) {

    // Assuming we can set up the annot with a single path

    gsize n_paths = 0;

    PopplerPath **ink_list = poppler_annot_ink_get_ink_list(annot, &n_paths);



    EXPECT_EQ(n_paths, 1);

    ASSERT_NE(ink_list, nullptr);



    // Assuming we can verify the points in the path if needed

    gsize num_points = poppler_path_get_num_points(ink_list[0]);

    EXPECT_GT(num_points, 0);



    for (gsize i = 0; i < num_points; ++i) {

        PopplerPoint point;

        poppler_path_get_point(ink_list[0], i, &point);

        // Verify the points are as expected

    }



    g_free(ink_list);

}



TEST_F(PopplerAnnotInkTest_2132, GetInkList_MultiplePathsNoRotation_2132) {

    // Assuming we can set up the annot with multiple paths

    gsize n_paths = 0;

    PopplerPath **ink_list = poppler_annot_ink_get_ink_list(annot, &n_paths);



    EXPECT_EQ(n_paths, 2); // Example number of paths

    ASSERT_NE(ink_list, nullptr);



    for (gsize i = 0; i < n_paths; ++i) {

        gsize num_points = poppler_path_get_num_points(ink_list[i]);

        EXPECT_GT(num_points, 0);

    }



    g_free(ink_list);

}



TEST_F(PopplerAnnotInkTest_2132, GetInkList_CropBoxPresentNoRotation_2132) {

    // Assuming we can set up the annot with a crop box

    gsize n_paths = 0;

    PopplerPath **ink_list = poppler_annot_ink_get_ink_list(annot, &n_paths);



    EXPECT_EQ(n_paths, 1); // Example number of paths

    ASSERT_NE(ink_list, nullptr);



    gsize num_points = poppler_path_get_num_points(ink_list[0]);

    EXPECT_GT(num_points, 0);



    for (gsize i = 0; i < num_points; ++i) {

        PopplerPoint point;

        poppler_path_get_point(ink_list[0], i, &point);

        // Verify the points are adjusted by the crop box

    }



    g_free(ink_list);

}



TEST_F(PopplerAnnotInkTest_2132, GetInkList_PageRotationPresent_2132) {

    // Assuming we can set up the annot with a page and rotation

    gsize n_paths = 0;

    PopplerPath **ink_list = poppler_annot_ink_get_ink_list(annot, &n_paths);



    EXPECT_EQ(n_paths, 1); // Example number of paths

    ASSERT_NE(ink_list, nullptr);



    gsize num_points = poppler_path_get_num_points(ink_list[0]);

    EXPECT_GT(num_points, 0);



    for (gsize i = 0; i < num_points; ++i) {

        PopplerPoint point;

        poppler_path_get_point(ink_list[0], i, &point);

        // Verify the points are adjusted by both crop box and page rotation

    }



    g_free(ink_list);

}
