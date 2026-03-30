// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::TiffDecoder::visitBinaryElement
// (black-box tests; no inference of internal logic)
// *****************************************************************

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Exiv2 public types (ExifData/IptcData/XmpData, etc.)
#include <exiv2/exiv2.hpp>

// Internal headers under test
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

// Try to construct a TiffBinaryElement with whatever constructor exists in the
// target Exiv2 version. This is intentionally "constructor-probing" only; it
// does not assume behavior/logic.
template <typename... Args>
static Exiv2::Internal::TiffBinaryElement* TryNewBinaryElement(Args&&... args) {
  if constexpr (std::is_constructible_v<Exiv2::Internal::TiffBinaryElement, Args...>) {
    return new Exiv2::Internal::TiffBinaryElement(std::forward<Args>(args)...);
  } else {
    return nullptr;
  }
}

static std::unique_ptr<Exiv2::Internal::TiffBinaryElement> MakeBinaryElementOrSkip() {
  using Exiv2::Internal::TiffBinaryElement;

  // Common constructor shapes seen across Exiv2 internals (varies by version).
  // We try a few and skip the tests if none match.
  TiffBinaryElement* p = nullptr;

  // 1) Default constructor (if available)
  p = TryNewBinaryElement<>();
  if (p) return std::unique_ptr<TiffBinaryElement>(p);

  // 2) (uint16_t tag, IfdId group)
  p = TryNewBinaryElement<uint16_t, Exiv2::IfdId>(static_cast<uint16_t>(0), Exiv2::ifdIdNotSet);
  if (p) return std::unique_ptr<TiffBinaryElement>(p);

  // 3) (uint16_t tag, IfdId group, uint16_t tiffType)
  //    Using 0 for type here; we don't assume meaning—just construction.
  p = TryNewBinaryElement<uint16_t, Exiv2::IfdId, uint16_t>(static_cast<uint16_t>(0), Exiv2::ifdIdNotSet,
                                                           static_cast<uint16_t>(0));
  if (p) return std::unique_ptr<TiffBinaryElement>(p);

  // 4) (uint16_t tag, IfdId group, TiffComponent* parent)
  p = TryNewBinaryElement<uint16_t, Exiv2::IfdId, Exiv2::Internal::TiffComponent*>(
      static_cast<uint16_t>(0), Exiv2::ifdIdNotSet, nullptr);
  if (p) return std::unique_ptr<TiffBinaryElement>(p);

  // 5) (uint16_t tag, IfdId group, uint16_t tiffType, TiffComponent* parent)
  p = TryNewBinaryElement<uint16_t, Exiv2::IfdId, uint16_t, Exiv2::Internal::TiffComponent*>(
      static_cast<uint16_t>(0), Exiv2::ifdIdNotSet, static_cast<uint16_t>(0), nullptr);
  if (p) return std::unique_ptr<TiffBinaryElement>(p);

  // If Exiv2 changes constructor surface, we prefer a clean skip rather than
  // guessing private/internal invariants.
  return nullptr;
}

class TiffDecoderVisitBinaryElementTest_1665 : public ::testing::Test {
 protected:
  // Helper to create a decoder (constructor signature is given in the prompt).
  static Exiv2::Internal::TiffDecoder MakeDecoder(Exiv2::ExifData& exif,
                                                 Exiv2::IptcData& iptc,
                                                 Exiv2::XmpData& xmp) {
    // pRoot and findDecoderFct are allowed by the public constructor; we do not
    // assume they are used for these tests.
    Exiv2::Internal::TiffComponent* root = nullptr;
    Exiv2::Internal::FindDecoderFct fct{};
    return Exiv2::Internal::TiffDecoder(exif, iptc, xmp, root, fct);
  }

  // Snapshot observable state of metadata containers (purely via public API).
  struct MetaSnapshot {
    size_t exifCount = 0;
    size_t iptcCount = 0;
    size_t xmpCount = 0;
  };

  static MetaSnapshot Snapshot(const Exiv2::ExifData& exif,
                               const Exiv2::IptcData& iptc,
                               const Exiv2::XmpData& xmp) {
    MetaSnapshot s;
    s.exifCount = exif.count();
    s.iptcCount = iptc.count();
    s.xmpCount = xmp.count();
    return s;
  }
};

}  // namespace

// -----------------------------------------------------------------------------
// Normal operation: visitBinaryElement is callable and does not throw for a
// constructible TiffBinaryElement.
// -----------------------------------------------------------------------------
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElement_DoesNotThrow_1665) {
  auto elem = MakeBinaryElementOrSkip();
  if (!elem) GTEST_SKIP() << "No accessible TiffBinaryElement constructor matched in this build.";

  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  auto decoder = MakeDecoder(exif, iptc, xmp);

  EXPECT_NO_THROW(decoder.visitBinaryElement(elem.get()));
}

