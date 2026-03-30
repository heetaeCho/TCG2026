// LinkSound_getVolume_317_test.cpp
// Unit tests for LinkSound::getVolume (TEST_ID = 317)

#include <gtest/gtest.h>

#include "Link.h"

// Poppler's Object is typically needed to construct LinkSound.
#include "Object.h"

#include <cmath>
#include <type_traits>

namespace {

// --- Small compatibility helpers for Poppler Object across versions ---

template <typename T, typename = void>
struct HasSetToNull : std::false_type {};
template <typename T>
struct HasSetToNull<T, std::void_t<decltype(std::declval<T&>().setToNull())>> : std::true_type {};

template <typename T, typename = void>
struct HasInitNull : std::false_type {};
template <typename T>
struct HasInitNull<T, std::void_t<decltype(std::declval<T&>().initNull())>> : std::true_type {};

inline Object MakeNullObject() {
  Object obj; // many Poppler versions provide a default ctor
  if constexpr (HasSetToNull<Object>::value) {
    obj.setToNull();
  } else if constexpr (HasInitNull<Object>::value) {
    obj.initNull();
  } else {
    // If neither API exists, we keep the default-constructed Object.
    // The test cases are written to only require that LinkSound can be
    // constructed and queried without crashing.
  }
  return obj;
}

inline bool IsFiniteDouble(double v) {
  return std::isfinite(v) != 0;
}

} // namespace

class LinkSoundTest_317 : public ::testing::Test {
protected:
  Object nullObj_ = MakeNullObject();
};

TEST_F(LinkSoundTest_317, ConstructWithNullObject_DoesNotCrash_317) {
  // Black-box: constructor should tolerate an "empty/invalid" Object pointer.
  ASSERT_NO_THROW({
    LinkSound action(&nullObj_);
    (void)action.getVolume();
  });
}

TEST_F(LinkSoundTest_317, GetVolume_IsStableAcrossMultipleCalls_317) {
  LinkSound action(&nullObj_);

  const double v1 = action.getVolume();
  const double v2 = action.getVolume();
  const double v3 = action.getVolume();

  // Observable behavior: repeated calls should be consistent.
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(LinkSoundTest_317, GetVolume_IsCallableOnConstInstance_317) {
  LinkSound nonConst(&nullObj_);
  const LinkSound& action = nonConst;

  // Compile-time + runtime check that the method is const-correct and callable.
  const double v = action.getVolume();
  (void)v;
  SUCCEED();
}

TEST_F(LinkSoundTest_317, GetVolume_ReturnsFiniteValueEvenForInvalidInput_317) {
  LinkSound action(&nullObj_);

  const double v = action.getVolume();

  // We do not assume any specific default/range; only that it is a usable number.
  EXPECT_TRUE(IsFiniteDouble(v));
}