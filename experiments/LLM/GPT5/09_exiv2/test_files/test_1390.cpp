// File: test_tags_int_print0x0019_1390.cpp
//
// Unit tests for Exiv2::Internal::print0x0019()
// NOTE: Tests treat implementation as a black box and validate only observable behavior.

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

namespace Exiv2::Internal {
// Function under test (defined in src/tags_int.cpp)
std::ostream& print0x0019(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class Print0x0019Test_1390 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr MakeAsciiValueOrSkip(const std::string& s) {
    // We intentionally avoid relying on internal formatting logic.
    // We only need a Value that can hold a small string and report ok().
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    if (!v) {
      GTEST_SKIP() << "Value::create(asciiString) returned null in this build.";
    }
    (void)v->read(s);
    if (!v->ok()) {
      GTEST_SKIP() << "Value could not read provided string in this build.";
    }
    return v;
  }

  static std::string Render(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    auto& ret = Exiv2::Internal::print0x0019(oss, v, md);
    // Return value must be the same stream reference; asserted in dedicated tests too.
    (void)ret;
    return oss.str();
  }
};

TEST_F(Print0x0019Test_1390, ReturnsSameStreamReference_1390) {
  auto v = MakeAsciiValueOrSkip("K");

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0x0019(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
}

TEST_F(Print0x0019Test_1390, ProducesSomeOutputForKnownInputs_1390) {
  auto vK = MakeAsciiValueOrSkip("K");
  auto vM = MakeAsciiValueOrSkip("M");
  auto vN = MakeAsciiValueOrSkip("N");

  const std::string outK = Render(*vK, nullptr);
  const std::string outM = Render(*vM, nullptr);
  const std::string outN = Render(*vN, nullptr);

  EXPECT_FALSE(outK.empty());
  EXPECT_FALSE(outM.empty());
  EXPECT_FALSE(outN.empty());
}

TEST_F(Print0x0019Test_1390, DifferentKnownInputsYieldDifferentOutputs_1390) {
  auto vK = MakeAsciiValueOrSkip("K");
  auto vM = MakeAsciiValueOrSkip("M");
  auto vN = MakeAsciiValueOrSkip("N");

  const std::string outK = Render(*vK, nullptr);
  const std::string outM = Render(*vM, nullptr);
  const std::string outN = Render(*vN, nullptr);

  // Black-box check: these represent different codes, so output should not all collapse to the same string.
  EXPECT_NE(outK, outM);
  EXPECT_NE(outK, outN);
  EXPECT_NE(outM, outN);
}

TEST_F(Print0x0019Test_1390, HandlesNullMetadataPointer_1390) {
  auto v = MakeAsciiValueOrSkip("K");

  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::print0x0019(oss, *v, nullptr);
  });
}

TEST_F(Print0x0019Test_1390, AcceptsNonNullMetadataPointer_1390) {
  auto v = MakeAsciiValueOrSkip("K");

  Exiv2::ExifData exif;  // Content is intentionally irrelevant; should not be required for printing.
  std::ostringstream oss;

  EXPECT_NO_THROW({
    (void)Exiv2::Internal::print0x0019(oss, *v, &exif);
  });
}

TEST_F(Print0x0019Test_1390, OutputDoesNotDependOnMetadataForSimpleCase_1390) {
  auto v = MakeAsciiValueOrSkip("M");

  Exiv2::ExifData exif;
  const std::string outNull = Render(*v, nullptr);
  const std::string outNonNull = Render(*v, &exif);

  // For a simple lookup-style print, metadata is expected to be irrelevant.
  // This is still a black-box assertion about observable consistency across metadata pointers.
  EXPECT_EQ(outNull, outNonNull);
}

TEST_F(Print0x0019Test_1390, UnknownInputStillProducesSomeOutput_1390) {
  auto vUnknown = MakeAsciiValueOrSkip("X");
  const std::string out = Render(*vUnknown, nullptr);

  EXPECT_FALSE(out.empty());
}

TEST_F(Print0x0019Test_1390, UnknownInputDiffersFromAtLeastOneKnownOutput_1390) {
  auto vUnknown = MakeAsciiValueOrSkip("X");
  auto vKnown = MakeAsciiValueOrSkip("K");

  const std::string outUnknown = Render(*vUnknown, nullptr);
  const std::string outKnown = Render(*vKnown, nullptr);

  // Avoid assuming exact formatting; just ensure it isn't identical to a known code output.
  EXPECT_NE(outUnknown, outKnown);
}

TEST_F(Print0x0019Test_1390, EmptyStringValueBoundaryCase_1390) {
  auto vEmpty = MakeAsciiValueOrSkip("");

  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::print0x0019(oss, *vEmpty, nullptr);
  });

  // Observable behavior: should emit *something* (could be empty depending on implementation),
  // but the call must be safe and return the same stream.
  // So here we only assert safety + valid stream reference.
  std::ostream& ret = Exiv2::Internal::print0x0019(oss, *vEmpty, nullptr);
  EXPECT_EQ(&ret, &oss);
}

}  // namespace