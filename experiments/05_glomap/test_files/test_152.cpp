#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/processors/relpose_filter.h"

#include "./TestProjects/glomap/glomap/scene/image.h"

#include "./TestProjects/glomap/glomap/scene/image_pair.h"

#include "./TestProjects/glomap/glomap/scene/view_graph.h"



namespace glomap {

using namespace testing;



// Mock Image class to control behavior of IsRegistered and CamFromWorld

class MockImage : public Image {

public:

    MOCK_METHOD(bool, IsRegistered, (), (const, override));

    MOCK_METHOD(Rigid3d, CamFromWorld, (), (const, override));

};



TEST_F(RelPoseFilterTest_152, FilterRotations_NoInvalidRotations_152) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;



    image_t img_id1 = 1, img_id2 = 2;

    auto mock_image1 = std::make_shared<MockImage>();

    auto mock_image2 = std::make_shared<MockImage>();



    EXPECT_CALL(*mock_image1, IsRegistered()).WillOnce(Return(true));

    EXPECT_CALL(*mock_image2, IsRegistered()).WillOnce(Return(true));



    Rigid3d cam_from_world1, cam_from_world2;

    cam_from_world1.SetRotation(Eigen::Quaterniond::Identity());

    cam_from_world2.SetRotation(Eigen::Quaterniond::Identity());



    EXPECT_CALL(*mock_image1, CamFromWorld()).WillRepeatedly(Return(cam_from_world1));

    EXPECT_CALL(*mock_image2, CamFromWorld()).WillRepeatedly(Return(cam_from_world2));



    images[img_id1] = *mock_image1;

    images[img_id2] = *mock_image2;



    image_pair_t pair_id = 3;

    ImagePair image_pair(img_id1, img_id2);

    view_graph.image_pairs[pair_id] = image_pair;



    double max_angle = 10.0;

    RelPoseFilter::FilterRotations(view_graph, images, max_angle);



    EXPECT_TRUE(view_graph.image_pairs.at(pair_id).is_valid);

}



TEST_F(RelPoseFilterTest_152, FilterRotations_AllInvalidRotations_152) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;



    image_t img_id1 = 1, img_id2 = 2;

    auto mock_image1 = std::make_shared<MockImage>();

    auto mock_image2 = std::make_shared<MockImage>();



    EXPECT_CALL(*mock_image1, IsRegistered()).WillOnce(Return(true));

    EXPECT_CALL(*mock_image2, IsRegistered()).WillOnce(Return(true));



    Rigid3d cam_from_world1, cam_from_world2;

    cam_from_world1.SetRotation(Eigen::Quaterniond::Identity());

    cam_from_world2.SetRotation(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitZ()));



    EXPECT_CALL(*mock_image1, CamFromWorld()).WillRepeatedly(Return(cam_from_world1));

    EXPECT_CALL(*mock_image2, CamFromWorld()).WillRepeatedly(Return(cam_from_world2));



    images[img_id1] = *mock_image1;

    images[img_id2] = *mock_image2;



    image_pair_t pair_id = 3;

    ImagePair image_pair(img_id1, img_id2);

    view_graph.image_pairs[pair_id] = image_pair;



    double max_angle = 5.0;

    RelPoseFilter::FilterRotations(view_graph, images, max_angle);



    EXPECT_FALSE(view_graph.image_pairs.at(pair_id).is_valid);

}



TEST_F(RelPoseFilterTest_152, FilterRotations_UnregisteredImages_152) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;



    image_t img_id1 = 1, img_id2 = 2;

    auto mock_image1 = std::make_shared<MockImage>();

    auto mock_image2 = std::make_shared<MockImage>();



    EXPECT_CALL(*mock_image1, IsRegistered()).WillOnce(Return(false));

    EXPECT_CALL(*mock_image2, IsRegistered()).WillOnce(Return(true));



    images[img_id1] = *mock_image1;

    images[img_id2] = *mock_image2;



    image_pair_t pair_id = 3;

    ImagePair image_pair(img_id1, img_id2);

    view_graph.image_pairs[pair_id] = image_pair;



    double max_angle = 5.0;

    RelPoseFilter::FilterRotations(view_graph, images, max_angle);



    EXPECT_TRUE(view_graph.image_pairs.at(pair_id).is_valid); // No change if either image is unregistered

}



