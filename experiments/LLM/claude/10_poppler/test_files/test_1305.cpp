#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

// Since PSOutputDev has complex constructors requiring PDFDoc and other dependencies,
// and we're testing the setOverlayCbk method which is fully visible in the header,
// we need to find a way to test it. The method is inline and simply sets member variables.
// However, constructing a full PSOutputDev is very complex. We'll focus on what we can test.

// Helper callback functions for testing
static bool g_callbackInvoked = false;
static PSOutputDev* g_callbackPsOut = nullptr;
static void* g_callbackData = nullptr;

static void testOverlayCallback(PSOutputDev* psOut, void* data) {
    g_callbackInvoked = true;
    g_callbackPsOut = psOut;
    g_callbackData = data;
}

static void anotherOverlayCallback(PSOutputDev* psOut, void* data) {
    int* counter = static_cast<int*>(data);
    if (counter) {
        (*counter)++;
    }
}

// Since we cannot easily construct a PSOutputDev (it requires PDFDoc, etc.),
// we test the setOverlayCbk via the FoFiOutputFunc constructor path or
// we create a minimal test that exercises the inline setter.
// 
// Given the constraints that PSOutputDev requires complex dependencies to construct,
// and setOverlayCbk is an inline method that simply assigns two member variables,
// we'll test via a mock output function constructor if possible, or test the setter
// behavior in terms of what's observable.

// We use a custom output function to capture PS output
static void dummyOutputFunc(void* stream, const char* data, size_t len) {
    // Do nothing - just a placeholder
}

class PSOutputDevOverlayTest_1305 : public ::testing::Test {
protected:
    void SetUp() override {
        g_callbackInvoked = false;
        g_callbackPsOut = nullptr;
        g_callbackData = nullptr;
    }

    void TearDown() override {
    }
};

// Test that setOverlayCbk accepts a valid callback and data pointer
// Since we can't easily construct PSOutputDev, we test the inline method's
// observable behavior through integration if a PSOutputDev can be created.
// For unit testing the inline setter, we verify it compiles and can be called.

// The following tests focus on the setOverlayCbk interface behavior.
// Due to the inability to easily construct PSOutputDev without a full PDF document,
// we'll create tests that at minimum verify the API contract.

// If we can create a PSOutputDev with the FoFiOutputFunc constructor using nullptr doc
// (which will likely fail isOk()), we can still test the setter methods.

class PSOutputDevSetterTest_1305 : public ::testing::Test {
protected:
    void SetUp() override {
        g_callbackInvoked = false;
        g_callbackPsOut = nullptr;
        g_callbackData = nullptr;
    }
};

