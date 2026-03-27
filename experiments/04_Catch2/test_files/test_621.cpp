#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class ColumnsIteratorTest_621 : public ::testing::Test {

protected:

    Columns columns;

    Columns::iterator it;

};



TEST_F(ColumnsIteratorTest_621, PostIncrementReturnsPreviousState_621) {

    Columns::iterator prev_it = it++;

    EXPECT_EQ(prev_it, it++);

}



TEST_F(ColumnsIteratorTest_621, PostIncrementAdvancesIterator_621) {

    Columns::iterator prev_it = it;

    Columns::iterator new_it = it++;

    EXPECT_NE(prev_it, new_it);

}

```


