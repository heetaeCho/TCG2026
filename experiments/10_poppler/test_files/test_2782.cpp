#include <gtest/gtest.h>

#include "Decrypt.cc"  // Assuming Mul0bTable is defined in this file



class Mul0bTableTest_2782 : public ::testing::Test {

protected:

    Mul0bTable table;

};



TEST_F(Mul0bTableTest_2782, NormalOperation_2782) {

    EXPECT_EQ(table(0), 0);

    EXPECT_EQ(table(1), 1);

    EXPECT_EQ(table(2), 3);

    EXPECT_EQ(table(3), 6);

}



TEST_F(Mul0bTableTest_2782, BoundaryConditions_2782) {

    EXPECT_EQ(table(0), 0);

    EXPECT_EQ(table(255), table(static_cast<uint8_t>(0xFF)));

}



// Since the operator() is deterministic and based on a lookup table,

// there are no exceptional or error cases to test for this specific function.

```


