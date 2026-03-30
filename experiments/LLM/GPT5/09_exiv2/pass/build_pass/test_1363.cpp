// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <type_traits>
#include <vector>

#include <exiv2/tags.hpp>

// isMakerIfd is an internal helper; prefer including the internal header if available.
#if defined(__has_include)
#  if __has_include("tags_int.hpp")
#    include "tags_int.hpp"
#  elif __has_include(<exiv2/tags_int.hpp>)
#    include <exiv2/tags_int.hpp>
#  else
namespace Exiv2::Internal {
bool isMakerIfd(Exiv2::IfdId ifdId);
}
#  endif
#else
namespace Exiv2::Internal {
bool isMakerIfd(Exiv2::IfdId ifdId);
}
#endif

namespace {

class IsMakerIfdTest_1363 : public ::testing::Test {};

TEST_F(IsMakerIfdTest_1363, ReturnsTrueForKnownMakerIfds_1363) {
  // Pick a representative set of IFD ids that are known to be "Makernote" groups.
  const std::vector<Exiv2::IfdId> makerIfds = {
      Exiv2::IfdId::mnId,
      Exiv2::IfdId::canonId,
      Exiv2::IfdId::nikon1Id,
      Exiv2::IfdId::pentaxId,
      Exiv2::IfdId::sony1Id,
      Exiv2::IfdId::sigmaId,
  };

  for (const auto ifd : makerIfds) {
    EXPECT_TRUE(Exiv2::Internal::isMakerIfd(ifd)) << "Expected true for maker IFD";
  }
}

TEST_F(IsMakerIfdTest_1363, ReturnsFalseForNonMakerIfds_1363) {
  // Representative non-makernote IFD ids (their IFD name is not "Makernote").
  const std::vector<Exiv2::IfdId> nonMakerIfds = {
      Exiv2::IfdId::ifdIdNotSet,
      Exiv2::IfdId::ifd0Id,
      Exiv2::IfdId::ifd1Id,
      Exiv2::IfdId::exifId,
      Exiv2::IfdId::gpsId,
      Exiv2::IfdId::iopId,
      Exiv2::IfdId::mpfId,
      Exiv2::IfdId::subImage1Id,
      Exiv2::IfdId::subThumb1Id,
      Exiv2::IfdId::lastId,
  };

  for (const auto ifd : nonMakerIfds) {
    EXPECT_FALSE(Exiv2::Internal::isMakerIfd(ifd)) << "Expected false for non-maker IFD";
  }
}

TEST_F(IsMakerIfdTest_1363, ReturnsFalseForUnknownIfdIdValues_1363) {
  using UT = std::underlying_type_t<Exiv2::IfdId>;

  // Values outside the known set should not match any known group info entry.
  const std::vector<Exiv2::IfdId> unknownIfds = {
      static_cast<Exiv2::IfdId>(static_cast<UT>(-1)),
      static_cast<Exiv2::IfdId>(static_cast<UT>(0)),
      static_cast<Exiv2::IfdId>(static_cast<UT>(0x7fffffff)),
  };

  for (const auto ifd : unknownIfds) {
    EXPECT_FALSE(Exiv2::Internal::isMakerIfd(ifd)) << "Expected false for unknown IfdId value";
  }
}

TEST_F(IsMakerIfdTest_1363, IdempotentForSameInput_1363) {
  // Observable behavior should be stable for repeated calls with the same input.
  const auto input = Exiv2::IfdId::canonId;

  const bool first = Exiv2::Internal::isMakerIfd(input);
  const bool second = Exiv2::Internal::isMakerIfd(input);

  EXPECT_EQ(first, second);
  EXPECT_TRUE(first);  // canonId is a known maker IFD id
}

}  // namespace