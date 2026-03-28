#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test as() with fallback on Null node returns "null" for string type
TEST(AsIfFallbackTest_552, NullNodeReturnsNullString_552) {
  YAML::Node node(YAML::NodeType::Null);
  std::string result = node.as<std::string>(std::string("fallback_value"));
  EXPECT_EQ(result, "null");
}

// Test as() with fallback on Scalar node returns the scalar value
TEST(AsIfFallbackTest_552, ScalarNodeReturnsScalarValue_552) {
  YAML::Node node("hello_world");
  std::string result = node.as<std::string>(std::string("fallback_value"));
  EXPECT_EQ(result, "hello_world");
}

// Test as() with fallback on Sequence node returns fallback
TEST(AsIfFallbackTest_552, SequenceNodeReturnsFallback_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back("item1");
  std::string result = node.as<std::string>(std::string("fallback_value"));
  EXPECT_EQ(result, "fallback_value");
}

// Test as() with fallback on Map node returns fallback
TEST(AsIfFallbackTest_552, MapNodeReturnsFallback_552) {
  YAML::Node node(YAML::NodeType::Map);
  node["key"] = "value";
  std::string result = node.as<std::string>(std::string("fallback_value"));
  EXPECT_EQ(result, "fallback_value");
}

// Test as() with fallback on Undefined node returns fallback
TEST(AsIfFallbackTest_552, UndefinedNodeReturnsFallback_552) {
  YAML::Node node;
  // Accessing a non-existent key creates an undefined node
  YAML::Node undefined = node["nonexistent"];
  std::string result = undefined.as<std::string>(std::string("fallback_value"));
  EXPECT_EQ(result, "fallback_value");
}

// Test as() without fallback on a Scalar node
TEST(AsIfNoFallbackTest_552, ScalarNodeReturnsValue_552) {
  YAML::Node node("test_value");
  std::string result = node.as<std::string>();
  EXPECT_EQ(result, "test_value");
}

// Test as() without fallback on a Null node returns "null" (or ~)
TEST(AsIfNoFallbackTest_552, NullNodeReturnsNullString_552) {
  YAML::Node node(YAML::NodeType::Null);
  std::string result = node.as<std::string>();
  EXPECT_EQ(result, "~");
}

// Test as() with fallback on empty scalar node
TEST(AsIfFallbackTest_552, EmptyScalarReturnsEmptyString_552) {
  YAML::Node node("");
  std::string result = node.as<std::string>(std::string("fallback_value"));
  EXPECT_EQ(result, "");
}

// Test as<int>() with fallback on a valid integer scalar
TEST(AsIfFallbackTest_552, IntScalarNodeReturnsIntValue_552) {
  YAML::Node node("42");
  int result = node.as<int>(99);
  EXPECT_EQ(result, 42);
}

// Test as<int>() with fallback on a null node returns fallback
TEST(AsIfFallbackTest_552, NullNodeReturnsIntFallback_552) {
  YAML::Node node(YAML::NodeType::Null);
  int result = node.as<int>(99);
  EXPECT_EQ(result, 99);
}

// Test as<int>() with fallback on a non-convertible scalar returns fallback
TEST(AsIfFallbackTest_552, NonConvertibleScalarReturnsIntFallback_552) {
  YAML::Node node("not_a_number");
  int result = node.as<int>(99);
  EXPECT_EQ(result, 99);
}

