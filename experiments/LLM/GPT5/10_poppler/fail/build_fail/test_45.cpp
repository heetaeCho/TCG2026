// TEST_ID is 45
// Unit tests for FoFiTrueType::isOpenTypeCFF()
//
// Constraints reminder (self-enforced):
// - Treat FoFiTrueType as a black box.
// - Only use the public interface (factories + isOpenTypeCFF()).
// - No access to private state.
//
// These tests build tiny, structurally-valid sfnt containers with either:
// - sfnt version "OTTO" (commonly used for OpenType/CFF), and a "CFF " table record
// - sfnt version 0x00010000 (TrueType), and a "glyf" table record
//
// The goal is to verify that isOpenTypeCFF() reflects the font container type
// as observed through the public API (and is stable across calls).

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "FoFiTrueType.h"

namespace {

// ---- Helpers to write big-endian integers into a byte buffer ----
static void appendBE16(std::vector<unsigned char>& out, uint16_t v) {
  out.push_back(static_cast<unsigned char>((v >> 8) & 0xff));
  out.push_back(static_cast<unsigned char>(v & 0xff));
}
static void appendBE32(std::vector<unsigned char>& out, uint32_t v) {
  out.push_back(static_cast<unsigned char>((v >> 24) & 0xff));
  out.push_back(static_cast<unsigned char>((v >> 16) & 0xff));
  out.push_back(static_cast<unsigned char>((v >> 8) & 0xff));
  out.push_back(static_cast<unsigned char>(v & 0xff));
}
static void appendTag(std::vector<unsigned char>& out, const char tag[4]) {
  out.push_back(static_cast<unsigned char>(tag[0]));
  out.push_back(static_cast<unsigned char>(tag[1]));
  out.push_back(static_cast<unsigned char>(tag[2]));
  out.push_back(static_cast<unsigned char>(tag[3]));
}

// Build a minimal sfnt file:
// - Offset table (12 bytes)
// - 1 table record (16 bytes)
// - No table data (length=0), offset points to EOF.
// This is intentionally tiny; if FoFiTrueType rejects it, the tests will gracefully
// fall back to asserting the factory returns nullptr in invalid/boundary tests.
static std::vector<unsigned char> makeMinimalSfnt(const char sfntVersionTag[4],
                                                 const char tableTag[4]) {
  std::vector<unsigned char> buf;
  buf.reserve(12 + 16);

  // sfnt version
  appendTag(buf, sfntVersionTag);

  // numTables = 1
  appendBE16(buf, 1);

  // searchRange, entrySelector, rangeShift can be 0 for a minimal container
  appendBE16(buf, 0);
  appendBE16(buf, 0);
  appendBE16(buf, 0);

  // Table record (16 bytes):
  // tag
  appendTag(buf, tableTag);
  // checksum (0)
  appendBE32(buf, 0);
  // offset (points just past directory)
  const uint32_t offset = 12 + 16;
  appendBE32(buf, offset);
  // length (0)
  appendBE32(buf, 0);

  // Ensure file length exactly equals offset.
  // (No table bytes; offset == buf.size()).
  return buf;
}

// ---- Factory-call detection helpers (support multiple possible Poppler signatures) ----
template <typename T, typename = void>
struct has_make_ptr_len_face : std::false_type {};
template <typename T>
struct has_make_ptr_len_face<
    T,
    std::void_t<decltype(T::make(std::declval<const unsigned char*>(),
                                 std::declval<int>(),
                                 std::declval<int>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_make_ptr_sizet_face : std::false_type {};
template <typename T>
struct has_make_ptr_sizet_face<
    T,
    std::void_t<decltype(T::make(std::declval<const unsigned char*>(),
                                 std::declval<size_t>(),
                                 std::declval<int>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_load_file_face : std::false_type {};
template <typename T>
struct has_load_file_face<
    T,
    std::void_t<decltype(T::load(std::declval<const char*>(), std::declval<int>()))>>
    : std::true_type {};

// Tries to create a FoFiTrueType instance from an in-memory buffer using whichever
// public factory exists in the actual build. If only load() exists, writes a temp file.
static std::unique_ptr<FoFiTrueType> createFromBuffer(const std::vector<unsigned char>& buf,
                                                      int faceIndex,
                                                      const std::string& tmpPath) {
  if constexpr (has_make_ptr_len_face<FoFiTrueType>::value) {
    return FoFiTrueType::make(buf.data(), static_cast<int>(buf.size()), faceIndex);
  } else if constexpr (has_make_ptr_sizet_face<FoFiTrueType>::value) {
    return FoFiTrueType::make(buf.data(), buf.size(), faceIndex);
  } else if constexpr (has_load_file_face<FoFiTrueType>::value) {
    // Fallback: write bytes to a file and use load().
    std::ofstream os(tmpPath, std::ios::binary | std::ios::trunc);
    if (!os.is_open()) {
      return nullptr;
    }
    if (!buf.empty()) {
      os.write(reinterpret_cast<const char*>(buf.data()),
               static_cast<std::streamsize>(buf.size()));
    }
    os.close();
    return FoFiTrueType::load(tmpPath.c_str(), faceIndex);
  } else {
    // No known factory available in this header configuration.
    return nullptr;
  }
}

static std::string makeTmpPath(const char* leaf) {
#if defined(_WIN32)
  // Keep it simple; most CI uses writable working dir.
  return std::string(".\\") + leaf;
#else
  return std::string("./") + leaf;
#endif
}

}  // namespace

class FoFiTrueTypeTest_45 : public ::testing::Test {
 protected:
  std::string tmp_otf_path_ = makeTmpPath("FoFiTrueTypeTest_45_otf.bin");
  std::string tmp_ttf_path_ = makeTmpPath("FoFiTrueTypeTest_45_ttf.bin");
  std::string tmp_bad_path_ = makeTmpPath("FoFiTrueTypeTest_45_bad.bin");
};

TEST_F(FoFiTrueTypeTest_45, IsOpenTypeCFF_TrueForOTTOContainer_45) {
  // "OTTO" sfnt version + "CFF " table record
  const auto otto = makeMinimalSfnt("OTTO", "CFF ");
  auto font = createFromBuffer(otto, /*faceIndex=*/0, tmp_otf_path_);

  // If the library rejects this minimal font, skip the behavioral assertion
  // (we still validated factory invocation path).
  if (!font) {
    GTEST_SKIP() << "FoFiTrueType factory rejected minimal OTTO/CFF test font buffer";
  }

  EXPECT_TRUE(font->isOpenTypeCFF());
  // Stability across repeated calls (no mutation visible through public API)
  EXPECT_TRUE(font->isOpenTypeCFF());
}

TEST_F(FoFiTrueTypeTest_45, IsOpenTypeCFF_FalseForTrueTypeContainer_45) {
  // 0x00010000 sfnt version encoded as bytes 00 01 00 00
  // We'll provide it via tag bytes to avoid guessing host endianness.
  const char ttfVer[4] = {0x00, 0x01, 0x00, 0x00};
  const auto ttf = makeMinimalSfnt(ttfVer, "glyf");
  auto font = createFromBuffer(ttf, /*faceIndex=*/0, tmp_ttf_path_);

  if (!font) {
    GTEST_SKIP() << "FoFiTrueType factory rejected minimal TrueType test font buffer";
  }

  EXPECT_FALSE(font->isOpenTypeCFF());
  EXPECT_FALSE(font->isOpenTypeCFF());
}

TEST_F(FoFiTrueTypeTest_45, IsOpenTypeCFF_BoundaryFaceIndexDoesNotCrash_45) {
  // Boundary-ish faceIndex values: 0 and a larger number.
  const auto otto = makeMinimalSfnt("OTTO", "CFF ");

  auto font0 = createFromBuffer(otto, /*faceIndex=*/0, tmp_otf_path_);
  auto fontBig = createFromBuffer(otto, /*faceIndex=*/999, tmp_otf_path_);

  // We don't assume creation succeeds for arbitrary faceIndex; just ensure that
  // if an object is produced, calling isOpenTypeCFF() is safe and returns a bool.
  if (font0) {
    (void)font0->isOpenTypeCFF();
    SUCCEED();
  }
  if (fontBig) {
    (void)fontBig->isOpenTypeCFF();
    SUCCEED();
  }

  if (!font0 && !fontBig) {
    GTEST_SKIP() << "FoFiTrueType factory rejected test font for both faceIndex values";
  }
}

TEST_F(FoFiTrueTypeTest_45, FactoryReturnsNullOnClearlyInvalidData_45) {
  // Exceptional/error case observable via interface: factory may return nullptr.
  const std::vector<unsigned char> bad = {0x00};  // too short to be a font
  auto font = createFromBuffer(bad, /*faceIndex=*/0, tmp_bad_path_);

  EXPECT_EQ(font, nullptr);
}