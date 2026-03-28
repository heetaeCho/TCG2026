#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and minimal type definitions needed for testing
// Based on the provided interface and dependencies

struct CairoOutputDev;
struct OptionalContentGroup;

struct _PopplerDocument {
    int parent_instance;
    int initer;
    GList *layers_rbgroups;
    CairoOutputDev *output_dev;
};

typedef struct _PopplerDocument PopplerDocument;

struct Layer {
    char *label;
    OptionalContentGroup *oc;
};

// Declaration of the function under test
extern "C" {
GList *_poppler_document_get_layer_rbgroup(PopplerDocument *document, Layer *layer);
}

class PopplerDocumentLayerRbgroupTest_2241 : public ::testing::Test {
protected:
    PopplerDocument doc;
    Layer layer;

    void SetUp() override {
        memset(&doc, 0, sizeof(doc));
        memset(&layer, 0, sizeof(layer));
        doc.layers_rbgroups = nullptr;
    }

    void TearDown() override {
        // Free the layers_rbgroups list structure
        // Each element in layers_rbgroups is itself a GList
        GList *l = doc.layers_rbgroups;
        while (l) {
            GList *group = (GList *)l->data;
            g_list_free(group);
            l = g_list_next(l);
        }
        g_list_free(doc.layers_rbgroups);
        doc.layers_rbgroups = nullptr;
    }

    // Helper to add a group (GList of OptionalContentGroup pointers) to the rbgroups
    void addGroup(GList *group) {
        doc.layers_rbgroups = g_list_append(doc.layers_rbgroups, group);
    }
};

// Test: When layers_rbgroups is NULL, should return nullptr
TEST_F(PopplerDocumentLayerRbgroupTest_2241, NullRbgroupsReturnsNull_2241) {
    doc.layers_rbgroups = nullptr;
    OptionalContentGroup dummy_oc;
    layer.oc = &dummy_oc;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, nullptr);
}

// Test: When layers_rbgroups is empty list, should return nullptr
TEST_F(PopplerDocumentLayerRbgroupTest_2241, EmptyRbgroupsReturnsNull_2241) {
    // layers_rbgroups is already nullptr from SetUp
    OptionalContentGroup dummy_oc;
    layer.oc = &dummy_oc;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, nullptr);
}

// Test: Layer's oc is found in the first group
TEST_F(PopplerDocumentLayerRbgroupTest_2241, LayerFoundInFirstGroup_2241) {
    OptionalContentGroup oc1, oc2, oc3;

    GList *group1 = nullptr;
    group1 = g_list_append(group1, &oc1);
    group1 = g_list_append(group1, &oc2);
    addGroup(group1);

    GList *group2 = nullptr;
    group2 = g_list_append(group2, &oc3);
    addGroup(group2);

    layer.oc = &oc1;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, group1);
}

// Test: Layer's oc is found in the second group
TEST_F(PopplerDocumentLayerRbgroupTest_2241, LayerFoundInSecondGroup_2241) {
    OptionalContentGroup oc1, oc2, oc3;

    GList *group1 = nullptr;
    group1 = g_list_append(group1, &oc1);
    addGroup(group1);

    GList *group2 = nullptr;
    group2 = g_list_append(group2, &oc2);
    group2 = g_list_append(group2, &oc3);
    addGroup(group2);

    layer.oc = &oc3;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, group2);
}

// Test: Layer's oc is not found in any group
TEST_F(PopplerDocumentLayerRbgroupTest_2241, LayerNotFoundReturnsNull_2241) {
    OptionalContentGroup oc1, oc2, oc_not_in_group;

    GList *group1 = nullptr;
    group1 = g_list_append(group1, &oc1);
    addGroup(group1);

    GList *group2 = nullptr;
    group2 = g_list_append(group2, &oc2);
    addGroup(group2);

    layer.oc = &oc_not_in_group;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, nullptr);
}

// Test: Single group with single element that matches
TEST_F(PopplerDocumentLayerRbgroupTest_2241, SingleGroupSingleElementMatch_2241) {
    OptionalContentGroup oc1;

    GList *group1 = nullptr;
    group1 = g_list_append(group1, &oc1);
    addGroup(group1);

    layer.oc = &oc1;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, group1);
}

// Test: Multiple groups, layer oc appears in the last group
TEST_F(PopplerDocumentLayerRbgroupTest_2241, LayerFoundInLastGroup_2241) {
    OptionalContentGroup oc1, oc2, oc3, oc4;

    GList *group1 = nullptr;
    group1 = g_list_append(group1, &oc1);
    addGroup(group1);

    GList *group2 = nullptr;
    group2 = g_list_append(group2, &oc2);
    addGroup(group2);

    GList *group3 = nullptr;
    group3 = g_list_append(group3, &oc3);
    group3 = g_list_append(group3, &oc4);
    addGroup(group3);

    layer.oc = &oc4;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, group3);
}

// Test: Layer oc is in multiple groups, should return the first matching group
TEST_F(PopplerDocumentLayerRbgroupTest_2241, ReturnsFirstMatchingGroup_2241) {
    OptionalContentGroup oc_shared, oc_other;

    GList *group1 = nullptr;
    group1 = g_list_append(group1, &oc_shared);
    addGroup(group1);

    GList *group2 = nullptr;
    group2 = g_list_append(group2, &oc_shared);
    group2 = g_list_append(group2, &oc_other);
    addGroup(group2);

    layer.oc = &oc_shared;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, group1);
}

// Test: Group with NULL data entry stops iteration (the loop condition checks l->data)
TEST_F(PopplerDocumentLayerRbgroupTest_2241, NullDataGroupStopsIteration_2241) {
    OptionalContentGroup oc1;

    // First entry has NULL data - loop should stop
    doc.layers_rbgroups = g_list_append(nullptr, nullptr);

    // Add a second group after the NULL one
    GList *group2 = nullptr;
    group2 = g_list_append(group2, &oc1);
    doc.layers_rbgroups = g_list_append(doc.layers_rbgroups, group2);

    layer.oc = &oc1;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    // The loop stops at the NULL data entry, so it should return nullptr
    EXPECT_EQ(result, nullptr);

    // Clean up: the second group needs manual cleanup since TearDown 
    // won't free it properly if first entry is NULL
    // Actually TearDown handles this - it iterates and frees groups
}

// Test: Large number of groups, layer found in one of them
TEST_F(PopplerDocumentLayerRbgroupTest_2241, ManyGroupsLayerFound_2241) {
    const int numGroups = 100;
    OptionalContentGroup ocs[numGroups];
    OptionalContentGroup target_oc;
    GList *target_group = nullptr;

    for (int i = 0; i < numGroups; i++) {
        GList *group = nullptr;
        group = g_list_append(group, &ocs[i]);
        if (i == 50) {
            group = g_list_append(group, &target_oc);
            target_group = group;
        }
        addGroup(group);
    }

    layer.oc = &target_oc;

    GList *result = _poppler_document_get_layer_rbgroup(&doc, &layer);
    EXPECT_EQ(result, target_group);
}
