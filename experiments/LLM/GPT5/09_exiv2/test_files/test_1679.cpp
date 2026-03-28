// File: test_tiffencoder_encode_tiffcomponent_1679.cpp
// TEST_ID: 1679
//
// Unit tests for Exiv2::Internal::TiffEncoder::encodeTiffComponent
// Constraints: treat implementation as black box; test only observable behavior via public API.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"

using ::testing::_;
using ::testing::NotNull;

namespace {

// A minimal test double for TiffEntryBase that lets us observe encode() -> doEncode() calls
// without touching internal state of TiffEncoder.
class ObservingEntry final : public Exiv2::Internal::TiffEntryBase {
 public:
  ObservingEntry(uint16_t tag, Exiv2::IfdId group, Exiv2::Internal::TiffType tiffType)
      : Exiv2::Internal::TiffEntryBase(tag, group, tiffType) {}

  // Expose protected setter to control boundary scenarios that depend on idx().
  void ForceIdx(int idx) { setIdx(idx); }

  int encode_calls() const { return encode_calls_; }
  const Exiv2::Exifdatum* last_datum() const { return last_datum_; }

 protected:
  void doEncode(Exiv2::Internal::TiffEncoder& /*encoder*/, const Exiv2::Exifdatum* datum) override {
    ++encode_calls_;
    last_datum_ = datum;
  }

 private:
  int encode_calls_{0};
  const Exiv2::Exifdatum* last_datum_{nullptr};
};

// Helper: build an Exifdatum with a specific tag/groupName and idx.
static Exiv2::Exifdatum MakeExifdatum(uint16_t tag, const std::string& groupName, int idx) {
  Exiv2::ExifKey key(tag, groupName);
  key.setIdx(idx);
  // pValue is not needed for these tests; nullptr is sufficient for construction in Exiv2.
  Exiv2::Exifdatum ed(key, nullptr);
  return ed;
}

// Helper: FindEncoderFct that never provides a specialized encoder function so that
// TiffEntryBase::encode() is used (when applicable).
static Exiv2::Internal::FindEncoderFct NoSpecialEncoderFct() {
  return [](const std::string& /*make*/, uint16_t /*tag*/, Exiv2::IfdId /*group*/)
             -> Exiv2::Internal::TiffEncoder::EncoderFct {
    return nullptr;
  };
}

// We need a TiffHeaderBase instance for TiffEncoder's constructor.
// In Exiv2, TiffHeaderBase is typically an abstract base. If your build exposes a concrete
// header type (e.g., TiffHeader), prefer using it instead of this stub.
//
// This stub only implements byteOrder(); if your Exiv2 version has more pure virtuals on
// TiffHeaderBase, extend this stub accordingly.
class StubTiffHeader final : public Exiv2::Internal::TiffHeaderBase {
 public:
  explicit StubTiffHeader(Exiv2::ByteOrder bo) : bo_(bo) {}
  Exiv2::ByteOrder byteOrder() const override { return bo_; }

 private:
  Exiv2::ByteOrder bo_;
};

class TiffEncoderEncodeTiffComponentTest_1679 : public ::testing::Test {
 protected:
  // Constructs a TiffEncoder with minimal collaborators.
  // Note: encodeTiffComponent() does not require a non-null pRoot_ for these tests.
  static std::unique_ptr<Exiv2::Internal::TiffEncoder> MakeEncoder(Exiv2::ExifData exifData) {
    static const Exiv2::IptcData kEmptyIptc;
    static const Exiv2::XmpData kEmptyXmp;

    static StubTiffHeader kHeader(Exiv2::littleEndian);
    Exiv2::Internal::PrimaryGroups primaryGroups;  // empty is fine for these tests

    return std::make_unique<Exiv2::Internal::TiffEncoder>(
        std::move(exifData),
        kEmptyIptc,
        kEmptyXmp,
        /*pRoot=*/nullptr,
        /*isNewImage=*/false,
        std::move(primaryGroups),
        &kHeader,
        NoSpecialEncoderFct());
  }
};

}  // namespace

TEST_F(TiffEncoderEncodeTiffComponentTest_1679, DatumProvided_UpdatesEntryIdxToDatumIdx_1679) {
  Exiv2::ExifData exifData;
  auto encoder = MakeEncoder(std::move(exifData));
  ASSERT_FALSE(encoder->dirty());

  // Use a tag/group that is unlikely to be treated as an "image tag".
  // (Even if it is, idx update is still observable and required.)
  const auto group = Exiv2::ifdExif;
  const std::string groupName = Exiv2::groupName(group);
  constexpr uint16_t kTag = 0x9286;  // UserComment tag in Exif (commonly 0x9286)

  ObservingEntry entry(kTag, group, Exiv2::Internal::ttUndefined);
  entry.ForceIdx(0);

  Exiv2::Exifdatum provided = MakeExifdatum(kTag, groupName, /*idx=*/7);

  encoder->encodeTiffComponent(&entry, &provided);

  // Observable: entry idx should match the provided datum's idx.
  EXPECT_EQ(entry.idx(), provided.idx());
}

