// -----------------------------------------------------------------------------
// Unit tests for resolveLens0x29 (minoltamn_int.cpp)
// TEST_ID: 1020
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

// Include the .cpp to access the internal-linkage (static) function in the same TU.
// This is a common technique for unit-testing file-local helpers without changing
// production code.
#include "minoltamn_int.cpp"

namespace {

class ResolveLens0x29Test_1020 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeValue_() {
    // The actual value content isn't required for the "match" path because the
    // function uses metadata strings to choose the resolved-lens branch.
    // For fallback paths, it still must be a valid Value object.
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    v->read("0");
    return v;
  }

  static void setExifString_(Exiv2::ExifData& md, const std::string& key, const std::string& value) {
    // Use only the public interface. Exiv2 commonly supports assigning a string
    // to an Exifdatum via operator=.
    md[key] = value;
  }

  static std::string call_(const Exiv2::Value& value, const Exiv2::ExifData* md) {
    std::ostringstream os;
    // Function is in Exiv2::Internal in the included translation unit.
    Exiv2::Internal::resolveLens0x29(os, value, md);
    return os.str();
  }
};

TEST_F(ResolveLens0x29Test_1020, MatchingModelAndLensProducesResolvedOutput_1020) {
  auto v = makeValue_();

  Exiv2::ExifData md;
  setExifString_(md, "Exif.Image.Model", "SLT-A77V");
  setExifString_(md, "Exif.Photo.LensModel", "DT 11-18mm F4.5-5.6");

  const std::string out = call_(*v, &md);

  // Observable expectations:
  //  - does not crash
  //  - produces some output
  //  - for the known special-case mapping (index=2), output should reflect a resolved lens name.
  EXPECT_FALSE(out.empty());

  // The global table shown in the prompt indicates index 2 is:
  // "Minolta AF 28-70mm F2.8 G"
  // We assert the resolved output contains that lens name (observable behavior).
  EXPECT_NE(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x29Test_1020, NonMatchingMetadataFallsBackToDefaultPrinting_1020) {
  auto v = makeValue_();

  Exiv2::ExifData md_match;
  setExifString_(md_match, "Exif.Image.Model", "SLT-A77V");
  setExifString_(md_match, "Exif.Photo.LensModel", "DT 11-18mm F4.5-5.6");
  const std::string out_match = call_(*v, &md_match);
  ASSERT_FALSE(out_match.empty());

  Exiv2::ExifData md_nonmatch;
  setExifString_(md_nonmatch, "Exif.Image.Model", "SLT-A77V");               // model matches
  setExifString_(md_nonmatch, "Exif.Photo.LensModel", "Some Other Lens");    // lens does not
  const std::string out_nonmatch = call_(*v, &md_nonmatch);

  EXPECT_FALSE(out_nonmatch.empty());

  // We don't assume the exact fallback formatting; we only assert observable
  // difference from the known special-case resolved output.
  EXPECT_NE(out_nonmatch, out_match);

  // And it should not incorrectly claim the special-case resolved lens name.
  EXPECT_EQ(out_nonmatch.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x29Test_1020, NullMetadataDoesNotThrowAndProducesOutput_1020) {
  auto v = makeValue_();

  std::string out;
  EXPECT_NO_THROW(out = call_(*v, nullptr));
  EXPECT_FALSE(out.empty());
}

TEST_F(ResolveLens0x29Test_1020, EmptyMetadataDoesNotThrowAndProducesOutput_1020) {
  auto v = makeValue_();

  Exiv2::ExifData md;  // no keys set
  std::string out;
  EXPECT_NO_THROW(out = call_(*v, &md));
  EXPECT_FALSE(out.empty());

  // With no keys, the special-case should not trigger, so it should not claim
  // the special-case resolved lens string.
  EXPECT_EQ(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x29Test_1020, OnlyLensMatchesButModelDoesNotDoesNotTriggerSpecialCase_1020) {
  auto v = makeValue_();

  Exiv2::ExifData md_match;
  setExifString_(md_match, "Exif.Image.Model", "SLT-A77V");
  setExifString_(md_match, "Exif.Photo.LensModel", "DT 11-18mm F4.5-5.6");
  const std::string out_match = call_(*v, &md_match);
  ASSERT_FALSE(out_match.empty());
  ASSERT_NE(out_match.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);

  Exiv2::ExifData md;
  setExifString_(md, "Exif.Image.Model", "Not-A77V"); // model differs
  setExifString_(md, "Exif.Photo.LensModel", "DT 11-18mm F4.5-5.6"); // lens matches
  const std::string out = call_(*v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out, out_match);
  EXPECT_EQ(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

}  // namespace