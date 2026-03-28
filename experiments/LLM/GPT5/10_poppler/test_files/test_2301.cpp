// get-layer-for-ref-test_2301.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler/Object.h" // Ref

// ---- Minimal stubs/types to compile & observe behavior of get_layer_for_ref ----

// Forward declarations matching the function under test's expectations.
struct _PopplerDocument;
typedef _PopplerDocument PopplerDocument;

struct DummyOC {
  Ref ref;
  Ref getRef() const { return ref; }
};

struct Layer {
  DummyOC* oc = nullptr;
  GList* kids = nullptr; // list of Layer*
};

struct _PopplerLayer {
  PopplerDocument* document = nullptr;
  Layer* layer = nullptr;
  GList* rb_group = nullptr;
};
typedef _PopplerLayer PopplerLayer;

// Observable side effects for external interactions.
namespace {
struct Calls {
  int rbgroup_calls = 0;
  PopplerDocument* rbgroup_doc = nullptr;
  Layer* rbgroup_layer = nullptr;
  GList* rbgroup_retval = nullptr;

  int layer_new_calls = 0;
  PopplerDocument* layer_new_doc = nullptr;
  Layer* layer_new_layer = nullptr;
  GList* layer_new_rb_group = nullptr;

  void Reset() { *this = Calls{}; }
};

Calls g_calls;

// A stable sentinel pointer for rb-group return (never dereferenced).
GList* kSentinelRBGroup = reinterpret_cast<GList*>(0x1);
} // namespace

extern "C" {

// Stubbed external collaborator: records calls and returns sentinel.
GList* _poppler_document_get_layer_rbgroup(PopplerDocument* document, Layer* layer)
{
  g_calls.rbgroup_calls++;
  g_calls.rbgroup_doc = document;
  g_calls.rbgroup_layer = layer;
  g_calls.rbgroup_retval = kSentinelRBGroup;
  return kSentinelRBGroup;
}

// Stubbed external collaborator: records calls and returns a newly allocated PopplerLayer.
PopplerLayer* _poppler_layer_new(PopplerDocument* document, Layer* layer, GList* rb_group)
{
  g_calls.layer_new_calls++;
  g_calls.layer_new_doc = document;
  g_calls.layer_new_layer = layer;
  g_calls.layer_new_rb_group = rb_group;

  auto* pl = new PopplerLayer();
  pl->document = document;
  pl->layer = layer;
  pl->rb_group = rb_group;
  return pl;
}

} // extern "C"

// Include the implementation so the static function is in this TU.
#include "./TestProjects/poppler/glib/poppler-action.cc"

// ---- Helpers ----
namespace {

Ref MakeRef(int num, int gen)
{
  Ref r;
  r.num = num;
  r.gen = gen;
  return r;
}

GList* MakeLayerList(std::initializer_list<Layer*> layers)
{
  GList* list = nullptr;
  for (Layer* l : layers) {
    list = g_list_append(list, l);
  }
  return list;
}

void FreeLayerListShallow(GList* list) { g_list_free(list); }

} // namespace

// ---- Tests ----
class GetLayerForRefTest_2301 : public ::testing::Test {
protected:
  void SetUp() override { g_calls.Reset(); }
};

TEST_F(GetLayerForRefTest_2301, ReturnsNullOnNullLayers_2301)
{
  PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(0x1234);

  PopplerLayer* out = get_layer_for_ref(doc, /*layers=*/nullptr, MakeRef(1, 0), /*preserve_rb=*/FALSE);

  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(g_calls.layer_new_calls, 0);
  EXPECT_EQ(g_calls.rbgroup_calls, 0);
}

TEST_F(GetLayerForRefTest_2301, ReturnsNullWhenNoMatch_2301)
{
  PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(0x1234);

  DummyOC oc1{MakeRef(10, 0)};
  Layer l1;
  l1.oc = &oc1;

  DummyOC oc2{MakeRef(20, 0)};
  Layer l2;
  l2.oc = &oc2;

  GList* layers = MakeLayerList({&l1, &l2});

  PopplerLayer* out = get_layer_for_ref(doc, layers, MakeRef(999, 0), /*preserve_rb=*/FALSE);

  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(g_calls.layer_new_calls, 0);
  EXPECT_EQ(g_calls.rbgroup_calls, 0);

  FreeLayerListShallow(layers);
}

