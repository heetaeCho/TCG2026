// =================================================================================================
// TEST_ID: 727
// File: test_exif_setvalue_727.cpp
// Unit tests for: Exiv2::setValue<T>(Exiv2::Exifdatum&, const T&)
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <limits>
#include <string>

#include <exiv2/exif.hpp>

namespace Exiv2 {
// Some builds may not expose the declaration in public headers. Declaring it here enables testing
// without re-implementing any logic (the definition is provided by the codebase).
template <typename T>
Exifdatum& setValue(Exifdatum& exifDatum, const T& value);
}  // namespace Exiv2

namespace {

using ::testing::AnyOf;
using ::testing::Eq;

class ExifSetValueTest_727 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeDatumWithKey() {
    // Use a well-known EXIF key string; we only need a valid Exifdatum instance.
    Exiv2::ExifKey key("Exif.Image.ImageDescription");
    return Exiv2::Exifdatum(key, nullptr);
  }
};

TEST_F(ExifSetValueTest_727, ReturnsSameObjectReference_727) {
  auto datum = MakeDatumWithKey();

  Exiv2::Exifdatum* ret = &Exiv2::setValue<uint16_t>(datum, static_cast<uint16_t>(1));
  EXPECT_EQ(ret, &datum);
}

TEST_F(ExifSetValueTest_727, SetsSingleValueAndCountIsOne_727) {
  auto datum = MakeDatumWithKey();

  Exiv2::setValue<uint16_t>(datum, static_cast<uint16_t>(7));

  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), 7);
}

TEST_F(ExifSetValueTest_727, OverwritesExistingValue_727) {
  auto datum = MakeDatumWithKey();

  Exiv2::setValue<uint16_t>(datum, static_cast<uint16_t>(10));
  ASSERT_EQ(datum.count(), 1u);
  ASSERT_EQ(datum.toInt64(0), 10);

  Exiv2::setValue<uint16_t>(datum, static_cast<uint16_t>(11));

  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), 11);
}

TEST_F(ExifSetValueTest_727, SetsZeroValueBoundary_727) {
  auto datum = MakeDatumWithKey();

  Exiv2::setValue<uint16_t>(datum, static_cast<uint16_t>(0));

  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), 0);
}

TEST_F(ExifSetValueTest_727, SetsMaxUInt32Boundary_727) {
  auto datum = MakeDatumWithKey();

  const uint32_t max_u32 = std::numeric_limits<uint32_t>::max();
  Exiv2::setValue<uint32_t>(datum, max_u32);

  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(max_u32));
}

TEST_F(ExifSetValueTest_727, SetsStringValueAndToStringReflectsIt_727) {
  auto datum = MakeDatumWithKey();

  const std::string s = "hello";
  Exiv2::setValue<std::string>(datum, s);

  EXPECT_EQ(datum.count(), 1u);

  // Exiv2 string formatting can vary by type/escaping; accept common observable outputs.
  EXPECT_THAT(datum.toString(), AnyOf(Eq("hello"), Eq("\"hello\"")));
}

}  // namespace