#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rotation_initializer.h"  // Where ConvertRotationsFromImageToRig is declared

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

namespace glomap {

// ---------------------------
// Mock Rig
// ---------------------------
class MockRig : public Rig {
public:
    MOCK_METHOD(void, SetSensorFromRig,
        (const sensor_t&, const Rigid3d&), (override));

    MOCK_METHOD(std::optional<Rigid3d>, MaybeSensorFromRig,
        (const sensor_t&) const, (override));
};

// ---------------------------
// Mock Frame
// ---------------------------
class MockFrame : public Frame {
public:
    MOCK_METHOD(std::vector<data_t>, ImageIds, (), (const, override));
    MOCK_METHOD(Rig*, RigPtr, (), (override));
    MOCK_METHOD(void, SetRigFromWorld, (const Rigid3d&), (override));
};

// ---------------------------
// Mock Image
// ---------------------------
class MockImage : public Image {
public:
    MOCK_METHOD(bool, IsRegistered, (), (const, override));
};

// ---------------------------
// Mock AverageQuaternions
// (Allowed because it is an external dependency outside class under test)
// ---------------------------
class MockAverage {
public:
    MOCK_METHOD(Eigen::Quaterniond, Compute,
        (const std::vector<Eigen::Quaterniond>&,
         const std::vector<double>&));
};

static MockAverage* g_avg_quat_mock = nullptr;

// Global override hook
namespace colmap {
Eigen::Quaterniond AverageQuaternions(
    const std::vector<Eigen::Quaterniond>& qs,
    const std::vector<double>& ws)
{
    return g_avg_quat_mock->Compute(qs, ws);
}
}  // namespace colmap

// ===========================
//        TEST FIXTURE
// ===========================

class RotationInitializerTest_100 : public ::testing::Test {
protected:
    void SetUp() override {
        g_avg_quat_mock = &avg_mock_;
    }
    void TearDown() override {
        g_avg_quat_mock = nullptr;
    }

    MockAverage avg_mock_;
};

// ====================================================================
// TEST 1: Empty inputs → Should return true and perform no operations
// ====================================================================
TEST_F(RotationInitializerTest_100, EmptyInputsReturnTrue_100)
{
    std::unordered_map<image_t, Rigid3d> cam_from_worlds;
    std::unordered_map<image_t, Image> images;
    std::unordered_map<rig_t, Rig> rigs;
    std::unordered_map<frame_t, Frame> frames;

    // No quaternion averaging should occur
    EXPECT_CALL(avg_mock_, Compute(_, _)).Times(0);

    bool result =
        ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);
}

// ====================================================================
// TEST 2: Frame exists but no registered images → should skip updates
// ====================================================================
TEST_F(RotationInitializerTest_100, FrameWithoutRegisteredImages_100)
{
    std::unordered_map<image_t, Rigid3d> cam_from_worlds;
    std::unordered_map<image_t, Image> images;
    std::unordered_map<rig_t, Rig> rigs;
    std::unordered_map<frame_t, Frame> frames;

    // Frame mock
    auto* f = new MockFrame();
    frames[0] = *f;

    EXPECT_CALL(*f, ImageIds()).WillRepeatedly(Return(std::vector<data_t>{}));
    EXPECT_CALL(*f, RigPtr()).Times(0);
    EXPECT_CALL(*f, SetRigFromWorld(_)).Times(0);

    EXPECT_CALL(avg_mock_, Compute(_, _)).Times(0);

    bool result =
        ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);
}

