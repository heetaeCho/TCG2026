#include <gtest/gtest.h>

#include <algorithm>

#include "FoFiTrueType.cc"  // Adjust the include path as necessary



// Define a simple fixture if needed

class cmpTrueTypeTableTagFunctorTest_48 : public ::testing::Test {

protected:

    TrueTypeTable table1;

    TrueTypeTable table2;



    void SetUp() override {

        table1.tag = 0x68656C6C; // 'hell'

        table2.tag = 0x776F726C; // 'worl'

    }

};



// Test normal operation: table1 < table2

TEST_F(cmpTrueTypeTableTagFunctorTest_48, CompareDifferentTagsNormalOperation_48) {

    cmpTrueTypeTableTagFunctor comparator;

    EXPECT_TRUE(comparator(table1, table2));

}



// Test boundary condition: same tags

TEST_F(cmpTrueTypeTableTagFunctorTest_48, CompareSameTagsBoundaryCondition_48) {

    cmpTrueTypeTableTagFunctor comparator;

    table2.tag = table1.tag;

    EXPECT_FALSE(comparator(table1, table2));

}



// Test boundary condition: table1 > table2

TEST_F(cmpTrueTypeTableTagFunctorTest_48, CompareReverseOrderBoundaryCondition_48) {

    cmpTrueTypeTableTagFunctor comparator;

    std::swap(table1.tag, table2.tag);

    EXPECT_FALSE(comparator(table1, table2));

}

```


