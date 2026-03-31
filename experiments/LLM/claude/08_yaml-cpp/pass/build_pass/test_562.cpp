#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test: Default constructed nodes are not the same (is returns false since m_pNode is null)
TEST(NodeIsTest_562, DefaultConstructedNodesAreNotSame_562) {
  YAML::Node a;
  YAML::Node b;
  EXPECT_FALSE(a.is(b));
}

// Test: A default constructed node is not the same as itself via is()
TEST(NodeIsTest_562, DefaultNodeIsNotSameAsItself_562) {
  YAML::Node a;
  EXPECT_FALSE(a.is(a));
}

// Test: A node copied from another node is the same as the original
TEST(NodeIsTest_562, CopiedNodeIsSameAsOriginal_562) {
  YAML::Node a("hello");
  YAML::Node b = a;
  EXPECT_TRUE(a.is(b));
}

// Test: Two independently created scalar nodes with the same value are not the same
TEST(NodeIsTest_562, IndependentNodesWithSameValueAreNotSame_562) {
  YAML::Node a("hello");
  YAML::Node b("hello");
  EXPECT_FALSE(a.is(b));
}

// Test: Two independently created scalar nodes with different values are not the same
TEST(NodeIsTest_562, IndependentNodesWithDifferentValuesAreNotSame_562) {
  YAML::Node a("hello");
  YAML::Node b("world");
  EXPECT_FALSE(a.is(b));
}

// Test: Node assigned via reset shares identity
TEST(NodeIsTest_562, ResetNodeSharesIdentity_562) {
  YAML::Node a("hello");
  YAML::Node b;
  b.reset(a);
  EXPECT_TRUE(a.is(b));
}

// Test: Sequence node children are not the same as the parent
TEST(NodeIsTest_562, SequenceChildIsNotSameAsParent_562) {
  YAML::Node seq;
  seq.push_back("item1");
  seq.push_back("item2");
  YAML::Node child = seq[0];
  EXPECT_FALSE(seq.is(child));
}

// Test: Accessing the same key in a map returns the same node
TEST(NodeIsTest_562, SameKeyInMapReturnsSameNode_562) {
  YAML::Node map;
  map["key"] = "value";
  YAML::Node ref1 = map["key"];
  YAML::Node ref2 = map["key"];
  EXPECT_TRUE(ref1.is(ref2));
}

// Test: Different keys in a map are not the same node
TEST(NodeIsTest_562, DifferentKeysInMapAreNotSame_562) {
  YAML::Node map;
  map["key1"] = "value1";
  map["key2"] = "value2";
  YAML::Node ref1 = map["key1"];
  YAML::Node ref2 = map["key2"];
  EXPECT_FALSE(ref1.is(ref2));
}

// Test: is() is symmetric
TEST(NodeIsTest_562, IsIsSymmetric_562) {
  YAML::Node a("test");
  YAML::Node b = a;
  EXPECT_TRUE(a.is(b));
  EXPECT_TRUE(b.is(a));
}

// Test: is() with node created from type
TEST(NodeIsTest_562, NodeCreatedFromTypeNotSameAsAnother_562) {
  YAML::Node a(YAML::NodeType::Sequence);
  YAML::Node b(YAML::NodeType::Sequence);
  EXPECT_FALSE(a.is(b));
}

// Test: Copied node via copy constructor is the same
TEST(NodeIsTest_562, CopyConstructedNodeIsSame_562) {
  YAML::Node a(42);
  YAML::Node b(a);
  EXPECT_TRUE(a.is(b));
}

// Test: Loaded YAML nodes - same reference
TEST(NodeIsTest_562, LoadedYamlNodeCopyIsSame_562) {
  YAML::Node root = YAML::Load("{a: 1, b: 2}");
  YAML::Node aRef1 = root["a"];
  YAML::Node aRef2 = root["a"];
  EXPECT_TRUE(aRef1.is(aRef2));
}

// Test: Loaded YAML nodes - different keys are not the same
TEST(NodeIsTest_562, LoadedYamlDifferentKeysNotSame_562) {
  YAML::Node root = YAML::Load("{a: 1, b: 2}");
  YAML::Node aRef = root["a"];
  YAML::Node bRef = root["b"];
  EXPECT_FALSE(aRef.is(bRef));
}

// Test: A node with a value assigned is the same as its copy
TEST(NodeIsTest_562, AssignedNodeCopyIsSame_562) {
  YAML::Node a;
  a = "some value";
  YAML::Node b = a;
  EXPECT_TRUE(a.is(b));
}

// Test: Null type nodes independently created are not the same
TEST(NodeIsTest_562, IndependentNullNodesAreNotSame_562) {
  YAML::Node a(YAML::NodeType::Null);
  YAML::Node b(YAML::NodeType::Null);
  EXPECT_FALSE(a.is(b));
}

// Test: Sequence element references obtained from index are the same
TEST(NodeIsTest_562, SequenceElementRefIsSame_562) {
  YAML::Node seq;
  seq.push_back("a");
  seq.push_back("b");
  seq.push_back("c");
  YAML::Node elem1 = seq[1];
  YAML::Node elem2 = seq[1];
  EXPECT_TRUE(elem1.is(elem2));
}

// Test: Invalid node calling is() throws InvalidNode
TEST(NodeIsTest_562, InvalidNodeThrowsOnIs_562) {
  YAML::Node valid("hello");
  // Accessing a non-existent key on a map to get a zombie/invalid node
  // Actually, let's use operator[] on a scalar to get an invalid node
  YAML::Node scalar("test");
  // Trying to get a sub-key from a scalar that doesn't exist
  // A more reliable way to get an invalid node:
  YAML::Node map;
  map["exists"] = "yes";
  // Accessing a non-existent key on a const map doesn't create it, returns undefined
  // The zombie node pattern comes from accessing a key on a node that gets reassigned
  
  // Create a scenario where a node becomes invalid
  YAML::Node a;
  a["key"] = "value";
  YAML::Node b = a["key"];
  a.reset(YAML::Node("scalar")); // a is now a scalar, b's reference becomes invalid
  
  // b should now be an invalid/zombie node
  EXPECT_THROW(b.is(a), YAML::InvalidNode);
}

// Test: Calling is() with an invalid rhs throws InvalidNode
TEST(NodeIsTest_562, InvalidRhsNodeThrowsOnIs_562) {
  YAML::Node a;
  a["key"] = "value";
  YAML::Node b = a["key"];
  a.reset(YAML::Node("scalar"));
  
  YAML::Node valid("hello");
  EXPECT_THROW(valid.is(b), YAML::InvalidNode);
}
