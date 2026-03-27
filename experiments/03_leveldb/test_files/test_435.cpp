#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/histogram.h"



using namespace leveldb;



class HistogramTest_435 : public ::testing::Test {

protected:

    Histogram histogram;

};



TEST_F(HistogramTest_435, AddSingleValueUpdatesMinAndMax_435) {

    double value = 10.0;

    histogram.Add(value);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("min\\s*=\\s*10\\.0"));

    EXPECT_THAT(result, testing::ContainsRegex("max\\s*=\\s*10\\.0"));

}



TEST_F(HistogramTest_435, AddMultipleValuesUpdatesMinAndMax_435) {

    histogram.Add(5.0);

    histogram.Add(20.0);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("min\\s*=\\s*5\\.0"));

    EXPECT_THAT(result, testing::ContainsRegex("max\\s*=\\s*20\\.0"));

}



TEST_F(HistogramTest_435, AddZeroValueUpdatesMinAndMax_435) {

    histogram.Add(0.0);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("min\\s*=\\s*0\\.0"));

    EXPECT_THAT(result, testing::ContainsRegex("max\\s*=\\s*0\\.0"));

}



TEST_F(HistogramTest_435, AddNegativeValueUpdatesMinAndMax_435) {

    histogram.Add(-10.0);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("min\\s*=\\s*-10\\.0"));

    EXPECT_THAT(result, testing::ContainsRegex("max\\s*=\\s*-10\\.0"));

}



TEST_F(HistogramTest_435, AddMultipleValuesCalculatesAverageCorrectly_435) {

    histogram.Add(10.0);

    histogram.Add(20.0);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("avg\\s*=\\s*15\\.0"));

}



TEST_F(HistogramTest_435, AddValuesCalculatesSumCorrectly_435) {

    histogram.Add(10.0);

    histogram.Add(20.0);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("sum\\s*=\\s*30\\.0"));

}



TEST_F(HistogramTest_435, AddValuesCalculatesSumSquaresCorrectly_435) {

    histogram.Add(10.0);

    histogram.Add(20.0);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("sum_squares\\s*=\\s*500\\.0"));

}



TEST_F(HistogramTest_435, ClearResetsHistogram_435) {

    histogram.Add(10.0);

    histogram.Clear();

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("min\\s*=\\s*inf"));

    EXPECT_THAT(result, testing::ContainsRegex("max\\s*=\\s*-inf"));

    EXPECT_THAT(result, testing::ContainsRegex("num\\s*=\\s*0"));

}



TEST_F(HistogramTest_435, MergeCombinesTwoHistogramsCorrectly_435) {

    Histogram other;

    histogram.Add(10.0);

    other.Add(20.0);

    histogram.Merge(other);

    std::string result = histogram.ToString();

    EXPECT_THAT(result, testing::ContainsRegex("min\\s*=\\s*10\\.0"));

    EXPECT_THAT(result, testing::ContainsRegex("max\\s*=\\s*20\\.0"));

    EXPECT_THAT(result, testing::ContainsRegex("num\\s*=\\s*2"));

}



TEST_F(HistogramTest_435, ToStringReturnsNonEmptyString_435) {

    histogram.Add(10.0);

    std::string result = histogram.ToString();

    EXPECT_FALSE(result.empty());

}
