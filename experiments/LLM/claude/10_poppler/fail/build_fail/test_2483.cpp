#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Forward declarations for poppler types
typedef struct _PopplerLinkMapping PopplerLinkMapping;
typedef struct _PopplerRectangle PopplerRectangle;
typedef struct _PopplerAction PopplerAction;

struct _PopplerRectangle
{
    double x1;
    double y1;
    double x2;
    double y2;
};

struct _PopplerLinkMapping
{
    PopplerRectangle area;
    PopplerAction *action;
};

// Declaration of the function under test
PopplerLinkMapping *poppler_link_mapping_new(void);
}

class PopplerLinkMappingTest_2483 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up allocated mappings
        for (auto *mapping : allocated_mappings_) {
            if (mapping) {
                g_slice_free(PopplerLinkMapping, mapping);
            }
        }
        allocated_mappings_.clear();
    }

    PopplerLinkMapping *createAndTrack() {
        PopplerLinkMapping *mapping = poppler_link_mapping_new();
        if (mapping) {
            allocated_mappings_.push_back(mapping);
        }
        return mapping;
    }

    std::vector<PopplerLinkMapping *> allocated_mappings_;
};

TEST_F(PopplerLinkMappingTest_2483, ReturnsNonNull_2483) {
    PopplerLinkMapping *mapping = createAndTrack();
    ASSERT_NE(mapping, nullptr);
}

TEST_F(PopplerLinkMappingTest_2483, FieldsAreZeroInitialized_2483) {
    PopplerLinkMapping *mapping = createAndTrack();
    ASSERT_NE(mapping, nullptr);

    // g_slice_new0 zero-initializes the memory, so all fields should be 0
    EXPECT_DOUBLE_EQ(mapping->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 0.0);
    EXPECT_EQ(mapping->action, nullptr);
}

TEST_F(PopplerLinkMappingTest_2483, MultipleAllocationsReturnDistinctPointers_2483) {
    PopplerLinkMapping *mapping1 = createAndTrack();
    PopplerLinkMapping *mapping2 = createAndTrack();
    ASSERT_NE(mapping1, nullptr);
    ASSERT_NE(mapping2, nullptr);
    EXPECT_NE(mapping1, mapping2);
}

TEST_F(PopplerLinkMappingTest_2483, EachAllocationIsIndependentlyZeroInitialized_2483) {
    PopplerLinkMapping *mapping1 = createAndTrack();
    ASSERT_NE(mapping1, nullptr);

    // Modify first mapping
    mapping1->area.x1 = 10.0;
    mapping1->area.y1 = 20.0;
    mapping1->area.x2 = 30.0;
    mapping1->area.y2 = 40.0;

    // Allocate a second mapping
    PopplerLinkMapping *mapping2 = createAndTrack();
    ASSERT_NE(mapping2, nullptr);

    // Second mapping should still be zero-initialized
    EXPECT_DOUBLE_EQ(mapping2->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping2->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping2->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(mapping2->area.y2, 0.0);
    EXPECT_EQ(mapping2->action, nullptr);
}

TEST_F(PopplerLinkMappingTest_2483, ActionPointerIsNull_2483) {
    PopplerLinkMapping *mapping = createAndTrack();
    ASSERT_NE(mapping, nullptr);
    EXPECT_EQ(mapping->action, nullptr);
}

TEST_F(PopplerLinkMappingTest_2483, ManyAllocationsSucceed_2483) {
    const int count = 100;
    std::vector<PopplerLinkMapping *> mappings;
    for (int i = 0; i < count; ++i) {
        PopplerLinkMapping *m = createAndTrack();
        ASSERT_NE(m, nullptr) << "Allocation failed at iteration " << i;
        mappings.push_back(m);
    }

    // Verify all pointers are unique
    std::set<PopplerLinkMapping *> unique_ptrs(mappings.begin(), mappings.end());
    EXPECT_EQ(unique_ptrs.size(), static_cast<size_t>(count));
}

TEST_F(PopplerLinkMappingTest_2483, CanWriteAndReadBackFields_2483) {
    PopplerLinkMapping *mapping = createAndTrack();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 1.5;
    mapping->area.y1 = 2.5;
    mapping->area.x2 = 3.5;
    mapping->area.y2 = 4.5;

    EXPECT_DOUBLE_EQ(mapping->area.x1, 1.5);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 2.5);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 3.5);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 4.5);
}
