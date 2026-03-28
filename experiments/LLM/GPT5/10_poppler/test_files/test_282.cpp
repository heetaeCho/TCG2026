// TEST_ID = 282
// Unit tests for LinkGoTo::isOk() and related observable behavior.
// File: LinkGoTo_isOk_282_test.cpp

#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"
#include "goo/GooString.h"

#include <type_traits>
#include <utility>

namespace {

// ---- Minimal compile-time adapters for different Poppler Object APIs ----

template <typename...>
using void_t = void;

template <typename T, typename = void>
struct HasInitNull : std::false_type {};
template <typename T>
struct HasInitNull<T, void_t<decltype(std::declval<T&>().initNull())>> : std::true_type {};

template <typename T, typename = void>
struct HasInitInt : std::false_type {};
template <typename T>
struct HasInitInt<T, void_t<decltype(std::declval<T&>().initInt(0))>> : std::true_type {};

template <typename T, typename = void>
struct HasInitString : std::false_type {};
template <typename T>
struct HasInitString<T, void_t<decltype(std::declval<T&>().initString((GooString*)nullptr))>> : std::true_type {};

// Some Poppler trees use constructors like Object(objNull), Object(objInt, v), Object(objString, GooString*)
enum ObjTypeCompat {
  // These names match older Poppler, but may not exist in every tree.
  // We only use them in unevaluated contexts / guarded code paths.
  objNullCompat = 0,
  objIntCompat = 1,
  objStringCompat = 2,
};

static Object MakeNullObject() {
  Object o;
  if constexpr (HasInitNull<Object>::value) {
    o.initNull();
    return o;
  } else {
    // Fallback: try older constructor form (best-effort).
    // If your Poppler tree doesn't support this, prefer enabling initNull().
    return Object(objNullCompat);
  }
}

static Object MakeIntObject(int v) {
  Object o;
  if constexpr (HasInitInt<Object>::value) {
    o.initInt(v);
    return o;
  } else {
    return Object(objIntCompat, v);
  }
}

static Object MakeStringObject(const char* s) {
  Object o;
  GooString* gs = new GooString(s);
  if constexpr (HasInitString<Object>::value) {
    o.initString(gs); // Object takes ownership in typical Poppler APIs
    return o;
  } else {
    return Object(objStringCompat, gs);
  }
}

class LinkGoToTest_282 : public ::testing::Test {};

} // namespace

TEST_F(LinkGoToTest_282, NullObject_YieldsNotOkAndNoDestPointers_282) {
  Object obj = MakeNullObject();
  LinkGoTo action(&obj);

  EXPECT_FALSE(action.isOk());
  EXPECT_EQ(action.getDest(), nullptr);
  EXPECT_EQ(action.getNamedDest(), nullptr);
}

TEST_F(LinkGoToTest_282, IntObject_YieldsNotOkAndNoDestPointers_282) {
  Object obj = MakeIntObject(123);
  LinkGoTo action(&obj);

  EXPECT_FALSE(action.isOk());
  EXPECT_EQ(action.getDest(), nullptr);
  EXPECT_EQ(action.getNamedDest(), nullptr);
}

TEST_F(LinkGoToTest_282, StringObject_YieldsOkAndProvidesNamedDest_282) {
  Object obj = MakeStringObject("Chapter1");
  LinkGoTo action(&obj);

  EXPECT_TRUE(action.isOk());
  EXPECT_NE(action.getNamedDest(), nullptr);

  // Observable contract: isOk() is true when either dest or namedDest is present.
  // We don't assume whether a string also produces a LinkDest.
  EXPECT_TRUE(action.getDest() != nullptr || action.getNamedDest() != nullptr);
}

TEST_F(LinkGoToTest_282, EmptyStringObject_BoundaryStillOkAndNamedDestNonNull_282) {
  Object obj = MakeStringObject("");
  LinkGoTo action(&obj);

  EXPECT_TRUE(action.isOk());
  EXPECT_NE(action.getNamedDest(), nullptr);
}

TEST_F(LinkGoToTest_282, GetKind_IsStableAcrossInputs_282) {
  // We don't assume a specific enum value; we only verify that getKind() is callable
  // and returns a consistent value for this action type regardless of construction input.
  Object nullObj = MakeNullObject();
  Object strObj = MakeStringObject("DestName");

  LinkGoTo a(&nullObj);
  LinkGoTo b(&strObj);

  const auto kindA = a.getKind();
  const auto kindB = b.getKind();

  EXPECT_EQ(kindA, kindB);
}

TEST_F(LinkGoToTest_282, ConstAccessors_AreCallableAndConsistentWithIsOk_282) {
  Object obj = MakeStringObject("NamedDest");
  const LinkGoTo action(&obj);

  const bool ok = action.isOk();
  const bool hasAny = (action.getDest() != nullptr) || (action.getNamedDest() != nullptr);

  EXPECT_EQ(ok, hasAny);
}