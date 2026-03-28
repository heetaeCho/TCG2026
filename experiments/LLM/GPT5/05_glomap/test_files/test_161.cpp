// File: bundle_adjuster_options_test_161.cc

#include <gtest/gtest.h>
#include <string>

#include "glomap/estimators/optimization_base.h"
#include "glomap/estimators/bundle_adjustment.h"

namespace {

class BundleAdjusterOptionsTest_161 : public ::testing::Test {};

// 기본 상속 관계와 업캐스트 가능 여부 확인
TEST_F(BundleAdjusterOptionsTest_161, InheritsFromOptimizationBaseOptions_161) {
  glomap::BundleAdjusterOptions options;
  glomap::OptimizationBaseOptions* base_ptr = &options;

  // 업캐스트가 성공해야 한다.
  EXPECT_NE(nullptr, base_ptr);
}

// 기본 옵션과 BundleAdjusterOptions 생성자에서의 재설정 값 확인
TEST_F(BundleAdjusterOptionsTest_161, ConstructorOverridesBaseThresholdAndIterations_161) {
  glomap::OptimizationBaseOptions base_options;
  // Partial code 상의 기본값 확인
  EXPECT_DOUBLE_EQ(0.1, base_options.thres_loss_function);

  glomap::BundleAdjusterOptions bundle_options;
  // BundleAdjusterOptions 생성자가 변경하는 값 확인
  EXPECT_DOUBLE_EQ(1.0, bundle_options.thres_loss_function);
  EXPECT_EQ(200, bundle_options.solver_options.max_num_iterations);
}

// 최적화 플래그들의 기본값 확인
TEST_F(BundleAdjusterOptionsTest_161, DefaultOptimizationFlags_161) {
  glomap::BundleAdjusterOptions options;

  EXPECT_FALSE(options.optimize_rig_poses);
  EXPECT_TRUE(options.optimize_rotations);
  EXPECT_TRUE(options.optimize_translation);
  EXPECT_TRUE(options.optimize_intrinsics);
  EXPECT_FALSE(options.optimize_principal_point);
  EXPECT_TRUE(options.optimize_points);
}

// GPU 관련 옵션의 기본값 확인
TEST_F(BundleAdjusterOptionsTest_161, DefaultGpuRelatedOptions_161) {
  glomap::BundleAdjusterOptions options;

  EXPECT_TRUE(options.use_gpu);
  EXPECT_EQ(std::string("-1"), options.gpu_index);
  EXPECT_EQ(50, options.min_num_images_gpu_solver);
  EXPECT_EQ(3, options.min_num_view_per_track);
}

// public 필드들이 정상적으로 수정/저장되는지 확인 (정상 동작 시나리오)
TEST_F(BundleAdjusterOptionsTest_161, CanModifyPublicOptionsFields_161) {
  glomap::BundleAdjusterOptions options;

  options.optimize_rig_poses = true;
  options.use_gpu = false;
  options.gpu_index = "1";
  options.min_num_images_gpu_solver = 10;
  options.min_num_view_per_track = 2;
  options.thres_loss_function = 0.5;
  options.solver_options.max_num_iterations = 5;

  EXPECT_TRUE(options.optimize_rig_poses);
  EXPECT_FALSE(options.use_gpu);
  EXPECT_EQ(std::string("1"), options.gpu_index);
  EXPECT_EQ(10, options.min_num_images_gpu_solver);
  EXPECT_EQ(2, options.min_num_view_per_track);
  EXPECT_DOUBLE_EQ(0.5, options.thres_loss_function);
  EXPECT_EQ(5, options.solver_options.max_num_iterations);
}

// CreateLossFunction 이 예외 없이 호출 가능한지를 확인 (정상 동작 시나리오)
TEST_F(BundleAdjusterOptionsTest_161, CreateLossFunctionDoesNotThrow_161) {
  glomap::BundleAdjusterOptions options;

  EXPECT_NO_THROW({
    auto loss = options.CreateLossFunction();
    (void)loss;  // 사용하지 않는 반환값에 대한 경고 방지
  });
}

// 경계 상황: thres_loss_function 이 0 또는 음수인 경우에도 예외 없이 동작하는지 확인
TEST_F(BundleAdjusterOptionsTest_161, CreateLossFunctionHandlesNonPositiveThreshold_161) {
  glomap::BundleAdjusterOptions options;

  options.thres_loss_function = 0.0;
  EXPECT_NO_THROW({
    auto loss = options.CreateLossFunction();
    (void)loss;
  });

  options.thres_loss_function = -1.0;
  EXPECT_NO_THROW({
    auto loss = options.CreateLossFunction();
    (void)loss;
  });
}

}  // namespace
