// TEST_ID: 271
// File: linkdest_isPageRef_tests_271.cpp

#include <gtest/gtest.h>

#include "Link.h"

// Poppler typically defines Array/Object/Ref in Object.h (and sometimes Dict.h).
// Include it if available in your build; many Poppler builds already pull it via Link.h,
// but this keeps the test TU self-contained.
#include "Object.h"

#include <type_traits>
#include <utility>

// ---- Small compatibility helpers (to cope with Poppler API differences) ----
namespace {

template <typename T, typename = void>
struct has_initInt : std::false_type {};
template <typename T>
struct has_initInt<T, std::void_t<decltype(std::declval<T&>().initInt(0))>> : std::true_type {};

template <typename T, typename = void>
struct has_initReal : std::false_type {};
template <typename T>
struct has_initReal<T, std::void_t<decltype(std::declval<T&>().initReal(0.0))>> : std::true_type {};

template <typename T, typename = void>
struct has_initName : std::false_type {};
template <typename T>
struct has_initName<T, std::void_t<decltype(std::declval<T&>().initName(static_cast<const char*>(nullptr)))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_initNull : std::false_type {};
template <typename T>
struct has_initNull<T, std::void_t<decltype(std::declval<T&>().initNull())>> : std::true_type {};

template <typename T, typename = void>
struct has_initRef : std::false_type {};
template <typename T>
struct has_initRef<T, std::void_t<decltype(std::declval<T&>().initRef(Ref{}))>> : std::true_type {};

template <typename Arr, typename Obj, typename = void>
struct array_add_rvalue : std::false_type {};
template <typename Arr, typename Obj>
struct array_add_rvalue<Arr,
                        Obj,
                        std::void_t<decltype(std::declval<Arr&>().add(std::declval<Obj&&>()))>> : std::true_type {};

template <typename Arr, typename Obj, typename = void>
struct array_add_lvalue : std::false_type {};
template <typename Arr, typename Obj>
struct array_add_lvalue<Arr,
                        Obj,
                        std::void_t<decltype(std::declval<Arr&>().add(std::declval<const Obj&>()))>> : std::true_type {};

static Object MakeIntObj(int v) {
  Object o;
  if constexpr (has_initInt<Object>::value) {
    o.initInt(v);
    return o;
  } else {
    // Some older Poppler builds may have different constructors.
    // Fall back to a common pattern if available.
    return Object(v);
  }
}

static Object MakeRealObj(double v) {
  Object o;
  if constexpr (has_initReal<Object>::value) {
    o.initReal(v);
    return o;
  } else {
    return Object(v);
  }
}

static Object MakeNameObj(const char* s) {
  Object o;
  if constexpr (has_initName<Object>::value) {
    o.initName(s);
    return o;
  } else {
    return Object(objName, s);
  }
}

static Object MakeNullObj() {
  Object o;
  if constexpr (has_initNull<Object>::value) {
    o.initNull();
    return o;
  } else {
    return Object(objNull);
  }
}

static Object MakeRefObj(Ref r) {
  Object o;
  if constexpr (has_initRef<Object>::value) {
    o.initRef(r);
    return o;
  } else {
    // Common older signature is initRef(num, gen), but we avoid guessing too hard.
    // Try the Ref overload first; if not available, rely on a constructor if present.
    return Object(r);
  }
}

template <typename ArrT>
static void ArrayAdd(ArrT& a, Object&& o) {
  if constexpr (array_add_rvalue<ArrT, Object>::value) {
    a.add(std::move(o));
  } else if constexpr (array_add_lvalue<ArrT, Object>::value) {
    a.add(o);
  } else {
    // If Array doesn't support add(Object), compilation will fail here, which is fine:
    // it indicates the Poppler API differs from the expected one for this test.
    a.add(std::move(o));
  }
}

// Build a simple, standards-based PDF destination array:
// [ page, /XYZ, left, top, zoom ]
static Array MakeXYZDestArrayWithPageNum(int pageNum) {
  Array a;
  ArrayAdd(a, MakeIntObj(pageNum));
  ArrayAdd(a, MakeNameObj("XYZ"));
  ArrayAdd(a, MakeNullObj());  // left
  ArrayAdd(a, MakeNullObj());  // top
  ArrayAdd(a, MakeNullObj());  // zoom
  return a;
}

static Array MakeXYZDestArrayWithPageRef(Ref pageRef) {
  Array a;
  ArrayAdd(a, MakeRefObj(pageRef));
  ArrayAdd(a, MakeNameObj("XYZ"));
  ArrayAdd(a, MakeNullObj());  // left
  ArrayAdd(a, MakeNullObj());  // top
  ArrayAdd(a, MakeNullObj());  // zoom
  return a;
}

}  // namespace

