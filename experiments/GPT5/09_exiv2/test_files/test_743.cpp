// File: test_exifdatum_familyname_743.cpp
#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifdatumTest_743 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeValidKey() {
    // Use a commonly valid Exif key string; tests only compare observable outputs.
    return Exiv2::ExifKey("Exif.Image.Make");
  }

  static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    v->read(s);
    return v;
  }

  static void ExpectCStrNonNullAndValid(const char* s) {
    ASSERT_NE(s, nullptr);
    // Must be NUL-terminated; strlen should not crash and should be deterministic.
    (void)std::strlen(s);
  }
};

TEST_F(ExifdatumTest_743, FamilyNameMatchesKeyFamilyName_NullValueCtor_743) {
  const Exiv2::ExifKey key = MakeValidKey();
  Exiv2::Exifdatum datum(key, nullptr);

  const char* expected = key.familyName();
  const char* got = datum.familyName();

  ExpectCStrNonNullAndValid(expected);
  ExpectCStrNonNullAndValid(got);
  EXPECT_STREQ(got, expected);
}

TEST_F(ExifdatumTest_743, FamilyNameMatchesKeyFamilyName_WithValueCtor_743) {
  const Exiv2::ExifKey key = MakeValidKey();
  auto v = MakeAsciiValue("Canon");

  // Constructor takes a raw pointer; keep the UniquePtr alive for construction.
  Exiv2::Exifdatum datum(key, v.get());

  const char* expected = key.familyName();
  const char* got = datum.familyName();

  ExpectCStrNonNullAndValid(expected);
  ExpectCStrNonNullAndValid(got);
  EXPECT_STREQ(got, expected);
}

TEST_F(ExifdatumTest_743, FamilyNameStableAcrossRepeatedCalls_743) {
  const Exiv2::ExifKey key = MakeValidKey();
  Exiv2::Exifdatum datum(key, nullptr);

  const char* a = datum.familyName();
  const char* b = datum.familyName();

  ExpectCStrNonNullAndValid(a);
  ExpectCStrNonNullAndValid(b);
  EXPECT_STREQ(a, b);
}

TEST_F(ExifdatumTest_743, FamilyNamePreservedByCopyConstruction_743) {
  const Exiv2::ExifKey key = MakeValidKey();
  Exiv2::Exifdatum original(key, nullptr);

  Exiv2::Exifdatum copy(original);

  const char* a = original.familyName();
  const char* b = copy.familyName();

  ExpectCStrNonNullAndValid(a);
  ExpectCStrNonNullAndValid(b);
  EXPECT_STREQ(b, a);
}

TEST_F(ExifdatumTest_743, FamilyNameUpdatedByCopyAssignment_743) {
  const Exiv2::ExifKey keyA("Exif.Image.Make");
  const Exiv2::ExifKey keyB("Exif.Photo.FocalLength");

  Exiv2::Exifdatum a(keyA, nullptr);
  Exiv2::Exifdatum b(keyB, nullptr);

  const char* expectedBefore = b.familyName();
  ExpectCStrNonNullAndValid(expectedBefore);

  a = b;

  const char* expectedAfter = b.familyName();
  const char* gotAfter = a.familyName();

  ExpectCStrNonNullAndValid(expectedAfter);
  ExpectCStrNonNullAndValid(gotAfter);
  EXPECT_STREQ(gotAfter, expectedAfter);
}

TEST_F(ExifdatumTest_743, FamilyNameIsNonNullEvenForDifferentKeys_743) {
  const Exiv2::ExifKey key1("Exif.Image.Make");
  const Exiv2::ExifKey key2("Exif.Thumbnail.Compression");

  Exiv2::Exifdatum d1(key1, nullptr);
  Exiv2::Exifdatum d2(key2, nullptr);

  ExpectCStrNonNullAndValid(d1.familyName());
  ExpectCStrNonNullAndValid(d2.familyName());

  // Compare to their respective keys (black-box, no hard-coded family literal).
  EXPECT_STREQ(d1.familyName(), key1.familyName());
  EXPECT_STREQ(d2.familyName(), key2.familyName());
}

}  // namespace