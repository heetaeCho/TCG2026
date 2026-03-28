#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node_iterator.h>



using namespace YAML::detail;



// Mocking proxy class for testing purposes

class MockProxy {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



// Test fixture for node_iterator_base tests

class NodeIteratorBaseTest_188 : public ::testing::Test {

protected:

    using value_type = int; // Assuming a simple type for value_type

    using SeqIter = std::vector<value_type>::iterator;

    using MapIter = std::map<std::string, value_type>::iterator;



    node_iterator_base<int> defaultIterator_;

    node_iterator_base<int> seqIterator_;

    node_iterator_base<int> mapIterator_;



    NodeIteratorBaseTest_188()

        : defaultIterator_(),

          seqIterator_(SeqIter()),

          mapIterator_(MapIter(), MapIter()) {}

};



// Test normal operation of operator==

TEST_F(NodeIteratorBaseTest_188, OperatorEqual_NormalOperation_188) {

    node_iterator_base<int> iterator1(SeqIter());

    node_iterator_base<int> iterator2(SeqIter());



    EXPECT_TRUE(iterator1 == iterator2);

}



// Test normal operation of operator!=

TEST_F(NodeIteratorBaseTest_188, OperatorNotEqual_NormalOperation_188) {

    node_iterator_base<int> iterator1(SeqIter());

    SeqIter seqIt;

    node_iterator_base<int> iterator2(++seqIt);



    EXPECT_TRUE(iterator1 != iterator2);

}



// Test boundary condition of operator++ (prefix)

TEST_F(NodeIteratorBaseTest_188, OperatorIncrementPrefix_BoundaryCondition_188) {

    std::vector<value_type> seq = {1};

    SeqIter seqIt = seq.begin();

    node_iterator_base<int> iterator(seqIt);



    ++iterator;

    EXPECT_EQ(iterator.operator*(), value_type());

}



// Test boundary condition of operator++ (postfix)

TEST_F(NodeIteratorBaseTest_188, OperatorIncrementPostfix_BoundaryCondition_188) {

    std::vector<value_type> seq = {1};

    SeqIter seqIt = seq.begin();

    node_iterator_base<int> iterator(seqIt);



    auto oldIterator = iterator++;

    EXPECT_EQ(oldIterator.operator*(), 1);

    EXPECT_EQ(iterator.operator*(), value_type());

}



// Test normal operation of operator*

TEST_F(NodeIteratorBaseTest_188, OperatorDereference_NormalOperation_188) {

    std::vector<value_type> seq = {42};

    SeqIter seqIt = seq.begin();

    node_iterator_base<int> iterator(seqIt);



    EXPECT_EQ(iterator.operator*(), 42);

}



// Test normal operation of operator->

TEST_F(NodeIteratorBaseTest_188, OperatorArrow_NormalOperation_188) {

    std::vector<value_type> seq = {42};

    SeqIter seqIt = seq.begin();

    node_iterator_base<int> iterator(seqIt);



    MockProxy mockProxy;

    EXPECT_CALL(mockProxy, someMethod());



    // Since we can't directly test the return value of operator-> due to its proxy nature,

    // we need to use a mock object and call a method on it.

    // Here we assume that the proxy has a method `someMethod` for demonstration.

    auto proxy = iterator.operator->();

    static_cast<MockProxy&>(proxy).someMethod();

}
