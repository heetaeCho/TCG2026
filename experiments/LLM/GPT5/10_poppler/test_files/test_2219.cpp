// File: poppler-index-iter-free-test-2219.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Poppler GLib header (expected to provide PopplerIndexIter definition)
#include <poppler.h>

namespace {

class PopplerIndexIterFreeTest_2219 : public ::testing::Test {
protected:
  static void WeakNotify(gpointer data, GObject* /*where_the_object_was*/) {
    auto* flag = static_cast<bool*>(data);
    *flag = true;
  }
};

TEST_F(PopplerIndexIterFreeTest_2219, NullIterDoesNotCrash_2219) {
  // Should be a no-op.
  poppler_index_iter_free(nullptr);
  SUCCEED();
}

TEST_F(PopplerIndexIterFreeTest_2219, UnrefsDocumentAndFinalizesWhenLastRef_2219) {
  // Use a plain GObject instance; g_object_unref should work on any GObject.
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  bool finalized = false;
  g_object_weak_ref(obj, &WeakNotify, &finalized);

  // Allocate an iterator and attach the object as its "document".
  // This matches the observable behavior: poppler_index_iter_free() must unref iter->document.
  PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);
  ASSERT_NE(iter, nullptr);

  // Cast is safe for ref/unref purposes (GObject ABI); the function only calls g_object_unref().
  iter->document = reinterpret_cast<PopplerDocument*>(obj);

  // If poppler_index_iter_free() unrefs the document, and this was the last reference,
  // the weak notify should run synchronously.
  poppler_index_iter_free(iter);

  EXPECT_TRUE(finalized);
}

TEST_F(PopplerIndexIterFreeTest_2219, UnrefsDocumentButDoesNotFinalizeIfExtraRefHeld_2219) {
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  bool finalized = false;
  g_object_weak_ref(obj, &WeakNotify, &finalized);

  // Hold an extra reference so one unref won't finalize it.
  g_object_ref(obj);

  PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);
  ASSERT_NE(iter, nullptr);
  iter->document = reinterpret_cast<PopplerDocument*>(obj);

  poppler_index_iter_free(iter);

  // Should still be alive due to the extra ref.
  EXPECT_FALSE(finalized);

  // Drop our remaining refs; this should now finalize.
  g_object_unref(obj); // releases the extra ref we took
  g_object_unref(obj); // releases the original ref from g_object_new

  EXPECT_TRUE(finalized);
}

} // namespace