// Test as<double>() with fallback on a valid double scalar
TEST(AsIfFallbackTest_552, DoubleScalarNodeReturnsDoubleValue_552) {
  YAML::Node node("3.14");
  double result = node.as<double>(0.0);
  EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test as<double>() with fallback on a sequence node returns fallback
TEST(AsIfFallbackTest_552, SequenceNodeReturnsDoubleFallback_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  double result = node.as<double>(99.9);
  EXPECT_DOUBLE_EQ(result, 99.9);
}

// Test as<bool>() with fallback on a boolean scalar
TEST(AsIfFallbackTest_552, BoolScalarNodeReturnsBoolValue_552) {
  YAML::Node node("true");
  bool result = node.as<bool>(false);
  EXPECT_TRUE(result);
}

// Test as<bool>() with fallback on a map node returns fallback
TEST(AsIfFallbackTest_552, MapNodeReturnsBoolFallback_552) {
  YAML::Node node(YAML::NodeType::Map);
  node["key"] = "value";
  bool result = node.as<bool>(true);
  EXPECT_TRUE(result);
}

// Test as<string>() with fallback where fallback is empty string
TEST(AsIfFallbackTest_552, SequenceNodeReturnsEmptyFallback_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back("item");
  std::string result = node.as<std::string>(std::string(""));
  EXPECT_EQ(result, "");
}

// Test Node basic type checks
TEST(NodeTypeTest_552, DefaultNodeIsNull_552) {
  YAML::Node node;
  EXPECT_TRUE(node.IsNull());
}

TEST(NodeTypeTest_552, ScalarNodeIsScalar_552) {
  YAML::Node node("hello");
  EXPECT_TRUE(node.IsScalar());
}

TEST(NodeTypeTest_552, SequenceNodeIsSequence_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  EXPECT_TRUE(node.IsSequence());
}

TEST(NodeTypeTest_552, MapNodeIsMap_552) {
  YAML::Node node(YAML::NodeType::Map);
  EXPECT_TRUE(node.IsMap());
}

// Test Scalar() method
TEST(NodeScalarTest_552, ScalarReturnsCorrectValue_552) {
  YAML::Node node("test_scalar");
  EXPECT_EQ(node.Scalar(), "test_scalar");
}

// Test size() on sequence
TEST(NodeSizeTest_552, SequenceSizeIsCorrect_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);
  EXPECT_EQ(node.size(), 3u);
}

// Test size() on map
TEST(NodeSizeTest_552, MapSizeIsCorrect_552) {
  YAML::Node node(YAML::NodeType::Map);
  node["a"] = 1;
  node["b"] = 2;
  EXPECT_EQ(node.size(), 2u);
}

// Test Tag and SetTag
TEST(NodeTagTest_552, SetAndGetTag_552) {
  YAML::Node node("value");
  node.SetTag("!mytag");
  EXPECT_EQ(node.Tag(), "!mytag");
}

