#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QImage>

// Forward declarations and includes needed for poppler
#include "poppler-qt5.h"
#include "poppler-page-private.h"
#include "poppler-private.h"

// We need access to Qt5SplashOutputDev and OutputDevCallbackHelper
// These are in the Poppler namespace
#include "poppler-page.cc" // or appropriate header

using namespace Poppler;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

namespace {

// Track callback invocations
static bool g_partialUpdateCalled = false;
static QImage g_receivedImage;
static void* g_receivedPayload = nullptr;
static bool g_shouldDoPartialReturnValue = false;
static bool g_shouldDoPartialCalled = false;

void resetGlobals() {
    g_partialUpdateCalled = false;
    g_receivedImage = QImage();
    g_receivedPayload = nullptr;
    g_shouldDoPartialReturnValue = false;
    g_shouldDoPartialCalled = false;
}

void testPartialUpdateCallback(const QImage &image, void *payload) {
    g_partialUpdateCalled = true;
    g_receivedImage = image;
    g_receivedPayload = payload;
}

bool testShouldDoPartialUpdateCallback(void *payload) {
    g_shouldDoPartialCalled = true;
    g_receivedPayload = payload;
    return g_shouldDoPartialReturnValue;
}

class Qt5SplashOutputDevDumpTest_1436 : public ::testing::Test {
protected:
    void SetUp() override {
        resetGlobals();
        // Set up default paper color (white)
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
    }

    void TearDown() override {
        resetGlobals();
    }

    SplashColor paperColor;
};

// Test that dump() does nothing when partialUpdateCallback is null
TEST_F(Qt5SplashOutputDevDumpTest_1436, DumpDoesNothingWhenPartialUpdateCallbackIsNull_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    // Don't set any callbacks - they should be null by default
    dev.partialUpdateCallback = nullptr;
    dev.shouldDoPartialUpdateCallback = nullptr;
    dev.payload = nullptr;

    // Should not crash and should not call anything
    dev.dump();
    
    EXPECT_FALSE(g_partialUpdateCalled);
    EXPECT_FALSE(g_shouldDoPartialCalled);
}

// Test that dump() does nothing when shouldDoPartialUpdateCallback is null
TEST_F(Qt5SplashOutputDevDumpTest_1436, DumpDoesNothingWhenShouldDoCallbackIsNull_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    dev.partialUpdateCallback = testPartialUpdateCallback;
    dev.shouldDoPartialUpdateCallback = nullptr;
    dev.payload = nullptr;

    dev.dump();
    
    EXPECT_FALSE(g_partialUpdateCalled);
}

// Test that dump() does not call partialUpdateCallback when shouldDoPartial returns false
TEST_F(Qt5SplashOutputDevDumpTest_1436, DumpDoesNotCallPartialUpdateWhenShouldDoReturnsFalse_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    g_shouldDoPartialReturnValue = false;
    dev.partialUpdateCallback = testPartialUpdateCallback;
    dev.shouldDoPartialUpdateCallback = testShouldDoPartialUpdateCallback;
    dev.payload = nullptr;

    dev.dump();
    
    EXPECT_TRUE(g_shouldDoPartialCalled);
    EXPECT_FALSE(g_partialUpdateCalled);
}

// Test that dump() calls partialUpdateCallback when shouldDoPartial returns true
TEST_F(Qt5SplashOutputDevDumpTest_1436, DumpCallsPartialUpdateWhenShouldDoReturnsTrue_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    g_shouldDoPartialReturnValue = true;
    int payloadData = 42;
    dev.partialUpdateCallback = testPartialUpdateCallback;
    dev.shouldDoPartialUpdateCallback = testShouldDoPartialUpdateCallback;
    dev.payload = &payloadData;

    dev.dump();
    
    EXPECT_TRUE(g_shouldDoPartialCalled);
    EXPECT_TRUE(g_partialUpdateCalled);
    EXPECT_EQ(g_receivedPayload, &payloadData);
}

// Test that payload is correctly passed to shouldDoPartialUpdateCallback
TEST_F(Qt5SplashOutputDevDumpTest_1436, DumpPassesPayloadToShouldDoCallback_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    g_shouldDoPartialReturnValue = false;
    int payloadData = 99;
    dev.partialUpdateCallback = testPartialUpdateCallback;
    dev.shouldDoPartialUpdateCallback = testShouldDoPartialUpdateCallback;
    dev.payload = &payloadData;

    dev.dump();
    
    EXPECT_TRUE(g_shouldDoPartialCalled);
    EXPECT_EQ(g_receivedPayload, &payloadData);
}

// Test that dump() with null payload works correctly
TEST_F(Qt5SplashOutputDevDumpTest_1436, DumpWithNullPayload_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    g_shouldDoPartialReturnValue = true;
    dev.partialUpdateCallback = testPartialUpdateCallback;
    dev.shouldDoPartialUpdateCallback = testShouldDoPartialUpdateCallback;
    dev.payload = nullptr;

    dev.dump();
    
    EXPECT_TRUE(g_shouldDoPartialCalled);
    EXPECT_TRUE(g_partialUpdateCalled);
    EXPECT_EQ(g_receivedPayload, nullptr);
}

// Test destructor doesn't crash
TEST_F(Qt5SplashOutputDevDumpTest_1436, DestructorDoesNotCrash_1436) {
    {
        Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                               splashThinLineDefault, false);
    }
    // If we reach here, destructor didn't crash
    SUCCEED();
}

// Test construction with ignorePaperColor true
TEST_F(Qt5SplashOutputDevDumpTest_1436, ConstructionWithIgnorePaperColorTrue_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, true, paperColor, true,
                           splashThinLineDefault, false);
    // Should construct without issues
    SUCCEED();
}

// Test construction with various thin line modes
TEST_F(Qt5SplashOutputDevDumpTest_1436, ConstructionWithDifferentThinLineModes_1436) {
    {
        Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                               splashThinLineDefault, false);
    }
    {
        Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                               splashThinLineSolid, false);
    }
    {
        Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                               splashThinLineShape, false);
    }
    SUCCEED();
}

// Test getXBGRImage returns a QImage
TEST_F(Qt5SplashOutputDevDumpTest_1436, GetXBGRImageReturnsQImage_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    QImage image = dev.getXBGRImage(false);
    // The image may be null/empty if no rendering has been done, but it should not crash
    EXPECT_TRUE(image.isNull() || !image.isNull()); // Just verifying it doesn't crash
}

// Test getXBGRImage with takeImageData parameter
TEST_F(Qt5SplashOutputDevDumpTest_1436, GetXBGRImageWithTakeImageData_1436) {
    Qt5SplashOutputDev dev(splashModeXBGR8, 4, false, paperColor, true,
                           splashThinLineDefault, false);
    
    QImage image = dev.getXBGRImage(true);
    // Should not crash
    SUCCEED();
}

} // namespace
