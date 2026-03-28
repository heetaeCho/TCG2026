// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_printCsLensType_950.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include "canonmn_int.hpp"

#include <sstream>
#include <string>
#include <type_traits>

namespace {

// Helper that can call printCsLensType whether it is implemented as a static
// function or as a non-static member function (some builds differ).
template <typename T>
struct CanonPrintCsLensTypeCaller {
  static std::ostream& call(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata) {
    // If this fails to compile, the class signature differs; see the specialization below.
    return T::printCsLensType(os, value, metadata);
  }
};

template <>
struct CanonPrintCsLensTypeCaller<Exiv2::Internal::CanonMakerNote> {
  static std::ostream& call(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata) {
    using T = Exiv2::Internal::CanonMakerNote;
    using FnPtr = decltype(&T::printCsLensType);

    // static: std::ostream& (*)(std::ostream&, const Value&, const ExifData*)
    // member: std::ostream& (T::*)(std::ostream&, const Value&, const ExifData*)
    if constexpr (std::is_pointer_v<FnPtr>) {
      return T::printCsLensType(os, value, metadata);
    } else {
      T obj;
      return (obj.*(&T::printCsLensType))(os, value, metadata);
    }
  }
};

static std::string ValueToStringViaStream(const Exiv2::Value& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

}  // namespace

class CanonMakerNotePrintCsLensTypeTest_950 : public ::testing::Test {};

TEST_F(CanonMakerNotePrintCsLensTypeTest_950, TypeNotUnsignedShort_WrapsValueInParentheses_950) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read(std::string("hello")));

  std::ostringstream os;
  Exiv2::ExifData exif;

  std::ostream& ret = CanonPrintCsLensTypeCaller<Exiv2::Internal::CanonMakerNote>::call(os, *v, &exif);

  EXPECT_EQ(&ret, &os);

  const std::string expected = "(" + ValueToStringViaStream(*v) + ")";
  EXPECT_EQ(os.str(), expected);
}

TEST_F(CanonMakerNotePrintCsLensTypeTest_950, UnsignedShortWithZeroCount_WrapsValueInParentheses_950) {
  // Newly created Value typically has count()==0 until populated.
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_EQ(v->count(), 0u);

  std::ostringstream os;
  // metadata may be null in practice; this branch should not require it.
  std::ostream& ret = CanonPrintCsLensTypeCaller<Exiv2::Internal::CanonMakerNote>::call(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);

  const std::string expected = "(" + ValueToStringViaStream(*v) + ")";
  EXPECT_EQ(os.str(), expected);
}

TEST_F(CanonMakerNotePrintCsLensTypeTest_950, ReturnsSameStreamReference_WhenWrapping_950) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read(std::string("x")));

  std::ostringstream os;
  Exiv2::ExifData exif;

  std::ostream& ret = CanonPrintCsLensTypeCaller<Exiv2::Internal::CanonMakerNote>::call(os, *v, &exif);

  EXPECT_EQ(&ret, &os);
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNotePrintCsLensTypeTest_950, UnsignedShortNonZeroCount_DoesNotThrowAndReturnsStream_950) {
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  // Populate with a simple value so count() becomes non-zero.
  ASSERT_EQ(0, v->read(std::string("1")));
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream os;
  Exiv2::ExifData exif;

  EXPECT_NO_THROW({
    std::ostream& ret = CanonPrintCsLensTypeCaller<Exiv2::Internal::CanonMakerNote>::call(os, *v, &exif);
    EXPECT_EQ(&ret, &os);
  });

  EXPECT_TRUE(os.good());
}