// TEST_ID: 639
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;

class NodeDataEmptyScalarTest_639 : public ::testing::Test {};

TEST_F(NodeDataEmptyScalarTest_639, ReturnsEmptyString_639) {
  node_data data;
  const std::string& s = data.empty_scalar();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

TEST_F(NodeDataEmptyScalarTest_639, ReturnsSameReferenceAcrossRepeatedCalls_639) {
  node_data data;

  const std::string& s1 = data.empty_scalar();
  const std::string& s2 = data.empty_scalar();
  const std::string& s3 = data.empty_scalar();

  EXPECT_EQ(&s1, &s2);
  EXPECT_EQ(&s2, &s3);
  EXPECT_TRUE(s1.empty());
}

TEST_F(NodeDataEmptyScalarTest_639, ReturnsSameReferenceAcrossInstances_639) {
  node_data a;
  node_data b;

  const std::string& sa = a.empty_scalar();
  const std::string& sb = b.empty_scalar();

  EXPECT_EQ(&sa, &sb);
  EXPECT_TRUE(sa.empty());
}

TEST_F(NodeDataEmptyScalarTest_639, CopyingReturnedValueProducesIndependentStdString_639) {
  node_data data;

  const std::string& sref = data.empty_scalar();
  std::string copy = sref;

  // Mutating the copy should not affect the returned reference (observable behavior).
  copy.push_back('x');

  EXPECT_TRUE(sref.empty());
  EXPECT_EQ(copy, "x");
}

}  // namespace