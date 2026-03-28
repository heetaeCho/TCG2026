// StructElement_ownerToName_1780_test.cc
#include <gtest/gtest.h>

#include <cstring>
#include <string>

// NOTE:
// ownerToName(...) is a static function in StructElement.cc (internal linkage).
// To test it as a black box through its signature/return value, we include the
// implementation file into this test translation unit.
#include "StructElement.cc"

namespace {

class StructElementOwnerToNameTest_1780 : public ::testing::Test {
protected:
  static std::string CallOwnerToName(Attribute::Owner owner)
  {
    const char *s = ownerToName(owner);
    return s ? std::string(s) : std::string();
  }
};

TEST_F(StructElementOwnerToNameTest_1780, ReturnsNonNullAndNonEmptyForVariousInputs_1780)
{
  // Boundary-ish values (including out-of-range) should still return a valid C-string.
  const Attribute::Owner inputs[] = {
      static_cast<Attribute::Owner>(-1),
      static_cast<Attribute::Owner>(0),
      static_cast<Attribute::Owner>(1),
      static_cast<Attribute::Owner>(9999),
  };

  for (auto owner : inputs) {
    const char *s = ownerToName(owner);
    ASSERT_NE(s, nullptr);
    EXPECT_GT(std::strlen(s), 0u);
  }
}

TEST_F(StructElementOwnerToNameTest_1780, InvalidOwnerNegativeReturnsUnknownOwner_1780)
{
  const std::string name = CallOwnerToName(static_cast<Attribute::Owner>(-1));
  EXPECT_EQ(name, "UnknownOwner");
}

TEST_F(StructElementOwnerToNameTest_1780, InvalidOwnerLargeReturnsUnknownOwner_1780)
{
  const std::string name = CallOwnerToName(static_cast<Attribute::Owner>(9999));
  EXPECT_EQ(name, "UnknownOwner");
}

TEST_F(StructElementOwnerToNameTest_1780, FindsAtLeastOneMappedOwnerInReasonableScanRange_1780)
{
  // Normal-operation check without assuming any specific enum values:
  // scan a reasonable range and ensure at least one value maps to something
  // other than "UnknownOwner".
  bool foundMapped = false;

  for (int i = 0; i <= 200; ++i) {
    const std::string name = CallOwnerToName(static_cast<Attribute::Owner>(i));
    if (name != "UnknownOwner") {
      foundMapped = true;
      break;
    }
  }

  EXPECT_TRUE(foundMapped);
}

TEST_F(StructElementOwnerToNameTest_1780, MappedOwnerNameIsDeterministicAcrossCalls_1780)
{
  // Locate one mapped owner value first.
  int mappedValue = -1;
  std::string firstName;

  for (int i = 0; i <= 200; ++i) {
    const std::string name = CallOwnerToName(static_cast<Attribute::Owner>(i));
    if (name != "UnknownOwner") {
      mappedValue = i;
      firstName = name;
      break;
    }
  }

  ASSERT_NE(mappedValue, -1) << "No mapped owner found in scan range; cannot validate determinism.";
  ASSERT_FALSE(firstName.empty());

  // Verify repeated calls return the same observable string content.
  for (int k = 0; k < 10; ++k) {
    const std::string name2 = CallOwnerToName(static_cast<Attribute::Owner>(mappedValue));
    EXPECT_EQ(name2, firstName);
  }
}

} // namespace