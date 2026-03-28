// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_resolveLens0xff_1023.cpp
//
// Unit tests for Exiv2::Internal::resolveLens0xff (black-box tests via its interface).
//
// NOTE: This test intentionally includes the production .cpp to access the internal-linkage
//       function (static) in the same translation unit.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

// Include the implementation so the TU can call the internal-linkage function.
#include "minoltamn_int.cpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;

static Value::UniquePtr makeNumericValue(long v) {
  // Use a numeric type that can represent lens IDs like 0xff (255) reliably.
  // We do not assume the internal parsing/printing beyond the public interface of Value.
  auto val = Value::create(Exiv2::unsignedLong);
  // Value::read(std::string) is part of the public interface.
  (void)val->read(std::to_string(v));
  return val;
}

static std::string printFallback(const Value& value, const ExifData* md) {
  std::ostringstream os;
  // Black-box call to the fallback printer used by resolveLens0xff on non-match/error.
  EXV_PRINT_TAG(Exiv2::Internal::minoltaSonyLensID)(os, value, md);
  return os.str();
}

static std::string runResolve(const Value& value, const ExifData* md) {
  std::ostringstream os;
  auto& ret = Exiv2::Internal::resolveLens0xff(os, value, md);
  EXPECT_EQ(&ret, &os);  // Should return the same stream reference.
  return os.str();
}

class ResolveLens0xffTest_1023 : public ::testing::Test {};

}  // namespace

TEST_F(ResolveLens0xffTest_1023, ReturnsSameStreamReference_1023) {
  ExifData md;
  auto v = makeNumericValue(0xff);

  std::ostringstream os;
  auto& ret = Exiv2::Internal::resolveLens0xff(os, *v, &md);
  EXPECT_EQ(&ret, &os);
}

TEST_F(ResolveLens0xffTest_1023, FallsBackWhenMetadataIsNull_1023) {
  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, /*md=*/nullptr);
  const std::string fb = printFallback(*v, /*md=*/nullptr);

  EXPECT_EQ(out, fb);
}

TEST_F(ResolveLens0xffTest_1023, FallsBackWhenRequiredKeysMissing_1023) {
  ExifData md;  // No keys set -> helpers inside resolveLens0xff may throw and be caught.
  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, &md);
  const std::string fb = printFallback(*v, &md);

  EXPECT_EQ(out, fb);
}

TEST_F(ResolveLens0xffTest_1023, ResolvesWhenAllConditionsMatch_FocalLengthLowerBoundary_1023) {
  ExifData md;
  md["Exif.Image.Model"] = "SLT-A77V";
  md["Exif.Photo.MaxApertureValue"] = "760/256";
  md["Exif.Photo.FocalLength"] = 17;  // boundary value mentioned in the implementation

  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, &md);
  const std::string fb = printFallback(*v, &md);

  // Observable behavior: on match it should not take the fallback path.
  EXPECT_NE(out, fb);
  EXPECT_FALSE(out.empty());
}

TEST_F(ResolveLens0xffTest_1023, ResolvesWhenAllConditionsMatch_FocalLengthUpperBoundary_1023) {
  ExifData md;
  md["Exif.Image.Model"] = "SLT-A77V";
  md["Exif.Photo.MaxApertureValue"] = "760/256";
  md["Exif.Photo.FocalLength"] = 50;  // boundary value mentioned in the implementation

  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, &md);
  const std::string fb = printFallback(*v, &md);

  EXPECT_NE(out, fb);
  EXPECT_FALSE(out.empty());
}

TEST_F(ResolveLens0xffTest_1023, DoesNotResolveWhenFocalLengthBelowRange_1023) {
  ExifData md;
  md["Exif.Image.Model"] = "SLT-A77V";
  md["Exif.Photo.MaxApertureValue"] = "760/256";
  md["Exif.Photo.FocalLength"] = 16;  // just below stated range

  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, &md);
  const std::string fb = printFallback(*v, &md);

  EXPECT_EQ(out, fb);
}

TEST_F(ResolveLens0xffTest_1023, DoesNotResolveWhenFocalLengthAboveRange_1023) {
  ExifData md;
  md["Exif.Image.Model"] = "SLT-A77V";
  md["Exif.Photo.MaxApertureValue"] = "760/256";
  md["Exif.Photo.FocalLength"] = 51;  // just above stated range

  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, &md);
  const std::string fb = printFallback(*v, &md);

  EXPECT_EQ(out, fb);
}

TEST_F(ResolveLens0xffTest_1023, DoesNotResolveWhenModelDoesNotMatch_1023) {
  ExifData md;
  md["Exif.Image.Model"] = "SLT-A77";  // different model
  md["Exif.Photo.MaxApertureValue"] = "760/256";
  md["Exif.Photo.FocalLength"] = 17;

  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, &md);
  const std::string fb = printFallback(*v, &md);

  EXPECT_EQ(out, fb);
}

TEST_F(ResolveLens0xffTest_1023, DoesNotResolveWhenMaxApertureDoesNotMatch_1023) {
  ExifData md;
  md["Exif.Image.Model"] = "SLT-A77V";
  md["Exif.Photo.MaxApertureValue"] = "759/256";  // different
  md["Exif.Photo.FocalLength"] = 17;

  auto v = makeNumericValue(0xff);

  const std::string out = runResolve(*v, &md);
  const std::string fb = printFallback(*v, &md);

  EXPECT_EQ(out, fb);
}