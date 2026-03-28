// TEST_ID: 178
// File: embed_stream_unfilteredrewind_test_178.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/Stream.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// A strict mock so we can verify the external interaction precisely.
class MockStream final : public Stream {
public:
  MOCK_METHOD(bool, unfilteredRewind, (), (override));
};

class EmbedStreamTest_178 : public ::testing::Test {
protected:
  // Helper to construct an EmbedStream with minimal assumptions.
  // We avoid relying on any internal behavior; we only need a valid object.
  static std::unique_ptr<EmbedStream> MakeEmbedStream(MockStream *underlying) {
    // Poppler's Object is movable; exact contents are irrelevant for these tests.
    Object dictObj;

    // Use non-limited stream with length 0 by default; "unfilteredRewind" behavior
    // is expected to be forwarded regardless of these flags.
    const bool limited = false;
    const Goffset length = 0;
    const bool reusable = false;

    return std::make_unique<EmbedStream>(underlying, std::move(dictObj), limited, length, reusable);
  }
};

} // namespace

TEST_F(EmbedStreamTest_178, UnfilteredRewind_ForwardsCallAndReturnsTrue_178) {
  StrictMock<MockStream> mock;
  auto es = MakeEmbedStream(&mock);

  EXPECT_CALL(mock, unfilteredRewind()).Times(1).WillOnce(Return(true));

  EXPECT_TRUE(es->unfilteredRewind());
}

TEST_F(EmbedStreamTest_178, UnfilteredRewind_ForwardsCallAndReturnsFalse_178) {
  StrictMock<MockStream> mock;
  auto es = MakeEmbedStream(&mock);

  EXPECT_CALL(mock, unfilteredRewind()).Times(1).WillOnce(Return(false));

  EXPECT_FALSE(es->unfilteredRewind());
}

TEST_F(EmbedStreamTest_178, UnfilteredRewind_MultipleCallsAreForwardedEachTime_178) {
  StrictMock<MockStream> mock;
  auto es = MakeEmbedStream(&mock);

  EXPECT_CALL(mock, unfilteredRewind())
      .Times(2)
      .WillOnce(Return(true))
      .WillOnce(Return(false));

  EXPECT_TRUE(es->unfilteredRewind());
  EXPECT_FALSE(es->unfilteredRewind());
}