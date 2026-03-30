// BaseMemStream_test_2754.cpp
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <memory>
#include <utility>

#include "Stream.h"
#include "Object.h"

namespace {

// Keep the fixture minimal: we treat BaseMemStream as a black box and only
// verify observable behavior through the public Stream/BaseStream interface.
class BaseMemStreamTest_2754 : public ::testing::Test {
protected:
  using Byte = unsigned char;

  static Object MakeEmptyDictObject()
  {
    // BaseStream stores an Object "dict". An empty/default Object is sufficient
    // for construction; tests only use observable behaviors of the stream.
    return Object();
  }
};

} // namespace

TEST_F(BaseMemStreamTest_2754, ConstructorExposesStartAndLength_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 10> buf{};
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<BaseMemStreamTest_2754::Byte>(i);
  }

  const Goffset start = 2;
  const Goffset length = 5;

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  EXPECT_EQ(s.getStart(), start);
  EXPECT_EQ(s.getLength(), length);
}

TEST_F(BaseMemStreamTest_2754, GetCharReadsSequentiallyAndEventuallyEOF_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 8> buf{};
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<BaseMemStreamTest_2754::Byte>(10 + i);
  }

  const Goffset start = 1;
  const Goffset length = 3; // bytes: 11,12,13

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  const Goffset pos0 = s.getPos();

  const int c0 = s.getChar();
  const Goffset pos1 = s.getPos();
  ASSERT_GE(c0, 0);
  EXPECT_EQ(static_cast<BaseMemStreamTest_2754::Byte>(c0), buf[static_cast<size_t>(start + 0)]);
  EXPECT_EQ(pos1 - pos0, 1);

  const int c1 = s.getChar();
  const Goffset pos2 = s.getPos();
  ASSERT_GE(c1, 0);
  EXPECT_EQ(static_cast<BaseMemStreamTest_2754::Byte>(c1), buf[static_cast<size_t>(start + 1)]);
  EXPECT_EQ(pos2 - pos1, 1);

  const int c2 = s.getChar();
  const Goffset pos3 = s.getPos();
  ASSERT_GE(c2, 0);
  EXPECT_EQ(static_cast<BaseMemStreamTest_2754::Byte>(c2), buf[static_cast<size_t>(start + 2)]);
  EXPECT_EQ(pos3 - pos2, 1);

  // Past end: should return EOF (negative).
  EXPECT_LT(s.getChar(), 0);
}

TEST_F(BaseMemStreamTest_2754, LookCharDoesNotAdvancePosition_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 6> buf{};
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<BaseMemStreamTest_2754::Byte>(i);
  }

  const Goffset start = 2;
  const Goffset length = 2; // bytes: 2,3

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  const Goffset pos0 = s.getPos();

  const int l0 = s.lookChar();
  const Goffset pos1 = s.getPos();
  ASSERT_GE(l0, 0);
  EXPECT_EQ(static_cast<BaseMemStreamTest_2754::Byte>(l0), buf[static_cast<size_t>(start)]);
  EXPECT_EQ(pos1, pos0);

  const int l1 = s.lookChar();
  const Goffset pos2 = s.getPos();
  ASSERT_GE(l1, 0);
  EXPECT_EQ(static_cast<BaseMemStreamTest_2754::Byte>(l1), buf[static_cast<size_t>(start)]);
  EXPECT_EQ(pos2, pos0);

  const int c0 = s.getChar();
  const Goffset pos3 = s.getPos();
  ASSERT_GE(c0, 0);
  EXPECT_EQ(static_cast<BaseMemStreamTest_2754::Byte>(c0), buf[static_cast<size_t>(start)]);
  EXPECT_EQ(pos3 - pos0, 1);
}

