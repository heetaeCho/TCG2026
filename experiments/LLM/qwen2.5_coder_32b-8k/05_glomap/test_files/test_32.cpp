#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <unordered_map>

#include "TestProjects/glomap/glomap/estimators/global_rotation_averaging.h"



namespace glomap {

    class Frame {

    public:

        bool is_registered = false;

        bool HasGravity() const { return has_gravity; }

        void SetHasGravity(bool value) { has_gravity = value; }



    private:

        bool has_gravity = false;

    };



    struct RotationEstimatorOptions {

        bool use_gravity = false;

    };



    class MockFrame : public Frame {

    public:

        MOCK_METHOD(bool, HasGravity, (), (const));

    };



    class TestRotationEstimator : public ::testing::Test {

    protected:

        RotationEstimatorOptions options;

        RotationEstimator estimator;



        TestRotationEstimator() : options{}, estimator(options) {}



        std::unordered_map<frame_t, Frame> CreateFrames(size_t num_frames, bool is_registered = false, bool has_gravity = false) {

            std::unordered_map<frame_t, Frame> frames;

            for (size_t i = 0; i < num_frames; ++i) {

                frames[i] = Frame{is_registered};

                frames[i].SetHasGravity(has_gravity);

            }

            return frames;

        }

    };



    TEST_F(TestRotationEstimator_32, ComputeAverageStepSize_NoFrames_32) {

        std::unordered_map<frame_t, Frame> frames;

        EXPECT_EQ(estimator.ComputeAverageStepSize(frames), 0.0);

    }



    TEST_F(TestRotationEstimator_32, ComputeAverageStepSize_AllRegistered_32) {

        auto frames = CreateFrames(5, true);

        EXPECT_EQ(estimator.ComputeAverageStepSize(frames), 0.0);

    }



    TEST_F(TestRotationEstimator_32, ComputeAverageStepSize_SingleFrameNoGravity_32) {

        auto frames = CreateFrames(1, false);

        EXPECT_EQ(estimator.ComputeAverageStepSize(frames), 0.0); // Assuming tangent_space_step is zero initialized

    }



    TEST_F(TestRotationEstimator_32, ComputeAverageStepSize_MultipleFramesNoGravity_32) {

        options.use_gravity = false;

        auto frames = CreateFrames(5, false);

        EXPECT_EQ(estimator.ComputeAverageStepSize(frames), 0.0); // Assuming tangent_space_step is zero initialized

    }



    TEST_F(TestRotationEstimator_32, ComputeAverageStepSize_SingleFrameWithGravity_32) {

        options.use_gravity = true;

        auto frames = CreateFrames(1, false, true);

        EXPECT_EQ(estimator.ComputeAverageStepSize(frames), 0.0); // Assuming tangent_space_step is zero initialized

    }



    TEST_F(TestRotationEstimator_32, ComputeAverageStepSize_MultipleFrameWithGravity_32) {

        options.use_gravity = true;

        auto frames = CreateFrames(5, false, true);

        EXPECT_EQ(estimator.ComputeAverageStepSize(frames), 0.0); // Assuming tangent_space_step is zero initialized

    }

}
