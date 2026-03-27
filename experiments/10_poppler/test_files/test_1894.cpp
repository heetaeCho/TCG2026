#include <gtest/gtest.h>

#include <cmath>



extern int compute_coverage(int coverage[], int src_length, int dest_length);



class ComputeCoverageTest_1894 : public ::testing::Test {

protected:

    static const int MAX_LENGTH = 1024;

    int coverage[MAX_LENGTH];



    void AssertCoverage(int expected[], int length) {

        for (int i = 0; i < length; ++i) {

            EXPECT_EQ(expected[i], coverage[i]) << "Mismatch at index " << i;

        }

    }

};



TEST_F(ComputeCoverageTest_1894, NormalOperation_SrcLengthGreaterThanDestLength_1894) {

    int src_length = 256;

    int dest_length = 128;

    compute_coverage(coverage, src_length, dest_length);



    // Expected coverage values are derived based on the provided function logic

    // Example: For each destination pixel, calculate the expected coverage value

    int expected[128];

    double scale = static_cast<double>(src_length) / dest_length;

    for (int i = 0; i < dest_length; ++i) {

        double left_side = i * scale;

        double right_side = (i + 1) * scale;

        double right_fract = right_side - std::floor(right_side);

        double left_fract = std::ceil(left_side) - left_side;

        int count = static_cast<int>(std::floor(right_side)) - static_cast<int>(std::ceil(left_side));

        if (left_fract == 0.0) {

            count--;

        }

        int overage = ((1 << 24) * right_fract);

        expected[i] = (1 << 24) - (count * (1 << 24) / src_length + overage);

    }



    AssertCoverage(expected, dest_length);

}



TEST_F(ComputeCoverageTest_1894, NormalOperation_SrcLengthEqualsDestLength_1894) {

    int src_length = 256;

    int dest_length = 256;

    compute_coverage(coverage, src_length, dest_length);



    // Each destination pixel covers exactly one source pixel

    int expected[256] = {(1 << 24)};

    AssertCoverage(expected, dest_length);

}



TEST_F(ComputeCoverageTest_1894, BoundaryCondition_ZeroSrcLength_1894) {

    int src_length = 0;

    int dest_length = 128;



    // Expecting undefined behavior or crash; however, based on the function,

    // it will not crash and return a ratio of 0

    EXPECT_THROW(compute_coverage(coverage, src_length, dest_length), std::invalid_argument);

}



TEST_F(ComputeCoverageTest_1894, BoundaryCondition_ZeroDestLength_1894) {

    int src_length = 256;

    int dest_length = 0;



    // Expecting undefined behavior or crash; however, based on the function,

    // it will not crash and return a ratio of 0

    EXPECT_THROW(compute_coverage(coverage, src_length, dest_length), std::invalid_argument);

}



TEST_F(ComputeCoverageTest_1894, BoundaryCondition_MaxSrcLength_1894) {

    int src_length = ComputeCoverageTest_1894::MAX_LENGTH;

    int dest_length = 128;



    compute_coverage(coverage, src_length, dest_length);



    // Expected coverage values are derived based on the provided function logic

    int expected[128];

    double scale = static_cast<double>(src_length) / dest_length;

    for (int i = 0; i < dest_length; ++i) {

        double left_side = i * scale;

        double right_side = (i + 1) * scale;

        double right_fract = right_side - std::floor(right_side);

        double left_fract = std::ceil(left_side) - left_side;

        int count = static_cast<int>(std::floor(right_side)) - static_cast<int>(std::ceil(left_side));

        if (left_fract == 0.0) {

            count--;

        }

        int overage = ((1 << 24) * right_fract);

        expected[i] = (1 << 24) - (count * (1 << 24) / src_length + overage);

    }



    AssertCoverage(expected, dest_length);

}



TEST_F(ComputeCoverageTest_1894, BoundaryCondition_MaxDestLength_1894) {

    int src_length = 128;

    int dest_length = ComputeCoverageTest_1894::MAX_LENGTH;



    compute_coverage(coverage, src_length, dest_length);



    // Expected coverage values are derived based on the provided function logic

    int expected[MAX_LENGTH] = {0};

    double scale = static_cast<double>(src_length) / dest_length;

    for (int i = 0; i < dest_length; ++i) {

        double left_side = i * scale;

        double right_side = (i + 1) * scale;

        double right_fract = right_side - std::floor(right_side);

        double left_fract = std::ceil(left_side) - left_side;

        int count = static_cast<int>(std::floor(right_side)) - static_cast<int>(std::ceil(left_side));

        if (left_fract == 0.0) {

            count--;

        }

        int overage = ((1 << 24) * right_fract);

        expected[i] = (1 << 24) - (count * (1 << 24) / src_length + overage);

    }



    AssertCoverage(expected, dest_length);

}
