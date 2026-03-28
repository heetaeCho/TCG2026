// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1193
//
// Unit tests for Exiv2::BmffImage::mimeType() based on observable behavior via public API.
// We treat the implementation as a black box and only drive it through construction +
// (optionally) readMetadata() using in-memory BMFF "ftyp" payloads.

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/bmffimage.hpp>
#include <exiv2/error.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace {

constexpr const char* kGeneric = "image/generic";

uint32_t fourcc(const char a, const char b, const char c, const char d) {
  return (static_cast<uint32_t>(static_cast<unsigned char>(a)) << 24) |
         (static_cast<uint32_t>(static_cast<unsigned char>(b)) << 16) |
         (static_cast<uint32_t>(static_cast<unsigned char>(c)) << 8)  |
         (static_cast<uint32_t>(static_cast<unsigned char>(d)));
}

void appendU32BE(std::vector<Exiv2::byte>& out, uint32_t v) {
  out.push_back(static_cast<Exiv2::byte>((v >> 24) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 16) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>(v & 0xFF));
}

// Build a minimal BMFF "ftyp" box: size(4) + 'ftyp'(4) + major(4) + minor(4) + compat*(4)
std::vector<Exiv2::byte> makeFtypFile(uint32_t majorBrand,
                                      uint32_t minorVersion = 0,
                                      const std::vector<uint32_t>& compatibleBrands = {}) {
  std::vector<Exiv2::byte> data;
  const uint32_t boxType = fourcc('f', 't', 'y', 'p');
  const uint32_t boxSize = static_cast<uint32_t>(8 + 4 + 4 + 4 * compatibleBrands.size());

  appendU32BE(data, boxSize);
  appendU32BE(data, boxType);
  appendU32BE(data, majorBrand);
  appendU32BE(data, minorVersion);
  for (uint32_t c : compatibleBrands) appendU32BE(data, c);

  return data;
}

std::unique_ptr<Exiv2::BasicIo> makeMemIo(const std::vector<Exiv2::byte>& bytes) {
  auto io = std::make_unique<Exiv2::MemIo>();
  if (!bytes.empty()) {
    io->write(bytes.data(), static_cast<long>(bytes.size()));
    io->seek(0, Exiv2::BasicIo::beg);
  }
  return io;
}

}  // namespace

class BmffImageMimeTypeTest_1193 : public ::testing::Test {
 protected:
  static Exiv2::BmffImage makeImageFromBytes(const std::vector<Exiv2::byte>& bytes) {
    // max_box_depth is an external parameter; choose a reasonable non-zero value.
    constexpr size_t kMaxBoxDepth = 16;
    return Exiv2::BmffImage(makeMemIo(bytes), /*create=*/false, kMaxBoxDepth);
  }

  static void readMetadataOrFail(Exiv2::BmffImage& img) {
    try {
      img.readMetadata();
    } catch (const Exiv2::Error& e) {
      FAIL() << "readMetadata() threw Exiv2::Error: " << e.what();
    } catch (const std::exception& e) {
      FAIL() << "readMetadata() threw std::exception: " << e.what();
    } catch (...) {
      FAIL() << "readMetadata() threw unknown exception";
    }
  }
};

TEST_F(BmffImageMimeTypeTest_1193, DefaultWithoutMetadataReturnsGeneric_1193) {
  auto img = makeImageFromBytes({});
  EXPECT_EQ(std::string(kGeneric), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataAvciReturnsImageAvci_1193) {
  auto bytes = makeFtypFile(fourcc('a', 'v', 'c', 'i'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/avci"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataAvcsReturnsImageAvcs_1193) {
  auto bytes = makeFtypFile(fourcc('a', 'v', 'c', 's'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/avcs"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataAvifReturnsImageAvif_1193) {
  auto bytes = makeFtypFile(fourcc('a', 'v', 'i', 'f'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/avif"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataAvioReturnsImageAvif_1193) {
  auto bytes = makeFtypFile(fourcc('a', 'v', 'i', 'o'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/avif"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataAvisReturnsImageAvif_1193) {
  auto bytes = makeFtypFile(fourcc('a', 'v', 'i', 's'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/avif"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataHeicReturnsImageHeic_1193) {
  auto bytes = makeFtypFile(fourcc('h', 'e', 'i', 'c'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/heic"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataHeimReturnsImageHeic_1193) {
  auto bytes = makeFtypFile(fourcc('h', 'e', 'i', 'm'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/heic"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataHeisReturnsImageHeic_1193) {
  auto bytes = makeFtypFile(fourcc('h', 'e', 'i', 's'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/heic"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataHeixReturnsImageHeic_1193) {
  auto bytes = makeFtypFile(fourcc('h', 'e', 'i', 'x'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/heic"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataHeifReturnsImageHeif_1193) {
  auto bytes = makeFtypFile(fourcc('h', 'e', 'i', 'f'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/heif"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataMif1ReturnsImageHeif_1193) {
  auto bytes = makeFtypFile(fourcc('m', 'i', 'f', '1'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/heif"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataJ2isReturnsImageJ2is_1193) {
  auto bytes = makeFtypFile(fourcc('j', '2', 'i', 's'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/j2is"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataJ2kiReturnsImageHej2k_1193) {
  auto bytes = makeFtypFile(fourcc('j', '2', 'k', 'i'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/hej2k"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataCrxReturnsCanonCr3Mime_1193) {
  auto bytes = makeFtypFile(fourcc('c', 'r', 'x', ' '));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/x-canon-cr3"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataJxlReturnsImageJxl_1193) {
  auto bytes = makeFtypFile(fourcc('j', 'x', 'l', ' '));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string("image/jxl"), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, ReadMetadataUnknownBrandReturnsGeneric_1193) {
  auto bytes = makeFtypFile(fourcc('x', 'x', 'x', 'x'));
  auto img = makeImageFromBytes(bytes);

  readMetadataOrFail(img);
  EXPECT_EQ(std::string(kGeneric), img.mimeType());
}

TEST_F(BmffImageMimeTypeTest_1193, MimeTypeDoesNotThrowOnEmptyIo_1193) {
  // Boundary / error-ish case: no bytes. We only assert mimeType is stable and returns a string.
  auto img = makeImageFromBytes({});
  EXPECT_NO_THROW({
    const std::string mt = img.mimeType();
    EXPECT_FALSE(mt.empty());
  });
}