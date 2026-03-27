#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/goo/grandom.cc"



using namespace testing;



TEST(grandom_double_Test_27, ReturnsValueInRange_27) {

    double result = grandom_double();

    EXPECT_GE(result, 0.0);

    EXPECT_LE(result, 1.0);

}



TEST(grandom_double_Test_27, MultipleCallsProduceDifferentValues_27) {

    double first_call = grandom_double();

    double second_call = grandom_double();

    // While it's possible that two consecutive calls could return the same value,

    // this test is a basic check for variability. In practice, it should rarely fail.

    EXPECT_NE(first_call, second_call);

}



TEST(grandom_double_Test_27, ConsistentPrecision_27) {

    double result = grandom_double();

    // std::generate_canonical returns a value in the range [0, 1) with the full precision of double

    int digits = std::numeric_limits<double>::digits;

    EXPECT_EQ(std::frexp(result, &digits), result);

}



// Since the function does not take any parameters and its behavior is probabilistic,

// there are no exceptional or error cases to test based on the provided interface.
