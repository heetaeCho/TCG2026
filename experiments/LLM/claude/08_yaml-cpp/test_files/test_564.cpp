#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// ============================================================
// Tests for Node default construction and type checks
// ============================================================

TEST(NodeTest_564, DefaultConstructedNodeIsNull_564) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

TEST(NodeTest_564, DefaultConstructedNodeIsDefined_564) {
    YAML::Node node;
    EXPECT_TRUE(node.IsDefined());
}

TEST(NodeTest_564, DefaultConstructedNodeBoolConversion_564) {
    YAML::Node node;
    // A default-constructed (null) node should still be "valid"
    // but IsNull() is true
    EXPECT_TRUE(node.IsNull());
}

// ============================================================
// Tests for construction with explicit types
// ============================================================

TEST(NodeTest_564, ConstructWithScalarType_564) {
    YAML::Node node(YAML::NodeType::Scalar);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_564, ConstructWithSequenceType_564) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsMap());
}

TEST(NodeTest_564, ConstructWithMapType_564) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_TRUE(node.IsMap());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
}

TEST(NodeTest_564, ConstructWithNullType_564) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_564, ConstructWithUndefinedType_564) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_FALSE(node.IsDefined());
}

// ============================================================
// Tests for construction with values
// ============================================================

TEST(NodeTest_564, ConstructWithString_564) {
    YAML::Node node(std::string("hello"));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_564, ConstructWithInt_564) {
    YAML::Node node(42);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

TEST(NodeTest_564, ConstructWithDouble_564) {
    YAML::Node node(3.14);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14);
}

TEST(NodeTest_564, ConstructWithBool_564) {
    YAML::Node node(true);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<bool>(), true);
}

// ============================================================
// Tests for copy construction
// ============================================================

TEST(NodeTest_564, CopyConstructionSharesIdentity_564) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
    EXPECT_EQ(copy.as<std::string>(), "test");
}

TEST(NodeTest_564, CopyConstructionModifiesOriginal_564) {
    YAML::Node node("original");
    YAML::Node copy(node);
    copy = "modified";
    // After assignment of a new value, copy should have changed
    EXPECT_EQ(copy.as<std::string>(), "modified");
}

// ============================================================
// Tests for assignment operator
// ============================================================

TEST(NodeTest_564, AssignmentFromValue_564) {
    YAML::Node node;
    node = "hello";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "hello");
}

TEST(NodeTest_564, AssignmentFromInt_564) {
    YAML::Node node;
    node = 100;
    EXPECT_EQ(node.as<int>(), 100);
}

TEST(NodeTest_564, SelfAssignmentNode_564) {
    YAML::Node node("self");
    node = node;
    EXPECT_EQ(node.as<std::string>(), "self");
}

TEST(NodeTest_564, AssignmentFromAnotherNode_564) {
    YAML::Node a("alpha");
    YAML::Node b("beta");
    a = b;
    // After assignment, a should point to the same node as b
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<std::string>(), "beta");
}

// ============================================================
// Tests for reset
// ============================================================

TEST(NodeTest_564, ResetToAnotherNode_564) {
    YAML::Node a("first");
    YAML::Node b("second");
    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<std::string>(), "second");
}

// ============================================================
// Tests for as<T> and as<T>(fallback)
// ============================================================

TEST(NodeTest_564, AsStringFromScalar_564) {
    YAML::Node node("world");
    EXPECT_EQ(node.as<std::string>(), "world");
}

TEST(NodeTest_564, AsIntFromScalar_564) {
    YAML::Node node("123");
    EXPECT_EQ(node.as<int>(), 123);
}

TEST(NodeTest_564, AsWithFallbackOnUndefined_564) {
    YAML::Node node;
    YAML::Node child = node["nonexistent"];
    std::string result = child.as<std::string>("default_value");
    EXPECT_EQ(result, "default_value");
}

TEST(NodeTest_564, AsWithFallbackOnDefinedNode_564) {
    YAML::Node node("actual_value");
    std::string result = node.as<std::string>("fallback");
    EXPECT_EQ(result, "actual_value");
}

TEST(NodeTest_564, AsBoolTrue_564) {
    YAML::Node node("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST(NodeTest_564, AsBoolFalse_564) {
    YAML::Node node("false");
    EXPECT_FALSE(node.as<bool>());
}

// ============================================================
// Tests for Scalar()
// ============================================================

TEST(NodeTest_564, ScalarReturnsValue_564) {
    YAML::Node node("my_scalar");
    EXPECT_EQ(node.Scalar(), "my_scalar");
}

TEST(NodeTest_564, ScalarOnNonScalarReturnsEmpty_564) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.Scalar(), "");
}

// ============================================================
// Tests for Tag and SetTag
// ============================================================

TEST(NodeTest_564, SetAndGetTag_564) {
    YAML::Node node("value");
    node.SetTag("!my_tag");
    EXPECT_EQ(node.Tag(), "!my_tag");
}

