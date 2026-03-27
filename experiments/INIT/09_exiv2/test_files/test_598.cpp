// SPDX-License-Identifier: GPL-2.0-or-later
// File: remoteio_populateblocks_test.cpp
//
// TEST_ID: 598
//
// Unit tests for Exiv2::RemoteIo::Impl::populateBlocks(size_t, size_t)
//
// Notes / constraints handling:
// - Treat implementation as black box: validate only observable behavior (return value / thrown exception)
// - Use Google Mock only to mock external interaction: getDataByRange(...)
// - Do not inspect or assert on internal/private state (no direct checks of blocksMap_ contents)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

#include "exiv2/error.hpp"

// Include the header that declares Exiv2::RemoteIo (and nested Impl).
// In the Exiv2 codebase this is typically "exiv2/basicio.hpp".
#include "exiv2/basicio.hpp"

namespace {

// We only mock an external interaction: the data fetch by range.
// This assumes getDataByRange is a virtual member of RemoteIo::Impl with the
// signature used by populateBlocks(lowBlock, highBlock, data).
class MockRemoteIoImpl : public Exiv2::RemoteIo::Impl {
public:
  using Exiv2::RemoteIo::Impl::Impl;

  MOCK_METHOD(void, getDataByRange, (size_t lowBlock, size_t highBlock, std::string& data), (override));

  // Helpers to make the SUT usable in tests without asserting on private state.
  // These helpers are only used if the corresponding members are accessible
  // (e.g., protected in the real code). If they are private, compilation will fail,
  // in which case these tests should be adapted to the actual public construction API.
  void EnsureBlocksSize(size_t n) {
    blocksMap_.resize(n);
  }
  void SetBlockSize(size_t n) { blockSize_ = n; }
  void SetTotalSize(size_t n) { size_ = n; }

  // Optionally mark a block as non-none to exercise boundary paths without reading state back.
  void PopulateBlock(size_t idx, const std::string& bytes) {
    blocksMap_[idx].populate(reinterpret_cast<const Exiv2::byte*>(bytes.data()), bytes.size());
  }
};

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::StrictMock;

TEST(RemoteIoPopulateBlocksTest_598, ReturnsDataLengthWhenRangeFetchProvidesData_598) {
  StrictMock<MockRemoteIoImpl> impl;

  // Arrange minimal internal sizing needed for indexing; we do not assert on internal contents.
  impl.EnsureBlocksSize(16);
  impl.SetBlockSize(4);

  const size_t low = 0;
  const size_t high = 3;

  const std::string payload = "HelloWorld"; // length 10
  impl.SetTotalSize(payload.size());        // helps exercise the (rcount == size_) branch deterministically

  EXPECT_CALL(impl, getDataByRange(low, high, _))
      .WillOnce(Invoke([&](size_t, size_t, std::string& out) { out = payload; }));

  // Act
  const size_t rcount = impl.populateBlocks(low, high);

  // Assert (observable)
  EXPECT_EQ(rcount, payload.size());
}

TEST(RemoteIoPopulateBlocksTest_598, ThrowsErrorWhenRangeFetchReturnsEmptyData_598) {
  StrictMock<MockRemoteIoImpl> impl;

  impl.EnsureBlocksSize(4);
  impl.SetBlockSize(4);
  impl.SetTotalSize(123); // any non-zero, not important for this behavior

  const size_t low = 0;
  const size_t high = 0;

  EXPECT_CALL(impl, getDataByRange(low, high, _))
      .WillOnce(Invoke([&](size_t, size_t, std::string& out) { out.clear(); }));

  // Act / Assert (observable)
  EXPECT_THROW(
      {
        (void)impl.populateBlocks(low, high);
      },
      Exiv2::Error);
}

TEST(RemoteIoPopulateBlocksTest_598, CallsGetDataByRangeWithExactLowHighForSingleBlockRange_598) {
  StrictMock<MockRemoteIoImpl> impl;

  impl.EnsureBlocksSize(8);
  impl.SetBlockSize(8);

  const size_t low = 2;
  const size_t high = 2;

  const std::string payload = "abcd"; // length 4
  impl.SetTotalSize(999);             // ensure (rcount == size_) is false so iBlock starts at low

  EXPECT_CALL(impl, getDataByRange(low, high, _))
      .WillOnce(Invoke([&](size_t gotLow, size_t gotHigh, std::string& out) {
        // Verify external interaction parameters (mock boundary)
        EXPECT_EQ(gotLow, low);
        EXPECT_EQ(gotHigh, high);
        out = payload;
      }));

  const size_t rcount = impl.populateBlocks(low, high);
  EXPECT_EQ(rcount, payload.size());
}

TEST(RemoteIoPopulateBlocksTest_598, DoesNotFetchIfRequestedHighBlockAlreadyPopulatedAndLowEqualsHigh_598) {
  StrictMock<MockRemoteIoImpl> impl;

  // This test is meant to exercise the early-exit behavior when the target block is not "None".
  // We only assert observable behavior: return value and that getDataByRange is not invoked.
  impl.EnsureBlocksSize(4);
  impl.SetBlockSize(4);
  impl.SetTotalSize(0);

  const size_t low = 1;
  const size_t high = 1;

  // Make blocksMap_[high] non-none by populating it.
  impl.PopulateBlock(high, "X");

  EXPECT_CALL(impl, getDataByRange(_, _, _)).Times(0);

  const size_t rcount = impl.populateBlocks(low, high);

  // When no fetch happens, rcount is expected to stay 0 (observable via return).
  EXPECT_EQ(rcount, 0u);
}

TEST(RemoteIoPopulateBlocksTest_598, SkipsLeadingNonNoneBlocksByAdvancingLowBlockBeforeFetch_598) {
  StrictMock<MockRemoteIoImpl> impl;

  // Arrange: low block and the next block are already non-none; high is none.
  // We verify that getDataByRange is called with an advanced low value (external interaction),
  // without asserting anything about internal maps.
  impl.EnsureBlocksSize(10);
  impl.SetBlockSize(4);
  impl.SetTotalSize(999);

  const size_t originalLow = 0;
  const size_t high = 5;

  impl.PopulateBlock(0, "A");
  impl.PopulateBlock(1, "B");
  // Expect low advanced to 2 (first "None" after 0 and 1).
  const size_t expectedLow = 2;

  const std::string payload = "123456"; // length 6

  EXPECT_CALL(impl, getDataByRange(expectedLow, high, _))
      .WillOnce(Invoke([&](size_t gotLow, size_t gotHigh, std::string& out) {
        EXPECT_EQ(gotLow, expectedLow);
        EXPECT_EQ(gotHigh, high);
        out = payload;
      }));

  const size_t rcount = impl.populateBlocks(originalLow, high);
  EXPECT_EQ(rcount, payload.size());
}

} // namespace