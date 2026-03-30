#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "util/histogram.h"



using namespace leveldb;



class HistogramTest_434 : public ::testing::Test {

protected:

    Histogram histogram;

};



TEST_F(HistogramTest_434, ClearResetsValues_434) {

    // Arrange

    histogram.Add(10.0);

    histogram.Add(20.0);



    // Act

    histogram.Clear();



    // Assert

    EXPECT_EQ(histogram.ToString(), "");

}



TEST_F(HistogramTest_434, AddSingleValue_434) {

    // Arrange & Act

    histogram.Add(5.0);



    // Assert

    EXPECT_NE(histogram.ToString(), "");

}



TEST_F(HistogramTest_434, AddMultipleValues_434) {

    // Arrange & Act

    histogram.Add(1.0);

    histogram.Add(2.0);

    histogram.Add(3.0);



    // Assert

    EXPECT_NE(histogram.ToString(), "");

}



TEST_F(HistogramTest_434, MergeWithAnotherHistogram_434) {

    // Arrange

    Histogram other;

    other.Add(15.0);

    other.Add(25.0);



    histogram.Add(10.0);

    histogram.Add(20.0);



    // Act

    histogram.Merge(other);



    // Assert

    EXPECT_NE(histogram.ToString(), "");

}



TEST_F(HistogramTest_434, ClearAfterMerge_434) {

    // Arrange

    Histogram other;

    other.Add(15.0);

    other.Add(25.0);



    histogram.Add(10.0);

    histogram.Add(20.0);

    histogram.Merge(other);



    // Act

    histogram.Clear();



    // Assert

    EXPECT_EQ(histogram.ToString(), "");

}



TEST_F(HistogramTest_434, AddBoundaryValues_434) {

    // Arrange & Act

    histogram.Add(std::numeric_limits<double>::min());

    histogram.Add(std::numeric_limits<double>::max());



    // Assert

    EXPECT_NE(histogram.ToString(), "");

}
