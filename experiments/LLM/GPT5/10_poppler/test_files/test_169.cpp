// TEST_ID: 169
// File: base_mem_stream_lookchar_test_169.cpp

#include <gtest/gtest.h>

#include <cstdio>   // EOF
#include <cstdint>
#include <memory>

#include "poppler/Stream.h"
#include "poppler/Object.h"

namespace {

// Focused fixture for BaseMemStream::lookChar() behavior.
class BaseMemStreamLookCharTest_169 : public ::testing::Test {};

// Helper to create a minimal dict object (null is typically acceptable for BaseStream).
static Object MakeNullDict_169() {
  return Object(); // null object
}

} // namespace

TEST_F(BaseMemStreamLookCharTest_169, ReturnsFirstByteWhenNotAtEnd_169) {
  unsigned char buf[] = {0x01, 0x7F, 0x80, 0xFF};

  BaseMemStream<unsigned char> s(buf, /*startA=*/0, /*lengthA=*/static_cast<Goffset>(sizeof(buf)),
                                 MakeNullDict_169());

  const int c = s.lookChar();
  EXPECT_EQ(0x01, c);

  // lookChar should not advance the stream position (observable via getPos()).
  EXPECT_EQ(0, s.getPos());
}

TEST_F(BaseMemStreamLookCharTest_169, LookCharDoesNotAdvanceAndMatchesGetChar_169) {
  unsigned char buf[] = {0x11, 0x22, 0x33};

  BaseMemStream<unsigned char> s(buf, /*startA=*/0, /*lengthA=*/static_cast<Goffset>(sizeof(buf)),
                                 MakeNullDict_169());

  const int a1 = s.lookChar();
  const int a2 = s.lookChar();
  EXPECT_EQ(a1, a2);
  EXPECT_EQ(0, s.getPos());

  const int g1 = s.getChar();
  EXPECT_EQ(a1, g1);
  EXPECT_EQ(1, s.getPos());

  const int b1 = s.lookChar();
  EXPECT_EQ(0x22, b1);
  EXPECT_EQ(1, s.getPos());
}

TEST_F(BaseMemStreamLookCharTest_169, ReturnsEOFForEmptyStream_169) {
  unsigned char buf[] = {};

  BaseMemStream<unsigned char> s(buf, /*startA=*/0, /*lengthA=*/0, MakeNullDict_169());

  EXPECT_EQ(EOF, s.lookChar());
  EXPECT_EQ(0, s.getPos());
}

TEST_F(BaseMemStreamLookCharTest_169, ReturnsEOFAtEndAfterConsumingAllBytes_169) {
  unsigned char buf[] = {0xAA};

  BaseMemStream<unsigned char> s(buf, /*startA=*/0, /*lengthA=*/static_cast<Goffset>(sizeof(buf)),
                                 MakeNullDict_169());

  EXPECT_EQ(0xAA, s.lookChar());
  EXPECT_EQ(0xAA, s.getChar());
  EXPECT_EQ(1, s.getPos());

  EXPECT_EQ(EOF, s.lookChar());
  // Position should remain at end.
  EXPECT_EQ(1, s.getPos());
}

TEST_F(BaseMemStreamLookCharTest_169, ReturnsEOFWhenPositionSetToEnd_169) {
  unsigned char buf[] = {0x10, 0x20};

  BaseMemStream<unsigned char> s(buf, /*startA=*/0, /*lengthA=*/static_cast<Goffset>(sizeof(buf)),
                                 MakeNullDict_169());

  s.setPos(static_cast<Goffset>(sizeof(buf)), /*dir=*/0);
  EXPECT_EQ(static_cast<Goffset>(sizeof(buf)), s.getPos());
  EXPECT_EQ(EOF, s.lookChar());
}

TEST_F(BaseMemStreamLookCharTest_169, MasksSignedCharTo0To255Range_169) {
  // Use char buffer so that 0xFF may be stored as -1 on platforms with signed char.
  char buf[] = {static_cast<char>(0xFF), static_cast<char>(0x80), static_cast<char>(0x7F)};

  BaseMemStream<char> s(buf, /*startA=*/0, /*lengthA=*/static_cast<Goffset>(sizeof(buf)),
                        MakeNullDict_169());

  // Observable requirement from the provided implementation: (*bufPtr & 0xff)
  EXPECT_EQ(255, s.lookChar());

  // Ensure it remains consistent with getChar() and does not advance on lookChar.
  EXPECT_EQ(0, s.getPos());
  EXPECT_EQ(255, s.getChar());
  EXPECT_EQ(1, s.getPos());

  EXPECT_EQ(128, s.lookChar());
  EXPECT_EQ(1, s.getPos());
}

TEST_F(BaseMemStreamLookCharTest_169, RewindRestoresLookCharToFirstByte_169) {
  unsigned char buf[] = {0x01, 0x02, 0x03};

  BaseMemStream<unsigned char> s(buf, /*startA=*/0, /*lengthA=*/static_cast<Goffset>(sizeof(buf)),
                                 MakeNullDict_169());

  EXPECT_EQ(0x01, s.getChar());
  EXPECT_EQ(1, s.getPos());
  EXPECT_EQ(0x02, s.lookChar());

  const bool rewound = s.rewind();
  // Only assert observable outcome: if rewind reports success, lookChar should show the first byte.
  if (rewound) {
    EXPECT_EQ(0, s.getPos());
    EXPECT_EQ(0x01, s.lookChar());
  }
}