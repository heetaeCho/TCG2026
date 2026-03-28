// ============================================================================
// TEST_ID: 1164
// File: test_tiffmapping_findencoder_1164.cpp
// Unit tests for Exiv2::Internal::TiffMapping::findEncoder
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <type_traits>

#include "tiffimage_int.hpp"  // Exiv2::Internal::TiffMapping, EncoderFct, IfdId

namespace {

using Exiv2::Internal::EncoderFct;
using Exiv2::Internal::IfdId;
using Exiv2::Internal::TiffMapping;

class TiffMappingTest_1164 : public ::testing::Test {
 protected:
  TiffMapping mapping_;
};

static IfdId MakeIfdId0() {
  return static_cast<IfdId>(0);
}

static IfdId MakeIfdIdMax() {
  if constexpr (std::is_enum_v<IfdId>) {
    using U = std::underlying_type_t<IfdId>;
    return static_cast<IfdId>(std::numeric_limits<U>::max());
  } else {
    // IfdId is not an enum on some builds; fall back to a large integral cast.
    return static_cast<IfdId>(std::numeric_limits<int>::max());
  }
}

TEST_F(TiffMappingTest_1164, UnknownMakeReturnsNull_1164) {
  const std::string_view make = "DefinitelyNotARealCameraMake_Exiv2_1164";
  const uint32_t extendedTag = 0x12345678u;
  const IfdId group = MakeIfdId0();

  EncoderFct f = mapping_.findEncoder(make, extendedTag, group);
  EXPECT_EQ(f, nullptr);
}

TEST_F(TiffMappingTest_1164, EmptyMakeReturnsNull_1164) {
  const std::string_view make = "";
  const uint32_t extendedTag = 0u;
  const IfdId group = MakeIfdId0();

  EncoderFct f = mapping_.findEncoder(make, extendedTag, group);
  EXPECT_EQ(f, nullptr);
}

TEST_F(TiffMappingTest_1164, UnknownMakeWithMaxValuesReturnsNull_1164) {
  const std::string_view make = "UnknownMake_1164";
  const uint32_t extendedTag = std::numeric_limits<uint32_t>::max();
  const IfdId group = MakeIfdIdMax();

  EncoderFct f = mapping_.findEncoder(make, extendedTag, group);
  EXPECT_EQ(f, nullptr);
}

TEST_F(TiffMappingTest_1164, SameInputsAreStableAcrossCalls_1164) {
  const std::string_view make = "DefinitelyNotARealCameraMake_Exiv2_1164";
  const uint32_t extendedTag = 0x89ABCDEFu;
  const IfdId group = MakeIfdId0();

  EncoderFct f1 = mapping_.findEncoder(make, extendedTag, group);
  EncoderFct f2 = mapping_.findEncoder(make, extendedTag, group);

  // Observable behavior: repeated calls with identical inputs should yield the same observable result.
  EXPECT_EQ(f1, f2);
  EXPECT_EQ(f1, nullptr);
}

TEST_F(TiffMappingTest_1164, AcceptsTemporaryStringViewInput_1164) {
  // Boundary: make provided via std::string temporary storage; function consumes std::string_view.
  const uint32_t extendedTag = 0x01020304u;
  const IfdId group = MakeIfdId0();

  EncoderFct f = nullptr;
  {
    std::string tmp = "DefinitelyNotARealCameraMake_Exiv2_1164_tmp";
    f = mapping_.findEncoder(std::string_view(tmp), extendedTag, group);
  }

  // Only observable postcondition we can assert portably without knowing mapping table contents.
  EXPECT_EQ(f, nullptr);
}

TEST_F(TiffMappingTest_1164, DifferentGroupsCanBeQueriedWithoutCrashing_1164) {
  const std::string_view make = "DefinitelyNotARealCameraMake_Exiv2_1164";
  const uint32_t extendedTag = 0x0u;

  const IfdId g0 = MakeIfdId0();
  const IfdId gMax = MakeIfdIdMax();

  EncoderFct f0 = mapping_.findEncoder(make, extendedTag, g0);
  EncoderFct fMax = mapping_.findEncoder(make, extendedTag, gMax);

  // For unknown make we expect no encoder regardless of group.
  EXPECT_EQ(f0, nullptr);
  EXPECT_EQ(fMax, nullptr);
}

}  // namespace