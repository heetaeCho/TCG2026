#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "glomap/scene/camera.h"

// We need to include colmap's Camera header since glomap::Camera depends on it
#include <colmap/scene/camera.h>

class CameraTest_6 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction of Camera
TEST_F(CameraTest_6, DefaultConstruction_6) {
    glomap::Camera camera;
    // Default constructed camera should exist without crashing
    SUCCEED();
}

// Test assignment from colmap::Camera
TEST_F(CameraTest_6, AssignmentFromColmapCamera_6) {
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(1);
    colmap_cam.SetModelIdFromName("PINHOLE");
    colmap_cam.SetWidth(1920);
    colmap_cam.SetHeight(1080);
    colmap_cam.SetParams({500.0, 500.0, 960.0, 540.0});

    glomap::Camera glomap_cam;
    glomap_cam = colmap_cam;

    // The assignment should complete without error
    SUCCEED();
}

// Test self-assignment stability (assign from colmap::Camera then reassign)
TEST_F(CameraTest_6, MultipleAssignmentsFromColmapCamera_6) {
    colmap::Camera colmap_cam1;
    colmap_cam1.SetCameraId(1);
    colmap_cam1.SetModelIdFromName("PINHOLE");
    colmap_cam1.SetWidth(640);
    colmap_cam1.SetHeight(480);
    colmap_cam1.SetParams({320.0, 320.0, 320.0, 240.0});

    colmap::Camera colmap_cam2;
    colmap_cam2.SetCameraId(2);
    colmap_cam2.SetModelIdFromName("SIMPLE_RADIAL");
    colmap_cam2.SetWidth(1920);
    colmap_cam2.SetHeight(1080);
    colmap_cam2.SetParams({1000.0, 960.0, 540.0, 0.0});

    glomap::Camera glomap_cam;
    glomap_cam = colmap_cam1;
    glomap_cam = colmap_cam2;

    // Multiple assignments should not crash
    SUCCEED();
}

// Test assignment operator returns reference to self
TEST_F(CameraTest_6, AssignmentReturnsReference_6) {
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(1);
    colmap_cam.SetModelIdFromName("PINHOLE");
    colmap_cam.SetWidth(640);
    colmap_cam.SetHeight(480);
    colmap_cam.SetParams({320.0, 320.0, 320.0, 240.0});

    glomap::Camera glomap_cam;
    glomap::Camera& ref = (glomap_cam = colmap_cam);

    // The returned reference should point to the same object
    EXPECT_EQ(&ref, &glomap_cam);
}

// Test chained assignment from colmap::Camera
TEST_F(CameraTest_6, ChainedAssignment_6) {
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(3);
    colmap_cam.SetModelIdFromName("PINHOLE");
    colmap_cam.SetWidth(800);
    colmap_cam.SetHeight(600);
    colmap_cam.SetParams({400.0, 400.0, 400.0, 300.0});

    glomap::Camera cam1, cam2;
    // Chained assignment: cam2 = cam1 = colmap_cam
    // This first assigns colmap_cam to cam1, then assigns cam1 to cam2 via copy
    cam1 = colmap_cam;
    cam2 = cam1;

    SUCCEED();
}

// Test assignment from default-constructed colmap::Camera (boundary case)
TEST_F(CameraTest_6, AssignmentFromDefaultColmapCamera_6) {
    colmap::Camera colmap_cam;
    // Default colmap camera - no model, no size set

    glomap::Camera glomap_cam;
    glomap_cam = colmap_cam;

    // Should handle default/empty camera without crashing
    SUCCEED();
}

// Test copy construction of Camera
TEST_F(CameraTest_6, CopyConstruction_6) {
    glomap::Camera cam1;
    
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(5);
    colmap_cam.SetModelIdFromName("PINHOLE");
    colmap_cam.SetWidth(1024);
    colmap_cam.SetHeight(768);
    colmap_cam.SetParams({512.0, 512.0, 512.0, 384.0});
    
    cam1 = colmap_cam;
    
    glomap::Camera cam2 = cam1;
    // Copy should work fine
    SUCCEED();
}

// Test with various camera models
TEST_F(CameraTest_6, AssignmentWithSimplePinholeModel_6) {
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(10);
    colmap_cam.SetModelIdFromName("SIMPLE_PINHOLE");
    colmap_cam.SetWidth(1920);
    colmap_cam.SetHeight(1080);
    colmap_cam.SetParams({1000.0, 960.0, 540.0});

    glomap::Camera glomap_cam;
    glomap_cam = colmap_cam;

    SUCCEED();
}

TEST_F(CameraTest_6, AssignmentWithRadialModel_6) {
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(11);
    colmap_cam.SetModelIdFromName("RADIAL");
    colmap_cam.SetWidth(2048);
    colmap_cam.SetHeight(1536);
    colmap_cam.SetParams({1024.0, 1024.0, 768.0, 0.01, -0.001});

    glomap::Camera glomap_cam;
    glomap_cam = colmap_cam;

    SUCCEED();
}

// Test with extreme dimensions (boundary)
TEST_F(CameraTest_6, AssignmentWithLargeDimensions_6) {
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(20);
    colmap_cam.SetModelIdFromName("PINHOLE");
    colmap_cam.SetWidth(10000);
    colmap_cam.SetHeight(10000);
    colmap_cam.SetParams({5000.0, 5000.0, 5000.0, 5000.0});

    glomap::Camera glomap_cam;
    glomap_cam = colmap_cam;

    SUCCEED();
}

// Test with minimum valid dimensions (boundary)
TEST_F(CameraTest_6, AssignmentWithMinimalDimensions_6) {
    colmap::Camera colmap_cam;
    colmap_cam.SetCameraId(21);
    colmap_cam.SetModelIdFromName("PINHOLE");
    colmap_cam.SetWidth(1);
    colmap_cam.SetHeight(1);
    colmap_cam.SetParams({1.0, 1.0, 0.5, 0.5});

    glomap::Camera glomap_cam;
    glomap_cam = colmap_cam;

    SUCCEED();
}
