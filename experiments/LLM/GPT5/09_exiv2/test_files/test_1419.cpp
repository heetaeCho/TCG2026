// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::print0xa40c
// File: test_print0xa40c_1419.cpp
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Function under test (defined in ./TestProjects/exiv2/src/tags_int.cpp)
std::ostream& print0xa40c(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0xa40cTest_1419 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUIntValue(uint32_t v) {
    // Use a numeric Value type commonly supported by Exiv2; populate it via read(string)
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    EXPECT_NE(val.get(), nullptr);
    const int rc = val->read(std::to_string(v));
    (void)rc;  // do not assume rc semantics; keep black-box
    return val;
  }

  static Exiv2::Value::UniquePtr makeInvalidNumericValue() {
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    EXPECT_NE(val.get(), nullptr);
    const int rc = val->read(std::string("not-a-number"));
    (void)rc;  // do not assume rc semantics; keep black-box
    return val;
  }
};

TEST_F(Print0xa40cTest_1419, PrintsUnknownFor0_1419) {
  auto v = makeUIntValue(0);
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  EXPECT_EQ(os.str(), "Unknown");
  EXPECT_TRUE(os.good());
}

TEST_F(Print0xa40cTest_1419, PrintsMacroFor1_1419) {
  auto v = makeUIntValue(1);
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  EXPECT_EQ(os.str(), "Macro");
  EXPECT_TRUE(os.good());
}

TEST_F(Print0xa40cTest_1419, PrintsCloseViewFor2_1419) {
  auto v = makeUIntValue(2);
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  EXPECT_EQ(os.str(), "Close view");
  EXPECT_TRUE(os.good());
}

TEST_F(Print0xa40cTest_1419, PrintsDistantViewFor3_1419) {
  auto v = makeUIntValue(3);
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  EXPECT_EQ(os.str(), "Distant view");
  EXPECT_TRUE(os.good());
}

TEST_F(Print0xa40cTest_1419, OutOfRangeValueDoesNotThrowAndProducesSomeOutput_1419) {
  auto v = makeUIntValue(4);
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  // Black-box tolerant checks: should not be empty, and should not match any known mapped strings.
  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out, "Unknown");
  EXPECT_NE(out, "Macro");
  EXPECT_NE(out, "Close view");
  EXPECT_NE(out, "Distant view");
  EXPECT_TRUE(os.good());
}

TEST_F(Print0xa40cTest_1419, LargeOutOfRangeValueDoesNotThrow_1419) {
  auto v = makeUIntValue(1000000U);
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  EXPECT_TRUE(os.good());
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Print0xa40cTest_1419, NonNullMetadataPointerDoesNotChangeMappedOutputForKnownValues_1419) {
  // For known mappings, output should remain consistent regardless of metadata being present.
  Exiv2::ExifData exif;
  auto v = makeUIntValue(2);
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, &exif);
  });

  EXPECT_EQ(os.str(), "Close view");
  EXPECT_TRUE(os.good());
}

TEST_F(Print0xa40cTest_1419, InvalidNumericInputDoesNotThrow_1419) {
  // Exceptional/error-ish case: value parsing may fail; printing should still be safe.
  auto v = makeInvalidNumericValue();
  std::ostringstream os;

  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  EXPECT_TRUE(os.good());
  // Output is implementation-defined; just require it to be safe and produce something (or at least not crash).
  // Some implementations may emit an empty string; avoid over-constraining.
}

TEST_F(Print0xa40cTest_1419, DefaultConstructedNumericValueDoesNotThrow_1419) {
  // Boundary-ish case: Value created but not populated.
  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa40c(os, *v, nullptr);
  });

  EXPECT_TRUE(os.good());
  // Do not assume specific output when the Value has no data.
}

}  // namespace