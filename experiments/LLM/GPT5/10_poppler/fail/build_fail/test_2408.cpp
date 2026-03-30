// poppler-get-certificate-info-by-id-test-2408.cc
//
// Unit tests for:
//   PopplerCertificateInfo *poppler_get_certificate_info_by_id(const char *id)
//
// Constraints respected:
// - Treat implementation as black box (we only assert observable behavior).
// - Mock/stub only external collaborators used by the function.
// - Do not access private/internal state of production code.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// ---- Minimal public-facing types / declarations needed by the snippet ----
// We only model what is required for observable behavior in this function.
typedef struct _PopplerCertificateInfo {
  char *id;
} PopplerCertificateInfo;

// Collaborators the function under test depends on.
// In the real codebase these come from Poppler GLib; here we stub them so tests
// are deterministic and can verify external interactions.
GList *poppler_get_available_signing_certificates(void);
PopplerCertificateInfo *poppler_certificate_info_copy(PopplerCertificateInfo *info);
void poppler_certificate_info_free(PopplerCertificateInfo *info);

// Function under test (provided by the production object).
PopplerCertificateInfo *poppler_get_certificate_info_by_id(const char *id);

}  // extern "C"

// ------------------------------
// Test doubles / instrumentation
// ------------------------------
namespace {

struct StubState {
  GList *available_list = nullptr;

  int get_available_calls = 0;

  int copy_calls = 0;
  PopplerCertificateInfo *last_copy_arg = nullptr;

  int free_calls = 0;
  GPtrArray *freed_ptrs = nullptr;  // store freed pointers for verification
};

StubState &S() {
  static StubState st;
  return st;
}

PopplerCertificateInfo *MakeInfo(const char *id) {
  auto *info = static_cast<PopplerCertificateInfo *>(g_malloc0(sizeof(PopplerCertificateInfo)));
  info->id = id ? g_strdup(id) : nullptr;
  return info;
}

void ResetStubState() {
  // Free any leftover list (if test forgot).
  if (S().available_list) {
    g_list_free_full(S().available_list, (GDestroyNotify)poppler_certificate_info_free);
    S().available_list = nullptr;
  }

  S().get_available_calls = 0;
  S().copy_calls = 0;
  S().last_copy_arg = nullptr;
  S().free_calls = 0;

  if (S().freed_ptrs) {
    g_ptr_array_free(S().freed_ptrs, TRUE);
    S().freed_ptrs = nullptr;
  }
  S().freed_ptrs = g_ptr_array_new();
}

void SetAvailable(std::initializer_list<PopplerCertificateInfo *> infos) {
  // Ensure any previous list is cleaned up deterministically.
  if (S().available_list) {
    g_list_free_full(S().available_list, (GDestroyNotify)poppler_certificate_info_free);
    S().available_list = nullptr;
  }

  for (auto *p : infos) {
    S().available_list = g_list_append(S().available_list, p);
  }
}

bool FreedContains(PopplerCertificateInfo *ptr) {
  for (guint i = 0; i < S().freed_ptrs->len; ++i) {
    if (g_ptr_array_index(S().freed_ptrs, i) == ptr)
      return true;
  }
  return false;
}

}  // namespace

// ------------------------------------
// Stub implementations of collaborators
// ------------------------------------
extern "C" {

GList *poppler_get_available_signing_certificates(void) {
  S().get_available_calls++;

  // The production code frees the returned list via g_list_free_full(list, free_fn).
  // We return our owned list and transfer ownership to the caller.
  GList *ret = S().available_list;
  S().available_list = nullptr;
  return ret;
}

PopplerCertificateInfo *poppler_certificate_info_copy(PopplerCertificateInfo *info) {
  S().copy_calls++;
  S().last_copy_arg = info;

  // Deep-copy only what our tests model/need.
  auto *copy = static_cast<PopplerCertificateInfo *>(g_malloc0(sizeof(PopplerCertificateInfo)));
  copy->id = info && info->id ? g_strdup(info->id) : nullptr;
  return copy;
}

void poppler_certificate_info_free(PopplerCertificateInfo *info) {
  S().free_calls++;
  if (S().freed_ptrs) {
    g_ptr_array_add(S().freed_ptrs, info);
  }
  if (!info)
    return;
  g_free(info->id);
  info->id = nullptr;
  g_free(info);
}

}  // extern "C"

// --------------
// Test fixture
// --------------
class PopplerGetCertificateInfoByIdTest_2408 : public ::testing::Test {
 protected:
  void SetUp() override { ResetStubState(); }
  void TearDown() override {
    // Ensure no leaks from a failing test.
    ResetStubState();
  }
};

// -----------------
// Actual test cases
// -----------------

