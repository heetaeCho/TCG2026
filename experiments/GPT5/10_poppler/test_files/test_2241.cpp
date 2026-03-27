// File: poppler-document-layer-rbgroup-test_2241.cc
#include <gtest/gtest.h>

#include <glib.h>

// Forward declarations matching the production signature.
struct _PopplerDocument;
typedef _PopplerDocument PopplerDocument;

struct OptionalContentGroup {
  int dummy;
};

struct Layer {
  int* label;
  OptionalContentGroup* oc;
};

// The implementation exists in the codebase; do not re-implement it here.
extern "C" GList* _poppler_document_get_layer_rbgroup(PopplerDocument* document, Layer* layer);

// Minimal view of PopplerDocument sufficient for constructing inputs.
// In the real codebase, this comes from poppler-private.h; we only model what we need
// to set up observable behavior through the public function under test.
struct _PopplerDocument {
  int parent_instance;
  int initer;
  // In production this is a GList*; tests set it as such to exercise the function.
  GList* layers_rbgroups;
  void* output_dev;
};

namespace {

class PopplerDocumentGetLayerRbgroupTest_2241 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Free any lists we created that are still tracked.
    for (GList* group : groups_to_free_) {
      g_list_free(group);  // group elements are non-owned dummy pointers
    }
    groups_to_free_.clear();

    if (doc_.layers_rbgroups) {
      g_list_free(doc_.layers_rbgroups);  // nodes only; data pointers are group lists freed above
      doc_.layers_rbgroups = nullptr;
    }
  }

  GList* MakeGroup(std::initializer_list<OptionalContentGroup*> ocs) {
    GList* group = nullptr;
    for (auto* oc : ocs) {
      group = g_list_append(group, oc);
    }
    groups_to_free_.push_back(group);
    return group;
  }

  void SetDocumentGroups(std::initializer_list<GList*> groups) {
    doc_.layers_rbgroups = nullptr;
    for (GList* group : groups) {
      doc_.layers_rbgroups = g_list_append(doc_.layers_rbgroups, group);
    }
  }

  _PopplerDocument doc_{};  // zero-init
  std::vector<GList*> groups_to_free_;
};

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, ReturnsNullWhenDocumentHasNoGroups_2241) {
  Layer layer{};
  OptionalContentGroup oc1{};
  layer.oc = &oc1;

  doc_.layers_rbgroups = nullptr;

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), nullptr);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, ReturnsNullWhenGroupListIsEmpty_2241) {
  Layer layer{};
  OptionalContentGroup oc1{};
  layer.oc = &oc1;

  // Document list exists but contains no nodes (still nullptr).
  SetDocumentGroups({});

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), nullptr);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, ReturnsGroupWhenSingleGroupContainsLayerOc_2241) {
  Layer layer{};
  OptionalContentGroup oc1{};
  layer.oc = &oc1;

  GList* group = MakeGroup({&oc1});
  SetDocumentGroups({group});

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), group);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, ReturnsNullWhenSingleGroupDoesNotContainLayerOc_2241) {
  Layer layer{};
  OptionalContentGroup oc1{};
  OptionalContentGroup oc2{};
  layer.oc = &oc1;

  GList* group = MakeGroup({&oc2});
  SetDocumentGroups({group});

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), nullptr);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, ReturnsMatchingGroupAmongMultipleGroups_2241) {
  Layer layer{};
  OptionalContentGroup oc_target{};
  OptionalContentGroup oc_other1{};
  OptionalContentGroup oc_other2{};
  layer.oc = &oc_target;

  GList* group1 = MakeGroup({&oc_other1});
  GList* group2 = MakeGroup({&oc_target, &oc_other2});
  GList* group3 = MakeGroup({&oc_other2});

  SetDocumentGroups({group1, group2, group3});

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), group2);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, ReturnsFirstMatchingGroupIfOcAppearsInMultipleGroups_2241) {
  Layer layer{};
  OptionalContentGroup oc_shared{};
  OptionalContentGroup oc_other{};
  layer.oc = &oc_shared;

  GList* group1 = MakeGroup({&oc_shared});
  GList* group2 = MakeGroup({&oc_other, &oc_shared});

  SetDocumentGroups({group1, group2});

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), group1);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, HandlesNullLayerOcWhenAGroupContainsNull_2241) {
  Layer layer{};
  layer.oc = nullptr;

  OptionalContentGroup oc1{};
  GList* group_with_null = MakeGroup({nullptr, &oc1});
  GList* other_group = MakeGroup({&oc1});

  SetDocumentGroups({other_group, group_with_null});

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), group_with_null);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, HandlesNullLayerOcWhenNoGroupContainsNull_2241) {
  Layer layer{};
  layer.oc = nullptr;

  OptionalContentGroup oc1{};
  OptionalContentGroup oc2{};
  GList* group1 = MakeGroup({&oc1});
  GList* group2 = MakeGroup({&oc2});

  SetDocumentGroups({group1, group2});

  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), nullptr);
}

TEST_F(PopplerDocumentGetLayerRbgroupTest_2241, BoundaryStopsIfEncounteringNodeWithNullData_2241) {
  // Boundary/error-like input: a node in layers_rbgroups with data == nullptr.
  Layer layer{};
  OptionalContentGroup oc_target{};
  layer.oc = &oc_target;

  GList* matching_group = MakeGroup({&oc_target});

  // Build a list whose first node has null data, followed by a valid group.
  GList* groups = nullptr;
  groups = g_list_append(groups, nullptr);         // node with data == nullptr
  groups = g_list_append(groups, matching_group);  // later node that would match
  doc_.layers_rbgroups = groups;

  // Observable behavior: function should not return the later group in this setup.
  EXPECT_EQ(_poppler_document_get_layer_rbgroup(&doc_, &layer), nullptr);

  // TearDown will free doc_.layers_rbgroups and groups_to_free_ will free matching_group.
}

}  // namespace