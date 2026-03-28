// CMYKGrayEncoder_tests.cpp
// Unit tests for CMYKGrayEncoder (Poppler Stream.h)
// The TEST_ID is 230

#include <gtest/gtest.h>

#include "poppler/Stream.h"
#include "poppler/Object.h"

#include <memory>

class CMYKGrayEncoderTest_230 : public ::testing::Test {
protected:
  static std::unique_ptr<MemStream> MakeMemStream(const char *data, Goffset len) {
    // MemStream takes an rvalue Object dictionary; default-constructed Object is acceptable
    // for tests that don't depend on dictionary contents.
    return std::make_unique<MemStream>(data, /*startA=*/0, /*lengthA=*/len, Object());
  }
};

TEST_F(CMYKGrayEncoderTest_230, GetKindReturnsStrWeird_230) {
  const char kData[] = "abcd";
  auto src = MakeMemStream(kData, static_cast<Goffset>(sizeof(kData) - 1));

  CMYKGrayEncoder enc(src.get());
  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(CMYKGrayEncoderTest_230, GetKindViaBaseStreamPointerReturnsStrWeird_230) {
  const char kData[] = "xyz";
  auto src = MakeMemStream(kData, static_cast<Goffset>(sizeof(kData) - 1));

  // Verify behavior through the public base-type interface.
  std::unique_ptr<Stream> s = std::make_unique<CMYKGrayEncoder>(src.get());
  EXPECT_EQ(s->getKind(), strWeird);
}

TEST_F(CMYKGrayEncoderTest_230, GetKindIsStableAcrossMultipleCalls_230) {
  const char kData[] = "0123456789";
  auto src = MakeMemStream(kData, static_cast<Goffset>(sizeof(kData) - 1));

  CMYKGrayEncoder enc(src.get());

  const StreamKind k1 = enc.getKind();
  const StreamKind k2 = enc.getKind();
  const StreamKind k3 = enc.getKind();

  EXPECT_EQ(k1, strWeird);
  EXPECT_EQ(k2, strWeird);
  EXPECT_EQ(k3, strWeird);
}

TEST_F(CMYKGrayEncoderTest_230, GetKindWorksWithEmptyUnderlyingStream_230) {
  const char kEmpty[] = "";
  auto src = MakeMemStream(kEmpty, /*len=*/0);

  CMYKGrayEncoder enc(src.get());
  EXPECT_EQ(enc.getKind(), strWeird);
}