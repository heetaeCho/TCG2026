#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// A concrete subclass for testing, since OutputDev has virtual methods
class TestOutputDev : public OutputDev
{
};

class OutputDevTest_1065 : public ::testing::Test
{
protected:
    TestOutputDev dev;
};

// Test that checkPageSlice returns true with all default parameters
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_DefaultParams_1065)
{
    bool result = dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test that checkPageSlice returns true with nullptr callbacks explicitly passed
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_NullCallbacks_1065)
{
    bool result = dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false, nullptr, nullptr, nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test with various DPI values
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_VariousDPI_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 300.0, 300.0, 0, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 1.0, 1.0, 0, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 0.0, 0.0, 0, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 1200.0, 1200.0, 0, false, false, 0, 0, 100, 100, false));
}

// Test with different rotation values
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_VariousRotation_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 90, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 180, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 270, false, false, 0, 0, 100, 100, false));
}

// Test with useMediaBox true
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_UseMediaBox_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, true, false, 0, 0, 100, 100, false));
}

// Test with crop true
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_Crop_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, true, 0, 0, 100, 100, false));
}

// Test with printing true
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_Printing_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, true));
}

// Test with zero-sized slice
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_ZeroSlice_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 0, 0, false));
}

// Test with negative slice coordinates
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_NegativeSlice_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, -10, -10, 100, 100, false));
}

// Test with large slice dimensions
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_LargeSlice_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100000, 100000, false));
}

// Test with a non-null abort callback (should still return true from base implementation)
static bool dummyAbortCheck(void *data)
{
    return false;
}

TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_WithAbortCallback_1065)
{
    int userData = 42;
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false, dummyAbortCheck, &userData));
}

// Test with a non-null annot display decide callback
static bool dummyAnnotDecide(Annot *annot, void *user_data)
{
    return true;
}

TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_WithAnnotCallback_1065)
{
    int userData = 99;
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false, nullptr, nullptr, dummyAnnotDecide, &userData));
}

// Test with all boolean parameters set to true
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_AllBoolsTrue_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, true, true, 0, 0, 100, 100, true));
}

// Test with both callbacks provided
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_BothCallbacks_1065)
{
    int abortData = 1;
    int annotData = 2;
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 90, true, true, 10, 20, 640, 480, true, dummyAbortCheck, &abortData, dummyAnnotDecide, &annotData));
}

// Test with negative DPI values (boundary)
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_NegativeDPI_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, -72.0, -72.0, 0, false, false, 0, 0, 100, 100, false));
}

// Test with very large DPI values
TEST_F(OutputDevTest_1065, CheckPageSliceReturnsTrue_VeryLargeDPI_1065)
{
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 1e10, 1e10, 0, false, false, 0, 0, 100, 100, false));
}

// Test that the base class can be used through a pointer (polymorphism)
TEST_F(OutputDevTest_1065, CheckPageSliceViaBasePointer_1065)
{
    OutputDev *basePtr = &dev;
    EXPECT_TRUE(basePtr->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}

// Test a derived class that overrides checkPageSlice
class OverridingOutputDev : public OutputDev
{
public:
    bool checkPageSlice(Page *page, double hDPI, double vDPI, int rotate, bool useMediaBox, bool crop, int sliceX, int sliceY, int sliceW, int sliceH, bool printing,
                        bool (*abortCheckCbk)(void *data) = nullptr, void *abortCheckCbkData = nullptr, bool (*annotDisplayDecideCbk)(Annot *annot, void *user_data) = nullptr,
                        void *annotDisplayDecideCbkData = nullptr) override
    {
        return false;
    }
};

TEST_F(OutputDevTest_1065, OverriddenCheckPageSliceReturnsFalse_1065)
{
    OverridingOutputDev overriding;
    OutputDev *basePtr = &overriding;
    EXPECT_FALSE(basePtr->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}
