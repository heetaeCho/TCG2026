// build_ocg_state_test_2302.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <vector>

// -----------------------------------------------------------------------------
// Minimal test scaffolding (external collaborators + data types)
//
// These are *test doubles* for the types/collaborators referenced by the
// provided function. We do NOT re-implement Poppler internals; we only provide
// enough surface for observable behavior testing of build_ocg_state().
// -----------------------------------------------------------------------------

struct Ref {
  int num = 0;
  int gen = 0;
};

struct PopplerLayer {
  int id = 0;
};

enum PopplerActionLayerAction {
  POPPLER_ACTION_LAYER_ON = 1,
  POPPLER_ACTION_LAYER_OFF = 2,
  POPPLER_ACTION_LAYER_TOGGLE = 3,
};

struct PopplerActionLayer {
  PopplerActionLayerAction action = POPPLER_ACTION_LAYER_ON;
  GList* layers = nullptr;  // PopplerLayer*
};

struct PopplerActionOCGState {
  GList* state_list = nullptr;  // PopplerActionLayer*
};

union PopplerAction {
  PopplerActionOCGState ocg_state;
};

struct PopplerDocument {
  // In real Poppler this is richer; for this unit we only need "layers".
  GList* layers = nullptr;  // PopplerLayer* (or any opaque)
};

// Fake LinkOCGState compatible with the interface used by build_ocg_state().
class LinkOCGState {
public:
  enum State {
    On,
    Off,
    Toggle,
  };

  struct StateList {
    State st;
    std::vector<Ref> list;
  };

  explicit LinkOCGState(std::vector<StateList> states, bool preserve_rb)
      : states_(std::move(states)), preserve_rb_(preserve_rb) {}

  const std::vector<StateList>& getStateList() const { return states_; }
  bool getPreserveRB() const { return preserve_rb_; }

private:
  std::vector<StateList> states_;
  bool preserve_rb_ = false;
};

// -----------------------------------------------------------------------------
// External collaborators used by build_ocg_state() in the snippet.
// We implement them as controllable stubs to verify external interactions.
// -----------------------------------------------------------------------------

static bool g_get_layers_result = true;
static int g_get_layers_call_count = 0;

static std::vector<bool> g_get_layer_preserve_rb_args;
static std::vector<Ref> g_get_layer_ref_args;

extern "C" gboolean _poppler_document_get_layers(PopplerDocument* document) {
  ++g_get_layers_call_count;
  if (!g_get_layers_result) {
    return FALSE;
  }
  // For the "success" case, ensure document->layers becomes non-null.
  if (!document->layers) {
    // Any non-null sentinel is enough for build_ocg_state() to proceed.
    document->layers = reinterpret_cast<GList*>(0x1);
  }
  return TRUE;
}

static PopplerLayer* make_layer_for(const Ref& ref, bool preserve_rb) {
  // Stable, deterministic identity for assertions.
  // (We just need distinct pointers per call.)
  auto* layer = g_new0(PopplerLayer, 1);
  layer->id = (ref.num * 100000) + (ref.gen * 10) + (preserve_rb ? 1 : 0);
  return layer;
}

// Signature based on usage in the provided snippet.
static PopplerLayer* get_layer_for_ref(PopplerDocument* /*document*/,
                                      GList* /*layers*/,
                                      const Ref& ref,
                                      bool preserve_rb) {
  g_get_layer_ref_args.push_back(ref);
  g_get_layer_preserve_rb_args.push_back(preserve_rb);
  return make_layer_for(ref, preserve_rb);
}

// -----------------------------------------------------------------------------
// Function under test: exact snippet provided.
// -----------------------------------------------------------------------------
static void build_ocg_state(PopplerDocument* document,
                            PopplerAction* action,
                            const LinkOCGState* ocg_state) {
  const std::vector<LinkOCGState::StateList>& st_list = ocg_state->getStateList();
  bool preserve_rb = ocg_state->getPreserveRB();
  GList* layer_state = nullptr;

  if (!document->layers) {
    if (!_poppler_document_get_layers(document)) {
      return;
    }
  }

  for (const LinkOCGState::StateList& list : st_list) {
    auto* action_layer = g_slice_new0(PopplerActionLayer);
    switch (list.st) {
      case LinkOCGState::On:
        action_layer->action = POPPLER_ACTION_LAYER_ON;
        break;
      case LinkOCGState::Off:
        action_layer->action = POPPLER_ACTION_LAYER_OFF;
        break;
      case LinkOCGState::Toggle:
        action_layer->action = POPPLER_ACTION_LAYER_TOGGLE;
        break;
    }
    for (const Ref& ref : list.list) {
      PopplerLayer* layer = get_layer_for_ref(document, document->layers, ref, preserve_rb);
      action_layer->layers = g_list_prepend(action_layer->layers, layer);
    }
    layer_state = g_list_prepend(layer_state, action_layer);
  }

  action->ocg_state.state_list = g_list_reverse(layer_state);
}

