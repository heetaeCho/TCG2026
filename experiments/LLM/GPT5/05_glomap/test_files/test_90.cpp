// File: gravity_info_test_90.cc

#include <gtest/gtest.h>
#include <Eigen/Dense>

#include "glomap/scene/frame.h"

namespace {

using glomap::GravityInfo;

class GravityInfoTest_90 : public ::testing::Test {
 protected:
  GravityInfo info_;
};

// 기본 상태 확인: 생성 직후에는 중력 정보가 없다고 가정
TEST_F(GravityInfoTest_90, DefaultConstructor_HasNoGravity_90) {
  EXPECT_FALSE(info_.has_gravity);
}

// 정상 동작: Vector3d로 SetGravity 호출 시 has_gravity가 true로 설정되는지 확인
TEST_F(GravityInfoTest_90, SetGravityVector_SetsHasGravityTrue_90) {
  Eigen::Vector3d g(0.0, 0.0, -9.81);

  info_.SetGravity(g);

  EXPECT_TRUE(info_.has_gravity);
}

// 정상 동작: SetGravity 이후 GetGravity가 설정한 값과 동일한 값을 반환하는지 확인
TEST_F(GravityInfoTest_90, SetGravityVector_StoresGravity_90) {
  Eigen::Vector3d g(1.0, 2.0, 3.0);

  info_.SetGravity(g);
  Eigen::Vector3d stored = info_.GetGravity();

  EXPECT_DOUBLE_EQ(g.x(), stored.x());
  EXPECT_DOUBLE_EQ(g.y(), stored.y());
  EXPECT_DOUBLE_EQ(g.z(), stored.z());
}

// 경계 조건: Zero vector를 입력해도 has_gravity가 true가 되고,
// GetGravity가 zero vector를 그대로 반환하는지 확인
TEST_F(GravityInfoTest_90, SetGravityVector_ZeroVector_90) {
  Eigen::Vector3d g = Eigen::Vector3d::Zero();

  info_.SetGravity(g);
  Eigen::Vector3d stored = info_.GetGravity();

  EXPECT_TRUE(info_.has_gravity);
  EXPECT_DOUBLE_EQ(g.x(), stored.x());
  EXPECT_DOUBLE_EQ(g.y(), stored.y());
  EXPECT_DOUBLE_EQ(g.z(), stored.z());
}

// 여러 번 호출: 여러 번 SetGravity를 호출했을 때 마지막으로 설정한 값이 유지되는지 확인
TEST_F(GravityInfoTest_90, MultipleSetGravityVector_UpdatesGravity_90) {
  Eigen::Vector3d g1(1.0, 0.0, 0.0);
  Eigen::Vector3d g2(0.0, 1.0, 0.0);

  info_.SetGravity(g1);
  info_.SetGravity(g2);
  Eigen::Vector3d stored = info_.GetGravity();

  EXPECT_TRUE(info_.has_gravity);
  EXPECT_DOUBLE_EQ(g2.x(), stored.x());
  EXPECT_DOUBLE_EQ(g2.y(), stored.y());
  EXPECT_DOUBLE_EQ(g2.z(), stored.z());
}

// 인터페이스 관점 검증: GetRAlign이 항상 동일한 내부 행렬에 대한 const reference를 반환하는지 확인
TEST_F(GravityInfoTest_90, GetRAlign_ReturnsStableReference_90) {
  // 같은 객체에 대해 두 번 호출했을 때 참조의 주소가 동일한지 확인
  const Eigen::Matrix3d* p1 = &info_.GetRAlign();
  const Eigen::Matrix3d* p2 = &info_.GetRAlign();

  EXPECT_EQ(p1, p2);
}

}  // namespace
