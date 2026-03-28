// =================================================================================================
// TEST_ID: 1672
// Unit tests for Exiv2::Internal::TiffEncoder::visitDirectoryNext(TiffDirectory*)
// File: ./TestProjects/exiv2/src/tiffvisitor_int.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

// Exiv2 internals under test
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

// Public Exiv2 containers used by TiffEncoder ctor
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp.hpp>

namespace {

using Exiv2::ByteOrder;
using Exiv2::ExifData;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::FindEncoderFct;
using Exiv2::Internal::IfdId;
using Exiv2::Internal::PrimaryGroups;
using Exiv2::Internal::TiffComponent;
using Exiv2::Internal::TiffDirectory;
using Exiv2::Internal::TiffEncoder;
using Exiv2::Internal::TiffHeaderBase;

// Helper: create a TiffEncoder with minimal dependencies.
// NOTE: This relies only on the constructor signature shown in the prompt.
// If the production code provides a different concrete header type, adjust here.
struct EncoderDeps_1672 {
  ExifData exif;
  IptcData iptc;
  XmpData xmp;
  PrimaryGroups primaryGroups{};
  FindEncoderFct findEncoderFct{nullptr};

  // We store a header object (or pointer to one) that can be passed to TiffEncoder.
  // Assumption: TiffHeaderBase is constructible with a ByteOrder or default-constructible.
  // This is a compile-time dependency, not a behavioral inference.
  std::unique_ptr<TiffHeaderBase> header;
};

// Try the most common construction patterns without guessing runtime behavior.
static std::unique_ptr<TiffHeaderBase> makeHeader_1672(ByteOrder bo) {
  // Prefer a (ByteOrder) constructor if available; otherwise default-construct then rely on it
  // already having a valid byte order for tests that only check "no crash / buffer mutation".
#if __cplusplus >= 201703L
  if constexpr (std::is_constructible<TiffHeaderBase, ByteOrder>::value) {
    return std::make_unique<TiffHeaderBase>(bo);
  } else if constexpr (std::is_default_constructible<TiffHeaderBase>::value) {
    auto h = std::make_unique<TiffHeaderBase>();
    (void)bo;
    return h;
  } else {
    // If neither is available in a particular build configuration, tests depending on encoder
    // construction cannot run.
    return nullptr;
  }
#else
  // C++11/14 fallback: attempt ByteOrder ctor first by direct compilation; if it fails, adapt.
  // (Most Exiv2 builds for this project use at least C++17.)
  return std::unique_ptr<TiffHeaderBase>(new TiffHeaderBase(bo));
#endif
}

static std::unique_ptr<TiffEncoder> makeEncoder_1672(TiffComponent* root,
                                                     bool isNewImage,
                                                     ByteOrder bo) {
  auto deps = std::make_unique<EncoderDeps_1672>();
  deps->header = makeHeader_1672(bo);
  if (!deps->header) return nullptr;

  // Keep deps alive by leaking into a static store owned for the lifetime of the test process.
  // This avoids storing references in the encoder to temporaries.
  static std::vector<std::unique_ptr<EncoderDeps_1672>> s_deps;
  s_deps.emplace_back(std::move(deps));
  EncoderDeps_1672* d = s_deps.back().get();

  return std::make_unique<TiffEncoder>(std::move(d->exif),
                                       d->iptc,
                                       d->xmp,
                                       root,
                                       isNewImage,
                                       d->primaryGroups,
                                       d->header.get(),
                                       d->findEncoderFct);
}

static std::vector<Exiv2::byte> makePatternBuffer_1672(size_t n, Exiv2::byte seed) {
  std::vector<Exiv2::byte> buf(n);
  for (size_t i = 0; i < n; ++i) {
    buf[i] = static_cast<Exiv2::byte>(seed + static_cast<Exiv2::byte>(i));
  }
  return buf;
}

static bool anyByteDiffAfterOffset_1672(const std::vector<Exiv2::byte>& a,
                                        const std::vector<Exiv2::byte>& b,
                                        size_t offset) {
  if (a.size() != b.size() || offset > a.size()) return false;
  for (size_t i = offset; i < a.size(); ++i) {
    if (a[i] != b[i]) return true;
  }
  return false;
}

class TiffEncoderVisitDirectoryNextTest_1672 : public ::testing::Test {
protected:
  // Use a commonly valid IFD group. IfdId is an enum in Exiv2 internals; "ifd0Id" is typically present.
  // If your build uses a different name, adjust accordingly.
  static constexpr IfdId kGroup =
#ifdef ifd0Id
      ifd0Id;
#else
      static_cast<IfdId>(0);
#endif

  // Arbitrary tag value for constructing directories.
  static constexpr uint16_t kTag = 0x1234;
};

}  // namespace

