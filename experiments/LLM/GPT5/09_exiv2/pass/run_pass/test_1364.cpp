// File: test_isExifIfd_1364.cpp
#include <gtest/gtest.h>

#include <vector>

#include "exiv2/tags.hpp"

namespace Exiv2::Internal {
// Black-box declaration (implemented in the production codebase).
bool isExifIfd(Exiv2::IfdId ifdId);
}  // namespace Exiv2::Internal

namespace {

using Exiv2::IfdId;

TEST(IsExifIfdTest_1364, ReturnsTrueForAllDocumentedExifIfds_1364) {
  const std::vector<IfdId> exifIfds = {
      IfdId::ifd0Id,       IfdId::exifId,       IfdId::gpsId,
      IfdId::iopId,        IfdId::ifd1Id,       IfdId::ifd2Id,
      IfdId::ifd3Id,       IfdId::mpfId,        IfdId::subImage1Id,
      IfdId::subImage2Id,  IfdId::subImage3Id,  IfdId::subImage4Id,
      IfdId::subImage5Id,  IfdId::subImage6Id,  IfdId::subImage7Id,
      IfdId::subImage8Id,  IfdId::subImage9Id,  IfdId::subThumb1Id,
      IfdId::panaRawId,
  };

  for (const auto id : exifIfds) {
    EXPECT_TRUE(Exiv2::Internal::isExifIfd(id)) << "Expected true for IfdId=" << static_cast<int>(id);
  }
}

TEST(IsExifIfdTest_1364, ReturnsFalseForNotSetAndSentinels_1364) {
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::ifdIdNotSet));
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::lastId));
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::ignoreId));
}

TEST(IsExifIfdTest_1364, ReturnsFalseForMakerNoteAndNonExifIfds_1364) {
  // A few representative non-EXIF IFDs / maker-note IFDs from the enum.
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::mnId));
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::canonId));
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::nikon3Id));
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::olympusId));
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(IfdId::sony2Id));
}

TEST(IsExifIfdTest_1364, ReturnsFalseForOutOfRangeEnumValues_1364) {
  // Boundary / robustness checks: invalid underlying values should not be treated as EXIF IFDs.
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(static_cast<IfdId>(-1)));
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(static_cast<IfdId>(0)));      // same underlying as ifdIdNotSet
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(static_cast<IfdId>(141)));    // beyond lastId/ignoreId underlying
  EXPECT_FALSE(Exiv2::Internal::isExifIfd(static_cast<IfdId>(9999)));
}

}  // namespace