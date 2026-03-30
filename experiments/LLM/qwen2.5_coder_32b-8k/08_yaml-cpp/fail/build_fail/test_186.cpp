#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"



using namespace YAML::detail;



class NodeIteratorBaseTest_186 : public ::testing::Test {

protected:

    node_iterator_base<int> iterator;

};



TEST_F(NodeIteratorBaseTest_186, PostIncrementReturnsPreviousValue_186) {

    node_iterator_base<int> result = iterator++;

    EXPECT_EQ(&result, &iterator - 1);

}



// Since the class is very minimal and there are no observable side effects or error conditions

// through the provided interface, we limit ourselves to testing the defined behavior.



TEST_F(NodeIteratorBaseTest_186, PostIncrementDoesNotModifyCurrentState_186) {

    node_iterator_base<int> pre_increment = iterator;

    node_iterator_base<int> post_increment = iterator++;

    EXPECT_EQ(pre_increment, post_increment);

}



// Boundary conditions and exceptional cases are not applicable given the current interface.

```


