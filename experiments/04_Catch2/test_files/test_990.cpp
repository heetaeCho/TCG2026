#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"



using namespace Catch::Benchmark::Detail;



// Mocking the sample and related functions for testing purposes

class SampleMock {

public:

    MOCK_METHOD(double*, data, (), (const));

    MOCK_METHOD(size_t, size, (), (const));

};



double mock_estimator(double const* first, double const* last) {

    // Simple mock implementation of estimator

    return (*first + *last) / 2.0;

}



TEST(BootstrapTest_990, SingleSample_ReturnsPointEstimate_990) {

    double sample_data = 42.0;

    SampleMock mock_sample;

    EXPECT_CALL(mock_sample, data()).WillRepeatedly(testing::Return(&sample_data));

    EXPECT_CALL(mock_sample, size()).WillRepeatedly(testing::Return(1));



    auto result = bootstrap(0.95, &sample_data, &sample_data + 1, mock_sample, mock_estimator);

    EXPECT_DOUBLE_EQ(result.point_estimate, sample_data);

    EXPECT_DOUBLE_EQ(result.lower_bound, sample_data);

    EXPECT_DOUBLE_EQ(result.upper_bound, sample_data);

}



TEST(BootstrapTest_990, MultipleSamples_CalculatesCorrectBounds_990) {

    double sample_data[] = {1.0, 2.0, 3.0};

    SampleMock mock_sample;

    EXPECT_CALL(mock_sample, data()).WillRepeatedly(testing::Return(sample_data));

    EXPECT_CALL(mock_sample, size()).WillRepeatedly(testing::Return(3));



    auto result = bootstrap(0.95, sample_data, sample_data + 3, mock_sample, mock_estimator);

    // The actual values depend on the implementation details which we don't know,

    // but we can check if they are within a reasonable range.

    EXPECT_GE(result.lower_bound, 1.0);

    EXPECT_LE(result.upper_bound, 3.0);

}



TEST(BootstrapTest_990, ConfidenceLevelZero_ReturnsPointEstimate_990) {

    double sample_data[] = {1.0, 2.0, 3.0};

    SampleMock mock_sample;

    EXPECT_CALL(mock_sample, data()).WillRepeatedly(testing::Return(sample_data));

    EXPECT_CALL(mock_sample, size()).WillRepeatedly(testing::Return(3));



    auto result = bootstrap(0.0, sample_data, sample_data + 3, mock_sample, mock_estimator);

    EXPECT_DOUBLE_EQ(result.point_estimate, mock_estimator(sample_data, sample_data + 3));

    EXPECT_DOUBLE_EQ(result.lower_bound, mock_estimator(sample_data, sample_data + 3));

    EXPECT_DOUBLE_EQ(result.upper_bound, mock_estimator(sample_data, sample_data + 3));

}



TEST(BootstrapTest_990, ConfidenceLevelOne_ReturnsPointEstimate_990) {

    double sample_data[] = {1.0, 2.0, 3.0};

    SampleMock mock_sample;

    EXPECT_CALL(mock_sample, data()).WillRepeatedly(testing::Return(sample_data));

    EXPECT_CALL(mock_sample, size()).WillRepeatedly(testing::Return(3));



    auto result = bootstrap(1.0, sample_data, sample_data + 3, mock_sample, mock_estimator);

    EXPECT_DOUBLE_EQ(result.point_estimate, mock_estimator(sample_data, sample_data + 3));

    EXPECT_DOUBLE_EQ(result.lower_bound, mock_estimator(sample_data, sample_data + 3));

    EXPECT_DOUBLE_EQ(result.upper_bound, mock_estimator(sample_data, sample_data + 3));

}
