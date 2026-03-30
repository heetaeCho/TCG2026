#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.h"  // Assuming Annot.h contains the definition of HorizontalTextLayouter



using namespace testing;



TEST_F(HorizontalTextLayouterTest_2023, TotalWidth_ReturnsZeroForEmptyData_2023) {

    HorizontalTextLayouter layouter;

    EXPECT_EQ(layouter.totalWidth(), 0.0);

}



TEST_F(HorizontalTextLayouterTest_2023, TotalWidth_SumsUpWidthsOfAllDataEntries_2023) {

    // Assuming we can modify internal state for testing purposes

    HorizontalTextLayouter layouter;

    layouter.data.push_back({10.5});

    layouter.data.push_back({20.3});

    EXPECT_EQ(layouter.totalWidth(), 30.8);

}



TEST_F(HorizontalTextLayouterTest_2023, TotalCharCount_ReturnsZeroForEmptyData_2023) {

    HorizontalTextLayouter layouter;

    EXPECT_EQ(layouter.totalCharCount(), 0);

}



TEST_F(HorizontalTextLayouterTest_2023, TotalCharCount_SumsUpCharCountsOfAllDataEntries_2023) {

    // Assuming we can modify internal state for testing purposes

    HorizontalTextLayouter layouter;

    layouter.data.push_back({10.5, 5});

    layouter.data.push_back({20.3, 7});

    EXPECT_EQ(layouter.totalCharCount(), 12);

}



TEST_F(HorizontalTextLayouterTest_2023, Constructor_InitializesConsumedTextToZero_2023) {

    HorizontalTextLayouter layouter;

    EXPECT_EQ(layouter.consumedText, 0);

}



// Assuming GooString, Form, and GfxFont are mockable or provided by test setup

class MockGooString : public GooString {};

class MockForm : public Form {};

class MockGfxFont : public GfxFont {};



TEST_F(HorizontalTextLayouterTest_2023, ConstructorWithParameters_InitializesObjectCorrectly_2023) {

    MockGooString mockText;

    MockForm mockForm;

    MockGfxFont mockFont;

    std::optional<double> availableWidth = 100.0;

    bool noReencode = false;



    HorizontalTextLayouter layouter(&mockText, &mockForm, &mockFont, availableWidth, noReencode);

    // Assuming we can verify internal state through public functions

    EXPECT_EQ(layouter.consumedText, 0);  // Example check, adjust as necessary

}



TEST_F(HorizontalTextLayouterTest_2023, ConstructorWithParameters_InitializesObjectWithoutAvailableWidth_2023) {

    MockGooString mockText;

    MockForm mockForm;

    MockGfxFont mockFont;

    std::optional<double> availableWidth = std::nullopt;

    bool noReencode = false;



    HorizontalTextLayouter layouter(&mockText, &mockForm, &mockFont, availableWidth, noReencode);

    // Assuming we can verify internal state through public functions

    EXPECT_EQ(layouter.consumedText, 0);  // Example check, adjust as necessary

}



TEST_F(HorizontalTextLayouterTest_2023, ConstructorWithParameters_InitializesObjectWithNoReencodeTrue_2023) {

    MockGooString mockText;

    MockForm mockForm;

    MockGfxFont mockFont;

    std::optional<double> availableWidth = 100.0;

    bool noReencode = true;



    HorizontalTextLayouter layouter(&mockText, &mockForm, &mockFont, availableWidth, noReencode);

    // Assuming we can verify internal state through public functions

    EXPECT_EQ(layouter.consumedText, 0);  // Example check, adjust as necessary

}



TEST_F(HorizontalTextLayouterTest_2023, CopyConstructor_IsDeleted_2023) {

    HorizontalTextLayouter layouter;

    EXPECT_FALSE(std::is_copy_constructible<HorizontalTextLayouter>::value);

}



TEST_F(HorizontalTextLayouterTest_2023, AssignmentOperator_IsDeleted_2023) {

    HorizontalTextLayouter layouter;

    EXPECT_FALSE(std::is_assignable<HorizontalTextLayouter, HorizontalTextLayouter>::value);

}

```


