// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_print0xa401_1411.cpp
//
// Unit tests for:
//   Exiv2::Internal::print0xa401(std::ostream& os, const Value& value, const ExifData* metadata)
//
// Constraints honored:
// - Treat implementation as black box (no internal logic re-implementation).
// - Test only observable behavior via public interfaces and returned output/stream ref.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Declaration for the function under test (defined in tags_int.cpp).
std::ostream& print0xa401(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0xa401Test_1411 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(const std::string& s) {
    // Use a public factory and public read API only.
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_NO_THROW({
      // read(string) is part of the public interface.
      (void)v->read(s);
    });
    return v;
  }
};

TEST_F(Print0xa401Test_1411, ReturnsSameStreamReference_1411) {
  auto v = makeUShortValue("0");
  std::ostringstream os;

  std::ostream& returned = Exiv2::Internal::print0xa401(os, *v, nullptr);

  EXPECT_EQ(&returned, &os);
}

TEST_F(Print0xa401Test_1411, NormalProcessForValue0_1411) {
  auto v = makeUShortValue("0");
  std::ostringstream os;

  Exiv2::Internal::print0xa401(os, *v, nullptr);

  const std::string out = os.str();
  // Observable behavior: should render the known TagDetails string for 0.
  EXPECT_NE(out.find("Normal process"), std::string::npos);
}

TEST_F(Print0xa401Test_1411, CustomProcessForValue1_1411) {
  auto v = makeUShortValue("1");
  std::ostringstream os;

  Exiv2::Internal::print0xa401(os, *v, nullptr);

  const std::string out = os.str();
  // Observable behavior: should render the known TagDetails string for 1.
  EXPECT_NE(out.find("Custom process"), std::string::npos);
}

TEST_F(Print0xa401Test_1411, HandlesNullMetadataPointer_1411) {
  auto v = makeUShortValue("1");
  std::ostringstream os;

  // Should be safe to call with nullptr metadata (signature permits it).
  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa401(os, *v, nullptr);
  });

  EXPECT_FALSE(os.str().empty());
}

TEST_F(Print0xa401Test_1411, OutOfRangeValueDoesNotCrashAndProducesSomeOutput_1411) {
  auto v = makeUShortValue("2");  // Not in the provided TagDetails[2].
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa401(os, *v, nullptr);
  });

  const std::string out = os.str();
  // Black-box friendly assertions: it should produce *some* representation.
  EXPECT_FALSE(out.empty());
  // And it should not incorrectly claim either known label.
  EXPECT_EQ(out.find("Normal process"), std::string::npos);
  EXPECT_EQ(out.find("Custom process"), std::string::npos);
}

}  // namespace