// ====================================================================
// TEST 3: Single rig, single camera, ref image registered → expect
//         SetSensorFromRig() and SetRigFromWorld() to be called
// ====================================================================
TEST_F(RotationInitializerTest_100,
       RegisteredReferenceImageTriggersSensorUpdate_100)
{
    // ------------------------
    // Input containers
    // ------------------------
    std::unordered_map<image_t, Rigid3d> cam_from_worlds;
    std::unordered_map<image_t, Image> images;

    // ------------------------
    // Construct mock image
    // ------------------------
    MockImage img_ref;
    EXPECT_CALL(img_ref, IsRegistered()).WillRepeatedly(Return(true));

    img_ref.camera_id = 10;   // camera id
    images[100] = img_ref;    // image_id = 100

    // ------------------------
    // Camera orientation
    // ------------------------
    cam_from_worlds[100] =
        Rigid3d(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d(0, 0, 0));

    // ------------------------
    // Mock Rig
    // ------------------------
    auto* rig = new MockRig();

    // Reference sensor = camera 10
    sensor_t ref_sensor(SensorType::CAMERA, 10);

    EXPECT_CALL(*rig, MaybeSensorFromRig(ref_sensor))
        .WillRepeatedly(Return(std::optional<Rigid3d>{}));

    // Expect rig.SetSensorFromRig() to be called once
    EXPECT_CALL(*rig, SetSensorFromRig(_, _)).Times(1);

    std::unordered_map<rig_t, Rig> rigs;
    rigs[1] = *rig;

    // ------------------------
    // Frame mock
    // ------------------------
    auto* f = new MockFrame();

    EXPECT_CALL(*f, ImageIds())
        .WillRepeatedly(Return(std::vector<data_t>{{100}}));

    EXPECT_CALL(*f, RigPtr())
        .WillRepeatedly(Return(rig));

    // Expect frame.SetRigFromWorld()
    EXPECT_CALL(*f, SetRigFromWorld(_)).Times(1);

    std::unordered_map<frame_t, Frame> frames;
    frames[0] = *f;

    // ------------------------
    // Quaternion averaging
    // ------------------------
    EXPECT_CALL(avg_mock_, Compute(_, _))
        .WillRepeatedly(Return(Eigen::Quaterniond(1, 0, 0, 0)));

    // ------------------------
    // Execute
    // ------------------------
    bool result =
        ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);
}

// ====================================================================
// TEST 4: Unregistered image should be ignored
// ====================================================================
TEST_F(RotationInitializerTest_100, UnregisteredImageIsIgnored_100)
{
    std::unordered_map<image_t, Rigid3d> cam_from_worlds;
    std::unordered_map<image_t, Image> images;

    MockImage img;
    EXPECT_CALL(img, IsRegistered()).WillRepeatedly(Return(false));

    img.camera_id = 5;
    images[200] = img;

    std::unordered_map<rig_t, Rig> rigs;
    std::unordered_map<frame_t, Frame> frames;

    EXPECT_CALL(avg_mock_, Compute(_, _)).Times(0);

    bool result =
        ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);
}

// ====================================================================
// TEST 5: If camera has no rig mapping, no SetSensorFromRig should occur
// ====================================================================
TEST_F(RotationInitializerTest_100, MissingCameraRigMapping_100)
{
    std::unordered_map<image_t, Rigid3d> cam_from_worlds;
    std::unordered_map<image_t, Image> images;
    std::unordered_map<rig_t, Rig> rigs;
    std::unordered_map<frame_t, Frame> frames;

    MockImage img;
    EXPECT_CALL(img, IsRegistered()).WillRepeatedly(Return(true));
    img.camera_id = 7;
    images[300] = img;

    cam_from_worlds[300] =
        Rigid3d(Eigen::Quaterniond(1, 0, 0, 0), Eigen::Vector3d(0, 0, 0));

    // Frame
    auto* f = new MockFrame();
    EXPECT_CALL(*f, ImageIds())
        .WillRepeatedly(Return(std::vector<data_t>{{300}}));
    EXPECT_CALL(*f, SetRigFromWorld(_)).Times(0);

    frames[0] = *f;

    EXPECT_CALL(avg_mock_, Compute(_, _)).Times(0);

    bool result =
        ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);
}

} // namespace glomap
