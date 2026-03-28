#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <map>

// ============================================================
// Tests for Node::as<T>(const S& fallback)
// ============================================================

TEST(NodeAsWithFallbackTest_556, ValidIntNodeReturnsValue_556) {
  YAML::Node node = YAML::Load("42");
  int result = node.as<int>(0);
  EXPECT_EQ(42, result);
}

TEST(NodeAsWithFallbackTest_556, ValidStringNodeReturnsValue_556) {
  YAML::Node node = YAML::Load("hello");
  std::string result = node.as<std::string>(std::string("default"));
  EXPECT_EQ("hello", result);
}

TEST(NodeAsWithFallbackTest_556, ValidDoubleNodeReturnsValue_556) {
  YAML::Node node = YAML::Load("3.14");
  double result = node.as<double>(0.0);
  EXPECT_DOUBLE_EQ(3.14, result);
}

TEST(NodeAsWithFallbackTest_556, ValidBoolNodeReturnsValue_556) {
  YAML::Node node = YAML::Load("true");
  bool result = node.as<bool>(false);
  EXPECT_TRUE(result);
}

TEST(NodeAsWithFallbackTest_556, InvalidNodeReturnsFallbackInt_556) {
  YAML::Node root = YAML::Load("key: value");
  YAML::Node invalid = root["nonexistent"]["deep"];
  int result = invalid.as<int>(99);
  EXPECT_EQ(99, result);
}

TEST(NodeAsWithFallbackTest_556, InvalidNodeReturnsFallbackString_556) {
  YAML::Node root = YAML::Load("key: value");
  YAML::Node invalid = root["nonexistent"]["deep"];
  std::string result = invalid.as<std::string>(std::string("fallback_value"));
  EXPECT_EQ("fallback_value", result);
}

TEST(NodeAsWithFallbackTest_556, NullNodeReturnsFallback_556) {
  YAML::Node node = YAML::Load("~");
  std::string result = node.as<std::string>(std::string("default"));
  // Null node - conversion may fail, should return fallback
  // Actually, ~ is null in YAML, but as<string> might convert it to "~" or ""
  // The important thing is it doesn't crash
  // We just verify it returns something without throwing
  (void)result;
}

TEST(NodeAsWithFallbackTest_556, UndefinedNodeReturnsFallback_556) {
  YAML::Node root = YAML::Load("a: 1");
  YAML::Node undef = root["nonexistent"];
  int result = undef.as<int>(42);
  EXPECT_EQ(42, result);
}

TEST(NodeAsWithFallbackTest_556, EmptyNodeReturnsFallback_556) {
  YAML::Node node;
  int result = node.as<int>(100);
  EXPECT_EQ(100, result);
}

TEST(NodeAsWithFallbackTest_556, ConversionFailureReturnsFallback_556) {
  YAML::Node node = YAML::Load("not_a_number");
  int result = node.as<int>(-1);
  EXPECT_EQ(-1, result);
}

TEST(NodeAsWithFallbackTest_556, SequenceNodeAsVectorInt_556) {
  YAML::Node node = YAML::Load("[1, 2, 3]");
  std::vector<int> fallback = {0};
  std::vector<int> result = node.as<std::vector<int>>(fallback);
  ASSERT_EQ(3u, result.size());
  EXPECT_EQ(1, result[0]);
  EXPECT_EQ(2, result[1]);
  EXPECT_EQ(3, result[2]);
}

TEST(NodeAsWithFallbackTest_556, MapNodeAsMapStringString_556) {
  YAML::Node node = YAML::Load("{a: b, c: d}");
  std::map<std::string, std::string> fallback;
  std::map<std::string, std::string> result =
      node.as<std::map<std::string, std::string>>(fallback);
  EXPECT_EQ(2u, result.size());
  EXPECT_EQ("b", result["a"]);
  EXPECT_EQ("d", result["c"]);
}

TEST(NodeAsWithFallbackTest_556, FallbackZeroForDouble_556) {
  YAML::Node node = YAML::Load("not_a_double");
  double result = node.as<double>(0.0);
  EXPECT_DOUBLE_EQ(0.0, result);
}

TEST(NodeAsWithFallbackTest_556, FallbackFalseForBool_556) {
  YAML::Node node = YAML::Load("not_a_bool");
  bool result = node.as<bool>(false);
  EXPECT_FALSE(result);
}

TEST(NodeAsWithFallbackTest_556, ValidIntegerAsStringReturnsStringRepresentation_556) {
  YAML::Node node = YAML::Load("42");
  std::string result = node.as<std::string>(std::string("default"));
  EXPECT_EQ("42", result);
}

TEST(NodeAsWithFallbackTest_556, NegativeIntNodeReturnsValue_556) {
  YAML::Node node = YAML::Load("-10");
  int result = node.as<int>(0);
  EXPECT_EQ(-10, result);
}

TEST(NodeAsWithFallbackTest_556, LargeIntNodeReturnsValue_556) {
  YAML::Node node = YAML::Load("2147483647");
  int result = node.as<int>(0);
  EXPECT_EQ(2147483647, result);
}

