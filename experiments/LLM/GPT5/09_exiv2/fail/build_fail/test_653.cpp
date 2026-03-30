// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 653
//
// Unit tests for Exiv2::Internal::equalsQTimeTag (quicktimevideo.cpp)

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

#include "exiv2/types.hpp"

// Include the .cpp to access the internal-linkage function in this translation unit.
#include "TestProjects/exiv2/src/quicktimevideo.cpp"

namespace {

class EqualsQTimeTagTest_653 : public ::testing::Test {
 protected:
  static Exiv2::DataBuf MakeBufFrom4(const std::array<Exiv2::byte, 4>& bytes4) {
    return Exiv2::DataBuf(bytes4.data(), bytes4.size());
  }

  static Exiv2::DataBuf MakeBufWithPrefixAndExtra(const std::array<Exiv2::byte, 4>& prefix,
                                                  const std::vector<Exiv2::byte>& extra) {
    std::vector<Exiv2::byte> all(prefix.begin(), prefix.end());
    all.insert(all.end(), extra.begin(), extra.end());
    return Exiv2::DataBuf(all.data(), all.size());
  }
};

TEST_F(EqualsQTimeTagTest_653, ExactMatchCaseSensitive_653) {
  const auto buf = MakeBufFrom4({{'f', 't', 'y', 'p'}});
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "ftyp"));
}

TEST_F(EqualsQTimeTagTest_653, MatchIsCaseInsensitive_BufferUpper_653) {
  const auto buf = MakeBufFrom4({{'F', 'T', 'Y', 'P'}});
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "ftyp"));
}

TEST_F(EqualsQTimeTagTest_653, MatchIsCaseInsensitive_Mixed_653) {
  const auto buf = MakeBufFrom4({{'F', 't', 'Y', 'p'}});
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "fTyP"));
}

TEST_F(EqualsQTimeTagTest_653, MismatchOneCharacter_ReturnsFalse_653) {
  const auto buf = MakeBufFrom4({{'f', 't', 'y', 'q'}});
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "ftyp"));
}

TEST_F(EqualsQTimeTagTest_653, OnlyFirstFourBytesAreCompared_BufferLargerThanFour_653) {
  const auto buf = MakeBufWithPrefixAndExtra({{'m', 'o', 'o', 'v'}},
                                             std::vector<Exiv2::byte>{'X', 'Y', 'Z'});
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "moov"));
}

TEST_F(EqualsQTimeTagTest_653, NonAlphabeticBytesComparedAsIs_653) {
  // '1','2','3','4' should match exactly; case-folding should not change digits.
  const auto buf = MakeBufFrom4({{'1', '2', '3', '4'}});
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "1234"));
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "1235"));
}

TEST_F(EqualsQTimeTagTest_653, Boundary_SizeExactlyFour_DoesNotRequireMore_653) {
  const auto buf = MakeBufFrom4({{'w', 'i', 'd', 'e'}});
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "wide"));
}

}  // namespace