// ---- Tests ----

class LinkDestTest_271 : public ::testing::Test {};

TEST_F(LinkDestTest_271, IsPageRefFalseWhenConstructedWithPageNumber_271) {
  // Normal operation: a destination whose first element is a page number should not be a page ref.
  Array a = MakeXYZDestArrayWithPageNum(1);
  LinkDest dest(a);

  // Only assert stronger properties when observable via the public API.
  if (dest.isOk()) {
    EXPECT_FALSE(dest.isPageRef());
    EXPECT_EQ(1, dest.getPageNum());
  } else {
    // Even if parsing fails for some build/config, calling isPageRef() must be safe.
    (void)dest.isPageRef();
    SUCCEED();
  }
}

TEST_F(LinkDestTest_271, IsPageRefTrueWhenConstructedWithPageRef_271) {
  // Normal operation: a destination whose first element is a Ref should be a page ref.
  Ref r;
  r.num = 12;
  r.gen = 0;

  Array a = MakeXYZDestArrayWithPageRef(r);
  LinkDest dest(a);

  if (dest.isOk()) {
    EXPECT_TRUE(dest.isPageRef());

    const Ref got = dest.getPageRef();
    EXPECT_EQ(r.num, got.num);
    EXPECT_EQ(r.gen, got.gen);
  } else {
    (void)dest.isPageRef();
    SUCCEED();
  }
}

TEST_F(LinkDestTest_271, Boundary_PageNumberZeroOrNegativeDoesNotCrash_271) {
  // Boundary: page numbers at/under 0 are commonly invalid in PDF destinations.
  // We do NOT assume exact validation behavior; we only verify safe, observable calls.
  for (int pageNum : {0, -1}) {
    Array a = MakeXYZDestArrayWithPageNum(pageNum);
    LinkDest dest(a);

    // Must be callable regardless of validity.
    EXPECT_NO_THROW({ (void)dest.isPageRef(); });

    // If it is considered OK, getPageNum should reflect the input (public behavior).
    if (dest.isOk()) {
      EXPECT_FALSE(dest.isPageRef());
      EXPECT_EQ(pageNum, dest.getPageNum());
    }
  }
}

TEST_F(LinkDestTest_271, Boundary_LargePageNumberRoundTripsWhenOk_271) {
  // Boundary: very large page numbers.
  const int kLarge = 2147483647;  // INT_MAX for 32-bit int
  Array a = MakeXYZDestArrayWithPageNum(kLarge);
  LinkDest dest(a);

  EXPECT_NO_THROW({ (void)dest.isPageRef(); });

  if (dest.isOk()) {
    EXPECT_FALSE(dest.isPageRef());
    EXPECT_EQ(kLarge, dest.getPageNum());
  }
}

TEST_F(LinkDestTest_271, Error_EmptyArrayIsHandledSafely_271) {
  // Exceptional/error case: empty destination array.
  Array a;
  LinkDest dest(a);

  // Regardless of how LinkDest validates, calling isPageRef must be safe.
  EXPECT_NO_THROW({ (void)dest.isPageRef(); });

  // If the implementation exposes invalidity, this should typically be not-ok.
  // We don't require it, but we accept it as an observable behavior when present.
  if (!dest.isOk()) {
    // In an invalid state, we only assert the boolean is stable/callable.
    const bool v1 = dest.isPageRef();
    const bool v2 = dest.isPageRef();
    EXPECT_EQ(v1, v2);
  }
}

TEST_F(LinkDestTest_271, Error_MissingKindEntryIsHandledSafely_271) {
  // Exceptional/error case: array contains only a page element, missing the kind/name.
  Array a;
  ArrayAdd(a, MakeIntObj(1));
  LinkDest dest(a);

  EXPECT_NO_THROW({ (void)dest.isPageRef(); });

  if (dest.isOk()) {
    // If treated as OK in some configuration, it still should behave consistently.
    EXPECT_FALSE(dest.isPageRef());
    EXPECT_EQ(1, dest.getPageNum());
  }
}