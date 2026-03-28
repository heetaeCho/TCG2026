#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node_iterator.h>



using namespace YAML::detail;



struct MockValue {

    int data;

};



TEST_F(NodeIteratorValueTest_179, DereferenceOperator_ReturnsReferencedValue_179) {

    MockValue value{42};

    node_iterator_value<MockValue> it(value);

    

    EXPECT_EQ((*it).data, 42);

}



TEST_F(NodeIteratorValueTest_179, ArrowOperator_ReturnsPointerToReferencedValue_179) {

    MockValue value{42};

    node_iterator_value<MockValue> it(value);

    

    EXPECT_EQ(it->data, 42);

}



TEST_F(NodeIteratorValueTest_179, ConstructorWithSingleValue_SetsPNodeCorrectly_179) {

    MockValue value{42};

    node_iterator_value<MockValue> it(value);

    

    EXPECT_EQ(it.pNode, &value);

}



TEST_F(NodeIteratorValueTest_179, ConstructorWithKeyValue_SetsPNodeToNullptr_179) {

    MockValue key{42};

    MockValue value{84};

    node_iterator_value<MockValue> it(key, value);

    

    EXPECT_EQ(it.pNode, nullptr);

}



TEST_F(NodeIteratorValueTest_179, DefaultConstructor_SetsPNodeToNullptr_179) {

    node_iterator_value<MockValue> it;

    

    EXPECT_EQ(it.pNode, nullptr);

}
