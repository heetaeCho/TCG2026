// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_resolveLens0xffff_test.cpp
//
// Unit tests for resolveLens0xffff() in ./TestProjects/exiv2/src/minoltamn_int.cpp
//
// NOTE:
// - The function under test has internal linkage (static in a .cpp). To test it as a black box
//   without re-implementing logic, we include the implementation .cpp into this test TU.
// - Tests compare observable output against the documented fallback printer
//   EXV_PRINT_TAG(minoltaSonyLensID)(...).

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

// Include implementation to access the internal-linkage function in the same translation unit.
#include "./TestProjects/exiv2/src/minoltamn_int.cpp"

namespace {

class MinoltaResolveLens0xFFFFTest_1024 : public ::testing::Test {
 protected:
  static void AddAscii(Exiv2::ExifData& exif, const char* key, const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    ASSERT_TRUE(static_cast<bool>(v));
    ASSERT_EQ(0, v->read(s));
    exif.add(Exiv2::ExifKey(key), v.get());
  }

  static void AddLong(Exiv2::ExifData& exif, const char* key, long n) {
    auto v = Exiv2::Value::create(Exiv2::unsignedLong);
    ASSERT_TRUE(static_cast<bool>(v));
    ASSERT_EQ(0, v->read(std::to_string(n)));
    exif.add(Exiv2::ExifKey(key), v.get());
  }

  static std::string CallResolve(const Exiv2::Value& lensIdValue, const Exiv2::ExifData* md) {
    std::ostringstream os;
    // Function under test (internal linkage, visible due to .cpp include above)
    Exiv2::Internal::resolveLens0xffff(os, lensIdValue, md);
    return os.str();
  }

  static std::string CallFallback(const Exiv2::Value& lensIdValue, const Exiv2::ExifData* md) {
    std::ostringstream os;
    EXV_PRINT_TAG(minoltaSonyLensID)(os, lensIdValue, md);
    return os.str();
  }

  static Exiv2::Value::UniquePtr MakeLensIdFFFFValue() {
    auto v = Exiv2::Value::create(Exiv2::unsignedLong);
    if (!v) return v;
    // 0xffff == 65535
    v->read("65535");
    return v;
  }
};

TEST_F(MinoltaResolveLens0xFFFFTest_1024, NullMetadataFallsBack_1024) {
  auto lensId = MakeLensIdFFFFValue();
  ASSERT_TRUE(static_cast<bool>(lensId));

  const std::string out = CallResolve(*lensId, nullptr);
  const std::string fallback = CallFallback(*lensId, nullptr);

  EXPECT_EQ(out, fallback);
}

TEST_F(MinoltaResolveLens0xFFFFTest_1024, NonMatchingModelFallsBack_1024) {
  auto lensId = MakeLensIdFFFFValue();
  ASSERT_TRUE(static_cast<bool>(lensId));

  Exiv2::ExifData md;
  AddAscii(md, "Exif.Image.Model", "SOME-OTHER-MODEL");
  AddAscii(md, "Exif.Photo.MaxApertureValue", "434/256");  // F1.8 string from implementation

  const std::string out = CallResolve(*lensId, &md);
  const std::string fallback = CallFallback(*lensId, &md);

  EXPECT_EQ(out, fallback);
}

TEST_F(MinoltaResolveLens0xFFFFTest_1024, MatchingModelAndF18AndRatioInRangeChangesOutput_1024) {
  auto lensId = MakeLensIdFFFFValue();
  ASSERT_TRUE(static_cast<bool>(lensId));

  Exiv2::ExifData md;
  AddAscii(md, "Exif.Image.Model", "ILCE-6000");
  AddAscii(md, "Exif.Photo.MaxApertureValue", "434/256");  // F1.8
  // ratio = (75*100)/50 = 150 (in [145,155])
  AddLong(md, "Exif.Photo.FocalLength", 50);
  AddLong(md, "Exif.Photo.FocalLengthIn35mmFilm", 75);

  const std::string out = CallResolve(*lensId, &md);
  const std::string fallback = CallFallback(*lensId, &md);

  // Observable behavior: when the internal resolver chooses a resolved lens path,
  // output should differ from the default tag printer.
  EXPECT_NE(out, fallback);
  EXPECT_FALSE(out.empty());
}

TEST_F(MinoltaResolveLens0xFFFFTest_1024, MatchingModelAndKnownMaxApertureAndRatioInRangeChangesOutput_1024) {
  auto lensId = MakeLensIdFFFFValue();
  ASSERT_TRUE(static_cast<bool>(lensId));

  Exiv2::ExifData md;
  AddAscii(md, "Exif.Image.Model", "ILCE-6000");
  // One of the known maxApertures in the implementation (e.g., "1024/256" == F4)
  AddAscii(md, "Exif.Photo.MaxApertureValue", "1024/256");
  // ratio = (75*100)/50 = 150 (in [145,155])
  AddLong(md, "Exif.Photo.FocalLength", 50);
  AddLong(md, "Exif.Photo.FocalLengthIn35mmFilm", 75);

  const std::string out = CallResolve(*lensId, &md);
  const std::string fallback = CallFallback(*lensId, &md);

  EXPECT_NE(out, fallback);
  EXPECT_FALSE(out.empty());
}

TEST_F(MinoltaResolveLens0xFFFFTest_1024, RatioJustOutsideLowerBoundFallsBack_1024) {
  auto lensId = MakeLensIdFFFFValue();
  ASSERT_TRUE(static_cast<bool>(lensId));

  Exiv2::ExifData md;
  AddAscii(md, "Exif.Image.Model", "ILCE-6000");
  AddAscii(md, "Exif.Photo.MaxApertureValue", "434/256");  // F1.8
  // ratio = (72*100)/50 = 144 (just below 145)
  AddLong(md, "Exif.Photo.FocalLength", 50);
  AddLong(md, "Exif.Photo.FocalLengthIn35mmFilm", 72);

  const std::string out = CallResolve(*lensId, &md);
  const std::string fallback = CallFallback(*lensId, &md);

  EXPECT_EQ(out, fallback);
}

TEST_F(MinoltaResolveLens0xFFFFTest_1024, RatioJustOutsideUpperBoundFallsBack_1024) {
  auto lensId = MakeLensIdFFFFValue();
  ASSERT_TRUE(static_cast<bool>(lensId));

  Exiv2::ExifData md;
  AddAscii(md, "Exif.Image.Model", "ILCE-6000");
  AddAscii(md, "Exif.Photo.MaxApertureValue", "1024/256");  // known max aperture
  // ratio = (78*100)/50 = 156 (just above 155)
  AddLong(md, "Exif.Photo.FocalLength", 50);
  AddLong(md, "Exif.Photo.FocalLengthIn35mmFilm", 78);

  const std::string out = CallResolve(*lensId, &md);
  const std::string fallback = CallFallback(*lensId, &md);

  EXPECT_EQ(out, fallback);
}

TEST_F(MinoltaResolveLens0xFFFFTest_1024, MissingFocalLengthKeysDoesNotThrowAndFallsBack_1024) {
  auto lensId = MakeLensIdFFFFValue();
  ASSERT_TRUE(static_cast<bool>(lensId));

  Exiv2::ExifData md;
  AddAscii(md, "Exif.Image.Model", "ILCE-6000");
  AddAscii(md, "Exif.Photo.MaxApertureValue", "434/256");  // F1.8
  // Intentionally omit focal length keys to exercise exception-handling path.

  const std::string out = CallResolve(*lensId, &md);
  const std::string fallback = CallFallback(*lensId, &md);

  EXPECT_EQ(out, fallback);
}

}  // namespace