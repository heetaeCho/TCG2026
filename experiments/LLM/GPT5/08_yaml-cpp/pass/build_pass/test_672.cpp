// TEST_ID: 672
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

#include <string>

namespace {

class NodeApiTest_672 : public ::testing::Test {};

TEST_F(NodeApiTest_672, LoadScalarAndAsWorks_672) {
  YAML::Node n = YAML::Load("hello");
  ASSERT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "hello");
}

TEST_F(NodeApiTest_672, MissingKeyIsNotDefinedAndFallbackAsWorks_672) {
  YAML::Node n = YAML::Load("{a: 1}");

  YAML::Node missing = n["b"];
  EXPECT_FALSE(missing.IsDefined());

  EXPECT_EQ(missing.as<int>(42), 42);
  EXPECT_ANY_THROW((void)missing.as<int>());
}

TEST_F(NodeApiTest_672, SequenceIndexAutoExpandsAndSizeReflectsHighestIndexPlusOne_672) {
  YAML::Node seq(YAML::NodeType::Sequence);
  EXPECT_EQ(seq.size(), 0u);

  seq[0] = 0;
  EXPECT_EQ(seq.size(), 1u);

  seq[2] = "two";
  EXPECT_EQ(seq.size(), 3u);

  EXPECT_EQ(seq[0].as<int>(), 0);
  EXPECT_EQ(seq[2].as<std::string>(), "two");

  // Behavior of the "hole" node (index 1) can vary (null vs undefined);
  // we only assert it's safe to query and doesn't crash.
  (void)seq[1].IsDefined();
  (void)seq[1].IsNull();
}

TEST_F(NodeApiTest_672, CopySharesUnderlyingNodeSoMutationIsObservable_672) {
  YAML::Node root = YAML::Load("[0, 1, 2]");
  YAML::Node other = root;

  other[0] = 5;

  EXPECT_EQ(root[0].as<int>(), 5);
  EXPECT_EQ(other[0].as<int>(), 5);
}

TEST_F(NodeApiTest_672, RemoveKeyReturnsWhetherRemovalHappened_672) {
  YAML::Node m = YAML::Load("{key: 5}");
  ASSERT_TRUE(m["key"].IsDefined());

  EXPECT_TRUE(m.remove("key"));
  EXPECT_FALSE(m["key"].IsDefined());

  // Removing again should report failure.
  EXPECT_FALSE(m.remove("key"));
}

TEST_F(NodeApiTest_672, ResetReplacesNodeContents_672) {
  YAML::Node n = YAML::Load("a");
  YAML::Node replacement = YAML::Load("b");

  n.reset(replacement);

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "b");
  EXPECT_EQ(replacement.as<std::string>(), "b");
}

TEST_F(NodeApiTest_672, AssignmentOverwritesAndExistingSubnodeRemainsValid_672) {
  YAML::Node root;
  root.push_back("zero");
  root.push_back("one");
  root.push_back("two");

  YAML::Node two = root[2];
  ASSERT_TRUE(two.IsDefined());
  EXPECT_EQ(two.as<std::string>(), "two");

  // Overwrite root entirely; the previously-referenced 'two' should remain usable.
  root = "scalar";

  EXPECT_TRUE(root.IsScalar());
  EXPECT_EQ(root.as<std::string>(), "scalar");
  EXPECT_EQ(two.as<std::string>(), "two");
}

TEST_F(NodeApiTest_672, ForceInsertDoesNotThrowAndKeyIsReadable_672) {
  YAML::Node m(YAML::NodeType::Map);

  EXPECT_NO_THROW(m.force_insert("a", 1));
  EXPECT_TRUE(m["a"].IsDefined());
  EXPECT_EQ(m["a"].as<int>(), 1);

  // If duplicates are allowed or overwrite occurs depends on implementation;
  // we only require that the operation is observable and doesn't throw.
  EXPECT_NO_THROW(m.force_insert("a", 2));
  EXPECT_TRUE(m["a"].IsDefined());
  EXPECT_NO_THROW((void)m["a"].as<int>());
}

}  // namespace