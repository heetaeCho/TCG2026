// =================================================================================================
// TestProjects/exiv2/tests/tiffencoder_setdirty_test_1666.cpp
// Unit tests for Exiv2::Internal::TiffEncoder::setDirty(bool)
// TEST_ID: 1666
// =================================================================================================

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

namespace {

// A minimal header implementation to satisfy TiffEncoder construction in tests.
// This does NOT re-implement TiffEncoder logic; it only provides a ByteOrder.
class DummyTiffHeader final : public Exiv2::Internal::TiffHeaderBase {
public:
  explicit DummyTiffHeader(Exiv2::ByteOrder bo) : bo_(bo) {}
  Exiv2::ByteOrder byteOrder() const override { return bo_; }

private:
  Exiv2::ByteOrder bo_;
};

class TiffEncoderSetDirtyTest_1666 : public ::testing::Test {
protected:
  // Keep these alive for the lifetime of the encoder (refs are stored).
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;
  DummyTiffHeader header_{Exiv2::littleEndian};

  // Helper to construct an encoder with minimal dependencies.
  // We intentionally pass nullptr for pRoot because setDirty() is expected to be
  // observable through the public interface (dirty()/go()) without traversals.
  std::unique_ptr<Exiv2::Internal::TiffEncoder> makeEncoder() {
    Exiv2::ExifData exif; // moved into ctor
    Exiv2::Internal::PrimaryGroups primaryGroups{};
    Exiv2::Internal::FindEncoderFct findFct{}; // default / empty

    return std::make_unique<Exiv2::Internal::TiffEncoder>(
        std::move(exif), iptc_, xmp_,
        /*pRoot=*/nullptr,
        /*isNewImage=*/false,
        std::move(primaryGroups),
        /*pHeader=*/&header_,
        std::move(findFct));
  }
};

} // namespace

TEST_F(TiffEncoderSetDirtyTest_1666, SetDirtyTrueMarksDirtyAndDisablesTraverse_1666) {
  auto enc = makeEncoder();

  enc->setDirty(true);

  EXPECT_TRUE(enc->dirty());
  EXPECT_FALSE(enc->go(Exiv2::Internal::TiffVisitor::geTraverse));
}

TEST_F(TiffEncoderSetDirtyTest_1666, SetDirtyFalseClearsDirtyAndEnablesTraverse_1666) {
  auto enc = makeEncoder();

  enc->setDirty(true);
  ASSERT_TRUE(enc->dirty());
  ASSERT_FALSE(enc->go(Exiv2::Internal::TiffVisitor::geTraverse));

  enc->setDirty(false);

  EXPECT_FALSE(enc->dirty());
  EXPECT_TRUE(enc->go(Exiv2::Internal::TiffVisitor::geTraverse));
}

TEST_F(TiffEncoderSetDirtyTest_1666, ToggleDirtyMultipleTimesKeepsConsistentState_1666) {
  auto enc = makeEncoder();

  enc->setDirty(false);
  EXPECT_FALSE(enc->dirty());
  EXPECT_TRUE(enc->go(Exiv2::Internal::TiffVisitor::geTraverse));

  enc->setDirty(true);
  EXPECT_TRUE(enc->dirty());
  EXPECT_FALSE(enc->go(Exiv2::Internal::TiffVisitor::geTraverse));

  enc->setDirty(true);  // idempotent from caller perspective
  EXPECT_TRUE(enc->dirty());
  EXPECT_FALSE(enc->go(Exiv2::Internal::TiffVisitor::geTraverse));

  enc->setDirty(false);
  EXPECT_FALSE(enc->dirty());
  EXPECT_TRUE(enc->go(Exiv2::Internal::TiffVisitor::geTraverse));
}

TEST_F(TiffEncoderSetDirtyTest_1666, SetDirtyDoesNotDisableKnownMakernoteGoEvent_1666) {
  auto enc = makeEncoder();

  // TiffVisitor default go_ is {true, true} per provided header snippet.
  EXPECT_TRUE(enc->go(Exiv2::Internal::TiffVisitor::geKnownMakernote));

  enc->setDirty(true);
  EXPECT_TRUE(enc->go(Exiv2::Internal::TiffVisitor::geKnownMakernote));

  enc->setDirty(false);
  EXPECT_TRUE(enc->go(Exiv2::Internal::TiffVisitor::geKnownMakernote));
}