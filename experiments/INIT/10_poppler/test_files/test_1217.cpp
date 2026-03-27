#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Test fixture class for TextOutputDev
class TextOutputDevTest : public ::testing::Test {
protected:
    TextOutputDev *textOutputDev;

    void SetUp() override {
        // Mock initialization as needed, for example:
        // textOutputDev = new TextOutputDev(...);
    }

    void TearDown() override {
        delete textOutputDev;
    }
};

// TEST_ID 1217 - Test case for normal operation of the `isOk` method
TEST_F(TextOutputDevTest, isOk_1217) {
    // Assuming the constructor initializes 'ok' to true
    EXPECT_TRUE(textOutputDev->isOk());
}

// TEST_ID 1218 - Test case for boundary condition of the `setMinColSpacing1` method
TEST_F(TextOutputDevTest, setMinColSpacing1_1218) {
    const double maxVal = std::numeric_limits<double>::max();
    textOutputDev->setMinColSpacing1(maxVal);
    EXPECT_EQ(textOutputDev->getMinColSpacing1(), maxVal);
    
    const double minVal = std::numeric_limits<double>::lowest();
    textOutputDev->setMinColSpacing1(minVal);
    EXPECT_EQ(textOutputDev->getMinColSpacing1(), minVal);
}

// TEST_ID 1219 - Test case for exceptional condition in `getText` method (empty area)
TEST_F(TextOutputDevTest, getTextEmptyArea_1219) {
    std::optional<PDFRectangle> emptyArea;
    EXPECT_EQ(textOutputDev->getText(emptyArea).getLength(), 0);
}

// TEST_ID 1220 - Test case for boundary condition of `getText` method (valid area)
TEST_F(TextOutputDevTest, getTextValidArea_1220) {
    PDFRectangle validArea(0, 0, 100, 100);
    std::optional<PDFRectangle> area(validArea);
    EXPECT_GT(textOutputDev->getText(area).getLength(), 0);
}

// TEST_ID 1221 - Test case for exceptional condition in `findText` method (case-sensitive search)
TEST_F(TextOutputDevTest, findTextCaseSensitive_1221) {
    const Unicode searchText = L"Hello";
    const int len = 5;
    double xMin, yMin, xMax, yMax;
    
    bool found = textOutputDev->findText(&searchText, len, true, true, false, false, true, false, true, false, &xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(found);
}

// TEST_ID 1222 - Test case for normal operation of `findText` method
TEST_F(TextOutputDevTest, findTextNormal_1222) {
    const Unicode searchText = L"Test";
    const int len = 4;
    double xMin, yMin, xMax, yMax;
    
    bool found = textOutputDev->findText(&searchText, len, true, true, false, false, false, false, false, false, &xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(found);
}

// TEST_ID 1223 - Test case for exceptional behavior in `startPage` method
TEST_F(TextOutputDevTest, startPageException_1223) {
    GfxState state;
    XRef xref;
    
    // Test invalid pageNum or state handling
    try {
        textOutputDev->startPage(-1, &state, &xref);  // Assuming this should throw an error
    } catch (const std::exception &e) {
        EXPECT_STREQ(e.what(), "Invalid page number");
    }
}

// TEST_ID 1224 - Test case for boundary condition of `takeText` method
TEST_F(TextOutputDevTest, takeTextBoundary_1224) {
    auto textPage = textOutputDev->takeText();
    EXPECT_NE(textPage, nullptr);
    // Further checks on the textPage could be added as needed
}