#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ceres/ceres.h"

#include "Eigen/Eigen"



namespace glomap {

    struct RigBATAPairwiseDirectionError {

    public:

        const Eigen::Vector3d translation_obs_;

        const Eigen::Vector3d translation_rig_;



        RigBATAPairwiseDirectionError(const Eigen::Vector3d& translation_obs, const Eigen::Vector3d& translation_rig)

            : translation_obs_(translation_obs), translation_rig_(translation_rig) {}



        template <typename T>

        bool operator()(const T* position1, const T* position2, const T* scale, const T* scale_rig, T* residuals) const {

            Eigen::Map<Eigen::Matrix<T, 3, 1>> residuals_vec(residuals);

            residuals_vec = translation_obs_.cast<T>() - scale[0] * (Eigen::Map<const Eigen::Matrix<T, 3, 1>>(position2) - Eigen::Map<const Eigen::Matrix<T, 3, 1>>(position1) + scale_rig[0] * translation_rig_.cast<T>());

            return true;

        }



        static ceres::CostFunction* Create(const Eigen::Vector3d& translation_obs, const Eigen::Vector3d& translation_rig);

    };

}



using namespace glomap;



TEST_F(RigBATAPairwiseDirectionErrorTest_13, NormalOperation_13) {

    Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);

    Eigen::Vector3d translation_rig(4.0, 5.0, 6.0);



    RigBATAPairwiseDirectionError error_func(translation_obs, translation_rig);



    double position1[3] = {0.0, 0.0, 0.0};

    double position2[3] = {1.0, 1.0, 1.0};

    double scale[1] = {1.0};

    double scale_rig[1] = {1.0};



    double residuals[3];

    EXPECT_TRUE(error_func(position1, position2, scale, scale_rig, residuals));



    Eigen::Vector3d expected_residuals(translation_obs - (position2[0] - position1[0] + translation_rig[0]));

    for (int i = 0; i < 3; ++i) {

        EXPECT_DOUBLE_EQ(residuals[i], expected_residuals[i]);

    }

}



TEST_F(RigBATAPairwiseDirectionErrorTest_13, BoundaryConditions_ZeroScale_13) {

    Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);

    Eigen::Vector3d translation_rig(4.0, 5.0, 6.0);



    RigBATAPairwiseDirectionError error_func(translation_obs, translation_rig);



    double position1[3] = {0.0, 0.0, 0.0};

    double position2[3] = {1.0, 1.0, 1.0};

    double scale[1] = {0.0};

    double scale_rig[1] = {1.0};



    double residuals[3];

    EXPECT_TRUE(error_func(position1, position2, scale, scale_rig, residuals));



    Eigen::Vector3d expected_residuals(translation_obs);

    for (int i = 0; i < 3; ++i) {

        EXPECT_DOUBLE_EQ(residuals[i], expected_residuals[i]);

    }

}



TEST_F(RigBATAPairwiseDirectionErrorTest_13, BoundaryConditions_ZeroScaleRig_13) {

    Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);

    Eigen::Vector3d translation_rig(4.0, 5.0, 6.0);



    RigBATAPairwiseDirectionError error_func(translation_obs, translation_rig);



    double position1[3] = {0.0, 0.0, 0.0};

    double position2[3] = {1.0, 1.0, 1.0};

    double scale[1] = {1.0};

    double scale_rig[1] = {0.0};



    double residuals[3];

    EXPECT_TRUE(error_func(position1, position2, scale, scale_rig, residuals));



    Eigen::Vector3d expected_residuals(translation_obs - (position2[0] - position1[0]));

    for (int i = 0; i < 3; ++i) {

        EXPECT_DOUBLE_EQ(residuals[i], expected_residuals[i]);

    }

}



TEST_F(RigBATAPairwiseDirectionErrorTest_13, BoundaryConditions_IdenticalPositions_13) {

    Eigen::Vector3d translation_obs(1.0, 2.0, 3.0);

    Eigen::Vector3d translation_rig(4.0, 5.0, 6.0);



    RigBATAPairwiseDirectionError error_func(translation_obs, translation_rig);



    double position1[3] = {1.0, 1.0, 1.0};

    double position2[3] = {1.0, 1.0, 1.0};

    double scale[1] = {1.0};

    double scale_rig[1] = {1.0};



    double residuals[3];

    EXPECT_TRUE(error_func(position1, position2, scale, scale_rig, residuals));



    Eigen::Vector3d expected_residuals(translation_obs - scale[0] * (scale_rig[0] * translation_rig));

    for (int i = 0; i < 3; ++i) {

        EXPECT_DOUBLE_EQ(residuals[i], expected_residuals[i]);

    }

}
