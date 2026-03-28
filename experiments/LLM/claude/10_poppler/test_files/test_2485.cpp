#include <gtest/gtest.h>
#include <glib.h>

extern "C" {
#include "poppler.h"
}

class PopplerLinkMappingTest_2485 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_link_mapping_free handles NULL gracefully (no crash)
TEST_F(PopplerLinkMappingTest_2485, FreeNullMapping_2485)
{
    // Should not crash or cause any issues when passed NULL
    poppler_link_mapping_free(nullptr);
}

// Test that poppler_link_mapping_free works with a newly created mapping
TEST_F(PopplerLinkMappingTest_2485, FreeNewlyCreatedMapping_2485)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);
    // The new mapping should have action as NULL by default
    // Free should work without crash
    poppler_link_mapping_free(mapping);
}

// Test that poppler_link_mapping_new returns a valid mapping
TEST_F(PopplerLinkMappingTest_2485, NewMappingIsValid_2485)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);
    // New mapping should have action initialized to NULL
    EXPECT_EQ(mapping->action, nullptr);
    poppler_link_mapping_free(mapping);
}

// Test that poppler_link_mapping_copy creates a proper copy
TEST_F(PopplerLinkMappingTest_2485, CopyMappingWithNullAction_2485)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);
    mapping->area.x1 = 10.0;
    mapping->area.y1 = 20.0;
    mapping->area.x2 = 30.0;
    mapping->area.y2 = 40.0;
    mapping->action = nullptr;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 30.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 40.0);
    EXPECT_EQ(copy->action, nullptr);

    poppler_link_mapping_free(mapping);
    poppler_link_mapping_free(copy);
}

// Test that poppler_link_mapping_free handles mapping with null action
TEST_F(PopplerLinkMappingTest_2485, FreeMappingWithNullAction_2485)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);
    mapping->action = nullptr;
    // Should not crash when action is NULL
    poppler_link_mapping_free(mapping);
}

// Test copy of NULL returns NULL
TEST_F(PopplerLinkMappingTest_2485, CopyNullReturnsNull_2485)
{
    PopplerLinkMapping *copy = poppler_link_mapping_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test area values are preserved after creation
TEST_F(PopplerLinkMappingTest_2485, AreaValuesPreserved_2485)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 0.0;
    mapping->area.y1 = 0.0;
    mapping->area.x2 = 100.0;
    mapping->area.y2 = 200.0;

    EXPECT_DOUBLE_EQ(mapping->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 100.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 200.0);

    poppler_link_mapping_free(mapping);
}

// Test boundary: area with negative coordinates
TEST_F(PopplerLinkMappingTest_2485, AreaWithNegativeCoordinates_2485)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = -50.0;
    mapping->area.y1 = -100.0;
    mapping->area.x2 = -10.0;
    mapping->area.y2 = -20.0;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, -50.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, -100.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, -10.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, -20.0);

    poppler_link_mapping_free(mapping);
    poppler_link_mapping_free(copy);
}

// Test boundary: area with zero-size rectangle
TEST_F(PopplerLinkMappingTest_2485, AreaWithZeroSize_2485)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 5.0;
    mapping->area.y1 = 5.0;
    mapping->area.x2 = 5.0;
    mapping->area.y2 = 5.0;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, copy->area.x2);
    EXPECT_DOUBLE_EQ(copy->area.y1, copy->area.y2);

    poppler_link_mapping_free(mapping);
    poppler_link_mapping_free(copy);
}
