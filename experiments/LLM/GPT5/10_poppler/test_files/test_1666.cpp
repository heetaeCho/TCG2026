// DeviceNRecoder_test_1666.cc
//
// Unit tests for DeviceNRecoder (PSOutputDev.cc)
// Constraints respected:
// - Treat implementation as black box (no internal logic assumptions)
// - Only use public interface / observable behavior
// - Use bounded reads to avoid hangs
// - TEST_ID suffix added to every test name (1666)

#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <vector>

#include "poppler-config.h"

// DeviceNRecoder is an internal helper implemented in PSOutputDev.cc.
// To test it via its public interface without re-implementing logic,
// we include the translation unit that defines it.
//
// NOTE: This is intentionally done to access the class definition as used
// in the actual codebase.
#include "PSOutputDev.cc"

#include "Stream.h"
#include "Object.h"
#include "Dict.h"
#include "GfxState.h"

// -------------------------
// Small helpers (black-box friendly)
// -------------------------

namespace {

static constexpr int kReadLimit = 4096;

// Create a BaseStream from a memory buffer if MemStream is available in this Poppler build.
// This keeps the tests independent of filesystem and avoids relying on internal state.
std::unique_ptr<Stream> MakeInputStreamFromBytes(const std::vector<unsigned char> &bytes) {
  // Many Poppler versions provide MemStream; if not, this will fail to compile,
  // and the test project should adjust to its local Stream helpers.
  Object dictObj;
  dictObj.initDict(new Dict(nullptr));

  // MemStream historically takes (const char* buf, Guint start, Guint length, Object&& dict)
  // but signatures vary. Try the common forms behind small adapter blocks.
#if defined(__cpp_lib_optional)
  // Prefer rvalue dict if supported by the local Object API.
#endif

  // Common signature: MemStream(const char *bufA, Guint startA, Guint lengthA, Object &&dictA)
  return std::unique_ptr<Stream>(
      new MemStream(reinterpret_cast<const char *>(bytes.data()),
                    /*startA=*/0,
                    /*lengthA=*/static_cast<Guint>(bytes.size()),
                    std::move(dictObj)));
}

// Build a minimal grayscale image color map.
// We do *not* assume how DeviceNRecoder uses it; we only need a valid instance
// to construct the object under test.
std::unique_ptr<GfxImageColorMap> MakeGrayColorMap(int bits = 8) {
  // GfxDeviceGrayColorSpace is commonly available.
  // Constructor signatures for GfxImageColorMap vary; this uses a widely used form:
  //   GfxImageColorMap(int bitsA, const Object *decode, GfxColorSpace *colorSpaceA)
  //
  // If your local Poppler differs, adjust this helper to match the project headers
  // (still black-box compliant).
  auto *cs = GfxDeviceGrayColorSpace::create();

  // Decode array: for Gray, typically [0 1]
  Object decodeObj;
  decodeObj.initArray(nullptr);
  decodeObj.arrayAdd(Object(0.0));
  decodeObj.arrayAdd(Object(1.0));

  return std::unique_ptr<GfxImageColorMap>(new GfxImageColorMap(bits, &decodeObj, cs));
}

// Read up to kReadLimit chars from stream-like object via getChar() until EOF.
template <typename T>
std::vector<int> ReadAllCharsBounded(T &s) {
  std::vector<int> out;
  out.reserve(128);

  for (int i = 0; i < kReadLimit; ++i) {
    int c = s.getChar();
    out.push_back(c);
    if (c == EOF) break;
  }
  return out;
}

// Read first N chars (or until EOF) via getChar().
template <typename T>
std::vector<int> ReadNChars(T &s, int n) {
  std::vector<int> out;
  out.reserve(n);
  for (int i = 0; i < n; ++i) {
    int c = s.getChar();
    out.push_back(c);
    if (c == EOF) break;
  }
  return out;
}

} // namespace

// -------------------------
// Tests
// -------------------------

TEST(DeviceNRecoderTest_1666, ConstructionAndBasicCallsDoNotCrash_1666) {
  // Normal-ish construction with minimal valid collaborators.
  std::vector<unsigned char> bytes = {0x00, 0x7f, 0xff, 0x12};
  auto in = MakeInputStreamFromBytes(bytes);
  auto cmap = MakeGrayColorMap(8);

  ASSERT_NE(in.get(), nullptr);
  ASSERT_NE(cmap.get(), nullptr);

  DeviceNRecoder recoder(in.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());

  // Observable: calls return something / do not crash.
  (void)recoder.getKind();
  (void)recoder.isBinary(true);
  (void)recoder.isBinary(false);
  (void)recoder.isEncoder();
  (void)recoder.lookChar();
  (void)recoder.getPSFilter(/*psLevel*/2, /*indent*/"  ");
}

