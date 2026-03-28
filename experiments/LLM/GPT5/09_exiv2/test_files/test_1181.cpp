// ============================================================================
// TestProjects/exiv2/tests/tiffheader_isimagetag_test_1181.cpp
// Unit tests for Exiv2::Internal::TiffHeader::isImageTag
// TEST_ID: 1181
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <initializer_list>

#include "tiffimage_int.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/types.hpp"

namespace {

// Helper to build PrimaryGroups without assuming its concrete container type.
template <typename PrimaryGroupsT>
PrimaryGroupsT MakePrimaryGroups(std::initializer_list<Exiv2::IfdId> ids) {
  PrimaryGroupsT pg;
  for (auto id : ids) pg.push_back(id);
  return pg;
}

}  // namespace

namespace Exiv2::Internal {

class TiffHeaderIsImageTagTest_1181 : public ::testing::Test {
 protected:
  static constexpr uint32_t kOffset = 0u;

  static constexpr uint16_t kTagMin = 0u;
  static constexpr uint16_t kTagMax = 0xFFFFu;
};

TEST_F(TiffHeaderIsImageTagTest_1181, HasNoImageTagsAlwaysReturnsFalse_1181) {
  const TiffHeader hdr(Exiv2::littleEndian, kOffset, /*hasImageTags=*/false);

  const PrimaryGroups emptyPg{};
  const PrimaryGroups ifd0OnlyPg = MakePrimaryGroups<PrimaryGroups>({IfdId::ifd0Id});
  const PrimaryGroups ifd1OnlyPg = MakePrimaryGroups<PrimaryGroups>({IfdId::ifd1Id});

  EXPECT_FALSE(hdr.isImageTag(kTagMin, IfdId::ifd0Id, emptyPg));
  EXPECT_FALSE(hdr.isImageTag(kTagMax, IfdId::ifd0Id, emptyPg));

  EXPECT_FALSE(hdr.isImageTag(kTagMin, IfdId::ifd0Id, ifd0OnlyPg));
  EXPECT_FALSE(hdr.isImageTag(kTagMax, IfdId::ifd1Id, ifd0OnlyPg));

  EXPECT_FALSE(hdr.isImageTag(kTagMin, IfdId::ifd1Id, ifd1OnlyPg));
  EXPECT_FALSE(hdr.isImageTag(kTagMax, IfdId::ifd2Id, ifd1OnlyPg));
}

TEST_F(TiffHeaderIsImageTagTest_1181, GroupNotInPrimaryGroupsReturnsFalse_1181) {
  const TiffHeader hdr(Exiv2::littleEndian, kOffset, /*hasImageTags=*/true);

  // Primary groups do not include ifd1Id.
  const PrimaryGroups primary = MakePrimaryGroups<PrimaryGroups>({IfdId::ifd0Id, IfdId::exifId});

  EXPECT_FALSE(hdr.isImageTag(kTagMin, IfdId::ifd1Id, primary));
  EXPECT_FALSE(hdr.isImageTag(kTagMax, IfdId::ifd1Id, primary));
}

TEST_F(TiffHeaderIsImageTagTest_1181, PrimaryGroupNonIfd0ReturnsTrueRegardlessOfTag_1181) {
  const TiffHeader hdr(Exiv2::littleEndian, kOffset, /*hasImageTags=*/true);

  // When primary groups are provided and include a non-ifd0 group, that group is treated as image tags.
  const PrimaryGroups primary = MakePrimaryGroups<PrimaryGroups>({IfdId::ifd1Id});

  EXPECT_TRUE(hdr.isImageTag(kTagMin, IfdId::ifd1Id, primary));
  EXPECT_TRUE(hdr.isImageTag(kTagMax, IfdId::ifd1Id, primary));
}

TEST_F(TiffHeaderIsImageTagTest_1181, Ifd0WithPrimaryGroupsBehavesLikeEmptyPrimaryGroups_1181) {
  const TiffHeader hdr(Exiv2::littleEndian, kOffset, /*hasImageTags=*/true);

  const PrimaryGroups emptyPg{};
  const PrimaryGroups ifd0OnlyPg = MakePrimaryGroups<PrimaryGroups>({IfdId::ifd0Id});

  // For group==ifd0Id, having ifd0Id present in primary groups should not force true/false;
  // both cases fall through to the same decision path. We assert equality without assuming the value.
  EXPECT_EQ(hdr.isImageTag(kTagMin, IfdId::ifd0Id, emptyPg),
            hdr.isImageTag(kTagMin, IfdId::ifd0Id, ifd0OnlyPg));

  EXPECT_EQ(hdr.isImageTag(kTagMax, IfdId::ifd0Id, emptyPg),
            hdr.isImageTag(kTagMax, IfdId::ifd0Id, ifd0OnlyPg));
}

TEST_F(TiffHeaderIsImageTagTest_1181, RepeatedCallsWithSameInputsReturnSameResult_1181) {
  const TiffHeader hdr(Exiv2::littleEndian, kOffset, /*hasImageTags=*/true);

  const PrimaryGroups emptyPg{};

  const bool r1 = hdr.isImageTag(123u, IfdId::ifd0Id, emptyPg);
  const bool r2 = hdr.isImageTag(123u, IfdId::ifd0Id, emptyPg);
  EXPECT_EQ(r1, r2);

  const bool r3 = hdr.isImageTag(kTagMax, IfdId::exifId, emptyPg);
  const bool r4 = hdr.isImageTag(kTagMax, IfdId::exifId, emptyPg);
  EXPECT_EQ(r3, r4);
}

}  // namespace Exiv2::Internal