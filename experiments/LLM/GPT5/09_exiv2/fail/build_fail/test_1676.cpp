// TEST_ID 1676
// File: test_tiffvisitor_int_visitBinaryArray_1676.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <functional>

#if __has_include("tiffvisitor_int.hpp")
#include "tiffvisitor_int.hpp"
#else
#include "exiv2/tiffvisitor_int.hpp"
#endif

#if __has_include("tiffcomposite_int.hpp")
#include "tiffcomposite_int.hpp"
#else
#include "exiv2/tiffcomposite_int.hpp"
#endif

// Some Exiv2 internal types (e.g., TiffHeader/TiffHeaderBase) live in other headers.
// We include them opportunistically to construct a real TiffEncoder instance.
#if __has_include("tiffimage_int.hpp")
#include "tiffimage_int.hpp"
#elif __has_include("tiffheader_int.hpp")
#include "tiffheader_int.hpp"
#endif

namespace {

// Helper: build a minimal, real TiffHeaderBase instance.
// Exiv2 typically has a concrete TiffHeader class that provides byteOrder().
static const Exiv2::Internal::TiffHeaderBase& MakeHeaderOrDie() {
  // Many Exiv2 builds provide Exiv2::Internal::TiffHeader (concrete).
  // If yours names it differently, adjust this helper accordingly.
  static Exiv2::Internal::TiffHeader header(
      Exiv2::littleEndian,
      /*offset*/ 0u);
  return header;
}

static Exiv2::Internal::TiffEncoder MakeEncoderOrDie(Exiv2::Internal::TiffComponent* root) {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  // PrimaryGroups is typically a container-like type; value-init is fine.
  Exiv2::Internal::PrimaryGroups primaryGroups{};

  // FindEncoderFct is a function type; empty callable is acceptable.
  Exiv2::Internal::FindEncoderFct findFct{};

  const Exiv2::Internal::TiffHeaderBase& header = MakeHeaderOrDie();

  return Exiv2::Internal::TiffEncoder(std::move(exif), iptc, xmp, root,
                                      /*isNewImage*/ false, std::move(primaryGroups),
                                      &header, findFct);
}

// Helper: create an ArrayCfg-backed TiffBinaryArray (cfg() is expected to be non-null).
// We only rely on public constructors; we do not assume any internal encoding logic.
static Exiv2::Internal::TiffBinaryArray MakeCfgBackedBinaryArrayOrDie() {
  // ArrayCfg is expected to be a concrete type in Exiv2 internals.
  // Value-initialization keeps this as "minimal" as possible.
  Exiv2::Internal::ArrayCfg cfg{};
  // Some builds require elTiffType_ to be set; if it exists, keep it default.
  // (No inference about meaning; just ensuring it compiles on common Exiv2 layouts.)

  return Exiv2::Internal::TiffBinaryArray(
      /*tag*/ 0,
      static_cast<Exiv2::Internal::IfdId>(0),
      cfg,
      /*arrayDef*/ nullptr,
      /*defSize*/ 0);
}

// Helper: create a set-backed TiffBinaryArray that commonly yields cfg()==nullptr
// until initialized/selected. We do not depend on that; we just exercise the path.
static Exiv2::Internal::TiffBinaryArray MakeSetBackedBinaryArray() {
  return Exiv2::Internal::TiffBinaryArray(
      /*tag*/ 0,
      static_cast<Exiv2::Internal::IfdId>(0),
      /*arraySet*/ nullptr,
      /*setSize*/ 0,
      /*cfgSelFct*/ {});
}

}  // namespace

// ---------- Tests (black-box) ----------

TEST(TiffEncoderVisitBinaryArrayTest_1676, DoesNotThrowWithNullCfg_DefaultDecodedFalse_1676) {
  // Arrange
  auto encoder = MakeEncoderOrDie(/*root*/ nullptr);
  auto arr = MakeSetBackedBinaryArray();  // typically cfg()==nullptr
  // decoded defaults to false in the class; we don't rely on internals beyond interface.
  EXPECT_FALSE(arr.decoded());

  // Act / Assert
  EXPECT_NO_THROW(encoder.visitBinaryArray(&arr));
}

TEST(TiffEncoderVisitBinaryArrayTest_1676, DoesNotThrowWithNullCfg_DecodedTrue_1676) {
  // Arrange
  auto encoder = MakeEncoderOrDie(/*root*/ nullptr);
  auto arr = MakeSetBackedBinaryArray();
  arr.setDecoded(true);
  EXPECT_TRUE(arr.decoded());

  // Act / Assert
  EXPECT_NO_THROW(encoder.visitBinaryArray(&arr));
}

TEST(TiffEncoderVisitBinaryArrayTest_1676, DoesNotThrowWithNonNullCfg_DecodedFalse_1676) {
  // Arrange
  auto encoder = MakeEncoderOrDie(/*root*/ nullptr);
  auto arr = MakeCfgBackedBinaryArrayOrDie();
  arr.setDecoded(false);
  EXPECT_FALSE(arr.decoded());

  // Act / Assert
  EXPECT_NO_THROW(encoder.visitBinaryArray(&arr));
}

TEST(TiffEncoderVisitBinaryArrayTest_1676, DoesNotThrowWithNonNullCfg_DecodedTrue_1676) {
  // Arrange
  auto encoder = MakeEncoderOrDie(/*root*/ nullptr);
  auto arr = MakeCfgBackedBinaryArrayOrDie();
  arr.setDecoded(true);
  EXPECT_TRUE(arr.decoded());

  // Act / Assert
  EXPECT_NO_THROW(encoder.visitBinaryArray(&arr));
}

TEST(TiffEncoderVisitBinaryArrayTest_1676, Boundary_NullObjectPointer_IsNotUsed_1676) {
  // Boundary / defensive test:
  // We do NOT call visitBinaryArray(nullptr) because the interface accepts a raw pointer
  // and behavior on nullptr is not specified/observable here (would be UB in many implementations).
  SUCCEED();
}