// Test Style and SetStyle
TEST(NodeStyleTest_552, SetAndGetStyle_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.SetStyle(YAML::EmitterStyle::Flow);
  EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// Test operator bool
TEST(NodeBoolTest_552, ValidNodeIsTrue_552) {
  YAML::Node node("value");
  EXPECT_TRUE(static_cast<bool>(node));
}

// Test IsDefined
TEST(NodeDefinedTest_552, DefinedNodeReturnsTrue_552) {
  YAML::Node node("value");
  EXPECT_TRUE(node.IsDefined());
}

// Test remove on map
TEST(NodeRemoveTest_552, RemoveKeyFromMap_552) {
  YAML::Node node(YAML::NodeType::Map);
  node["key1"] = "value1";
  node["key2"] = "value2";
  EXPECT_TRUE(node.remove("key1"));
  EXPECT_EQ(node.size(), 1u);
}

// Test remove non-existent key
TEST(NodeRemoveTest_552, RemoveNonExistentKeyReturnsFalse_552) {
  YAML::Node node(YAML::NodeType::Map);
  node["key1"] = "value1";
  EXPECT_FALSE(node.remove("nonexistent"));
}

// Test is() method
TEST(NodeIsTest_552, SameNodeReturnsTrue_552) {
  YAML::Node node("value");
  YAML::Node copy = node;
  EXPECT_TRUE(node.is(copy));
}

TEST(NodeIsTest_552, DifferentNodesReturnsFalse_552) {
  YAML::Node node1("value1");
  YAML::Node node2("value2");
  EXPECT_FALSE(node1.is(node2));
}

// Test reset
TEST(NodeResetTest_552, ResetChangesNode_552) {
  YAML::Node node1("original");
  YAML::Node node2("replacement");
  node1.reset(node2);
  EXPECT_TRUE(node1.is(node2));
  EXPECT_EQ(node1.as<std::string>(), "replacement");
}

// Test push_back on sequence
TEST(NodePushBackTest_552, PushBackIncreasesSize_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  EXPECT_EQ(node.size(), 0u);
  node.push_back(42);
  EXPECT_EQ(node.size(), 1u);
  node.push_back("hello");
  EXPECT_EQ(node.size(), 2u);
}

// Test operator[] on sequence
TEST(NodeIndexTest_552, AccessSequenceByIndex_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back("first");
  node.push_back("second");
  EXPECT_EQ(node[0].as<std::string>(), "first");
  EXPECT_EQ(node[1].as<std::string>(), "second");
}

// Test operator[] on map
TEST(NodeIndexTest_552, AccessMapByKey_552) {
  YAML::Node node(YAML::NodeType::Map);
  node["key"] = "value";
  EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test copy constructor
TEST(NodeCopyTest_552, CopyConstructorSharesIdentity_552) {
  YAML::Node original("test");
  YAML::Node copy(original);
  EXPECT_TRUE(original.is(copy));
}

// Test assignment operator
TEST(NodeAssignTest_552, AssignmentFromValue_552) {
  YAML::Node node;
  node = "assigned_value";
  EXPECT_EQ(node.as<std::string>(), "assigned_value");
}

// Test as<string>() with fallback on a scalar that has numeric content
TEST(AsIfFallbackTest_552, NumericScalarReturnsAsString_552) {
  YAML::Node node("12345");
  std::string result = node.as<std::string>(std::string("fallback"));
  EXPECT_EQ(result, "12345");
}

// Test force_insert on map
TEST(NodeForceInsertTest_552, ForceInsertAddsEntry_552) {
  YAML::Node node(YAML::NodeType::Map);
  node.force_insert("key1", "value1");
  EXPECT_EQ(node.size(), 1u);
  EXPECT_EQ(node["key1"].as<std::string>(), "value1");
}

// Test iteration over sequence
TEST(NodeIterationTest_552, IterateOverSequence_552) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(10);
  node.push_back(20);
  node.push_back(30);
  
  std::vector<int> values;
  for (auto it = node.begin(); it != node.end(); ++it) {
    values.push_back(it->as<int>());
  }
  ASSERT_EQ(values.size(), 3u);
  EXPECT_EQ(values[0], 10);
  EXPECT_EQ(values[1], 20);
  EXPECT_EQ(values[2], 30);
}

// Test iteration over map
TEST(NodeIterationTest_552, IterateOverMap_552) {
  YAML::Node node(YAML::NodeType::Map);
  node["a"] = 1;
  node["b"] = 2;
  
  std::map<std::string, int> values;
  for (auto it = node.begin(); it != node.end(); ++it) {
    values[it->first.as<std::string>()] = it->second.as<int>();
  }
  EXPECT_EQ(values.size(), 2u);
  EXPECT_EQ(values["a"], 1);
  EXPECT_EQ(values["b"], 2);
}

// Test from YAML::Load
TEST(AsIfFallbackTest_552, LoadedNullNodeReturnsNullString_552) {
  YAML::Node node = YAML::Load("~");
  EXPECT_TRUE(node.IsNull());
  std::string result = node.as<std::string>(std::string("fallback"));
  EXPECT_EQ(result, "null");
}

TEST(AsIfFallbackTest_552, LoadedScalarNodeReturnsValue_552) {
  YAML::Node node = YAML::Load("hello");
  EXPECT_TRUE(node.IsScalar());
  std::string result = node.as<std::string>(std::string("fallback"));
  EXPECT_EQ(result, "hello");
}

TEST(AsIfFallbackTest_552, LoadedSequenceReturnsFallback_552) {
  YAML::Node node = YAML::Load("[1, 2, 3]");
  EXPECT_TRUE(node.IsSequence());
  std::string result = node.as<std::string>(std::string("fallback"));
  EXPECT_EQ(result, "fallback");
}

TEST(AsIfFallbackTest_552, LoadedMapReturnsFallback_552) {
  YAML::Node node = YAML::Load("{a: 1, b: 2}");
  EXPECT_TRUE(node.IsMap());
  std::string result = node.as<std::string>(std::string("fallback"));
  EXPECT_EQ(result, "fallback");
}
