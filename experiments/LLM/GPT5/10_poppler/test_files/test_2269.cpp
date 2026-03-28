// poppler-attachment-finalize-ut-2269.cc
//
// Unit tests for poppler_attachment_finalize() behavior via the public GObject lifecycle.
// Constraints honored:
//  - Treat implementation as black box (no logic re-implementation).
//  - No private state access.
//  - Observable behavior tested: object can be finalized safely; weak-notify external interaction.
//
// Build expectations:
//  - Poppler GLib headers available (poppler.h / poppler-glib.h depending on distro)
//  - GLib/GObject available
//  - GoogleTest available

#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <atomic>
#include <type_traits>
#include <utility>

#if __has_include(<poppler.h>)
#include <poppler.h>
#elif __has_include(<poppler-glib.h>)
#include <poppler-glib.h>
#else
#error "Poppler GLib headers not found (expected <poppler.h> or <poppler-glib.h>)."
#endif

namespace {

// ---- Compile-time member detection helpers (so tests don't assume struct layout) ----
template <typename T, typename = void>
struct has_member_name : std::false_type {};
template <typename T>
struct has_member_name<T, std::void_t<decltype(std::declval<T>().name)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_description : std::false_type {};
template <typename T>
struct has_member_description<T, std::void_t<decltype(std::declval<T>().description)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_checksum : std::false_type {};
template <typename T>
struct has_member_checksum<T, std::void_t<decltype(std::declval<T>().checksum)>> : std::true_type {};

// If checksum exists, detect if it's a GString* (most likely) by checking assignability.
template <typename T, typename = void>
struct checksum_is_gstring_ptr : std::false_type {};
template <typename T>
struct checksum_is_gstring_ptr<
    T,
    std::void_t<decltype(std::declval<T>().checksum), decltype(std::declval<T>().checksum = (GString*)nullptr)>>
    : std::true_type {};

static PopplerAttachment* NewAttachmentOrSkip() {
#if defined(POPPLER_TYPE_ATTACHMENT)
  GObject* obj = static_cast<GObject*>(g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr));
  if (!obj) {
    return nullptr;
  }
  return reinterpret_cast<PopplerAttachment*>(obj);
#else
  return nullptr;
#endif
}

static void WeakNotifyCounter(gpointer data, GObject* /*where_object_was*/) {
  auto* counter = static_cast<std::atomic<int>*>(data);
  counter->fetch_add(1, std::memory_order_relaxed);
}

class PopplerAttachmentFinalizeTest_2269 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GType system is ready (no-op on modern GLib, harmless otherwise).
    // We avoid deprecated g_type_init().
    ASSERT_TRUE(true);
  }
};

}  // namespace

TEST_F(PopplerAttachmentFinalizeTest_2269, UnrefDoesNotCrashWithDefaults_2269) {
  PopplerAttachment* att = NewAttachmentOrSkip();
  if (!att) {
    GTEST_SKIP() << "POPPLER_TYPE_ATTACHMENT not available in this build; cannot instantiate PopplerAttachment.";
  }

  std::atomic<int> weak_calls{0};
  g_object_weak_ref(G_OBJECT(att), &WeakNotifyCounter, &weak_calls);

  // Observable behavior: unref should safely finalize/free the object.
  g_object_unref(att);

  // External interaction verification: weak notify should be invoked exactly once.
  EXPECT_EQ(weak_calls.load(std::memory_order_relaxed), 1);
}

