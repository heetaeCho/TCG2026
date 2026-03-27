#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the full class definition from Known or Inferred Dependencies

class HorizontalTextLayouter {

public:

    int consumedText;

    HorizontalTextLayouter() = default;

    HorizontalTextLayouter(const GooString *text, const Form *form, const GfxFont *font, std::optional<double> availableWidth, const bool noReencode);

    HorizontalTextLayouter(const HorizontalTextLayouter &) = delete;

    HorizontalTextLayouter &operator=(const HorizontalTextLayouter &) = delete;

    double totalWidth() const;

    int totalCharCount() const;



private:

    struct Data {

        int charCount;

    };

    std::vector<Data> data;

};



// Test fixture for HorizontalTextLayouter

class HorizontalTextLayouterTest : public ::testing::Test {

protected:

    HorizontalTextLayouter layouter;

};



// Test case: Verify totalCharCount returns 0 when no text is added - TEST_ID 2024

TEST_F(HorizontalTextLayouterTest, TotalCharCountZero_2024) {

    EXPECT_EQ(layouter.totalCharCount(), 0);

}



// Test case: Verify totalCharCount returns correct count for single data entry - TEST_ID 2024

TEST_F(HorizontalTextLayouterTest, TotalCharCountSingleEntry_2024) {

    HorizontalTextLayouter::Data d1 = {5};

    layouter.data.push_back(d1);

    EXPECT_EQ(layouter.totalCharCount(), 5);

}



// Test case: Verify totalCharCount returns correct count for multiple data entries - TEST_ID 2024

TEST_F(HorizontalTextLayouterTest, TotalCharCountMultipleEntries_2024) {

    HorizontalTextLayouter::Data d1 = {3};

    HorizontalTextLayouter::Data d2 = {7};

    layouter.data.push_back(d1);

    layouter.data.push_back(d2);

    EXPECT_EQ(layouter.totalCharCount(), 10);

}



// Test case: Verify totalCharCount handles boundary condition of max int - TEST_ID 2024

TEST_F(HorizontalTextLayouterTest, TotalCharCountMaxInt_2024) {

    HorizontalTextLayouter::Data d1 = {INT_MAX};

    layouter.data.push_back(d1);

    EXPECT_EQ(layouter.totalCharCount(), INT_MAX);

}



// Test case: Verify totalCharCount handles boundary condition of zero char counts - TEST_ID 2024

TEST_F(HorizontalTextLayouterTest, TotalCharCountZeroCounts_2024) {

    HorizontalTextLayouter::Data d1 = {0};

    HorizontalTextLayouter::Data d2 = {0};

    layouter.data.push_back(d1);

    layouter.data.push_back(d2);

    EXPECT_EQ(layouter.totalCharCount(), 0);

}



// Test case: Verify totalWidth is callable (boundary condition) - TEST_ID 2024

TEST_F(HorizontalTextLayouterTest, TotalWidthCallable_2024) {

    EXPECT_CALL(*this, totalWidth()).Times(1); // This would require a mock if totalWidth was virtual, but since it's not, we just call it.

    layouter.totalWidth(); // Ensure no crash or undefined behavior

}
