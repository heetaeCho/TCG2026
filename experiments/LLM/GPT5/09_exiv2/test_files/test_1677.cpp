// =================================================================================================
// TEST_ID: 1677
// File:    test_tiffvisitor_int_visitBinaryArrayEnd_1677.cpp
// Target:  Exiv2::Internal::TiffEncoder::visitBinaryArrayEnd(TiffBinaryArray*)
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

// These are commonly available in Exiv2; included defensively for the encoder ctor types.
#include "exif.hpp"
#include "iptc.hpp"
#include "xmp.hpp"

namespace {

// Some Exiv2 internal builds keep these in Exiv2::Internal; others in Exiv2::Internal::.
using ::testing::NiceMock;

class TiffEncoderTest_1677 : public ::testing::Test {
protected:
  // Minimal root component usable as encoder's root pointer.
  // We avoid relying on any particular IFD enum value by using a zero-cast.
  Exiv2::Internal::TiffComponent root_{0, static_cast<Exiv2::IfdId>(0)};

  // Many Exiv2 builds have a concrete header type. If your tree uses a different concrete type,
  // replace this with the appropriate header construction.
  //
  // NOTE: We intentionally keep this as simple as possible; tests focus on observable encoder behavior.
  struct MinimalHeader final : public Exiv2::Internal::TiffHeaderBase {
    explicit MinimalHeader(Exiv2::ByteOrder bo) : bo_(bo) {}
    Exiv2::ByteOrder byteOrder() const override { return bo_; }

    // If your Exiv2 version has more pure virtual methods on TiffHeaderBase, implement them here
    // with minimal safe defaults required for compilation.
    Exiv2::ByteOrder bo_;
  };

  Exiv2::Internal::TiffEncoder makeEncoder_(Exiv2::ByteOrder bo = Exiv2::littleEndian) {
    // Empty metadata containers are fine for these tests: we only observe encoder.dirty().
    Exiv2::ExifData exif;
    Exiv2::IptcData iptc;
    Exiv2::XmpData xmp;

    // PrimaryGroups is an Exiv2 internal type; default construction should be valid.
    Exiv2::Internal::PrimaryGroups primaryGroups{};

    // Header must be non-null; encoder ctor reads byteOrder().
    header_ = std::make_unique<MinimalHeader>(bo);

    // findEncoderFct_ is not used by visitBinaryArrayEnd() in the provided snippet.
    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;

    return Exiv2::Internal::TiffEncoder(std::move(exif), iptc, xmp, &root_,
                                        /*isNewImage=*/false, std::move(primaryGroups),
                                        header_.get(), findEncoderFct);
  }

  // Builds a TiffBinaryArray using the ArrayCfg-based ctor so cfg() is expected to be non-null.
  static Exiv2::Internal::TiffBinaryArray makeArrayWithCfg_(uint16_t tag, Exiv2::IfdId group,
                                                           Exiv2::TiffType elType,
                                                           Exiv2::Internal::CryptFct cryptFct) {
    Exiv2::Internal::ArrayCfg cfg{};
    cfg.elTiffType_ = elType;
    cfg.cryptFct_ = cryptFct;
    cfg.hasSize_ = false;
    cfg.hasFillers_ = false;
    cfg.concat_ = false;
    // elDefaultDef_ left default-initialized; tests do not depend on it.

    // arrayDef may be null; we avoid assuming internal usage.
    const Exiv2::Internal::ArrayDef* arrayDef = nullptr;
    const size_t defSize = 0;

    return Exiv2::Internal::TiffBinaryArray(tag, group, cfg, arrayDef, defSize);
  }

  // Builds a TiffBinaryArray using the ArraySet-based ctor so cfg() is expected to be null.
  static Exiv2::Internal::TiffBinaryArray makeArrayWithoutCfg_(uint16_t tag, Exiv2::IfdId group) {
    const Exiv2::Internal::ArraySet* arraySet = nullptr;
    const size_t setSize = 0;
    Exiv2::Internal::CfgSelFct cfgSelFct = nullptr;
    return Exiv2::Internal::TiffBinaryArray(tag, group, arraySet, setSize, cfgSelFct);
  }