TEST_F(TiffEncoderVisitDirectoryNextTest_1672, EmptyDirectory_DoesNotModifyBufferBeyondHeader_1672) {
  TiffDirectory dir(kTag, kGroup, /*hasNext=*/false);

  // Provide a start buffer and set it on the directory.
  auto buf = makePatternBuffer_1672(/*n=*/64, /*seed=*/0x10);
  const auto before = buf;

  dir.setStart(buf.data());

  auto enc = makeEncoder_1672(&dir, /*isNewImage=*/false, Exiv2::littleEndian);
  ASSERT_NE(enc, nullptr) << "Failed to construct TiffEncoder in this build configuration.";

  // With no children/components, observable behavior should be "no crash".
  // Additionally, per the implementation, the method begins writing at start()+2,
  // so the first two bytes should never be modified by this call.
  EXPECT_NO_THROW(enc->visitDirectoryNext(&dir));

  EXPECT_EQ(buf[0], before[0]);
  EXPECT_EQ(buf[1], before[1]);

  // For an empty directory, the loop body should not run; we expect no modifications at all.
  EXPECT_EQ(buf, before);
}

TEST_F(TiffEncoderVisitDirectoryNextTest_1672, SingleChild_ModifiesSomeByteAfterFirstTwo_1672) {
  TiffDirectory dir(kTag, kGroup, /*hasNext=*/false);

  auto buf = makePatternBuffer_1672(/*n=*/128, /*seed=*/0x40);
  const auto before = buf;
  dir.setStart(buf.data());

  // Add one child component to make the directory non-empty.
  auto child = std::make_shared<TiffDirectory>(static_cast<uint16_t>(kTag + 1), kGroup, /*hasNext=*/false);
  ASSERT_NE(dir.addChild(child), nullptr);

  auto enc = makeEncoder_1672(&dir, /*isNewImage=*/false, Exiv2::littleEndian);
  ASSERT_NE(enc, nullptr) << "Failed to construct TiffEncoder in this build configuration.";

  EXPECT_NO_THROW(enc->visitDirectoryNext(&dir));

  // Must not touch the first two bytes (write cursor starts at +2).
  EXPECT_EQ(buf[0], before[0]);
  EXPECT_EQ(buf[1], before[1]);

  // With at least one component, we expect some observable mutation after offset 2.
  // (We do not assert exact content to avoid inferring internal encoding details.)
  EXPECT_TRUE(anyByteDiffAfterOffset_1672(buf, before, /*offset=*/2));
}

TEST_F(TiffEncoderVisitDirectoryNextTest_1672, MultipleChildren_ModifiesBufferAfterFirstTwo_1672) {
  TiffDirectory dir(kTag, kGroup, /*hasNext=*/false);

  auto buf = makePatternBuffer_1672(/*n=*/256, /*seed=*/0x80);
  const auto before = buf;
  dir.setStart(buf.data());

  // Add multiple children to increase coverage for iteration.
  for (int i = 0; i < 5; ++i) {
    auto child = std::make_shared<TiffDirectory>(static_cast<uint16_t>(kTag + 1 + i), kGroup, /*hasNext=*/false);
    ASSERT_NE(dir.addChild(child), nullptr);
  }

  auto enc = makeEncoder_1672(&dir, /*isNewImage=*/true, Exiv2::bigEndian);
  ASSERT_NE(enc, nullptr) << "Failed to construct TiffEncoder in this build configuration.";

  EXPECT_NO_THROW(enc->visitDirectoryNext(&dir));

  EXPECT_EQ(buf[0], before[0]);
  EXPECT_EQ(buf[1], before[1]);
  EXPECT_TRUE(anyByteDiffAfterOffset_1672(buf, before, /*offset=*/2));
}

TEST_F(TiffEncoderVisitDirectoryNextTest_1672, SmallBuffer_SizeTwo_EmptyDirectory_NoCrash_1672) {
  TiffDirectory dir(kTag, kGroup, /*hasNext=*/false);

  // Boundary: buffer exactly 2 bytes. Method sets pointer to start()+2 and should not dereference it
  // if there are no components to write.
  std::vector<Exiv2::byte> buf = {static_cast<Exiv2::byte>(0xAA), static_cast<Exiv2::byte>(0xBB)};
  const auto before = buf;
  dir.setStart(buf.data());

  auto enc = makeEncoder_1672(&dir, /*isNewImage=*/false, Exiv2::littleEndian);
  ASSERT_NE(enc, nullptr) << "Failed to construct TiffEncoder in this build configuration.";

  EXPECT_NO_THROW(enc->visitDirectoryNext(&dir));
  EXPECT_EQ(buf, before);
}