// SPDX-License-Identifier: GPL-2.0-or-later
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

// Use a well-known, valid Exif key string to construct ExifKey.
inline Exiv2::ExifKey MakeTestKey() {
  return Exiv2::ExifKey("Exif.Image.Make");
}

class ExifdatumTest_753 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeDatumWithNullValue() {
    Exiv2::ExifKey key = MakeTestKey();
    return Exiv2::Exifdatum(key, nullptr);
  }

  static Exiv2::Exifdatum MakeDatumWithValueType(Exiv2::TypeId tid) {
    Exiv2::ExifKey key = MakeTestKey();
    auto v = Exiv2::Value::create(tid);
    EXPECT_NE(v, nullptr);
    return Exiv2::Exifdatum(key, v.get());  // Exifdatum is expected to take/clone Value via pointer.
  }
};

}  // namespace

TEST_F(ExifdatumTest_753, TypeId_WhenConstructedWithNullValue_IsInvalidTypeId_753) {
  Exiv2::Exifdatum d = MakeDatumWithNullValue();
  EXPECT_EQ(d.typeId(), Exiv2::invalidTypeId);
}

TEST_F(ExifdatumTest_753, TypeId_WhenConstructedWithNonNullValue_MatchesValueTypeId_753) {
  Exiv2::Exifdatum d = MakeDatumWithValueType(Exiv2::asciiString);
  EXPECT_EQ(d.typeId(), Exiv2::asciiString);
}

TEST_F(ExifdatumTest_753, TypeId_AfterSetValue_MatchesNewValueTypeId_753) {
  Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum d(key, nullptr);
  EXPECT_EQ(d.typeId(), Exiv2::invalidTypeId);

  auto v1 = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v1, nullptr);
  ASSERT_NO_THROW(d.setValue(v1.get()));
  EXPECT_EQ(d.typeId(), Exiv2::unsignedShort);

  auto v2 = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_NE(v2, nullptr);
  ASSERT_NO_THROW(d.setValue(v2.get()));
  EXPECT_EQ(d.typeId(), Exiv2::signedLong);
}

TEST_F(ExifdatumTest_753, TypeId_CopyConstruction_PreservesTypeId_753) {
  Exiv2::Exifdatum original = MakeDatumWithValueType(Exiv2::unsignedLongLong);
  EXPECT_EQ(original.typeId(), Exiv2::unsignedLongLong);

  Exiv2::Exifdatum copy(original);
  EXPECT_EQ(copy.typeId(), Exiv2::unsignedLongLong);
}

TEST_F(ExifdatumTest_753, TypeId_CopyAssignment_PreservesTypeId_753) {
  Exiv2::Exifdatum src = MakeDatumWithValueType(Exiv2::tiffDouble);
  Exiv2::Exifdatum dst = MakeDatumWithNullValue();

  EXPECT_EQ(src.typeId(), Exiv2::tiffDouble);
  EXPECT_EQ(dst.typeId(), Exiv2::invalidTypeId);

  ASSERT_NO_THROW(dst = src);
  EXPECT_EQ(dst.typeId(), Exiv2::tiffDouble);
}

TEST_F(ExifdatumTest_753, TypeId_AssigningFromValue_PreservesAssignedValueTypeId_753) {
  Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum d(key, nullptr);
  EXPECT_EQ(d.typeId(), Exiv2::invalidTypeId);

  auto v = Exiv2::Value::create(Exiv2::unsignedRational);
  ASSERT_NE(v, nullptr);

  // Observable behavior: after assigning from a Value, typeId() should reflect the assigned Value's type.
  ASSERT_NO_THROW(d = *v);
  EXPECT_EQ(d.typeId(), Exiv2::unsignedRational);
}