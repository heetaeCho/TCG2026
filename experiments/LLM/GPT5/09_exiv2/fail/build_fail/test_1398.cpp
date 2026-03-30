// -------------------------------------------------------------------------------------------------
// TEST_ID: 1398
// File: test_tags_int_print0x8827_1398.cpp
//
// Unit tests for:
//   Exiv2::Internal::print0x8827(std::ostream& os, const Value& value, const ExifData*)
//
// Constraints honored:
// - Treat implementation as a black box (assert only observable behavior).
// - Do not access private state.
// - Use mocks only for external collaborators (not needed here).
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths to your project layout as needed)
#include <exiv2/exiv2.hpp>

// Forward declare the internal function under test (in case internal header isn't exposed).
// If you have the proper internal header, prefer including it instead.
namespace Exiv2 {
namespace Internal {
std::ostream& print0x8827(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0x8827Test_1398 : public ::testing::Test {
 protected:
  std::ostringstream os_;
  Exiv2::ExifData exif_;  // optional; can pass nullptr per signature
};

static std::string Trimmed(const std::string& s) {
  // For safety across platforms, keep exact output; do not trim.
  return s;
}

TEST_F(Print0x8827Test_1398, WritesIntegerRepresentationForPositive_1398) {
  // Arrange
  const std::int64_t input = 123456789LL;
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read(std::to_string(input)));

  // Act
  std::ostream& ret = Exiv2::Internal::print0x8827(os_, *v, nullptr);

  // Assert (observable behavior)
  EXPECT_EQ(&ret, &os_) << "Function should return the same ostream reference it writes to.";
  EXPECT_EQ(Trimmed(os_.str()), std::to_string(input));
}

TEST_F(Print0x8827Test_1398, WritesIntegerRepresentationForNegative_1398) {
  // Arrange
  const std::int64_t input = -42LL;
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read(std::to_string(input)));

  // Act
  Exiv2::Internal::print0x8827(os_, *v, nullptr);

  // Assert
  EXPECT_EQ(Trimmed(os_.str()), std::to_string(input));
}

TEST_F(Print0x8827Test_1398, WritesZero_1398) {
  // Arrange
  const std::int64_t input = 0;
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("0"));

  // Act
  Exiv2::Internal::print0x8827(os_, *v, nullptr);

  // Assert
  EXPECT_EQ(Trimmed(os_.str()), "0");
}

TEST_F(Print0x8827Test_1398, BoundaryWritesInt64Min_1398) {
  // Arrange
  const std::int64_t input = (std::numeric_limits<std::int64_t>::min)();
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read(std::to_string(input)));

  // Act
  Exiv2::Internal::print0x8827(os_, *v, nullptr);

  // Assert
  EXPECT_EQ(Trimmed(os_.str()), std::to_string(input));
}

TEST_F(Print0x8827Test_1398, BoundaryWritesInt64Max_1398) {
  // Arrange
  const std::int64_t input = (std::numeric_limits<std::int64_t>::max)();
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read(std::to_string(input)));

  // Act
  Exiv2::Internal::print0x8827(os_, *v, nullptr);

  // Assert
  EXPECT_EQ(Trimmed(os_.str()), std::to_string(input));
}

TEST_F(Print0x8827Test_1398, IgnoresExifDataPointerWhenNull_1398) {
  // Arrange
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("7"));

  // Act + Assert (should not crash; output should still be produced)
  EXPECT_NO_THROW({
    Exiv2::Internal::print0x8827(os_, *v, nullptr);
  });
  EXPECT_EQ(Trimmed(os_.str()), "7");
}

TEST_F(Print0x8827Test_1398, IgnoresExifDataPointerWhenNonNull_1398) {
  // Arrange
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("99"));

  // Act + Assert (should not crash; output should still be produced)
  EXPECT_NO_THROW({
    Exiv2::Internal::print0x8827(os_, *v, &exif_);
  });
  EXPECT_EQ(Trimmed(os_.str()), "99");
}

TEST_F(Print0x8827Test_1398, PropagatesStreamFailureState_1398) {
  // Arrange: put stream in bad state before call
  os_.setstate(std::ios::badbit);

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLongType);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("123"));

  // Act
  std::ostream& ret = Exiv2::Internal::print0x8827(os_, *v, nullptr);

  // Assert: still the same stream; badbit remains set (observable)
  EXPECT_EQ(&ret, &os_);
  EXPECT_TRUE(os_.bad());
}

}  // namespace