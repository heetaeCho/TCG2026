// OptionalContentGroup_getViewState_944_test.cc
// Unit tests for OptionalContentGroup::getViewState()
// The TEST_ID is 944

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Poppler headers (paths may vary by build; OptionalContent.h should exist per prompt)
#include "poppler/OptionalContent.h"

// These are typically available in Poppler and are needed only to construct a Dict-based OCG.
#include "poppler/GooString.h"
#include "poppler/Object.h"

namespace {

// --------- Small, compile-friendly helpers (do not inspect private state) ---------

// Detection idiom for Dict insertion APIs.
template <typename T, typename = void>
struct HasAddObj : std::false_type {};
template <typename T>
struct HasAddObj<T, std::void_t<decltype(std::declval<T&>().add(
                     std::declval<const char*>(), std::declval<Object&&>()))>> : std::true_type {};

template <typename T, typename = void>
struct HasSetObj : std::false_type {};
template <typename T>
struct HasSetObj<T, std::void_t<decltype(std::declval<T&>().set(
                     std::declval<const char*>(), std::declval<Object>()))>> : std::true_type {};

inline void PutInDict(Dict* d, const char* key, Object obj) {
  // Prefer Dict::add(key, Object&&) if available (common in Poppler)
  if constexpr (HasAddObj<Dict>::value) {
    d->add(key, std::move(obj));
  } else if constexpr (HasSetObj<Dict>::value) {
    // Some versions expose set(key, Object)
    d->set(key, obj);
  } else {
    // If neither API exists, the build environment's Poppler Dict API differs.
    // Fail fast with a clear message rather than guessing internals.
    FAIL() << "Unsupported Poppler Dict API in this build (no add/set for Object).";
  }
}

inline Object MakeNameObject(const std::string& s) {
  // Construct an Object holding a GooString. Different Poppler versions have different helpers,
  // so we use a conservative approach: allocate a GooString and set it into an Object via
  // commonly available API.
  GooString* gs = new GooString(s.c_str());

  Object o;
  // Common Poppler API patterns: Object(objString, GooString*) or Object::initString
  // We avoid relying on one exact constructor by trying the most typical init* method first.
#if defined(POPPLER_OBJECT_H) || defined(OBJECT_H) || 1
  // Many Poppler versions provide initString(GooString*)
  // If not present, compilation will fail here, highlighting an API mismatch in the environment.
  o.initString(gs);
#else
  // Fallback (kept for completeness; not expected to be used)
  o = Object(objString, gs);
#endif
  return o;
}

inline std::unique_ptr<Dict> MakeMinimalOcgDictWithName(const std::string& name) {
  // Dict constructor differs by Poppler version: Dict(XRef*) is common.
  // Passing nullptr is typical for unit tests that don't need XRef resolution.
  auto dict = std::make_unique<Dict>(nullptr);
  PutInDict(dict.get(), "Name", MakeNameObject(name));
  return dict;
}

}  // namespace

class OptionalContentGroupTest_944 : public ::testing::Test {};

TEST_F(OptionalContentGroupTest_944, GetViewState_IsCallableAndStable_944) {
  auto dict = MakeMinimalOcgDictWithName("OCG-Name");
  OptionalContentGroup ocg(dict.get());

  const UsageState s1 = ocg.getViewState();
  const UsageState s2 = ocg.getViewState();

  // Observable behavior: repeated calls should be stable for the same object state.
  EXPECT_EQ(s1, s2);
}

TEST_F(OptionalContentGroupTest_944, GetViewState_WorksOnConstInstance_944) {
  auto dict = MakeMinimalOcgDictWithName("Const-OCG");
  OptionalContentGroup ocg(dict.get());

  const OptionalContentGroup& cocg = ocg;
  const UsageState s = cocg.getViewState();

  // Compare to a second const call (no assumptions about specific enum values).
  EXPECT_EQ(s, cocg.getViewState());
}

TEST_F(OptionalContentGroupTest_944, GetViewState_WithEmptyNameBoundary_DoesNotCrashAndStable_944) {
  auto dict = MakeMinimalOcgDictWithName(std::string{});  // boundary: empty name
  OptionalContentGroup ocg(dict.get());

  const UsageState s1 = ocg.getViewState();
  const UsageState s2 = ocg.getViewState();
  EXPECT_EQ(s1, s2);
}

TEST_F(OptionalContentGroupTest_944, GetViewState_WithVeryLongNameBoundary_DoesNotCrashAndStable_944) {
  std::string longName(4096, 'A');  // boundary: very long string
  auto dict = MakeMinimalOcgDictWithName(longName);
  OptionalContentGroup ocg(dict.get());

  const UsageState s1 = ocg.getViewState();
  const UsageState s2 = ocg.getViewState();
  EXPECT_EQ(s1, s2);
}

TEST_F(OptionalContentGroupTest_944, GetViewState_MultipleInstancesEachCallable_944) {
  auto dict1 = MakeMinimalOcgDictWithName("OCG-1");
  auto dict2 = MakeMinimalOcgDictWithName("OCG-2");

  OptionalContentGroup ocg1(dict1.get());
  OptionalContentGroup ocg2(dict2.get());

  // We do NOT assume they differ; we only verify observable behavior:
  // method is callable and stable per instance.
  EXPECT_EQ(ocg1.getViewState(), ocg1.getViewState());
  EXPECT_EQ(ocg2.getViewState(), ocg2.getViewState());
}