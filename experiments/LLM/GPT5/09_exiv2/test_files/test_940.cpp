// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 940
//
// Unit tests for Exiv2::Internal::CanonMakerNote (partial interface)
// File under test: ./TestProjects/exiv2/src/canonmn_int.hpp

#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>

// Exiv2 public API types used by the declared printer functions
#include <exiv2/exiv2.hpp>

// Internal header under test
#include "canonmn_int.hpp"

namespace {

class CanonMakerNoteTest_940 : public ::testing::Test {};

template <typename T>
static void ExpectStablePointerLikeResult_940(const T& a, const T& b) {
  // For pointer-like results, we can check stable identity and non-null.
  if constexpr (std::is_pointer_v<T>) {
    EXPECT_EQ(a, b);
    EXPECT_NE(a, nullptr);
  } else {
    // For non-pointer results, we can still check it is copyable/movable and stable via == if available.
    // We avoid assuming operators exist; just ensure both calls compile and types match.
    (void)a;
    (void)b;
    SUCCEED();
  }
}

static Exiv2::ExifData MakeMinimalExif_940() {
  Exiv2::ExifData exif;
  // Keep it empty/minimal. Some printers consult metadata; tests cover both null and non-null.
  return exif;
}

// Creates a Value instance with minimal content; avoids relying on Canon-specific expectations.
static Exiv2::UShortValue MakeUShortValue_940(uint16_t v) {
  Exiv2::UShortValue value;
  // Using read() avoids assumptions about internal storage layout.
  value.read(std::to_string(v));
  return value;
}

static Exiv2::ULongValue MakeULongValue_940(uint32_t v) {
  Exiv2::ULongValue value;
  value.read(std::to_string(v));
  return value;
}

}  // namespace

// -------- tagListRawB() --------

TEST_F(CanonMakerNoteTest_940, TagListRawB_IsCallableAndTypeIsNotVoid_940) {
  using Ret = decltype(Exiv2::Internal::CanonMakerNote::tagListRawB());
  static_assert(!std::is_void_v<Ret>, "tagListRawB() must not return void");

  // Also ensure it is callable at runtime (even if constexpr).
  (void)Exiv2::Internal::CanonMakerNote::tagListRawB();
  SUCCEED();
}

TEST_F(CanonMakerNoteTest_940, TagListRawB_IsStableAcrossCalls_940) {
  const auto a = Exiv2::Internal::CanonMakerNote::tagListRawB();
  const auto b = Exiv2::Internal::CanonMakerNote::tagListRawB();
  ExpectStablePointerLikeResult_940(a, b);
}

// -------- print* functions (declared in header; implemented elsewhere in codebase) --------
// Black-box expectations:
// - Must return the same std::ostream& passed in (common Exiv2 pattern).
// - Should be safe with nullptr metadata when signature allows (const ExifData*).
// - Should not put the stream into a bad/fail state for basic inputs.

