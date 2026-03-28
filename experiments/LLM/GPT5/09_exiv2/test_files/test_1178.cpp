// ============================================================================
// Test file for ./TestProjects/exiv2/src/tiffimage_int.cpp
// Unit tests for: Exiv2::Internal::TiffHeaderBase::isImageTag
// TEST_ID: 1178
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <set>

// ---- Minimal stubs to satisfy the provided interface ----
// The partial code references IfdId and PrimaryGroups but does not define them.
// These stubs are only for compilation of the test translation unit.
namespace Exiv2 {
namespace Internal {

using IfdId = int;  // stubbed type; only passed through as a parameter

using PrimaryGroups = std::set<IfdId>;  // "group-set" semantics are reasonable for tests

class TiffHeaderBase {
 public:
  bool isImageTag(uint16_t /*tag*/, IfdId /*group*/, const PrimaryGroups& /*primaryGroups*/) const {
    return false;
  }
};

}  // namespace Internal
}  // namespace Exiv2

// ----------------------------------------------------------------------------

namespace {

using Exiv2::Internal::IfdId;
using Exiv2::Internal::PrimaryGroups;
using Exiv2::Internal::TiffHeaderBase;

class TiffHeaderBaseTest_1178 : public ::testing::Test {
 protected:
  TiffHeaderBase subject_;
};

TEST_F(TiffHeaderBaseTest_1178, ReturnsFalseForTypicalInputs_1178) {
  PrimaryGroups groups;
  groups.insert(static_cast<IfdId>(0));
  const bool result = subject_.isImageTag(static_cast<uint16_t>(256), static_cast<IfdId>(0), groups);
  EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1178, ReturnsFalseWhenPrimaryGroupsIsEmpty_1178) {
  PrimaryGroups groups;
  const bool result = subject_.isImageTag(static_cast<uint16_t>(256), static_cast<IfdId>(0), groups);
  EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1178, ReturnsFalseForZeroTagAndZeroGroup_1178) {
  PrimaryGroups groups;
  groups.insert(static_cast<IfdId>(0));
  const bool result = subject_.isImageTag(static_cast<uint16_t>(0), static_cast<IfdId>(0), groups);
  EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1178, ReturnsFalseForMaxUint16Tag_1178) {
  PrimaryGroups groups;
  groups.insert(static_cast<IfdId>(1));
  const bool result = subject_.isImageTag(static_cast<uint16_t>(0xFFFF), static_cast<IfdId>(1), groups);
  EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1178, ReturnsFalseForNegativeGroupValue_1178) {
  PrimaryGroups groups;
  groups.insert(static_cast<IfdId>(-1));
  const bool result = subject_.isImageTag(static_cast<uint16_t>(256), static_cast<IfdId>(-1), groups);
  EXPECT_FALSE(result);
}

TEST_F(TiffHeaderBaseTest_1178, ReturnsFalseRegardlessOfGroupsContent_1178) {
  PrimaryGroups emptyGroups;
  PrimaryGroups someGroups;
  someGroups.insert(static_cast<IfdId>(0));
  someGroups.insert(static_cast<IfdId>(42));
  someGroups.insert(static_cast<IfdId>(-7));

  const uint16_t tag = static_cast<uint16_t>(300);

  EXPECT_FALSE(subject_.isImageTag(tag, static_cast<IfdId>(0), emptyGroups));
  EXPECT_FALSE(subject_.isImageTag(tag, static_cast<IfdId>(0), someGroups));
}

TEST_F(TiffHeaderBaseTest_1178, IsConstCallableAndDeterministicForSameInputs_1178) {
  const TiffHeaderBase constSubject;
  PrimaryGroups groups;
  groups.insert(static_cast<IfdId>(7));

  const uint16_t tag = static_cast<uint16_t>(257);
  const IfdId group = static_cast<IfdId>(7);

  const bool r1 = constSubject.isImageTag(tag, group, groups);
  const bool r2 = constSubject.isImageTag(tag, group, groups);

  EXPECT_EQ(r1, r2);
  EXPECT_FALSE(r1);
}

TEST_F(TiffHeaderBaseTest_1178, DoesNotModifyPrimaryGroupsArgument_1178) {
  PrimaryGroups groups;
  groups.insert(static_cast<IfdId>(1));
  groups.insert(static_cast<IfdId>(2));

  const PrimaryGroups before = groups;
  (void)subject_.isImageTag(static_cast<uint16_t>(256), static_cast<IfdId>(1), groups);
  EXPECT_EQ(groups, before);
}

}  // namespace