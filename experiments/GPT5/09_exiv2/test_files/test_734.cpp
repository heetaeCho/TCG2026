// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_urational_operator_assign_734.cpp
//
// Unit tests for Exiv2::Exifdatum::operator=(const URational&)
// based strictly on observable behavior via the public interface.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

namespace {

// NOTE: We intentionally keep construction minimal and only use public API.
// Using a tag that is commonly represented as an (unsigned) rational in Exif.
inline Exiv2::Exifdatum makeUratDatumForTests() {
  Exiv2::ExifKey key("Exif.Photo.ExposureTime");
  // Pass nullptr for initial value; then assign via operator= under test.
  return Exiv2::Exifdatum(key, nullptr);
}

inline Exiv2::URational urat(uint32_t num, uint32_t den) {
  return Exiv2::URational(num, den);
}

class ExifdatumUrationalAssignTest_734 : public ::testing::Test {};

}  // namespace

TEST_F(ExifdatumUrationalAssignTest_734, ReturnsSelfReference_734) {
  auto d = makeUratDatumForTests();
  const auto v = urat(1u, 200u);

  Exiv2::Exifdatum& ret = (d = v);
  EXPECT_EQ(&ret, &d);
}

TEST_F(ExifdatumUrationalAssignTest_734, SupportsChaining_AssignmentReturnsLvalue_734) {
  auto d = makeUratDatumForTests();
  const auto v1 = urat(1u, 250u);
  const auto v2 = urat(1u, 500u);

  Exiv2::Exifdatum& ret = ((d = v1) = v2);
  EXPECT_EQ(&ret, &d);

  const Exiv2::Rational got = d.toRational(0);
  EXPECT_EQ(got.first, static_cast<int32_t>(v2.first));
  EXPECT_EQ(got.second, static_cast<int32_t>(v2.second));
}

TEST_F(ExifdatumUrationalAssignTest_734, SetsCountToAtLeastOneForScalarAssignment_734) {
  auto d = makeUratDatumForTests();
  const auto v = urat(3u, 8u);

  ASSERT_NO_THROW(d = v);
  EXPECT_GE(d.count(), static_cast<size_t>(1));
}

TEST_F(ExifdatumUrationalAssignTest_734, TypeIdBecomesUnsignedRationalOrCompatibleAfterAssignment_734) {
  auto d = makeUratDatumForTests();
  const auto v = urat(1u, 60u);

  ASSERT_NO_THROW(d = v);

  // Observable property: a URational assignment should result in an unsigned-rational type
  // (or a compatible rational representation exposed by the library).
  //
  // We accept either unsignedRational or rational to avoid over-constraining behavior across builds,
  // but still validate that the type is rational-like rather than unrelated.
  const Exiv2::TypeId tid = d.typeId();
  EXPECT_TRUE(tid == Exiv2::unsignedRational || tid == Exiv2::rational)
      << "Unexpected TypeId after URational assignment: " << static_cast<int>(tid);
}

TEST_F(ExifdatumUrationalAssignTest_734, ToRationalReflectsAssignedValue_734) {
  auto d = makeUratDatumForTests();
  const auto v = urat(1u, 200u);

  ASSERT_NO_THROW(d = v);

  const Exiv2::Rational got = d.toRational(0);
  EXPECT_EQ(got.first, static_cast<int32_t>(v.first));
  EXPECT_EQ(got.second, static_cast<int32_t>(v.second));
}

TEST_F(ExifdatumUrationalAssignTest_734, ReassignUpdatesValue_734) {
  auto d = makeUratDatumForTests();
  const auto v1 = urat(1u, 125u);
  const auto v2 = urat(5u, 16u);

  ASSERT_NO_THROW(d = v1);
  ASSERT_NO_THROW(d = v2);

  const Exiv2::Rational got = d.toRational(0);
  EXPECT_EQ(got.first, static_cast<int32_t>(v2.first));
  EXPECT_EQ(got.second, static_cast<int32_t>(v2.second));
}

TEST_F(ExifdatumUrationalAssignTest_734, Boundary_ZeroNumerator_734) {
  auto d = makeUratDatumForTests();
  const auto v = urat(0u, 1u);

  ASSERT_NO_THROW(d = v);

  const Exiv2::Rational got = d.toRational(0);
  EXPECT_EQ(got.first, 0);
  EXPECT_EQ(got.second, 1);
}

TEST_F(ExifdatumUrationalAssignTest_734, Boundary_LargeNumerator_DoesNotThrowAndStringNotEmpty_734) {
  auto d = makeUratDatumForTests();
  const auto v = urat(std::numeric_limits<uint32_t>::max(), 1u);

  ASSERT_NO_THROW(d = v);

  // Avoid over-specifying formatting; just require it is representable as a non-empty string.
  const std::string s = d.toString();
  EXPECT_FALSE(s.empty());
  EXPECT_GE(d.count(), static_cast<size_t>(1));
}

TEST_F(ExifdatumUrationalAssignTest_734, Edge_DenominatorZero_EitherThrowsOrLeavesObjectUsable_734) {
  auto d = makeUratDatumForTests();
  const auto v = urat(1u, 0u);

  bool threw = false;
  try {
    d = v;
  } catch (...) {
    threw = true;
  }

  // Regardless of whether assignment rejects denominator==0, the object should remain usable
  // through its public interface (no crashes / undefined observable behavior).
  EXPECT_NO_THROW((void)d.count());
  EXPECT_NO_THROW((void)d.typeId());
  EXPECT_NO_THROW((void)d.toString());

  // If assignment was accepted, we can still assert scalar-like behavior without assuming
  // how denominator==0 is normalized/printed.
  if (!threw) {
    EXPECT_GE(d.count(), static_cast<size_t>(1));
  }
}