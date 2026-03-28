#include <gtest/gtest.h>



namespace re2 {



// Mocking is not required for this function as it does not interact with any external collaborators.



TEST(MaxRuneTest_302, SingleByteUtf8_302) {

    EXPECT_EQ(MaxRune(1), 127); // 7 bits can represent values from 0 to 127

}



TEST(MaxRuneTest_302, TwoByteUtf8_302) {

    EXPECT_EQ(MaxRune(2), 2047); // 11 bits can represent values from 0 to 2047

}



TEST(MaxRuneTest_302, ThreeByteUtf8_302) {

    EXPECT_EQ(MaxRune(3), 65535); // 16 bits can represent values from 0 to 65535

}



TEST(MaxRuneTest_302, FourByteUtf8_302) {

    EXPECT_EQ(MaxRune(4), 1114111); // 21 bits can represent values from 0 to 1114111

}



// Boundary conditions

TEST(MaxRuneTest_302, MinLenBoundary_302) {

    EXPECT_EQ(MaxRune(1), 127);

}



TEST(MaxRuneTest_302, MaxLenBoundary_302) {

    EXPECT_EQ(MaxRune(4), 1114111);

}



// Error cases (if any observable through the interface)

// For this function, there are no error cases as it assumes valid input within the expected range (1 to 4).



} // namespace re2
