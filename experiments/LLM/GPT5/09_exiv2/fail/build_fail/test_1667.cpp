// ============================================================================
// TEST_ID: 1667
// Unit tests for Exiv2::Internal::TiffEncoder::dirty() const
// File: test_tiffencoder_dirty_1667.cpp
// ============================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

// Public Exiv2 data containers
#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp.hpp"

// Class under test (internal)
#include "tiffvisitor_int.hpp"

// Some Exiv2 builds expose TiffHeaderBase via other internal headers. If your build
// needs an extra include for TiffHeaderBase, add it here (examples in Exiv2 tree):
//   #include "tiffimage_int.hpp"
//   #include "tiffcomposite_int.hpp"
//   #include "tiffheader_int.hpp"

namespace {

// A minimal header object to satisfy TiffEncoder's ctor dependency on pHeader->byteOrder().
// If your Exiv2 version has additional pure-virtuals on TiffHeaderBase, implement them
// here as trivial stubs required only to construct the encoder for these tests.
class DummyTiffHeaderBase_1667 : public Exiv2::Internal::TiffHeaderBase {
public:
  explicit DummyTiffHeaderBase_1667(Exiv2::ByteOrder bo) : bo_(bo) {}
  ~DummyTiffHeaderBase_1667() override = default;

  Exiv2::ByteOrder byteOrder() const override { return bo_; }

private:
  Exiv2::ByteOrder bo_;
};

class TiffEncoderTest_1667 : public ::testing::Test {
protected:
  // Helper to build an encoder with minimal collaborators.
  static std::unique_ptr<Exiv2::Internal::TiffEncoder> MakeEncoder(Exiv2::ExifData exifData) {
    static Exiv2::IptcData iptcData; // empty, stable lifetime
    static Exiv2::XmpData xmpData;   // empty, stable lifetime

    // Root TIFF component is not needed for dirty() tests; ctor should not dereference it.
    Exiv2::Internal::TiffComponent* root = nullptr;

    // Provide a valid header; dirty() does not depend on byte order, but ctor does.
    // Use a commonly available enumerator; adjust if your build uses different names.
    static DummyTiffHeaderBase_1667 header(Exiv2::littleEndian);

    // PrimaryGroups type comes from Exiv2 internals; default construction should be valid.
    Exiv2::Internal::PrimaryGroups primaryGroups{};

    // Encoder finder function is not needed for dirty() tests.
    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;

    return std::make_unique<Exiv2::Internal::TiffEncoder>(
        std::move(exifData),
        iptcData,
        xmpData,
        root,
        /*isNewImage=*/false,
        std::move(primaryGroups),
        &header,
        findEncoderFct);
  }
};

} // namespace

// ----------------------------------------------------------------------------
// Normal operation: empty ExifData + default dirty flag => not dirty
// ----------------------------------------------------------------------------
TEST_F(TiffEncoderTest_1667, DirtyReturnsFalseWhenNoExifAndNotMarkedDirty_1667) {
  Exiv2::ExifData exif;
  auto encoder = MakeEncoder(std::move(exif));

  EXPECT_FALSE(encoder->dirty());
}

// ----------------------------------------------------------------------------
// Normal operation: setDirty(true) makes dirty() true
// ----------------------------------------------------------------------------
TEST_F(TiffEncoderTest_1667, DirtyReturnsTrueAfterSetDirtyTrue_1667) {
  Exiv2::ExifData exif;
  auto encoder = MakeEncoder(std::move(exif));

  encoder->setDirty(true);
  EXPECT_TRUE(encoder->dirty());
}

// ----------------------------------------------------------------------------
// Boundary: toggling setDirty back to false restores cleanliness when ExifData empty
// ----------------------------------------------------------------------------
TEST_F(TiffEncoderTest_1667, DirtyReturnsFalseAfterSetDirtyTrueThenFalseWhenExifEmpty_1667) {
  Exiv2::ExifData exif;
  auto encoder = MakeEncoder(std::move(exif));

  encoder->setDirty(true);
  ASSERT_TRUE(encoder->dirty());

  encoder->setDirty(false);
  EXPECT_FALSE(encoder->dirty());
}

// ----------------------------------------------------------------------------
// Normal operation: non-empty ExifData makes dirty() true (even if not marked dirty)
// ----------------------------------------------------------------------------
TEST_F(TiffEncoderTest_1667, DirtyReturnsTrueWhenExifDataNotEmpty_1667) {
  Exiv2::ExifData exif;

  // Add one datum via public ExifData interface. We only assert the observable outcome
  // through dirty(), not any internal encoding behavior.
  //
  // Use operator[] which is part of the provided interface.
  exif["Exif.Image.Make"] = "UnitTestMake";

  auto encoder = MakeEncoder(std::move(exif));
  EXPECT_TRUE(encoder->dirty());
}

// ----------------------------------------------------------------------------
// Boundary: setDirty(false) does not override non-empty ExifData (still dirty)
// ----------------------------------------------------------------------------
TEST_F(TiffEncoderTest_1667, DirtyStaysTrueWithNonEmptyExifEvenAfterSetDirtyFalse_1667) {
  Exiv2::ExifData exif;
  exif["Exif.Image.Model"] = "UnitTestModel";

  auto encoder = MakeEncoder(std::move(exif));

  // Even if user explicitly clears the dirty flag, the interface contract (as observed
  // through dirty()) indicates ExifData presence still implies dirty.
  encoder->setDirty(false);
  EXPECT_TRUE(encoder->dirty());
}

// ----------------------------------------------------------------------------
// Boundary: setDirty(true) remains true regardless of ExifData content
// ----------------------------------------------------------------------------
TEST_F(TiffEncoderTest_1667, DirtyRemainsTrueWhenSetDirtyTrueEvenIfExifEmpty_1667) {
  Exiv2::ExifData exif;
  auto encoder = MakeEncoder(std::move(exif));

  encoder->setDirty(true);
  EXPECT_TRUE(encoder->dirty());

  // Repeat call to ensure stable behavior.
  EXPECT_TRUE(encoder->dirty());
}