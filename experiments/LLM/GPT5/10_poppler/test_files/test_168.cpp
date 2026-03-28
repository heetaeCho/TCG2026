// SPDX-License-Identifier: GPL-2.0-or-later
// File: BaseMemStream_getChar_tests_168.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#include "./TestProjects/poppler/poppler/Stream.h"
#include "./TestProjects/poppler/poppler/Object.h"

namespace {

Object MakeNullDict() {
  Object obj;
  // Poppler commonly provides initNull() for Object.
  obj.initNull();
  return obj;
}

template <typename T>
std::unique_ptr<BaseMemStream<T>> MakeBaseMemStream(T* buf, Goffset start, Goffset length) {
  Object dict = MakeNullDict();
  return std::make_unique<BaseMemStream<T>>(buf, start, length, std::move(dict));
}

class BaseMemStreamGetCharTest_168 : public ::testing::Test {};

}  // namespace

TEST_F(BaseMemStreamGetCharTest_168, ReadsSequentialBytesAndThenEOF_168) {
  unsigned char data[] = {0x01, 0x7F, 0x80, 0xFF};
  auto s = MakeBaseMemStream<unsigned char>(data, /*start=*/0, /*length=*/4);

  EXPECT_EQ(s->getChar(), 0x01);
  EXPECT_EQ(s->getChar(), 0x7F);
  EXPECT_EQ(s->getChar(), 0x80);
  EXPECT_EQ(s->getChar(), 0xFF);

  // Past end -> EOF (and stays EOF on subsequent reads).
  EXPECT_EQ(s->getChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(BaseMemStreamGetCharTest_168, EmptyStreamReturnsEOFImmediately_168) {
  unsigned char data[] = {0xAA, 0xBB};
  auto s = MakeBaseMemStream<unsigned char>(data, /*start=*/0, /*length=*/0);

  EXPECT_EQ(s->getChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(BaseMemStreamGetCharTest_168, RespectsProvidedLengthNotUnderlyingBufferSize_168) {
  unsigned char data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
  // Only expose first 2 bytes via length.
  auto s = MakeBaseMemStream<unsigned char>(data, /*start=*/0, /*length=*/2);

  EXPECT_EQ(s->getChar(), 0x10);
  EXPECT_EQ(s->getChar(), 0x20);
  EXPECT_EQ(s->getChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(BaseMemStreamGetCharTest_168, ReturnsUnsignedByteValuesIn0To255Range_168) {
  // Use signed char buffer to ensure conversion behavior is observable.
  signed char data[] = {
      static_cast<signed char>(0x00),
      static_cast<signed char>(0x7F),
      static_cast<signed char>(0x80),  // typically negative if char is signed
      static_cast<signed char>(0xFF)   // typically -1 if char is signed
  };

  auto s = MakeBaseMemStream<signed char>(data, /*start=*/0, /*length=*/4);

  // Observable contract: return value should be an int representing a byte, not sign-extended.
  EXPECT_EQ(s->getChar(), 0x00);
  EXPECT_EQ(s->getChar(), 0x7F);
  EXPECT_EQ(s->getChar(), 0x80);
  EXPECT_EQ(s->getChar(), 0xFF);
  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(BaseMemStreamGetCharTest_168, DoesNotSkipBytesAcrossMultipleCalls_168) {
  unsigned char data[] = {0x11, 0x22, 0x33};
  auto s = MakeBaseMemStream<unsigned char>(data, /*start=*/0, /*length=*/3);

  int c1 = s->getChar();
  int c2 = s->getChar();
  int c3 = s->getChar();

  EXPECT_EQ(c1, 0x11);
  EXPECT_EQ(c2, 0x22);
  EXPECT_EQ(c3, 0x33);
  EXPECT_EQ(s->getChar(), EOF);
}