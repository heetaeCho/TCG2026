// File: test_tiff_mn_registry_operator_eq_string_view_1429.cpp

#include <gtest/gtest.h>

#include <string_view>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::TiffMnRegistry;

TEST(TiffMnRegistryTest_1429, ReturnsTrueWhenKeyStartsWithMake_1429) {
  TiffMnRegistry reg{};
  reg.make_ = "Canon";

  EXPECT_TRUE(reg == std::string_view{"Canon"});
  EXPECT_TRUE(reg == std::string_view{"CanonEOS"});
  EXPECT_TRUE(reg == std::string_view{"Canon\0X", 6});  // still starts with "Canon"
}

TEST(TiffMnRegistryTest_1429, ReturnsFalseWhenKeyDoesNotStartWithMake_1429) {
  TiffMnRegistry reg{};
  reg.make_ = "Nikon";

  EXPECT_FALSE(reg == std::string_view{"Canon"});
  EXPECT_FALSE(reg == std::string_view{"Ni"});         // shorter than "Nikon"
  EXPECT_FALSE(reg == std::string_view{""});           // empty key
  EXPECT_FALSE(reg == std::string_view{"X-Nikon"});    // does not start with "Nikon"
}

TEST(TiffMnRegistryTest_1429, ReturnsFalseWhenKeyBeginsWithDashEvenIfMakeMatchesAfterDash_1429) {
  TiffMnRegistry reg{};
  reg.make_ = "Canon";

  EXPECT_FALSE(reg == std::string_view{"-Canon"});
  EXPECT_FALSE(reg == std::string_view{"-CanonEOS"});
}

TEST(TiffMnRegistryTest_1429, EmptyMakeMatchesNonDashKeysAndRejectsDashKeys_1429) {
  TiffMnRegistry reg{};
  reg.make_ = "";

  // For empty make_, starts-with should be true for any key that is not rejected by the dash rule.
  EXPECT_TRUE(reg == std::string_view{""});
  EXPECT_TRUE(reg == std::string_view{"Canon"});
  EXPECT_TRUE(reg == std::string_view{"-"} == false);  // clarify behavior for dash-only key

  // Keys beginning with '-' are rejected regardless of make_.
  EXPECT_FALSE(reg == std::string_view{"-Canon"});
  EXPECT_FALSE(reg == std::string_view{"-"});
}

TEST(TiffMnRegistryTest_1429, BoundaryCasesSingleCharacterKeys_1429) {
  TiffMnRegistry reg{};
  reg.make_ = "A";

  EXPECT_TRUE(reg == std::string_view{"A"});
  EXPECT_TRUE(reg == std::string_view{"AB"});
  EXPECT_FALSE(reg == std::string_view{"B"});
  EXPECT_FALSE(reg == std::string_view{"-A"});
}

}  // namespace