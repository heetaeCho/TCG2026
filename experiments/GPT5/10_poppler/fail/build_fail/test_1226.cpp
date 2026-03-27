#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Mock dependencies (if necessary, e.g., OutputDev, TextOutputFunc)
class MockOutputDev : public OutputDev {
public:
    MOCK_METHOD(void, startPage, (int, GfxState*, XRef*), (override));
    MOCK_METHOD(void, endPage, (), (override));
    MOCK_METHOD(void, restoreState, (GfxState*), (override));
    MOCK_METHOD(void, updateFont, (GfxState*), (override));
    MOCK_METHOD(void, beginString, (GfxState*, const GooString*), (override));
    MOCK_METHOD(void, endString, (GfxState*), (override));
    MOCK_METHOD(void, drawChar, (GfxState*, double, double, double, double, double, double, CharCode, int, const Unicode*, int), (override));
    MOCK_METHOD(void, incCharCount, (int), (override));
    MOCK_METHOD(void, beginActualText, (GfxState*, const GooString*), (override));
    MOCK_METHOD(void, endActualText, (GfxState*), (override));
    MOCK_METHOD(void, stroke, (GfxState*), (override));
    MOCK_METHOD(void, fill, (GfxState*), (override));
    MOCK_METHOD(void, eoFill, (GfxState*), (override));
    MOCK_METHOD(void, processLink, (AnnotLink*), (override));
};

class TextOutputDevTest_1226 : public ::testing::Test {
protected:
    // Mock dependencies
    MockOutputDev mockOutputDev;

    // Test subject
    TextOutputDev textOutputDev;

    // Setup and teardown can be placed here if needed
    void SetUp() override {
        // Initialize mock dependencies or textOutputDev as necessary
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

TEST_F(TextOutputDevTest_1226, GetMinColSpacing1_ReturnsCorrectValue_1226) {
    // Given
    double expectedMinColSpacing = 10.0;
    textOutputDev.setMinColSpacing1(expectedMinColSpacing);

    // When
    double minColSpacing = textOutputDev.getMinColSpacing1();

    // Then
    EXPECT_EQ(minColSpacing, expectedMinColSpacing);
}

TEST_F(TextOutputDevTest_1226, GetMinColSpacing1_DefaultValue_1226) {
    // Given
    double defaultMinColSpacing = 0.0;  // Assuming default value is 0.0

    // When
    double minColSpacing = textOutputDev.getMinColSpacing1();

    // Then
    EXPECT_EQ(minColSpacing, defaultMinColSpacing);
}

TEST_F(TextOutputDevTest_1226, SetMinColSpacing1_ValidValue_1226) {
    // Given
    double newMinColSpacing = 15.5;

    // When
    textOutputDev.setMinColSpacing1(newMinColSpacing);

    // Then
    EXPECT_EQ(textOutputDev.getMinColSpacing1(), newMinColSpacing);
}

TEST_F(TextOutputDevTest_1226, SetMinColSpacing1_NegativeValue_1226) {
    // Given
    double negativeMinColSpacing = -5.0;

    // When
    textOutputDev.setMinColSpacing1(negativeMinColSpacing);

    // Then
    EXPECT_EQ(textOutputDev.getMinColSpacing1(), negativeMinColSpacing);
}

TEST_F(TextOutputDevTest_1226, SetMinColSpacing1_ZeroValue_1226) {
    // Given
    double zeroMinColSpacing = 0.0;

    // When
    textOutputDev.setMinColSpacing1(zeroMinColSpacing);

    // Then
    EXPECT_EQ(textOutputDev.getMinColSpacing1(), zeroMinColSpacing);
}

TEST_F(TextOutputDevTest_1226, CheckTextPageBreaks_WhenSet_1226) {
    // Given
    textOutputDev.setTextPageBreaks(true);

    // When
    bool textPageBreaks = textOutputDev.isTextPageBreaksEnabled();

    // Then
    EXPECT_TRUE(textPageBreaks);
}

TEST_F(TextOutputDevTest_1226, CheckTextEOL_Setting_1226) {
    // Given
    EndOfLineKind eolSetting = EndOfLineKind::EOL_UNIX;
    textOutputDev.setTextEOL(eolSetting);

    // When
    EndOfLineKind currentEOL = textOutputDev.getTextEOL();

    // Then
    EXPECT_EQ(currentEOL, eolSetting);
}

// Verify external interaction (e.g., mock method call)
TEST_F(TextOutputDevTest_1226, ProcessLink_CallsExternalMethod_1226) {
    // Given
    AnnotLink* mockLink = new AnnotLink();

    // When
    textOutputDev.processLink(mockLink);

    // Then
    EXPECT_CALL(mockOutputDev, processLink(mockLink))
        .Times(1);
}