  // Helper to set the entry data buffer in a way observable by public API.
  static void setEntryData_(Exiv2::Internal::TiffBinaryArray& arr, size_t n) {
    auto buf = std::make_shared<Exiv2::DataBuf>(n);
    if (n > 0) {
      // Fill with deterministic content.
      for (size_t i = 0; i < n; ++i) buf->write_uint8(i, static_cast<uint8_t>(i & 0xFF));
    }
    arr.setData(buf);
  }

  std::unique_ptr<MinimalHeader> header_;
};

// -------------------------------------------------------------------------------------------------
// TESTS
// -------------------------------------------------------------------------------------------------

TEST_F(TiffEncoderTest_1677, NotDecoded_EarlyReturn_DirtyRemainsFalse_1677) {
  auto encoder = makeEncoder_();
  ASSERT_FALSE(encoder.dirty());

  // cfg non-null (ArrayCfg ctor), but decoded() remains false by default.
  auto arr = makeArrayWithCfg_(/*tag=*/0x1234, static_cast<Exiv2::IfdId>(0),
                               static_cast<Exiv2::TiffType>(0), /*cryptFct=*/nullptr);

  // Provide some data; should still early-return due to !decoded().
  setEntryData_(arr, /*n=*/8);

  encoder.visitBinaryArrayEnd(&arr);

  // Observable behavior: dirty() remains unchanged.
  EXPECT_FALSE(encoder.dirty());
}

TEST_F(TiffEncoderTest_1677, NoCfg_EarlyReturn_DirtyRemainsFalse_1677) {
  auto encoder = makeEncoder_();
  ASSERT_FALSE(encoder.dirty());

  // cfg() expected null with ArraySet ctor; set decoded true to ensure cfg() check is the gate.
  auto arr = makeArrayWithoutCfg_(/*tag=*/0x1234, static_cast<Exiv2::IfdId>(0));
  arr.setDecoded(true);

  // Even with non-empty data, visitBinaryArrayEnd should return immediately when cfg() is null.
  setEntryData_(arr, /*n=*/8);

  encoder.visitBinaryArrayEnd(&arr);

  EXPECT_FALSE(encoder.dirty());
}

TEST_F(TiffEncoderTest_1677, SizeZero_EarlyReturn_DirtyRemainsFalse_1677) {
  auto encoder = makeEncoder_();
  ASSERT_FALSE(encoder.dirty());

  auto arr = makeArrayWithCfg_(/*tag=*/0x1234, static_cast<Exiv2::IfdId>(0),
                               static_cast<Exiv2::TiffType>(0), /*cryptFct=*/nullptr);

  // Ensure decoded() passes the decoded check.
  arr.setDecoded(true);

  // Provide an empty buffer (size == 0). visitBinaryArrayEnd should return at size==0 gate.
  setEntryData_(arr, /*n=*/0);

  encoder.visitBinaryArrayEnd(&arr);

  EXPECT_FALSE(encoder.dirty());
}

TEST_F(TiffEncoderTest_1677, RepeatedCalls_OnEarlyReturnPaths_AreIdempotent_1677) {
  auto encoder = makeEncoder_();
  ASSERT_FALSE(encoder.dirty());

  auto arr = makeArrayWithoutCfg_(/*tag=*/0xCAFE, static_cast<Exiv2::IfdId>(0));
  arr.setDecoded(true);
  setEntryData_(arr, /*n=*/16);

  // Call multiple times: should remain safe and keep dirty() unchanged on the early-return path.
  encoder.visitBinaryArrayEnd(&arr);
  encoder.visitBinaryArrayEnd(&arr);
  encoder.visitBinaryArrayEnd(&arr);

  EXPECT_FALSE(encoder.dirty());
}

}  // namespace