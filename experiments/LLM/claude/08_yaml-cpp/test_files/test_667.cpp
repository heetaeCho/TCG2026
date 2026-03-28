#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace YAML {
namespace detail {

class NodeEqualsTest_667 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test that a node with a scalar string value equals the same string
TEST_F(NodeEqualsTest_667, ScalarStringEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals(std::string("hello"), pMemory));
}

// Test that a node with a scalar string value does not equal a different string
TEST_F(NodeEqualsTest_667, ScalarStringNotEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_FALSE(n.equals(std::string("world"), pMemory));
}

// Test equals with const char* overload
TEST_F(NodeEqualsTest_667, EqualsConstCharPtr_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals("test", pMemory));
}

// Test equals with const char* overload - not equal
TEST_F(NodeEqualsTest_667, NotEqualsConstCharPtr_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_FALSE(n.equals("other", pMemory));
}

// Test equals with integer value
TEST_F(NodeEqualsTest_667, ScalarIntEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("42");

  EXPECT_TRUE(n.equals(42, pMemory));
}

// Test equals with integer value - not equal
TEST_F(NodeEqualsTest_667, ScalarIntNotEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("42");

  EXPECT_FALSE(n.equals(99, pMemory));
}

// Test equals with double value
TEST_F(NodeEqualsTest_667, ScalarDoubleEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("3.14");

  EXPECT_TRUE(n.equals(3.14, pMemory));
}

// Test equals with boolean true
TEST_F(NodeEqualsTest_667, ScalarBoolTrueEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("true");

  EXPECT_TRUE(n.equals(true, pMemory));
}

// Test equals with boolean false
TEST_F(NodeEqualsTest_667, ScalarBoolFalseEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("false");

  EXPECT_TRUE(n.equals(false, pMemory));
}

// Test equals on a Null node with a string - should not equal
TEST_F(NodeEqualsTest_667, NullNodeNotEqualsString_667) {
  node& n = pMemory->create_node();
  n.set_null();

  EXPECT_FALSE(n.equals(std::string("hello"), pMemory));
}

// Test equals with empty string
TEST_F(NodeEqualsTest_667, EmptyStringEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");

  EXPECT_TRUE(n.equals(std::string(""), pMemory));
}

// Test equals with empty const char*
TEST_F(NodeEqualsTest_667, EmptyConstCharPtrEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");

  EXPECT_TRUE(n.equals("", pMemory));
}

// Test that a non-scalar (sequence) node doesn't equal a string
TEST_F(NodeEqualsTest_667, SequenceNodeNotEqualsString_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);

  EXPECT_FALSE(n.equals(std::string("hello"), pMemory));
}

// Test that a non-scalar (map) node doesn't equal a string
TEST_F(NodeEqualsTest_667, MapNodeNotEqualsString_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);

  EXPECT_FALSE(n.equals(std::string("hello"), pMemory));
}

// Test equals with negative integer
TEST_F(NodeEqualsTest_667, ScalarNegativeIntEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("-10");

  EXPECT_TRUE(n.equals(-10, pMemory));
}

// Test equals with zero
TEST_F(NodeEqualsTest_667, ScalarZeroEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("0");

  EXPECT_TRUE(n.equals(0, pMemory));
}

// Test that a scalar with non-numeric content doesn't equal an integer
TEST_F(NodeEqualsTest_667, NonNumericScalarNotEqualsInt_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("abc");

  EXPECT_FALSE(n.equals(42, pMemory));
}

// Test is() method - same node
TEST_F(NodeEqualsTest_667, IsSameNode_667) {
  node& n = pMemory->create_node();
  EXPECT_TRUE(n.is(n));
}

// Test is() method - different nodes
TEST_F(NodeEqualsTest_667, IsDifferentNode_667) {
  node& n1 = pMemory->create_node();
  node& n2 = pMemory->create_node();
  EXPECT_FALSE(n1.is(n2));
}

