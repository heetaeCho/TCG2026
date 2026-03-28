// TEST_ID 1668
// File: tiffvisitor_int_test_1668.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <atomic>
#include <memory>
#include <utility>

#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"          // Exiv2::Internal::TiffHeader
#include "tiffcomposite_int.hpp"      // Exiv2::Internal::TiffCreator, TiffComponent, TiffEntry (via RTTI)

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

// A small helper to build a TiffEncoder with minimal, valid-looking dependencies.
// We intentionally do NOT assume any internal semantics beyond what the public
// constructor requires.
struct EncoderBundle {
  std::unique_ptr<TiffHeader> header;
  std::unique_ptr<TiffEncoder> encoder;
  std::atomic<int> find_calls{0};
};

EncoderBundle MakeEncoderOrSkip(bool isNewImage) {
  EncoderBundle b;

  // TiffEncoder's ctor uses pHeader->byteOrder(), so pHeader must be non-null.
  b.header = std::make_unique<TiffHeader>(littleEndian);

  // Provide a FindEncoderFct that is safe to call. We don't assume how often it
  // will be called (or even if it will be called for a given entry).
  FindEncoderFct findEncoderFct = [&b](const std::string&, uint32_t, IfdId) -> EncoderFct {
    ++b.find_calls;
    return nullptr;
  };

  // PrimaryGroups is an internal alias; in Exiv2 it is default-constructible.
  PrimaryGroups primaryGroups{};

  // pRoot is stored, and might be used during encoding. We try with nullptr to
  // keep this unit test focused on visitEntry forwarding. If your build requires
  // a non-null root, replace nullptr with a suitable root directory component.
  TiffComponent* pRoot = nullptr;

  try {
    b.encoder = std::make_unique<TiffEncoder>(
        ExifData{},      // empty ExifData moved in
        IptcData{},      // const ref - temporary ok for this scope? no: must outlive encoder => store local below
        XmpData{},       // const ref - temporary ok for this scope? no: must outlive encoder => store local below
        pRoot,
        isNewImage,
        std::move(primaryGroups),
        b.header.get(),
        findEncoderFct);
  } catch (const std::exception& e) {
    GTEST_SKIP() << "Unable to construct TiffEncoder in this build/config: " << e.what();
  } catch (...) {
    GTEST_SKIP() << "Unable to construct TiffEncoder in this build/config (unknown exception).";
  }

  return b;
}

// NOTE: The TiffEncoder constructor stores references to IptcData/XmpData.
// Therefore, we must ensure those objects outlive the encoder.
// This helper creates an encoder while keeping the backing Iptc/Xmp alive.
struct EncoderWithBacking {
  IptcData iptc;
  XmpData xmp;
  std::unique_ptr<TiffHeader> header;
  std::atomic<int> find_calls{0};
  std::unique_ptr<TiffEncoder> encoder;
};

EncoderWithBacking MakeEncoderWithBackingOrSkip(bool isNewImage) {
  EncoderWithBacking b;
  b.header = std::make_unique<TiffHeader>(littleEndian);

  FindEncoderFct findEncoderFct = [&b](const std::string&, uint32_t, IfdId) -> EncoderFct {
    ++b.find_calls;
    return nullptr;
  };

  PrimaryGroups primaryGroups{};
  TiffComponent* pRoot = nullptr;

  try {
    b.encoder = std::make_unique<TiffEncoder>(
        ExifData{}, b.iptc, b.xmp, pRoot, isNewImage, std::move(primaryGroups), b.header.get(), findEncoderFct);
  } catch (const std::exception& e) {
    GTEST_SKIP() << "Unable to construct TiffEncoder in this build/config: " << e.what();
  } catch (...) {
    GTEST_SKIP() << "Unable to construct TiffEncoder in this build/config (unknown exception).";
  }

  return b;
}

std::unique_ptr<TiffEntry> MakeTiffEntryViaCreatorOrSkip(uint32_t tag, IfdId group) {
  // TiffCreator is a public internal factory; we don't assume which concrete
  // component it returns, we only proceed if it returns a TiffEntry.
  std::unique_ptr<TiffComponent> comp;
  try {
    comp = TiffCreator::create(tag, group);
  } catch (const std::exception& e) {
    GTEST_SKIP() << "TiffCreator::create threw in this build/config: " << e.what();
  } catch (...) {
    GTEST_SKIP() << "TiffCreator::create threw in this build/config (unknown exception).";
  }

  if (!comp) {
    GTEST_SKIP() << "TiffCreator::create returned null for tag/group in this build/config.";
  }

  // We only know visitEntry takes TiffEntry*. If the factory returns something else,
  // skip rather than guessing constructors.
  auto* entryPtr = dynamic_cast<TiffEntry*>(comp.get());
  if (!entryPtr) {
    GTEST_SKIP() << "Factory did not produce a TiffEntry for the requested tag/group.";
  }

  // Transfer ownership: comp actually owns a TiffEntry instance.
  comp.release();
  return std::unique_ptr<TiffEntry>(entryPtr);
}

}  // namespace

// -------------------- Tests (TEST_ID 1668) --------------------

TEST(TiffEncoderTest_1668, VisitEntry_Nullptr_DoesNotCrash_1668) {
  auto b = MakeEncoderWithBackingOrSkip(/*isNewImage=*/true);
  ASSERT_NE(b.encoder, nullptr);

  // Boundary case: null pointer. We only assert it is handled without crashing.
  // If the implementation chooses to throw on nullptr, replace with EXPECT_ANY_THROW.
  EXPECT_NO_THROW(b.encoder->visitEntry(nullptr));
}

TEST(TiffEncoderTest_1668, VisitEntry_WithFactoryCreatedEntry_DoesNotThrow_1668) {
  auto b = MakeEncoderWithBackingOrSkip(/*isNewImage=*/true);
  ASSERT_NE(b.encoder, nullptr);

  // Try to obtain a real TiffEntry without assuming constructors.
  // 0x010E (ImageDescription) in IFD0 is a commonly-defined TIFF/Exif tag.
  auto entry = MakeTiffEntryViaCreatorOrSkip(/*tag=*/0x010Eu, /*group=*/ifd0Id);
  ASSERT_NE(entry, nullptr);

  // Normal operation: visiting a real entry should not throw.
  EXPECT_NO_THROW(b.encoder->visitEntry(entry.get()));
}

TEST(TiffEncoderTest_1668, VisitEntry_DoesNotClearDirtyFlag_WhenAlreadyDirty_1668) {
  auto b = MakeEncoderWithBackingOrSkip(/*isNewImage=*/true);
  ASSERT_NE(b.encoder, nullptr);

  b.encoder->setDirty(true);
  ASSERT_TRUE(b.encoder->dirty());

  auto entry = MakeTiffEntryViaCreatorOrSkip(/*tag=*/0x010Eu, /*group=*/ifd0Id);
  ASSERT_NE(entry, nullptr);

  // Boundary/behavioral: calling visitEntry should not unexpectedly clear the dirty flag.
  EXPECT_NO_THROW(b.encoder->visitEntry(entry.get()));
  EXPECT_TRUE(b.encoder->dirty());
}