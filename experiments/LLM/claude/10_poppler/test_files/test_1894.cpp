#include <gtest/gtest.h>
#include <cmath>
#include <vector>

// We need to declare the function since it's static in the .cc file.
// To test a static function, we include the source file directly.
// This is a common technique for testing static (file-scope) functions.

// Include the source file to get access to the static function
// We need to handle potential include dependencies

// Forward declare or re-include. Since the function is static, we must include the .cc
// But first let's check what headers it needs.

#include <cstdlib>
#include <cstring>

// Include the implementation file to access the static function
// We wrap it to avoid multiple definition issues
namespace CairoRescaleBoxTest {
#include "CairoRescaleBox.cc"
}

using CairoRescaleBoxTest::compute_coverage;

class ComputeCoverageTest_1894 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic downscaling: dest_length < src_length
TEST_F(ComputeCoverageTest_1894, BasicDownscale2to1_1894) {
    int coverage[1];
    int ratio = compute_coverage(coverage, 2, 1);
    
    // ratio should be (1<<24) * 1 / 2 = 8388608
    EXPECT_EQ(ratio, (1 << 24) / 2);
    
    // coverage[0] should be computed
    // scale = 2.0/1.0 = 2.0
    // i=0: left_side=0, right_side=2.0
    // right_fract = 2.0 - floor(2.0) = 0.0
    // left_fract = ceil(0) - 0 = 0.0
    // count = floor(2.0) - ceil(0.0) = 2 - 0 = 2
    // left_fract == 0 => count-- => count = 1
    // overage = ratio * 0.0 = 0
    // coverage[0] = (1<<24) - (1 * ratio + 0) = 16777216 - 8388608 = 8388608
    EXPECT_EQ(coverage[0], (1 << 24) - ratio);
}

// Test identity: src_length == dest_length
TEST_F(ComputeCoverageTest_1894, IdentityScale_1894) {
    const int length = 5;
    int coverage[length];
    int ratio = compute_coverage(coverage, length, length);
    
    // ratio = (1<<24) * length / length = 1<<24
    EXPECT_EQ(ratio, 1 << 24);
    
    // scale = 1.0
    // For each i: left_side = i, right_side = i+1
    // right_fract = 0, left_fract = 0
    // count = (i+1) - i = 1, then count-- => count = 0
    // overage = ratio * 0 = 0
    // coverage[i] = (1<<24) - (0 * ratio + 0) = 1<<24
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(coverage[i], 1 << 24);
    }
}

// Test downscale by factor of 3
TEST_F(ComputeCoverageTest_1894, Downscale3to1_1894) {
    int coverage[1];
    int ratio = compute_coverage(coverage, 3, 1);
    
    // ratio = (1<<24) * 1 / 3 = 5592405 (integer division)
    EXPECT_EQ(ratio, ((1 << 24) * 1LL) / 3);
}

// Test downscale 4 to 2
TEST_F(ComputeCoverageTest_1894, Downscale4to2_1894) {
    int coverage[2];
    int ratio = compute_coverage(coverage, 4, 2);
    
    // ratio = (1<<24) * 2 / 4 = (1<<24) / 2 = 8388608
    EXPECT_EQ(ratio, (1 << 24) / 2);
    
    // scale = 4.0/2.0 = 2.0
    // For each pixel, same calculation as 2-to-1 case
    for (int i = 0; i < 2; i++) {
        // left_side = i*2.0, right_side = (i+1)*2.0
        // right_fract = 0, left_fract = 0
        // count = 2, then count-- => 1
        // overage = 0
        // coverage = (1<<24) - ratio
        EXPECT_EQ(coverage[i], (1 << 24) - ratio);
    }
}

// Test downscale 6 to 4
TEST_F(ComputeCoverageTest_1894, Downscale6to4_1894) {
    int coverage[4];
    int ratio = compute_coverage(coverage, 6, 4);
    
    // ratio = (1<<24) * 4 / 6 = (1<<24) * 2 / 3
    long long expected_ratio = ((1LL << 24) * 4) / 6;
    EXPECT_EQ(ratio, (int)expected_ratio);
}

// Test larger downscale
TEST_F(ComputeCoverageTest_1894, Downscale100to10_1894) {
    int coverage[10];
    int ratio = compute_coverage(coverage, 100, 10);
    
    // ratio = (1<<24) * 10 / 100 = (1<<24) / 10
    long long expected_ratio = ((1LL << 24) * 10) / 100;
    EXPECT_EQ(ratio, (int)expected_ratio);
    
    // All coverage values should be positive and within reasonable range
    for (int i = 0; i < 10; i++) {
        EXPECT_GT(coverage[i], 0);
        EXPECT_LE(coverage[i], 1 << 24);
    }
}

