#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class TiffMnRegistryTest_1430 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
};

// Test that operator==(IfdId) returns true when mnGroup_ matches the key
TEST_F(TiffMnRegistryTest_1430, OperatorEqualIfdId_MatchingGroup_ReturnsTrue_1430) {
  TiffMnRegistry registry{};
  registry.mnGroup_ = Exiv2::IfdId::ifd0Id;

  EXPECT_TRUE(registry == Exiv2::IfdId::ifd0Id);
}

// Test that operator==(IfdId) returns false when mnGroup_ does not match the key
TEST_F(TiffMnRegistryTest_1430, OperatorEqualIfdId_NonMatchingGroup_ReturnsFalse_1430) {
  TiffMnRegistry registry{};
  registry.mnGroup_ = Exiv2::IfdId::ifd0Id;

  EXPECT_FALSE(registry == Exiv2::IfdId::ifd1Id);
}

// Test that operator==(IfdId) returns true when both are the same enum value (boundary: same value)
TEST_F(TiffMnRegistryTest_1430, OperatorEqualIfdId_SameEnumValue_ReturnsTrue_1430) {
  TiffMnRegistry registry{};
  registry.mnGroup_ = Exiv2::IfdId::exifId;

  EXPECT_TRUE(registry == Exiv2::IfdId::exifId);
}

// Test with a different IfdId value to ensure distinctness
TEST_F(TiffMnRegistryTest_1430, OperatorEqualIfdId_DifferentIfdIds_ReturnsFalse_1430) {
  TiffMnRegistry registry{};
  registry.mnGroup_ = Exiv2::IfdId::exifId;

  EXPECT_FALSE(registry == Exiv2::IfdId::gpsId);
}

// Test operator==(string_view) returns true when make_ matches
TEST_F(TiffMnRegistryTest_1430, OperatorEqualStringView_MatchingMake_ReturnsTrue_1430) {
  TiffMnRegistry registry{};
  registry.make_ = "Canon";
  registry.mnGroup_ = Exiv2::IfdId::ifd0Id;

  EXPECT_TRUE(registry == std::string_view("Canon"));
}

// Test operator==(string_view) with non-matching make_
TEST_F(TiffMnRegistryTest_1430, OperatorEqualStringView_NonMatchingMake_ReturnsFalse_1430) {
  TiffMnRegistry registry{};
  registry.make_ = "Canon";
  registry.mnGroup_ = Exiv2::IfdId::ifd0Id;

  EXPECT_FALSE(registry == std::string_view("Nikon"));
}

// Test operator==(string_view) with empty string
TEST_F(TiffMnRegistryTest_1430, OperatorEqualStringView_EmptyString_1430) {
  TiffMnRegistry registry{};
  registry.make_ = "";
  registry.mnGroup_ = Exiv2::IfdId::ifd0Id;

  EXPECT_TRUE(registry == std::string_view(""));
}

// Test operator==(string_view) with partial match - the key is a prefix of make_
TEST_F(TiffMnRegistryTest_1430, OperatorEqualStringView_PartialMatch_1430) {
  TiffMnRegistry registry{};
  registry.make_ = "Canon EOS";
  registry.mnGroup_ = Exiv2::IfdId::ifd0Id;

  // Depending on the implementation, a partial string may or may not match.
  // We test observable behavior - "Canon" vs "Canon EOS"
  // The result depends on whether it does prefix matching or exact matching.
  // We just verify it doesn't crash and returns a bool.
  bool result = (registry == std::string_view("Canon"));
  // We can't assert true or false without knowing implementation,
  // but we can verify the call is valid
  (void)result;
}

// Test operator==(IfdId) with the default/zero IfdId value
TEST_F(TiffMnRegistryTest_1430, OperatorEqualIfdId_DefaultValue_1430) {
  TiffMnRegistry registry{};
  registry.mnGroup_ = static_cast<Exiv2::IfdId>(0);

  EXPECT_TRUE(registry == static_cast<Exiv2::IfdId>(0));
  EXPECT_FALSE(registry == Exiv2::IfdId::ifd0Id);
}

// Test consistency: calling operator== multiple times yields the same result
TEST_F(TiffMnRegistryTest_1430, OperatorEqualIfdId_ConsistentResults_1430) {
  TiffMnRegistry registry{};
  registry.mnGroup_ = Exiv2::IfdId::ifd0Id;

  bool result1 = (registry == Exiv2::IfdId::ifd0Id);
  bool result2 = (registry == Exiv2::IfdId::ifd0Id);
  EXPECT_EQ(result1, result2);
  EXPECT_TRUE(result1);
}
