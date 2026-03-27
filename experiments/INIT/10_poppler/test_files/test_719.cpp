// TEST_ID 719
// Unit tests for Page::getSeparationInfo()
// File: Page_getSeparationInfo_719_test.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "poppler/Page.h"

// Poppler headers commonly needed for Object/Dict/Ref factories (names may vary by version)
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/XRef.h"
#include "poppler/PDFDoc.h"

namespace {

// --- Small compatibility helpers (SFINAE) for different Poppler APIs ---

template <typename T, typename = void>
struct HasMakeDict : std::false_type {};
template <typename T>
struct HasMakeDict<T, std::void_t<decltype(T::makeDict(static_cast<XRef *>(nullptr)))>> : std::true_type {};

template <typename T, typename = void>
struct HasInitDict : std::false_type {};
template <typename T>
struct HasInitDict<T, std::void_t<decltype(std::declval<T &>().initDict(static_cast<XRef *>(nullptr)))>> : std::true_type {};

template <typename T, typename = void>
struct HasInitNull : std::false_type {};
template <typename T>
struct HasInitNull<T, std::void_t<decltype(std::declval<T &>().initNull())>> : std::true_type {};

inline Object MakeNullObject() {
  Object o;
  if constexpr (HasInitNull<Object>::value) {
    o.initNull();
    return o;
  } else {
    // Many Poppler versions default-construct to null-ish; keep it as-is.
    return o;
  }
}

inline Object MakeDictObject(XRef *xref) {
  if constexpr (HasMakeDict<Object>::value) {
    return Object::makeDict(xref);
  } else if constexpr (HasInitDict<Object>::value) {
    Object o;
    o.initDict(xref);
    return o;
  } else {
    // Fallback: create a null object (tests that require dict insertion will be skipped).
    return MakeNullObject();
  }
}

template <typename D, typename = void>
struct HasAddKV : std::false_type {};
template <typename D>
struct HasAddKV<D, std::void_t<decltype(std::declval<D *>()
                                           ->add(static_cast<const char *>(nullptr), std::declval<Object &&>()))>>
    : std::true_type {};

template <typename D, typename = void>
struct HasSetKV : std::false_type {};
template <typename D>
struct HasSetKV<D, std::void_t<decltype(std::declval<D *>()
                                           ->set(static_cast<const char *>(nullptr), std::declval<Object &&>()))>>
    : std::true_type {};

template <typename D>
inline void DictPut(D *dict, const char *key, Object &&val) {
  if constexpr (HasAddKV<D>::value) {
    dict->add(key, std::move(val));
  } else if constexpr (HasSetKV<D>::value) {
    dict->set(key, std::move(val));
  } else {
    // If we can't insert, tests depending on this should be skipped by caller.
    (void)dict;
    (void)key;
    (void)val;
  }
}

inline bool CanInsertIntoDict() {
  return HasAddKV<Dict>::value || HasSetKV<Dict>::value;
}

// Avoid invoking Page::~Page() in case it expects a fully valid PDFDoc/XRef environment.
struct NoDelete {
  void operator()(Page *p) const noexcept { (void)p; }
};

inline Ref MakeRef(int num, int gen) {
  Ref r;
  r.num = num;
  r.gen = gen;
  return r;
}

class PageGetSeparationInfoTest_719 : public ::testing::Test {
protected:
  XRef *xref_ = nullptr;  // We intentionally keep these null; tests target forwarding behavior only.
  PDFDoc *doc_ = nullptr;
};

}  // namespace

