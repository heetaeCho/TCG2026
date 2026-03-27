#include <gtest/gtest.h>

#include "util/histogram.h"



using namespace leveldb;



class HistogramTest_437 : public ::testing::Test {

protected:

    Histogram histogram;

};



TEST_F(HistogramTest_437, InitialState_437) {

    EXPECT_EQ(histogram.ToString(), "Count: 0 Average: 0.0000 StdDev: 0.00\nMin: 0.0000 Median: 0.0000 Max: 0.0000\n------------------------------------------------------\n");

}



TEST_F(HistogramTest_437, AddSingleValue_437) {

    histogram.Add(5.0);

    EXPECT_EQ(histogram.ToString(), "Count: 1 Average: 5.0000 StdDev: 0.00\nMin: 5.0000 Median: 5.0000 Max: 5.0000\n------------------------------------------------------\n[       0,      10 )       1 100.000% 100.000% ####################\n");

}



TEST_F(HistogramTest_437, AddMultipleValues_437) {

    histogram.Add(5.0);

    histogram.Add(15.0);

    histogram.Add(25.0);

    EXPECT_EQ(histogram.ToString(), "Count: 3 Average: 15.0000 StdDev: 8.16\nMin: 5.0000 Median: 15.0000 Max: 25.0000\n------------------------------------------------------\n[       0,      10 )       1  33.333%  33.333% #######\n[      10,      20 )       1  33.333%  66.667% #######\n[      20,      30 )       1  33.333% 100.000% #######\n");

}



TEST_F(HistogramTest_437, MergeWithEmptyHistogram_437) {

    Histogram other;

    histogram.Add(5.0);

    histogram.Merge(other);

    EXPECT_EQ(histogram.ToString(), "Count: 1 Average: 5.0000 StdDev: 0.00\nMin: 5.0000 Median: 5.0000 Max: 5.0000\n------------------------------------------------------\n[       0,      10 )       1 100.000% 100.000% ####################\n");

}



TEST_F(HistogramTest_437, MergeWithNonEmptyHistogram_437) {

    Histogram other;

    histogram.Add(5.0);

    other.Add(25.0);

    histogram.Merge(other);

    EXPECT_EQ(histogram.ToString(), "Count: 2 Average: 15.0000 StdDev: 7.07\nMin: 5.0000 Median: 15.0000 Max: 25.0000\n------------------------------------------------------\n[       0,      10 )       1  50.000%  50.000% ##########\n[      20,      30 )       1  50.000% 100.000% ##########\n");

}



TEST_F(HistogramTest_437, ClearHistogram_437) {

    histogram.Add(5.0);

    histogram.Clear();

    EXPECT_EQ(histogram.ToString(), "Count: 0 Average: 0.0000 StdDev: 0.00\nMin: 0.0000 Median: 0.0000 Max: 0.0000\n------------------------------------------------------\n");

}
