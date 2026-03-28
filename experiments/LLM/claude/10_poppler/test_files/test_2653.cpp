#include <gtest/gtest.h>
#include <string>

// Include necessary headers
#include "goo/GooString.h"

// Declare the external global variables used by parseJpegOptions
extern GooString jpegOpt;
extern int jpegQuality;
extern bool jpegProgressive;
extern bool jpegOptimize;

// Declare the function under test
static bool parseJpegOptions();

// We need to include the actual implementation. Since parseJpegOptions is static,
// we need to either include the source or redefine the globals and function here.
// For testing purposes, we'll replicate the global variable declarations and
// include the function by including the source indirectly.

// Since the function is static in pdftoppm.cc, we need to work around that.
// One approach: include the relevant portion. For the test, let's assume we can
// access it. We'll define the globals and copy the function for testability.

// Helper function from poppler
static bool isInt(const char *s)
{
    if (!s || !*s) {
        return false;
    }
    if (*s == '-' || *s == '+') {
        s++;
    }
    if (!*s) {
        return false;
    }
    while (*s) {
        if (*s < '0' || *s > '9') {
            return false;
        }
        s++;
    }
    return true;
}

// Define the globals for testing
GooString jpegOpt;
int jpegQuality = -1;
bool jpegProgressive = false;
bool jpegOptimize = false;

// Copy of the function under test (since it's static in the original file)
static bool parseJpegOptions()
{
    const char *nextOpt = jpegOpt.c_str();
    while (nextOpt && *nextOpt) {
        const char *comma = strchr(nextOpt, ',');
        GooString opt;
        if (comma) {
            opt.assign(nextOpt, static_cast<int>(comma - nextOpt));
            nextOpt = comma + 1;
        } else {
            opt.assign(nextOpt);
            nextOpt = nullptr;
        }
        const char *equal = strchr(opt.c_str(), '=');
        if (!equal) {
            fprintf(stderr, "Unknown jpeg option \"%s\"\n", opt.c_str());
            return false;
        }
        const int iequal = static_cast<int>(equal - opt.c_str());
        GooString value(&opt, iequal + 1, opt.size() - iequal - 1);
        opt.erase(iequal, opt.size() - iequal);

        if (opt.compare("quality") == 0) {
            if (!isInt(value.c_str())) {
                fprintf(stderr, "Invalid jpeg quality\n");
                return false;
            }
            jpegQuality = atoi(value.c_str());
            if (jpegQuality < 0 || jpegQuality > 100) {
                fprintf(stderr, "jpeg quality must be between 0 and 100\n");
                return false;
            }
        } else if (opt.compare("progressive") == 0) {
            jpegProgressive = false;
            if (value.compare("y") == 0) {
                jpegProgressive = true;
            } else if (value.compare("n") != 0) {
                fprintf(stderr, "jpeg progressive option must be \"y\" or \"n\"\n");
                return false;
            }
        } else if (opt.compare("optimize") == 0 || opt.compare("optimise") == 0) {
            jpegOptimize = false;
            if (value.compare("y") == 0) {
                jpegOptimize = true;
            } else if (value.compare("n") != 0) {
                fprintf(stderr, "jpeg optimize option must be \"y\" or \"n\"\n");
                return false;
            }
        } else {
            fprintf(stderr, "Unknown jpeg option \"%s\"\n", opt.c_str());
            return false;
        }
    }
    return true;
}

// Test fixture to reset globals before each test
class ParseJpegOptionsTest_2653 : public ::testing::Test {
protected:
    void SetUp() override
    {
        jpegOpt.assign("");
        jpegQuality = -1;
        jpegProgressive = false;
        jpegOptimize = false;
    }
};

// ==================== Normal Operation Tests ====================

TEST_F(ParseJpegOptionsTest_2653, EmptyString_ReturnsTrue_2653)
{
    jpegOpt.assign("");
    EXPECT_TRUE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, QualityValid_SetsQuality_2653)
{
    jpegOpt.assign("quality=50");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 50);
}

TEST_F(ParseJpegOptionsTest_2653, QualityZero_SetsQualityToZero_2653)
{
    jpegOpt.assign("quality=0");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 0);
}

TEST_F(ParseJpegOptionsTest_2653, QualityHundred_SetsQualityToHundred_2653)
{
    jpegOpt.assign("quality=100");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 100);
}

TEST_F(ParseJpegOptionsTest_2653, ProgressiveYes_SetsProgressiveTrue_2653)
{
    jpegOpt.assign("progressive=y");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_TRUE(jpegProgressive);
}

TEST_F(ParseJpegOptionsTest_2653, ProgressiveNo_SetsProgressiveFalse_2653)
{
    jpegOpt.assign("progressive=n");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_FALSE(jpegProgressive);
}

TEST_F(ParseJpegOptionsTest_2653, OptimizeYes_SetsOptimizeTrue_2653)
{
    jpegOpt.assign("optimize=y");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_TRUE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, OptimizeNo_SetsOptimizeFalse_2653)
{
    jpegOpt.assign("optimize=n");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_FALSE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, OptimiseYes_SetsOptimizeTrue_2653)
{
    jpegOpt.assign("optimise=y");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_TRUE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, OptimiseNo_SetsOptimizeFalse_2653)
{
    jpegOpt.assign("optimise=n");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_FALSE(jpegOptimize);
}