// Test: setOverlayCbk with valid callback and data
TEST_F(PSOutputDevSetterTest_1305, SetOverlayCbkWithValidCallbackAndData_1305) {
    // We attempt to construct PSOutputDev with FoFiOutputFunc
    // Even if the object fails initialization, the setter should still work
    // as it's a simple member assignment
    std::vector<int> pages;
    
    // Try to create with output function - doc is nullptr so it may not fully init
    // but setOverlayCbk is just an inline setter
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr, 
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
        // If construction fails, we skip
    }
    
    if (dev) {
        int testData = 42;
        dev->setOverlayCbk(testOverlayCallback, &testData);
        // The setter should not crash and should accept the values
        // We can't directly verify private members, but the call should succeed
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test: setOverlayCbk with nullptr callback and nullptr data
TEST_F(PSOutputDevSetterTest_1305, SetOverlayCbkWithNullCallbackAndNullData_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setOverlayCbk(nullptr, nullptr);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test: setOverlayCbk with valid callback but nullptr data
TEST_F(PSOutputDevSetterTest_1305, SetOverlayCbkWithValidCallbackNullData_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setOverlayCbk(testOverlayCallback, nullptr);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test: setOverlayCbk with nullptr callback but valid data
TEST_F(PSOutputDevSetterTest_1305, SetOverlayCbkWithNullCallbackValidData_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        int testData = 99;
        dev->setOverlayCbk(nullptr, &testData);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test: setOverlayCbk can be called multiple times (overwrite)
TEST_F(PSOutputDevSetterTest_1305, SetOverlayCbkCalledMultipleTimes_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        int data1 = 1;
        int data2 = 2;
        
        dev->setOverlayCbk(testOverlayCallback, &data1);
        dev->setOverlayCbk(anotherOverlayCallback, &data2);
        dev->setOverlayCbk(nullptr, nullptr);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test: setUnderlayCbk also works (sibling method)
TEST_F(PSOutputDevSetterTest_1305, SetUnderlayCbkWithValidCallbackAndData_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        int testData = 42;
        dev->setUnderlayCbk(testOverlayCallback, &testData);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test: Boolean setters/getters for embed settings
TEST_F(PSOutputDevSetterTest_1305, SetAndGetEmbedType1_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setEmbedType1(true);
        EXPECT_TRUE(dev->getEmbedType1());
        dev->setEmbedType1(false);
        EXPECT_FALSE(dev->getEmbedType1());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetEmbedTrueType_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setEmbedTrueType(true);
        EXPECT_TRUE(dev->getEmbedTrueType());
        dev->setEmbedTrueType(false);
        EXPECT_FALSE(dev->getEmbedTrueType());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetEmbedCIDPostScript_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setEmbedCIDPostScript(true);
        EXPECT_TRUE(dev->getEmbedCIDPostScript());
        dev->setEmbedCIDPostScript(false);
        EXPECT_FALSE(dev->getEmbedCIDPostScript());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetEmbedCIDTrueType_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setEmbedCIDTrueType(true);
        EXPECT_TRUE(dev->getEmbedCIDTrueType());
        dev->setEmbedCIDTrueType(false);
        EXPECT_FALSE(dev->getEmbedCIDTrueType());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetFontPassthrough_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setFontPassthrough(true);
        EXPECT_TRUE(dev->getFontPassthrough());
        dev->setFontPassthrough(false);
        EXPECT_FALSE(dev->getFontPassthrough());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetOptimizeColorSpace_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setOptimizeColorSpace(true);
        EXPECT_TRUE(dev->getOptimizeColorSpace());
        dev->setOptimizeColorSpace(false);
        EXPECT_FALSE(dev->getOptimizeColorSpace());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetEnableLZW_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setEnableLZW(true);
        EXPECT_TRUE(dev->getEnableLZW());
        dev->setEnableLZW(false);
        EXPECT_FALSE(dev->getEnableLZW());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetEnableFlate_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setEnableFlate(true);
        EXPECT_TRUE(dev->getEnableFlate());
        dev->setEnableFlate(false);
        EXPECT_FALSE(dev->getEnableFlate());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetAndGetPassLevel1CustomColor_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setPassLevel1CustomColor(true);
        EXPECT_TRUE(dev->getPassLevel1CustomColor());
        dev->setPassLevel1CustomColor(false);
        EXPECT_FALSE(dev->getPassLevel1CustomColor());
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test OutputDev interface methods
TEST_F(PSOutputDevSetterTest_1305, UpsideDownReturnsFalse_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        // PSOutputDev typically returns false for upsideDown
        bool result = dev->upsideDown();
        EXPECT_FALSE(result);
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, UseDrawCharReturnsFalse_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        bool result = dev->useDrawChar();
        EXPECT_FALSE(result);
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test display text setter
TEST_F(PSOutputDevSetterTest_1305, SetDisplayText_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setDisplayText(true);
        dev->setDisplayText(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test PSCenter setter
TEST_F(PSOutputDevSetterTest_1305, SetPSCenter_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setPSCenter(true);
        dev->setPSCenter(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test expand/shrink setters
TEST_F(PSOutputDevSetterTest_1305, SetPSExpandSmaller_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setPSExpandSmaller(true);
        dev->setPSExpandSmaller(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetPSShrinkLarger_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setPSShrinkLarger(true);
        dev->setPSShrinkLarger(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test setOffset
TEST_F(PSOutputDevSetterTest_1305, SetOffset_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setOffset(10.0, 20.0);
        dev->setOffset(0.0, 0.0);
        dev->setOffset(-5.0, -10.0);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test setScale
TEST_F(PSOutputDevSetterTest_1305, SetScale_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setScale(1.0, 1.0);
        dev->setScale(2.0, 2.0);
        dev->setScale(0.5, 0.5);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test setRotate
TEST_F(PSOutputDevSetterTest_1305, SetRotate_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setRotate(0);
        dev->setRotate(90);
        dev->setRotate(180);
        dev->setRotate(270);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test setClip
TEST_F(PSOutputDevSetterTest_1305, SetClip_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setClip(0.0, 0.0, 612.0, 792.0);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test setRasterResolution
TEST_F(PSOutputDevSetterTest_1305, SetRasterResolution_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setRasterResolution(300.0);
        dev->setRasterResolution(72.0);
        dev->setRasterResolution(600.0);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test setOverprintPreview
TEST_F(PSOutputDevSetterTest_1305, SetOverprintPreview_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setOverprintPreview(true);
        dev->setOverprintPreview(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test setRasterAntialias
TEST_F(PSOutputDevSetterTest_1305, SetRasterAntialias_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setRasterAntialias(true);
        dev->setRasterAntialias(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test binary/hex setters
TEST_F(PSOutputDevSetterTest_1305, SetUseASCIIHex_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setUseASCIIHex(true);
        dev->setUseASCIIHex(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

TEST_F(PSOutputDevSetterTest_1305, SetUseBinary_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        dev->setUseBinary(true);
        dev->setUseBinary(false);
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}

// Test that both overlay and underlay can be set independently
TEST_F(PSOutputDevSetterTest_1305, SetBothOverlayAndUnderlayCbk_1305) {
    std::vector<int> pages;
    PSOutputDev* dev = nullptr;
    
    try {
        dev = new PSOutputDev(dummyOutputFunc, nullptr, nullptr, nullptr,
                              pages, psModePS, 612, 792, false, false,
                              0, 0, 0, 0, psRasterizeWhenNeeded, true,
                              nullptr, nullptr, psLevel2);
    } catch (...) {
    }
    
    if (dev) {
        int overlayData = 1;
        int underlayData = 2;
        dev->setOverlayCbk(testOverlayCallback, &overlayData);
        dev->setUnderlayCbk(anotherOverlayCallback, &underlayData);
        // Both should be set without interfering with each other
        SUCCEED();
        delete dev;
    } else {
        GTEST_SKIP() << "Cannot construct PSOutputDev without valid PDFDoc";
    }
}
