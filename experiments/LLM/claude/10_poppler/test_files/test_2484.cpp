#include <gtest/gtest.h>
#include <glib.h>

extern "C" {
#include "poppler.h"
}

class PopplerLinkMappingCopyTest_2484 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerLinkMappingCopyTest_2484, CopyWithNullAction_2484)
{
    PopplerLinkMapping mapping;
    memset(&mapping, 0, sizeof(PopplerLinkMapping));
    mapping.area.x1 = 10.0;
    mapping.area.y1 = 20.0;
    mapping.area.x2 = 30.0;
    mapping.area.y2 = 40.0;
    mapping.action = nullptr;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(&mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 30.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 40.0);
    EXPECT_EQ(copy->action, nullptr);

    poppler_link_mapping_free(copy);
}

TEST_F(PopplerLinkMappingCopyTest_2484, CopiedMappingIsDifferentPointer_2484)
{
    PopplerLinkMapping mapping;
    memset(&mapping, 0, sizeof(PopplerLinkMapping));
    mapping.area.x1 = 1.0;
    mapping.area.y1 = 2.0;
    mapping.area.x2 = 3.0;
    mapping.area.y2 = 4.0;
    mapping.action = nullptr;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(&mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, &mapping);

    poppler_link_mapping_free(copy);
}

TEST_F(PopplerLinkMappingCopyTest_2484, CopyPreservesAreaCoordinates_2484)
{
    PopplerLinkMapping mapping;
    memset(&mapping, 0, sizeof(PopplerLinkMapping));
    mapping.area.x1 = -100.5;
    mapping.area.y1 = 0.0;
    mapping.area.x2 = 999.999;
    mapping.area.y2 = -0.001;
    mapping.action = nullptr;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(&mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, -100.5);
    EXPECT_DOUBLE_EQ(copy->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 999.999);
    EXPECT_DOUBLE_EQ(copy->area.y2, -0.001);

    poppler_link_mapping_free(copy);
}

TEST_F(PopplerLinkMappingCopyTest_2484, CopyZeroArea_2484)
{
    PopplerLinkMapping mapping;
    memset(&mapping, 0, sizeof(PopplerLinkMapping));
    mapping.area.x1 = 0.0;
    mapping.area.y1 = 0.0;
    mapping.area.x2 = 0.0;
    mapping.area.y2 = 0.0;
    mapping.action = nullptr;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(&mapping);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 0.0);
    EXPECT_EQ(copy->action, nullptr);

    poppler_link_mapping_free(copy);
}

TEST_F(PopplerLinkMappingCopyTest_2484, CopyNewAndFreeAreSymmetric_2484)
{
    PopplerLinkMapping *mapping = poppler_link_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 5.0;
    mapping->area.y1 = 10.0;
    mapping->area.x2 = 15.0;
    mapping->area.y2 = 20.0;
    mapping->action = nullptr;

    PopplerLinkMapping *copy = poppler_link_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, mapping);

    EXPECT_DOUBLE_EQ(copy->area.x1, 5.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 15.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 20.0);

    poppler_link_mapping_free(copy);
    poppler_link_mapping_free(mapping);
}
