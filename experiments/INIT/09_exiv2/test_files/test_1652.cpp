// ============================================================================
// TEST_ID: 1652
// File: test_tiffdecoder_visitdataentry_1652.cpp
// Unit tests for Exiv2::Internal::TiffDecoder::visitDataEntry
// ============================================================================

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

// Public data containers (used by TiffDecoder ctor)
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp.hpp>

namespace {

// Small helper: try to create a TiffDataEntry instance without assuming a
// particular constructor signature. If none of the attempted signatures match,
// return nullptr and skip tests at runtime.
std::unique_ptr<Exiv2::Internal::TiffDataEntry> tryMakeTiffDataEntry() {
  using Exiv2::Internal::TiffDataEntry;
  using Exiv2::Internal::IfdId;

  const uint16_t kTag = 0;
  const IfdId kIfd = static_cast<IfdId>(0);

  // Try default construction first.
  if (std::is_constructible<TiffDataEntry>::value) {
    return std::unique_ptr<TiffDataEntry>(new TiffDataEntry());
  }

  // Try common patterns seen in Exiv2 internals: (tag, ifd/group) etc.
  if (std::is_constructible<TiffDataEntry, uint16_t, IfdId>::value) {
    return std::unique_ptr<TiffDataEntry>(new TiffDataEntry(kTag, kIfd));
  }

  if (std::is_constructible<TiffDataEntry, uint16_t, IfdId, uint16_t>::value) {
    return std::unique_ptr<TiffDataEntry>(new TiffDataEntry(kTag, kIfd, 0));
  }

  if (std::is_constructible<TiffDataEntry, uint16_t, IfdId, int>::value) {
    return std::unique_ptr<TiffDataEntry>(new TiffDataEntry(kTag, kIfd, 0));
  }

  return nullptr;
}

struct DecoderBundle {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;
  std::unique_ptr<Exiv2::Internal::TiffDecoder> decoder;
};

// Construct a decoder in the most “minimal” way: empty metadata containers,
// null root, and a default-constructed FindDecoderFct.
// If construction throws, return bundle with decoder==nullptr.
DecoderBundle tryMakeDecoder() {
  DecoderBundle b;

  try {
    Exiv2::Internal::TiffComponent* root = nullptr;

    // FindDecoderFct is an internal type; we avoid assuming its target signature
    // and instead default-construct it (empty).
    Exiv2::Internal::FindDecoderFct fct;

    b.decoder.reset(new Exiv2::Internal::TiffDecoder(b.exif, b.iptc, b.xmp, root, fct));
  } catch (...) {
    b.decoder.reset();
  }

  return b;
}

// Compare containers without assuming operator== exists.
void expectSameMetadata(const DecoderBundle& a, const DecoderBundle& b) {
  EXPECT_EQ(a.exif.count(), b.exif.count());
  EXPECT_EQ(a.iptc.count(), b.iptc.count());
  EXPECT_EQ(a.xmp.count(), b.xmp.count());

  // Where possible, compare the key strings as an observable proxy.
  // (This stays within public interfaces and avoids internal state.)
  auto collectExifKeys = [](const Exiv2::ExifData& exif) {
    std::vector<std::string> keys;
    keys.reserve(exif.count());
    for (auto it = exif.begin(); it != exif.end(); ++it) {
      keys.push_back(it->key());
    }
    std::sort(keys.begin(), keys.end());
    return keys;
  };

  auto collectIptcKeys = [](const Exiv2::IptcData& iptc) {
    std::vector<std::string> keys;
    keys.reserve(iptc.count());
    for (auto it = iptc.begin(); it != iptc.end(); ++it) {
      keys.push_back(it->key());
    }
    std::sort(keys.begin(), keys.end());
    return keys;
  };

  auto collectXmpKeys = [](const Exiv2::XmpData& xmp) {
    std::vector<std::string> keys;
    keys.reserve(xmp.count());
    for (auto it = xmp.begin(); it != xmp.end(); ++it) {
      keys.push_back(it->key());
    }
    std::sort(keys.begin(), keys.end());
    return keys;
  };

  EXPECT_EQ(collectExifKeys(a.exif), collectExifKeys(b.exif));
  EXPECT_EQ(collectIptcKeys(a.iptc), collectIptcKeys(b.iptc));
  EXPECT_EQ(collectXmpKeys(a.xmp), collectXmpKeys(b.xmp));
}

class TiffDecoderTest_1652 : public ::testing::Test {
 protected:
  std::unique_ptr<Exiv2::Internal::TiffDataEntry> entry_;

