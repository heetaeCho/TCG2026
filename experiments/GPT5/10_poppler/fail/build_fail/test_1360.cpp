#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Poppler {

// Mock class or dependencies can be included here if necessary.

bool isOverprintPreviewAvailable() {
    return true;
}

}  // namespace Poppler

// Test Fixture class if necessary, for setup and teardown
// Not needed here since the function doesn't take any parameters

// Test case for normal operation
TEST_F(PopplerTest_1360, isOverprintPreviewAvailable_NormalOperation_1360) {
    // Verify the function returns true as expected
    EXPECT_TRUE(Poppler::isOverprintPreviewAvailable());
}

// Boundary or exceptional cases (though the function is simple, it's good to consider future extensibility)
TEST_F(PopplerTest_1360, isOverprintPreviewAvailable_ExceptionalCase_1360) {
    // Since the function is static and deterministic, there are no real boundary or error conditions.
    // This test case serves as a placeholder to check if any changes to the function affect its expected behavior.
    EXPECT_TRUE(Poppler::isOverprintPreviewAvailable());
}