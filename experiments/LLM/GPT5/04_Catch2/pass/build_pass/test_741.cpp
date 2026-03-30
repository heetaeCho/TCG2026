// File: tests/config_benchmarkNoAnalysis_741_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"  // Path as provided in your tree

using namespace Catch;

class ConfigBenchmarkNoAnalysisTest_741 : public ::testing::Test {
protected:
    ConfigData data{};
};

// [Normal] Default constructed ConfigData should yield false
TEST_F(ConfigBenchmarkNoAnalysisTest_741, DefaultIsFalse_741) {
    // Given
    Config cfg{data};

    // Then
    EXPECT_FALSE(cfg.benchmarkNoAnalysis());
}

// [Normal] Explicitly setting to true should be observed via the getter
TEST_F(ConfigBenchmarkNoAnalysisTest_741, ReturnsTrueWhenEnabled_741) {
    // Given
    data.benchmarkNoAnalysis = true;
    Config cfg{data};

    // Then
    EXPECT_TRUE(cfg.benchmarkNoAnalysis());
}

// [Boundary] Explicitly setting to false should be observed via the getter
TEST_F(ConfigBenchmarkNoAnalysisTest_741, ReturnsFalseWhenDisabled_741) {
    // Given
    data.benchmarkNoAnalysis = false;
    Config cfg{data};

    // Then
    EXPECT_FALSE(cfg.benchmarkNoAnalysis());
}

// [Boundary] Getter must be callable and correct on const objects (const-correctness)
TEST_F(ConfigBenchmarkNoAnalysisTest_741, ConstObjectCall_741) {
    // Given
    data.benchmarkNoAnalysis = true;
    const Config cfg{data};  // const object

    // Then
    EXPECT_TRUE(cfg.benchmarkNoAnalysis());
}

// [Exceptional/Interaction] Ensure orthogonality vs. skipBenchmarks (no hidden coupling)
// Case A: skipBenchmarks=true, benchmarkNoAnalysis=false -> getter must still be false
TEST_F(ConfigBenchmarkNoAnalysisTest_741, IndependentFromSkipBenchmarks_FalseWhenOnlySkipEnabled_741) {
    // Given
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = false;
    Config cfg{data};

    // Then
    EXPECT_FALSE(cfg.benchmarkNoAnalysis());
}

// Case B: skipBenchmarks=false, benchmarkNoAnalysis=true -> getter must still be true
TEST_F(ConfigBenchmarkNoAnalysisTest_741, IndependentFromSkipBenchmarks_TrueWhenOnlyNoAnalysisEnabled_741) {
    // Given
    data.skipBenchmarks = false;
    data.benchmarkNoAnalysis = true;
    Config cfg{data};

    // Then
    EXPECT_TRUE(cfg.benchmarkNoAnalysis());
}
