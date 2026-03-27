#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Partial code to be tested
static const char *determineFallbackFont(const std::string &tok, const char *defaultFallback) { 
    if (tok == "/ZaDb") { 
        return "ZapfDingbats"; 
    } 
    if (tok == "/Cour") { 
        return "Courier"; 
    } 
    if (tok == "/TiRo") { 
        return "TimesNewRoman"; 
    } 
    if (tok == "/Helvetica-Bold") { 
        return "Helvetica-Bold"; 
    } 
    return defaultFallback; 
}

// Test Fixture Class for TEST_ID 2021
class DetermineFallbackFontTest_2021 : public ::testing::Test {
protected:
    // Setup code if necessary (not required in this case)
    void SetUp() override {
        // Can initialize any common setup here
    }

    // TearDown code if necessary (not required in this case)
    void TearDown() override {
        // Clean up any resources if necessary
    }
};

// Test Case 1: Normal operation with a valid font token
TEST_F(DetermineFallbackFontTest_2021, ValidFontToken_2021) {
    const char* result = determineFallbackFont("/ZaDb", "DefaultFont");
    EXPECT_STREQ(result, "ZapfDingbats");

    result = determineFallbackFont("/Cour", "DefaultFont");
    EXPECT_STREQ(result, "Courier");

    result = determineFallbackFont("/TiRo", "DefaultFont");
    EXPECT_STREQ(result, "TimesNewRoman");

    result = determineFallbackFont("/Helvetica-Bold", "DefaultFont");
    EXPECT_STREQ(result, "Helvetica-Bold");
}

// Test Case 2: Boundary condition with a token that does not match any of the predefined ones
TEST_F(DetermineFallbackFontTest_2021, DefaultFallback_2021) {
    const char* result = determineFallbackFont("/NonExistent", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test Case 3: Exceptional case, passing an empty string as token
TEST_F(DetermineFallbackFontTest_2021, EmptyToken_2021) {
    const char* result = determineFallbackFont("", "DefaultFont");
    EXPECT_STREQ(result, "DefaultFont");
}

// Test Case 4: Exceptional case, passing a null default fallback value
TEST_F(DetermineFallbackFontTest_2021, NullFallback_2021) {
    const char* result = determineFallbackFont("/ZaDb", nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test Case 5: Verification of external interaction (mock example)
TEST_F(DetermineFallbackFontTest_2021, MockHandlerCall_2021) {
    // This test doesn't directly apply to the function provided, as it doesn't involve external dependencies
    // But if it did, we would verify external calls here using Google Mock.
}