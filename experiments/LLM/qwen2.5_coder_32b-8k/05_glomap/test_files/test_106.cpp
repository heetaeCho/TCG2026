#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "global_positioning.h"

#include "image.h"

#include "view_graph.h"



using namespace glomap;



class GlobalPositionerTest_106 : public ::testing::Test {

protected:

    GlobalPositionerOptions options;

    std::shared_ptr<ceres::LossFunction> loss_function = std::make_shared<ceres::HuberLoss>(1.0);

    GlobalPositioner global_positioner{options};

};



TEST_F(GlobalPositionerTest_106, AddCameraToCameraConstraints_NoImages_106) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;



    global_positioner.AddCameraToCameraConstraints(view_graph, images);



    // No constraints should be added if there are no images.

    EXPECT_EQ(global_positioner.scales_.size(), 0);

}



TEST_F(GlobalPositionerTest_106, AddCameraToCameraConstraints_NoValidImagePairs_106) {

    ViewGraph view_graph;

    Image image1{1, 1, "image1"};

    Image image2{2, 2, "image2"};

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};

    ImagePair invalid_pair{1, 2};

    invalid_pair.is_valid = false;

    view_graph.image_pairs[0] = invalid_pair;



    global_positioner.AddCameraToCameraConstraints(view_graph, images);



    // No constraints should be added if all image pairs are invalid.

    EXPECT_EQ(global_positioner.scales_.size(), 0);

}



TEST_F(GlobalPositionerTest_106, AddCameraToCameraConstraints_UnregisteredImage_106) {

    ViewGraph view_graph;

    Image image1{1, 1, "image1"};

    Image image2{2, 2, "image2"};

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};

    ImagePair valid_pair{1, 2};

    view_graph.image_pairs[0] = valid_pair;



    // Mock IsRegistered to return false for both images.

    ON_CALL(image1, IsRegistered()).WillByDefault(::testing::Return(false));

    ON_CALL(image2, IsRegistered()).WillByDefault(::testing::Return(false));



    global_positioner.AddCameraToCameraConstraints(view_graph, images);



    // No constraints should be added if all images are unregistered.

    EXPECT_EQ(global_positioner.scales_.size(), 0);

}



TEST_F(GlobalPositionerTest_106, AddCameraToCameraConstraints_NonTrivialFrame_106) {

    ViewGraph view_graph;

    Image image1{1, 1, "image1"};

    Image image2{2, 2, "image2"};

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};

    ImagePair valid_pair{1, 2};

    view_graph.image_pairs[0] = valid_pair;



    // Mock IsRegistered to return true for both images.

    ON_CALL(image1, IsRegistered()).WillByDefault(::testing::Return(true));

    ON_CALL(image2, IsRegistered()).WillByDefault(::testing::Return(true));



    // Mock HasTrivialFrame to return false for one of the images.

    ON_CALL(image1, HasTrivialFrame()).WillByDefault(::testing::Return(false));



    global_positioner.AddCameraToCameraConstraints(view_graph, images);



    // No constraints should be added if any image has a non-trivial frame.

    EXPECT_EQ(global_positioner.scales_.size(), 0);

}



TEST_F(GlobalPositionerTest_106, AddCameraToCameraConstraints_ValidConstraintsAdded_106) {

    ViewGraph view_graph;

    Image image1{1, 1, "image1"};

    Image image2{2, 2, "image2"};

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};

    ImagePair valid_pair{1, 2};

    view_graph.image_pairs[0] = valid_pair;



    // Mock IsRegistered to return true for both images.

    ON_CALL(image1, IsRegistered()).WillByDefault(::testing::Return(true));

    ON_CALL(image2, IsRegistered()).WillByDefault(::testing::Return(true));



    // Mock HasTrivialFrame to return true for both images.

    ON_CALL(image1, HasTrivialFrame()).WillByDefault(::testing::Return(true));

    ON_CALL(image2, HasTrivialFrame()).WillByDefault(::testing::Return(true));



    global_positioner.AddCameraToCameraConstraints(view_graph, images);



    // Constraints should be added if all conditions are met.

    EXPECT_EQ(global_positioner.scales_.size(), 1);

}



TEST_F(GlobalPositionerTest_106, AddCameraToCameraConstraints_BoundaryConditionSingleImage_106) {

    ViewGraph view_graph;

    Image image{1, 1, "image1"};

    std::unordered_map<image_t, Image> images = {{1, image}};

    ImagePair valid_pair{1, 2};

    view_graph.image_pairs[0] = valid_pair;



    // Mock IsRegistered to return true for the image.

    ON_CALL(image, IsRegistered()).WillByDefault(::testing::Return(true));



    // Mock HasTrivialFrame to return true for the image.

    ON_CALL(image, HasTrivialFrame()).WillByDefault(::testing::Return(true));



    global_positioner.AddCameraToCameraConstraints(view_graph, images);



    // No constraints should be added if there is only one image.

    EXPECT_EQ(global_positioner.scales_.size(), 0);

}



TEST_F(GlobalPositionerTest_106, AddCameraToCameraConstraints_ScaleCapacityCheck_106) {

    ViewGraph view_graph;

    Image image1{1, 1, "image1"};

    Image image2{2, 2, "image2"};

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};

    ImagePair valid_pair{1, 2};

    view_graph.image_pairs[0] = valid_pair;



    // Mock IsRegistered to return true for both images.

    ON_CALL(image1, IsRegistered()).WillByDefault(::testing::Return(true));

    ON_CALL(image2, IsRegistered()).WillByDefault(::testing::Return(true));



    // Mock HasTrivialFrame to return true for both images.

    ON_CALL(image1, HasTrivialFrame()).WillByDefault(::testing::Return(true));

    ON_CALL(image2, HasTrivialFrame()).WillByDefault(::testing::Return(true));



    global_positioner.scales_.reserve(1);  // Reserve enough capacity



    global_positioner.AddCameraToCameraConstraints(view_graph, images);



    // Constraints should be added if scale capacity is sufficient.

    EXPECT_EQ(global_positioner.scales_.size(), 1);

}
