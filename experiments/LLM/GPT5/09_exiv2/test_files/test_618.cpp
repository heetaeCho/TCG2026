// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_remoteio_populatefakedata_618.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::BasicIo;
using Exiv2::RemoteIo;

class RemoteIoTest_618 : public ::testing::Test {
 protected:
  RemoteIo io_;

  void TearDown() override {
    // Close defensively; do not assert on close behavior here.
    (void)io_.close();
  }

  static std::vector<Exiv2::byte> ReadFromStart(RemoteIo& io, size_t n, size_t* outRead = nullptr) {
    std::vector<Exiv2::byte> buf(n);
    if (n == 0) {
      if (outRead) *outRead = 0;
      return buf;
    }

    // Best-effort seek to start; if seek fails, still attempt read to keep the test black-boxy.
    (void)io.seek(0, BasicIo::beg);

    const size_t r = io.read(buf.data(), n);
    buf.resize(r);
    if (outRead) *outRead = r;
    return buf;
  }
};

TEST_F(RemoteIoTest_618, PopulateFakeData_DoesNotChangeOpenStateWhenClosed_618) {
  const bool wasOpen = io_.isopen();
  ASSERT_FALSE(wasOpen);

  EXPECT_NO_THROW(io_.populateFakeData());

  EXPECT_EQ(io_.isopen(), wasOpen);
}

TEST_F(RemoteIoTest_618, PopulateFakeData_CanBeCalledAfterOpen_618) {
  (void)io_.open();
  const bool wasOpen = io_.isopen();

  EXPECT_NO_THROW(io_.populateFakeData());

  EXPECT_EQ(io_.isopen(), wasOpen);
}

TEST_F(RemoteIoTest_618, PopulateFakeData_CanBeCalledAfterClose_618) {
  (void)io_.open();
  (void)io_.close();

  const bool wasOpen = io_.isopen();
  ASSERT_FALSE(wasOpen);

  EXPECT_NO_THROW(io_.populateFakeData());

  EXPECT_EQ(io_.isopen(), wasOpen);
}

TEST_F(RemoteIoTest_618, PopulateFakeData_IdempotentForObservableReadResults_618) {
  // This test does NOT assume what "fake data" is; it only checks that a second call
  // does not further change observable data compared to the first call.
  (void)io_.open();

  io_.populateFakeData();
  size_t r1 = 0;
  const auto afterFirst = ReadFromStart(io_, /*n=*/256, &r1);

  io_.populateFakeData();
  size_t r2 = 0;
  const auto afterSecond = ReadFromStart(io_, /*n=*/256, &r2);

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(afterFirst, afterSecond);
}

TEST_F(RemoteIoTest_618, PopulateFakeData_DoesNotBreakZeroLengthRead_618) {
  (void)io_.open();
  io_.populateFakeData();

  std::vector<Exiv2::byte> buf;  // empty
  // read(nullptr, 0) is sometimes allowed/used; but passing nullptr is risky across impls.
  // Use a valid pointer with zero count instead.
  Exiv2::byte dummy = 0;
  EXPECT_EQ(io_.read(&dummy, 0), static_cast<size_t>(0));
}

TEST_F(RemoteIoTest_618, PopulateFakeData_DoesNotIncreaseErrorCode_618) {
  // Black-box invariant: calling populateFakeData should not *introduce* an error state.
  // We only assert that error() does not become "more erroneous" if it was already non-zero.
  // (No assumptions on the numeric meaning of error codes.)
  (void)io_.open();

  const int errBefore = io_.error();
  EXPECT_NO_THROW(io_.populateFakeData());
  const int errAfter = io_.error();

  if (errBefore == 0) {
    EXPECT_EQ(errAfter, 0);
  } else {
    // If there was already an error, at least ensure the call doesn't flip to a *different* one.
    // This stays purely observable without guessing semantics.
    EXPECT_EQ(errAfter, errBefore);
  }
}

TEST_F(RemoteIoTest_618, PopulateFakeData_AllowsSubsequentSeekAndTell_618) {
  (void)io_.open();
  io_.populateFakeData();

  // Exercise boundary-ish seeks and tell without assuming file size semantics.
  const size_t t0 = io_.tell();
  EXPECT_NO_THROW((void)io_.seek(0, BasicIo::cur));
  const size_t t1 = io_.tell();

  // tell() should remain stable for a no-op seek, if the seek succeeded; if seek fails, tell may be unchanged anyway.
  EXPECT_EQ(t1, io_.tell());
  (void)t0;  // t0 intentionally unused for assertions (we don't assume starting offset).
}

}  // namespace