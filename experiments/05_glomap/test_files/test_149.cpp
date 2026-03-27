#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/processors/image_pair_inliers.h"

#include "glomap/scene/view_graph.h"

#include "glomap/types.h"



using namespace glomap;

using testing::ElementsAre;



class ImagePairsInlierCountTest_149 : public ::testing::Test {

protected:

    ViewGraph view_graph_;

    std::unordered_map<camera_t, Camera> cameras_;

    std::unordered_map<image_t, Image> images_;

    InlierThresholdOptions options_;

};



TEST_F(ImagePairsInlierCountTest_149, NoImagePairs_149) {

    // Given: An empty view_graph

    // When: Calling ImagePairsInlierCount with clean_inliers = false

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false);

    // Then: No changes should occur as there are no image pairs

    EXPECT_TRUE(view_graph_.image_pairs.empty());

}



TEST_F(ImagePairsInlierCountTest_149, SingleValidImagePairWithInliers_CleanFalse_149) {

    // Given: A single valid image pair with inliers and clean_inliers = false

    ImagePair image_pair(1, 2);

    image_pair.inliers = {1, 2, 3};

    view_graph_.image_pairs[0] = image_pair;



    // When: Calling ImagePairsInlierCount with clean_inliers = false

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false);



    // Then: The inliers should not be cleared as clean_inliers is false

    EXPECT_EQ(view_graph_.image_pairs[0].inliers, ElementsAre(1, 2, 3));

}



TEST_F(ImagePairsInlierCountTest_149, SingleValidImagePairWithInliers_CleanTrue_149) {

    // Given: A single valid image pair with inliers and clean_inliers = true

    ImagePair image_pair(1, 2);

    image_pair.inliers = {1, 2, 3};

    view_graph_.image_pairs[0] = image_pair;



    // When: Calling ImagePairsInlierCount with clean_inliers = true

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true);



    // Then: The inliers should be cleared as clean_inliers is true

    EXPECT_TRUE(view_graph_.image_pairs[0].inliers.empty());

}



TEST_F(ImagePairsInlierCountTest_149, SingleInvalidImagePair_CleanFalse_149) {

    // Given: A single invalid image pair and clean_inliers = false

    ImagePair image_pair(1, 2);

    image_pair.is_valid = false;

    view_graph_.image_pairs[0] = image_pair;



    // When: Calling ImagePairsInlierCount with clean_inliers = false

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false);



    // Then: The inliers should not be cleared as the pair is invalid

    EXPECT_TRUE(view_graph_.image_pairs[0].inliers.empty());

}



TEST_F(ImagePairsInlierCountTest_149, SingleInvalidImagePair_CleanTrue_149) {

    // Given: A single invalid image pair and clean_inliers = true

    ImagePair image_pair(1, 2);

    image_pair.is_valid = false;

    view_graph_.image_pairs[0] = image_pair;



    // When: Calling ImagePairsInlierCount with clean_inliers = true

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true);



    // Then: The inliers should not be cleared as the pair is invalid

    EXPECT_TRUE(view_graph_.image_pairs[0].inliers.empty());

}



TEST_F(ImagePairsInlierCountTest_149, MultipleImagePairsWithInliers_CleanFalse_149) {

    // Given: Multiple image pairs with inliers and clean_inliers = false

    ImagePair image_pair1(1, 2);

    image_pair1.inliers = {1, 2, 3};

    view_graph_.image_pairs[0] = image_pair1;



    ImagePair image_pair2(3, 4);

    image_pair2.inliers = {4, 5, 6};

    view_graph_.image_pairs[1] = image_pair2;



    // When: Calling ImagePairsInlierCount with clean_inliers = false

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false);



    // Then: The inliers should not be cleared as clean_inliers is false

    EXPECT_EQ(view_graph_.image_pairs[0].inliers, ElementsAre(1, 2, 3));

    EXPECT_EQ(view_graph_.image_pairs[1].inliers, ElementsAre(4, 5, 6));

}



TEST_F(ImagePairsInlierCountTest_149, MultipleImagePairsWithInliers_CleanTrue_149) {

    // Given: Multiple image pairs with inliers and clean_inliers = true

    ImagePair image_pair1(1, 2);

    image_pair1.inliers = {1, 2, 3};

    view_graph_.image_pairs[0] = image_pair1;



    ImagePair image_pair2(3, 4);

    image_pair2.inliers = {4, 5, 6};

    view_graph_.image_pairs[1] = image_pair2;



    // When: Calling ImagePairsInlierCount with clean_inliers = true

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true);



    // Then: The inliers should be cleared as clean_inliers is true

    EXPECT_TRUE(view_graph_.image_pairs[0].inliers.empty());

    EXPECT_TRUE(view_graph_.image_pairs[1].inliers.empty());

}



TEST_F(ImagePairsInlierCountTest_149, MixedValidAndInvalidImagePairs_CleanFalse_149) {

    // Given: Mixed valid and invalid image pairs with inliers and clean_inliers = false

    ImagePair valid_image_pair(1, 2);

    valid_image_pair.inliers = {1, 2, 3};

    view_graph_.image_pairs[0] = valid_image_pair;



    ImagePair invalid_image_pair(3, 4);

    invalid_image_pair.is_valid = false;

    invalid_image_pair.inliers = {4, 5, 6};

    view_graph_.image_pairs[1] = invalid_image_pair;



    // When: Calling ImagePairsInlierCount with clean_inliers = false

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, false);



    // Then: The inliers should not be cleared as clean_inliers is false and the valid pair's inliers are retained

    EXPECT_EQ(view_graph_.image_pairs[0].inliers, ElementsAre(1, 2, 3));

    EXPECT_TRUE(view_graph_.image_pairs[1].inliers.empty());

}



TEST_F(ImagePairsInlierCountTest_149, MixedValidAndInvalidImagePairs_CleanTrue_149) {

    // Given: Mixed valid and invalid image pairs with inliers and clean_inliers = true

    ImagePair valid_image_pair(1, 2);

    valid_image_pair.inliers = {1, 2, 3};

    view_graph_.image_pairs[0] = valid_image_pair;



    ImagePair invalid_image_pair(3, 4);

    invalid_image_pair.is_valid = false;

    invalid_image_pair.inliers = {4, 5, 6};

    view_graph_.image_pairs[1] = invalid_image_pair;



    // When: Calling ImagePairsInlierCount with clean_inliers = true

    ImagePairsInlierCount(view_graph_, cameras_, images_, options_, true);



    // Then: The inliers should be cleared as clean_inliers is true, and the valid pair's inliers are cleared

    EXPECT_TRUE(view_graph_.image_pairs[0].inliers.empty());

    EXPECT_TRUE(view_graph_.image_pairs[1].inliers.empty());

}
