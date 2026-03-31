#include <gtest/gtest.h>

// Forward declare the function from Poppler namespace
namespace Poppler {
bool isOverprintPreviewAvailable();
}

// Test normal operation: isOverprintPreviewAvailable returns true
TEST(PopplerDocumentTest_1360, IsOverprintPreviewAvailableReturnsTrue_1360)
{
    bool result = Poppler::isOverprintPreviewAvailable();
    EXPECT_TRUE(result);
}

// Test that repeated calls consistently return the same value
TEST(PopplerDocumentTest_1360, IsOverprintPreviewAvailableIsConsistent_1360)
{
    bool result1 = Poppler::isOverprintPreviewAvailable();
    bool result2 = Poppler::isOverprintPreviewAvailable();
    EXPECT_EQ(result1, result2);
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

// Test that the function can be called multiple times without side effects
TEST(PopplerDocumentTest_1360, IsOverprintPreviewAvailableMultipleCalls_1360)
{
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(Poppler::isOverprintPreviewAvailable());
    }
}