// -----------------------------------------------------------------------------
// Test helpers
// -----------------------------------------------------------------------------

static void ResetStubs() {
  g_get_layers_result = true;
  g_get_layers_call_count = 0;
  g_get_layer_preserve_rb_args.clear();
  g_get_layer_ref_args.clear();
}

static std::vector<PopplerActionLayer*> CollectStateLayers(GList* state_list) {
  std::vector<PopplerActionLayer*> out;
  for (GList* it = state_list; it; it = it->next) {
    out.push_back(static_cast<PopplerActionLayer*>(it->data));
  }
  return out;
}

static std::vector<PopplerLayer*> CollectLayers(GList* layers_list) {
  std::vector<PopplerLayer*> out;
  for (GList* it = layers_list; it; it = it->next) {
    out.push_back(static_cast<PopplerLayer*>(it->data));
  }
  return out;
}

static void FreeActionStateList(GList* state_list) {
  // Free allocated PopplerActionLayer and PopplerLayer elements created by stubs.
  for (GList* it = state_list; it; it = it->next) {
    auto* al = static_cast<PopplerActionLayer*>(it->data);
    for (GList* lit = al->layers; lit; lit = lit->next) {
      auto* layer = static_cast<PopplerLayer*>(lit->data);
      g_free(layer);
    }
    g_list_free(al->layers);
    g_slice_free(PopplerActionLayer, al);
  }
  g_list_free(state_list);
}

// -----------------------------------------------------------------------------
// Tests (TEST_ID = 2302)
// -----------------------------------------------------------------------------

class BuildOCGStateTest_2302 : public ::testing::Test {
protected:
  void SetUp() override { ResetStubs(); }
  void TearDown() override { ResetStubs(); }
};

TEST_F(BuildOCGStateTest_2302, BuildsStateListAndMapsActions_2302) {
  PopplerDocument doc{};
  doc.layers = reinterpret_cast<GList*>(0x1234);  // already available, no fetch needed

  PopplerAction action{};
  action.ocg_state.state_list = nullptr;

  LinkOCGState::StateList s1;
  s1.st = LinkOCGState::On;
  s1.list = {Ref{1, 0}, Ref{2, 0}};

  LinkOCGState::StateList s2;
  s2.st = LinkOCGState::Off;
  s2.list = {Ref{5, 1}};

  LinkOCGState ocg({s1, s2}, /*preserve_rb=*/true);

  build_ocg_state(&doc, &action, &ocg);

  ASSERT_EQ(g_get_layers_call_count, 0) << "Should not fetch layers when document->layers is set";

  // Verify state_list length equals number of StateList entries.
  ASSERT_EQ(g_list_length(action.ocg_state.state_list), 2u);

  auto layers = CollectStateLayers(action.ocg_state.state_list);
  ASSERT_EQ(layers.size(), 2u);

  // Verify action mapping per list.
  EXPECT_EQ(layers[0]->action, POPPLER_ACTION_LAYER_ON);
  EXPECT_EQ(layers[1]->action, POPPLER_ACTION_LAYER_OFF);

  // Verify get_layer_for_ref called for each ref, and preserve_rb forwarded.
  ASSERT_EQ(g_get_layer_ref_args.size(), 3u);
  ASSERT_EQ(g_get_layer_preserve_rb_args.size(), 3u);
  for (bool b : g_get_layer_preserve_rb_args) {
    EXPECT_TRUE(b);
  }
  EXPECT_EQ(g_get_layer_ref_args[0].num, 1);
  EXPECT_EQ(g_get_layer_ref_args[1].num, 2);
  EXPECT_EQ(g_get_layer_ref_args[2].num, 5);

  // Verify each action-layer contains the expected layers (order-agnostic).
  auto al0_layers = CollectLayers(layers[0]->layers);
  auto al1_layers = CollectLayers(layers[1]->layers);

  ASSERT_EQ(al0_layers.size(), 2u);
  ASSERT_EQ(al1_layers.size(), 1u);

  // The stub encodes preserve_rb in id (+1).
  // We just ensure IDs correspond to the input refs with preserve_rb=true.
  auto expect_id = [](int num, int gen) { return (num * 100000) + (gen * 10) + 1; };

  // Order in the GList is not asserted; only membership.
  bool found1 = false, found2 = false;
  for (auto* l : al0_layers) {
    found1 |= (l->id == expect_id(1, 0));
    found2 |= (l->id == expect_id(2, 0));
  }
  EXPECT_TRUE(found1);
  EXPECT_TRUE(found2);

  EXPECT_EQ(al1_layers[0]->id, expect_id(5, 1));

  FreeActionStateList(action.ocg_state.state_list);
  action.ocg_state.state_list = nullptr;
}

