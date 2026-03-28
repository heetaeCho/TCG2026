// TEST_ID: 208
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;

class NodeDataScalarTest_208 : public ::testing::Test {};

TEST_F(NodeDataScalarTest_208, ScalarDoesNotThrowOnDefaultConstructed_208) {
  node_data nd;
  EXPECT_NO_THROW({
    (void)nd.scalar();
  });
}

TEST_F(NodeDataScalarTest_208, ScalarReturnsSameReferenceOnRepeatedCalls_208) {
  node_data nd;

  const std::string* p1 = &nd.scalar();
  const std::string* p2 = &nd.scalar();

  EXPECT_EQ(p1, p2);
}

TEST_F(NodeDataScalarTest_208, ScalarReflectsValueAfterSetScalar_208) {
  node_data nd;

  const std::string value = "hello";
  nd.set_scalar(value);

  EXPECT_EQ(nd.scalar(), value);
}

TEST_F(NodeDataScalarTest_208, ScalarCanBeSetToEmptyString_208) {
  node_data nd;

  nd.set_scalar("non-empty");
  ASSERT_FALSE(nd.scalar().empty());

  nd.set_scalar(std::string{});
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataScalarTest_208, ScalarHandlesLargeString_208) {
  node_data nd;

  const std::string large(256 * 1024, 'x');  // 256 KiB
  nd.set_scalar(large);

  EXPECT_EQ(nd.scalar().size(), large.size());
  EXPECT_EQ(nd.scalar(), large);
}

TEST_F(NodeDataScalarTest_208, ScalarReferenceRemainsStableAcrossSetScalarCalls_208) {
  node_data nd;

  const std::string* before = &nd.scalar();

  nd.set_scalar("a");
  const std::string* after1 = &nd.scalar();

  nd.set_scalar("a much longer string to encourage reallocation of contents");
  const std::string* after2 = &nd.scalar();

  // We only assert the reference points to the same std::string object,
  // not that its internal buffer address is stable.
  EXPECT_EQ(before, after1);
  EXPECT_EQ(after1, after2);
}

}  // namespace