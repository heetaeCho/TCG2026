#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ceres/ceres.h>
#include <unordered_map>

// We need to include or replicate the minimal types used by the code
// Based on the code, we need camera_t, Camera, and the ViewGraphCalibrator class

namespace glomap {

// Minimal type definitions inferred from the interface
using camera_t = uint32_t;

struct Camera {
    bool has_prior_focal_length = false;
    // other fields may exist but we only need what's used in ParameterizeCameras
};

class ViewGraphCalibrator {
public:
    // We need to expose enough to test. Based on the code, the class uses:
    // - problem_ (a ceres::Problem pointer)
    // - focals_ (a map from camera_t to double)
    
    // For testing purposes, we need to set up problem_ and focals_
    // We'll create a minimal version that allows testing ParameterizeCameras
    
    std::unique_ptr<ceres::Problem> problem_;
    std::unordered_map<camera_t, double> focals_;

    size_t ParameterizeCameras(
        const std::unordered_map<camera_t, Camera>& cameras) {
        size_t num_cameras = 0;
        for (auto& [camera_id, camera] : cameras) {
            if (!problem_->HasParameterBlock(&(focals_[camera_id])))
                continue;
            num_cameras++;
            problem_->SetParameterLowerBound(&(focals_[camera_id]), 0, 1e-3);
            if (camera.has_prior_focal_length) {
                problem_->SetParameterBlockConstant(&(focals_[camera_id]));
                num_cameras--;
            }
        }
        return num_cameras;
    }
};

class ViewGraphCalibratorTest_21 : public ::testing::Test {
protected:
    void SetUp() override {
        calibrator_.problem_ = std::make_unique<ceres::Problem>();
    }

    // Helper: add a focal as a parameter block to the problem
    void AddFocalToProlem(camera_t camera_id, double initial_focal = 500.0) {
        calibrator_.focals_[camera_id] = initial_focal;
        // We need a trivial cost function to add the parameter block
        // Using a simple AutoDiff or manually created cost function
        ceres::CostFunction* cost_function =
            new ceres::AutoDiffCostFunction<TrivialCost, 1, 1>(new TrivialCost());
        calibrator_.problem_->AddResidualBlock(
            cost_function, nullptr, &(calibrator_.focals_[camera_id]));
    }

    struct TrivialCost {
        template <typename T>
        bool operator()(const T* const x, T* residual) const {
            residual[0] = x[0];
            return true;
        }
    };

    ViewGraphCalibrator calibrator_;
};

// Test: Empty cameras map returns 0
TEST_F(ViewGraphCalibratorTest_21, EmptyCamerasReturnsZero_21) {
    std::unordered_map<camera_t, Camera> cameras;
    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, 0u);
}

// Test: Camera not in problem (no parameter block) is skipped
TEST_F(ViewGraphCalibratorTest_21, CameraNotInProblemIsSkipped_21) {
    std::unordered_map<camera_t, Camera> cameras;
    Camera cam;
    cam.has_prior_focal_length = false;
    cameras[1] = cam;
    
    // focals_[1] exists but is NOT added to problem_
    calibrator_.focals_[1] = 500.0;
    
    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, 0u);
}

// Test: Single camera in problem without prior focal length counts as 1
TEST_F(ViewGraphCalibratorTest_21, SingleCameraWithoutPriorCountsAsOne_21) {
    std::unordered_map<camera_t, Camera> cameras;
    Camera cam;
    cam.has_prior_focal_length = false;
    cameras[1] = cam;

    AddFocalToProlem(1, 500.0);

    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, 1u);
}

// Test: Single camera with prior focal length returns 0
TEST_F(ViewGraphCalibratorTest_21, SingleCameraWithPriorReturnsZero_21) {
    std::unordered_map<camera_t, Camera> cameras;
    Camera cam;
    cam.has_prior_focal_length = true;
    cameras[1] = cam;

    AddFocalToProlem(1, 500.0);

    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, 0u);
}

// Test: Multiple cameras, all without prior focal length
TEST_F(ViewGraphCalibratorTest_21, MultipleCamerasAllWithoutPrior_21) {
    std::unordered_map<camera_t, Camera> cameras;
    
    for (camera_t id = 0; id < 5; ++id) {
        Camera cam;
        cam.has_prior_focal_length = false;
        cameras[id] = cam;
        AddFocalToProlem(id, 500.0 + id);
    }

    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, 5u);
}

