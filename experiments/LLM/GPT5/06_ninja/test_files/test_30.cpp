#include "graph.h"
#include "disk_interface.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Exactly;

// Simple mock for DiskInterface to observe calls from Node.
class MockDiskInterface_30 : public DiskInterface {
public:
  // We only need to mock Stat; other methods can use the base implementation.
  MOCK_METHOD(TimeStamp, Stat,
              (const std::string& path, std::string* err),
              (override));
};

// Test fixture for Node::StatIfNecessary tests.
class NodeStatIfNecessaryTest_30 : public ::testing::Test {
protected:
  NodeStatIfNecessaryTest_30()
      : node_("path/to/file", /*slash_bits=*/0) {}

  Node node_;
};

// When status is already known, StatIfNecessary should immediately return true
// and must not call DiskInterface::Stat.
TEST_F(NodeStatIfNecessaryTest_30,
       DoesNotCallStatWhenStatusAlreadyKnown_30) {
  MockDiskInterface_30 mock_disk;
  std::string err;

  // Arrange: put Node into a state where status_known() is true using public API.
  node_.MarkMissing();
  ASSERT_TRUE(node_.status_known());

  // DiskInterface::Stat must NOT be called.
  EXPECT_CALL(mock_disk, Stat(_, _)).Times(0);

  // Act
  bool result = node_.StatIfNecessary(&mock_disk, &err);

  // Assert
  EXPECT_TRUE(result);
}

// When status is not known yet, StatIfNecessary should delegate to Node::Stat,
// which in turn is expected to call DiskInterface::Stat once with the node's
// path and the same error pointer.
TEST_F(NodeStatIfNecessaryTest_30,
       CallsStatWhenStatusUnknown_30) {
  MockDiskInterface_30 mock_disk;
  std::string err;

  // Arrange: ensure status is "unknown" using public API.
  node_.ResetState();
  ASSERT_FALSE(node_.status_known());

  // Expect DiskInterface::Stat to be called exactly once with the node's path
  // and the same error string pointer we pass into StatIfNecessary.
  EXPECT_CALL(mock_disk, Stat(node_.path(), &err))
      .Times(Exactly(1));

  // Act
  bool result = node_.StatIfNecessary(&mock_disk, &err);

  // We do not assert on |result| value itself, because the mapping from
  // DiskInterface::Stat to the boolean return is internal to Node::Stat
  // (black box). Here we only verify the observable interaction with
  // DiskInterface under the "status unknown" condition.
  (void)result;  // suppress unused-variable warning if no assertion is made
}
