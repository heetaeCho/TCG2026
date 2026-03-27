// poppler_layers_iter_free_test_2247.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Include the public Poppler headers if available in the build.
// (This test assumes PopplerLayersIter is defined with a public `document` field
// in the build environment where these tests run.)
#include <poppler.h>

extern "C" {
void poppler_layers_iter_free(PopplerLayersIter *iter);
}

namespace {

struct WeakNotifyState {
  bool called = false;
};

void WeakNotifyThunk(gpointer data, GObject* /*where_the_object_was*/) {
  auto* state = static_cast<WeakNotifyState*>(data);
  state->called = true;
}

class PopplerLayersIterFreeTest_2247 : public ::testing::Test {
protected:
  void SetUp() override {
    // No explicit GLib/GObject init required on modern GLib, but keep the suite
    // simple and deterministic.
  }
};

}  // namespace

TEST_F(PopplerLayersIterFreeTest_2247, NullptrIsNoOp_2247) {
  // Boundary / error-safe behavior: should not crash.
  poppler_layers_iter_free(nullptr);
  SUCCEED();
}

TEST_F(PopplerLayersIterFreeTest_2247, UnrefsDocumentOnce_WhenSoleOwner_2247) {
  // Normal operation: when iter holds the only reference, freeing the iter
  // should drop that ref and finalize the document.
  auto* iter = g_slice_new0(PopplerLayersIter);
  ASSERT_NE(iter, nullptr);

  GObject* doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(doc, nullptr);

  WeakNotifyState state;
  g_object_weak_ref(doc, &WeakNotifyThunk, &state);

  // Transfer sole ownership to iter (no extra refs kept by the test).
  iter->document = doc;

  poppler_layers_iter_free(iter);

  // If poppler_layers_iter_free unref'ed doc and it was the last ref,
  // weak notify must have fired.
  EXPECT_TRUE(state.called);
}

TEST_F(PopplerLayersIterFreeTest_2247, DoesNotFinalizeDocument_WhenOtherRefsExist_2247) {
  // Boundary condition: if the document has an extra ref, freeing the iter
  // should not finalize the document (it should still be alive).
  auto* iter = g_slice_new0(PopplerLayersIter);
  ASSERT_NE(iter, nullptr);

  GObject* doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(doc, nullptr);

  // Hold an extra reference so the unref inside free() won't drop it to zero.
  g_object_ref(doc);

  WeakNotifyState state;
  g_object_weak_ref(doc, &WeakNotifyThunk, &state);

  iter->document = doc;

  poppler_layers_iter_free(iter);

  // Should not be finalized yet because we still hold a ref.
  EXPECT_FALSE(state.called);

  // Cleanup our remaining ref; this should now finalize and trigger weak notify.
  g_object_unref(doc);
  EXPECT_TRUE(state.called);
}