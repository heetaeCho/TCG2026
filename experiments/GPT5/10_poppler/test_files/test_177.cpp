// TEST_ID: 177
// File: embed_stream_get_unfiltered_char_test.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Stream.h" // ./TestProjects/poppler/poppler/Stream.h

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::InSequence;

namespace {

class MockStream : public Stream {
public:
  MOCK_METHOD(int, getUnfilteredChar, (), (override));
};

class EmbedStreamTest_177 : public ::testing::Test {
protected:
  // Keep construction arguments in one place to make tests consistent and readable.
  // We intentionally avoid relying on any internal behavior of EmbedStream besides its public interface.
  static std::unique_ptr<EmbedStream> MakeEmbedStream(Stream *s,
                                                      bool limited = false,
                                                      Goffset length = 0,
                                                      bool reusable = false) {
    // `EmbedStream` takes an Object&& for the dict. We provide a default-constructed Object.
    // The tests do not assume anything about how EmbedStream uses this dict beyond being constructible.
    return std::make_unique<EmbedStream>(s, Object(), limited, length, reusable);
  }
};

TEST_F(EmbedStreamTest_177, GetUnfilteredChar_ForwardsToUnderlyingStream_177) {
  NiceMock<MockStream> mock;

  auto es = MakeEmbedStream(&mock);

  EXPECT_CALL(mock, getUnfilteredChar()).Times(1).WillOnce(Return(42));
  EXPECT_EQ(es->getUnfilteredChar(), 42);
}

TEST_F(EmbedStreamTest_177, GetUnfilteredChar_MultipleCallsForwardEachTime_177) {
  NiceMock<MockStream> mock;

  auto es = MakeEmbedStream(&mock);

  InSequence seq;
  EXPECT_CALL(mock, getUnfilteredChar()).WillOnce(Return(1));
  EXPECT_CALL(mock, getUnfilteredChar()).WillOnce(Return(2));
  EXPECT_CALL(mock, getUnfilteredChar()).WillOnce(Return(3));

  EXPECT_EQ(es->getUnfilteredChar(), 1);
  EXPECT_EQ(es->getUnfilteredChar(), 2);
  EXPECT_EQ(es->getUnfilteredChar(), 3);
}

TEST_F(EmbedStreamTest_177, GetUnfilteredChar_PassesThroughEOF_177) {
  NiceMock<MockStream> mock;

  auto es = MakeEmbedStream(&mock);

  EXPECT_CALL(mock, getUnfilteredChar()).Times(1).WillOnce(Return(EOF));
  EXPECT_EQ(es->getUnfilteredChar(), EOF);
}

TEST_F(EmbedStreamTest_177, GetUnfilteredChar_PassesThroughBoundaryByteValues_177) {
  NiceMock<MockStream> mock;

  auto es = MakeEmbedStream(&mock);

  // Boundary values commonly used by stream APIs: 0x00 and 0xFF (255).
  InSequence seq;
  EXPECT_CALL(mock, getUnfilteredChar()).WillOnce(Return(0));
  EXPECT_CALL(mock, getUnfilteredChar()).WillOnce(Return(255));

  EXPECT_EQ(es->getUnfilteredChar(), 0);
  EXPECT_EQ(es->getUnfilteredChar(), 255);
}

} // namespace