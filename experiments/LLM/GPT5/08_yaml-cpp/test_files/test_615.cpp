// File: test/node/convert_array_encode_test_615.cpp

#include <gtest/gtest.h>

#include <array>
#include <string>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

class ConvertArrayEncodeTest_615 : public ::testing::Test {};

TEST_F(ConvertArrayEncodeTest_615, EncodesIntArrayAsSequenceAndPreservesOrder_615) {
  const std::array<int, 4> input{{10, -3, 0, 42}};

  YAML::Node node = YAML::convert<std::array<int, 4>>::encode(input);

  EXPECT_TRUE(node.IsDefined());
  EXPECT_TRUE(static_cast<bool>(node));
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), input.size());

  for (std::size_t i = 0; i < input.size(); ++i) {
    EXPECT_EQ(node[i].as<int>(), input[i]) << "Mismatch at index " << i;
  }
}

TEST_F(ConvertArrayEncodeTest_615, EncodesStringArrayAsSequenceAndPreservesOrder_615) {
  const std::array<std::string, 3> input{{"alpha", "", "gamma"}};

  YAML::Node node = YAML::convert<std::array<std::string, 3>>::encode(input);

  EXPECT_TRUE(node.IsDefined());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), input.size());

  for (std::size_t i = 0; i < input.size(); ++i) {
    EXPECT_EQ(node[i].as<std::string>(), input[i]) << "Mismatch at index " << i;
  }
}

TEST_F(ConvertArrayEncodeTest_615, EncodesEmptyArrayAsEmptySequence_615) {
  const std::array<int, 0> input{};

  YAML::Node node = YAML::convert<std::array<int, 0>>::encode(input);

  EXPECT_TRUE(node.IsDefined());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 0u);
}

TEST_F(ConvertArrayEncodeTest_615, EncodesArrayOfNodesKeepsElementContent_615) {
  YAML::Node a("one");
  YAML::Node b(2);
  YAML::Node c(true);

  const std::array<YAML::Node, 3> input{{a, b, c}};

  YAML::Node node = YAML::convert<std::array<YAML::Node, 3>>::encode(input);

  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), input.size());

  // Validate that each position is accessible and convertible as expected.
  EXPECT_EQ(node[0].as<std::string>(), "one");
  EXPECT_EQ(node[1].as<int>(), 2);
  EXPECT_EQ(node[2].as<bool>(), true);
}

TEST_F(ConvertArrayEncodeTest_615, MultipleEncodesAreIndependent_615) {
  const std::array<int, 2> a{{1, 2}};
  const std::array<int, 2> b{{3, 4}};

  YAML::Node node_a = YAML::convert<std::array<int, 2>>::encode(a);
  YAML::Node node_b = YAML::convert<std::array<int, 2>>::encode(b);

  ASSERT_TRUE(node_a.IsSequence());
  ASSERT_TRUE(node_b.IsSequence());
  ASSERT_EQ(node_a.size(), 2u);
  ASSERT_EQ(node_b.size(), 2u);

  EXPECT_EQ(node_a[0].as<int>(), 1);
  EXPECT_EQ(node_a[1].as<int>(), 2);
  EXPECT_EQ(node_b[0].as<int>(), 3);
  EXPECT_EQ(node_b[1].as<int>(), 4);
}

}  // namespace