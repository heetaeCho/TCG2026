// ============================================================================
// TEST_ID: 949
// Unit tests for Exiv2::Internal::printCsLensTypeByMetadata
// File: ./TestProjects/exiv2/src/canonmn_int.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Under test (implemented in src/canonmn_int.cpp)
std::ostream& printCsLensTypeByMetadata(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::TypeId;
using Exiv2::Value;

std::string StreamValueOnly(const Value& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

std::unique_ptr<Value> MakeValue(TypeId type, const std::string& str) {
  auto v = Value::create(type);
  // Use only public interface. Assume Value can parse from string for tests.
  (void)v->read(str);
  return v;
}

ExifData MakeExifWithLens(const std::string& lensUShortTriplet /* e.g. "200 100 1" */) {
  ExifData md;
  ExifKey lensKey("Exif.CanonCs.Lens");
  auto lensVal = MakeValue(TypeId::unsignedShort, lensUShortTriplet);
  md.add(lensKey, lensVal.get());
  return md;
}

}  // namespace

class PrintCsLensTypeByMetadataTest_949 : public ::testing::Test {};

TEST_F(PrintCsLensTypeByMetadataTest_949, NullMetadata_OutputsValue_949) {
  auto v = MakeValue(TypeId::unsignedShort, "123");
  const std::string expected = StreamValueOnly(*v);

  std::ostringstream oss;
  EXPECT_NO_THROW(Exiv2::Internal::printCsLensTypeByMetadata(oss, *v, nullptr));
  EXPECT_EQ(oss.str(), expected);
}

TEST_F(PrintCsLensTypeByMetadataTest_949, WrongTypeId_OutputsValue_949) {
  ExifData md;  // non-null, but value has wrong type
  auto v = MakeValue(TypeId::unsignedLong, "123");
  const std::string expected = StreamValueOnly(*v);

  std::ostringstream oss;
  EXPECT_NO_THROW(Exiv2::Internal::printCsLensTypeByMetadata(oss, *v, &md));
  EXPECT_EQ(oss.str(), expected);
}

TEST_F(PrintCsLensTypeByMetadataTest_949, ZeroCount_OutputsValue_949) {
  ExifData md;

  // Create an unsignedShort Value but do not populate it -> count() expected to be 0.
  auto v = Value::create(TypeId::unsignedShort);
  const std::string expected = StreamValueOnly(*v);

  std::ostringstream oss;
  EXPECT_NO_THROW(Exiv2::Internal::printCsLensTypeByMetadata(oss, *v, &md));
  EXPECT_EQ(oss.str(), expected);
}

TEST_F(PrintCsLensTypeByMetadataTest_949, MissingLensKey_PrintsUnknownLens_949) {
  ExifData md;  // no "Exif.CanonCs.Lens" present
  auto v = MakeValue(TypeId::unsignedShort, "1");

  std::ostringstream oss;
  EXPECT_NO_THROW(Exiv2::Internal::printCsLensTypeByMetadata(oss, *v, &md));
  EXPECT_EQ(oss.str(), "Unknown Lens (1)");
}

TEST_F(PrintCsLensTypeByMetadataTest_949, LensKeyWithTooFewComponents_PrintsUnknownLens_949) {
  // Lens key exists but count < 3 -> should be Unknown Lens (lensType)
  ExifData md;
  {
    ExifKey lensKey("Exif.CanonCs.Lens");
    auto lensVal = MakeValue(TypeId::unsignedShort, "200 100");  // only 2 values
    md.add(lensKey, lensVal.get());
  }

  auto v = MakeValue(TypeId::unsignedShort, "2");

  std::ostringstream oss;
  EXPECT_NO_THROW(Exiv2::Internal::printCsLensTypeByMetadata(oss, *v, &md));
  EXPECT_EQ(oss.str(), "Unknown Lens (2)");
}

TEST_F(PrintCsLensTypeByMetadataTest_949, MissingMaxApertureKey_PrintsUnknownLens_949) {
  // Pass the Lens-key validation (>=3, unsignedShort, toFloat(2)!=0),
  // but omit "Exif.CanonCs.MaxAperture" -> Unknown Lens (lensType)
  ExifData md = MakeExifWithLens("200 100 1");  // third value non-zero

  auto v = MakeValue(TypeId::unsignedShort, "3");

  std::ostringstream oss;
  EXPECT_NO_THROW(Exiv2::Internal::printCsLensTypeByMetadata(oss, *v, &md));
  EXPECT_EQ(oss.str(), "Unknown Lens (3)");
}