TEST(DeviceNRecoderTest_1666, LookCharDoesNotAdvanceWhenNotEOF_1666) {
  std::vector<unsigned char> bytes = {0x10, 0x20, 0x30, 0x40};
  auto in = MakeInputStreamFromBytes(bytes);
  auto cmap = MakeGrayColorMap(8);

  DeviceNRecoder recoder(in.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());

  int a = recoder.lookChar();
  int b = recoder.lookChar();
  // Same observable result for repeated lookChar() without consuming.
  EXPECT_EQ(a, b);

  int c = recoder.getChar();
  // If lookChar returned EOF, getChar must also be EOF; otherwise we only require consistency
  // that getChar returns *some* int and doesn't crash.
  if (a == EOF) {
    EXPECT_EQ(c, EOF);
  }
}

TEST(DeviceNRecoderTest_1666, GetCharEventuallyReachesEOF_Bounded_1666) {
  // Boundary-ish: small input, ensure no infinite production.
  std::vector<unsigned char> bytes(16, 0xab);
  auto in = MakeInputStreamFromBytes(bytes);
  auto cmap = MakeGrayColorMap(8);

  DeviceNRecoder recoder(in.get(), /*widthA=*/2, /*heightA=*/2, cmap.get());

  auto out = ReadAllCharsBounded(recoder);

  // Observable: within bound we should reach EOF (or at least stop at bound).
  // We require that the sequence contains EOF within the limit to prove termination.
  bool sawEOF = false;
  for (int v : out) {
    if (v == EOF) {
      sawEOF = true;
      break;
    }
  }
  EXPECT_TRUE(sawEOF);
}

TEST(DeviceNRecoderTest_1666, RewindResetsSequenceIfItSucceeds_1666) {
  std::vector<unsigned char> bytes = {0x01, 0x02, 0x03, 0x04, 0x05};
  auto in = MakeInputStreamFromBytes(bytes);
  auto cmap = MakeGrayColorMap(8);

  DeviceNRecoder recoder(in.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());

  // Read an initial prefix.
  auto first = ReadNChars(recoder, 16);

  // If rewind succeeds, reading again should yield the same prefix (observable behavior).
  bool ok = recoder.rewind();
  if (ok) {
    auto second = ReadNChars(recoder, 16);
    EXPECT_EQ(first, second);
  } else {
    // If rewind is not supported/possible, at least ensure it is a safe call.
    SUCCEED();
  }
}

TEST(DeviceNRecoderTest_1666, ZeroDimensionsBehaveGracefully_1666) {
  // Boundary: width/height zero.
  std::vector<unsigned char> bytes = {0xff, 0xee, 0xdd};
  auto in = MakeInputStreamFromBytes(bytes);
  auto cmap = MakeGrayColorMap(8);

  DeviceNRecoder recoder(in.get(), /*widthA=*/0, /*heightA=*/0, cmap.get());

  // Observable: Should not crash; should terminate quickly.
  auto out = ReadAllCharsBounded(recoder);
  bool sawEOF = false;
  for (int v : out) {
    if (v == EOF) {
      sawEOF = true;
      break;
    }
  }
  EXPECT_TRUE(sawEOF);

  // lookChar at end should be EOF as well (observable error-ish condition).
  EXPECT_EQ(recoder.lookChar(), EOF);
}

TEST(DeviceNRecoderTest_1666, PSFilterOptionalIsStableAcrossCalls_1666) {
  std::vector<unsigned char> bytes = {0x11, 0x22};
  auto in = MakeInputStreamFromBytes(bytes);
  auto cmap = MakeGrayColorMap(8);

  DeviceNRecoder recoder(in.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());

  std::optional<std::string> a = recoder.getPSFilter(/*psLevel*/2, /*indent*/"");
  std::optional<std::string> b = recoder.getPSFilter(/*psLevel*/2, /*indent*/"");

  EXPECT_EQ(a.has_value(), b.has_value());
  if (a.has_value() && b.has_value()) {
    EXPECT_EQ(*a, *b);
  }
}

TEST(DeviceNRecoderTest_1666, IsBinaryAndIsEncoderAreCallableAndConsistent_1666) {
  std::vector<unsigned char> bytes = {0x00};
  auto in = MakeInputStreamFromBytes(bytes);
  auto cmap = MakeGrayColorMap(8);

  DeviceNRecoder recoder(in.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());

  // No assumption about true/false, only that repeated calls are consistent.
  bool b1 = recoder.isBinary(true);
  bool b2 = recoder.isBinary(true);
  EXPECT_EQ(b1, b2);

  bool e1 = recoder.isEncoder();
  bool e2 = recoder.isEncoder();
  EXPECT_EQ(e1, e2);
}