#include <gtest/gtest.h>
#include <set>
#include <cmath>
#include <vector>

// Declaration of the function under test
double grandom_double();

class GRandomDoubleTest_27 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that grandom_double returns a value in [0, 1)
TEST_F(GRandomDoubleTest_27, ReturnsValueInZeroToOneRange_27) {
    for (int i = 0; i < 10000; ++i) {
        double val = grandom_double();
        EXPECT_GE(val, 0.0) << "Value should be >= 0.0, got " << val;
        EXPECT_LT(val, 1.0) << "Value should be < 1.0, got " << val;
    }
}

// Test that grandom_double returns finite values
TEST_F(GRandomDoubleTest_27, ReturnsFiniteValues_27) {
    for (int i = 0; i < 1000; ++i) {
        double val = grandom_double();
        EXPECT_TRUE(std::isfinite(val)) << "Value should be finite, got " << val;
    }
}

// Test that grandom_double does not return NaN
TEST_F(GRandomDoubleTest_27, DoesNotReturnNaN_27) {
    for (int i = 0; i < 1000; ++i) {
        double val = grandom_double();
        EXPECT_FALSE(std::isnan(val)) << "Value should not be NaN";
    }
}

// Test that grandom_double does not return infinity
TEST_F(GRandomDoubleTest_27, DoesNotReturnInfinity_27) {
    for (int i = 0; i < 1000; ++i) {
        double val = grandom_double();
        EXPECT_FALSE(std::isinf(val)) << "Value should not be infinity";
    }
}

// Test that grandom_double produces varying values (not constant)
TEST_F(GRandomDoubleTest_27, ProducesVaryingValues_27) {
    std::set<double> values;
    for (int i = 0; i < 100; ++i) {
        values.insert(grandom_double());
    }
    // It's extremely unlikely that 100 random doubles are all the same
    EXPECT_GT(values.size(), 1u) << "Random values should not all be identical";
}

// Test that grandom_double produces reasonable distribution (not clustered)
TEST_F(GRandomDoubleTest_27, ProducesReasonableDistribution_27) {
    int below_half = 0;
    int above_half = 0;
    const int num_samples = 10000;
    
    for (int i = 0; i < num_samples; ++i) {
        double val = grandom_double();
        if (val < 0.5) {
            below_half++;
        } else {
            above_half++;
        }
    }
    
    // With 10000 samples, we expect roughly 5000 in each half.
    // Allow a generous margin (e.g., each should be at least 3000)
    EXPECT_GT(below_half, 3000) << "Distribution seems skewed: too few values below 0.5";
    EXPECT_GT(above_half, 3000) << "Distribution seems skewed: too few values above 0.5";
}

// Test that grandom_double never returns exactly 1.0
TEST_F(GRandomDoubleTest_27, NeverReturnsExactlyOne_27) {
    for (int i = 0; i < 100000; ++i) {
        double val = grandom_double();
        EXPECT_NE(val, 1.0) << "generate_canonical should never return exactly 1.0";
    }
}

// Test that grandom_double never returns negative values
TEST_F(GRandomDoubleTest_27, NeverReturnsNegative_27) {
    for (int i = 0; i < 100000; ++i) {
        double val = grandom_double();
        EXPECT_GE(val, 0.0) << "Value should never be negative, got " << val;
    }
}

// Test that calling grandom_double many times does not crash or hang
TEST_F(GRandomDoubleTest_27, StressTestNocrash_27) {
    for (int i = 0; i < 1000000; ++i) {
        volatile double val = grandom_double();
        (void)val;
    }
}

// Test that grandom_double produces sufficient entropy (many distinct values)
TEST_F(GRandomDoubleTest_27, ProducesSufficientEntropy_27) {
    std::set<double> values;
    for (int i = 0; i < 1000; ++i) {
        values.insert(grandom_double());
    }
    // 1000 random doubles should produce at least 990 unique values
    EXPECT_GT(values.size(), 990u) << "Expected nearly all unique values from 1000 random doubles";
}

// Test that values span the full range [0, 1) with quartile coverage
TEST_F(GRandomDoubleTest_27, CoversAllQuartiles_27) {
    bool q1 = false, q2 = false, q3 = false, q4 = false;
    for (int i = 0; i < 10000; ++i) {
        double val = grandom_double();
        if (val < 0.25) q1 = true;
        else if (val < 0.5) q2 = true;
        else if (val < 0.75) q3 = true;
        else q4 = true;
    }
    EXPECT_TRUE(q1) << "No values in [0, 0.25)";
    EXPECT_TRUE(q2) << "No values in [0.25, 0.5)";
    EXPECT_TRUE(q3) << "No values in [0.5, 0.75)";
    EXPECT_TRUE(q4) << "No values in [0.75, 1.0)";
}

// Test that successive calls return different values
TEST_F(GRandomDoubleTest_27, SuccessiveCallsReturnDifferentValues_27) {
    double prev = grandom_double();
    int different_count = 0;
    for (int i = 0; i < 100; ++i) {
        double curr = grandom_double();
        if (curr != prev) {
            different_count++;
        }
        prev = curr;
    }
    // Virtually all successive pairs should be different
    EXPECT_GT(different_count, 95) << "Successive calls should almost always return different values";
}
