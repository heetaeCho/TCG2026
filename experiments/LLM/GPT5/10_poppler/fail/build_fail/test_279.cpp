// File: linkdest_getchangeleft_test.cpp
// TEST_ID: 279

#include <gtest/gtest.h>

#include "poppler/Link.h"

// These helpers are intentionally written to be tolerant of small Poppler API
// differences across versions (Object/Array construction & Array::add overloads).
// They do NOT assume LinkDest internal behavior; they only help build inputs.

namespace {

// -------- Object makers (SFINAE for old/new Poppler Object APIs) --------
template <typename T, typename = void>
struct HasInitNull : std::false_type {};
template <typename T>
struct HasInitNull<T, std::void_t<decltype(std::declval<T&>().initNull())>> : std::true_type {};

template <typename T, typename = void>
struct HasInitInt : std::false_type {};
template <typename T>
struct HasInitInt<T, std::void_t<decltype(std::declval<T&>().initInt(0))>> : std::true_type {};

template <typename T, typename = void>
struct HasInitReal : std::false_type {};
template <typename T>
struct HasInitReal<T, std::void_t<decltype(std::declval<T&>().initReal(0.0))>> : std::true_type {};

template <typename T, typename = void>
struct HasInitName : std::false_type {};
template <typename T>
struct HasInitName<T, std::void_t<decltype(std::declval<T&>().initName("XYZ"))>> : std::true_type {};

inline Object MakeNullObj() {
  Object o;
  if constexpr (HasInitNull<Object>::value) {
    o.initNull();
  } else {
    // Fallback for newer APIs that provide direct constructors.
    // If this doesn't compile in your Poppler revision, replace with the
    // appropriate "null object" constructor for your tree.
    o = Object(objNull);
  }
  return o;
}

inline Object MakeIntObj(int v) {
  Object o;
  if constexpr (HasInitInt<Object>::value) {
    o.initInt(v);
  } else {
    o = Object(objInt, v);
  }
  return o;
}

inline Object MakeRealObj(double v) {
  Object o;
  if constexpr (HasInitReal<Object>::value) {
    o.initReal(v);
  } else {
    o = Object(objReal, v);
  }
  return o;
}

inline Object MakeNameObj(const char* name) {
  Object o;
  if constexpr (HasInitName<Object>::value) {
    o.initName(name);
  } else {
    o = Object(objName, name);
  }
  return o;
}

// -------- Array helpers (ctor + add overload tolerance) --------
template <typename Arr, typename = void>
struct HasCtorWithXRef : std::false_type {};
template <typename Arr>
struct HasCtorWithXRef<Arr, std::void_t<decltype(Arr(static_cast<XRef*>(nullptr)))>> : std::true_type {};

template <typename Arr, typename Obj, typename = void>
struct HasAddRvalue : std::false_type {};
template <typename Arr, typename Obj>
struct HasAddRvalue<Arr, Obj, std::void_t<decltype(std::declval<Arr&>().add(std::declval<Obj&&>()))>>
    : std::true_type {};

template <typename Arr, typename Obj, typename = void>
struct HasAddLvalue : std::false_type {};
template <typename Arr, typename Obj>
struct HasAddLvalue<Arr, Obj, std::void_t<decltype(std::declval<Arr&>().add(std::declval<const Obj&>()))>>
    : std::true_type {};

inline Array MakeEmptyArray() {
  if constexpr (HasCtorWithXRef<Array>::value) {
    return Array(static_cast<XRef*>(nullptr));
  } else {
    return Array();
  }
}

inline void ArrayAdd(Array& a, Object&& o) {
  if constexpr (HasAddRvalue<Array, Object>::value) {
    a.add(std::move(o));
  } else if constexpr (HasAddLvalue<Array, Object>::value) {
    a.add(o);
  } else {
    // If your Poppler tree uses a different API (e.g., a.put(i, obj) or a.add(obj.copy())),
    // adapt this function accordingly.
    static_assert(sizeof(Array) == 0, "Unsupported Array::add API in this Poppler revision.");
  }
}

// Build a standard PDF destination array for /XYZ (page, /XYZ, left, top, zoom).
// This is based on the PDF destination format (external spec), not LinkDest internals.
inline Array MakeXYZDestArray(int pageNum, Object&& left, Object&& top, Object&& zoom) {
  Array a = MakeEmptyArray();
  ArrayAdd(a, MakeIntObj(pageNum));
  ArrayAdd(a, MakeNameObj("XYZ"));
  ArrayAdd(a, std::move(left));
  ArrayAdd(a, std::move(top));
  ArrayAdd(a, std::move(zoom));
  return a;
}

class LinkDestGetChangeLeftTest_279 : public ::testing::Test {};

}  // namespace

TEST_F(LinkDestGetChangeLeftTest_279, XYZWithNullLeftReportsNoChange_279) {
  Array a = MakeXYZDestArray(/*pageNum=*/1, MakeNullObj(), MakeNullObj(), MakeNullObj());
  LinkDest dest(a);

  // For a well-formed /XYZ destination where left is null (unspecified), change-left is expected false.
  ASSERT_TRUE(dest.isOk());
  EXPECT_FALSE(dest.getChangeLeft());
}

TEST_F(LinkDestGetChangeLeftTest_279, XYZWithNumericLeftReportsChange_279) {
  Array a = MakeXYZDestArray(/*pageNum=*/1, MakeRealObj(12.5), MakeNullObj(), MakeNullObj());
  LinkDest dest(a);

  ASSERT_TRUE(dest.isOk());
  EXPECT_TRUE(dest.getChangeLeft());
}

TEST_F(LinkDestGetChangeLeftTest_279, XYZWithZeroLeftStillReportsChange_279) {
  Array a = MakeXYZDestArray(/*pageNum=*/1, MakeRealObj(0.0), MakeNullObj(), MakeNullObj());
  LinkDest dest(a);

  ASSERT_TRUE(dest.isOk());
  EXPECT_TRUE(dest.getChangeLeft());
}

TEST_F(LinkDestGetChangeLeftTest_279, MalformedArrayIsNotOkAndGetterIsCallable_279) {
  Array a = MakeEmptyArray();  // Empty / malformed destination array
  LinkDest dest(a);

  // Observable error surface via isOk().
  EXPECT_FALSE(dest.isOk());

  // Even in an error state, the getter should be callable and return a bool.
  // (No value asserted to avoid inferring internal defaulting.)
  (void)dest.getChangeLeft();
  SUCCEED();
}