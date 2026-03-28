// TEST_ID: 611
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

class ConvertVectorEncodeTest_611 : public ::testing::Test {};

TEST_F(ConvertVectorEncodeTest_611, EncodeEmptyVectorProducesEmptySequence_611) {
  const std::vector<int> input;

  YAML::Node node = YAML::convert<std::vector<int>>::encode(input);

  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 0u);
}

TEST_F(ConvertVectorEncodeTest_611, EncodeIntVectorPreservesSizeAndOrder_611) {
  const std::vector<int> input{1, -2, 0, 42};

  YAML::Node node = YAML::convert<std::vector<int>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), input.size());

  for (std::size_t i = 0; i < input.size(); ++i) {
    EXPECT_EQ(node[i].as<int>(), input[i]) << "Mismatch at index " << i;
  }
}

TEST_F(ConvertVectorEncodeTest_611, EncodeStringVectorPreservesSizeAndOrder_611) {
  const std::vector<std::string> input{"", "alpha", "한글", "with spaces"};

  YAML::Node node = YAML::convert<std::vector<std::string>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), input.size());

  for (std::size_t i = 0; i < input.size(); ++i) {
    EXPECT_EQ(node[i].as<std::string>(), input[i]) << "Mismatch at index " << i;
  }
}

TEST_F(ConvertVectorEncodeTest_611, EncodeVectorOfNodesKeepsNodeValues_611) {
  YAML::Node a("first");
  YAML::Node b(123);
  YAML::Node c("third");

  const std::vector<YAML::Node> input{a, b, c};

  YAML::Node node = YAML::convert<std::vector<YAML::Node>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), input.size());

  EXPECT_TRUE(node[0].IsScalar());
  EXPECT_EQ(node[0].as<std::string>(), "first");

  EXPECT_TRUE(node[1].IsScalar());
  EXPECT_EQ(node[1].as<int>(), 123);

  EXPECT_TRUE(node[2].IsScalar());
  EXPECT_EQ(node[2].as<std::string>(), "third");
}

TEST_F(ConvertVectorEncodeTest_611, EncodeLargeVectorHasExpectedSizeAndEndpoints_611) {
  std::vector<int> input;
  input.reserve(1000);
  for (int i = 0; i < 1000; ++i) input.push_back(i);

  YAML::Node node = YAML::convert<std::vector<int>>::encode(input);

  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), input.size());

  // Spot-check endpoints to verify observable ordering.
  EXPECT_EQ(node[0].as<int>(), 0);
  EXPECT_EQ(node[999].as<int>(), 999);
}

}  // namespace