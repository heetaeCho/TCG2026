// Stream_toUnsignedChars_122_test.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "Stream.h"

using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class DataStreamMock : public Stream {
public:
  explicit DataStreamMock(const std::vector<unsigned char> &bytes) : data_(bytes) {
    using namespace testing;

    ON_CALL(*this, hasGetChars()).WillByDefault(Return(true));
    ON_CALL(*this, rewind()).WillByDefault(Invoke(this, &DataStreamMock::DoRewind));
    ON_CALL(*this, lookChar()).WillByDefault(Invoke(this, &DataStreamMock::DoLookChar));
    ON_CALL(*this, getChars).WillByDefault(Invoke(this, &DataStreamMock::DoGetChars));
    ON_CALL(*this, getChar()).WillByDefault(Return(EOF));
  }

  // Public virtuals we may want to assert on.
  MOCK_METHOD(bool, rewind, (), (override));
  MOCK_METHOD(int, lookChar, (), (override));
  MOCK_METHOD(int, getChar, (), (override));

  // These are private virtuals in the base, but still overridable.
  MOCK_METHOD(int, getChars, (int nChars, unsigned char *buffer), (override));
  MOCK_METHOD(bool, hasGetChars, (), (override));

  void SetData(const std::vector<unsigned char> &bytes) {
    data_ = bytes;
    pos_ = 0;
  }

private:
  bool DoRewind() {
    pos_ = 0;
    return true;
  }

  int DoLookChar() {
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<int>(data_[pos_]);
  }

  int DoGetChars(int nChars, unsigned char *buffer) {
    if (nChars <= 0) {
      return 0;
    }
    const size_t remaining = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t toRead = std::min<size_t>(static_cast<size_t>(nChars), remaining);
    if (toRead == 0) {
      return 0;
    }
    std::memcpy(buffer, data_.data() + pos_, toRead);
    pos_ += toRead;
    return static_cast<int>(toRead);
  }

  std::vector<unsigned char> data_;
  size_t pos_ = 0;
};

class StreamToUnsignedCharsTest_122 : public ::testing::Test {};

static std::vector<unsigned char> BytesOf(const std::string &s) {
  return std::vector<unsigned char>(s.begin(), s.end());
}

TEST_F(StreamToUnsignedCharsTest_122, RewindFailsReturnsEmpty_122) {
  StrictMock<DataStreamMock> s(BytesOf("abc"));

  EXPECT_CALL(s, rewind()).WillOnce(Return(false));
  // If rewind fails, no further reads/peeks should happen.
  EXPECT_CALL(s, getChars(testing::_, testing::_)).Times(0);
  EXPECT_CALL(s, lookChar()).Times(0);

  const auto out = s.toUnsignedChars(/*initialSize=*/4, /*sizeIncrement=*/4);
  EXPECT_TRUE(out.empty());
}

TEST_F(StreamToUnsignedCharsTest_122, ReadsLessThanInitialSizeStopsWithoutLookChar_122) {
  // Data shorter than initialSize -> first read is partial -> should stop without calling lookChar().
  StrictMock<DataStreamMock> s(BytesOf("abc"));

  EXPECT_CALL(s, rewind()).Times(1);
  EXPECT_CALL(s, hasGetChars()).Times(testing::AtLeast(1));
  EXPECT_CALL(s, getChars(8, testing::_)).Times(1);
  EXPECT_CALL(s, lookChar()).Times(0);
  EXPECT_CALL(s, getChar()).Times(0);

  const auto out = s.toUnsignedChars(/*initialSize=*/8, /*sizeIncrement=*/4);
  EXPECT_EQ(out, BytesOf("abc"));
}

TEST_F(StreamToUnsignedCharsTest_122, ReadsExactlyInitialSizeThenLookCharEOFStops_122) {
  // Exactly fills initial buffer, then lookChar() returns EOF -> stop without growing.
  StrictMock<DataStreamMock> s(BytesOf("ABCDEFGH"));

  EXPECT_CALL(s, rewind()).Times(1);
  EXPECT_CALL(s, hasGetChars()).Times(testing::AtLeast(1));
  EXPECT_CALL(s, getChars(8, testing::_)).Times(1);
  EXPECT_CALL(s, lookChar()).Times(1);
  EXPECT_CALL(s, getChar()).Times(0);

  const auto out = s.toUnsignedChars(/*initialSize=*/8, /*sizeIncrement=*/4);
  EXPECT_EQ(out, BytesOf("ABCDEFGH"));
}

TEST_F(StreamToUnsignedCharsTest_122, GrowsAndReadsMultipleChunksUntilShortRead_122) {
  // initialSize=4, increment=4, data=10 bytes
  // read 4 (full) -> lookChar != EOF -> grow -> read 4 (full) -> lookChar != EOF -> grow -> read 2 (short) -> stop
  StrictMock<DataStreamMock> s(BytesOf("0123456789"));

  EXPECT_CALL(s, rewind()).Times(1);
  EXPECT_CALL(s, hasGetChars()).Times(testing::AtLeast(1));

  EXPECT_CALL(s, getChars(4, testing::_)).Times(3);  // 4, 4, then 2 (still called with 4)
  EXPECT_CALL(s, lookChar()).Times(2);               // after each full read, until the last short read stops
  EXPECT_CALL(s, getChar()).Times(0);

  const auto out = s.toUnsignedChars(/*initialSize=*/4, /*sizeIncrement=*/4);
  EXPECT_EQ(out, BytesOf("0123456789"));
}

TEST_F(StreamToUnsignedCharsTest_122, InitialSizeZeroReturnsEmptyAndDoesNotLoopForever_122) {
  StrictMock<DataStreamMock> s(BytesOf("xyz"));

  EXPECT_CALL(s, rewind()).Times(1);
  EXPECT_CALL(s, hasGetChars()).Times(testing::AtLeast(1));
  // With initialSize=0, the implementation will try to read 0 chars first; our stream returns 0.
  EXPECT_CALL(s, getChars(0, testing::_)).Times(1);
  EXPECT_CALL(s, lookChar()).Times(0);

  const auto out = s.toUnsignedChars(/*initialSize=*/0, /*sizeIncrement=*/4);
  EXPECT_TRUE(out.empty());
}

TEST_F(StreamToUnsignedCharsTest_122, SizeIncrementZeroStopsAfterFirstFullRead_122) {
  // Boundary: sizeIncrement=0. If first read fills initialSize and lookChar != EOF, next read will request 0 bytes
  // and loop should terminate, returning only the initial chunk.
  StrictMock<DataStreamMock> s(BytesOf("ABCDEFGHIJ"));  // 10 bytes

  EXPECT_CALL(s, rewind()).Times(1);
  EXPECT_CALL(s, hasGetChars()).Times(testing::AtLeast(1));

  // First full read of 4, then lookChar indicates there is more data, then a 0-length read ends the loop.
  EXPECT_CALL(s, getChars(4, testing::_)).Times(1);
  EXPECT_CALL(s, lookChar()).Times(1);
  EXPECT_CALL(s, getChars(0, testing::_)).Times(1);

  const auto out = s.toUnsignedChars(/*initialSize=*/4, /*sizeIncrement=*/0);
  EXPECT_EQ(out, BytesOf("ABCD"));
}

} // namespace