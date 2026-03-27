#include <gtest/gtest.h>

#include <Catch2/internal/catch_uniform_integer_distribution.hpp>



using namespace Catch;



// Define a mock generator for testing purposes

class MockGenerator {

public:

    MOCK_METHOD0(operator(), std::uint32_t());

};



TEST_F(UniformIntegerDistributionTest_1057, ConstructorValidRange_1057) {

    uniform_integer_distribution<int> dist(1, 10);

    EXPECT_EQ(dist.a(), 1);

    EXPECT_EQ(dist.b(), 10);

}



TEST_F(UniformIntegerDistributionTest_1057, ConstructorSingleValueRange_1057) {

    uniform_integer_distribution<int> dist(5, 5);

    EXPECT_EQ(dist.a(), 5);

    EXPECT_EQ(dist.b(), 5);

}



TEST_F(UniformIntegerDistributionTest_1057, OperatorCallWithinRange_1057) {

    MockGenerator mock_gen;

    uniform_integer_distribution<int> dist(1, 10);



    EXPECT_CALL(mock_gen, operator()).WillOnce(testing::Return(5));



    int result = dist(mock_gen);

    EXPECT_GE(result, 1);

    EXPECT_LE(result, 10);

}



TEST_F(UniformIntegerDistributionTest_1057, OperatorCallBoundaryValues_1057) {

    MockGenerator mock_gen;

    uniform_integer_distribution<int> dist(1, 1);



    EXPECT_CALL(mock_gen, operator()).WillOnce(testing::Return(0));



    int result = dist(mock_gen);

    EXPECT_EQ(result, 1);

}



TEST_F(UniformIntegerDistributionTest_1057, ConstructorInvalidRange_1057) {

    try {

        uniform_integer_distribution<int> dist(10, 1);

        FAIL() << "Expected assertion failure";

    } catch (const std::exception& e) {

        SUCCEED();

    }

}



TEST_F(UniformIntegerDistributionTest_1057, OperatorCallLargeRange_1057) {

    MockGenerator mock_gen;

    uniform_integer_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());



    EXPECT_CALL(mock_gen, operator()).WillOnce(testing::Return(42));



    int result = dist(mock_gen);

    EXPECT_GE(result, std::numeric_limits<int>::min());

    EXPECT_LE(result, std::numeric_limits<int>::max());

}
