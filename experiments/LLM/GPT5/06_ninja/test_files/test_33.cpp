// File: graph_exists_test_33.cc

#include "graph.h"

#include "gtest/gtest.h"

class NodeExistsTest_33 : public ::testing::Test {
protected:
  Node MakeNode(const std::string& path = "out") {
    return Node(path, 0);
  }
};

// TEST_ID: 33
// 기본 생성 직후에는 존재하지 않는 것으로 간주되어야 한다.
TEST_F(NodeExistsTest_33, DefaultConstructedNodeDoesNotExist_33) {
  Node node = MakeNode();
  EXPECT_FALSE(node.exists());
}

// TEST_ID: 33
// UpdatePhonyMtime 호출 후에는 존재하는 것으로 간주되어야 한다.
TEST_F(NodeExistsTest_33, UpdatePhonyMtimeMakesNodeExist_33) {
  Node node = MakeNode();

  node.UpdatePhonyMtime(1);

  EXPECT_TRUE(node.exists());
}

// TEST_ID: 33
// 존재 상태인 노드에 대해 MarkMissing 호출 시 exists()는 false가 되어야 한다.
TEST_F(NodeExistsTest_33, MarkMissingClearsExistence_33) {
  Node node = MakeNode();

  node.UpdatePhonyMtime(1);
  ASSERT_TRUE(node.exists());

  node.MarkMissing();

  EXPECT_FALSE(node.exists());
}

// TEST_ID: 33
// 존재 상태인 노드에 대해 ResetState 호출 시 다시 존재하지 않는 것으로 간주되어야 한다.
TEST_F(NodeExistsTest_33, ResetStateResetsExistence_33) {
  Node node = MakeNode();

  node.UpdatePhonyMtime(1);
  ASSERT_TRUE(node.exists());

  node.ResetState();

  EXPECT_FALSE(node.exists());
}

// TEST_ID: 33
// UpdatePhonyMtime를 여러 번 호출하더라도 exists()는 계속 true를 반환해야 한다 (정상 동작/경계).
TEST_F(NodeExistsTest_33, MultiplePhonyMtimeUpdatesKeepNodeExisting_33) {
  Node node = MakeNode();

  node.UpdatePhonyMtime(1);
  EXPECT_TRUE(node.exists());

  node.UpdatePhonyMtime(2);
  EXPECT_TRUE(node.exists());
}