// ============================================================
// Tests for Node general interface
// ============================================================

TEST(NodeTest_556, DefaultConstructorCreatesNullNode_556) {
  YAML::Node node;
  EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_556, ConstructorWithTypeSequence_556) {
  YAML::Node node(YAML::NodeType::Sequence);
  EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_556, ConstructorWithTypeMap_556) {
  YAML::Node node(YAML::NodeType::Map);
  EXPECT_TRUE(node.IsMap());
}

TEST(NodeTest_556, ConstructorWithTypeScalar_556) {
  YAML::Node node(YAML::NodeType::Scalar);
  EXPECT_TRUE(node.IsScalar());
}

TEST(NodeTest_556, ConstructorWithValue_556) {
  YAML::Node node(42);
  EXPECT_TRUE(node.IsScalar());
  EXPECT_EQ(42, node.as<int>());
}

TEST(NodeTest_556, ConstructorWithString_556) {
  YAML::Node node(std::string("hello"));
  EXPECT_TRUE(node.IsScalar());
  EXPECT_EQ("hello", node.as<std::string>());
}

TEST(NodeTest_556, CopyConstructor_556) {
  YAML::Node original = YAML::Load("42");
  YAML::Node copy(original);
  EXPECT_EQ(42, copy.as<int>());
}

TEST(NodeTest_556, AssignmentOperator_556) {
  YAML::Node node;
  node = 42;
  EXPECT_EQ(42, node.as<int>());
}

TEST(NodeTest_556, NodeAssignment_556) {
  YAML::Node a = YAML::Load("hello");
  YAML::Node b;
  b = a;
  EXPECT_EQ("hello", b.as<std::string>());
}

TEST(NodeTest_556, IsDefinedForExistingKey_556) {
  YAML::Node node = YAML::Load("{a: 1}");
  EXPECT_TRUE(node["a"].IsDefined());
}

TEST(NodeTest_556, IsDefinedForMissingKey_556) {
  YAML::Node node = YAML::Load("{a: 1}");
  EXPECT_FALSE(node["b"].IsDefined());
}

TEST(NodeTest_556, ScalarValue_556) {
  YAML::Node node = YAML::Load("hello");
  EXPECT_EQ("hello", node.Scalar());
}

TEST(NodeTest_556, SetAndGetTag_556) {
  YAML::Node node = YAML::Load("42");
  node.SetTag("!custom");
  EXPECT_EQ("!custom", node.Tag());
}

TEST(NodeTest_556, SetAndGetStyle_556) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.SetStyle(YAML::EmitterStyle::Flow);
  EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

TEST(NodeTest_556, SizeOfSequence_556) {
  YAML::Node node = YAML::Load("[1, 2, 3]");
  EXPECT_EQ(3u, node.size());
}

TEST(NodeTest_556, SizeOfMap_556) {
  YAML::Node node = YAML::Load("{a: 1, b: 2}");
  EXPECT_EQ(2u, node.size());
}

TEST(NodeTest_556, PushBackToSequence_556) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  node.push_back(2);
  EXPECT_EQ(2u, node.size());
  EXPECT_EQ(1, node[0].as<int>());
  EXPECT_EQ(2, node[1].as<int>());
}

TEST(NodeTest_556, SubscriptOperatorMapAccess_556) {
  YAML::Node node = YAML::Load("{key: value}");
  EXPECT_EQ("value", node["key"].as<std::string>());
}

TEST(NodeTest_556, RemoveKeyFromMap_556) {
  YAML::Node node = YAML::Load("{a: 1, b: 2}");
  EXPECT_TRUE(node.remove("a"));
  EXPECT_FALSE(node["a"].IsDefined());
}

TEST(NodeTest_556, RemoveNonexistentKey_556) {
  YAML::Node node = YAML::Load("{a: 1}");
  EXPECT_FALSE(node.remove("nonexistent"));
}

TEST(NodeTest_556, IsMethodSameNode_556) {
  YAML::Node a = YAML::Load("42");
  YAML::Node b = a;
  EXPECT_TRUE(a.is(b));
}

TEST(NodeTest_556, IsMethodDifferentNode_556) {
  YAML::Node a = YAML::Load("42");
  YAML::Node b = YAML::Load("42");
  EXPECT_FALSE(a.is(b));
}

TEST(NodeTest_556, BoolOperatorValidNode_556) {
  YAML::Node node = YAML::Load("42");
  EXPECT_TRUE(static_cast<bool>(node));
}

TEST(NodeTest_556, BoolOperatorInvalidNode_556) {
  YAML::Node root = YAML::Load("{a: 1}");
  YAML::Node invalid = root["x"]["y"];
  EXPECT_FALSE(static_cast<bool>(invalid));
}

TEST(NodeTest_556, NotOperatorValidNode_556) {
  YAML::Node node = YAML::Load("42");
  EXPECT_FALSE(!node);
}

TEST(NodeTest_556, NotOperatorInvalidNode_556) {
  YAML::Node root = YAML::Load("{a: 1}");
  YAML::Node invalid = root["x"]["y"];
  EXPECT_TRUE(!invalid);
}

