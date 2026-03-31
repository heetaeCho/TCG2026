#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_248 : public ::testing::Test {
protected:
    void SetUp() override {
        pMemory = create_shared_memory_holder();
    }

    shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_248, DefaultConstructionNotDefined_248) {
    node& n = pMemory->create_node();
    EXPECT_FALSE(n.is_defined());
}

// Test default type is Undefined
TEST_F(NodeTest_248, DefaultTypeIsUndefined_248) {
    node& n = pMemory->create_node();
    EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_248, MarkDefinedMakesNodeDefined_248) {
    node& n = pMemory->create_node();
    n.mark_defined();
    EXPECT_TRUE(n.is_defined());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_248, SetMarkAndRetrieve_248) {
    node& n = pMemory->create_node();
    Mark m;
    m.pos = 10;
    m.line = 5;
    m.column = 3;
    n.set_mark(m);
    const Mark& retrieved = n.mark();
    EXPECT_EQ(10, retrieved.pos);
    EXPECT_EQ(5, retrieved.line);
    EXPECT_EQ(3, retrieved.column);
}

// Test set_type to Scalar
TEST_F(NodeTest_248, SetTypeScalar_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_248, SetTypeSequence_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Sequence);
    EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_248, SetTypeMap_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Map);
    EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null sets type to Null
TEST_F(NodeTest_248, SetNull_248) {
    node& n = pMemory->create_node();
    n.set_null();
    EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_248, SetScalarAndRetrieve_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    n.set_scalar("hello");
    EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_248, SetScalarEmptyString_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    n.set_scalar("");
    EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_248, SetTagAndRetrieve_248) {
    node& n = pMemory->create_node();
    n.set_tag("!mytag");
    EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_248, SetTagEmpty_248) {
    node& n = pMemory->create_node();
    n.set_tag("");
    EXPECT_EQ("", n.tag());
}

