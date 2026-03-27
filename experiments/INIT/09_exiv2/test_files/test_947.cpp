// =================================================================================================
// TEST_ID: 947
// File: test_canonmn_int_printCsLensFFFF_947.cpp
// Unit tests for Exiv2::Internal::printCsLensFFFF (black-box tests)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Function under test (defined in ./TestProjects/exiv2/src/canonmn_int.cpp)
std::ostream& printCsLensFFFF(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

// A Value implementation that throws from toString(size_t), which is commonly used by Value::toString().
class ThrowingToStringValue final : public Exiv2::Value {
 public:
  explicit ThrowingToStringValue(Exiv2::TypeId typeId = Exiv2::asciiString)
      : Exiv2::Value(typeId) {}

  // If Value::toString() calls virtual toString(size_t), this will throw and exercise the catch path.
  std::string toString(size_t /*n*/) const override { throw std::runtime_error("toString(size_t) failure"); }

 private:
  // Value uses clone() internally; provide clone_ so the value can be copied/cloned by Exiv2 containers.
  const Exiv2::Value* clone_() override { return new ThrowingToStringValue(*this); }
};

std::unique_ptr<Exiv2::Value> makeUShortValue(uint16_t v) {
  auto vp = Exiv2::Value::create(Exiv2::unsignedShort);
  // Use string read to avoid assumptions about internal byte layout.
  vp->read(std::to_string(v));
  return std::unique_ptr<Exiv2::Value>(vp.release());
}

}  // namespace

class CanonMnPrintCsLensFFFFTest_947 : public ::testing::Test {
 protected:
  static std::string call(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    Exiv2::Internal::printCsLensFFFF(oss, v, md);
    return oss.str();
  }
};

TEST_F(CanonMnPrintCsLensFFFFTest_947, SpecialCase_MatchingMetadataPrintsExpectedLensName_947) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = "Canon EOS 30D";
  md["Exif.CanonCs.Lens"] = "24 24 1";
  md["Exif.CanonCs.MaxAperture"] = "95";

  // Even if the provided 'value' would normally map to something else, the special-case should win.
  auto v = makeUShortValue(1);

  const std::string out = call(*v, &md);
  EXPECT_EQ("Canon EF-S 24mm f/2.8 STM", out);
}

TEST_F(CanonMnPrintCsLensFFFFTest_947, NonMatchingModel_DoesNotUseSpecialCase_947) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = "Canon EOS 40D";  // differs
  md["Exif.CanonCs.Lens"] = "24 24 1";
  md["Exif.CanonCs.MaxAperture"] = "95";

  auto v = makeUShortValue(1);

  const std::string out = call(*v, &md);
  EXPECT_NE("Canon EF-S 24mm f/2.8 STM", out);
  EXPECT_FALSE(out.empty());  // should still produce some output via fallback printer
}

TEST_F(CanonMnPrintCsLensFFFFTest_947, MissingLensKey_DoesNotUseSpecialCase_947) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = "Canon EOS 30D";
  // md["Exif.CanonCs.Lens"] missing
  md["Exif.CanonCs.MaxAperture"] = "95";

  auto v = makeUShortValue(1);

  const std::string out = call(*v, &md);
  EXPECT_NE("Canon EF-S 24mm f/2.8 STM", out);
  EXPECT_FALSE(out.empty());
}

TEST_F(CanonMnPrintCsLensFFFFTest_947, MissingMaxApertureKey_DoesNotUseSpecialCase_947) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = "Canon EOS 30D";
  md["Exif.CanonCs.Lens"] = "24 24 1";
  // md["Exif.CanonCs.MaxAperture"] missing

  auto v = makeUShortValue(1);

  const std::string out = call(*v, &md);
  EXPECT_NE("Canon EF-S 24mm f/2.8 STM", out);
  EXPECT_FALSE(out.empty());
}

TEST_F(CanonMnPrintCsLensFFFFTest_947, SlightMismatchInLensString_DoesNotUseSpecialCase_947) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = "Canon EOS 30D";
  md["Exif.CanonCs.Lens"] = "24 24 2";  // differs
  md["Exif.CanonCs.MaxAperture"] = "95";

  auto v = makeUShortValue(1);

  const std::string out = call(*v, &md);
  EXPECT_NE("Canon EF-S 24mm f/2.8 STM", out);
  EXPECT_FALSE(out.empty());
}

TEST_F(CanonMnPrintCsLensFFFFTest_947, SlightMismatchInApertureString_DoesNotUseSpecialCase_947) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = "Canon EOS 30D";
  md["Exif.CanonCs.Lens"] = "24 24 1";
  md["Exif.CanonCs.MaxAperture"] = "96";  // differs

  auto v = makeUShortValue(1);

  const std::string out = call(*v, &md);
  EXPECT_NE("Canon EF-S 24mm f/2.8 STM", out);
  EXPECT_FALSE(out.empty());
}

TEST_F(CanonMnPrintCsLensFFFFTest_947, SpecialCase_OverridesValueBasedMapping_947) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = "Canon EOS 30D";
  md["Exif.CanonCs.Lens"] = "24 24 1";
  md["Exif.CanonCs.MaxAperture"] = "95";

  // Boundary-ish: use a value that likely maps to "n/a" or some other string.
  auto v = makeUShortValue(65535);

  const std::string out = call(*v, &md);
  EXPECT_EQ("Canon EF-S 24mm f/2.8 STM", out);
}

TEST_F(CanonMnPrintCsLensFFFFTest_947, ExceptionInMetadataValue_IsCaughtAndFallbackStillProducesOutput_947) {
  Exiv2::ExifData md;

  // Add a key that will be found, but whose value throws during toString evaluation.
  ThrowingToStringValue throwingValue;
  md.add(Exiv2::ExifKey("Exif.Image.Model"), &throwingValue);

  // Provide other keys too; regardless, the function should swallow std::exception and use fallback.
  md["Exif.CanonCs.Lens"] = "24 24 1";
  md["Exif.CanonCs.MaxAperture"] = "95";

  auto v = makeUShortValue(1);

  EXPECT_NO_THROW({
    const std::string out = call(*v, &md);
    EXPECT_FALSE(out.empty());
    // Since we threw before matching, we should not get the special-case string.
    EXPECT_NE("Canon EF-S 24mm f/2.8 STM", out);
  });
}