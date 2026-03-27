// File: poppler-ps-file-free-test_2260.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <atomic>

extern "C" {
// Function under test (implemented in poppler-document.cc)
void poppler_ps_file_free(PopplerPSFile *ps_file);
}

// Some builds expose the GType macro for PopplerPSFile; use it when available.
// If the type macro is not available, these tests (except NULL-handling) will be
// compiled out safely.
#ifndef POPPLER_TYPE_PS_FILE
// Some distributions may use a different macro name; add aliases here if needed.
// #define POPPLER_TYPE_PS_FILE POPPLER_TYPE_POSTSCRIPT_FILE
#endif

namespace {

struct WeakNotifyState {
  std::atomic<int> finalized_count{0};
};

static void WeakNotifyCb(gpointer data, GObject* /*where_the_object_was*/) {
  auto* state = static_cast<WeakNotifyState*>(data);
  state->finalized_count.fetch_add(1, std::memory_order_relaxed);
}

class PopplerPSFileFreeTest_2260 : public ::testing::Test {
protected:
  void TearDown() override {
    // Drain any unexpected GLib test messages to avoid polluting other tests.
    // (No-op unless g_test_expect_message was used and not asserted.)
  }
};

TEST_F(PopplerPSFileFreeTest_2260, NullptrTriggersCriticalAndReturns_2260) {
  // g_return_if_fail(ps_file != nullptr) should log a critical and return.
  // We verify it's observable via GLib's test log capture and that it doesn't crash.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*ps_file*failed*");
  poppler_ps_file_free(nullptr);
  g_test_assert_expected_messages();
}

#if defined(POPPLER_TYPE_PS_FILE)

TEST_F(PopplerPSFileFreeTest_2260, UnrefsObjectAndFinalizesOnLastRef_2260) {
  // Create a real PopplerPSFile instance as a GObject and verify it is finalized
  // when poppler_ps_file_free() is called with a single reference.
  WeakNotifyState state;

  GObject* obj = G_OBJECT(g_object_new(POPPLER_TYPE_PS_FILE, nullptr));
  ASSERT_NE(obj, nullptr);

  g_object_weak_ref(obj, WeakNotifyCb, &state);

  // With a single ref, free should drop the last reference -> finalize exactly once.
  poppler_ps_file_free(reinterpret_cast<PopplerPSFile*>(obj));

  EXPECT_EQ(state.finalized_count.load(std::memory_order_relaxed), 1);
}

TEST_F(PopplerPSFileFreeTest_2260, UnrefsOnlyOneReferenceWhenMultipleRefs_2260) {
  // Boundary: if caller holds extra references, poppler_ps_file_free() should only
  // unref once (it uses g_object_unref), so the object should *not* finalize yet.
  WeakNotifyState state;

  GObject* obj = G_OBJECT(g_object_new(POPPLER_TYPE_PS_FILE, nullptr));
  ASSERT_NE(obj, nullptr);

  g_object_weak_ref(obj, WeakNotifyCb, &state);

  // Add an extra ref so it's not destroyed by a single unref.
  g_object_ref(obj);

  poppler_ps_file_free(reinterpret_cast<PopplerPSFile*>(obj));

  // Should not have finalized yet because we still hold one reference.
  EXPECT_EQ(state.finalized_count.load(std::memory_order_relaxed), 0);

  // Release the remaining reference; now it should finalize exactly once.
  g_object_unref(obj);
  EXPECT_EQ(state.finalized_count.load(std::memory_order_relaxed), 1);
}

#else  // !POPPLER_TYPE_PS_FILE

TEST_F(PopplerPSFileFreeTest_2260, TypeMacroUnavailable_SkipsNonNullTests_2260) {
  GTEST_SKIP() << "POPPLER_TYPE_PS_FILE is not available in this build; "
                  "skipping non-null PopplerPSFile lifecycle tests.";
}

#endif