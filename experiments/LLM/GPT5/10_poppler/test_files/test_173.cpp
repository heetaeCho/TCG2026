// TEST_ID: 173
// Unit tests for BaseMemStream::moveStart (black-box, interface-only)
//
// File: Stream_test_173.cpp

#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "poppler/Stream.h" // adjust include path if your build uses a different prefix

namespace {

using U8MemStream = BaseMemStream<unsigned char>;

class BaseMemStreamTest_173 : public ::testing::Test {
protected:
  static std::vector<unsigned char> Bytes(const std::string &s)
  {
    return std::vector<unsigned char>(s.begin(), s.end());
  }

  static std::string ReadAll(U8MemStream &s)
  {
    std::string out;
    while (true) {
      const int c = s.getChar();
      if (c == EOF) {
        break;
      }
      out.push_back(static_cast<char>(c));
    }
    return out;
  }

  static int Look(U8MemStream &s) { return s.lookChar(); }
  static int Get(U8MemStream &s) { return s.getChar(); }
};

TEST_F(BaseMemStreamTest_173, MoveStartZero_NoObservableChange_173)
{
  auto buf = Bytes("abcde");
  Object dict;
  U8MemStream s(buf.data(), /*startA=*/0, /*lengthA=*/static_cast<Goffset>(buf.size()), std::move(dict));

  ASSERT_TRUE(s.rewind());
  const auto startBefore = s.getStart();
  const auto lenBefore = s.getLength();

  // Observe initial read
  const int first = Get(s);
  ASSERT_NE(first, EOF);

  // Move by zero should not change observable stream range.
  s.moveStart(0);

  EXPECT_EQ(s.getStart(), startBefore);
  EXPECT_EQ(s.getLength(), lenBefore);

  ASSERT_TRUE(s.rewind());
  EXPECT_EQ(Get(s), first);
}

TEST_F(BaseMemStreamTest_173, MoveStartPositive_ShiftsStartAndReducesLength_173)
{
  auto buf = Bytes("abcde");
  Object dict;
  U8MemStream s(buf.data(), /*startA=*/0, /*lengthA=*/static_cast<Goffset>(buf.size()), std::move(dict));

  s.moveStart(2);

  EXPECT_EQ(s.getStart(), 2);
  EXPECT_EQ(s.getLength(), 3);

  ASSERT_TRUE(s.rewind());
  EXPECT_EQ(Get(s), static_cast<unsigned char>('c'));
  EXPECT_EQ(Get(s), static_cast<unsigned char>('d'));
  EXPECT_EQ(Get(s), static_cast<unsigned char>('e'));
  EXPECT_EQ(Get(s), EOF);
}

TEST_F(BaseMemStreamTest_173, MoveStartFromNonZeroStart_UpdatesStartAndVisibleBytes_173)
{
  // Underlying buffer: a b c d e
  // Initial visible range: start=1, length=3 => b c d
  auto buf = Bytes("abcde");
  Object dict;
  U8MemStream s(buf.data(), /*startA=*/1, /*lengthA=*/3, std::move(dict));

  ASSERT_TRUE(s.rewind());
  EXPECT_EQ(Get(s), static_cast<unsigned char>('b'));
  EXPECT_EQ(Get(s), static_cast<unsigned char>('c'));
  EXPECT_EQ(Get(s), static_cast<unsigned char>('d'));
  EXPECT_EQ(Get(s), EOF);

  // Shift by 1 => start=2, length=2 => c d
  s.moveStart(1);

  EXPECT_EQ(s.getStart(), 2);
  EXPECT_EQ(s.getLength(), 2);

  ASSERT_TRUE(s.rewind());
  EXPECT_EQ(Get(s), static_cast<unsigned char>('c'));
  EXPECT_EQ(Get(s), static_cast<unsigned char>('d'));
  EXPECT_EQ(Get(s), EOF);
}

TEST_F(BaseMemStreamTest_173, MoveStartToExactEnd_LengthBecomesZeroAndReadsEOF_173)
{
  auto buf = Bytes("abcd");
  Object dict;
  U8MemStream s(buf.data(), /*startA=*/0, /*lengthA=*/static_cast<Goffset>(buf.size()), std::move(dict));

  // Move start by exactly the visible length => empty stream.
  s.moveStart(static_cast<Goffset>(buf.size()));

  EXPECT_EQ(s.getStart(), static_cast<Goffset>(buf.size()));
  EXPECT_EQ(s.getLength(), 0);

  ASSERT_TRUE(s.rewind());
  EXPECT_EQ(Look(s), EOF);
  EXPECT_EQ(Get(s), EOF);
}

TEST_F(BaseMemStreamTest_173, MoveStartAffectsLookCharAndGetCharConsistently_173)
{
  auto buf = Bytes("wxyz");
  Object dict;
  U8MemStream s(buf.data(), /*startA=*/0, /*lengthA=*/static_cast<Goffset>(buf.size()), std::move(dict));

  s.moveStart(1); // visible should begin at 'x'

  ASSERT_TRUE(s.rewind());
  EXPECT_EQ(Look(s), static_cast<unsigned char>('x'));
  EXPECT_EQ(Get(s), static_cast<unsigned char>('x'));
  EXPECT_EQ(Look(s), static_cast<unsigned char>('y'));
  EXPECT_EQ(Get(s), static_cast<unsigned char>('y'));
}

} // namespace