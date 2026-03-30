#include <gtest/gtest.h>

#include "safe_op.hpp"



class SafeOpTest_67 : public ::testing::Test {

protected:

    // Additional setup can be done here if needed

};



TEST_F(SafeOpTest_67, AbsPositiveInt_67) {

    int num = 42;

    EXPECT_EQ(Safe::abs(num), 42);

}



TEST_F(SafeOpTest_67, AbsNegativeInt_67) {

    int num = -42;

    EXPECT_EQ(Safe::abs(num), 42);

}



TEST_F(SafeOpTest_67, AbsZeroInt_67) {

    int num = 0;

    EXPECT_EQ(Safe::abs(num), 0);

}



TEST_F(SafeOpTest_67, AbsMinInt_67) {

    int num = std::numeric_limits<int>::min();

    EXPECT_EQ(Safe::abs(num), std::numeric_limits<int>::max());

}



TEST_F(SafeOpTest_67, AbsMaxInt_67) {

    int num = std::numeric_limits<int>::max();

    EXPECT_EQ(Safe::abs(num), std::numeric_limits<int>::max());

}



TEST_F(SafeOpTest_67, AbsPositiveUnsignedInt_67) {

    unsigned int num = 42;

    EXPECT_EQ(Safe::abs(num), 42);

}



TEST_F(SafeOpTest_67, AbsZeroUnsignedInt_67) {

    unsigned int num = 0;

    EXPECT_EQ(Safe::abs(num), 0);

}



TEST_F(SafeOpTest_67, AbsMaxUnsignedInt_67) {

    unsigned int num = std::numeric_limits<unsigned int>::max();

    EXPECT_EQ(Safe::abs(num), std::numeric_limits<unsigned int>::max());

}