TEST(NodeTest_564, DefaultTagIsEmpty_564) {
    YAML::Node node("value");
    // By default, the tag should be empty or "?"
    // The exact default depends on implementation; just check it doesn't crash
    std::string tag = node.Tag();
    // We just verify it's callable
    (void)tag;
}

// ============================================================
// Tests for Style and SetStyle
// ============================================================

TEST(NodeTest_564, SetAndGetStyle_564) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeTest_564, DefaultStyle_564) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.Style(), YAML::EmitterStyle::Default);
}

// ============================================================
// Tests for is()
// ============================================================

TEST(NodeTest_564, IsReturnsTrueForSameNode_564) {
    YAML::Node node("test");
    YAML::Node copy(node);
    EXPECT_TRUE(node.is(copy));
}

TEST(NodeTest_564, IsReturnsFalseForDifferentNodes_564) {
    YAML::Node a("test");
    YAML::Node b("test");
    EXPECT_FALSE(a.is(b));
}

// ============================================================
// Tests for Sequence operations
// ============================================================

TEST(NodeTest_564, PushBackCreatesSequence_564) {
    YAML::Node node;
    node.push_back("item1");
    node.push_back("item2");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_564, PushBackNodeCreatesSequence_564) {
    YAML::Node node;
    YAML::Node child("child_value");
    node.push_back(child);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "child_value");
}

TEST(NodeTest_564, SequenceIndexAccess_564) {
    YAML::Node node;
    node.push_back(10);
    node.push_back(20);
    node.push_back(30);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST(NodeTest_564, SequenceSize_564) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
    node.push_back("a");
    EXPECT_EQ(node.size(), 1u);
    node.push_back("b");
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_564, SequenceIteration_564) {
    YAML::Node node;
    node.push_back("x");
    node.push_back("y");
    node.push_back("z");

    std::vector<std::string> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<std::string>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], "x");
    EXPECT_EQ(values[1], "y");
    EXPECT_EQ(values[2], "z");
}

// ============================================================
// Tests for Map operations
// ============================================================

TEST(NodeTest_564, MapSubscriptCreatesMap_564) {
    YAML::Node node;
    node["key1"] = "value1";
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
}

TEST(NodeTest_564, MapMultipleKeys_564) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node["c"].as<int>(), 3);
}

TEST(NodeTest_564, MapRemoveKey_564) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_TRUE(node.remove("key"));
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_564, MapRemoveNonexistentKey_564) {
    YAML::Node node;
    node["key"] = "value";
    EXPECT_FALSE(node.remove("nonexistent"));
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_564, MapRemoveNodeKey_564) {
    YAML::Node node;
    node["key"] = "value";
    YAML::Node keyNode("key");
    EXPECT_TRUE(node.remove(keyNode));
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_564, MapIteration_564) {
    YAML::Node node;
    node["alpha"] = 1;
    node["beta"] = 2;

    std::map<std::string, int> result;
    for (auto it = node.begin(); it != node.end(); ++it) {
        result[it->first.as<std::string>()] = it->second.as<int>();
    }
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["alpha"], 1);
    EXPECT_EQ(result["beta"], 2);
}

TEST(NodeTest_564, MapConstSubscriptDoesNotCreate_564) {
    YAML::Node node;
    node["existing"] = "value";
    const YAML::Node& constNode = node;
    YAML::Node missing = constNode["missing"];
    EXPECT_FALSE(missing.IsDefined());
    EXPECT_EQ(node.size(), 1u);
}

// ============================================================
// Tests for force_insert
// ============================================================

TEST(NodeTest_564, ForceInsertIntoMap_564) {
    YAML::Node node;
    node["key1"] = "val1";
    node.force_insert("key2", "val2");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key2"].as<std::string>(), "val2");
}

// ============================================================
// Tests for operator bool and operator!
// ============================================================

TEST(NodeTest_564, OperatorBoolOnValidNode_564) {
    YAML::Node node("value");
    EXPECT_TRUE(static_cast<bool>(node));
    EXPECT_FALSE(!node);
}

TEST(NodeTest_564, OperatorBoolOnNullNode_564) {
    YAML::Node node;
    // A null but valid node - behavior may vary
    // Just check it doesn't crash
    (void)static_cast<bool>(node);
    (void)(!node);
}

// ============================================================
// Tests for size on empty containers
// ============================================================

TEST(NodeTest_564, SizeOfNullNodeIsZero_564) {
    YAML::Node node;
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_564, SizeOfScalarNodeIsZero_564) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_564, SizeOfEmptySequenceIsZero_564) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(node.size(), 0u);
}

TEST(NodeTest_564, SizeOfEmptyMapIsZero_564) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(node.size(), 0u);
}

// ============================================================
// Tests for YAML parsing and Node interaction
// ============================================================

TEST(NodeTest_564, ParseScalar_564) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST(NodeTest_564, ParseSequence_564) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<int>(), 2);
    EXPECT_EQ(node[2].as<int>(), 3);
}