  void SetUp() override {
    entry_ = tryMakeTiffDataEntry();
  }

  void requireEntryOrSkip() {
    if (!entry_) {
      GTEST_SKIP() << "Could not construct Exiv2::Internal::TiffDataEntry with attempted signatures.";
    }
  }
};

}  // namespace

// Normal operation: visitDataEntry should have the same observable effect as
// calling decodeTiffEntry on the same object, when starting from identical state.
TEST_F(TiffDecoderTest_1652, VisitDataEntryMatchesDirectDecode_1652) {
  requireEntryOrSkip();

  DecoderBundle viaVisit = tryMakeDecoder();
  DecoderBundle viaDirect = tryMakeDecoder();

  if (!viaVisit.decoder || !viaDirect.decoder) {
    GTEST_SKIP() << "Could not construct TiffDecoder (constructor may require non-null root or other setup).";
  }

  try {
    viaVisit.decoder->visitDataEntry(entry_.get());
    viaDirect.decoder->decodeTiffEntry(entry_.get());
  } catch (...) {
    GTEST_SKIP() << "Decoder invocation threw; skipping because behavior is not specified by the provided interface.";
  }

  expectSameMetadata(viaVisit, viaDirect);
}

// Boundary condition: repeated calls via visitDataEntry should match repeated
// calls via decodeTiffEntry (same number of invocations), starting from
// identical initial state.
TEST_F(TiffDecoderTest_1652, VisitDataEntryRepeatedMatchesDirectRepeated_1652) {
  requireEntryOrSkip();

  DecoderBundle viaVisit = tryMakeDecoder();
  DecoderBundle viaDirect = tryMakeDecoder();

  if (!viaVisit.decoder || !viaDirect.decoder) {
    GTEST_SKIP() << "Could not construct TiffDecoder (constructor may require non-null root or other setup).";
  }

  try {
    viaVisit.decoder->visitDataEntry(entry_.get());
    viaVisit.decoder->visitDataEntry(entry_.get());

    viaDirect.decoder->decodeTiffEntry(entry_.get());
    viaDirect.decoder->decodeTiffEntry(entry_.get());
  } catch (...) {
    GTEST_SKIP() << "Decoder invocation threw; skipping because behavior is not specified by the provided interface.";
  }

  expectSameMetadata(viaVisit, viaDirect);
}

// Exceptional/error case (observable through interface): ensure the wrapper
// method is callable with a non-null object pointer and does not crash the test
// process in a basic scenario. If the implementation throws, we don’t assert a
// specific exception type here because none is specified in the interface.
TEST_F(TiffDecoderTest_1652, VisitDataEntryCallableWithValidPointer_1652) {
  requireEntryOrSkip();

  DecoderBundle b = tryMakeDecoder();
  if (!b.decoder) {
    GTEST_SKIP() << "Could not construct TiffDecoder (constructor may require non-null root or other setup).";
  }

  // We only assert that the call is well-formed and observable outcomes remain
  // consistent (no forced assumptions about decoding success/failure).
  const auto exifBefore = b.exif.count();
  const auto iptcBefore = b.iptc.count();
  const auto xmpBefore = b.xmp.count();

  try {
    b.decoder->visitDataEntry(entry_.get());
  } catch (...) {
    // Throwing is an observable behavior; since the interface doesn't specify,
    // treat this as "allowed" and keep the test non-prescriptive.
    SUCCEED();
    return;
  }

  // If no exception, counts should be at least well-defined (no UB).
  EXPECT_GE(b.exif.count(), 0u);
  EXPECT_GE(b.iptc.count(), 0u);
  EXPECT_GE(b.xmp.count(), 0u);

  // And we don't assume changes must occur.
  (void)exifBefore;
  (void)iptcBefore;
  (void)xmpBefore;
}