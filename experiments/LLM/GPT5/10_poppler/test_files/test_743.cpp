// File: test_annotbordereffect_743.cpp
// TEST_ID: 743

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>
#include <utility>

#include "poppler/Annot.h"
#include "poppler/Object.h"

// These tests treat AnnotBorderEffect as a black box.
// They only verify observable behavior via the public interface and that construction
// from various Dict inputs is robust (no-throw where applicable).

namespace {

// ---- SFINAE helpers to support multiple Poppler Object/Dict APIs across versions ----

template <typename T, typename = void>
struct has_initName : std::false_type {};
template <typename T>
struct has_initName<T, std::void_t<decltype(std::declval<T&>().initName(""))>> : std::true_type {};

template <typename T, typename = void>
struct has_initReal : std::false_type {};
template <typename T>
struct has_initReal<T, std::void_t<decltype(std::declval<T&>().initReal(0.0))>> : std::true_type {};

template <typename T, typename = void>
struct has_initNum : std::false_type {};
template <typename T>
struct has_initNum<T, std::void_t<decltype(std::declval<T&>().initNum(0))>> : std::true_type {};

template <typename D, typename O, typename = void>
struct has_add_key_obj : std::false_type {};
template <typename D, typename O>
struct has_add_key_obj<D, O, std::void_t<decltype(std::declval<D&>().add("", std::declval<O&&>()))>>
    : std::true_type {};

template <typename D, typename O, typename = void>
struct has_set_key_obj : std::false_type {};
template <typename D, typename O>
struct has_set_key_obj<D, O, std::void_t<decltype(std::declval<D&>().set("", std::declval<O&&>()))>>
    : std::true_type {};

static Object MakeNameObj(const char* name) {
  Object obj;
  if constexpr (has_initName<Object>::value) {
    obj.initName(name);
    return obj;
  } else {
    // Older API: Object(Type, const char*)
    return Object(objName, const_cast<char*>(name));
  }
}

static Object MakeRealObj(double v) {
  Object obj;
  if constexpr (has_initReal<Object>::value) {
    obj.initReal(v);
    return obj;
  } else {
    // Older API: Object(Type, double)
    return Object(objReal, v);
  }
}

static Object MakeIntObj(int v) {
  Object obj;
  if constexpr (has_initNum<Object>::value) {
    obj.initNum(v);
    return obj;
  } else {
    // Older API: Object(Type, int)
    return Object(objInt, v);
  }
}

static void DictPut(Dict& d, const char* key, Object&& value) {
  if constexpr (has_add_key_obj<Dict, Object>::value) {
    d.add(key, std::move(value));
  } else if constexpr (has_set_key_obj<Dict, Object>::value) {
    d.set(key, std::move(value));
  } else {
    // If neither API exists, compilation will fail here (signals an incompatible Poppler API).
    d.add(key, std::move(value));
  }
}

static bool IsFinite(double x) {
  return std::isfinite(x) != 0;
}

}  // namespace

class AnnotBorderEffectTest_743 : public ::testing::Test {
 protected:
  // Creates a Dict suitable for passing to AnnotBorderEffect(Dict*)
  // Keys commonly used in PDF border effect dictionaries include:
  //  - "S" (name): effect style
  //  - "I" (number): intensity
  //
  // We do NOT assert specific semantic mappings; we only ensure construction is robust and
  // getters are callable and stable.
  static Dict MakeBorderEffectDict(const char* styleName, bool includeIntensity, double intensity) {
    Dict d(nullptr);

    if (styleName) {
      DictPut(d, "S", MakeNameObj(styleName));
    }
    if (includeIntensity) {
      DictPut(d, "I", MakeRealObj(intensity));
    }
    return d;
  }
};

TEST_F(AnnotBorderEffectTest_743, ConstructWithEmptyDict_AllowsGetters_743) {
  Dict d(nullptr);

  // Black-box: only verify that construction and getter calls are safe/observable.
  EXPECT_NO_THROW({
    AnnotBorderEffect be(&d);
    (void)be.getEffectType();
    (void)be.getIntensity();
  });
}

TEST_F(AnnotBorderEffectTest_743, GetEffectType_IsStableAcrossMultipleCalls_743) {
  Dict d = MakeBorderEffectDict("S", /*includeIntensity=*/false, 0.0);

  AnnotBorderEffect be(&d);

  const auto first = be.getEffectType();
  const auto second = be.getEffectType();
  const auto third = be.getEffectType();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(AnnotBorderEffectTest_743, ConstructWithKnownStyleName_DoesNotThrow_743) {
  // Use a commonly-seen style name key; we do not rely on any specific mapping.
  Dict d = MakeBorderEffectDict("C", /*includeIntensity=*/true, 1.0);

  EXPECT_NO_THROW({
    AnnotBorderEffect be(&d);
    (void)be.getEffectType();
  });
}

TEST_F(AnnotBorderEffectTest_743, ConstructWithUnknownStyleName_IsRobust_743) {
  Dict d = MakeBorderEffectDict("BogusStyleName", /*includeIntensity=*/true, 0.5);

  EXPECT_NO_THROW({
    AnnotBorderEffect be(&d);
    // We do not assume how unknown styles are handled; only that getters are callable.
    (void)be.getEffectType();
    (void)be.getIntensity();
  });
}

TEST_F(AnnotBorderEffectTest_743, GetIntensity_ReturnsFiniteForTypicalValues_743) {
  // Typical values around 0..2 (not asserted), just ensure finiteness and callability.
  Dict d0 = MakeBorderEffectDict("S", /*includeIntensity=*/true, 0.0);
  Dict d1 = MakeBorderEffectDict("S", /*includeIntensity=*/true, 1.0);
  Dict d2 = MakeBorderEffectDict("S", /*includeIntensity=*/true, 2.0);

  AnnotBorderEffect be0(&d0);
  AnnotBorderEffect be1(&d1);
  AnnotBorderEffect be2(&d2);

  EXPECT_TRUE(IsFinite(be0.getIntensity()));
  EXPECT_TRUE(IsFinite(be1.getIntensity()));
  EXPECT_TRUE(IsFinite(be2.getIntensity()));
}

TEST_F(AnnotBorderEffectTest_743, GetIntensity_IsFiniteForExtremeInputs_743) {
  // Boundary-ish: large magnitude and negative values. We do not assume clamping behavior.
  Dict dNeg = MakeBorderEffectDict("C", /*includeIntensity=*/true, -12345.0);
  Dict dHuge = MakeBorderEffectDict("C", /*includeIntensity=*/true, 1e308);

  AnnotBorderEffect beNeg(&dNeg);
  AnnotBorderEffect beHuge(&dHuge);

  EXPECT_TRUE(IsFinite(beNeg.getIntensity()));
  EXPECT_TRUE(IsFinite(beHuge.getIntensity()));
}

TEST_F(AnnotBorderEffectTest_743, MissingIntensityKey_DoesNotThrowAndIsFinite_743) {
  Dict d = MakeBorderEffectDict("S", /*includeIntensity=*/false, 0.0);

  AnnotBorderEffect be(&d);

  // Do not assume the default; only verify it is a usable number.
  EXPECT_TRUE(IsFinite(be.getIntensity()));
}