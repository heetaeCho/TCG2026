// TEST_ID: 508
#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/yaml.h>

namespace {

class CloneTest_508 : public ::testing::Test {};

// Helper: build a small nested structure for structural checks.
static YAML::Node MakeNestedNode_508() {
  YAML::Node root(YAML::NodeType::Map);
  root["name"] = "yaml-cpp";
  root["version"] = 1;

  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back("a");
  seq.push_back("b");

  YAML::Node inner_map(YAML::NodeType::Map);
  inner_map["k1"] = "v1";
  inner_map["k2"] = 2;

  root["items"] = seq;
  root["meta"] = inner_map;
  return root;
}

}  // namespace

TEST_F(CloneTest_508, CloneScalarPreservesTypeAndValue_508) {
  YAML::Node original("hello");

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(original));

  EXPECT_EQ(cloned.Type(), original.Type());
  EXPECT_TRUE(cloned.IsScalar());
  EXPECT_EQ(cloned.Scalar(), original.Scalar());

  // Mutating clone should not affect original (deep copy behavior).
  cloned = "world";
  EXPECT_EQ(original.Scalar(), "hello");
  EXPECT_EQ(cloned.Scalar(), "world");
}

TEST_F(CloneTest_508, CloneEmptySequencePreservesTypeAndSize_508) {
  YAML::Node original(YAML::NodeType::Sequence);
  ASSERT_TRUE(original.IsSequence());
  EXPECT_EQ(original.size(), 0u);

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(original));

  EXPECT_TRUE(cloned.IsSequence());
  EXPECT_EQ(cloned.Type(), original.Type());
  EXPECT_EQ(cloned.size(), 0u);

  // Ensure mutation doesn't reflect back.
  cloned.push_back(1);
  EXPECT_EQ(cloned.size(), 1u);
  EXPECT_EQ(original.size(), 0u);
}

TEST_F(CloneTest_508, CloneEmptyMapPreservesTypeAndSize_508) {
  YAML::Node original(YAML::NodeType::Map);
  ASSERT_TRUE(original.IsMap());
  EXPECT_EQ(original.size(), 0u);

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(original));

  EXPECT_TRUE(cloned.IsMap());
  EXPECT_EQ(cloned.Type(), original.Type());
  EXPECT_EQ(cloned.size(), 0u);

  // Ensure mutation doesn't reflect back.
  cloned["a"] = 1;
  EXPECT_EQ(cloned.size(), 1u);
  EXPECT_EQ(original.size(), 0u);
}

TEST_F(CloneTest_508, CloneSequencePreservesElements_508) {
  YAML::Node original(YAML::NodeType::Sequence);
  original.push_back(10);
  original.push_back(20);
  original.push_back("thirty");

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(original));

  ASSERT_TRUE(cloned.IsSequence());
  ASSERT_EQ(cloned.size(), original.size());

  EXPECT_EQ(cloned[0].as<int>(), 10);
  EXPECT_EQ(cloned[1].as<int>(), 20);
  EXPECT_EQ(cloned[2].as<std::string>(), "thirty");

  // Deep-copy check: change clone, original unchanged.
  cloned.push_back(40);
  EXPECT_EQ(cloned.size(), 4u);
  EXPECT_EQ(original.size(), 3u);
}

TEST_F(CloneTest_508, CloneMapPreservesKeyValuePairs_508) {
  YAML::Node original(YAML::NodeType::Map);
  original["a"] = 1;
  original["b"] = "two";
  original["c"] = true;

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(original));

  ASSERT_TRUE(cloned.IsMap());
  ASSERT_EQ(cloned.size(), original.size());

  EXPECT_EQ(cloned["a"].as<int>(), 1);
  EXPECT_EQ(cloned["b"].as<std::string>(), "two");
  EXPECT_EQ(cloned["c"].as<bool>(), true);

  // Deep-copy check: changing clone doesn't affect original.
  cloned["a"] = 999;
  EXPECT_EQ(cloned["a"].as<int>(), 999);
  EXPECT_EQ(original["a"].as<int>(), 1);
}

TEST_F(CloneTest_508, CloneNestedStructurePreservesShapeAndValues_508) {
  YAML::Node original = MakeNestedNode_508();

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(original));

  ASSERT_TRUE(cloned.IsMap());
  EXPECT_EQ(cloned["name"].as<std::string>(), "yaml-cpp");
  EXPECT_EQ(cloned["version"].as<int>(), 1);

  ASSERT_TRUE(cloned["items"].IsSequence());
  ASSERT_EQ(cloned["items"].size(), 2u);
  EXPECT_EQ(cloned["items"][0].as<std::string>(), "a");
  EXPECT_EQ(cloned["items"][1].as<std::string>(), "b");

  ASSERT_TRUE(cloned["meta"].IsMap());
  EXPECT_EQ(cloned["meta"]["k1"].as<std::string>(), "v1");
  EXPECT_EQ(cloned["meta"]["k2"].as<int>(), 2);

  // Deep-copy check: mutate nested clone, ensure original unaffected.
  cloned["meta"]["k2"] = 999;
  EXPECT_EQ(cloned["meta"]["k2"].as<int>(), 999);
  EXPECT_EQ(original["meta"]["k2"].as<int>(), 2);
}

TEST_F(CloneTest_508, ClonePreservesTagAndStyleWhenSet_508) {
  YAML::Node original("value");
  original.SetTag("!custom_tag");

  // Style enum values are provided by yaml-cpp; for scalar, style may or may not be meaningful,
  // but it is observable through the public interface.
  original.SetStyle(YAML::EmitterStyle::Flow);

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(original));

  EXPECT_EQ(cloned.Tag(), "!custom_tag");
  EXPECT_EQ(cloned.Style(), YAML::EmitterStyle::Flow);

  // Changing clone tag/style should not impact original.
  cloned.SetTag("!other");
  cloned.SetStyle(YAML::EmitterStyle::Block);
  EXPECT_EQ(original.Tag(), "!custom_tag");
  EXPECT_EQ(original.Style(), YAML::EmitterStyle::Flow);
}

TEST_F(CloneTest_508, CloneOfUndefinedNodeRemainsUndefined_508) {
  // Accessing a missing key typically yields an undefined ("Zombie") node in yaml-cpp.
  YAML::Node container(YAML::NodeType::Map);
  YAML::Node missing = container["does_not_exist"];

  // Observable behavior: undefined nodes generally convert to false.
  EXPECT_FALSE(static_cast<bool>(missing));

  YAML::Node cloned;
  ASSERT_NO_THROW(cloned = YAML::Clone(missing));

  EXPECT_FALSE(static_cast<bool>(cloned));

  // Also ensure that making the cloned node defined doesn't back-propagate.
  cloned = "now_defined";
  EXPECT_TRUE(static_cast<bool>(cloned));
  EXPECT_FALSE(static_cast<bool>(missing));
}

TEST_F(CloneTest_508, CloneDoesNotThrowForVariousNodeKinds_508) {
  YAML::Node scalar("s");
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(1);
  YAML::Node map(YAML::NodeType::Map);
  map["k"] = "v";

  EXPECT_NO_THROW((void)YAML::Clone(scalar));
  EXPECT_NO_THROW((void)YAML::Clone(seq));
  EXPECT_NO_THROW((void)YAML::Clone(map));
}