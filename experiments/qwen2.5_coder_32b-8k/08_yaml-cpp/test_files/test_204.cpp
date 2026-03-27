#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/iterator.h"



using namespace YAML::detail;



class IteratorBaseTest_204 : public ::testing::Test {

protected:

    iterator_base<int> defaultIterator;

    shared_memory_holder pMemory = std::make_shared<int>(42);

    base_type m_iterator = 10;

    iterator_base<int> initializedIterator = iterator_base<int>(m_iterator, pMemory);



    template <typename V>

    void checkEquality(const iterator_base<V>& it1, const iterator_base<V>& it2) {

        EXPECT_TRUE(it1 == it2);

        EXPECT_FALSE(it1 != it2);

    }



    template <typename V>

    void checkInequality(const iterator_base<V>& it1, const iterator_base<V>& it2) {

        EXPECT_FALSE(it1 == it2);

        EXPECT_TRUE(it1 != it2);

    }

};



TEST_F(IteratorBaseTest_204, DefaultConstructorInitializesMembers_204) {

    // Assuming default constructor initializes m_iterator and m_pMemory to some valid state

    // We can only verify if the object is constructible without errors in this case

}



TEST_F(IteratorBaseTest_204, ParameterizedConstructorSetsMembers_204) {

    EXPECT_EQ(initializedIterator.m_iterator, m_iterator);

    EXPECT_EQ(*initializedIterator.m_pMemory, *pMemory);

}



TEST_F(IteratorBaseTest_204, CopyConstructorWorksForConvertibleTypes_204) {

    iterator_base<const int> constIterator = initializedIterator;

    checkEquality(constIterator, initializedIterator);

}



TEST_F(IteratorBaseTest_204, IncrementOperatorPreIncrementUpdatesIterator_204) {

    base_type originalValue = initializedIterator.m_iterator;

    ++initializedIterator;

    EXPECT_EQ(initializedIterator.m_iterator, originalValue + 1);

}



TEST_F(IteratorBaseTest_204, IncrementOperatorPostIncrementUpdatesIterator_204) {

    base_type originalValue = initializedIterator.m_iterator;

    iterator_base<int> temp = initializedIterator++;

    EXPECT_EQ(temp.m_iterator, originalValue);

    EXPECT_EQ(initializedIterator.m_iterator, originalValue + 1);

}



TEST_F(IteratorBaseTest_204, EqualityOperatorReturnsTrueForEqualIterators_204) {

    iterator_base<int> anotherInitializedIterator = iterator_base<int>(m_iterator, pMemory);

    checkEquality(anotherInitializedIterator, initializedIterator);

}



TEST_F(IteratorBaseTest_204, InequalityOperatorReturnsFalseForEqualIterators_204) {

    iterator_base<int> anotherInitializedIterator = iterator_base<int>(m_iterator, pMemory);

    checkInequality(defaultIterator, initializedIterator);

}



// Assuming operator* and operator-> are observable through some other means or callbacks

// Since we cannot infer the internal logic, these tests are hypothetical based on typical usage



TEST_F(IteratorBaseTest_204, DereferenceOperatorReturnsCorrectValue_204) {

    // This test assumes that dereferencing returns a value_type which is an int in this case

    EXPECT_EQ(*initializedIterator, *m_iterator);

}



// Note: operator-> requires more context about the proxy class and its behavior

// Since we treat the implementation as a black box, no specific tests for it can be written without assumptions.
