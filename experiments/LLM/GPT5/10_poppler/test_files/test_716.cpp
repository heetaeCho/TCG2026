// File: page_getGroup_test_716.cpp
// TEST_ID: 716
//
// Unit tests for Page::getGroup() forwarding behavior.
//
// Constraints honored:
// - Treat Page/PageAttrs as black boxes.
// - Only use public interfaces and observable behavior (return values / stability).
// - No access to private state.
// - No re-implementation of internal logic.

#include <gtest/gtest.h>

#include "Page.h"

// Poppler headers commonly needed for Dict/Object/Ref.
// If your build uses different include paths, adjust accordingly.
#include "Object.h"
#include "Dict.h"

#include <type_traits>
#include <utility>

namespace {

// ---- Helper: create an Object that wraps a Dict* (covers common Poppler APIs) ----
inline Object MakeDictObject(Dict *d) {
  // Common Poppler patterns include:
  // - Object obj; obj.initDict(d);
  // - Object obj(d);   (less common)
  // We try to support both, without assuming one exists.
  Object obj;

  // Prefer initDict if available.
  struct HasInitDict {
    template <typename T>
    static auto test(int) -> decltype(std::declval<T &>().initDict(std::declval<Dict *>()), std::true_type{});
    template <typename>
    static auto test(...) -> std::false_type;
    static constexpr bool value = decltype(test<Object>(0))::value;
  };

  if constexpr (HasInitDict::value) {
    obj.initDict(d);
    return obj;
  } else if constexpr (std::is_constructible<Object, Dict *>::value) {
    return Object(d);
  } else {
    // Last resort: return a default object; test will still compile, but may fail
    // at runtime if Dict insertion requires a proper dict object.
    return obj;
  }
}

// ---- Helper: insert a key->Object into a Dict using whichever API exists ----
template <typename DictT>
struct DictAddTraits {
  template <typename T>
  static auto has_add_rvalue(int)
      -> decltype(std::declval<T &>().add(std::declval<const char *>(), std::declval<Object &&>()), std::true_type{});
  template <typename>
  static auto has_add_rvalue(...) -> std::false_type;

  template <typename T>
  static auto has_add_lvalue(int)
      -> decltype(std::declval<T &>().add(std::declval<const char *>(), std::declval<Object>()), std::true_type{});
  template <typename>
  static auto has_add_lvalue(...) -> std::false_type;

  template <typename T>
  static auto has_set(int)
      -> decltype(std::declval<T &>().set(std::declval<const char *>(), std::declval<Object &&>()), std::true_type{});
  template <typename>
  static auto has_set(...) -> std::false_type;

  static constexpr bool kHasAddRvalue = decltype(has_add_rvalue<DictT>(0))::value;
  static constexpr bool kHasAddLvalue = decltype(has_add_lvalue<DictT>(0))::value;
  static constexpr bool kHasSet = decltype(has_set<DictT>(0))::value;
};

inline void DictPut(Dict *dict, const char *key, Object &&value) {
  if (!dict) return;

  if constexpr (DictAddTraits<Dict>::kHasAddRvalue) {
    dict->add(key, std::move(value));
  } else if constexpr (DictAddTraits<Dict>::kHasAddLvalue) {
    dict->add(key, value);
  } else if constexpr (DictAddTraits<Dict>::kHasSet) {
    dict->set(key, std::move(value));
  } else {
    // If none of these exist in your Poppler version,
    // adjust this helper to match your Dict API.
  }
}

// ---- Helper: make a minimal Ref without guessing internals ----
inline Ref MakeRef(int num, int gen) {
  Ref r;
  r.num = num;
  r.gen = gen;
  return r;
}

} // namespace

class PageGetGroupTest_716 : public ::testing::Test {};

TEST_F(PageGetGroupTest_716, ForwardsToAttrsGetGroup_716) {
  // Arrange: build a Dict that contains a "Group" entry, and build PageAttrs from it.
  // We do NOT assume what PageAttrs does with the dict; we only assert Page forwards.
  auto *groupDict = new Dict(nullptr);
  auto *attrsDict = new Dict(nullptr);

  // Put "Group" => (dict) into attrsDict in a version-tolerant way.
  DictPut(attrsDict, "Group", MakeDictObject(groupDict));

  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, /*dict=*/attrsDict);
  PageAttrs *attrsRaw = attrs.get();

  // Minimal inputs for Page ctor. We only care that Page is constructed and callable.
  Object pageDictObj; // default/null object; treated as black box
  Ref pageRef = MakeRef(1, 0);

  Page page(/*docA=*/nullptr, /*numA=*/1, std::move(pageDictObj), pageRef, std::move(attrs));

  // Act
  Dict *fromPage = page.getGroup();
  Dict *fromAttrs = attrsRaw->getGroup();

  // Assert: observable forwarding behavior.
  EXPECT_EQ(fromPage, fromAttrs);
}

TEST_F(PageGetGroupTest_716, ReturnValueIsStableAcrossCalls_716) {
  auto *groupDict = new Dict(nullptr);
  auto *attrsDict = new Dict(nullptr);
  DictPut(attrsDict, "Group", MakeDictObject(groupDict));

  auto attrs = std::make_unique<PageAttrs>(nullptr, attrsDict);

  Object pageDictObj;
  Ref pageRef = MakeRef(2, 0);
  Page page(nullptr, 2, std::move(pageDictObj), pageRef, std::move(attrs));

  Dict *g1 = page.getGroup();
  Dict *g2 = page.getGroup();

  // We don't assume non-null; only that repeated calls are consistent.
  EXPECT_EQ(g1, g2);
}

TEST_F(PageGetGroupTest_716, MissingGroupKeyDoesNotChangeBetweenCalls_716) {
  // Boundary/error-ish case: dict without "Group".
  // We do NOT assume whether this yields nullptr or some inherited/default dict.
  auto *attrsDict = new Dict(nullptr);

  auto attrs = std::make_unique<PageAttrs>(nullptr, attrsDict);

  Object pageDictObj;
  Ref pageRef = MakeRef(3, 0);
  Page page(nullptr, 3, std::move(pageDictObj), pageRef, std::move(attrs));

  Dict *g1 = nullptr;
  Dict *g2 = nullptr;

  ASSERT_NO_FATAL_FAILURE({ g1 = page.getGroup(); });
  ASSERT_NO_FATAL_FAILURE({ g2 = page.getGroup(); });

  EXPECT_EQ(g1, g2);
}

TEST_F(PageGetGroupTest_716, ForwardingMatchesAttrsEvenAfterOtherCalls_716) {
  // Normal operation variation: call other public getters first (if available via Page),
  // then ensure getGroup still matches attrs->getGroup.
  auto *groupDict = new Dict(nullptr);
  auto *attrsDict = new Dict(nullptr);
  DictPut(attrsDict, "Group", MakeDictObject(groupDict));

  auto attrs = std::make_unique<PageAttrs>(nullptr, attrsDict);
  PageAttrs *attrsRaw = attrs.get();

  Object pageDictObj;
  Ref pageRef = MakeRef(4, 0);
  Page page(nullptr, 4, std::move(pageDictObj), pageRef, std::move(attrs));

  // We only call methods that are clearly public in the provided interface.
  // No assumptions about return values; just ensure no crash and forwarding still holds.
  (void)page.getRotate();
  (void)page.isCropped();
  (void)page.getMediaBox();

  EXPECT_EQ(page.getGroup(), attrsRaw->getGroup());
}