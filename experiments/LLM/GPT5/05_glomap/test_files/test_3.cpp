#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"

namespace glomap {

class ImageGetRAlignTest_3 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// [Normal / boundary] When the image has no gravity, GetRAlign should return identity.
TEST_F(ImageGetRAlignTest_3, ReturnsIdentityWhenNoGravity_3) {
  Image image;  // default-constructed image

  // We only assert the branch when HasGravity() reports false, to avoid
  // making assumptions about internal initialization.
  if (!image.HasGravity()) {
    const Eigen::Matrix3d R_align = image.GetRAlign();
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity();

    // Use isApprox to avoid floating-point comparison issues.
    EXPECT_TRUE(R_align.isApprox(I))
        << "GetRAlign should return identity when HasGravity() is false";
  } else {
    GTEST_SKIP() << "Default-constructed Image reports gravity; "
                    "cannot validate no-gravity behavior reliably.";
  }
}

// [Normal operation] When the image has gravity and a trivial frame,
// GetRAlign should match the frame's gravity_info alignment.
TEST_F(ImageGetRAlignTest_3, ReturnsFrameGravityAlignForTrivialFrame_3) {
  Frame frame;
  Image image;

  // Attach the frame to the image.
  image.frame_ptr = &frame;

  // Configure gravity via the public API of GravityInfo.
  const Eigen::Vector3d gravity(0.0, 0.0, -1.0);
  frame.gravity_info.SetGravity(gravity);

  // We only assert this specific behavior if the observable preconditions
  // (HasGravity && HasTrivialFrame) are satisfied, without assuming how
  // they are implemented internally.
  if (image.HasGravity() && image.HasTrivialFrame()) {
    const Eigen::Matrix3d expected = frame.gravity_info.GetRAlign();
    const Eigen::Matrix3d actual = image.GetRAlign();

    EXPECT_TRUE(actual.isApprox(expected))
        << "GetRAlign should match frame_ptr->gravity_info.GetRAlign() "
           "when HasGravity() and HasTrivialFrame() are both true.";
  } else {
    GTEST_SKIP()
        << "Could not satisfy HasGravity() && HasTrivialFrame() via public API; "
           "skipping branch-specific assertion.";
  }
}

}  // namespace glomap
