// File: page_getpageobj_test_722.cpp
// Unit tests for Page::getPageObj()
// TEST_ID: 722

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#if __has_include("poppler/Page.h")
#include "poppler/Page.h"
#else
#include "Page.h"
#endif

// Try to include common Poppler headers (best-effort; tests still compile if Page.h already includes them).
#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#endif
#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#endif
#if __has_include("poppler/Ref.h")
#include "poppler/Ref.h"
#endif
#if __has_include("poppler/PDFDoc.h")
#include "poppler/PDFDoc.h"
#endif

namespace {

class PageTest_722 : public ::testing::Test {};

// --- Compile-time interface tests (always safe; no assumptions about internals) ---

TEST_F(PageTest_722, ReturnTypeIsConstObjectRef_722) {
  static_assert(
      std::is_same<decltype(std::declval<const Page &>().getPageObj()), const Object &>::value,
      "Page::getPageObj() must return const Object&");
  SUCCEED();
}

TEST_F(PageTest_722, CallableOnConstInstance_722) {
  // If this compiles, it's callable on const Page& (as declared).
  (void)std::declval<const Page &>().getPageObj();
  SUCCEED();
}

// --- Optional runtime tests (only enabled when Page is constructible with the known ctor signature) ---

template <typename T, typename = void>
struct HasIsNull : std::false_type {};
template <typename T>
struct HasIsNull<T, std::void_t<decltype(std::declval<const T &>().isNull())>> : std::true_type {};

template <typename T, typename = void>
struct HasInitInt : std::false_type {};
template <typename T>
struct HasInitInt<T, std::void_t<decltype(std::declval<T &>().initInt(0))>> : std::true_type {};

template <typename T, typename = void>
struct HasIsInt : std::false_type {};
template <typename T>
struct HasIsInt<T, std::void_t<decltype(std::declval<const T &>().isInt())>> : std::true_type {};

template <typename T, typename = void>
struct HasGetInt : std::false_type {};
template <typename T>
struct HasGetInt<T, std::void_t<decltype(std::declval<const T &>().getInt())>> : std::true_type {};

constexpr bool kPageCtorAvailable =
    std::is_constructible<Page, PDFDoc *, int, Object &&, Ref, int>::value;

TEST_F(PageTest_722, GetPageObjDoesNotThrow_722) {
  if constexpr (!kPageCtorAvailable) {
    GTEST_SKIP() << "Skipping: Page(PDFDoc*, int, Object&&, Ref, int) not available in this build.";
  } else {
    Object pageDict;
    Ref ref{};
    Page page(/*docA=*/nullptr, /*numA=*/1, std::move(pageDict), ref, /*attrsA=*/0);
    EXPECT_NO_THROW((void)page.getPageObj());
  }
}

TEST_F(PageTest_722, ReturnedReferenceIsStableAcrossCalls_722) {
  if constexpr (!kPageCtorAvailable) {
    GTEST_SKIP() << "Skipping: Page(PDFDoc*, int, Object&&, Ref, int) not available in this build.";
  } else {
    Object pageDict;
    Ref ref{};
    Page page(/*docA=*/nullptr, /*numA=*/1, std::move(pageDict), ref, /*attrsA=*/0);

    const Object *p1 = &page.getPageObj();
    const Object *p2 = &page.getPageObj();
    EXPECT_EQ(p1, p2) << "getPageObj() should return a reference to the same Object each time.";
  }
}

TEST_F(PageTest_722, ReturnsNullWhenConstructedWithDefaultObjectIfObservable_722) {
  if constexpr (!kPageCtorAvailable) {
    GTEST_SKIP() << "Skipping: Page(PDFDoc*, int, Object&&, Ref, int) not available in this build.";
  } else if constexpr (!HasIsNull<Object>::value) {
    GTEST_SKIP() << "Skipping: Object::isNull() not available in this build.";
  } else {
    Object pageDict;  // default constructed
    Ref ref{};
    Page page(/*docA=*/nullptr, /*numA=*/1, std::move(pageDict), ref, /*attrsA=*/0);

    // Observable behavior only: check nullness via public Object API (if provided).
    EXPECT_TRUE(page.getPageObj().isNull());
  }
}

TEST_F(PageTest_722, PreservesObservableIntPayloadIfSupportedByObjectApi_722) {
  if constexpr (!kPageCtorAvailable) {
    GTEST_SKIP() << "Skipping: Page(PDFDoc*, int, Object&&, Ref, int) not available in this build.";
  } else if constexpr (!(HasInitInt<Object>::value && HasIsInt<Object>::value && HasGetInt<Object>::value)) {
    GTEST_SKIP() << "Skipping: Object int init/inspect API not available in this build.";
  } else {
    Object pageDict;
    pageDict.initInt(42);

    Ref ref{};
    Page page(/*docA=*/nullptr, /*numA=*/1, std::move(pageDict), ref, /*attrsA=*/0);

    const Object &out = page.getPageObj();
    ASSERT_TRUE(out.isInt());
    EXPECT_EQ(out.getInt(), 42);
  }
}

}  // namespace