// =================================================================================================
// File:        test_print_exif_unit_1381.cpp
// Description: Unit tests for Exiv2::Internal::printExifUnit (tags_int.cpp)
// Test ID:     1381
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Interface under test (implemented in ./TestProjects/exiv2/src/tags_int.cpp)
std::ostream& printExifUnit(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class PrintExifUnitTest_1381 : public ::testing::Test {
protected:
  static std::unique_ptr<Exiv2::Value> MakeUShortValueFromString(const std::string& s) {
    // Use a common numeric type used for Exif "unit"-like tags.
    // We do not assume internal behavior beyond Value's public interface.
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    // If parsing fails, tests that require valid parsing will assert via output checks.
    (void)v->read(s);
    return v;
  }

  static std::string PrintToString(const Exiv2::Value& value, const Exiv2::ExifData* md, std::ostream** out_stream_ptr = nullptr) {
    std::ostringstream oss;
    std::ostream& ret = Exiv2::Internal::printExifUnit(oss, value, md);
    if (out_stream_ptr) *out_stream_ptr = &ret;
    return oss.str();
  }
};

TEST_F(PrintExifUnitTest_1381, ReturnsSameStreamReference_1381) {
  auto v = MakeUShortValueFromString("1");
  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printExifUnit(oss, *v, nullptr);

  // Observable behavior: function returns an ostream&; it should be the same stream passed in.
  EXPECT_EQ(&ret, &oss);
}

TEST_F(PrintExifUnitTest_1381, PrintsNoneForUnitCode1_1381) {
  auto v = MakeUShortValueFromString("1");
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_EQ(out, "none");
}

TEST_F(PrintExifUnitTest_1381, PrintsInchForUnitCode2_1381) {
  auto v = MakeUShortValueFromString("2");
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_EQ(out, "inch");
}

TEST_F(PrintExifUnitTest_1381, PrintsCmForUnitCode3_1381) {
  auto v = MakeUShortValueFromString("3");
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_EQ(out, "cm");
}

TEST_F(PrintExifUnitTest_1381, OutputDoesNotDependOnMetadataPointerForKnownCodes_1381) {
  auto v2 = MakeUShortValueFromString("2");

  Exiv2::ExifData md;  // Empty metadata object
  const std::string out_null = PrintToString(*v2, nullptr);
  const std::string out_md = PrintToString(*v2, &md);

  // Observable behavior: for unit printing, metadata is not expected to change the mapping output.
  // We only assert equality for a known code to avoid assumptions for unknown values.
  EXPECT_EQ(out_null, out_md);
  EXPECT_EQ(out_md, "inch");
}

TEST_F(PrintExifUnitTest_1381, UnknownUnitCodeDoesNotCrashAndProducesSomeOutput_1381) {
  auto v = MakeUShortValueFromString("0");
  std::ostream* returned_stream = nullptr;
  const std::string out = PrintToString(*v, nullptr, &returned_stream);

  ASSERT_NE(returned_stream, nullptr);
  // Must return the same stream reference (checked again here as part of boundary case).
  // Note: returned_stream points to a local oss inside PrintToString; we only check it was set.
  EXPECT_FALSE(out.empty());

  // Be tolerant of implementation: unknown may print "0", "unknown", or similar.
  // Still enforce it should NOT be one of the known labels.
  EXPECT_NE(out, "none");
  EXPECT_NE(out, "inch");
  EXPECT_NE(out, "cm");

  // And require it looks plausibly related to the input (either numeric or an "unknown"-style marker).
  const bool has_numeric = (out.find('0') != std::string::npos);
  const bool has_unknown_word =
      (out.find("unknown") != std::string::npos) || (out.find("Unknown") != std::string::npos);
  EXPECT_TRUE(has_numeric || has_unknown_word);
}

TEST_F(PrintExifUnitTest_1381, ValueWithNoDataDoesNotCrash_1381) {
  // Boundary/exceptional-like case: construct a Value but don't populate it with read().
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  // Observable requirement: should be callable without crashing and return a stream reference.
  std::ostream& ret = Exiv2::Internal::printExifUnit(oss, *v, nullptr);
  EXPECT_EQ(&ret, &oss);

  // Output may be empty or some default; we don't assume internal formatting.
  // Just ensure the stream is still usable.
  oss << "";
  SUCCEED();
}

}  // namespace