// File: test_linkdest_getleft_274.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <type_traits>
#include <utility>

#include "Link.h"
#include "Object.h"

namespace {

// ---- Small helpers to build poppler core Objects/Arrays without depending on internals ----

static Object MakeInt(int v) {
  Object o;
  o.initInt(v);
  return o;
}

static Object MakeReal(double v) {
  Object o;
  o.initReal(v);
  return o;
}

static Object MakeName(const char* n) {
  Object o;
  o.initName(const_cast<char*>(n));
  return o;
}

static Object MakeNull() {
  Object o;
  o.initNull();
  return o;
}

// SFINAE wrapper: supports Array::add(Object&&) OR Array::add(const Object&).
template <typename TArray>
static auto AddImpl(TArray& a, Object&& o, int) -> decltype(a.add(std::move(o)), void()) {
  a.add(std::move(o));
}
template <typename TArray>
static auto AddImpl(TArray& a, Object&& o, long) -> decltype(a.add(o), void()) {
  a.add(o);
}
static void Add(Array& a, Object&& o) { AddImpl(a, std::move(o), 0); }

// Build a common PDF destination array: [page, /XYZ left top zoom]
// (Using page number for simplicity. This uses only public constructors and isOk() to validate.)
static Array MakeXYZDestArray(Object&& page, Object&& left, Object&& top, Object&& zoom) {
  Array a;
  Add(a, std::move(page));
  Add(a, MakeName("XYZ"));
  Add(a, std::move(left));
  Add(a, std::move(top));
  Add(a, std::move(zoom));
  return a;
}

}  // namespace

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------

class LinkDestTest_274 : public ::testing::Test {};

// Normal operation: When a destination is OK, getLeft() should reflect the observable left value.
TEST_F(LinkDestTest_274, GetLeft_ReturnsProvidedLeftWhenOk_274) {
  const double kLeft = 123.25;

  Array a = MakeXYZDestArray(MakeInt(1), MakeReal(kLeft), MakeReal(400.0), MakeReal(2.0));
  LinkDest d(a);

  ASSERT_TRUE(d.isOk());
  ASSERT_TRUE(d.getChangeLeft());
  EXPECT_DOUBLE_EQ(d.getLeft(), kLeft);
}

// Boundary: left = 0.0
TEST_F(LinkDestTest_274, GetLeft_ZeroLeftWhenOk_274) {
  const double kLeft = 0.0;

  Array a = MakeXYZDestArray(MakeInt(1), MakeReal(kLeft), MakeReal(10.0), MakeReal(1.0));
  LinkDest d(a);

  ASSERT_TRUE(d.isOk());
  ASSERT_TRUE(d.getChangeLeft());
  EXPECT_DOUBLE_EQ(d.getLeft(), kLeft);
}

// Boundary: negative left (should be preserved/observable if the destination is accepted)
TEST_F(LinkDestTest_274, GetLeft_NegativeLeftWhenOk_274) {
  const double kLeft = -42.5;

  Array a = MakeXYZDestArray(MakeInt(1), MakeReal(kLeft), MakeReal(10.0), MakeReal(1.0));
  LinkDest d(a);

  ASSERT_TRUE(d.isOk());
  ASSERT_TRUE(d.getChangeLeft());
  EXPECT_DOUBLE_EQ(d.getLeft(), kLeft);
}

// Boundary/flags: null left should typically mean "do not change left" (observable via getChangeLeft()).
// We do not assume any specific numeric value for getLeft() in this case; we only verify the flag.
TEST_F(LinkDestTest_274, GetLeft_NullLeftDoesNotChangeLeftFlag_274) {
  Array a = MakeXYZDestArray(MakeInt(1), MakeNull(), MakeReal(10.0), MakeReal(1.0));
  LinkDest d(a);

  ASSERT_TRUE(d.isOk());
  EXPECT_FALSE(d.getChangeLeft());

  // Still callable; should not crash and returns a double.
  volatile double v = d.getLeft();
  (void)v;
}

// Exceptional/error case: clearly invalid destination array (empty) should not be OK.
TEST_F(LinkDestTest_274, IsOk_FalseForEmptyArray_274) {
  Array a;
  LinkDest d(a);

  EXPECT_FALSE(d.isOk());

  // getLeft() remains callable regardless; should not crash.
  volatile double v = d.getLeft();
  (void)v;
}

// Exceptional/error case: wrong type/too short array should not be OK.
TEST_F(LinkDestTest_274, IsOk_FalseForTooShortArray_274) {
  Array a;
  Add(a, MakeInt(1));           // page
  Add(a, MakeName("XYZ"));      // kind
  // missing left/top/zoom
  LinkDest d(a);

  EXPECT_FALSE(d.isOk());

  volatile double v = d.getLeft();
  (void)v;
}