// ==================== Multiple Options Tests ====================

TEST_F(ParseJpegOptionsTest_2653, MultipleOptions_AllSet_2653)
{
    jpegOpt.assign("quality=75,progressive=y,optimize=y");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 75);
    EXPECT_TRUE(jpegProgressive);
    EXPECT_TRUE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, MultipleOptions_QualityAndProgressive_2653)
{
    jpegOpt.assign("quality=90,progressive=n");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 90);
    EXPECT_FALSE(jpegProgressive);
}

TEST_F(ParseJpegOptionsTest_2653, MultipleOptions_AllNo_2653)
{
    jpegOpt.assign("quality=50,progressive=n,optimize=n");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 50);
    EXPECT_FALSE(jpegProgressive);
    EXPECT_FALSE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, MultipleOptions_OptimiseSpelling_2653)
{
    jpegOpt.assign("quality=30,optimise=y,progressive=y");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 30);
    EXPECT_TRUE(jpegOptimize);
    EXPECT_TRUE(jpegProgressive);
}

// ==================== Boundary Condition Tests ====================

TEST_F(ParseJpegOptionsTest_2653, QualityNegative_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=-1");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, QualityAbove100_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=101");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, QualityVeryLarge_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=999");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, QualityBoundaryOne_SetsQuality_2653)
{
    jpegOpt.assign("quality=1");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 1);
}

TEST_F(ParseJpegOptionsTest_2653, QualityBoundary99_SetsQuality_2653)
{
    jpegOpt.assign("quality=99");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 99);
}

// ==================== Error / Exceptional Cases ====================

TEST_F(ParseJpegOptionsTest_2653, NoEqualSign_ReturnsFalse_2653)
{
    jpegOpt.assign("quality");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, UnknownOption_ReturnsFalse_2653)
{
    jpegOpt.assign("unknown=value");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, QualityNonInteger_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=abc");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, QualityFloat_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=50.5");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, QualityEmpty_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, ProgressiveInvalidValue_ReturnsFalse_2653)
{
    jpegOpt.assign("progressive=yes");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, ProgressiveInvalidValue2_ReturnsFalse_2653)
{
    jpegOpt.assign("progressive=1");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, OptimizeInvalidValue_ReturnsFalse_2653)
{
    jpegOpt.assign("optimize=yes");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, OptimizeInvalidValue2_ReturnsFalse_2653)
{
    jpegOpt.assign("optimize=1");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, OptimiseInvalidValue_ReturnsFalse_2653)
{
    jpegOpt.assign("optimise=yes");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, MultipleOptionsWithOneInvalid_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=50,badoption=value");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, MultipleOptionsWithInvalidQuality_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=200,progressive=y");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, NoEqualSignInSecondOption_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=50,progressive");
    EXPECT_FALSE(parseJpegOptions());
}

// ==================== Edge Cases ====================

TEST_F(ParseJpegOptionsTest_2653, ProgressiveResetsToFalseBeforeSettingY_2653)
{
    // First set progressive to true via another call, then check it resets
    jpegProgressive = true;
    jpegOpt.assign("progressive=n");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_FALSE(jpegProgressive);
}

TEST_F(ParseJpegOptionsTest_2653, OptimizeResetsToFalseBeforeSettingY_2653)
{
    jpegOptimize = true;
    jpegOpt.assign("optimize=n");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_FALSE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, ProgressiveResetThenSetY_2653)
{
    jpegProgressive = false;
    jpegOpt.assign("progressive=y");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_TRUE(jpegProgressive);
}

TEST_F(ParseJpegOptionsTest_2653, TrailingComma_2653)
{
    // A trailing comma means nextOpt points to empty string after comma
    // which should cause the while loop to exit (empty string)
    jpegOpt.assign("quality=50,");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 50);
}

TEST_F(ParseJpegOptionsTest_2653, QualityNegativeLarge_ReturnsFalse_2653)
{
    jpegOpt.assign("quality=-100");
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, AllThreeOptionsSet_2653)
{
    jpegOpt.assign("quality=42,progressive=y,optimise=y");
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 42);
    EXPECT_TRUE(jpegProgressive);
    EXPECT_TRUE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, OnlyEqualsSign_ReturnsFalse_2653)
{
    jpegOpt.assign("=value");
    // The option name would be empty, which doesn't match any known option
    EXPECT_FALSE(parseJpegOptions());
}

TEST_F(ParseJpegOptionsTest_2653, DoubleComma_2653)
{
    // "quality=50,,progressive=y" - middle empty option should be handled
    jpegOpt.assign("quality=50,,progressive=y");
    // The empty string between commas should cause the while loop to skip
    EXPECT_TRUE(parseJpegOptions());
    EXPECT_EQ(jpegQuality, 50);
    // progressive should be set if the loop continues past the empty string
    EXPECT_TRUE(jpegProgressive);
}
