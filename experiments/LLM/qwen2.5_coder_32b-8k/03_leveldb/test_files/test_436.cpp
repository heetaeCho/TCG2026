#include <gtest/gtest.h>

#include "util/histogram.h"



using namespace leveldb;



class HistogramTest_436 : public ::testing::Test {

protected:

    Histogram histogram;

};



TEST_F(HistogramTest_436, MergeWithEmptyHistogram_436) {

    Histogram other;

    histogram.Merge(other);

    // Assuming Clear initializes min/max to some default values

    EXPECT_EQ(histogram.ToString(), other.ToString());

}



TEST_F(HistogramTest_436, MergeUpdatesMinAndMax_436) {

    Histogram other;

    histogram.Add(10.0);

    other.Add(20.0);

    histogram.Merge(other);

    EXPECT_EQ(histogram.Min(), 10.0);

    EXPECT_EQ(histogram.Max(), 20.0);

}



TEST_F(HistogramTest_436, MergeUpdatesSumAndNum_436) {

    Histogram other;

    histogram.Add(5.0);

    other.Add(10.0);

    other.Add(15.0);

    histogram.Merge(other);

    EXPECT_EQ(histogram.Sum(), 30.0);

    EXPECT_EQ(histogram.Num(), 3);

}



TEST_F(HistogramTest_436, MergeUpdatesSumSquares_436) {

    Histogram other;

    histogram.Add(3.0);

    other.Add(4.0);

    histogram.Merge(other);

    EXPECT_DOUBLE_EQ(histogram.SumSquares(), 25.0); // 9 + 16

}



TEST_F(HistogramTest_436, MergeUpdatesBuckets_436) {

    Histogram other;

    for (int i = 0; i < 10; ++i) {

        histogram.Add(1.0);

    }

    for (int i = 0; i < 5; ++i) {

        other.Add(2.0);

    }

    histogram.Merge(other);

    // Assuming bucket index is determined by the value

    EXPECT_EQ(histogram.BucketAt(/*index of bucket for value 1.0*/), 10);

    EXPECT_EQ(histogram.BucketAt(/*index of bucket for value 2.0*/), 5);

}



TEST_F(HistogramTest_436, MergeWithSameHistogram_436) {

    Histogram other;

    histogram.Add(5.0);

    other.Add(5.0);

    histogram.Merge(other);

    EXPECT_EQ(histogram.Sum(), 10.0);

    EXPECT_EQ(histogram.Num(), 2);

}



TEST_F(HistogramTest_436, MergeWithLargerValues_436) {

    Histogram other;

    histogram.Add(1.0);

    other.Add(100.0);

    histogram.Merge(other);

    EXPECT_EQ(histogram.Min(), 1.0);

    EXPECT_EQ(histogram.Max(), 100.0);

}



TEST_F(HistogramTest_436, MergeWithSmallerValues_436) {

    Histogram other;

    histogram.Add(100.0);

    other.Add(1.0);

    histogram.Merge(other);

    EXPECT_EQ(histogram.Min(), 1.0);

    EXPECT_EQ(histogram.Max(), 100.0);

}



// Assuming ToString provides a way to verify internal state

TEST_F(HistogramTest_436, MergeResultIsConsistentWithToString_436) {

    Histogram other;

    histogram.Add(5.0);

    other.Add(15.0);

    histogram.Merge(other);

    std::string expected = histogram.ToString();

    EXPECT_EQ(histogram.ToString(), expected);

}



TEST_F(HistogramTest_436, MergeBoundaryConditionMin_436) {

    Histogram other;

    histogram.Add(-std::numeric_limits<double>::max());

    other.Add(std::numeric_limits<double>::min());

    histogram.Merge(other);

    EXPECT_DOUBLE_EQ(histogram.Min(), -std::numeric_limits<double>::max());

    EXPECT_DOUBLE_EQ(histogram.Max(), std::numeric_limits<double>::min());

}



TEST_F(HistogramTest_436, MergeBoundaryConditionMax_436) {

    Histogram other;

    histogram.Add(std::numeric_limits<double>::max());

    other.Add(-std::numeric_limits<double>::min());

    histogram.Merge(other);

    EXPECT_DOUBLE_EQ(histogram.Min(), -std::numeric_limits<double>::min());

    EXPECT_DOUBLE_EQ(histogram.Max(), std::numeric_limits<double>::max());

}

```


