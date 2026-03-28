#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"

#include "./TestProjects/Catch2/src/catch2/benchmark/catch_estimate.hpp"

#include "./TestProjects/Catch2/src/catch2/benchmark/catch_outlier_classification.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using namespace Catch::Benchmark;

using namespace Catch::Benchmark::Detail;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));

};



TEST_F(MockIConfigTest_982, NormalOperationWithAnalysis_982) {

    MockIConfig config;

    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(testing::Return(false));

    EXPECT_CALL(config, benchmarkConfidenceInterval()).WillOnce(testing::Return(0.95));

    EXPECT_CALL(config, benchmarkResamples()).WillOnce(testing::Return(100));



    FDuration samples[] = {FDuration(1), FDuration(2), FDuration(3)};

    SampleAnalysis result = analyse(config, &samples[0], &samples[3]);



    ASSERT_EQ(result.samples.size(), 3);

    EXPECT_DOUBLE_EQ(result.mean.point.count(), 2.0);

}



TEST_F(MockIConfigTest_982, NormalOperationWithoutAnalysis_982) {

    MockIConfig config;

    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(testing::Return(true));



    FDuration samples[] = {FDuration(1), FDuration(2), FDuration(3)};

    SampleAnalysis result = analyse(config, &samples[0], &samples[3]);



    ASSERT_EQ(result.samples.size(), 3);

    EXPECT_DOUBLE_EQ(result.mean.point.count(), 2.0);

}



TEST_F(MockIConfigTest_982, SingleSample_982) {

    MockIConfig config;

    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(testing::Return(true));



    FDuration samples[] = {FDuration(1)};

    SampleAnalysis result = analyse(config, &samples[0], &samples[1]);



    ASSERT_EQ(result.samples.size(), 1);

    EXPECT_DOUBLE_EQ(result.mean.point.count(), 1.0);

}



TEST_F(MockIConfigTest_982, EmptySampleSet_982) {

    MockIConfig config;

    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(testing::Return(true));



    FDuration samples[] = {};

    SampleAnalysis result = analyse(config, &samples[0], &samples[0]);



    ASSERT_EQ(result.samples.size(), 0);

}



TEST_F(MockIConfigTest_982, ZeroConfidenceInterval_982) {

    MockIConfig config;

    EXPECT_CALL(config, benchmarkNoAnalysis()).WillOnce(testing::Return(false));

    EXPECT_CALL(config, benchmarkConfidenceInterval()).WillOnce(testing::Return(0.0));

    EXPECT_CALL(config, benchmarkResamples()).WillOnce(testing::Return(100));



    FDuration samples[] = {FDuration(1), FDuration(2), FDuration(3)};

    SampleAnalysis result = analyse(config, &samples[0], &samples[3]);



    ASSERT_EQ(result.samples.size(), 3);

    EXPECT_DOUBLE_EQ(result.mean.confidence_interval, 0.0);

}
