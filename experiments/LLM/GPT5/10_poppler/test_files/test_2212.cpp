// File: poppler-index-iter-copy-test_2212.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <atomic>
#include <cstddef>
#include <cstdint>

// Include the implementation unit to access PopplerIndexIter layout as used by the codebase.
// This matches the "already implemented and used" constraint while keeping tests black-box
// at the function boundary (we only validate observable effects via the public struct fields
// that are available in this TU).
#include "./TestProjects/poppler/glib/poppler-document.cc"

namespace {

class ScopedGlgCriticalCatcher {
public:
  ScopedGlgCriticalCatcher() {
    handler_id_ = g_log_set_handler(
        G_LOG_DOMAIN, static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
        &ScopedGlgCriticalCatcher::LogHandler, this);
  }

  ~ScopedGlgCriticalCatcher() {
    if (handler_id_ != 0) {
      g_log_remove_handler(G_LOG_DOMAIN, handler_id_);
    }
  }

  int critical_count() const { return critical_count_.load(); }

private:
  static void LogHandler(const gchar* /*log_domain*/,
                         GLogLevelFlags log_level,
                         const gchar* /*message*/,
                         gpointer user_data) {
    auto* self = static_cast<ScopedGlgCriticalCatcher*>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      self->critical_count_.fetch_add(1);
    }
    // Swallow the message to keep test output clean.
  }

  guint handler_id_{0};
  std::atomic<int> critical_count_{0};
};

struct WeakNotifyState {
  std::atomic<int> finalized{0};
};

static void WeakNotifyCb(gpointer data, GObject* /*where_the_object_was*/) {
  auto* st = static_cast<WeakNotifyState*>(data);
  st->finalized.fetch_add(1);
}

class PopplerIndexIterCopyTest_2212 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure type system initialized (older GLib needed this; harmless otherwise).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerIndexIterCopyTest_2212, NullIterReturnsNull_2212) {
  ScopedGlgCriticalCatcher catcher;

  PopplerIndexIter* copied = poppler_index_iter_copy(nullptr);

  EXPECT_EQ(copied, nullptr);
  // g_return_val_if_fail should emit a critical log on NULL input.
  EXPECT_GE(catcher.critical_count(), 1);
}

TEST_F(PopplerIndexIterCopyTest_2212, CopiesPointerAndPublicFields_2212) {
  // Create a valid GObject to satisfy g_object_ref() in the implementation.
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Allocate iter in the same way the implementation expects to duplicate (slice).
  PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);
  ASSERT_NE(iter, nullptr);

  // Populate observable fields.
  static const int kItems[] = {1, 2, 3, 4};
  iter->items = kItems;
  iter->index = 2;

  // The real struct in poppler-document.cc includes "document" and the copy refs it.
  iter->document = reinterpret_cast<PopplerDocument*>(obj);

  PopplerIndexIter* copied = poppler_index_iter_copy(iter);
  ASSERT_NE(copied, nullptr);
  EXPECT_NE(copied, iter);

  // Observable behavior: shallow copy of items pointer and index value.
  EXPECT_EQ(copied->items, iter->items);
  EXPECT_EQ(copied->index, iter->index);

  // Observable behavior: copied iterator references the same document pointer.
  EXPECT_EQ(copied->document, iter->document);

  // Cleanup: The implementation adds a ref for the copied iterator's document.
  // We release both references explicitly to avoid leaks in the unit test.
  g_object_unref(obj); // drops one ref
  g_object_unref(obj); // drops the ref added by poppler_index_iter_copy

  g_slice_free(PopplerIndexIter, copied);
  g_slice_free(PopplerIndexIter, iter);
}

TEST_F(PopplerIndexIterCopyTest_2212, RefCountIncreasesForDocument_2212) {
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  WeakNotifyState st;
  g_object_weak_ref(obj, &WeakNotifyCb, &st);

  PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);
  ASSERT_NE(iter, nullptr);

  iter->items = nullptr;
  iter->index = 0;
  iter->document = reinterpret_cast<PopplerDocument*>(obj);

  PopplerIndexIter* copied = poppler_index_iter_copy(iter);
  ASSERT_NE(copied, nullptr);

  // If poppler_index_iter_copy took a reference, then unref'ing the original single ref
  // should NOT finalize the object yet.
  g_object_unref(obj);
  EXPECT_EQ(st.finalized.load(), 0);

  // Dropping the extra ref (taken by copy) should allow finalization.
  g_object_unref(obj);
  EXPECT_EQ(st.finalized.load(), 1);

  g_slice_free(PopplerIndexIter, copied);
  g_slice_free(PopplerIndexIter, iter);
}

TEST_F(PopplerIndexIterCopyTest_2212, BoundaryValuesArePreserved_2212) {
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  PopplerIndexIter* iter = g_slice_new0(PopplerIndexIter);
  ASSERT_NE(iter, nullptr);

  // Boundary-like values: null items pointer and very large index.
  iter->items = nullptr;
  iter->index = static_cast<size_t>(~static_cast<size_t>(0)); // SIZE_MAX
  iter->document = reinterpret_cast<PopplerDocument*>(obj);

  PopplerIndexIter* copied = poppler_index_iter_copy(iter);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->items, nullptr);
  EXPECT_EQ(copied->index, iter->index);
  EXPECT_EQ(copied->document, iter->document);

  // Release both document refs (original + copy's g_object_ref).
  g_object_unref(obj);
  g_object_unref(obj);

  g_slice_free(PopplerIndexIter, copied);
  g_slice_free(PopplerIndexIter, iter);
}

}  // namespace