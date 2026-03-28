// TEST_ID 750
// File: test_exifdatum_ifdname_750.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

// Exifdatum::ifdName() delegates to Exiv2::Internal::ifdName(IfdId) when key_ is present.
// The declaration is typically available via tags_int.hpp in Exiv2.
#include <exiv2/tags_int.hpp>

namespace {

class ExifdatumIfdNameTest_750 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeDummyValue() {
    // Use any concrete Value type; the tests focus only on ifdName().
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    // Best-effort initialization (should not affect ifdName()).
    (void)v->read("1");
    return v;
  }

  static Exiv2::Exifdatum MakeDatumFromKeyString(const std::string& keyStr) {
    Exiv2::ExifKey key(keyStr);
    auto v = MakeDummyValue();
    return Exiv2::Exifdatum(key, v.get());
  }
};

}  // namespace

TEST_F(ExifdatumIfdNameTest_750, IfdNameMatchesInternalIfdNameForImageKey_750) {
  const std::string keyStr = "Exif.Image.ImageWidth";
  Exiv2::ExifKey key(keyStr);
  auto v = ExifdatumIfdNameTest_750::MakeDummyValue();

  Exiv2::Exifdatum datum(key, v.get());

  const char* expected = Exiv2::Internal::ifdName(key.ifdId());
  ASSERT_NE(expected, nullptr);
  ASSERT_NE(datum.ifdName(), nullptr);

  EXPECT_STREQ(datum.ifdName(), expected);
  EXPECT_STREQ(datum.ifdName(), Exiv2::Internal::ifdName(datum.ifdId()));
}

TEST_F(ExifdatumIfdNameTest_750, IfdNameMatchesInternalIfdNameForPhotoKey_750) {
  const std::string keyStr = "Exif.Photo.ExposureTime";
  Exiv2::ExifKey key(keyStr);
  auto v = ExifdatumIfdNameTest_750::MakeDummyValue();

  Exiv2::Exifdatum datum(key, v.get());

  const char* expected = Exiv2::Internal::ifdName(key.ifdId());
  ASSERT_NE(expected, nullptr);
  ASSERT_NE(datum.ifdName(), nullptr);

  EXPECT_STREQ(datum.ifdName(), expected);
  EXPECT_STREQ(datum.ifdName(), Exiv2::Internal::ifdName(datum.ifdId()));
}

TEST_F(ExifdatumIfdNameTest_750, MultipleCallsReturnSameContent_750) {
  Exiv2::Exifdatum datum = MakeDatumFromKeyString("Exif.Image.ImageWidth");

  const std::string first = datum.ifdName();
  const std::string second = datum.ifdName();
  const std::string third = datum.ifdName();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(ExifdatumIfdNameTest_750, CopyConstructorPreservesIfdName_750) {
  Exiv2::Exifdatum original = MakeDatumFromKeyString("Exif.Photo.ExposureTime");
  Exiv2::Exifdatum copy(original);

  EXPECT_STREQ(copy.ifdName(), original.ifdName());
  EXPECT_EQ(copy.ifdId(), original.ifdId());
}

TEST_F(ExifdatumIfdNameTest_750, CopyAssignmentPreservesIfdName_750) {
  Exiv2::Exifdatum a = MakeDatumFromKeyString("Exif.Image.ImageWidth");
  Exiv2::Exifdatum b = MakeDatumFromKeyString("Exif.Photo.ExposureTime");

  const std::string expectedName = a.ifdName();
  const Exiv2::IfdId expectedId = a.ifdId();

  b = a;

  EXPECT_STREQ(b.ifdName(), expectedName.c_str());
  EXPECT_EQ(b.ifdId(), expectedId);
}

TEST_F(ExifdatumIfdNameTest_750, IfdNameUnchangedByKeyIndexBoundaryValue_750) {
  // Boundary-style interaction: setIdx with a non-zero index and ensure ifdName is still consistent
  // with the key's ifdId mapping.
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  key.setIdx(5);

  auto v = ExifdatumIfdNameTest_750::MakeDummyValue();
  Exiv2::Exifdatum datum(key, v.get());

  EXPECT_STREQ(datum.ifdName(), Exiv2::Internal::ifdName(key.ifdId()));
  EXPECT_STREQ(datum.ifdName(), Exiv2::Internal::ifdName(datum.ifdId()));
}