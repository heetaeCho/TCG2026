// File: test_print0xa405_1415.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

// Forward declaration (function under test lives in tags_int.cpp)
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa405(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*);
}  // namespace Internal
}  // namespace Exiv2

namespace {

Exiv2::Value::UniquePtr makeInt64Value(int64_t v) {
  // Use a numeric Value type and populate it via read(), staying within public APIs.
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::signedLongLong);
  val->read(std::to_string(v));
  return val;
}

class Print0xa405Test_1415 : public ::testing::Test {};

}  // namespace

TEST_F(Print0xa405Test_1415, NonZeroPrintsLengthWithSuffix_1415) {
  auto value = makeInt64Value(12);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0xa405(oss, *value, nullptr);

  EXPECT_EQ(&ret, &oss);
  EXPECT_EQ(oss.str(), "12.0 mm");
}

TEST_F(Print0xa405Test_1415, ZeroPrintsUnknown_1415) {
  auto value = makeInt64Value(0);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0xa405(oss, *value, nullptr);

  EXPECT_EQ(&ret, &oss);
  // Note: _("Unknown") is expected to be "Unknown" under the usual test locale.
  EXPECT_EQ(oss.str(), "Unknown");
}

TEST_F(Print0xa405Test_1415, NegativeValueStillFormatsWithMmSuffix_1415) {
  auto value = makeInt64Value(-5);

  std::ostringstream oss;
  Exiv2::Internal::print0xa405(oss, *value, nullptr);

  EXPECT_EQ(oss.str(), "-5.0 mm");
}

TEST_F(Print0xa405Test_1415, Int64MaxFormatsAndDoesNotCrash_1415) {
  auto value = makeInt64Value((std::numeric_limits<int64_t>::max)());

  std::ostringstream oss;
  Exiv2::Internal::print0xa405(oss, *value, nullptr);

  const std::string out = oss.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find(".0 mm"), std::string::npos);
  EXPECT_NE(out.find(std::to_string((std::numeric_limits<int64_t>::max)())), std::string::npos);
}

TEST_F(Print0xa405Test_1415, NullExifDataIsAccepted_1415) {
  auto value = makeInt64Value(1);

  std::ostringstream oss;
  Exiv2::Internal::print0xa405(oss, *value, nullptr);

  EXPECT_EQ(oss.str(), "1.0 mm");
}