// Test basic node properties
TEST_F(NodeEqualsTest_667, DefaultNodeIsUndefined_667) {
  node& n = pMemory->create_node();
  EXPECT_EQ(n.type(), NodeType::Undefined);
}

// Test mark_defined
TEST_F(NodeEqualsTest_667, MarkDefined_667) {
  node& n = pMemory->create_node();
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeEqualsTest_667, SetTypeScalar_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(n.type(), NodeType::Scalar);
}

// Test set_type to Sequence
TEST_F(NodeEqualsTest_667, SetTypeSequence_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.type(), NodeType::Sequence);
}

// Test set_type to Map
TEST_F(NodeEqualsTest_667, SetTypeMap_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  EXPECT_EQ(n.type(), NodeType::Map);
}

// Test set_null
TEST_F(NodeEqualsTest_667, SetNull_667) {
  node& n = pMemory->create_node();
  n.set_null();
  EXPECT_EQ(n.type(), NodeType::Null);
}

// Test set_scalar and scalar getter
TEST_F(NodeEqualsTest_667, SetScalarAndGet_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test_value");
  EXPECT_EQ(n.scalar(), "test_value");
}

// Test set_tag and tag getter
TEST_F(NodeEqualsTest_667, SetTagAndGet_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_tag("!mytag");
  EXPECT_EQ(n.tag(), "!mytag");
}

// Test set_style and style getter
TEST_F(NodeEqualsTest_667, SetStyleAndGet_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(n.style(), EmitterStyle::Flow);
}

// Test size of empty sequence
TEST_F(NodeEqualsTest_667, EmptySequenceSize_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.size(), 0u);
}

// Test push_back increases size
TEST_F(NodeEqualsTest_667, PushBackIncreasesSize_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);

  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");

  n.push_back(child, pMemory);
  EXPECT_EQ(n.size(), 1u);
}

// Test push_back multiple items
TEST_F(NodeEqualsTest_667, PushBackMultipleItems_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);

  for (int i = 0; i < 3; ++i) {
    node& child = pMemory->create_node();
    child.set_type(NodeType::Scalar);
    child.set_scalar(std::to_string(i));
    n.push_back(child, pMemory);
  }
  EXPECT_EQ(n.size(), 3u);
}

// Test insert into map
TEST_F(NodeEqualsTest_667, InsertIntoMap_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");

  n.insert(key, value, pMemory);
  EXPECT_EQ(n.size(), 1u);
}

// Test get from map
TEST_F(NodeEqualsTest_667, GetFromMap_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");

  n.insert(key, value, pMemory);

  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->scalar(), "myvalue");
  }
}

// Test get non-existent key from map
TEST_F(NodeEqualsTest_667, GetNonExistentKey_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);

  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test set_data copies data from another node
TEST_F(NodeEqualsTest_667, SetDataFromAnotherNode_667) {
  node& src = pMemory->create_node();
  src.set_type(NodeType::Scalar);
  src.set_scalar("source_value");

  node& dst = pMemory->create_node();
  dst.set_data(src);

  EXPECT_EQ(dst.scalar(), "source_value");
  EXPECT_EQ(dst.type(), NodeType::Scalar);
}

// Test equals with long string
TEST_F(NodeEqualsTest_667, LongStringEquals_667) {
  std::string longStr(1000, 'a');
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar(longStr);

  EXPECT_TRUE(n.equals(longStr, pMemory));
}

// Test equals with special characters in string
TEST_F(NodeEqualsTest_667, SpecialCharsEquals_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello\nworld\t!");

  EXPECT_TRUE(n.equals(std::string("hello\nworld\t!"), pMemory));
}

// Test remove from map
TEST_F(NodeEqualsTest_667, RemoveFromMap_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");

  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");

  n.insert(key, value, pMemory);
  EXPECT_EQ(n.size(), 1u);

  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeEqualsTest_667, RemoveNonExistentKey_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);

  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test begin/end on empty sequence
TEST_F(NodeEqualsTest_667, EmptySequenceIterators_667) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

}  // namespace detail
}  // namespace YAML