TEST_F(BaseMemStreamTest_2754, RewindReturnsToBeginningOfStream_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 5> buf{};
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<BaseMemStreamTest_2754::Byte>(50 + i);
  }

  const Goffset start = 1;
  const Goffset length = 3; // bytes: 51,52,53

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  const int first = s.getChar();
  ASSERT_GE(first, 0);

  EXPECT_TRUE(s.rewind());

  const int again = s.getChar();
  ASSERT_GE(again, 0);
  EXPECT_EQ(again, first);
}

TEST_F(BaseMemStreamTest_2754, SetPosCanReturnToStartAndAdvanceFromCurrent_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 7> buf{};
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<BaseMemStreamTest_2754::Byte>(100 + i);
  }

  const Goffset start = 2;
  const Goffset length = 4; // bytes: 102,103,104,105

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  // Consume one byte.
  const int c0 = s.getChar();
  ASSERT_GE(c0, 0);
  EXPECT_EQ(static_cast<Byte>(c0), buf[static_cast<size_t>(start)]);

  // Absolute setPos(0) should bring us back to the beginning of the stream.
  s.setPos(0 /*pos*/, 0 /*dir*/);
  const int c0b = s.getChar();
  ASSERT_GE(c0b, 0);
  EXPECT_EQ(static_cast<Byte>(c0b), buf[static_cast<size_t>(start)]);

  // Move forward relative to current position (dir=1): skip one byte, then read.
  // We do not assume how out-of-range is handled; we stay within length.
  s.setPos(1 /*pos*/, 1 /*dir*/);
  const int c2 = s.getChar();
  ASSERT_GE(c2, 0);
  // After reading first byte and resetting + reading it again, we're positioned after it.
  // Then setPos(+1, CUR) should land on the third element in the stream.
  EXPECT_EQ(static_cast<Byte>(c2), buf[static_cast<size_t>(start + 2)]);
}

TEST_F(BaseMemStreamTest_2754, ZeroLengthStreamReturnsEOF_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 4> buf{{1, 2, 3, 4}};

  const Goffset start = 0;
  const Goffset length = 0;

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  EXPECT_LT(s.lookChar(), 0);
  EXPECT_LT(s.getChar(), 0);

  // Even if rewind() behavior is implementation-defined, it should not make reads succeed.
  (void)s.rewind();
  EXPECT_LT(s.getChar(), 0);
}

TEST_F(BaseMemStreamTest_2754, MoveStartAdjustsReportedStart_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 8> buf{};
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<BaseMemStreamTest_2754::Byte>(i);
  }

  const Goffset start = 1;
  const Goffset length = 5;

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  const Goffset before = s.getStart();
  s.moveStart(2);
  const Goffset after = s.getStart();

  EXPECT_EQ(after, before + 2);
}

TEST_F(BaseMemStreamTest_2754, MakeSubStreamProducesReadableSubrange_2754)
{
  std::array<BaseMemStreamTest_2754::Byte, 10> buf{};
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<BaseMemStreamTest_2754::Byte>(200 + i);
  }

  // Main stream covers bytes [start..start+len).
  const Goffset start = 2;
  const Goffset length = 6; // bytes: 202..207

  BaseMemStream<BaseMemStreamTest_2754::Byte> s(buf.data(), start, length, MakeEmptyDictObject());

  // Substream starting 1 byte into the main stream, limited to 2 bytes.
  std::unique_ptr<Stream> sub = s.makeSubStream(/*startA=*/1, /*limited=*/true, /*lengthA=*/2,
                                                MakeEmptyDictObject());
  ASSERT_NE(sub, nullptr);

  const int a = sub->getChar();
  const int b = sub->getChar();
  const int eof = sub->getChar();

  ASSERT_GE(a, 0);
  ASSERT_GE(b, 0);
  EXPECT_EQ(static_cast<Byte>(a), buf[static_cast<size_t>(start + 1)]);
  EXPECT_EQ(static_cast<Byte>(b), buf[static_cast<size_t>(start + 2)]);
  EXPECT_LT(eof, 0);
}