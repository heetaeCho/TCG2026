#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "global_rotation_averaging.h"

#include "view_graph.h"



using namespace glomap;

using ::testing::UnorderedElementsAre;



class RotationEstimatorTest : public ::testing::Test {

protected:

    void SetUp() override {

        options = RotationEstimatorOptions();

        rotation_estimator = std::make_unique<RotationEstimator>(options);

    }



    RotationEstimatorOptions options;

    std::unique_ptr<RotationEstimator> rotation_estimator;

};



TEST_F(RotationEstimatorTest_31, ComputeResiduals_HasGravity_31) {

    ViewGraph view_graph;

    Image image1, image2;



    image_t image_id1 = 1;

    image_t image_id2 = 2;

    image_pair_t pair_id = std::make_pair(image_id1, image_id2);



    view_graph.image_pairs[pair_id].image_id1 = image_id1;

    view_graph.image_pairs[pair_id].image_id2 = image_id2;



    view_graph.image_pairs[pair_id].has_gravity = true;

    view_graph.image_pairs[pair_id].angle_rel = 0.5;



    rotation_estimator->rotation_estimated_.resize(3);

    rotation_estimator->rotation_estimated_ << 0, 0, 0;



    std::unordered_map<image_t, Image> images;

    images[image_id1] = image1;

    images[image_id2] = image2;



    images[image_id1].SetGravity(true);

    images[image_id2].SetGravity(true);



    rotation_estimator->ComputeResiduals(view_graph, images);



    EXPECT_TRUE(std::abs(rotation_estimator->tangent_space_residual_[0]) < 1e-6);

}



TEST_F(RotationEstimatorTest_31, ComputeResiduals_NoGravity_31) {

    ViewGraph view_graph;

    Image image1, image2;



    image_t image_id1 = 1;

    image_t image_id2 = 2;

    image_pair_t pair_id = std::make_pair(image_id1, image_id2);



    view_graph.image_pairs[pair_id].image_id1 = image_id1;

    view_graph.image_pairs[pair_id].image_id2 = image_id2;



    view_graph.image_pairs[pair_id].has_gravity = false;

    view_graph.image_pairs[pair_id].R_rel = Eigen::Matrix3d::Identity();



    rotation_estimator->rotation_estimated_.resize(6);

    rotation_estimator->rotation_estimated_ << 0, 0, 0, 1, 0, 0;



    std::unordered_map<image_t, Image> images;

    images[image_id1] = image1;

    images[image_id2] = image2;



    rotation_estimator->ComputeResiduals(view_graph, images);



    EXPECT_TRUE(rotation_estimator->tangent_space_residual_.segment(0, 3).norm() < 1e-6);

}



TEST_F(RotationEstimatorTest_31, ComputeResiduals_NoImagePairs_31) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;



    rotation_estimator->ComputeResiduals(view_graph, images);



    EXPECT_EQ(rotation_estimator->tangent_space_residual_.size(), 0);

}



TEST_F(RotationEstimatorTest_31, ComputeResiduals_BoundaryCondition_EmptyImagesMap_31) {

    ViewGraph view_graph;

    Image image1;



    image_t image_id1 = 1;

    image_t image_id2 = 2;

    image_pair_t pair_id = std::make_pair(image_id1, image_id2);



    view_graph.image_pairs[pair_id].image_id1 = image_id1;

    view_graph.image_pairs[pair_id].image_id2 = image_id2;



    rotation_estimator->rotation_estimated_.resize(3);

    rotation_estimator->rotation_estimated_ << 0, 0, 0;



    std::unordered_map<image_t, Image> images;



    EXPECT_THROW(rotation_estimator->ComputeResiduals(view_graph, images), ...); // Replace '...' with appropriate exception type

}



TEST_F(RotationEstimatorTest_31, ComputeResiduals_BoundaryCondition_EmptyRotationEstimated_31) {

    ViewGraph view_graph;

    Image image1, image2;



    image_t image_id1 = 1;

    image_t image_id2 = 2;

    image_pair_t pair_id = std::make_pair(image_id1, image_id2);



    view_graph.image_pairs[pair_id].image_id1 = image_id1;

    view_graph.image_pairs[pair_id].image_id2 = image_id2;



    rotation_estimator->rotation_estimated_.resize(0); // Empty



    std::unordered_map<image_t, Image> images;

    images[image_id1] = image1;

    images[image_id2] = image2;



    EXPECT_THROW(rotation_estimator->ComputeResiduals(view_graph, images), ...); // Replace '...' with appropriate exception type

}

```


