// TEST_ID: 609
// File: yaml_cpp_node_convert_unordered_map_test_609.cpp

#include <gtest/gtest.h>

#include <string>
#include <unordered_map>
#include <utility>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/type.h"

namespace {

class EncodeUnorderedMapTest_609 : public ::testing::Test {};

TEST_F(EncodeUnorderedMapTest_609, EncodeEmptyMap_ReturnsEmptyMapNode_609) {
  const std::unordered_map<std::string, int> input;

  YAML::Node out = YAML::encode(input);

  EXPECT_TRUE(out.IsMap());
  EXPECT_EQ(out.Type(), YAML::NodeType::Map);
  EXPECT_EQ(out.size(), 0u);
}

TEST_F(EncodeUnorderedMapTest_609, EncodeSingleElement_PreservesKeyValue_609) {
  const std::unordered_map<std::string, int> input{{"a", 1}};

  YAML::Node out = YAML::encode(input);

  EXPECT_TRUE(out.IsMap());
  EXPECT_EQ(out.size(), 1u);

  const YAML::Node value = out["a"];
  EXPECT_TRUE(value.IsDefined());
  EXPECT_EQ(value.as<int>(), 1);
}

TEST_F(EncodeUnorderedMapTest_609, EncodeMultipleElements_PreservesAllPairs_609) {
  const std::unordered_map<std::string, int> input{
      {"alpha", 10},
      {"beta", 20},
      {"gamma", 30},
  };

  YAML::Node out = YAML::encode(input);

  EXPECT_TRUE(out.IsMap());
  EXPECT_EQ(out.size(), input.size());

  // Verify all pairs exist and match, without assuming any ordering.
  for (const auto& kv : input) {
    const YAML::Node value = out[kv.first];
    EXPECT_TRUE(value.IsDefined()) << "Missing key: " << kv.first;
    EXPECT_EQ(value.as<int>(), kv.second) << "Mismatched value for key: " << kv.first;
  }
}

TEST_F(EncodeUnorderedMapTest_609, EncodeNonStringKeyValue_WorksWithIntToDouble_609) {
  const std::unordered_map<int, double> input{
      {1, 1.25},
      {2, -3.5},
      {42, 0.0},
  };

  YAML::Node out = YAML::encode(input);

  EXPECT_TRUE(out.IsMap());
  EXPECT_EQ(out.size(), input.size());

  for (const auto& kv : input) {
    const YAML::Node value = out[kv.first];
    EXPECT_TRUE(value.IsDefined()) << "Missing key: " << kv.first;
    EXPECT_DOUBLE_EQ(value.as<double>(), kv.second) << "Mismatched value for key: " << kv.first;
  }
}

TEST_F(EncodeUnorderedMapTest_609, MissingKey_AccessIsNotDefined_609) {
  const std::unordered_map<std::string, int> input{
      {"present", 123},
  };

  YAML::Node out = YAML::encode(input);

  EXPECT_TRUE(out.IsMap());
  EXPECT_EQ(out.size(), 1u);

  const YAML::Node missing = out["absent"];
  EXPECT_FALSE(missing.IsDefined());
  EXPECT_FALSE(static_cast<bool>(missing));
}

TEST_F(EncodeUnorderedMapTest_609, EncodeLargerMap_SizeMatchesAndAllPairsPresent_609) {
  std::unordered_map<std::string, int> input;
  for (int i = 0; i < 200; ++i) {
    input.emplace("k" + std::to_string(i), i);
  }

  YAML::Node out = YAML::encode(input);

  EXPECT_TRUE(out.IsMap());
  EXPECT_EQ(out.size(), input.size());

  // Spot-check a few keys and also verify by iterating all input pairs.
  EXPECT_EQ(out["k0"].as<int>(), 0);
  EXPECT_EQ(out["k199"].as<int>(), 199);
  EXPECT_EQ(out["k42"].as<int>(), 42);

  for (const auto& kv : input) {
    const YAML::Node value = out[kv.first];
    ASSERT_TRUE(value.IsDefined()) << "Missing key: " << kv.first;
    EXPECT_EQ(value.as<int>(), kv.second) << "Mismatched value for key: " << kv.first;
  }
}

}  // namespace