// -----------------------------------------------------------------------------
// Behavioral equivalence: visitBinaryElement forwards to decodeTiffEntry.
// We do not assert *what* gets decoded; only that observable outcomes match
// calling decodeTiffEntry directly from the same initial state.
// -----------------------------------------------------------------------------
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElement_EquivalentToDecodeTiffEntry_1665) {
  auto elem = MakeBinaryElementOrSkip();
  if (!elem) GTEST_SKIP() << "No accessible TiffBinaryElement constructor matched in this build.";

  // Path A: direct decodeTiffEntry
  Exiv2::ExifData exifA;
  Exiv2::IptcData iptcA;
  Exiv2::XmpData xmpA;
  auto decoderA = MakeDecoder(exifA, iptcA, xmpA);

  const auto beforeA = Snapshot(exifA, iptcA, xmpA);
  ASSERT_NO_THROW(decoderA.decodeTiffEntry(elem.get()));
  const auto afterA = Snapshot(exifA, iptcA, xmpA);

  // Path B: via visitBinaryElement
  Exiv2::ExifData exifB;
  Exiv2::IptcData iptcB;
  Exiv2::XmpData xmpB;
  auto decoderB = MakeDecoder(exifB, iptcB, xmpB);

  const auto beforeB = Snapshot(exifB, iptcB, xmpB);
  ASSERT_NO_THROW(decoderB.visitBinaryElement(elem.get()));
  const auto afterB = Snapshot(exifB, iptcB, xmpB);

  // Preconditions: both start empty in our setup.
  EXPECT_EQ(beforeA.exifCount, beforeB.exifCount);
  EXPECT_EQ(beforeA.iptcCount, beforeB.iptcCount);
  EXPECT_EQ(beforeA.xmpCount, beforeB.xmpCount);

  // Postconditions: observable counts match.
  EXPECT_EQ(afterA.exifCount, afterB.exifCount);
  EXPECT_EQ(afterA.iptcCount, afterB.iptcCount);
  EXPECT_EQ(afterA.xmpCount, afterB.xmpCount);
}

// -----------------------------------------------------------------------------
// Boundary conditions: exercise public setters on TiffBinaryElement before
// visiting. We do not assume meaning of specific enum values beyond being valid
// inputs to the public API.
// -----------------------------------------------------------------------------
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElement_WithElByteOrder_InvalidOrChanged_DoesNotThrow_1665) {
  auto elem = MakeBinaryElementOrSkip();
  if (!elem) GTEST_SKIP() << "No accessible TiffBinaryElement constructor matched in this build.";

  // Use the public API of TiffBinaryElement only.
  // invalidByteOrder is referenced in the prompt as a possible value.
  EXPECT_NO_THROW(elem->setElByteOrder(Exiv2::invalidByteOrder));
  EXPECT_EQ(elem->elByteOrder(), Exiv2::invalidByteOrder);

  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;
  auto decoder = MakeDecoder(exif, iptc, xmp);

  EXPECT_NO_THROW(decoder.visitBinaryElement(elem.get()));
}

TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElement_WithElDef_DefaultLike_DoesNotThrow_1665) {
  auto elem = MakeBinaryElementOrSkip();
  if (!elem) GTEST_SKIP() << "No accessible TiffBinaryElement constructor matched in this build.";

  // ArrayDef is part of Exiv2::Internal (from the prompt). We only set something
  // structurally valid; we do not assume semantic meaning.
  Exiv2::Internal::ArrayDef def{};
  EXPECT_NO_THROW(elem->setElDef(def));
  EXPECT_NE(elem->elDef(), nullptr);

  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;
  auto decoder = MakeDecoder(exif, iptc, xmp);

  EXPECT_NO_THROW(decoder.visitBinaryElement(elem.get()));
}

// -----------------------------------------------------------------------------
// Exceptional/error cases (observable): ensure both entry points behave the same
// when passed a null pointer. We do not assume whether it is supported; we only
// assert consistency between visitBinaryElement and decodeTiffEntry.
// If your build treats nullptr as invalid and crashes, enable death tests.
// -----------------------------------------------------------------------------
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElement_Nullptr_BehavesSameAsDecodeTiffEntry_1665) {
  Exiv2::ExifData exifA;
  Exiv2::IptcData iptcA;
  Exiv2::XmpData xmpA;
  auto decoderA = MakeDecoder(exifA, iptcA, xmpA);

  Exiv2::ExifData exifB;
  Exiv2::IptcData iptcB;
  Exiv2::XmpData xmpB;
  auto decoderB = MakeDecoder(exifB, iptcB, xmpB);

#if GTEST_HAS_DEATH_TEST
  // If one of these crashes, the other should crash too (since visitBinaryElement
  // forwards to decodeTiffEntry in the provided implementation).
  EXPECT_DEATH_IF_SUPPORTED({ decoderA.decodeTiffEntry(nullptr); }, ".*");
  EXPECT_DEATH_IF_SUPPORTED({ decoderB.visitBinaryElement(nullptr); }, ".*");
#else
  // If death tests are unavailable, we only verify that, if no crash occurs,
  // the observable metadata counts remain consistent between the two calls.
  const auto beforeA = Snapshot(exifA, iptcA, xmpA);
  const auto beforeB = Snapshot(exifB, iptcB, xmpB);

  // Either both calls do not throw, or one/both may terminate the process in
  // some environments; we avoid asserting stronger behavior here.
  EXPECT_NO_THROW(decoderA.decodeTiffEntry(nullptr));
  EXPECT_NO_THROW(decoderB.visitBinaryElement(nullptr));

  const auto afterA = Snapshot(exifA, iptcA, xmpA);
  const auto afterB = Snapshot(exifB, iptcB, xmpB);

  EXPECT_EQ(beforeA.exifCount, beforeB.exifCount);
  EXPECT_EQ(beforeA.iptcCount, beforeB.iptcCount);
  EXPECT_EQ(beforeA.xmpCount, beforeB.xmpCount);

  EXPECT_EQ(afterA.exifCount, afterB.exifCount);
  EXPECT_EQ(afterA.iptcCount, afterB.iptcCount);
  EXPECT_EQ(afterA.xmpCount, afterB.xmpCount);
#endif
}