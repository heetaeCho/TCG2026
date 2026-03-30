#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/controllers/option_manager.h"

#include "./TestProjects/glomap/glomap/global_mapper.h"



namespace glomap {



using ::testing::_;

using ::testing::NotNull;



class OptionManagerTest : public ::testing::Test {

protected:

    OptionManagerTest() : manager(false) {

        mapper = std::make_shared<GlobalMapperOptions>();

        manager.mapper = mapper;

    }



    OptionManager manager;

    std::shared_ptr<GlobalMapperOptions> mapper;

};



TEST_F(OptionManagerTest_47, AddInlierThresholdOptions_AddsOptionsOnce_47) {

    EXPECT_FALSE(manager.added_inliers_options_);

    manager.AddInlierThresholdOptions();

    EXPECT_TRUE(manager.added_inliers_options_);

}



TEST_F(OptionManagerTest_47, AddInlierThresholdOptions_DoesNotAddAgain_47) {

    manager.AddInlierThresholdOptions();

    manager.AddInlierThresholdOptions(); // Should not add again

    EXPECT_EQ(mapper->inlier_thresholds.max_angle_error, 1.);

}



TEST_F(OptionManagerTest_47, AddInlierThresholdOptions_DefaultValuesSetCorrectly_47) {

    manager.AddInlierThresholdOptions();

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.max_angle_error, 1.);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.max_reprojection_error, 0.01);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.min_triangulation_angle, 1.);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.max_epipolar_error_E, 1.);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.max_epipolar_error_F, 4.);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.max_epipolar_error_H, 4.);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.min_inlier_num, 30);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.min_inlier_ratio, 0.25);

    EXPECT_DOUBLE_EQ(mapper->inlier_thresholds.max_rotation_error, 10.);

}



} // namespace glomap