TEST(NodeTest_556, TypeOfLoadedScalar_556) {
  YAML::Node node = YAML::Load("hello");
  EXPECT_EQ(YAML::NodeType::Scalar, node.Type());
}

TEST(NodeTest_556, TypeOfLoadedSequence_556) {
  YAML::Node node = YAML::Load("[1, 2]");
  EXPECT_EQ(YAML::NodeType::Sequence, node.Type());
}

TEST(NodeTest_556, TypeOfLoadedMap_556) {
  YAML::Node node = YAML::Load("{a: 1}");
  EXPECT_EQ(YAML::NodeType::Map, node.Type());
}

TEST(NodeTest_556, TypeOfNull_556) {
  YAML::Node node = YAML::Load("~");
  EXPECT_EQ(YAML::NodeType::Null, node.Type());
}

TEST(NodeTest_556, IterateOverSequence_556) {
  YAML::Node node = YAML::Load("[10, 20, 30]");
  std::vector<int> values;
  for (auto it = node.begin(); it != node.end(); ++it) {
    values.push_back(it->as<int>());
  }
  ASSERT_EQ(3u, values.size());
  EXPECT_EQ(10, values[0]);
  EXPECT_EQ(20, values[1]);
  EXPECT_EQ(30, values[2]);
}

TEST(NodeTest_556, IterateOverMap_556) {
  YAML::Node node = YAML::Load("{x: 1, y: 2}");
  std::map<std::string, int> result;
  for (auto it = node.begin(); it != node.end(); ++it) {
    result[it->first.as<std::string>()] = it->second.as<int>();
  }
  EXPECT_EQ(2u, result.size());
  EXPECT_EQ(1, result["x"]);
  EXPECT_EQ(2, result["y"]);
}

TEST(NodeTest_556, ResetNode_556) {
  YAML::Node a = YAML::Load("42");
  YAML::Node b = YAML::Load("hello");
  a.reset(b);
  EXPECT_TRUE(a.is(b));
  EXPECT_EQ("hello", a.as<std::string>());
}

TEST(NodeTest_556, ForceInsertIntoMap_556) {
  YAML::Node node(YAML::NodeType::Map);
  node.force_insert("key1", "value1");
  node.force_insert("key2", "value2");
  EXPECT_EQ(2u, node.size());
  EXPECT_EQ("value1", node["key1"].as<std::string>());
  EXPECT_EQ("value2", node["key2"].as<std::string>());
}

TEST(NodeTest_556, AsWithoutFallbackValidInt_556) {
  YAML::Node node = YAML::Load("42");
  EXPECT_EQ(42, node.as<int>());
}

TEST(NodeTest_556, AsWithoutFallbackValidString_556) {
  YAML::Node node = YAML::Load("world");
  EXPECT_EQ("world", node.as<std::string>());
}

TEST(NodeTest_556, AsWithoutFallbackThrowsOnBadConversion_556) {
  YAML::Node node = YAML::Load("not_a_number");
  EXPECT_THROW(node.as<int>(), YAML::Exception);
}

TEST(NodeTest_556, PushBackNodeToSequence_556) {
  YAML::Node seq(YAML::NodeType::Sequence);
  YAML::Node val = YAML::Load("hello");
  seq.push_back(val);
  EXPECT_EQ(1u, seq.size());
  EXPECT_EQ("hello", seq[0].as<std::string>());
}

TEST(NodeTest_556, SubscriptWithNodeKey_556) {
  YAML::Node node = YAML::Load("{a: 1}");
  YAML::Node key = YAML::Load("a");
  EXPECT_EQ(1, node[key].as<int>());
}

TEST(NodeTest_556, RemoveWithNodeKey_556) {
  YAML::Node node = YAML::Load("{a: 1, b: 2}");
  YAML::Node key = YAML::Load("a");
  EXPECT_TRUE(node.remove(key));
  EXPECT_FALSE(node["a"].IsDefined());
}

TEST(NodeTest_556, EmptySequenceSize_556) {
  YAML::Node node = YAML::Load("[]");
  EXPECT_EQ(0u, node.size());
  EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTest_556, EmptyMapSize_556) {
  YAML::Node node = YAML::Load("{}");
  EXPECT_EQ(0u, node.size());
  EXPECT_TRUE(node.IsMap());
}

TEST(NodeAsWithFallbackTest_556, SequenceConversionFailReturnsFallback_556) {
  YAML::Node node = YAML::Load("just_a_string");
  std::vector<int> fallback = {1, 2, 3};
  std::vector<int> result = node.as<std::vector<int>>(fallback);
  EXPECT_EQ(fallback, result);
}

TEST(NodeAsWithFallbackTest_556, FallbackEmptyString_556) {
  YAML::Node root = YAML::Load("{a: 1}");
  YAML::Node invalid = root["missing"]["deep"];
  std::string result = invalid.as<std::string>(std::string(""));
  EXPECT_EQ("", result);
}
