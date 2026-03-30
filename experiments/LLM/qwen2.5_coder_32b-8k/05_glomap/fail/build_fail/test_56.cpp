#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "colmap/base/database.h"

#include "glomap/controllers/track_retriangulation.cc"



using ::testing::_;

using ::testing::Return;



namespace glomap {



class MockDatabase : public colmap::Database {

public:

    MOCK_METHOD(bool, ExistsImage, (image_t image_id), (const override));

};



struct TriangulatorOptionsMock : public TriangulatorOptions {

    double tri_complete_max_reproj_error = 1.0;

    double tri_merge_max_reproj_error = 2.0;

    double tri_min_angle = 3.0;

    size_t min_num_matches = 5;

    int ba_global_max_refinements = 3;

    double ba_global_max_refinement_change = 0.1;

};



class RetriangulateTracksTest_56 : public ::testing::Test {

protected:

    TriangulatorOptionsMock options_;

    MockDatabase mock_database_;

    std::unordered_map<rig_t, Rig> rigs_;

    std::unordered_map<camera_t, Camera> cameras_;

    std::unordered_map<frame_t, Frame> frames_;

    std::unordered_map<image_t, Image> images_;

    std::unordered_map<track_t, Track> tracks_;

};



TEST_F(RetriangulateTracksTest_56, NormalOperation_56) {

    image_t image_id = 1;

    Image image;

    image.SetRegistered(true);

    images_.insert({image_id, image});



    EXPECT_CALL(mock_database_, ExistsImage(image_id)).WillOnce(Return(false));



    ASSERT_TRUE(RetriangulateTracks(options_, mock_database_, rigs_, cameras_, frames_, images_, tracks_));

}



TEST_F(RetriangulateTracksTest_56, ImageExistsInDatabase_56) {

    image_t image_id = 1;

    Image image;

    image.SetRegistered(true);

    images_.insert({image_id, image});



    EXPECT_CALL(mock_database_, ExistsImage(image_id)).WillOnce(Return(true));



    ASSERT_TRUE(RetriangulateTracks(options_, mock_database_, rigs_, cameras_, frames_, images_, tracks_));

}



TEST_F(RetriangulateTracksTest_56, ImageNotRegistered_56) {

    image_t image_id = 1;

    Image image;

    image.SetRegistered(false);

    images_.insert({image_id, image});



    EXPECT_CALL(mock_database_, ExistsImage(image_id)).WillOnce(Return(false));



    ASSERT_TRUE(RetriangulateTracks(options_, mock_database_, rigs_, cameras_, frames_, images_, tracks_));

}



TEST_F(RetriangulateTracksTest_56, MultipleImages_56) {

    for (image_t image_id = 1; image_id <= 3; ++image_id) {

        Image image;

        image.SetRegistered(true);

        images_.insert({image_id, image});



        EXPECT_CALL(mock_database_, ExistsImage(image_id)).WillRepeatedly(Return(false));

    }



    ASSERT_TRUE(RetriangulateTracks(options_, mock_database_, rigs_, cameras_, frames_, images_, tracks_));

}



TEST_F(RetriangulateTracksTest_56, BundleAdjustmentFailure_56) {

    image_t image_id = 1;

    Image image;

    image.SetRegistered(true);

    images_.insert({image_id, image});



    EXPECT_CALL(mock_database_, ExistsImage(image_id)).WillOnce(Return(false));



    // Simulate bundle adjustment failure

    options_.ba_global_max_refinements = 0;



    ASSERT_FALSE(RetriangulateTracks(options_, mock_database_, rigs_, cameras_, frames_, images_, tracks_));

}



}  // namespace glomap