TEST_F(CanonMakerNoteTest_940, PrintFiFileNumber_ReturnsSameStream_WithNullMetadata_940) {
  std::ostringstream os;
  const auto value = MakeULongValue_940(1);

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::printFiFileNumber(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, PrintFiFileNumber_ReturnsSameStream_WithMetadata_940) {
  std::ostringstream os;
  const auto value = MakeULongValue_940(123456);
  Exiv2::ExifData exif = MakeMinimalExif_940();

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::printFiFileNumber(os, value, &exif);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, PrintFocalLength_ReturnsSameStream_NullMetadata_BoundaryValue_940) {
  std::ostringstream os;
  // Boundary-ish: zero focal length.
  const auto value = MakeUShortValue_940(0);

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::printFocalLength(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, Print0x0008_DoesNotThrow_EmptyValueAndNullMetadata_940) {
  std::ostringstream os;
  Exiv2::UShortValue value;  // empty / count==0 (as constructed)

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::print0x0008(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, Print0x000a_DoesNotThrow_WithMinimalValue_940) {
  std::ostringstream os;
  const auto value = MakeUShortValue_940(1);

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::print0x000a(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, Print0x000c_DoesNotThrow_WithMetadata_940) {
  std::ostringstream os;
  const auto value = MakeUShortValue_940(1);
  Exiv2::ExifData exif = MakeMinimalExif_940();

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::print0x000c(os, value, &exif);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, PrintCs0x0002_DoesNotThrow_NullMetadata_940) {
  std::ostringstream os;
  const auto value = MakeUShortValue_940(0);

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::printCs0x0002(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, PrintCsLensType_DoesNotThrow_WithAndWithoutMetadata_940) {
  const auto value = MakeUShortValue_940(1);

  {
    std::ostringstream os;
    EXPECT_NO_THROW({
      std::ostream& ret = Exiv2::Internal::CanonMakerNote::printCsLensType(os, value, nullptr);
      EXPECT_EQ(&ret, &os);
    });
    EXPECT_TRUE(os.good());
  }

  {
    std::ostringstream os;
    Exiv2::ExifData exif = MakeMinimalExif_940();
    EXPECT_NO_THROW({
      std::ostream& ret = Exiv2::Internal::CanonMakerNote::printCsLensType(os, value, &exif);
      EXPECT_EQ(&ret, &os);
    });
    EXPECT_TRUE(os.good());
  }
}

TEST_F(CanonMakerNoteTest_940, PrintCsLens_DoesNotThrow_EmptyValue_940) {
  std::ostringstream os;
  Exiv2::UShortValue value;  // empty

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::printCsLens(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, PrintLe0x0000_DoesNotThrow_MinimalValue_940) {
  std::ostringstream os;
  const auto value = MakeUShortValue_940(0);

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::printLe0x0000(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}

// A small matrix over a few "Si" printers to cover normal + boundary behavior without assuming formatting.
TEST_F(CanonMakerNoteTest_940, PrintSiPrinters_DoNotThrow_WithNullMetadata_940) {
  const auto v0 = MakeUShortValue_940(0);
  const auto v1 = MakeUShortValue_940(1);
  std::ostringstream os;

  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0001(os, v0, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0002(os, v1, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0003(os, v1, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0009(os, v0, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x000c(os, v1, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x000d(os, v1, nullptr), &os); });

  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x000e_DoesNotThrow_WithMetadataAndNullMetadata_940) {
  const auto value = MakeUShortValue_940(1);

  {
    std::ostringstream os;
    EXPECT_NO_THROW({
      std::ostream& ret = Exiv2::Internal::CanonMakerNote::printSi0x000e(os, value, nullptr);
      EXPECT_EQ(&ret, &os);
    });
    EXPECT_TRUE(os.good());
  }

  {
    std::ostringstream os;
    Exiv2::ExifData exif = MakeMinimalExif_940();
    EXPECT_NO_THROW({
      std::ostream& ret = Exiv2::Internal::CanonMakerNote::printSi0x000e(os, value, &exif);
      EXPECT_EQ(&ret, &os);
    });
    EXPECT_TRUE(os.good());
  }
}

TEST_F(CanonMakerNoteTest_940, PrintSiMorePrinters_DoNotThrow_WithEmptyValue_940) {
  Exiv2::UShortValue empty;
  std::ostringstream os;

  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0013(os, empty, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0015(os, empty, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0016(os, empty, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0017(os, empty, nullptr), &os); });
  EXPECT_NO_THROW({ EXPECT_EQ(&Exiv2::Internal::CanonMakerNote::printSi0x0018(os, empty, nullptr), &os); });

  EXPECT_TRUE(os.good());
}

TEST_F(CanonMakerNoteTest_940, PrintFiFocusDistance_ReturnsSameStream_NullMetadata_940) {
  std::ostringstream os;
  const auto value = MakeUShortValue_940(0);

  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_TRUE(os.good());
}