// Test set_style
TEST_F(NodeTest_248, SetStyleFlow_248) {
    node& n = pMemory->create_node();
    n.set_style(EmitterStyle::Flow);
    EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Block
TEST_F(NodeTest_248, SetStyleBlock_248) {
    node& n = pMemory->create_node();
    n.set_style(EmitterStyle::Block);
    EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_style Default
TEST_F(NodeTest_248, SetStyleDefault_248) {
    node& n = pMemory->create_node();
    n.set_style(EmitterStyle::Default);
    EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node
TEST_F(NodeTest_248, IsSameNode_248) {
    node& n = pMemory->create_node();
    EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_248, IsDifferentNode_248) {
    node& n1 = pMemory->create_node();
    node& n2 = pMemory->create_node();
    EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_248, RefIsNotNull_248) {
    node& n = pMemory->create_node();
    EXPECT_NE(nullptr, n.ref());
}

// Test size on empty sequence
TEST_F(NodeTest_248, SizeEmptySequence_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Sequence);
    EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_248, PushBackIncreasesSize_248) {
    node& seq = pMemory->create_node();
    seq.set_type(NodeType::Sequence);

    node& elem = pMemory->create_node();
    elem.set_type(NodeType::Scalar);
    elem.set_scalar("item1");

    seq.push_back(elem, pMemory);
    EXPECT_EQ(1u, seq.size());
}

// Test push_back multiple elements
TEST_F(NodeTest_248, PushBackMultipleElements_248) {
    node& seq = pMemory->create_node();
    seq.set_type(NodeType::Sequence);

    for (int i = 0; i < 5; i++) {
        node& elem = pMemory->create_node();
        elem.set_type(NodeType::Scalar);
        elem.set_scalar("item" + std::to_string(i));
        seq.push_back(elem, pMemory);
    }
    EXPECT_EQ(5u, seq.size());
}

// Test begin == end for empty sequence
TEST_F(NodeTest_248, BeginEqualsEndForEmpty_248) {
    node& seq = pMemory->create_node();
    seq.set_type(NodeType::Sequence);
    EXPECT_TRUE(seq.begin() == seq.end());
}

// Test insert into map
TEST_F(NodeTest_248, InsertIntoMap_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    node& key = pMemory->create_node();
    key.set_type(NodeType::Scalar);
    key.set_scalar("key1");

    node& value = pMemory->create_node();
    value.set_type(NodeType::Scalar);
    value.set_scalar("value1");

    map.insert(key, value, pMemory);
    EXPECT_EQ(1u, map.size());
}

// Test get on map
TEST_F(NodeTest_248, GetFromMap_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    node& key = pMemory->create_node();
    key.set_type(NodeType::Scalar);
    key.set_scalar("mykey");

    node& value = pMemory->create_node();
    value.set_type(NodeType::Scalar);
    value.set_scalar("myvalue");

    map.insert(key, value, pMemory);

    node* result = map.get(key, pMemory);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ("myvalue", result->scalar());
}

// Test get with string key
TEST_F(NodeTest_248, GetWithStringKey_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    node& key = pMemory->create_node();
    key.set_type(NodeType::Scalar);
    key.set_scalar("strkey");

    node& value = pMemory->create_node();
    value.set_type(NodeType::Scalar);
    value.set_scalar("strvalue");

    map.insert(key, value, pMemory);

    node* result = map.get(std::string("strkey"), pMemory);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ("strvalue", result->scalar());
}

// Test get returns null for missing key
TEST_F(NodeTest_248, GetReturnsNullForMissingKey_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    node* result = map.get(std::string("nonexistent"), pMemory);
    EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_248, RemoveFromMap_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    node& key = pMemory->create_node();
    key.set_type(NodeType::Scalar);
    key.set_scalar("removekey");

    node& value = pMemory->create_node();
    value.set_type(NodeType::Scalar);
    value.set_scalar("removevalue");

    map.insert(key, value, pMemory);
    EXPECT_EQ(1u, map.size());

    bool removed = map.remove(key, pMemory);
    EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeTest_248, RemoveNonExistentKey_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    bool removed = map.remove(std::string("nonexistent"), pMemory);
    EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_248, SetDataCopiesFromOther_248) {
    node& source = pMemory->create_node();
    source.set_type(NodeType::Scalar);
    source.set_scalar("source_data");
    source.set_tag("!src");

    node& target = pMemory->create_node();
    target.set_data(source);

    EXPECT_EQ(NodeType::Scalar, target.type());
    EXPECT_EQ("source_data", target.scalar());
    EXPECT_EQ("!src", target.tag());
}

// Test set_ref makes nodes point to same ref
TEST_F(NodeTest_248, SetRefSharesRef_248) {
    node& n1 = pMemory->create_node();
    n1.set_type(NodeType::Scalar);
    n1.set_scalar("shared");

    node& n2 = pMemory->create_node();
    n2.set_ref(n1);

    EXPECT_EQ("shared", n2.scalar());
    EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test equals with matching scalar
TEST_F(NodeTest_248, EqualsMatchingScalar_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    n.set_scalar("test");

    EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_248, EqualsNonMatchingScalar_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    n.set_scalar("test");

    EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_248, EqualsConstChar_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    n.set_scalar("hello");

    EXPECT_TRUE(n.equals("hello", pMemory));
    EXPECT_FALSE(n.equals("world", pMemory));
}

// Test set_mark with default mark (null mark)
TEST_F(NodeTest_248, SetMarkDefaultMark_248) {
    node& n = pMemory->create_node();
    Mark m;
    n.set_mark(m);
    const Mark& retrieved = n.mark();
    EXPECT_EQ(0, retrieved.pos);
    EXPECT_EQ(0, retrieved.line);
    EXPECT_EQ(0, retrieved.column);
}

// Test overwriting scalar
TEST_F(NodeTest_248, OverwriteScalar_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    n.set_scalar("first");
    EXPECT_EQ("first", n.scalar());

    n.set_scalar("second");
    EXPECT_EQ("second", n.scalar());
}

// Test overwriting tag
TEST_F(NodeTest_248, OverwriteTag_248) {
    node& n = pMemory->create_node();
    n.set_tag("!tag1");
    EXPECT_EQ("!tag1", n.tag());

    n.set_tag("!tag2");
    EXPECT_EQ("!tag2", n.tag());
}

// Test changing type
TEST_F(NodeTest_248, ChangeType_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    EXPECT_EQ(NodeType::Scalar, n.type());

    n.set_type(NodeType::Sequence);
    EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test force_insert into map
TEST_F(NodeTest_248, ForceInsertIntoMap_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    map.force_insert(std::string("fkey"), std::string("fvalue"), pMemory);
    EXPECT_EQ(1u, map.size());
}

// Test size of empty map
TEST_F(NodeTest_248, SizeEmptyMap_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);
    EXPECT_EQ(0u, map.size());
}

// Test multiple inserts into map
TEST_F(NodeTest_248, MultipleInsertsIntoMap_248) {
    node& map = pMemory->create_node();
    map.set_type(NodeType::Map);

    for (int i = 0; i < 3; i++) {
        node& key = pMemory->create_node();
        key.set_type(NodeType::Scalar);
        key.set_scalar("key" + std::to_string(i));

        node& value = pMemory->create_node();
        value.set_type(NodeType::Scalar);
        value.set_scalar("val" + std::to_string(i));

        map.insert(key, value, pMemory);
    }
    EXPECT_EQ(3u, map.size());
}

// Test set_type to Null
TEST_F(NodeTest_248, SetTypeNull_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Null);
    EXPECT_EQ(NodeType::Null, n.type());
}

// Test is_defined after setting type
TEST_F(NodeTest_248, IsDefinedAfterSetType_248) {
    node& n = pMemory->create_node();
    n.set_type(NodeType::Scalar);
    EXPECT_TRUE(n.is_defined());
}

// Test add_dependency does not change node state
TEST_F(NodeTest_248, AddDependencyDoesNotChangeState_248) {
    node& n1 = pMemory->create_node();
    n1.set_type(NodeType::Scalar);
    n1.set_scalar("independent");

    node& n2 = pMemory->create_node();
    n1.add_dependency(n2);

    // The node's observable state should remain the same
    EXPECT_EQ(NodeType::Scalar, n1.type());
    EXPECT_EQ("independent", n1.scalar());
}

}  // namespace detail
}  // namespace YAML
