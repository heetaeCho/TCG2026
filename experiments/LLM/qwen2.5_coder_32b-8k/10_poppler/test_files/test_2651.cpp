#include <gtest/gtest.h>



// Include the header file containing the function to be tested.

#include "TestProjects/poppler/utils/numberofcharacters.h"



class NumberOfCharactersTest_2651 : public ::testing::Test {

protected:

    // You can set up any common objects or state here if needed.

};



TEST_F(NumberOfCharactersTest_2651, SingleDigitNumber_2651) {

    EXPECT_EQ(numberOfCharacters(0), 1);

    EXPECT_EQ(numberOfCharacters(9), 1);

}



TEST_F(NumberOfCharactersTest_2651, DoubleDigitNumber_2651) {

    EXPECT_EQ(numberOfCharacters(10), 2);

    EXPECT_EQ(numberOfCharacters(99), 2);

}



TEST_F(NumberOfCharactersTest_2651, ThreeDigitNumber_2651) {

    EXPECT_EQ(numberOfCharacters(100), 3);

    EXPECT_EQ(numberOfCharacters(999), 3);

}



TEST_F(NumberOfCharactersTest_2651, LargeNumber_2651) {

    EXPECT_EQ(numberOfCharacters(1000000000), 10);

    EXPECT_EQ(numberOfCharacters(4294967295), 10); // Max unsigned int value

}



TEST_F(NumberOfCharactersTest_2651, BoundaryConditionZero_2651) {

    EXPECT_EQ(numberOfCharacters(0), 1);

}
