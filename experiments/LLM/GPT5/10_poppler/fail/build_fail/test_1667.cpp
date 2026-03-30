// DeviceNRecoder_tests_1667.cc
#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <optional>
#include <string>

#include "poppler/Stream.h"
#include "poppler/GfxState.h"

// DeviceNRecoder is an internal class in PSOutputDev.cc. Include the .cc to access it.
#include "poppler/PSOutputDev.cc"

namespace {

class DeviceNRecoderTest_1667 : public ::testing::Test {
protected:
  // Create a simple in-memory stream for tests.
  static std::unique_ptr<Stream> MakeMemStream(const std::string &bytes) {
    // Poppler MemStream typically takes ownership of a buffer; allocate a copy.
    auto *buf = new char[bytes.size()];
    if (!bytes.empty()) {
      std::memcpy(buf, bytes.data(), bytes.size());
    }

    Object dict;
    dict.initNull();

    // Common Poppler signature: MemStream(char *bufA, Guint lengthA, Object &&dictA)
    // If your Poppler version uses a slightly different signature, adjust here.
    return std::make_unique<MemStream>(buf, static_cast<Guint>(bytes.size()), std::move(dict));
  }

  // Create a basic RGB image color map for 8bpc images.
  static std::unique_ptr<GfxImageColorMap> MakeRGBColorMap8bpc() {
    // DeviceRGB colorspace.
    std::unique_ptr<GfxColorSpace> cs(GfxDeviceRGBColorSpace::create());

    // Decode is optional in many paths; use null to let implementation decide defaults.
    Object decode;
    decode.initNull();

    // Common Poppler signature: GfxImageColorMap(int bitsA, Object *decode,
    //                                           GfxColorSpace *colorSpaceA,
    //                                           int maxPixelA)
    return std::make_unique<GfxImageColorMap>(8, &decode, cs.release(), 255);
  }
};

TEST_F(DeviceNRecoderTest_1667, LookCharOnEmptyInputReturnsEOF_1667) {
  auto str = MakeMemStream(std::string{});
  auto colorMap = MakeRGBColorMap8bpc();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, colorMap.get());

  // Observable behavior: lookChar returns an int and can return EOF on empty input.
  EXPECT_EQ(recoder.lookChar(), EOF);
}

TEST_F(DeviceNRecoderTest_1667, LookCharDoesNotAdvanceComparedToGetChar_1667) {
  // Provide some bytes; the exact output bytes are an implementation detail, so
  // we only compare lookChar vs getChar for consistency.
  auto str = MakeMemStream(std::string("\x00\x7f\xff", 3));
  auto colorMap = MakeRGBColorMap8bpc();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, colorMap.get());

  const int lc = recoder.lookChar();
  const int gc = recoder.getChar();

  if (lc == EOF) {
    EXPECT_EQ(gc, EOF);
  } else {
    EXPECT_EQ(gc, lc);
  }
}

TEST_F(DeviceNRecoderTest_1667, RewindAllowsReReadingFirstByteWhenPossible_1667) {
  auto str = MakeMemStream(std::string("\x12\x34\x56", 3));
  auto colorMap = MakeRGBColorMap8bpc();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, colorMap.get());

  const int first = recoder.getChar();

  // rewind() is observable; it returns bool.
  const bool rewound = recoder.rewind();
  if (!rewound) {
    GTEST_SKIP() << "DeviceNRecoder::rewind() returned false in this configuration.";
  }

  const int first_again = recoder.getChar();

  if (first == EOF) {
    EXPECT_EQ(first_again, EOF);
  } else {
    EXPECT_EQ(first_again, first);
  }
}

TEST_F(DeviceNRecoderTest_1667, GetKindIsStableAcrossCalls_1667) {
  auto str = MakeMemStream(std::string("\x00", 1));
  auto colorMap = MakeRGBColorMap8bpc();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, colorMap.get());

  const StreamKind k1 = recoder.getKind();
  const StreamKind k2 = recoder.getKind();
  EXPECT_EQ(k1, k2);
}

TEST_F(DeviceNRecoderTest_1667, IsBinaryAcceptsArgumentsAndIsStable_1667) {
  auto str = MakeMemStream(std::string("\x00\x01\x02", 3));
  auto colorMap = MakeRGBColorMap8bpc();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, colorMap.get());

  // Boundary/robustness: both parameter values should be accepted.
  const bool b1 = recoder.isBinary(true);
  const bool b2 = recoder.isBinary(false);

  // Stability: repeated calls with same argument should match.
  EXPECT_EQ(b1, recoder.isBinary(true));
  EXPECT_EQ(b2, recoder.isBinary(false));
}

TEST_F(DeviceNRecoderTest_1667, GetPSFilterReturnsConsistentOptional_1667) {
  auto str = MakeMemStream(std::string("\x00\x01", 2));
  auto colorMap = MakeRGBColorMap8bpc();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, colorMap.get());

  const std::optional<std::string> f1 = recoder.getPSFilter(/*psLevel=*/2, /*indent=*/"  ");
  const std::optional<std::string> f2 = recoder.getPSFilter(/*psLevel=*/2, /*indent=*/"  ");

  ASSERT_EQ(f1.has_value(), f2.has_value());
  if (f1.has_value()) {
    EXPECT_EQ(*f1, *f2);
  }
}

TEST_F(DeviceNRecoderTest_1667, IsEncoderIsStableAcrossCalls_1667) {
  auto str = MakeMemStream(std::string("\xaa\xbb", 2));
  auto colorMap = MakeRGBColorMap8bpc();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, colorMap.get());

  const bool e1 = recoder.isEncoder();
  const bool e2 = recoder.isEncoder();
  EXPECT_EQ(e1, e2);
}

}  // namespace