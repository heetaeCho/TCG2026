#include <gtest/gtest.h>

#include <vector>



namespace Catch {

namespace Benchmark {

namespace Detail {



// Mocking OutlierClassification for testing purposes

class MockOutlierClassification : public OutlierClassification {

public:

    MOCK_CONST_METHOD0(total, int());

};



TEST(classify_outliers_985, NormalOperation_NoOutliers_985) {

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    OutlierClassification result = classify_outliers(data.data(), data.data() + data.size());

    EXPECT_EQ(result.samples_seen, 5);

    EXPECT_EQ(result.low_severe, 0);

    EXPECT_EQ(result.low_mild, 0);

    EXPECT_EQ(result.high_mild, 0);

    EXPECT_EQ(result.high_severe, 0);

}



TEST(classify_outliers_985, NormalOperation_WithOutliers_985) {

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, -10.0, 20.0};

    OutlierClassification result = classify_outliers(data.data(), data.data() + data.size());

    EXPECT_EQ(result.samples_seen, 7);

    EXPECT_EQ(result.low_severe, 1);

    EXPECT_EQ(result.low_mild, 0);

    EXPECT_EQ(result.high_mild, 0);

    EXPECT_EQ(result.high_severe, 1);

}



TEST(classify_outliers_985, BoundaryCondition_SingleElement_985) {

    std::vector<double> data = {3.0};

    OutlierClassification result = classify_outliers(data.data(), data.data() + data.size());

    EXPECT_EQ(result.samples_seen, 1);

    EXPECT_EQ(result.low_severe, 0);

    EXPECT_EQ(result.low_mild, 0);

    EXPECT_EQ(result.high_mild, 0);

    EXPECT_EQ(result.high_severe, 0);

}



TEST(classify_outliers_985, BoundaryCondition_EmptyData_985) {

    std::vector<double> data = {};

    OutlierClassification result = classify_outliers(data.data(), data.data() + data.size());

    EXPECT_EQ(result.samples_seen, 0);

    EXPECT_EQ(result.low_severe, 0);

    EXPECT_EQ(result.low_mild, 0);

    EXPECT_EQ(result.high_mild, 0);

    EXPECT_EQ(result.high_severe, 0);

}



TEST(classify_outliers_985, ExceptionalCase_AllSameValues_985) {

    std::vector<double> data = {2.0, 2.0, 2.0, 2.0, 2.0};

    OutlierClassification result = classify_outliers(data.data(), data.data() + data.size());

    EXPECT_EQ(result.samples_seen, 5);

    EXPECT_EQ(result.low_severe, 0);

    EXPECT_EQ(result.low_mild, 0);

    EXPECT_EQ(result.high_mild, 0);

    EXPECT_EQ(result.high_severe, 0);

}



} // namespace Detail

} // namespace Benchmark

} // namespace Catch
