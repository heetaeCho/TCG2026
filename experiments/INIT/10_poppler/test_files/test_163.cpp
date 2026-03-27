// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 163
//
// Unit tests for CachedFileStream::unfilteredRewind()
// Interface under test (from Stream.h):
//   bool unfilteredRewind() override { return rewind(); }

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

// Include the real Poppler header under test.
#include "poppler/Stream.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// A strict mock that lets us verify the observable external interaction:
// unfilteredRewind() must call rewind() and return its result.
class MockCachedFileStream final : public CachedFileStream {
public:
  MockCachedFileStream(std::shared_ptr<CachedFile> ccA, Goffset startA, bool limitedA, Goffset lengthA, Object&& dictA)
      : CachedFileStream(std::move(ccA), startA, limitedA, lengthA, std::move(dictA)) {}

  ~MockCachedFileStream() override = default;

  MOCK_METHOD(bool, rewind, (), (override));
};

class CachedFileStreamTest_163 : public ::testing::Test {
protected:
  // Helper to create a stream instance without relying on any internal details.
  // We intentionally pass a null CachedFile pointer and override rewind() in the mock,
  // so tests only validate the unfilteredRewind() -> rewind() delegation contract.
  static std::unique_ptr<StrictMock<MockCachedFileStream>> makeMock() {
    std::shared_ptr<CachedFile> cc; // null
    const Goffset start = 0;
    const bool limited = false;
    const Goffset length = 0;

    Object dict; // default-constructed dictionary object (black-box for these tests)
    return std::make_unique<StrictMock<MockCachedFileStream>>(cc, start, limited, length, std::move(dict));
  }
};

} // namespace

TEST_F(CachedFileStreamTest_163, UnfilteredRewindCallsRewindAndReturnsTrue_163) {
  auto s = makeMock();

  EXPECT_CALL(*s, rewind()).Times(1).WillOnce(Return(true));

  EXPECT_TRUE(s->unfilteredRewind());
}

TEST_F(CachedFileStreamTest_163, UnfilteredRewindCallsRewindAndReturnsFalse_163) {
  auto s = makeMock();

  EXPECT_CALL(*s, rewind()).Times(1).WillOnce(Return(false));

  EXPECT_FALSE(s->unfilteredRewind());
}

TEST_F(CachedFileStreamTest_163, UnfilteredRewindDelegatesEachTimeOnMultipleCalls_163) {
  auto s = makeMock();

  EXPECT_CALL(*s, rewind())
      .Times(3)
      .WillOnce(Return(true))
      .WillOnce(Return(false))
      .WillOnce(Return(true));

  EXPECT_TRUE(s->unfilteredRewind());
  EXPECT_FALSE(s->unfilteredRewind());
  EXPECT_TRUE(s->unfilteredRewind());
}