TEST_F(PopplerGetCertificateInfoByIdTest_2408, ReturnsNullWhenAvailableListIsNull_2408) {
  // poppler_get_available_signing_certificates returns nullptr by default.
  PopplerCertificateInfo *ret = poppler_get_certificate_info_by_id("any-id");

  EXPECT_EQ(ret, nullptr);
  EXPECT_EQ(S().get_available_calls, 1);
  EXPECT_EQ(S().copy_calls, 0) << "Should not copy when list is empty";
  EXPECT_EQ(S().free_calls, 0) << "No elements to free when list is null";
}

TEST_F(PopplerGetCertificateInfoByIdTest_2408, ReturnsNullWhenNoIdMatches_2408) {
  SetAvailable({MakeInfo("a"), MakeInfo("b"), MakeInfo("c")});

  PopplerCertificateInfo *ret = poppler_get_certificate_info_by_id("nope");

  EXPECT_EQ(ret, nullptr);
  EXPECT_EQ(S().get_available_calls, 1);
  EXPECT_EQ(S().copy_calls, 0);

  // All elements from the provided list should be freed by the function.
  EXPECT_EQ(S().free_calls, 3);
}

TEST_F(PopplerGetCertificateInfoByIdTest_2408, ReturnsCopyWhenIdMatchesSingleElement_2408) {
  auto *info = MakeInfo("match");
  SetAvailable({info});

  PopplerCertificateInfo *ret = poppler_get_certificate_info_by_id("match");

  ASSERT_NE(ret, nullptr);
  EXPECT_NE(ret, info) << "Should return a copy, not the original pointer";
  EXPECT_STREQ(ret->id, "match");

  EXPECT_EQ(S().get_available_calls, 1);
  EXPECT_EQ(S().copy_calls, 1);
  EXPECT_EQ(S().last_copy_arg, info);

  // Original list element freed by g_list_free_full.
  EXPECT_EQ(S().free_calls, 1);
  EXPECT_TRUE(FreedContains(info));

  // Caller owns the returned copy.
  poppler_certificate_info_free(ret);
}

TEST_F(PopplerGetCertificateInfoByIdTest_2408, ReturnsCopyOfFirstMatchWhenMultipleMatchesExist_2408) {
  auto *first = MakeInfo("dup");
  auto *second = MakeInfo("dup");
  auto *third = MakeInfo("other");
  SetAvailable({first, second, third});

  PopplerCertificateInfo *ret = poppler_get_certificate_info_by_id("dup");

  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret->id, "dup");

  // Observable external interaction: should copy the first matching element.
  EXPECT_EQ(S().copy_calls, 1);
  EXPECT_EQ(S().last_copy_arg, first);

  // Regardless of early break, list is freed in full.
  EXPECT_EQ(S().free_calls, 3);
  EXPECT_TRUE(FreedContains(first));
  EXPECT_TRUE(FreedContains(second));
  EXPECT_TRUE(FreedContains(third));

  poppler_certificate_info_free(ret);
}

TEST_F(PopplerGetCertificateInfoByIdTest_2408, HandlesNullSearchIdAndFindsNullInfoId_2408) {
  auto *null_id = MakeInfo(nullptr);
  auto *non_null = MakeInfo("x");
  SetAvailable({non_null, null_id});

  PopplerCertificateInfo *ret = poppler_get_certificate_info_by_id(nullptr);

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(ret->id, nullptr);

  EXPECT_EQ(S().copy_calls, 1);
  EXPECT_EQ(S().last_copy_arg, null_id);

  // Provided list gets freed.
  EXPECT_EQ(S().free_calls, 2);

  poppler_certificate_info_free(ret);
}

TEST_F(PopplerGetCertificateInfoByIdTest_2408, HandlesNullInfoIdsWhenSearchIdNonNull_2408) {
  auto *null_id_1 = MakeInfo(nullptr);
  auto *match = MakeInfo("m");
  auto *null_id_2 = MakeInfo(nullptr);
  SetAvailable({null_id_1, match, null_id_2});

  PopplerCertificateInfo *ret = poppler_get_certificate_info_by_id("m");

  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret->id, "m");

  EXPECT_EQ(S().copy_calls, 1);
  EXPECT_EQ(S().last_copy_arg, match);

  EXPECT_EQ(S().free_calls, 3);

  poppler_certificate_info_free(ret);
}

TEST_F(PopplerGetCertificateInfoByIdTest_2408, ReturnedCopyIsIndependentFromOriginal_2408) {
  auto *info = MakeInfo("orig");
  SetAvailable({info});

  PopplerCertificateInfo *ret = poppler_get_certificate_info_by_id("orig");

  ASSERT_NE(ret, nullptr);
  ASSERT_NE(ret->id, nullptr);
  EXPECT_STREQ(ret->id, "orig");

  // The original is freed by the function; returned copy should remain valid
  // (observable via still having the expected id string).
  EXPECT_EQ(S().free_calls, 1);

  // Mutate returned id to ensure it's writable and not tied to freed memory.
  // (This is about the returned object being a distinct allocation.)
  char *old = ret->id;
  ret->id = g_strdup("changed");
  g_free(old);

  EXPECT_STREQ(ret->id, "changed");

  poppler_certificate_info_free(ret);
}