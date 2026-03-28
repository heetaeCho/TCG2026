// TEST_ID: 180
// Unit tests for ASCIIHexStream::getChar()
// File: Stream.h (Poppler)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Stream.h"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::Throw;

class ASCIIHexStreamTest_180 : public ::testing::Test {};

// We mock lookChar() to verify getChar() behavior and interaction.
class MockASCIIHexStream_180 : public ASCIIHexStream {
public:
  using ASCIIHexStream::ASCIIHexStream; // inherit constructors

  MOCK_METHOD(int, lookChar, (), (override));
};

TEST_F(ASCIIHexStreamTest_180, GetCharReturnsLookCharValue_180) {
  MockASCIIHexStream_180 s(0);

  EXPECT_CALL(s, lookChar()).Times(1).WillOnce(Return('A'));

  const int c = s.getChar();
  EXPECT_EQ(c, 'A');
}

TEST_F(ASCIIHexStreamTest_180, GetCharPropagatesEOF_180) {
  MockASCIIHexStream_180 s(0);

  EXPECT_CALL(s, lookChar()).Times(1).WillOnce(Return(EOF));

  const int c = s.getChar();
  EXPECT_EQ(c, EOF);
}

TEST_F(ASCIIHexStreamTest_180, GetCharCallsLookCharEachTimeForMultipleReads_180) {
  MockASCIIHexStream_180 s(0);

  InSequence seq;
  EXPECT_CALL(s, lookChar()).WillOnce(Return('1'));
  EXPECT_CALL(s, lookChar()).WillOnce(Return('2'));
  EXPECT_CALL(s, lookChar()).WillOnce(Return(EOF));

  EXPECT_EQ(s.getChar(), '1');
  EXPECT_EQ(s.getChar(), '2');
  EXPECT_EQ(s.getChar(), EOF);
}

TEST_F(ASCIIHexStreamTest_180, GetCharPropagatesExceptionFromLookChar_180) {
  MockASCIIHexStream_180 s(0);

  EXPECT_CALL(s, lookChar()).Times(1).WillOnce(Throw(std::runtime_error("boom")));

  EXPECT_THROW((void)s.getChar(), std::runtime_error);
}