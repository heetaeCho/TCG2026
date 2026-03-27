// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::Internal::CanonMakerNote::printSi0x0013
// File under test: ./src/canonmn_int.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

#include "exiv2/exiv2.hpp"

// The class under test lives in Exiv2::Internal.
// canonmn_int.hpp is not always installed as a public header; canonmn_int.cpp is in src/.
// In Exiv2's own test suite, internal headers are typically reachable via the build include paths.
// If your build setup differs, adjust the include below accordingly.
#include "canonmn_int.hpp"

namespace {

class CanonMakerNotePrintSi0x0013Test_960 : public ::testing::Test {
 protected:
  Exiv2::Internal::CanonMakerNote sut_;
  Exiv2::ExifData exif_;  // unused by this function, but required by signature

  static std::string Call(const Exiv2::Internal::CanonMakerNote& sut,
                          const Exiv2::Value& v,
                          const Exiv2::ExifData* ed = nullptr) {
    std::ostringstream os;
    // Method is non-const in the provided snippet; keep SUT non-const in fixture.
    const_cast<Exiv2::Internal::CanonMakerNote&>(sut).printSi0x0013(os, v, ed);
    return os.str();
  }
};

// ------------------------ Normal operation ------------------------

TEST_F(CanonMakerNotePrintSi0x0013Test_960, UnsignedShortNonZeroFormatsMeters_960) {
  // value.toInt64() / 100.0 << " m"
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("1234"));  // 12.34 m expected
  EXPECT_EQ("12.34 m", Call(sut_, *v, &exif_));
}

TEST_F(CanonMakerNotePrintSi0x0013Test_960, UnsignedShortZeroRendersZeroMeters_960) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("0"));
  EXPECT_EQ("0 m", Call(sut_, *v, &exif_));
}

TEST_F(CanonMakerNotePrintSi0x0013Test_960, UnsignedShortSmallValueKeepsFraction_960) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("1"));  // 0.01 m
  EXPECT_EQ("0.01 m", Call(sut_, *v, &exif_));
}

// ------------------------ Boundary conditions ------------------------

TEST_F(CanonMakerNotePrintSi0x0013Test_960, UnsignedShortMaxNotInfiniteUnlessFFFF_960) {
  // For unsigned short, max is 65535 (0xffff) which *is* Infinite; use 65534 as boundary neighbor.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("65534"));  // 655.34 m
  EXPECT_EQ("655.34 m", Call(sut_, *v, &exif_));
}

TEST_F(CanonMakerNotePrintSi0x0013Test_960, UnsignedShortFFFFPrintsInfinite_960) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("65535"));  // 0xffff
  EXPECT_EQ("Infinite", Call(sut_, *v, &exif_));
}

TEST_F(CanonMakerNotePrintSi0x0013Test_960, CountGreaterThanOneUsesFirstNumericValue_960) {
  // Observable contract: it calls toInt64() and prints one value; provide 2 items and check output.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("250 999"));  // typical Exiv2 parsing for multi-values
  EXPECT_EQ("2.5 m", Call(sut_, *v, &exif_));
}

// ------------------------ Exceptional / error-like cases (observable) ------------------------

TEST_F(CanonMakerNotePrintSi0x0013Test_960, NonUnsignedShortFallsBackToValueStream_960) {
  // If typeId != unsignedShort => returns os << value.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("hello"));
  EXPECT_EQ("hello", Call(sut_, *v, &exif_));
}

TEST_F(CanonMakerNotePrintSi0x0013Test_960, UnsignedShortWithZeroCountFallsBackToValueStream_960) {
  // Build an unsignedShort value but do not read() anything => count() should be 0.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  // We can't access internals, but we can observe the output equals streaming the Value itself.
  std::ostringstream expected;
  expected << *v;

  EXPECT_EQ(expected.str(), Call(sut_, *v, &exif_));
}

TEST_F(CanonMakerNotePrintSi0x0013Test_960, NullExifDataPointerIsAccepted_960) {
  // ExifData* is unused in observable behavior; ensure passing nullptr doesn't crash and output matches.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("100"));
  EXPECT_EQ("1 m", Call(sut_, *v, nullptr));
}

}  // namespace