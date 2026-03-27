#include <gtest/gtest.h>

#include "Decrypt.hh"  // Assuming Mul03Table is declared in this header



class Mul03TableTest : public ::testing::Test {

protected:

    Mul03Table table;

};



TEST_F(Mul03TableTest_2780, NormalOperation_2780) {

    EXPECT_EQ(table(0), 0);

    EXPECT_EQ(table(1), 3);

    EXPECT_EQ(table(2), 6);

    EXPECT_EQ(table(4), 12);

}



TEST_F(Mul03TableTest_2780, BoundaryConditions_2780) {

    EXPECT_EQ(table(0), 0);       // Minimum value

    EXPECT_EQ(table(255), 97);    // Maximum value

}



// Since the table is computed at compile-time and there are no exceptional cases or error handling,

// we do not need to test for exceptional cases.

```