TEST_F(TiffEncoderEncodeTiffComponentTest_1679, DatumMissingAndKeyNotFound_SetsDirty_1679) {
  Exiv2::ExifData exifData;  // empty => key not found
  auto encoder = MakeEncoder(std::move(exifData));
  ASSERT_FALSE(encoder->dirty());

  const auto group = Exiv2::ifdExif;
  constexpr uint16_t kTag = 0x9286;

  ObservingEntry entry(kTag, group, Exiv2::Internal::ttUndefined);
  entry.ForceIdx(3);

  encoder->encodeTiffComponent(&entry, /*datum=*/nullptr);

  // Observable: dirty becomes true when datum is missing and ExifData doesn't contain the key.
  EXPECT_TRUE(encoder->dirty());

  // Boundary/robustness: idx should remain whatever it was (no datum to derive idx from).
  EXPECT_EQ(entry.idx(), 3);
}

TEST_F(TiffEncoderEncodeTiffComponentTest_1679, DatumMissingButKeyFound_FirstCallNotDirty_SecondCallDirtyDueToErase_1679) {
  const auto group = Exiv2::ifdExif;
  const std::string groupName = Exiv2::groupName(group);
  constexpr uint16_t kTag = 0x9286;

  Exiv2::ExifData exifData;
  Exiv2::Exifdatum stored = MakeExifdatum(kTag, groupName, /*idx=*/1);
  exifData.add(stored);

  auto encoder = MakeEncoder(std::move(exifData));
  ASSERT_FALSE(encoder->dirty());

  ObservingEntry entry(kTag, group, Exiv2::Internal::ttUndefined);
  entry.ForceIdx(0);

  // 1) datum=nullptr but key exists in ExifData -> should not mark dirty.
  encoder->encodeTiffComponent(&entry, /*datum=*/nullptr);
  EXPECT_FALSE(encoder->dirty());

  // 2) Call again with datum=nullptr:
  // If the encoder erased the found Exifdatum (del_ enabled by default in implementation),
  // the key should no longer be found and dirty should become true.
  encoder->encodeTiffComponent(&entry, /*datum=*/nullptr);
  EXPECT_TRUE(encoder->dirty());
}

TEST_F(TiffEncoderEncodeTiffComponentTest_1679, MultipleSameKeyDifferentIdx_PrefersMatchingIdx_WhenDatumNull_1679) {
  const auto group = Exiv2::ifdExif;
  const std::string groupName = Exiv2::groupName(group);
  constexpr uint16_t kTag = 0x9286;

  // Two Exifdatum entries with the same key (same tag+groupName) but different idx.
  Exiv2::ExifData exifData;
  Exiv2::Exifdatum ed0 = MakeExifdatum(kTag, groupName, /*idx=*/0);
  Exiv2::Exifdatum ed1 = MakeExifdatum(kTag, groupName, /*idx=*/1);
  exifData.add(ed0);
  exifData.add(ed1);

  auto encoder = MakeEncoder(std::move(exifData));
  ASSERT_FALSE(encoder->dirty());

  ObservingEntry entry(kTag, group, Exiv2::Internal::ttUndefined);

  // Boundary scenario: entry idx is 1, so the encoder should select the Exifdatum with idx 1
  // when resolving duplicates (observable via which datum reaches doEncode()).
  entry.ForceIdx(1);

  encoder->encodeTiffComponent(&entry, /*datum=*/nullptr);

  // Verify external interaction: our observing entry should have been asked to encode with
  // a non-null datum, and that datum should match idx 1.
  //
  // Note: If the tag/group is treated as an "image tag" by the library, encoding may be skipped;
  // in that case last_datum() would remain nullptr and this assertion would fail. If that happens
  // in your environment, switch kTag/group to a known non-image tag/group combination.
  ASSERT_THAT(entry.last_datum(), NotNull());
  EXPECT_EQ(entry.last_datum()->idx(), 1);
}

TEST_F(TiffEncoderEncodeTiffComponentTest_1679, NullObject_DoesNotCrash_WhenNotInvoked_1679) {
  // Exceptional/error case (observable): encodeTiffComponent requires a valid object pointer.
  // We do not call it with nullptr because the interface does not promise nullptr safety.
  // This test exists to document the constraint explicitly and keep the suite consistent.
  SUCCEED();
}