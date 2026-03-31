#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declare and include necessary headers
#include "TextOutputDev.h"

// Since TextLink is defined in TextOutputDev.cc and may not be directly accessible
// via the header, we need to work with what's available. Based on the provided code,
// TextLink is a simple class that stores coordinates and an AnnotLink pointer.

// We'll test the TextLink class based on its public interface.

class TextLinkTest_2788 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with valid parameters and nullptr link
TEST_F(TextLinkTest_2788, ConstructWithNullLink_2788)
{
    // TextLink should be constructible with nullptr for the AnnotLink pointer
    EXPECT_NO_THROW({
        TextLink link(0, 0, 100, 200, nullptr);
    });
}

// Test: Construction with zero-sized bounding box
TEST_F(TextLinkTest_2788, ConstructWithZeroSizeBoundingBox_2788)
{
    EXPECT_NO_THROW({
        TextLink link(0, 0, 0, 0, nullptr);
    });
}

// Test: Construction with negative coordinates
TEST_F(TextLinkTest_2788, ConstructWithNegativeCoordinates_2788)
{
    EXPECT_NO_THROW({
        TextLink link(-100, -200, -50, -25, nullptr);
    });
}

// Test: Construction with large coordinate values
TEST_F(TextLinkTest_2788, ConstructWithLargeCoordinates_2788)
{
    EXPECT_NO_THROW({
        TextLink link(INT_MAX, INT_MAX, INT_MAX, INT_MAX, nullptr);
    });
}

// Test: Construction with minimum integer values
TEST_F(TextLinkTest_2788, ConstructWithMinIntCoordinates_2788)
{
    EXPECT_NO_THROW({
        TextLink link(INT_MIN, INT_MIN, INT_MIN, INT_MIN, nullptr);
    });
}

// Test: Construction with inverted bounding box (xMin > xMax, yMin > yMax)
TEST_F(TextLinkTest_2788, ConstructWithInvertedBoundingBox_2788)
{
    EXPECT_NO_THROW({
        TextLink link(200, 300, 100, 50, nullptr);
    });
}

// Test: Construction with typical page coordinates
TEST_F(TextLinkTest_2788, ConstructWithTypicalCoordinates_2788)
{
    EXPECT_NO_THROW({
        TextLink link(72, 144, 500, 160, nullptr);
    });
}

// Test: Multiple TextLink instances can be created independently
TEST_F(TextLinkTest_2788, MultipleInstancesIndependent_2788)
{
    EXPECT_NO_THROW({
        TextLink link1(0, 0, 100, 100, nullptr);
        TextLink link2(50, 50, 200, 200, nullptr);
        TextLink link3(10, 20, 30, 40, nullptr);
    });
}

// Test: Default destructor works correctly
TEST_F(TextLinkTest_2788, DestructorDoesNotCrash_2788)
{
    EXPECT_NO_THROW({
        TextLink* link = new TextLink(10, 20, 30, 40, nullptr);
        delete link;
    });
}

// Test: Construction with mixed positive and negative coordinates
TEST_F(TextLinkTest_2788, ConstructWithMixedCoordinates_2788)
{
    EXPECT_NO_THROW({
        TextLink link(-50, -100, 50, 100, nullptr);
    });
}
