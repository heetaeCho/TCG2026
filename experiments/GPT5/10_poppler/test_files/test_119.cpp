// Stream_doGetChars_119_test.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdio>   // EOF
#include <cstdint>
#include <vector>

#include "Stream.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockStreamDoGetChars_119 : public Stream {
public:
  MockStreamDoGetChars_119() = default;
  ~MockStreamDoGetChars_119() override = default;

  // Public virtuals we want to observe
  MOCK_METHOD(int, getChar, (), (override));

  // These are private virtuals in Stream, but they can still be overridden.
  MOCK_METHOD(bool, hasGetChars, (), (override));
  MOCK_METHOD(int, getChars, (int nChars, unsigned char *buffer), (override));
};

class StreamDoGetCharsTest_119 : public ::testing::Test {
protected:
  StrictMock<MockStreamDoGetChars_119> stream;
};

TEST_F(StreamDoGetCharsTest_119, UsesGetCharsWhenHasGetCharsTrue_119) {
  std::vector<unsigned char> buf(5, 0);

  EXPECT_CALL(stream, hasGetChars()).WillOnce(Return(true));
  EXPECT_CALL(stream, getChars(5, buf.data())).WillOnce(Return(5));
  EXPECT_CALL(stream, getChar()).Times(0);

  const int ret = stream.doGetChars(5, buf.data());
  EXPECT_EQ(ret, 5);
}

TEST_F(StreamDoGetCharsTest_119, ReadsViaGetCharWhenHasGetCharsFalse_AllCharsAvailable_119) {
  std::vector<unsigned char> buf(4, 0);

  {
    InSequence seq;
    EXPECT_CALL(stream, hasGetChars()).WillOnce(Return(false));
    EXPECT_CALL(stream, getChar()).WillOnce(Return('A'));
    EXPECT_CALL(stream, getChar()).WillOnce(Return('B'));
    EXPECT_CALL(stream, getChar()).WillOnce(Return('C'));
    EXPECT_CALL(stream, getChar()).WillOnce(Return('D'));
  }

  const int ret = stream.doGetChars(4, buf.data());
  EXPECT_EQ(ret, 4);

  EXPECT_EQ(buf[0], static_cast<unsigned char>('A'));
  EXPECT_EQ(buf[1], static_cast<unsigned char>('B'));
  EXPECT_EQ(buf[2], static_cast<unsigned char>('C'));
  EXPECT_EQ(buf[3], static_cast<unsigned char>('D'));
}

TEST_F(StreamDoGetCharsTest_119, StopsEarlyOnEOFAndReturnsCountRead_119) {
  std::vector<unsigned char> buf(5, 0xEE);

  {
    InSequence seq;
    EXPECT_CALL(stream, hasGetChars()).WillOnce(Return(false));
    EXPECT_CALL(stream, getChar()).WillOnce(Return('X'));
    EXPECT_CALL(stream, getChar()).WillOnce(Return('Y'));
    EXPECT_CALL(stream, getChar()).WillOnce(Return(EOF));
  }

  const int ret = stream.doGetChars(5, buf.data());
  EXPECT_EQ(ret, 2);

  EXPECT_EQ(buf[0], static_cast<unsigned char>('X'));
  EXPECT_EQ(buf[1], static_cast<unsigned char>('Y'));
  // Remaining bytes are not specified by the interface; do not assert them.
}

TEST_F(StreamDoGetCharsTest_119, ZeroCharsRequestsNoReadsAndReturnsZero_119) {
  EXPECT_CALL(stream, hasGetChars()).WillOnce(Return(false));
  EXPECT_CALL(stream, getChar()).Times(0);
  EXPECT_CALL(stream, getChars(_, _)).Times(0);

  const int ret = stream.doGetChars(0, nullptr);
  EXPECT_EQ(ret, 0);
}

TEST_F(StreamDoGetCharsTest_119, NegativeNCharsDoesNotReadAndReturnsInputValueWhenHasGetCharsFalse_119) {
  EXPECT_CALL(stream, hasGetChars()).WillOnce(Return(false));
  EXPECT_CALL(stream, getChar()).Times(0);
  EXPECT_CALL(stream, getChars(_, _)).Times(0);

  unsigned char dummy = 0;
  const int ret = stream.doGetChars(-1, &dummy);
  EXPECT_EQ(ret, -1);
}

} // namespace