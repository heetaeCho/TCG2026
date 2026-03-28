// File: test_tiffvisitor_int_visitMnEntry_1674.cpp
// Unit tests for Exiv2::Internal::TiffEncoder::visitMnEntry
//
// Constraints respected:
// - Treat implementation as a black box (no re-implementation of internal logic).
// - Use only observable behavior through public APIs.
// - No access to private/internal state.
//
// NOTE:
// These tests focus on *observable* behavior that is reliably accessible from the provided interface.
// The visitMnEntry implementation shown has branches that depend on private state (object->mn_, encoder.del_,
// and encoder.exifData_), which are not directly observable or controllable via the provided public API.
// Therefore, these tests validate safety/robustness and stable observable invariants (e.g., dirty flag).

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

#include "exif.hpp"
#include "iptc.hpp"
#include "xmp.hpp"

namespace {

// A very small, test-local header implementation used only to satisfy the TiffEncoder ctor dependency.
// We intentionally keep it minimal and only implement what the base class requires.
// If Exiv2's actual TiffHeaderBase interface changes, adjust the overrides accordingly.
class TestTiffHeader_1674 final : public Exiv2::Internal::TiffHeaderBase {
public:
  explicit TestTiffHeader_1674(Exiv2::ByteOrder bo) : bo_(bo) {}
  ~TestTiffHeader_1674() override = default;

  Exiv2::ByteOrder byteOrder() const override { return bo_; }

private:
  Exiv2::ByteOrder bo_;
};

// A helper to provide a FindEncoderFct. The encoder may or may not call it for these tests;
// we provide a harmless function that returns nullptr.
static Exiv2::Internal::TiffEncoder::FindEncoderFct MakeFindEncoderFct_1674() {
  return [](uint16_t /*tag*/, Exiv2::IfdId /*group*/) -> Exiv2::Internal::TiffEncoderFct {
    return nullptr;
  };
}

class TiffEncoderVisitMnEntryTest_1674 : public ::testing::Test {
protected:
  // Builds a valid encoder instance with minimal collaborators.
  static Exiv2::Internal::TiffEncoder MakeEncoder_1674(Exiv2::ExifData exif = Exiv2::ExifData()) {
    static const Exiv2::IptcData kIptc;
    static const Exiv2::XmpData  kXmp;

    // Minimal root component. Tag/group values are not important for these tests.
    static Exiv2::Internal::TiffComponent kRoot(/*tag=*/0, /*group=*/Exiv2::ifdIdNotSet);

    // Minimal primary groups: leave default/empty.
    Exiv2::Internal::PrimaryGroups primaryGroups;

    // Header must be non-null because the encoder ctor uses pHeader->byteOrder().
    static TestTiffHeader_1674 kHeader(Exiv2::littleEndian);

    return Exiv2::Internal::TiffEncoder(
        std::move(exif),
        kIptc,
        kXmp,
        &kRoot,
        /*isNewImage=*/true,
        std::move(primaryGroups),
        &kHeader,
        MakeFindEncoderFct_1674());
  }
};

}  // namespace

TEST_F(TiffEncoderVisitMnEntryTest_1674, VisitMnEntryWithFreshMnEntryDoesNotThrow_1674) {
  auto encoder = MakeEncoder_1674();

  // Construct a TiffMnEntry. If mn_ is null by default (typical for a fresh entry),
  // the implementation may take the encode path. We only assert no exceptions/crashes.
  Exiv2::Internal::TiffMnEntry mnEntry(/*tag=*/0x1234, /*group=*/Exiv2::ifd0Id, /*mnGroup=*/Exiv2::ifdIdNotSet);

  EXPECT_NO_THROW(encoder.visitMnEntry(&mnEntry));
}

TEST_F(TiffEncoderVisitMnEntryTest_1674, VisitMnEntryDoesNotClearDirtyFlagIfAlreadyDirty_1674) {
  auto encoder = MakeEncoder_1674();

  // We can observe and control the dirty flag via the public API.
  encoder.setDirty(true);
  ASSERT_TRUE(encoder.dirty());

  Exiv2::Internal::TiffMnEntry mnEntry(/*tag=*/0x0001, /*group=*/Exiv2::ifd0Id, /*mnGroup=*/Exiv2::ifdIdNotSet);

  // Regardless of which internal branch executes, visitMnEntry should not "unset" dirtiness.
  EXPECT_NO_THROW(encoder.visitMnEntry(&mnEntry));
  EXPECT_TRUE(encoder.dirty());
}

TEST_F(TiffEncoderVisitMnEntryTest_1674, VisitMnEntryHandlesMultipleCallsOnSameEntry_1674) {
  auto encoder = MakeEncoder_1674();

  Exiv2::Internal::TiffMnEntry mnEntry(/*tag=*/0x00FF, /*group=*/Exiv2::ifd1Id, /*mnGroup=*/Exiv2::ifdIdNotSet);

  // Boundary-ish behavior: repeated invocations should be safe.
  EXPECT_NO_THROW(encoder.visitMnEntry(&mnEntry));
  EXPECT_NO_THROW(encoder.visitMnEntry(&mnEntry));
  EXPECT_NO_THROW(encoder.visitMnEntry(&mnEntry));
}