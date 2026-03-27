#include <gtest/gtest.h>

#include "catch_random_integer_helpers.hpp"



namespace Catch { namespace Detail {



class ExtendedMultResultTest : public ::testing::Test {

protected:

    using ResultType = ExtendedMultResult<int>;



    ResultType result1;

    ResultType result2;



    void SetUp() override {

        result1.upper = 42;

        result1.lower = 24;

        result2.upper = 42;

        result2.lower = 24;

    }

};



TEST_F(ExtendedMultResultTest_330, EqualityOperatorReturnsTrueForEqualResults_330) {

    EXPECT_TRUE(result1 == result2);

}



TEST_F(ExtendedMultResultTest_330, EqualityOperatorReturnsFalseForDifferentUpperValues_330) {

    result2.upper = 99;

    EXPECT_FALSE(result1 == result2);

}



TEST_F(ExtendedMultResultTest_330, EqualityOperatorReturnsFalseForDifferentLowerValues_330) {

    result2.lower = 99;

    EXPECT_FALSE(result1 == result2);

}



TEST_F(ExtendedMultResultTest_330, EqualityOperatorReturnsFalseForBothDifferentValues_330) {

    result2.upper = 99;

    result2.lower = 99;

    EXPECT_FALSE(result1 == result2);

}



}} // namespace Catch::Detail