TEST_F(PopplerAttachmentFinalizeTest_2269, UnrefDoesNotCrashWithAllocatedFields_2269) {
  PopplerAttachment* att = NewAttachmentOrSkip();
  if (!att) {
    GTEST_SKIP() << "POPPLER_TYPE_ATTACHMENT not available in this build; cannot instantiate PopplerAttachment.";
  }

  // Only touch fields if they exist publicly in this build's headers.
  if constexpr (has_member_name<PopplerAttachment>::value) {
    att->name = g_strdup("example-name");
  } else {
    // If the field isn't public, skip the part that would require it.
    // We still test finalize safety via unref below.
  }

  if constexpr (has_member_description<PopplerAttachment>::value) {
    att->description = g_strdup("example description");
  }

  if constexpr (has_member_checksum<PopplerAttachment>::value && checksum_is_gstring_ptr<PopplerAttachment>::value) {
    att->checksum = g_string_new("abc123");
  }

  std::atomic<int> weak_calls{0};
  g_object_weak_ref(G_OBJECT(att), &WeakNotifyCounter, &weak_calls);

  // Observable behavior: unref should safely free all owned resources and finalize.
  g_object_unref(att);

  EXPECT_EQ(weak_calls.load(std::memory_order_relaxed), 1);
}

TEST_F(PopplerAttachmentFinalizeTest_2269, UnrefDoesNotCrashWithEmptyAndLargeStrings_2269) {
  PopplerAttachment* att = NewAttachmentOrSkip();
  if (!att) {
    GTEST_SKIP() << "POPPLER_TYPE_ATTACHMENT not available in this build; cannot instantiate PopplerAttachment.";
  }

  // Boundary-style values: empty strings and large-ish strings.
  const std::string large(64 * 1024, 'x');  // 64KiB

  if constexpr (has_member_name<PopplerAttachment>::value) {
    att->name = g_strdup("");  // empty
  }
  if constexpr (has_member_description<PopplerAttachment>::value) {
    att->description = g_strdup(large.c_str());  // large
  }
  if constexpr (has_member_checksum<PopplerAttachment>::value && checksum_is_gstring_ptr<PopplerAttachment>::value) {
    // Include embedded NULs to ensure the underlying free path is robust.
    const char buf[] = {'a', '\0', 'b', '\0', 'c'};
    att->checksum = g_string_new_len(buf, static_cast<gssize>(sizeof(buf)));
  }

  std::atomic<int> weak_calls{0};
  g_object_weak_ref(G_OBJECT(att), &WeakNotifyCounter, &weak_calls);

  g_object_unref(att);

  EXPECT_EQ(weak_calls.load(std::memory_order_relaxed), 1);
}

TEST_F(PopplerAttachmentFinalizeTest_2269, FinalizeIsStableAcrossManyInstances_2269) {
  // Stress-ish boundary: finalize many objects to catch obvious lifecycle issues.
  // (Not a performance test; just coverage for repeated finalize.)
  constexpr int kCount = 200;

#if !defined(POPPLER_TYPE_ATTACHMENT)
  GTEST_SKIP() << "POPPLER_TYPE_ATTACHMENT not available in this build; cannot instantiate PopplerAttachment.";
#endif

  std::atomic<int> weak_calls_total{0};

  for (int i = 0; i < kCount; ++i) {
    PopplerAttachment* att = NewAttachmentOrSkip();
    ASSERT_NE(att, nullptr);

    if constexpr (has_member_name<PopplerAttachment>::value) {
      // Alternate between nullptr and allocated to cover both paths.
      if ((i % 2) == 0) {
        att->name = g_strdup("n");
      }
    }
    if constexpr (has_member_description<PopplerAttachment>::value) {
      if ((i % 3) == 0) {
        att->description = g_strdup("d");
      }
    }
    if constexpr (has_member_checksum<PopplerAttachment>::value && checksum_is_gstring_ptr<PopplerAttachment>::value) {
      if ((i % 5) == 0) {
        att->checksum = g_string_new("c");
      }
    }

    g_object_weak_ref(G_OBJECT(att), &WeakNotifyCounter, &weak_calls_total);
    g_object_unref(att);
  }

  // External interaction: each object should have triggered weak notify once.
  EXPECT_EQ(weak_calls_total.load(std::memory_order_relaxed), kCount);
}