TEST_F(RelPoseFilterTest_152, FilterRotations_MaxAngleZero_152) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;



    image_t img_id1 = 1, img_id2 = 2;

    auto mock_image1 = std::make_shared<MockImage>();

    auto mock_image2 = std::make_shared<MockImage>();



    EXPECT_CALL(*mock_image1, IsRegistered()).WillOnce(Return(true));

    EXPECT_CALL(*mock_image2, IsRegistered()).WillOnce(Return(true));



    Rigid3d cam_from_world1, cam_from_world2;

    cam_from_world1.SetRotation(Eigen::Quaterniond::Identity());

    cam_from_world2.SetRotation(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()));



    EXPECT_CALL(*mock_image1, CamFromWorld()).WillRepeatedly(Return(cam_from_world1));

    EXPECT_CALL(*mock_image2, CamFromWorld()).WillRepeatedly(Return(cam_from_world2));



    images[img_id1] = *mock_image1;

    images[img_id2] = *mock_image2;



    image_pair_t pair_id = 3;

    ImagePair image_pair(img_id1, img_id2);

    view_graph.image_pairs[pair_id] = image_pair;



    double max_angle = 0.0;

    RelPoseFilter::FilterRotations(view_graph, images, max_angle);



    EXPECT_FALSE(view_graph.image_pairs.at(pair_id).is_valid); // All rotations are invalid if max_angle is zero

}



TEST_F(RelPoseFilterTest_152, FilterRotations_MultiplePairs_152) {

    ViewGraph view_graph;

    std::unordered_map<image_t, Image> images;



    image_t img_id1 = 1, img_id2 = 2, img_id3 = 3;

    auto mock_image1 = std::make_shared<MockImage>();

    auto mock_image2 = std::make_shared<MockImage>();

    auto mock_image3 = std::make_shared<MockImage>();



    EXPECT_CALL(*mock_image1, IsRegistered()).WillRepeatedly(Return(true));

    EXPECT_CALL(*mock_image2, IsRegistered()).WillRepeatedly(Return(true));

    EXPECT_CALL(*mock_image3, IsRegistered()).WillRepeatedly(Return(true));



    Rigid3d cam_from_world1, cam_from_world2, cam_from_world3;

    cam_from_world1.SetRotation(Eigen::Quaterniond::Identity());

    cam_from_world2.SetRotation(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()));

    cam_from_world3.SetRotation(Eigen::AngleAxisd(0.2, Eigen::Vector3d::UnitZ()));



    EXPECT_CALL(*mock_image1, CamFromWorld()).WillRepeatedly(Return(cam_from_world1));

    EXPECT_CALL(*mock_image2, CamFromWorld()).WillRepeatedly(Return(cam_from_world2));

    EXPECT_CALL(*mock_image3, CamFromWorld()).WillRepeatedly(Return(cam_from_world3));



    images[img_id1] = *mock_image1;

    images[img_id2] = *mock_image2;

    images[img_id3] = *mock_image3;



    image_pair_t pair_id1 = 3, pair_id2 = 4;

    ImagePair image_pair1(img_id1, img_id2);

    ImagePair image_pair2(img_id2, img_id3);



    view_graph.image_pairs[pair_id1] = image_pair1;

    view_graph.image_pairs[pair_id2] = image_pair2;



    double max_angle = 0.15;

    RelPoseFilter::FilterRotations(view_graph, images, max_angle);



    EXPECT_FALSE(view_graph.image_pairs.at(pair_id1).is_valid); // First pair is invalid

    EXPECT_TRUE(view_graph.image_pairs.at(pair_id2).is_valid); // Second pair is valid

}



}  // namespace glomap