// Test downscale with non-integer ratio: 3 to 2
TEST_F(ComputeCoverageTest_1894, Downscale3to2_1894) {
    int coverage[2];
    int ratio = compute_coverage(coverage, 3, 2);
    
    // ratio = (1<<24) * 2 / 3
    long long expected_ratio = ((1LL << 24) * 2) / 3;
    EXPECT_EQ(ratio, (int)expected_ratio);
    
    // scale = 3.0/2.0 = 1.5
    // i=0: left_side=0.0, right_side=1.5
    //   right_fract = 0.5, left_fract = 0.0
    //   count = floor(1.5) - ceil(0) = 1 - 0 = 1
    //   left_fract == 0 => count-- => count = 0
    //   overage = ratio * 0.5
    //   coverage[0] = (1<<24) - (0 * ratio + overage) = (1<<24) - overage
    int overage0 = (int)(ratio * 0.5);
    EXPECT_EQ(coverage[0], (1 << 24) - overage0);
    
    // i=1: left_side=1.5, right_side=3.0
    //   right_fract = 0.0, left_fract = ceil(1.5) - 1.5 = 2.0 - 1.5 = 0.5
    //   count = floor(3.0) - ceil(1.5) = 3 - 2 = 1
    //   left_fract != 0 => no count--
    //   overage = ratio * 0.0 = 0
    //   coverage[1] = (1<<24) - (1 * ratio + 0) = (1<<24) - ratio
    EXPECT_EQ(coverage[1], (1 << 24) - ratio);
}

// Test downscale 5 to 3
TEST_F(ComputeCoverageTest_1894, Downscale5to3_1894) {
    int coverage[3];
    int ratio = compute_coverage(coverage, 5, 3);
    
    long long expected_ratio = ((1LL << 24) * 3) / 5;
    EXPECT_EQ(ratio, (int)expected_ratio);
    
    // All coverage values should be positive
    for (int i = 0; i < 3; i++) {
        EXPECT_GT(coverage[i], 0);
        EXPECT_LE(coverage[i], 1 << 24);
    }
}

// Test that coverage values are consistent with the scale factor
TEST_F(ComputeCoverageTest_1894, CoverageValuesPositive_1894) {
    const int src = 200;
    const int dest = 50;
    std::vector<int> coverage(dest);
    int ratio = compute_coverage(coverage.data(), src, dest);
    
    EXPECT_GT(ratio, 0);
    
    for (int i = 0; i < dest; i++) {
        EXPECT_GT(coverage[i], 0);
    }
}

// Test small values
TEST_F(ComputeCoverageTest_1894, SmallDownscale2to1Single_1894) {
    int coverage[1];
    int ratio = compute_coverage(coverage, 2, 1);
    EXPECT_EQ(ratio, 1 << 23); // (1<<24)/2
}

// Test dest_length = 1 with various src lengths
TEST_F(ComputeCoverageTest_1894, DestLength1_1894) {
    for (int src = 1; src <= 10; src++) {
        int coverage[1];
        int ratio = compute_coverage(coverage, src, 1);
        
        long long expected_ratio = ((1LL << 24) * 1) / src;
        EXPECT_EQ(ratio, (int)expected_ratio);
        
        EXPECT_GT(coverage[0], 0);
    }
}

// Test that ratio computation is correct for various combinations
TEST_F(ComputeCoverageTest_1894, RatioComputation_1894) {
    int coverage[10];
    
    // Test several src/dest combinations
    struct TestCase {
        int src;
        int dest;
    };
    
    TestCase cases[] = {
        {10, 5},
        {20, 10},
        {100, 25},
        {8, 4},
        {16, 8},
        {7, 3},
    };
    
    for (const auto &tc : cases) {
        std::vector<int> cov(tc.dest);
        int ratio = compute_coverage(cov.data(), tc.src, tc.dest);
        long long expected = ((1LL << 24) * tc.dest) / tc.src;
        EXPECT_EQ(ratio, (int)expected) 
            << "Failed for src=" << tc.src << " dest=" << tc.dest;
    }
}

// Test exact power of 2 downscale
TEST_F(ComputeCoverageTest_1894, PowerOf2Downscale_1894) {
    int coverage[4];
    int ratio = compute_coverage(coverage, 16, 4);
    
    // ratio = (1<<24) * 4 / 16 = (1<<24) / 4 = 1<<22
    EXPECT_EQ(ratio, 1 << 22);
    
    // scale = 4.0, all pixels should have same coverage
    // For each i: left_side = 4i, right_side = 4(i+1)
    // right_fract = 0, left_fract = 0
    // count = 4, count-- => 3
    // overage = 0
    // coverage = (1<<24) - 3*ratio
    int expected_cov = (1 << 24) - 3 * ratio;
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(coverage[i], expected_cov);
    }
}

// Test with large src and dest values
TEST_F(ComputeCoverageTest_1894, LargeValues_1894) {
    const int src = 4000;
    const int dest = 1000;
    std::vector<int> coverage(dest);
    int ratio = compute_coverage(coverage.data(), src, dest);
    
    long long expected_ratio = ((1LL << 24) * (long long)dest) / src;
    EXPECT_EQ(ratio, (int)expected_ratio);
    
    for (int i = 0; i < dest; i++) {
        EXPECT_GT(coverage[i], 0);
    }
}
