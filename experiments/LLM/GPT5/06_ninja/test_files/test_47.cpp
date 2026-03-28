// File: ./TestProjects/ninja/tests/node_generated_by_dep_loader_test_47.cc

#include "graph.h"

#include <gtest/gtest.h>

class NodeGeneratedByDepLoaderTest_47 : public ::testing::Test {
protected:
  NodeGeneratedByDepLoaderTest_47()
      : node_("path/to/file", /*slash_bits=*/0) {}

  Node node_;
};

// 기본 상태에서 generated_by_dep_loader 플래그가 true 인지 확인
TEST_F(NodeGeneratedByDepLoaderTest_47, DefaultGeneratedByDepLoaderIsTrue_47) {
  EXPECT_TRUE(node_.generated_by_dep_loader());
}

// false 로 설정했을 때 플래그가 false 로 변경되는지 확인
TEST_F(NodeGeneratedByDepLoaderTest_47, SetGeneratedByDepLoaderFalse_47) {
  // 사전조건: 기본 값이 true 라고 가정하지 않고, 현재 값을 기록
  bool original_value = node_.generated_by_dep_loader();

  node_.set_generated_by_dep_loader(false);

  EXPECT_FALSE(node_.generated_by_dep_loader());
  // 다른 관측 가능한 속성들은 변하지 않는지 확인 (id, path 등)
  EXPECT_EQ("path/to/file", node_.path());
  EXPECT_EQ(original_value ? original_value : false, node_.generated_by_dep_loader());
}

// false 로 변경 후 다시 true 로 설정했을 때 복원되는지 확인
TEST_F(NodeGeneratedByDepLoaderTest_47, SetGeneratedByDepLoaderFalseThenTrue_47) {
  node_.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node_.generated_by_dep_loader());

  node_.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node_.generated_by_dep_loader());
}

// 여러 번 호출 시 마지막으로 설정한 값이 반영되는지 확인
TEST_F(NodeGeneratedByDepLoaderTest_47, MultipleSetGeneratedByDepLoaderCalls_47) {
  node_.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node_.generated_by_dep_loader());

  node_.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node_.generated_by_dep_loader());

  node_.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node_.generated_by_dep_loader());
}

// set_generated_by_dep_loader 호출이 다른 공개 상태(id, path 등)에 영향을 주지 않는지 확인
TEST_F(NodeGeneratedByDepLoaderTest_47, SetGeneratedByDepLoaderDoesNotAffectOtherState_47) {
  const std::string original_path = node_.path();
  const uint64_t original_slash_bits = node_.slash_bits();
  const int original_id = node_.id();
  const bool original_dirty = node_.dirty();
  const bool original_dyndep_pending = node_.dyndep_pending();

  node_.set_generated_by_dep_loader(false);

  EXPECT_EQ(original_path, node_.path());
  EXPECT_EQ(original_slash_bits, node_.slash_bits());
  EXPECT_EQ(original_id, node_.id());
  EXPECT_EQ(original_dirty, node_.dirty());
  EXPECT_EQ(original_dyndep_pending, node_.dyndep_pending());
}
