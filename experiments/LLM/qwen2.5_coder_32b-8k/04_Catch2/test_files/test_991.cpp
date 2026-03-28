#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"



using namespace Catch::Benchmark::Detail;

using namespace Catch;



// Test fixture for bootstrap_analysis function

class BootstrapAnalysisTest_991 : public ::testing::Test {

protected:

    double samples[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    double confidence_level = 0.95;

    unsigned int n_resamples = 1000;



    Estimate<double> callBootstrapAnalysis() {

        return analyse_samples(confidence_level, n_resamples, samples, samples + 5);

    }

};



// Test normal operation

TEST_F(BootstrapAnalysisTest_991, NormalOperation_991) {

    auto result = callBootstrapAnalysis();

    EXPECT_TRUE(result.point >= 1.0 && result.point <= 5.0); // Mean should be within sample range

}



// Test boundary conditions with minimum and maximum values

TEST_F(BootstrapAnalysisTest_991, BoundaryConditionsMinMax_991) {

    double min_samples[3] = {1.0, 1.0, 1.0};

    double max_samples[3] = {5.0, 5.0, 5.0};



    auto result_min = analyse_samples(confidence_level, n_resamples, min_samples, min_samples + 3);

    EXPECT_DOUBLE_EQ(result_min.point, 1.0);



    auto result_max = analyse_samples(confidence_level, n_resamples, max_samples, max_samples + 3);

    EXPECT_DOUBLE_EQ(result_max.point, 5.0);

}



// Test with a single sample (edge case)

TEST_F(BootstrapAnalysisTest_991, SingleSample_991) {

    double single_sample[1] = {42.0};

    auto result = analyse_samples(confidence_level, n_resamples, single_sample, single_sample + 1);

    EXPECT_DOUBLE_EQ(result.point, 42.0);

}



// Test with zero resamples (edge case)

TEST_F(BootstrapAnalysisTest_991, ZeroResamples_991) {

    unsigned int zero_n_resamples = 0;

    auto result = analyse_samples(confidence_level, zero_n_resamples, samples, samples + 5);

    // Assuming the function handles zero resamples gracefully

    EXPECT_TRUE(result.point >= 1.0 && result.point <= 5.0); // Mean should be within sample range

}



// Test with confidence level of 0 (edge case)

TEST_F(BootstrapAnalysisTest_991, ConfidenceLevelZero_991) {

    double zero_confidence_level = 0.0;

    auto result = analyse_samples(zero_confidence_level, n_resamples, samples, samples + 5);

    // Assuming the function handles zero confidence level gracefully

    EXPECT_TRUE(result.point >= 1.0 && result.point <= 5.0); // Mean should be within sample range

}



// Test with confidence level of 1 (edge case)

TEST_F(BootstrapAnalysisTest_991, ConfidenceLevelOne_991) {

    double one_confidence_level = 1.0;

    auto result = analyse_samples(one_confidence_level, n_resamples, samples, samples + 5);

    // Assuming the function handles one confidence level gracefully

    EXPECT_TRUE(result.point >= 1.0 && result.point <= 5.0); // Mean should be within sample range

}