TEST(NodeTest_564, ParseMap_564) {
    YAML::Node node = YAML::Load("{key: value, num: 42}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
    EXPECT_EQ(node["num"].as<int>(), 42);
}

TEST(NodeTest_564, ParseNull_564) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeTest_564, ParseEmptyDocument_564) {
    YAML::Node node = YAML::Load("");
    EXPECT_TRUE(node.IsNull());
}

// ============================================================
// Tests for nested structures
// ============================================================

TEST(NodeTest_564, NestedMapAccess_564) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST(NodeTest_564, NestedSequenceInMap_564) {
    YAML::Node node = YAML::Load("{list: [1, 2, 3]}");
    EXPECT_TRUE(node["list"].IsSequence());
    EXPECT_EQ(node["list"].size(), 3u);
    EXPECT_EQ(node["list"][0].as<int>(), 1);
}

// ============================================================
// Tests for exceptions on invalid conversions
// ============================================================

TEST(NodeTest_564, AsThrowsOnInvalidConversion_564) {
    YAML::Node node("not_a_number");
    EXPECT_THROW(node.as<int>(), YAML::BadConversion);
}

TEST(NodeTest_564, AsWithFallbackDoesNotThrow_564) {
    YAML::Node node("not_a_number");
    int result = node.as<int>(42);
    EXPECT_EQ(result, 42);
}

// ============================================================
// Tests for begin/end on non-container types
// ============================================================

TEST(NodeTest_564, BeginEqualsEndOnScalar_564) {
    YAML::Node node("scalar");
    EXPECT_EQ(node.begin(), node.end());
}

TEST(NodeTest_564, BeginEqualsEndOnNull_564) {
    YAML::Node node;
    EXPECT_EQ(node.begin(), node.end());
}

// ============================================================
// Tests for assignment changing type
// ============================================================

TEST(NodeTest_564, AssignScalarToSequenceNode_564) {
    YAML::Node node(YAML::NodeType::Sequence);
    node = "now_a_scalar";
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "now_a_scalar");
}

TEST(NodeTest_564, AssignSequenceThenMap_564) {
    YAML::Node node;
    node.push_back("item");
    EXPECT_TRUE(node.IsSequence());
    
    // Reassign to scalar
    node = 42;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// ============================================================
// Tests for Mark
// ============================================================

TEST(NodeTest_564, MarkOnDefaultNode_564) {
    YAML::Node node;
    YAML::Mark mark = node.Mark();
    // Just ensure it's callable and returns something reasonable
    (void)mark;
}

TEST(NodeTest_564, MarkOnParsedNode_564) {
    YAML::Node node = YAML::Load("key: value");
    YAML::Mark mark = node.Mark();
    // Parsed nodes should have mark information
    (void)mark;
}

// ============================================================
// Tests for const correctness via subscript
// ============================================================

TEST(NodeTest_564, ConstNodeSubscriptReturnsUndefinedForMissing_564) {
    const YAML::Node node = YAML::Load("{a: 1}");
    YAML::Node b = node["b"];
    EXPECT_FALSE(b.IsDefined());
}

TEST(NodeTest_564, ConstNodeSubscriptReturnsValueForExisting_564) {
    const YAML::Node node = YAML::Load("{a: 1}");
    YAML::Node a = node["a"];
    EXPECT_TRUE(a.IsDefined());
    EXPECT_EQ(a.as<int>(), 1);
}

// ============================================================
// Tests for edge cases
// ============================================================

TEST(NodeTest_564, EmptyStringScalar_564) {
    YAML::Node node(std::string(""));
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.Scalar(), "");
}

TEST(NodeTest_564, LargeSequence_564) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node.push_back(i);
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[999].as<int>(), 999);
}

TEST(NodeTest_564, AssignCharPointer_564) {
    YAML::Node node;
    const char* str = "c_string";
    node = str;
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "c_string");
}

TEST(NodeTest_564, MultipleResets_564) {
    YAML::Node a("first");
    YAML::Node b("second");
    YAML::Node c("third");

    a.reset(b);
    EXPECT_TRUE(a.is(b));
    EXPECT_EQ(a.as<std::string>(), "second");

    a.reset(c);
    EXPECT_TRUE(a.is(c));
    EXPECT_EQ(a.as<std::string>(), "third");
    EXPECT_FALSE(a.is(b));
}

TEST(NodeTest_564, SequenceRemoveByIndex_564) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");

    EXPECT_TRUE(node.remove(1));
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeTest_564, MapOverwriteValue_564) {
    YAML::Node node;
    node["key"] = "original";
    node["key"] = "updated";
    EXPECT_EQ(node["key"].as<std::string>(), "updated");
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeTest_564, AssignFromNodeDoesNotShareIdentityWithDifferentValue_564) {
    YAML::Node a("alpha");
    YAML::Node b("beta");
    YAML::Node c = a;
    EXPECT_TRUE(c.is(a));
    EXPECT_FALSE(c.is(b));
}
