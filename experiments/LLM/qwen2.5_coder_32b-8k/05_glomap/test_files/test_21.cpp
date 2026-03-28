#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <unordered_map>



namespace glomap {

    class Camera {

    public:

        bool has_prior_focal_length;

        double focal_length;

    };



    using camera_t = int;



    class ProblemMock {

    public:

        MOCK_METHOD(void, SetParameterLowerBound, (double*, int, double));

        MOCK_METHOD(void, SetParameterBlockConstant, (double*));

        MOCK_METHOD(bool, HasParameterBlock, (const double*), (const));



        std::unordered_map<const double*, bool> parameter_blocks_;

        void AddParameterBlock(const double* block) {

            parameter_blocks_[block] = true;

        }



        void RemoveParameterBlock(const double* block) {

            parameter_blocks_.erase(block);

        }

    };



    class ViewGraphCalibrator {

    public:

        explicit ViewGraphCalibrator(ProblemMock* problem) : problem_(problem) {}



        size_t ParameterizeCameras(const std::unordered_map<camera_t, Camera>& cameras);



    private:

        ProblemMock* problem_;

        std::unordered_map<camera_t, double> focals_;

    };



    size_t ViewGraphCalibrator::ParameterizeCameras(const std::unordered_map<camera_t, Camera>& cameras) {

        size_t num_cameras = 0;

        for (auto& [camera_id, camera] : cameras) {

            if (!problem_->HasParameterBlock(&(focals_[camera_id]))) continue;

            num_cameras++;

            problem_->SetParameterLowerBound(&(focals_[camera_id]), 0, 1e-3);

            if (camera.has_prior_focal_length) {

                problem_->SetParameterBlockConstant(&(focals_[camera_id]));

                num_cameras--;

            }

        }

        return num_cameras;

    }

}



using namespace glomap;



class ViewGraphCalibratorTest_21 : public ::testing::Test {

protected:

    void SetUp() override {

        calibrator_ = std::make_unique<ViewGraphCalibrator>(&problem_);

        for (int i = 0; i < 5; ++i) {

            problem_.AddParameterBlock(&focals_[i]);

        }

    }



    ProblemMock problem_;

    std::unique_ptr<ViewGraphCalibrator> calibrator_;

    std::unordered_map<camera_t, double> focals_;

};



TEST_F(ViewGraphCalibratorTest_21, ParameterizeCameras_NormalOperation_21) {

    std::unordered_map<camera_t, Camera> cameras = {

        {0, {false, 1.0}},

        {1, {false, 2.0}}

    };



    EXPECT_CALL(problem_, HasParameterBlock(&focals_[0])).WillOnce(testing::Return(true));

    EXPECT_CALL(problem_, HasParameterBlock(&focals_[1])).WillOnce(testing::Return(true));



    EXPECT_CALL(problem_, SetParameterLowerBound(&focals_[0], 0, 1e-3)).Times(1);

    EXPECT_CALL(problem_, SetParameterLowerBound(&focals_[1], 0, 1e-3)).Times(1);



    size_t result = calibrator_->ParameterizeCameras(cameras);

    EXPECT_EQ(result, 2);

}



TEST_F(ViewGraphCalibratorTest_21, ParameterizeCameras_CameraWithPriorFocalLength_21) {

    std::unordered_map<camera_t, Camera> cameras = {

        {0, {true, 1.0}},

        {1, {false, 2.0}}

    };



    EXPECT_CALL(problem_, HasParameterBlock(&focals_[0])).WillOnce(testing::Return(true));

    EXPECT_CALL(problem_, HasParameterBlock(&focals_[1])).WillOnce(testing::Return(true));



    EXPECT_CALL(problem_, SetParameterLowerBound(&focals_[0], 0, 1e-3)).Times(1);

    EXPECT_CALL(problem_, SetParameterBlockConstant(&focals_[0])).Times(1);



    EXPECT_CALL(problem_, SetParameterLowerBound(&focals_[1], 0, 1e-3)).Times(1);



    size_t result = calibrator_->ParameterizeCameras(cameras);

    EXPECT_EQ(result, 1);

}



TEST_F(ViewGraphCalibratorTest_21, ParameterizeCameras_CameraWithoutParameterBlock_21) {

    std::unordered_map<camera_t, Camera> cameras = {

        {0, {false, 1.0}},

        {5, {false, 2.0}} // Camera 5 does not have a parameter block

    };



    EXPECT_CALL(problem_, HasParameterBlock(&focals_[0])).WillOnce(testing::Return(true));

    EXPECT_CALL(problem_, HasParameterBlock(&focals_[5])).WillOnce(testing::Return(false));



    EXPECT_CALL(problem_, SetParameterLowerBound(&focals_[0], 0, 1e-3)).Times(1);



    size_t result = calibrator_->ParameterizeCameras(cameras);

    EXPECT_EQ(result, 1);

}



TEST_F(ViewGraphCalibratorTest_21, ParameterizeCameras_EmptyCameraList_21) {

    std::unordered_map<camera_t, Camera> cameras;



    size_t result = calibrator_->ParameterizeCameras(cameras);

    EXPECT_EQ(result, 0);

}
