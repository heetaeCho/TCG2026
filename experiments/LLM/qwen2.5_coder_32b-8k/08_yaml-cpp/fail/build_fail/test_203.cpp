#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/iterator.h"

#include "yaml-cpp/node/detail/node_iterator.h"



using namespace YAML::detail;



class IteratorBaseTest_203 : public ::testing::Test {

protected:

    shared_memory_holder pMemory;

    base_type m_iterator;

};



TEST_F(IteratorBaseTest_203, DereferenceWithValidNodePtr_203) {

    node_iterator_value<Node> value(Node(), pMemory);

    iterator_base<node_iterator_value<Node>> iter(base_type(&value), pMemory);



    auto result = *iter;



    EXPECT_TRUE(result.first.pNode != nullptr);

}



TEST_F(IteratorBaseTest_203, DereferenceWithValidKeyValuePtrs_203) {

    Node keyNode;

    Node valueNode;

    node_iterator_value<Node> value(keyNode, valueNode);

    iterator_base<node_iterator_value<Node>> iter(base_type(&value), pMemory);



    auto result = *iter;



    EXPECT_TRUE(result.first.pNode != nullptr);

    EXPECT_TRUE(result.second.pNode != nullptr);

}



TEST_F(IteratorBaseTest_203, DereferenceWithNullPtrs_203) {

    node_iterator_value<Node> value;

    iterator_base<node_iterator_value<Node>> iter(base_type(&value), pMemory);



    auto result = *iter;



    EXPECT_TRUE(result.first.pNode == nullptr);

}



TEST_F(IteratorBaseTest_203, DereferenceWithOnlyKeyPtr_203) {

    Node keyNode;

    node_iterator_value<Node> value(keyNode, Node());

    iterator_base<node_iterator_value<Node>> iter(base_type(&value), pMemory);



    auto result = *iter;



    EXPECT_TRUE(result.first.pNode != nullptr);

    EXPECT_TRUE(result.second.pNode == nullptr);

}



TEST_F(IteratorBaseTest_203, DereferenceWithOnlyValuePtr_203) {

    Node valueNode;

    node_iterator_value<Node> value(Node(), valueNode);

    iterator_base<node_iterator_value<Node>> iter(base_type(&value), pMemory);



    auto result = *iter;



    EXPECT_TRUE(result.first.pNode == nullptr);

    EXPECT_TRUE(result.second.pNode != nullptr);

}
