#include <gtest/gtest.h>
#include "poppler-form.h"  // Include the appropriate header for Poppler

// Mock class for external interactions, if needed (not used in this case).
// You can add Google Mock if there are other collaborators to mock.

namespace Poppler {
    // Mocked function for demonstration, the actual `hasNSSSupport` is being tested.
    bool hasNSSSupport();
}

TEST_F(PopplerTest_1370, HasNSSSupport_ReturnsTrue_WhenEnabled_1370) {
    // Assuming the build is configured with ENABLE_NSS3
    #if ENABLE_NSS3
    EXPECT_TRUE(Poppler::hasNSSSupport());
    #else
    GTEST_SKIP() << "Test skipped because ENABLE_NSS3 is not enabled.";
    #endif
}

TEST_F(PopplerTest_1370, HasNSSSupport_ReturnsFalse_WhenDisabled_1370) {
    // Assuming the build is configured without ENABLE_NSS3
    #if !ENABLE_NSS3
    EXPECT_FALSE(Poppler::hasNSSSupport());
    #else
    GTEST_SKIP() << "Test skipped because ENABLE_NSS3 is enabled.";
    #endif
}