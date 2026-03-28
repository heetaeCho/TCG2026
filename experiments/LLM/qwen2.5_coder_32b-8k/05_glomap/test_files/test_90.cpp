#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/scene/frame.h"



using namespace glomap;

using ::testing::Eq;



class GravityInfoTest_90 : public ::testing::Test {

protected:

    GravityInfo gravity_info_;

};



TEST_F(GravityInfoTest_90, SetGravityUpdatesHasGravityTrue_90) {

    gravity_info_.SetGravity(Eigen::Vector3d(1.0, 2.0, 3.0));

    EXPECT_TRUE(gravity_info_.has_gravity);

}



TEST_F(GravityInfoTest_90, SetGravitySetsCorrectGravityValue_90) {

    Eigen::Vector3d expected_gravity(4.5, -2.3, 7.8);

    gravity_info_.SetGravity(expected_gravity);

    EXPECT_EQ(gravity_info_.GetGravity(), expected_gravity);

}



TEST_F(GravityInfoTest_90, SetGravityZeroVectorSetsCorrectGravityValue_90) {

    Eigen::Vector3d zero_vector(0.0, 0.0, 0.0);

    gravity_info_.SetGravity(zero_vector);

    EXPECT_EQ(gravity_info_.GetGravity(), zero_vector);

}



TEST_F(GravityInfoTest_90, SetGravityUpdatesRAlign_90) {

    Eigen::Vector3d test_gravity(1.0, 2.0, 3.0);

    gravity_info_.SetGravity(test_gravity);

    const Eigen::Matrix3d& R_align = gravity_info_.GetRAlign();

    EXPECT_FALSE(R_align.isIdentity());

}



TEST_F(GravityInfoTest_90, GetRAlignReturnsIdentityInitially_90) {

    const Eigen::Matrix3d& initial_R_align = gravity_info_.GetRAlign();

    EXPECT_TRUE(initial_R_align.isIdentity());

}
