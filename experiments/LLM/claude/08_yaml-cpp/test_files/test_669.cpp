#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/impl.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

class NodeDataGetTest_669 : public ::testing::Test {
protected:
    void SetUp() override {
        mem_holder = std::make_shared<memory>();
    }

    shared_memory_holder mem_holder;

    node& create_node() {
        return mem_holder->create_node();
    }

    node& create_scalar_node(const std::string& value) {
        node& n = create_node();
        n.set_scalar(value);
        return n;
    }
};

// Test: get on Null type returns nullptr
TEST_F(NodeDataGetTest_669, GetOnNullTypeReturnsNullptr_669) {
    node_data data;
    // Default type is Null
    node* result = data.get(std::string("key"), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: get on Undefined type returns nullptr
TEST_F(NodeDataGetTest_669, GetOnUndefinedTypeReturnsNullptr_669) {
    node_data data;
    // set_type to Undefined
    data.set_type(NodeType::Undefined);
    node* result = data.get(std::string("key"), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: get on Scalar type throws BadSubscript
TEST_F(NodeDataGetTest_669, GetOnScalarTypeThrowsBadSubscript_669) {
    node_data data;
    data.set_type(NodeType::Scalar);
    data.set_scalar("hello");
    EXPECT_THROW(data.get(std::string("key"), mem_holder), BadSubscript);
}

// Test: get on Sequence with valid integer index
TEST_F(NodeDataGetTest_669, GetOnSequenceWithValidIndex_669) {
    node_data data;
    data.set_type(NodeType::Sequence);

    node& child = create_node();
    child.set_scalar("value0");
    data.push_back(child, mem_holder);

    // Access index 0 using std::size_t key
    node* result = data.get(static_cast<std::size_t>(0), mem_holder);
    EXPECT_NE(result, nullptr);
}

// Test: get on Sequence with out-of-range index returns nullptr
TEST_F(NodeDataGetTest_669, GetOnSequenceWithOutOfRangeIndexReturnsNullptr_669) {
    node_data data;
    data.set_type(NodeType::Sequence);

    node& child = create_node();
    child.set_scalar("value0");
    data.push_back(child, mem_holder);

    node* result = data.get(static_cast<std::size_t>(5), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: get on Sequence with string key returns nullptr (string not a valid index)
TEST_F(NodeDataGetTest_669, GetOnSequenceWithStringKeyReturnsNullptr_669) {
    node_data data;
    data.set_type(NodeType::Sequence);

    node& child = create_node();
    child.set_scalar("value0");
    data.push_back(child, mem_holder);

    node* result = data.get(std::string("notanindex"), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: get on Map with existing key returns correct node
TEST_F(NodeDataGetTest_669, GetOnMapWithExistingKeyReturnsNode_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node& key_node = create_node();
    key_node.set_scalar("mykey");
    node& val_node = create_node();
    val_node.set_scalar("myvalue");
    data.insert(key_node, val_node, mem_holder);

    node* result = data.get(std::string("mykey"), mem_holder);
    EXPECT_NE(result, nullptr);
}

// Test: get on Map with non-existing key returns nullptr
TEST_F(NodeDataGetTest_669, GetOnMapWithNonExistingKeyReturnsNullptr_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node& key_node = create_node();
    key_node.set_scalar("mykey");
    node& val_node = create_node();
    val_node.set_scalar("myvalue");
    data.insert(key_node, val_node, mem_holder);

    node* result = data.get(std::string("otherkey"), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: get on empty Map returns nullptr
TEST_F(NodeDataGetTest_669, GetOnEmptyMapReturnsNullptr_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node* result = data.get(std::string("anykey"), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: get on Map with multiple keys finds correct one
TEST_F(NodeDataGetTest_669, GetOnMapWithMultipleKeysFindsCorrectOne_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node& key1 = create_node();
    key1.set_scalar("alpha");
    node& val1 = create_node();
    val1.set_scalar("val_alpha");
    data.insert(key1, val1, mem_holder);

    node& key2 = create_node();
    key2.set_scalar("beta");
    node& val2 = create_node();
    val2.set_scalar("val_beta");
    data.insert(key2, val2, mem_holder);

    node& key3 = create_node();
    key3.set_scalar("gamma");
    node& val3 = create_node();
    val3.set_scalar("val_gamma");
    data.insert(key3, val3, mem_holder);

    node* result = data.get(std::string("beta"), mem_holder);
    EXPECT_NE(result, nullptr);

    node* result2 = data.get(std::string("gamma"), mem_holder);
    EXPECT_NE(result2, nullptr);

    node* result3 = data.get(std::string("delta"), mem_holder);
    EXPECT_EQ(result3, nullptr);
}

// Test: get on Sequence with index 0 on empty sequence returns nullptr
TEST_F(NodeDataGetTest_669, GetOnEmptySequenceReturnsNullptr_669) {
    node_data data;
    data.set_type(NodeType::Sequence);

    node* result = data.get(static_cast<std::size_t>(0), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: Scalar type throws with integer key as well
TEST_F(NodeDataGetTest_669, GetOnScalarTypeThrowsWithIntKey_669) {
    node_data data;
    data.set_type(NodeType::Scalar);
    data.set_scalar("hello");
    EXPECT_THROW(data.get(static_cast<std::size_t>(0), mem_holder), BadSubscript);
}

// Test: remove on Map with existing key
TEST_F(NodeDataGetTest_669, RemoveOnMapWithExistingKey_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node& key_node = create_node();
    key_node.set_scalar("removeMe");
    node& val_node = create_node();
    val_node.set_scalar("value");
    data.insert(key_node, val_node, mem_holder);

    bool removed = data.remove(std::string("removeMe"), mem_holder);
    EXPECT_TRUE(removed);

    // After removal, get should return nullptr
    node* result = data.get(std::string("removeMe"), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: remove on Map with non-existing key returns false
TEST_F(NodeDataGetTest_669, RemoveOnMapWithNonExistingKeyReturnsFalse_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node& key_node = create_node();
    key_node.set_scalar("existingKey");
    node& val_node = create_node();
    val_node.set_scalar("value");
    data.insert(key_node, val_node, mem_holder);

    bool removed = data.remove(std::string("nonExisting"), mem_holder);
    EXPECT_FALSE(removed);
}

// Test: size of sequence
TEST_F(NodeDataGetTest_669, SequenceSizeIsCorrect_669) {
    node_data data;
    data.set_type(NodeType::Sequence);

    EXPECT_EQ(data.size(), 0u);

    node& child1 = create_node();
    child1.set_scalar("a");
    data.push_back(child1, mem_holder);
    EXPECT_EQ(data.size(), 1u);

    node& child2 = create_node();
    child2.set_scalar("b");
    data.push_back(child2, mem_holder);
    EXPECT_EQ(data.size(), 2u);
}

// Test: size of map
TEST_F(NodeDataGetTest_669, MapSizeIsCorrect_669) {
    node_data data;
    data.set_type(NodeType::Map);

    EXPECT_EQ(data.size(), 0u);

    node& key1 = create_node();
    key1.set_scalar("k1");
    node& val1 = create_node();
    val1.set_scalar("v1");
    data.insert(key1, val1, mem_holder);
    EXPECT_EQ(data.size(), 1u);
}

// Test: set_type and type accessor
TEST_F(NodeDataGetTest_669, SetTypeAndTypeAccessor_669) {
    node_data data;
    EXPECT_EQ(data.type(), NodeType::Null);

    data.set_type(NodeType::Sequence);
    EXPECT_EQ(data.type(), NodeType::Sequence);

    data.set_type(NodeType::Map);
    EXPECT_EQ(data.type(), NodeType::Map);

    data.set_type(NodeType::Scalar);
    EXPECT_EQ(data.type(), NodeType::Scalar);
}

// Test: set_scalar and scalar accessor
TEST_F(NodeDataGetTest_669, SetScalarAndScalarAccessor_669) {
    node_data data;
    data.set_type(NodeType::Scalar);
    data.set_scalar("test_value");
    EXPECT_EQ(data.scalar(), "test_value");
}

// Test: set_tag and tag accessor
TEST_F(NodeDataGetTest_669, SetTagAndTagAccessor_669) {
    node_data data;
    data.set_tag("!custom");
    EXPECT_EQ(data.tag(), "!custom");
}

// Test: mark_defined and is_defined
TEST_F(NodeDataGetTest_669, MarkDefinedAndIsDefined_669) {
    node_data data;
    EXPECT_FALSE(data.is_defined());
    data.mark_defined();
    EXPECT_TRUE(data.is_defined());
}

// Test: set_null sets type to Null
TEST_F(NodeDataGetTest_669, SetNullSetsTypeToNull_669) {
    node_data data;
    data.set_type(NodeType::Scalar);
    data.set_scalar("something");
    data.set_null();
    EXPECT_EQ(data.type(), NodeType::Null);
}

// Test: empty_scalar returns empty string
TEST_F(NodeDataGetTest_669, EmptyScalarReturnsEmptyString_669) {
    const std::string& empty = node_data::empty_scalar();
    EXPECT_TRUE(empty.empty());
}

// Test: set_style and style accessor
TEST_F(NodeDataGetTest_669, SetStyleAndStyleAccessor_669) {
    node_data data;
    data.set_style(EmitterStyle::Flow);
    EXPECT_EQ(data.style(), EmitterStyle::Flow);

    data.set_style(EmitterStyle::Block);
    EXPECT_EQ(data.style(), EmitterStyle::Block);
}

// Test: force_insert on map
TEST_F(NodeDataGetTest_669, ForceInsertOnMap_669) {
    node_data data;
    data.set_type(NodeType::Map);

    data.force_insert(std::string("fkey"), std::string("fval"), mem_holder);

    node* result = data.get(std::string("fkey"), mem_holder);
    EXPECT_NE(result, nullptr);
}

// Test: get with node& key on Map
TEST_F(NodeDataGetTest_669, GetWithNodeKeyOnMap_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node& key_node = create_node();
    key_node.set_scalar("nodekey");
    node& val_node = create_node();
    val_node.set_scalar("nodeval");
    data.insert(key_node, val_node, mem_holder);

    node* result = data.get(key_node, mem_holder);
    EXPECT_NE(result, nullptr);
}

// Test: remove with node& key on Map
TEST_F(NodeDataGetTest_669, RemoveWithNodeKeyOnMap_669) {
    node_data data;
    data.set_type(NodeType::Map);

    node& key_node = create_node();
    key_node.set_scalar("to_remove");
    node& val_node = create_node();
    val_node.set_scalar("val");
    data.insert(key_node, val_node, mem_holder);

    bool removed = data.remove(key_node, mem_holder);
    EXPECT_TRUE(removed);

    node* result = data.get(key_node, mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: Sequence with multiple elements, accessing each by index
TEST_F(NodeDataGetTest_669, SequenceAccessMultipleElements_669) {
    node_data data;
    data.set_type(NodeType::Sequence);

    for (int i = 0; i < 5; i++) {
        node& child = create_node();
        child.set_scalar(std::to_string(i));
        data.push_back(child, mem_holder);
    }

    for (std::size_t i = 0; i < 5; i++) {
        node* result = data.get(i, mem_holder);
        EXPECT_NE(result, nullptr);
    }

    // Out of range
    node* result = data.get(static_cast<std::size_t>(5), mem_holder);
    EXPECT_EQ(result, nullptr);
}

// Test: begin/end iterators on sequence
TEST_F(NodeDataGetTest_669, BeginEndOnSequence_669) {
    node_data data;
    data.set_type(NodeType::Sequence);

    node& child = create_node();
    child.set_scalar("item");
    data.push_back(child, mem_holder);

    auto it = data.begin();
    auto end = data.end();
    EXPECT_NE(it, end);
}

// Test: begin/end iterators on empty map
TEST_F(NodeDataGetTest_669, BeginEndOnEmptyMap_669) {
    node_data data;
    data.set_type(NodeType::Map);

    auto it = data.begin();
    auto end = data.end();
    EXPECT_EQ(it, end);
}

}  // namespace detail
}  // namespace YAML
