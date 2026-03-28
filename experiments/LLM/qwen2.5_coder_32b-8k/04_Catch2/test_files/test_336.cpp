#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_uniform_integer_distribution.hpp"



// Mock Generator for testing

class MockGenerator {

public:

    using result_type = Catch::uniform_integer_distribution<int>::UnsignedIntegerType;

    MOCK_METHOD(result_type, operator(), (), (const));

};



TEST_F(UniformIntDistTest_336, NormalOperation_336) {

    MockGenerator mockGen;

    EXPECT_CALL(mockGen, operator()).WillOnce(::testing::Return(1));



    Catch::uniform_integer_distribution<int> dist(0, 10);

    auto result = dist(mockGen);



    EXPECT_GE(result, 0);

    EXPECT_LE(result, 10);

}



TEST_F(UniformIntDistTest_336, BoundaryConditions_MinValue_336) {

    MockGenerator mockGen;

    EXPECT_CALL(mockGen, operator()).WillOnce(::testing::Return(0));



    Catch::uniform_integer_distribution<int> dist(5, 15);

    auto result = dist(mockGen);



    EXPECT_EQ(result, 5);

}



TEST_F(UniformIntDistTest_336, BoundaryConditions_MaxValue_336) {

    MockGenerator mockGen;

    EXPECT_CALL(mockGen, operator()).WillOnce(::testing::Return(~0));



    Catch::uniform_integer_distribution<int> dist(5, 15);

    auto result = dist(mockGen);



    EXPECT_EQ(result, 15);

}



TEST_F(UniformIntDistTest_336, RejectionThresholdHandling_336) {

    MockGenerator mockGen;

    EXPECT_CALL(mockGen, operator())

        .WillOnce(::testing::Return(Catch::uniform_integer_distribution<int>::UnsignedIntegerType{0}))

        .WillOnce(::testing::Return(Catch::uniform_integer_distribution<int>::UnsignedIntegerType{1}));



    Catch::uniform_integer_distribution<int> dist(5, 15);

    auto result = dist(mockGen);



    EXPECT_GE(result, 5);

    EXPECT_LE(result, 15);

}



TEST_F(UniformIntDistTest_336, AEqualsB_ReturnsA_336) {

    MockGenerator mockGen;



    Catch::uniform_integer_distribution<int> dist(7, 7);

    auto result = dist(mockGen);



    EXPECT_EQ(result, 7);

}



TEST_F(UniformIntDistTest_336, LargeRange_336) {

    MockGenerator mockGen;

    EXPECT_CALL(mockGen, operator()).WillOnce(::testing::Return(1));



    Catch::uniform_integer_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    auto result = dist(mockGen);



    EXPECT_GE(result, std::numeric_limits<int>::min());

    EXPECT_LE(result, std::numeric_limits<int>::max());

}



TEST_F(UniformIntDistTest_336, NegativeRange_336) {

    MockGenerator mockGen;

    EXPECT_CALL(mockGen, operator()).WillOnce(::testing::Return(1));



    Catch::uniform_integer_distribution<int> dist(-10, -5);

    auto result = dist(mockGen);



    EXPECT_GE(result, -10);

    EXPECT_LE(result, -5);

}
