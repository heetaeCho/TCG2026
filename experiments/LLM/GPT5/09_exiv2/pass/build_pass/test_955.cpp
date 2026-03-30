// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_printSi0x0003_955.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

// Exiv2 includes
#include <exiv2/exiv2.hpp>

// Include the internal header that declares CanonMakerNote.
// In Exiv2, internal Canon makernote helpers are typically declared in canonmn_int.hpp.
// If your tree uses a different internal header name/path, adjust this include accordingly.
#include "canonmn_int.hpp"

namespace {

// Helper: get a stable "as string" from stream output.
static std::string ToString(const std::ostringstream& oss) {
  return oss.str();
}

}  // namespace

namespace Exiv2::Internal {

class CanonMakerNotePrintSi0x0003Test_955 : public ::testing::Test {
 protected:
  CanonMakerNote sut_;
  Exiv2::ExifData exif_;  // unused by function but part of signature
};

TEST_F(CanonMakerNotePrintSi0x0003Test_955, WritesTwoDecimalNumberForUnsignedShortCountOne_955) {
  // Arrange
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  v->read("0");  // minimal valid input for unsignedShort
  std::ostringstream os;

  // Act
  sut_.printSi0x0003(os, *v, &exif_);

  // Assert: observable behavior is formatted number with 2 decimals
  // (Do not infer formula; just require that something numeric with two decimals was written.)
  const std::string out = ToString(os);
  ASSERT_FALSE(out.empty());
  // Must look like NNN.NN (allow optional leading '-' just in case of wrap/interpretation)
  EXPECT_NE(out.find('.'), std::string::npos);
  EXPECT_GE(out.size(), 4u);
  EXPECT_EQ(out.size() - out.rfind('.') - 1, 2u);
}

TEST_F(CanonMakerNotePrintSi0x0003Test_955, AppendsToExistingStreamContent_955) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  v->read("1");
  std::ostringstream os;
  os << "prefix:";

  sut_.printSi0x0003(os, *v, &exif_);

  const std::string out = ToString(os);
  EXPECT_TRUE(out.rfind("prefix:", 0) == 0);  // starts with prefix:
  EXPECT_GT(out.size(), std::string("prefix:").size());
}

TEST_F(CanonMakerNotePrintSi0x0003Test_955, ReturnsSameOstreamReference_955) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  v->read("2");
  std::ostringstream os;

  std::ostream& ret = sut_.printSi0x0003(os, *v, &exif_);

  EXPECT_EQ(&ret, &os);
}

TEST_F(CanonMakerNotePrintSi0x0003Test_955, DoesNotWriteAnythingWhenCountIsZero_955) {
  // Boundary: count == 0.
  // Use an unsignedShort value with no elements.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  os << "keep";

  sut_.printSi0x0003(os, *v, &exif_);

  EXPECT_EQ(ToString(os), "keep");
}

TEST_F(CanonMakerNotePrintSi0x0003Test_955, DoesNotWriteAnythingForNonUnsignedShortType_955) {
  // Boundary/type mismatch: use a different type (unsignedLong) with a value.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);
  v->read("123");

  std::ostringstream os;
  os << "keep";

  sut_.printSi0x0003(os, *v, &exif_);

  EXPECT_EQ(ToString(os), "keep");
}

TEST_F(CanonMakerNotePrintSi0x0003Test_955, NullExifDataPointerIsAccepted_955) {
  // Exceptional-ish: ExifData* is nullable by signature; observable behavior should not crash
  // and should behave consistently.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  v->read("3");

  std::ostringstream os;

  EXPECT_NO_THROW({
    sut_.printSi0x0003(os, *v, nullptr);
  });

  const std::string out = ToString(os);
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.find('.'), std::string::npos);
  EXPECT_EQ(out.size() - out.rfind('.') - 1, 2u);
}

TEST_F(CanonMakerNotePrintSi0x0003Test_955, HandlesLargeUnsignedShortValueWithoutThrow_955) {
  // Boundary: upper end of unsigned short range.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  v->read("65535");

  std::ostringstream os;

  EXPECT_NO_THROW({
    sut_.printSi0x0003(os, *v, &exif_);
  });

  const std::string out = ToString(os);
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.find('.'), std::string::npos);
  EXPECT_EQ(out.size() - out.rfind('.') - 1, 2u);
}

}  // namespace Exiv2::Internal