// poppler_certificate_info_new_test_2394.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
// Prefer including the real Poppler GLib headers if available in your build.
// If your build already includes Poppler headers globally, this is fine.
#include <poppler.h>

// Function under test (should be provided by the linked Poppler library/object files).
PopplerCertificateInfo *poppler_certificate_info_new(void);
}  // extern "C"

namespace {

// SFINAE helper: detect whether PopplerCertificateInfo is a complete type (sizeof(T) is valid).
template <typename T, typename = void>
struct is_complete : std::false_type {};

template <typename T>
struct is_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type {};

template <typename T>
bool all_bytes_zero(const T* p) {
  const unsigned char* bytes = reinterpret_cast<const unsigned char*>(p);
  for (size_t i = 0; i < sizeof(T); ++i) {
    if (bytes[i] != 0u) return false;
  }
  return true;
}

}  // namespace

class PopplerCertificateInfoNewTest_2394 : public ::testing::Test {};

TEST_F(PopplerCertificateInfoNewTest_2394, ReturnsNonNull_2394) {
  PopplerCertificateInfo* info = poppler_certificate_info_new();
  ASSERT_NE(info, nullptr);

  g_free(info);
}

TEST_F(PopplerCertificateInfoNewTest_2394, ReturnsDistinctInstances_2394) {
  PopplerCertificateInfo* a = poppler_certificate_info_new();
  PopplerCertificateInfo* b = poppler_certificate_info_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b);

  g_free(a);
  g_free(b);
}

TEST_F(PopplerCertificateInfoNewTest_2394, ReturnedMemoryIsZeroInitialized_WhenTypeComplete_2394) {
  PopplerCertificateInfo* info = poppler_certificate_info_new();
  ASSERT_NE(info, nullptr);

  if constexpr (!is_complete<PopplerCertificateInfo>::value) {
    // If the type is opaque in this build, we can't safely check its byte contents.
    g_free(info);
    GTEST_SKIP() << "PopplerCertificateInfo is incomplete/opaque; cannot validate zero-initialization.";
  } else {
    EXPECT_TRUE(all_bytes_zero(info));
    g_free(info);
  }
}

TEST_F(PopplerCertificateInfoNewTest_2394, CanAllocateAndFreeManyTimes_2394) {
  constexpr int kCount = 1024;
  PopplerCertificateInfo* ptrs[kCount] = {};

  for (int i = 0; i < kCount; ++i) {
    ptrs[i] = poppler_certificate_info_new();
    ASSERT_NE(ptrs[i], nullptr) << "Allocation failed at index " << i;
    // Basic uniqueness check against immediate predecessor (cheap sanity).
    if (i > 0) {
      EXPECT_NE(ptrs[i], ptrs[i - 1]);
    }
  }

  for (int i = 0; i < kCount; ++i) {
    g_free(ptrs[i]);
    ptrs[i] = nullptr;
  }
}

TEST_F(PopplerCertificateInfoNewTest_2394, FreeNullIsSafe_GLibContract_2394) {
  // This isn't testing Poppler directly, but guards a common cleanup pattern:
  // g_free(NULL) is a defined no-op in GLib, so callers can safely cleanup on failure paths.
  ASSERT_NO_FATAL_FAILURE(g_free(nullptr));
}