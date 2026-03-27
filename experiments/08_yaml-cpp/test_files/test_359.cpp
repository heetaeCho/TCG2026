#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



// Mock class for SignedSignificandBits to simulate different scenarios

class MockSignedSignificandBits {

public:

    MOCK_CONST_METHOD0(has_even_significand_bits, bool());

};



// Test Fixture

class NearestToOddTest_359 : public ::testing::Test {

protected:

    nearest_to_odd_t policy;

    MockSignedSignificandBits mock_ssb;

};



// Normal operation: has_even_significand_bits returns false

TEST_F(NearestToOddTest_359, NormalInterval_ReturnsTrueWhenFalse_359) {

    EXPECT_CALL(mock_ssb, has_even_significand_bits()).WillOnce(::testing::Return(false));

    auto result = policy.normal_interval(mock_ssb);

    EXPECT_TRUE(result);

}



// Normal operation: has_even_significand_bits returns true

TEST_F(NearestToOddTest_359, NormalInterval_ReturnsFalseWhenTrue_359) {

    EXPECT_CALL(mock_ssb, has_even_significand_bits()).WillOnce(::testing::Return(true));

    auto result = policy.normal_interval(mock_ssb);

    EXPECT_FALSE(result);

}



// Boundary condition: Edge case where has_even_significand_bits returns false

TEST_F(NearestToOddTest_359, NormalInterval_EdgeCaseFalse_359) {

    EXPECT_CALL(mock_ssb, has_even_significand_bits()).WillOnce(::testing::Return(false));

    auto result = policy.normal_interval(mock_ssb);

    EXPECT_TRUE(result);

}



// Boundary condition: Edge case where has_even_significand_bits returns true

TEST_F(NearestToOddTest_359, NormalInterval_EdgeCaseTrue_359) {

    EXPECT_CALL(mock_ssb, has_even_significand_bits()).WillOnce(::testing::Return(true));

    auto result = policy.normal_interval(mock_ssb);

    EXPECT_FALSE(result);

}

```