TEST_F(PageGetSeparationInfoTest_719, ForwardsReturnValueFromAttrs_719) {
  if (!CanInsertIntoDict()) {
    GTEST_SKIP() << "Poppler Dict does not expose add/set(Object&&) in this build; cannot construct SeparationInfo.";
  }

  // Build a minimal page dictionary (not used by getSeparationInfo(), but required by Page ctor).
  Object pageDict = MakeDictObject(xref_);
  if (!pageDict.isDict()) {
    GTEST_SKIP() << "Unable to create a Dict Object with this Poppler Object API.";
  }

  // Build an attrs dict containing /SeparationInfo << ... >>
  auto *attrsDict = new Dict(xref_);
  Object sepInfo = MakeDictObject(xref_);
  if (!sepInfo.isDict()) {
    GTEST_SKIP() << "Unable to create SeparationInfo dict object with this Poppler Object API.";
  }
  DictPut(attrsDict, "SeparationInfo", std::move(sepInfo));

  // Create PageAttrs from the dict and inject into Page.
  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, /*dict=*/attrsDict);
  PageAttrs *rawAttrs = attrs.get();

  // Construct a Page with provided attrs.
  const int pageNum = 1;
  Ref pageRef = MakeRef(/*num=*/1, /*gen=*/0);

  std::unique_ptr<Page, NoDelete> page(
      new Page(doc_, pageNum, std::move(pageDict), pageRef, std::move(attrs)));

  // Observable behavior: Page::getSeparationInfo() should match what the injected PageAttrs returns.
  Dict *fromAttrs = rawAttrs->getSeparationInfo();
  Dict *fromPage = page->getSeparationInfo();

  EXPECT_EQ(fromPage, fromAttrs);
}

TEST_F(PageGetSeparationInfoTest_719, ReturnsNullWhenAttrsReturnsNull_719) {
  // This test only needs PageAttrs to exist; no need to insert SeparationInfo.
  Object pageDict = MakeDictObject(xref_);
  if (!pageDict.isDict()) {
    GTEST_SKIP() << "Unable to create a Dict Object with this Poppler Object API.";
  }

  auto *attrsDict = new Dict(xref_);
  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, /*dict=*/attrsDict);
  PageAttrs *rawAttrs = attrs.get();

  const int pageNum = 1;
  Ref pageRef = MakeRef(/*num=*/1, /*gen=*/0);

  std::unique_ptr<Page, NoDelete> page(
      new Page(doc_, pageNum, std::move(pageDict), pageRef, std::move(attrs)));

  Dict *fromAttrs = rawAttrs->getSeparationInfo();
  Dict *fromPage = page->getSeparationInfo();

  // Boundary / error-ish case: missing SeparationInfo should be consistently observed through Page.
  EXPECT_EQ(fromAttrs, nullptr);
  EXPECT_EQ(fromPage, nullptr);
}

TEST_F(PageGetSeparationInfoTest_719, RepeatedCallsAreConsistent_719) {
  if (!CanInsertIntoDict()) {
    GTEST_SKIP() << "Poppler Dict does not expose add/set(Object&&) in this build; cannot construct SeparationInfo.";
  }

  Object pageDict = MakeDictObject(xref_);
  if (!pageDict.isDict()) {
    GTEST_SKIP() << "Unable to create a Dict Object with this Poppler Object API.";
  }

  auto *attrsDict = new Dict(xref_);
  Object sepInfo = MakeDictObject(xref_);
  if (!sepInfo.isDict()) {
    GTEST_SKIP() << "Unable to create SeparationInfo dict object with this Poppler Object API.";
  }
  DictPut(attrsDict, "SeparationInfo", std::move(sepInfo));

  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, /*dict=*/attrsDict);
  PageAttrs *rawAttrs = attrs.get();

  const int pageNum = 1;
  Ref pageRef = MakeRef(/*num=*/1, /*gen=*/0);

  std::unique_ptr<Page, NoDelete> page(
      new Page(doc_, pageNum, std::move(pageDict), pageRef, std::move(attrs)));

  Dict *a1 = rawAttrs->getSeparationInfo();
  Dict *p1 = page->getSeparationInfo();
  Dict *p2 = page->getSeparationInfo();

  EXPECT_EQ(p1, a1);
  EXPECT_EQ(p2, a1);
  EXPECT_EQ(p2, p1);
}