TEST_F(BuildOCGStateTest_2302, EmptyStateListProducesEmptyOutput_2302) {
  PopplerDocument doc{};
  doc.layers = reinterpret_cast<GList*>(0x1234);

  PopplerAction action{};
  action.ocg_state.state_list = nullptr;

  LinkOCGState ocg(/*states=*/{}, /*preserve_rb=*/false);

  build_ocg_state(&doc, &action, &ocg);

  EXPECT_EQ(g_get_layers_call_count, 0);
  EXPECT_EQ(action.ocg_state.state_list, nullptr);
  EXPECT_TRUE(g_get_layer_ref_args.empty());
  EXPECT_TRUE(g_get_layer_preserve_rb_args.empty());
}

TEST_F(BuildOCGStateTest_2302, FetchLayersCalledWhenDocumentHasNoLayers_2302) {
  PopplerDocument doc{};
  doc.layers = nullptr;

  PopplerAction action{};
  action.ocg_state.state_list = nullptr;

  LinkOCGState::StateList s1;
  s1.st = LinkOCGState::Toggle;
  s1.list = {Ref{7, 3}};
  LinkOCGState ocg({s1}, /*preserve_rb=*/false);

  g_get_layers_result = true;

  build_ocg_state(&doc, &action, &ocg);

  EXPECT_EQ(g_get_layers_call_count, 1);
  ASSERT_NE(doc.layers, nullptr) << "Stub _poppler_document_get_layers should populate layers on success";

  ASSERT_NE(action.ocg_state.state_list, nullptr);
  ASSERT_EQ(g_list_length(action.ocg_state.state_list), 1u);

  auto layers = CollectStateLayers(action.ocg_state.state_list);
  ASSERT_EQ(layers.size(), 1u);
  EXPECT_EQ(layers[0]->action, POPPLER_ACTION_LAYER_TOGGLE);

  // preserve_rb forwarded as false
  ASSERT_EQ(g_get_layer_preserve_rb_args.size(), 1u);
  EXPECT_FALSE(g_get_layer_preserve_rb_args[0]);

  FreeActionStateList(action.ocg_state.state_list);
  action.ocg_state.state_list = nullptr;
}

TEST_F(BuildOCGStateTest_2302, ReturnsEarlyWhenLayerFetchFails_2302) {
  PopplerDocument doc{};
  doc.layers = nullptr;

  PopplerAction action{};
  action.ocg_state.state_list = nullptr;

  LinkOCGState::StateList s1;
  s1.st = LinkOCGState::On;
  s1.list = {Ref{1, 1}, Ref{2, 2}};
  LinkOCGState ocg({s1}, /*preserve_rb=*/true);

  g_get_layers_result = false;

  build_ocg_state(&doc, &action, &ocg);

  EXPECT_EQ(g_get_layers_call_count, 1);
  EXPECT_EQ(action.ocg_state.state_list, nullptr) << "Should not modify output on early return";
  EXPECT_TRUE(g_get_layer_ref_args.empty()) << "Should not call get_layer_for_ref if layers can't be fetched";
  EXPECT_TRUE(g_get_layer_preserve_rb_args.empty());
}

TEST_F(BuildOCGStateTest_2302, PreserveRBForwardedForBothTrueAndFalse_2302) {
  PopplerDocument doc{};
  doc.layers = reinterpret_cast<GList*>(0x1234);

  {
    PopplerAction action{};
    action.ocg_state.state_list = nullptr;

    LinkOCGState::StateList s1;
    s1.st = LinkOCGState::Off;
    s1.list = {Ref{9, 0}};
    LinkOCGState ocg({s1}, /*preserve_rb=*/true);

    build_ocg_state(&doc, &action, &ocg);

    ASSERT_EQ(g_get_layer_preserve_rb_args.size(), 1u);
    EXPECT_TRUE(g_get_layer_preserve_rb_args[0]);

    FreeActionStateList(action.ocg_state.state_list);
    action.ocg_state.state_list = nullptr;
  }

  ResetStubs();

  {
    PopplerAction action{};
    action.ocg_state.state_list = nullptr;

    LinkOCGState::StateList s1;
    s1.st = LinkOCGState::Off;
    s1.list = {Ref{9, 0}};
    LinkOCGState ocg({s1}, /*preserve_rb=*/false);

    build_ocg_state(&doc, &action, &ocg);

    ASSERT_EQ(g_get_layer_preserve_rb_args.size(), 1u);
    EXPECT_FALSE(g_get_layer_preserve_rb_args[0]);

    FreeActionStateList(action.ocg_state.state_list);
    action.ocg_state.state_list = nullptr;
  }
}