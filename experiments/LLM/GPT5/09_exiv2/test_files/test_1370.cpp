// File: test_ifdname_1370.cpp
// Unit tests for Exiv2::Internal::ifdName(IfdId)
// TEST_ID: 1370

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// Prefer the real Exiv2 headers if available.
#if __has_include(<exiv2/tags.hpp>)
#include <exiv2/tags.hpp>
#else
// If your build uses a different include path, adjust as needed.
#include "exiv2/tags.hpp"
#endif

// ifdName is implemented in src/tags_int.cpp; it is typically declared in an internal header.
// Try common locations; fall back to a forward declaration.
#if __has_include("tags_int.hpp")
#include "tags_int.hpp"
#elif __has_include(<exiv2/tags_int.hpp>)
#include <exiv2/tags_int.hpp>
#else
namespace Exiv2 {
namespace Internal {
const char* ifdName(Exiv2::IfdId ifdId);
}  // namespace Internal
}  // namespace Exiv2
#endif

namespace {

class IfdNameTest_1370 : public ::testing::Test {};

TEST_F(IfdNameTest_1370, ReturnsExpectedName_ForCommonIfds_1370) {
  EXPECT_STREQ("IFD0", Exiv2::Internal::ifdName(Exiv2::IfdId::ifd0Id));
  EXPECT_STREQ("Exif", Exiv2::Internal::ifdName(Exiv2::IfdId::exifId));
  EXPECT_STREQ("GPSInfo", Exiv2::Internal::ifdName(Exiv2::IfdId::gpsId));
}

TEST_F(IfdNameTest_1370, ReturnsExpectedName_ForMakerNoteIfds_1370) {
  // Many maker note groups map to the same IFD name string "Makernote".
  EXPECT_STREQ("Makernote", Exiv2::Internal::ifdName(Exiv2::IfdId::mnId));
  EXPECT_STREQ("Makernote", Exiv2::Internal::ifdName(Exiv2::IfdId::canonId));
  EXPECT_STREQ("Makernote", Exiv2::Internal::ifdName(Exiv2::IfdId::sony1Id));
}

TEST_F(IfdNameTest_1370, ReturnsUnknownIfd_ForIfdIdNotSet_1370) {
  EXPECT_STREQ("Unknown IFD", Exiv2::Internal::ifdName(Exiv2::IfdId::ifdIdNotSet));
}

TEST_F(IfdNameTest_1370, ReturnsUnknownIfd_ForUnrecognizedIfdId_1370) {
  // Black-box check: for an unrecognized IfdId, the function should fall back to the default name.
  using UnderT = std::underlying_type<Exiv2::IfdId>::type;

  const auto unknown1 = static_cast<Exiv2::IfdId>(static_cast<UnderT>(-1));
  const auto unknown2 = static_cast<Exiv2::IfdId>(static_cast<UnderT>(999999));

  EXPECT_STREQ("Unknown IFD", Exiv2::Internal::ifdName(unknown1));
  EXPECT_STREQ("Unknown IFD", Exiv2::Internal::ifdName(unknown2));
}

TEST_F(IfdNameTest_1370, ReturnsExpectedName_ForLastIdBoundary_1370) {
  // Boundary case using a known sentinel present in the provided groupInfo table.
  EXPECT_STREQ("(Last IFD info)", Exiv2::Internal::ifdName(Exiv2::IfdId::lastId));
}

TEST_F(IfdNameTest_1370, ReturnedPointerIsNonNull_ForKnownAndUnknown_1370) {
  const char* known = Exiv2::Internal::ifdName(Exiv2::IfdId::ifd1Id);
  ASSERT_NE(nullptr, known);

  using UnderT = std::underlying_type<Exiv2::IfdId>::type;
  const auto unknown = static_cast<Exiv2::IfdId>(static_cast<UnderT>(-12345));
  const char* fallback = Exiv2::Internal::ifdName(unknown);
  ASSERT_NE(nullptr, fallback);
}

}  // namespace