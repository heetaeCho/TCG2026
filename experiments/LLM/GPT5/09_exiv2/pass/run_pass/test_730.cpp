// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 730
//
// Unit tests for Exiv2::Exifdatum::operator=(const Exifdatum&)
// File under test: ./TestProjects/exiv2/src/exif.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class ExifdatumAssignmentTest_730 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeDatumWithStringValue(const std::string& keyStr, const std::string& valueStr) {
    Exiv2::ExifKey key(keyStr);
    auto v = Exiv2::Value::create(key.defaultTypeId());
    Exiv2::Exifdatum d(key, v.get());
    // Use the public interface to set a deterministic value.
    d = valueStr;
    return d;
  }

  static Exiv2::Exifdatum MakeDatumWithNullValuePtr(const std::string& keyStr) {
    Exiv2::ExifKey key(keyStr);
    Exiv2::Exifdatum d(key, nullptr);
    return d;
  }
};

TEST_F(ExifdatumAssignmentTest_730, CopiesKeyAndValue_730) {
  auto rhs = MakeDatumWithStringValue("Exif.Image.Make", "Canon");
  auto lhs = MakeDatumWithStringValue("Exif.Image.Model", "EOS");

  lhs = rhs;

  EXPECT_EQ(lhs.key(), rhs.key());
  EXPECT_EQ(lhs.toString(), rhs.toString());

  // Also verify getValue() is usable and consistent with toString().
  auto lhsV = lhs.getValue();
  ASSERT_NE(lhsV.get(), nullptr);
  EXPECT_EQ(lhsV->toString(), lhs.toString());
}

TEST_F(ExifdatumAssignmentTest_730, SelfAssignmentDoesNotChangeObservableState_730) {
  auto d = MakeDatumWithStringValue("Exif.Image.Make", "Canon");

  const std::string beforeKey = d.key();
  const std::string beforeStr = d.toString();

  d = d;

  EXPECT_EQ(d.key(), beforeKey);
  EXPECT_EQ(d.toString(), beforeStr);
}

TEST_F(ExifdatumAssignmentTest_730, PostAssignmentRhsMutationDoesNotAffectLhs_730) {
  auto rhs = MakeDatumWithStringValue("Exif.Image.Make", "Canon");
  auto lhs = MakeDatumWithStringValue("Exif.Image.Model", "EOS");

  lhs = rhs;

  // Mutate RHS via public API; LHS should remain as it was after assignment.
  rhs = std::string("Nikon");

  EXPECT_EQ(lhs.key(), "Exif.Image.Make");
  EXPECT_EQ(lhs.toString(), "Canon");
  EXPECT_EQ(rhs.toString(), "Nikon");
}

TEST_F(ExifdatumAssignmentTest_730, PostAssignmentRhsReplacedDatumDoesNotAffectLhs_730) {
  auto rhs = MakeDatumWithStringValue("Exif.Image.Make", "Canon");
  auto lhs = MakeDatumWithStringValue("Exif.Image.Model", "EOS");

  lhs = rhs;

  // Replace RHS with a different Exifdatum (different key + value).
  rhs = MakeDatumWithStringValue("Exif.Image.Model", "D850");

  EXPECT_EQ(lhs.key(), "Exif.Image.Make");
  EXPECT_EQ(lhs.toString(), "Canon");
  EXPECT_EQ(rhs.key(), "Exif.Image.Model");
  EXPECT_EQ(rhs.toString(), "D850");
}

TEST_F(ExifdatumAssignmentTest_730, AssignFromNullValueDoesNotCrashAndValueIsAbsentOrEmpty_730) {
  auto rhsNull = MakeDatumWithNullValuePtr("Exif.Image.Make");
  auto lhs = MakeDatumWithStringValue("Exif.Image.Make", "Canon");

  ASSERT_NO_THROW(lhs = rhsNull);

  // Key should still be copyable/accessible.
  EXPECT_EQ(lhs.key(), rhsNull.key());

  // Value may be absent; validate via getValue() where possible.
  auto v = lhs.getValue();
  if (v) {
    // If an empty/default value object exists, it should be safely stringify-able.
    EXPECT_NO_THROW((void)v->toString());
  } else {
    SUCCEED();  // Acceptable: value truly absent.
  }

  EXPECT_NO_THROW((void)lhs.toString());
}

TEST_F(ExifdatumAssignmentTest_730, AssignToNullValuePtrCopiesValueFromRhs_730) {
  auto rhs = MakeDatumWithStringValue("Exif.Image.Make", "Canon");
  auto lhsNull = MakeDatumWithNullValuePtr("Exif.Image.Make");

  ASSERT_NO_THROW(lhsNull = rhs);

  EXPECT_EQ(lhsNull.key(), rhs.key());
  EXPECT_EQ(lhsNull.toString(), rhs.toString());

  auto v = lhsNull.getValue();
  ASSERT_NE(v.get(), nullptr);
  EXPECT_EQ(v->toString(), "Canon");
}

TEST_F(ExifdatumAssignmentTest_730, CopiesNumericAssignmentThroughRhs_730) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto v = Exiv2::Value::create(key.defaultTypeId());
  Exiv2::Exifdatum rhs(key, v.get());
  Exiv2::Exifdatum lhs(key, v.get());

  rhs = static_cast<uint32_t>(123u);
  lhs = static_cast<uint32_t>(0u);

  lhs = rhs;

  EXPECT_EQ(lhs.key(), rhs.key());
  EXPECT_EQ(lhs.toInt64(0), rhs.toInt64(0));
  EXPECT_EQ(lhs.toInt64(0), 123);
}

}  // namespace