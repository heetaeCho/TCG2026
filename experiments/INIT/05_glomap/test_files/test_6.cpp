#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// Forward declaration in case the header only uses colmap::Camera by reference.
namespace colmap {
class Camera;
}

#include "glomap/scene/camera.h"

// Test fixture (even if empty, keeps naming consistent with requirement)
class CameraTest_6 : public ::testing::Test {};

// [Interface-level] Verify that the assignment operator exists with the expected signature.
TEST_F(CameraTest_6, AssignmentOperatorHasExpectedSignature_6) {
    using LhsType = glomap::Camera;
    using RhsType = const colmap::Camera&;

    // Check that calling operator= with const colmap::Camera& returns glomap::Camera&.
    using ResultType = decltype(std::declval<LhsType&>().operator=(std::declval<RhsType>()));

    static_assert(
        std::is_same<ResultType, LhsType&>::value,
        "glomap::Camera::operator=(const colmap::Camera&) must return glomap::Camera&"
    );

    // No runtime checks needed here; if the signature changes, this test will fail to compile.
    SUCCEED();
}

// [Interface-level] Verify that the assignment operator is a public non-static member function.
TEST_F(CameraTest_6, AssignmentOperatorIsPublicMember_6) {
    // If operator= is not public with this exact signature, this line will fail to compile.
    using AssignPtr = glomap::Camera& (glomap::Camera::*)(const colmap::Camera&);
    AssignPtr ptr = &glomap::Camera::operator=;
    (void)ptr;

    SUCCEED();
}