TEST_F(GetLayerForRefTest_2301, FindsDirectMatchWithoutPreserveRB_2301)
{
  PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(0x1234);

  DummyOC oc1{MakeRef(10, 0)};
  Layer l1;
  l1.oc = &oc1;

  DummyOC oc2{MakeRef(20, 0)};
  Layer l2;
  l2.oc = &oc2;

  GList* layers = MakeLayerList({&l1, &l2});

  PopplerLayer* out = get_layer_for_ref(doc, layers, MakeRef(20, 0), /*preserve_rb=*/FALSE);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->document, doc);
  EXPECT_EQ(out->layer, &l2);
  EXPECT_EQ(out->rb_group, nullptr);

  EXPECT_EQ(g_calls.rbgroup_calls, 0);
  EXPECT_EQ(g_calls.layer_new_calls, 1);
  EXPECT_EQ(g_calls.layer_new_doc, doc);
  EXPECT_EQ(g_calls.layer_new_layer, &l2);
  EXPECT_EQ(g_calls.layer_new_rb_group, nullptr);

  delete out;
  FreeLayerListShallow(layers);
}

TEST_F(GetLayerForRefTest_2301, FindsDirectMatchWithPreserveRB_2301)
{
  PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(0x1234);

  DummyOC oc{MakeRef(42, 7)};
  Layer l;
  l.oc = &oc;

  GList* layers = MakeLayerList({&l});

  PopplerLayer* out = get_layer_for_ref(doc, layers, MakeRef(42, 7), /*preserve_rb=*/TRUE);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->document, doc);
  EXPECT_EQ(out->layer, &l);
  EXPECT_EQ(out->rb_group, kSentinelRBGroup);

  EXPECT_EQ(g_calls.rbgroup_calls, 1);
  EXPECT_EQ(g_calls.rbgroup_doc, doc);
  EXPECT_EQ(g_calls.rbgroup_layer, &l);

  EXPECT_EQ(g_calls.layer_new_calls, 1);
  EXPECT_EQ(g_calls.layer_new_doc, doc);
  EXPECT_EQ(g_calls.layer_new_layer, &l);
  EXPECT_EQ(g_calls.layer_new_rb_group, kSentinelRBGroup);

  delete out;
  FreeLayerListShallow(layers);
}

TEST_F(GetLayerForRefTest_2301, FindsNestedMatchInKids_2301)
{
  PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(0x1234);

  // Root layer doesn't match, but has a matching child.
  DummyOC root_oc{MakeRef(1, 0)};
  Layer root;
  root.oc = &root_oc;

  DummyOC child_oc{MakeRef(2, 0)};
  Layer child;
  child.oc = &child_oc;

  root.kids = MakeLayerList({&child});

  GList* layers = MakeLayerList({&root});

  PopplerLayer* out = get_layer_for_ref(doc, layers, MakeRef(2, 0), /*preserve_rb=*/FALSE);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->layer, &child);
  EXPECT_EQ(out->rb_group, nullptr);

  EXPECT_EQ(g_calls.rbgroup_calls, 0);
  EXPECT_EQ(g_calls.layer_new_calls, 1);
  EXPECT_EQ(g_calls.layer_new_layer, &child);

  delete out;
  FreeLayerListShallow(root.kids);
  FreeLayerListShallow(layers);
}

TEST_F(GetLayerForRefTest_2301, TraversesKidsEvenIfOcIsNull_2301)
{
  PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(0x1234);

  Layer root;
  root.oc = nullptr; // explicitly null

  DummyOC child_oc{MakeRef(77, 3)};
  Layer child;
  child.oc = &child_oc;

  root.kids = MakeLayerList({&child});

  GList* layers = MakeLayerList({&root});

  PopplerLayer* out = get_layer_for_ref(doc, layers, MakeRef(77, 3), /*preserve_rb=*/TRUE);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->layer, &child);
  EXPECT_EQ(out->rb_group, kSentinelRBGroup);

  EXPECT_EQ(g_calls.rbgroup_calls, 1);
  EXPECT_EQ(g_calls.rbgroup_layer, &child);
  EXPECT_EQ(g_calls.layer_new_calls, 1);
  EXPECT_EQ(g_calls.layer_new_layer, &child);
  EXPECT_EQ(g_calls.layer_new_rb_group, kSentinelRBGroup);

  delete out;
  FreeLayerListShallow(root.kids);
  FreeLayerListShallow(layers);
}

TEST_F(GetLayerForRefTest_2301, StopsAtFirstMatchAndDoesNotCreateMultipleLayers_2301)
{
  PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(0x1234);

  // Two siblings both match the same ref; expect only one allocation/call.
  DummyOC oc_a{MakeRef(5, 0)};
  Layer a;
  a.oc = &oc_a;

  DummyOC oc_b{MakeRef(5, 0)};
  Layer b;
  b.oc = &oc_b;

  GList* layers = MakeLayerList({&a, &b});

  PopplerLayer* out = get_layer_for_ref(doc, layers, MakeRef(5, 0), /*preserve_rb=*/FALSE);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(g_calls.layer_new_calls, 1);
  EXPECT_TRUE(out->layer == &a || out->layer == &b); // must be exactly one of them

  delete out;
  FreeLayerListShallow(layers);
}