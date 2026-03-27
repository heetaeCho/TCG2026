#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_235 : public ::testing::Test {

protected:

    Node node1;

    Node node2;

};



TEST_F(NodeTest_235, IsDefinedReturnsFalseInitially_235) {

    EXPECT_FALSE(node1.is_defined());

}



TEST_F(NodeTest_235, MarkDefinedSetsIsDefinedTrue_235) {

    node1.mark_defined();

    EXPECT_TRUE(node1.is_defined());

}



TEST_F(NodeTest_235, IsFunctionComparesNodesBasedOnRef_235) {

    Node anotherNode;

    EXPECT_FALSE(node1.is(anotherNode));

}



TEST_F(NodeTest_235, SetAndGetTypeWorksProperly_235) {

    node1.set_type(NodeType::Map);

    EXPECT_EQ(node1.type(), NodeType::Map);

}



TEST_F(NodeTest_235, SetAndGetScalarWorksProperly_235) {

    node1.set_scalar("test");

    EXPECT_EQ(node1.scalar(), "test");

}



TEST_F(NodeTest_235, SetAndGetTagWorksProperly_235) {

    node1.set_tag("!tag");

    EXPECT_EQ(node1.tag(), "!tag");

}



TEST_F(NodeTest_235, SetAndGetStyleWorksProperly_235) {

    node1.set_style(EmitterStyle::Block);

    EXPECT_EQ(node1.style(), EmitterStyle::Block);

}



TEST_F(NodeTest_235, SizeReturnsZeroInitially_235) {

    EXPECT_EQ(node1.size(), 0);

}



TEST_F(NodeTest_235, PushBackIncreasesSize_235) {

    Node childNode;

    shared_memory_holder pMemory; // Placeholder for actual memory holder

    node1.push_back(childNode, pMemory);

    EXPECT_EQ(node1.size(), 1);

}



TEST_F(NodeTest_235, InsertIncreasesSize_235) {

    Node keyNode, valueNode;

    shared_memory_holder pMemory; // Placeholder for actual memory holder

    node1.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(node1.size(), 1);

}



TEST_F(NodeTest_235, GetReturnsNullptrIfKeyNotFound_235) {

    Node keyNode;

    shared_memory_holder pMemory; // Placeholder for actual memory holder

    EXPECT_EQ(node1.get(keyNode, pMemory), nullptr);

}



TEST_F(NodeTest_235, RemoveByKeyDoesNothingIfKeyNotFound_235) {

    Node keyNode;

    shared_memory_holder pMemory; // Placeholder for actual memory holder

    EXPECT_FALSE(node1.remove(keyNode, pMemory));

}



TEST_F(NodeTest_235, ForceInsertAddsNewEntry_235) {

    Node keyNode, valueNode;

    shared_memory_holder pMemory; // Placeholder for actual memory holder

    node1.force_insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(node1.size(), 1);

}



TEST_F(NodeTest_235, LessComparatorComparesNodesByIndex_235) {

    Node::less comparator;

    node1.m_index = 1;

    node2.m_index = 2;

    EXPECT_TRUE(comparator(&node1, &node2));

    EXPECT_FALSE(comparator(&node2, &node1));

}