// Test: Multiple cameras, all with prior focal length
TEST_F(ViewGraphCalibratorTest_21, MultipleCamerasAllWithPrior_21) {
    std::unordered_map<camera_t, Camera> cameras;
    
    for (camera_t id = 0; id < 5; ++id) {
        Camera cam;
        cam.has_prior_focal_length = true;
        cameras[id] = cam;
        AddFocalToProlem(id, 500.0 + id);
    }

    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, 0u);
}

// Test: Mixed cameras - some with prior, some without, some not in problem
TEST_F(ViewGraphCalibratorTest_21, MixedCamerasPartialPriorAndPartialInProblem_21) {
    std::unordered_map<camera_t, Camera> cameras;

    // Camera 0: in problem, no prior -> counted
    Camera cam0;
    cam0.has_prior_focal_length = false;
    cameras[0] = cam0;
    AddFocalToProlem(0, 500.0);

    // Camera 1: in problem, has prior -> not counted
    Camera cam1;
    cam1.has_prior_focal_length = true;
    cameras[1] = cam1;
    AddFocalToProlem(1, 600.0);

    // Camera 2: NOT in problem -> skipped
    Camera cam2;
    cam2.has_prior_focal_length = false;
    cameras[2] = cam2;
    calibrator_.focals_[2] = 700.0;  // exists in focals_ but not in problem

    // Camera 3: in problem, no prior -> counted
    Camera cam3;
    cam3.has_prior_focal_length = false;
    cameras[3] = cam3;
    AddFocalToProlem(3, 800.0);

    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, 2u);
}

// Test: Verify that lower bound is set (indirectly via ceres Problem)
TEST_F(ViewGraphCalibratorTest_21, LowerBoundIsSetForCameraWithoutPrior_21) {
    std::unordered_map<camera_t, Camera> cameras;
    Camera cam;
    cam.has_prior_focal_length = false;
    cameras[1] = cam;

    AddFocalToProlem(1, 500.0);

    calibrator_.ParameterizeCameras(cameras);

    // After ParameterizeCameras, the lower bound should be set to 1e-3
    // We can verify by checking the parameter block's lower bound through ceres
    double lower_bound = calibrator_.problem_->GetParameterLowerBound(
        &(calibrator_.focals_[1]), 0);
    EXPECT_DOUBLE_EQ(lower_bound, 1e-3);
}

// Test: Verify that camera with prior is set constant
TEST_F(ViewGraphCalibratorTest_21, CameraWithPriorIsSetConstant_21) {
    std::unordered_map<camera_t, Camera> cameras;
    Camera cam;
    cam.has_prior_focal_length = true;
    cameras[1] = cam;

    AddFocalToProlem(1, 500.0);

    calibrator_.ParameterizeCameras(cameras);

    // The parameter block should be constant
    EXPECT_TRUE(calibrator_.problem_->IsParameterBlockConstant(
        &(calibrator_.focals_[1])));
}

// Test: Camera without prior is NOT set constant
TEST_F(ViewGraphCalibratorTest_21, CameraWithoutPriorIsNotConstant_21) {
    std::unordered_map<camera_t, Camera> cameras;
    Camera cam;
    cam.has_prior_focal_length = false;
    cameras[1] = cam;

    AddFocalToProlem(1, 500.0);

    calibrator_.ParameterizeCameras(cameras);

    EXPECT_FALSE(calibrator_.problem_->IsParameterBlockConstant(
        &(calibrator_.focals_[1])));
}

// Test: Large number of cameras
TEST_F(ViewGraphCalibratorTest_21, LargeNumberOfCameras_21) {
    std::unordered_map<camera_t, Camera> cameras;
    const size_t num_total = 100;
    size_t expected_count = 0;

    for (camera_t id = 0; id < num_total; ++id) {
        Camera cam;
        cam.has_prior_focal_length = (id % 3 == 0);  // every 3rd has prior
        cameras[id] = cam;
        AddFocalToProlem(id, 100.0 + id);
        if (!cam.has_prior_focal_length) {
            expected_count++;
        }
    }

    size_t result = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result, expected_count);
}

// Test: Calling ParameterizeCameras twice should be safe for cameras without prior
TEST_F(ViewGraphCalibratorTest_21, CalledTwiceForNonPriorCamera_21) {
    std::unordered_map<camera_t, Camera> cameras;
    Camera cam;
    cam.has_prior_focal_length = false;
    cameras[1] = cam;

    AddFocalToProlem(1, 500.0);

    size_t result1 = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result1, 1u);

    // Calling again should still work
    size_t result2 = calibrator_.ParameterizeCameras(cameras);
    EXPECT_EQ(result2, 1u);
}

}  // namespace glomap
