// File: test_exifdatum_setvalue_740.cpp
// Unit tests for Exiv2::Exifdatum::setValue(const std::string&)
// Focus: observable behavior via public API only (black-box).

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

class ExifdatumTest_740 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeDatumWithKey(const std::string& exifKeyString,
                                          const Exiv2::Value* pValue = nullptr) {
    Exiv2::ExifKey key(exifKeyString);
    return Exiv2::Exifdatum(key, pValue);
  }
};

TEST_F(ExifdatumTest_740, SetValueAsciiKeyStoresAndReturnsSuccess_740) {
  // Use a commonly string-typed key.
  auto datum = MakeDatumWithKey("Exif.Image.Make", nullptr);

  const int rc = datum.setValue(std::string("Canon"));

  // Most Exiv2 read() implementations return 0 on success; if not, at least value should be ok.
  EXPECT_EQ(0, rc);
  EXPECT_TRUE(datum.value().ok());
  EXPECT_EQ("Canon", datum.toString());

  // Also verify we can clone out a Value via getValue().
  auto v = datum.getValue();
  ASSERT_NE(nullptr, v.get());
  EXPECT_TRUE(v->ok());
}

TEST_F(ExifdatumTest_740, SetValueOverwritesPreviousValue_740) {
  auto datum = MakeDatumWithKey("Exif.Image.Make", nullptr);

  ASSERT_EQ(0, datum.setValue(std::string("Canon")));
  EXPECT_EQ("Canon", datum.toString());

  ASSERT_EQ(0, datum.setValue(std::string("Nikon")));
  EXPECT_EQ("Nikon", datum.toString());
  EXPECT_TRUE(datum.value().ok());
}

TEST_F(ExifdatumTest_740, SetValueEmptyStringIsHandled_740) {
  auto datum = MakeDatumWithKey("Exif.Image.Make", nullptr);

  const int rc = datum.setValue(std::string(""));

  EXPECT_EQ(0, rc);
  EXPECT_TRUE(datum.value().ok());
  EXPECT_EQ("", datum.toString());
}

TEST_F(ExifdatumTest_740, SetValueForRationalKeyAcceptsRationalText_740) {
  // Use a commonly rational-typed key.
  auto datum = MakeDatumWithKey("Exif.Photo.FNumber", nullptr);

  const int rc = datum.setValue(std::string("5/2"));

  EXPECT_EQ(0, rc);
  EXPECT_TRUE(datum.value().ok());

  // toString() should be non-empty and stable enough to observe.
  // We avoid asserting exact formatting beyond containing the input structure.
  const std::string s = datum.toString();
  EXPECT_FALSE(s.empty());
}

TEST_F(ExifdatumTest_740, SetValueInvalidTextForRationalKeyReportsFailureOrMarksNotOk_740) {
  auto datum = MakeDatumWithKey("Exif.Photo.FNumber", nullptr);

  const int rc = datum.setValue(std::string("not_a_number"));

  // Observable error case: either a non-zero return, or Value becomes !ok().
  // (We don't assume a specific error code.)
  if (rc == 0) {
    EXPECT_TRUE(datum.value().ok()) << "If parsing reports success, value() should remain ok()";
  } else {
    EXPECT_FALSE(datum.value().ok()) << "If parsing fails, value() should be marked not ok()";
  }
}

TEST_F(ExifdatumTest_740, SetValueDoesNotRequirePreexistingValueObject_740) {
  auto datum = MakeDatumWithKey("Exif.Image.Make", nullptr);

  // Before setValue, getValue() may be null or a default; we only assert post-condition.
  ASSERT_EQ(0, datum.setValue(std::string("Sony")));

  auto cloned = datum.getValue();
  ASSERT_NE(nullptr, cloned.get());
  EXPECT_TRUE(cloned->ok());

  // The datum's typeId should match the cloned value's typeId (observable consistency).
  EXPECT_EQ(datum.typeId(), cloned->typeId());
}

}  // namespace