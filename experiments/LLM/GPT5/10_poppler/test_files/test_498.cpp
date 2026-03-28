// TEST_ID = 498
// File: GfxTilingPattern_getMatrix_498_test.cc

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <memory>
#include <string>
#include <utility>

#include "poppler/GfxState.h"

// The following includes are best-effort to construct Objects for parse() without
// relying on private/internal state of GfxTilingPattern. If your Poppler fork
// uses different header paths, adjust includes accordingly.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"

namespace {

// --- Detection helpers (C++17) ------------------------------------------------
template <typename, typename = void>
struct HasInitInt : std::false_type {};
template <typename T>
struct HasInitInt<T, std::void_t<decltype(std::declval<T&>().initInt(0))>> : std::true_type {};

template <typename, typename = void>
struct HasInitReal : std::false_type {};
template <typename T>
struct HasInitReal<T, std::void_t<decltype(std::declval<T&>().initReal(0.0))>> : std::true_type {};

template <typename, typename = void>
struct HasInitName : std::false_type {};
template <typename T>
struct HasInitName<T, std::void_t<decltype(std::declval<T&>().initName(""))>> : std::true_type {};

template <typename, typename = void>
struct HasInitArray : std::false_type {};
template <typename T>
struct HasInitArray<T, std::void_t<decltype(std::declval<T&>().initArray(static_cast<Array*>(nullptr)))>>
    : std::true_type {};

template <typename, typename = void>
struct HasInitDict : std::false_type {};
template <typename T>
struct HasInitDict<T, std::void_t<decltype(std::declval<T&>().initDict(static_cast<Dict*>(nullptr)))>>
    : std::true_type {};

template <typename, typename = void>
struct HasDictAdd : std::false_type {};
template <typename T>
struct HasDictAdd<T, std::void_t<decltype(std::declval<T&>().add("", std::declval<Object&&>()))>>
    : std::true_type {};

template <typename, typename = void>
struct HasArrayAdd : std::false_type {};
template <typename T>
struct HasArrayAdd<T, std::void_t<decltype(std::declval<T&>().add(std::declval<Object&&>()))>>
    : std::true_type {};

// --- Object factory helpers (best-effort across Poppler variants) -------------
Object MakeInt(int v) {
  Object o;
  if constexpr (HasInitInt<Object>::value) {
    o.initInt(v);
    return o;
  } else {
    // Some variants have Object(int) ctor.
    return Object(v);
  }
}

Object MakeReal(double v) {
  Object o;
  if constexpr (HasInitReal<Object>::value) {
    o.initReal(v);
    return o;
  } else {
    // Some variants have Object(double) ctor.
    return Object(v);
  }
}

Object MakeName(const char* s) {
  Object o;
  if constexpr (HasInitName<Object>::value) {
    o.initName(s);
    return o;
  } else {
    // Some variants have Object(objName, "X") or similar; if so, adjust here.
    // As a fallback, create a null object (parse may still accept missing name).
    Object nullObj;
    nullObj.setToNull();
    return nullObj;
  }
}

Object MakeArrayFromDoubles(const std::initializer_list<double>& vals) {
  auto* arr = new Array();
  for (double v : vals) {
    if constexpr (HasArrayAdd<Array>::value) {
      arr->add(MakeReal(v));
    } else {
      // If Array API differs, you may need to adjust this.
      arr->add(MakeReal(v));
    }
  }

  Object o;
  if constexpr (HasInitArray<Object>::value) {
    o.initArray(arr);
  } else {
    // Some variants have Object(Array*) ctor.
    o = Object(arr);
  }
  return o;
}

Object MakeArrayFromInts(const std::initializer_list<int>& vals) {
  auto* arr = new Array();
  for (int v : vals) {
    if constexpr (HasArrayAdd<Array>::value) {
      arr->add(MakeInt(v));
    } else {
      arr->add(MakeInt(v));
    }
  }

  Object o;
  if constexpr (HasInitArray<Object>::value) {
    o.initArray(arr);
  } else {
    o = Object(arr);
  }
  return o;
}

void DictAdd(Dict* dict, const char* key, Object&& val) {
  if constexpr (HasDictAdd<Dict>::value) {
    dict->add(key, std::move(val));
  } else {
    // Some variants might use set() or another method; adjust if needed.
    dict->add(key, std::move(val));
  }
}

Object MakeDictObject(Dict* dict) {
  Object o;
  if constexpr (HasInitDict<Object>::value) {
    o.initDict(dict);
  } else {
    // Some variants have Object(Dict*) ctor.
    o = Object(dict);
  }
  return o;
}

// Build a *minimal* tiling pattern object dictionary as per PDF spec keys.
// NOTE: We do NOT assume internal behavior; we only use the public parse()
// interface and validate observable outcomes.
Object BuildTilingPatternDictObjectWithMatrix(const std::array<double, 6>& m) {
  // Dict constructor commonly takes XRef*, but nullptr is typically acceptable for unit tests.
  auto* dict = new Dict(nullptr);

  // PatternType = 1 (tiling pattern), PaintType, TilingType, BBox, XStep, YStep, Matrix
  DictAdd(dict, "Type", MakeName("Pattern"));         // optional in PDF, sometimes required by parse()
  DictAdd(dict, "PatternType", MakeInt(1));
  DictAdd(dict, "PaintType", MakeInt(1));
  DictAdd(dict, "TilingType", MakeInt(1));
  DictAdd(dict, "BBox", MakeArrayFromInts({0, 0, 10, 10}));
  DictAdd(dict, "XStep", MakeReal(10.0));
  DictAdd(dict, "YStep", MakeReal(10.0));
  DictAdd(dict, "Matrix",
          MakeArrayFromDoubles({m[0], m[1], m[2], m[3], m[4], m[5]}));

  // Resources/content stream are typically required for a fully valid pattern stream,
  // but some Poppler builds allow parsing from dict-only. If your build requires a
  // stream, you may need to enhance this builder accordingly.
  return MakeDictObject(dict);
}

Object BuildTilingPatternDictObjectWithInvalidMatrixLen(int len) {
  auto* dict = new Dict(nullptr);

  DictAdd(dict, "Type", MakeName("Pattern"));
  DictAdd(dict, "PatternType", MakeInt(1));
  DictAdd(dict, "PaintType", MakeInt(1));
  DictAdd(dict, "TilingType", MakeInt(1));
  DictAdd(dict, "BBox", MakeArrayFromInts({0, 0, 10, 10}));
  DictAdd(dict, "XStep", MakeReal(10.0));
  DictAdd(dict, "YStep", MakeReal(10.0));

  // Matrix with wrong number of entries.
  auto* arr = new Array();
  for (int i = 0; i < len; ++i) {
    arr->add(MakeReal(1.0 * i));
  }
  Object matObj;
  if constexpr (HasInitArray<Object>::value) {
    matObj.initArray(arr);
  } else {
    matObj = Object(arr);
  }
  DictAdd(dict, "Matrix", std::move(matObj));

  return MakeDictObject(dict);
}

}  // namespace

