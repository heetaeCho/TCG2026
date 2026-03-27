#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node_iterator.h>



using namespace YAML::detail;



// Mock class for testing node_iterator_value

class MockValue {

public:

    MOCK_METHOD0(getData, int());

};



TEST_F(NodeIteratorValueTest_180, DereferenceOperator_ReturnsCorrectReference_180) {

    MockValue mockValue;

    node_iterator_value<MockValue> it(mockValue);



    EXPECT_EQ(&mockValue, &(it.operator*()));

}



TEST_F(NodeIteratorValueTest_180, ArrowOperator_ReturnsCorrectPointer_180) {

    MockValue mockValue;

    node_iterator_value<MockValue> it(mockValue);



    EXPECT_EQ(&mockValue, it.operator->());

}



TEST_F(NodeIteratorValueTest_180, ConstructorWithKeyValue_InitializesCorrectly_180) {

    MockValue keyMock, valueMock;

    node_iterator_value<MockValue> it(keyMock, valueMock);



    EXPECT_EQ(&keyMock, it.kv.first);

    EXPECT_EQ(&valueMock, it.kv.second);

    EXPECT_EQ(nullptr, it.pNode);

}



TEST_F(NodeIteratorValueTest_180, ConstructorWithSingleValue_InitializesCorrectly_180) {

    MockValue mockValue;

    node_iterator_value<MockValue> it(mockValue);



    EXPECT_EQ(&mockValue, it.pNode);

    EXPECT_EQ(nullptr, it.kv.first);

    EXPECT_EQ(nullptr, it.kv.second);

}



TEST_F(NodeIteratorValueTest_180, DefaultConstructor_InitializesCorrectly_180) {

    node_iterator_value<MockValue> it;



    EXPECT_EQ(nullptr, it.pNode);

    EXPECT_EQ(nullptr, it.kv.first);

    EXPECT_EQ(nullptr, it.kv.second);

}
