// =================================================================================================
// TEST_ID: 1019
// Unit tests for: Exiv2::Internal::resolveLens0x1c (from ./TestProjects/exiv2/src/minoltamn_int.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

// NOTE: resolveLens0x1c is a TU-local (static) function in a .cpp file.
// To test it via its real interface (black-box), we include the implementation file into this TU.
#include "minoltamn_int.cpp"

namespace {

class ResolveLens0x1cTest_1019 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    if (v) {
      // read() return value is not specified here; we only require the object to exist.
      (void)v->read(s);
    }
    return v;
  }

  static std::string run(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream os;
    auto& ret = Exiv2::Internal::resolveLens0x1c(os, v, md);
    EXPECT_EQ(&ret, &os); // must return the same stream reference
    return os.str();
  }
};

TEST_F(ResolveLens0x1cTest_1019, ReturnsSameStreamReference_1019) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  auto& ret = Exiv2::Internal::resolveLens0x1c(os, *v, /*metadata=*/nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(ResolveLens0x1cTest_1019, NullMetadataDoesNotThrowAndProducesSomeOutput_1019) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  EXPECT_NO_THROW({
    const std::string out = run(*v, nullptr);
    // Black-box: we only require "something printable" to be produced.
    EXPECT_FALSE(out.empty());
  });
}

TEST_F(ResolveLens0x1cTest_1019, MetadataWithoutRelevantKeysDoesNotThrow_1019) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData md; // empty metadata
  EXPECT_NO_THROW({
    const std::string out = run(*v, &md);
    EXPECT_FALSE(out.empty());
  });
}

TEST_F(ResolveLens0x1cTest_1019, SpecialCaseModelAndLensModelAffectsResolution_1019) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  // Baseline output (no metadata / no special-case)
  const std::string baseline = run(*v, nullptr);
  ASSERT_FALSE(baseline.empty());

  Exiv2::ExifData md;
  // These keys are referenced by resolveLens0x1c
  md["Exif.Image.Model"] = "SLT-A77V";
  md["Exif.Photo.LensModel"] = "100mm F2.8 Macro";

  const std::string special = run(*v, &md);
  ASSERT_FALSE(special.empty());

  // Observable behavior: special-case path should be distinguishable from baseline.
  EXPECT_NE(special, baseline);

  // When the special-case triggers, the function uses index=2 with lensID=0x1c.
  // The known TagDetails table includes index 2 as "Minolta AF 28-70mm F2.8 G".
  // We assert for that recognizable description to ensure the special-case mapping is applied.
  EXPECT_NE(special.find("Minolta"), std::string::npos);
  EXPECT_NE(special.find("28-70mm"), std::string::npos);
  EXPECT_NE(special.find("F2.8"), std::string::npos);
}

TEST_F(ResolveLens0x1cTest_1019, SpecialCaseRequiresBothKeysMatchExactly_1019) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  // Fully-matching metadata
  Exiv2::ExifData md_match;
  md_match["Exif.Image.Model"] = "SLT-A77V";
  md_match["Exif.Photo.LensModel"] = "100mm F2.8 Macro";
  const std::string out_match = run(*v, &md_match);

  // Near-miss: model matches but lens differs
  Exiv2::ExifData md_lens_miss;
  md_lens_miss["Exif.Image.Model"] = "SLT-A77V";
  md_lens_miss["Exif.Photo.LensModel"] = "100mm F2.8 Macro ";// trailing space
  const std::string out_lens_miss = run(*v, &md_lens_miss);

  // Near-miss: lens matches but model differs
  Exiv2::ExifData md_model_miss;
  md_model_miss["Exif.Image.Model"] = "SLT-A77V "; // trailing space
  md_model_miss["Exif.Photo.LensModel"] = "100mm F2.8 Macro";
  const std::string out_model_miss = run(*v, &md_model_miss);

  // Black-box: exact comparison strings are used in the implementation.
  // Therefore, any mismatch should not follow the special-case path.
  EXPECT_NE(out_match, out_lens_miss);
  EXPECT_NE(out_match, out_model_miss);
}

} // namespace