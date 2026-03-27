#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/iterator.h"



namespace YAML {

namespace detail {



class IteratorBaseTest_200 : public ::testing::Test {

protected:

    iterator_base<int> it;

};



TEST_F(IteratorBaseTest_200, PostIncrementReturnsPreviousState_200) {

    // Arrange

    iterator_base<int> initial_it = it;



    // Act

    iterator_base<int> result = it++;



    // Assert

    EXPECT_EQ(result, initial_it);

}



// Assuming the operator++(int) modifies the internal state of 'it'

TEST_F(IteratorBaseTest_200, PostIncrementAdvancesIterator_200) {

    // Arrange

    iterator_base<int> initial_it = it;

    

    // Act

    it++;



    // Assert

    EXPECT_NE(it, initial_it);

}



// Boundary condition: Check behavior with default constructed iterator

TEST_F(IteratorBaseTest_200, PostIncrementOnDefaultConstructedIterator_200) {

    // Arrange

    iterator_base<int> default_it;

    iterator_base<int> initial_default_it = default_it;



    // Act

    default_it++;



    // Assert

    EXPECT_NE(default_it, initial_default_it);

}



}  // namespace detail

}  // namespace YAML
