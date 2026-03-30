#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/iterator.h"



using namespace YAML::detail;



// Test fixture for iterator_base tests

class IteratorBaseTest_201 : public ::testing::Test {

protected:

    using V = int;

    base_type m_iterator;

    shared_memory_holder m_pMemory;

    iterator_base<V> iter1;

    iterator_base<V> iter2;



    IteratorBaseTest_201() : m_iterator(0), m_pMemory(nullptr), iter1(m_iterator, m_pMemory) {

        // Initialize iterators for testing

        iter2 = iterator_base<V>(m_iterator + 1, m_pMemory);

    }

};



// Test if two iterators are equal when they point to the same location

TEST_F(IteratorBaseTest_201, EqualOperatorSameLocation_201) {

    EXPECT_TRUE(iter1 == iter1);

}



// Test if two iterators are not equal when they point to different locations

TEST_F(IteratorBaseTest_201, NotEqualOperatorDifferentLocations_201) {

    EXPECT_FALSE(iter1 == iter2);

}



// Test if the inequality operator returns false for equal iterators

TEST_F(IteratorBaseTest_201, InequalityOperatorSameLocation_201) {

    EXPECT_FALSE(iter1 != iter1);

}



// Test if the inequality operator returns true for different iterators

TEST_F(IteratorBaseDtest_201, InequalityOperatorDifferentLocations_201) {

    EXPECT_TRUE(iter1 != iter2);

}



// Test prefix increment operator

TEST_F(IteratorBaseTest_201, PrefixIncrement_201) {

    iterator_base<V> iter = iter1;

    ++iter;

    EXPECT_EQ(iter.m_iterator, iter1.m_iterator + 1);

}



// Test postfix increment operator

TEST_F(IteratorBaseTest_201, PostfixIncrement_201) {

    iterator_base<V> iter = iter1;

    iterator_base<V> temp = iter++;

    EXPECT_EQ(temp.m_iterator, iter1.m_iterator);

    EXPECT_EQ(iter.m_iterator, iter1.m_iterator + 1);

}



// Test dereference operator

TEST_F(IteratorBaseTest_201, DereferenceOperator_201) {

    // Assuming value_type can be compared with base_type

    EXPECT_EQ(*iter1, m_iterator);

}