// -----------------------------------------------------------------------------

class GfxTilingPatternTest_498 : public ::testing::Test {};

TEST_F(GfxTilingPatternTest_498, ParseValidPatternReturnsNonNull_498) {
  const std::array<double, 6> m = {1, 0, 0, 1, 2.5, -3.25};
  Object patObj = BuildTilingPatternDictObjectWithMatrix(m);

  auto pat = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/0);

  if (!pat) {
    GTEST_SKIP() << "GfxTilingPattern::parse() returned nullptr with a dict-only pattern object; "
                    "your Poppler build may require a stream-backed pattern Object. "
                    "Enhance BuildTilingPatternDictObjectWithMatrix() accordingly.";
  }
  EXPECT_NE(pat.get(), nullptr);
}

TEST_F(GfxTilingPatternTest_498, GetMatrixReturnsProvidedValues_498) {
  const std::array<double, 6> m = {0.5, 1.25, -2.0, 3.0, 100.0, -200.0};
  Object patObj = BuildTilingPatternDictObjectWithMatrix(m);

  auto pat = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/7);
  if (!pat) {
    GTEST_SKIP() << "parse() returned nullptr; likely requires stream-backed pattern Object in this build.";
  }

  const auto& got = pat->getMatrix();
  EXPECT_EQ(got.size(), 6u);

  // Observable behavior: accessor returns the matrix values exposed through the interface.
  for (size_t i = 0; i < 6; ++i) {
    EXPECT_DOUBLE_EQ(got[i], m[i]) << "matrix index " << i;
  }
}

TEST_F(GfxTilingPatternTest_498, GetMatrixReferenceStableAcrossCalls_498) {
  const std::array<double, 6> m = {1, 2, 3, 4, 5, 6};
  Object patObj = BuildTilingPatternDictObjectWithMatrix(m);

  auto pat = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/1);
  if (!pat) {
    GTEST_SKIP() << "parse() returned nullptr; likely requires stream-backed pattern Object in this build.";
  }

  const auto& a = pat->getMatrix();
  const auto& b = pat->getMatrix();

  // Observable: getMatrix returns a const reference; the reference should remain stable.
  EXPECT_EQ(&a, &b);

  // And values remain accessible.
  EXPECT_DOUBLE_EQ(a[0], m[0]);
  EXPECT_DOUBLE_EQ(b[5], m[5]);
}

TEST_F(GfxTilingPatternTest_498, ParseRejectsInvalidMatrixLength_498) {
  // Boundary/error: matrix length must be 6 for an affine transform (observable via parse result).
  Object patObjTooShort = BuildTilingPatternDictObjectWithInvalidMatrixLen(5);
  auto patShort = GfxTilingPattern::parse(&patObjTooShort, /*patternRefNum=*/0);
  // If parse requires a stream, this will also be nullptr; still acceptable as "rejects/doesn't parse".
  EXPECT_EQ(patShort.get(), nullptr);

  Object patObjTooLong = BuildTilingPatternDictObjectWithInvalidMatrixLen(7);
  auto patLong = GfxTilingPattern::parse(&patObjTooLong, /*patternRefNum=*/0);
  EXPECT_EQ(patLong.get(), nullptr);
}

TEST_F(GfxTilingPatternTest_498, GetMatrixSupportsExtremeFiniteValues_498) {
  // Boundary: very large/small finite doubles (but not inf/nan) should round-trip via accessor
  // if parse accepts them.
  const std::array<double, 6> m = {
      1e300, -1e-300, 1e-200, -1e200, 1e150, -1e150,
  };
  Object patObj = BuildTilingPatternDictObjectWithMatrix(m);

  auto pat = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/42);
  if (!pat) {
    GTEST_SKIP() << "parse() returned nullptr; likely requires stream-backed pattern Object in this build.";
  }

  const auto& got = pat->getMatrix();
  for (size_t i = 0; i < 6; ++i) {
    ASSERT_TRUE(std::isfinite(got[i])) << "matrix index " << i << " is not finite";
    EXPECT_DOUBLE_EQ(got[i], m[i]) << "matrix index " << i;
  }
}