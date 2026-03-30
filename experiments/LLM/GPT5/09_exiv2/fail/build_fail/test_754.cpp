// File: test_exifdatum_typename_754.cpp
// TEST_ID: 754

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifdatumTypeNameTest_754 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // Any valid Exif key string should work; the exact tag is not important for these tests.
    return Exiv2::ExifKey("Exif.Image.Make");
  }
};

TEST_F(ExifdatumTypeNameTest_754, ReturnsTypeInfoNameForCurrentTypeId_754) {
  Exiv2::ExifKey key = MakeKey();

  // Create a concrete Value with a known TypeId, without assuming the returned typeName string.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  (void)v->read("abc");

  Exiv2::Exifdatum d(key, v.get());

  const Exiv2::TypeId tid = d.typeId();
  const char* expected = Exiv2::TypeInfo::typeName(tid);
  const char* actual = d.typeName();

  // Observable behavior: Exifdatum::typeName() should match TypeInfo::typeName(typeId()).
  ASSERT_NE(actual, nullptr);
  ASSERT_NE(expected, nullptr);
  EXPECT_STREQ(actual, expected);
}

TEST_F(ExifdatumTypeNameTest_754, TypeNameIsStableAcrossRepeatedCalls_754) {
  Exiv2::ExifKey key = MakeKey();

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);
  (void)v->read("123");

  Exiv2::Exifdatum d(key, v.get());

  const char* n1 = d.typeName();
  const char* n2 = d.typeName();

  ASSERT_NE(n1, nullptr);
  ASSERT_NE(n2, nullptr);
  EXPECT_STREQ(n1, n2);

  // Also keep the contract check tied to the public interface.
  EXPECT_STREQ(n1, Exiv2::TypeInfo::typeName(d.typeId()));
}

TEST_F(ExifdatumTypeNameTest_754, WorksWhenConstructedWithNullValuePointer_754) {
  Exiv2::ExifKey key = MakeKey();

  // Boundary / robustness: constructor allows a Value pointer; pass nullptr and ensure the
  // observable contract of typeName vs typeId remains consistent (and does not crash).
  Exiv2::Exifdatum d(key, nullptr);

  const Exiv2::TypeId tid = d.typeId();
  const char* expected = Exiv2::TypeInfo::typeName(tid);
  const char* actual = d.typeName();

  // We don't assume what tid is in this scenario; only that the mapping is consistent.
  ASSERT_NE(actual, nullptr);
  ASSERT_NE(expected, nullptr);
  EXPECT_STREQ(actual, expected);
}

}  // namespace