// SPDX-License-Identifier: GPL-2.0-or-later
// File: BaseMemStream_getStart_tests_172.cpp
//
// Unit tests for BaseMemStream::getStart() (black-box via public interface)

#include <gtest/gtest.h>

#include <limits>
#include <utility>
#include <vector>

// Depending on your build include paths, you may need one of these.
// Prefer the one that matches your project's existing test includes.
#include "Stream.h"

namespace {

class BaseMemStreamTest_172 : public ::testing::Test {
protected:
  using BufT = unsigned char;

  static std::unique_ptr<BaseStream> MakeStream(Goffset start, Goffset length) {
    // BaseMemStream keeps a pointer to the caller-provided buffer; keep it alive in the test.
    // For getStart(), the actual buffer contents are irrelevant.
    auto buf = std::make_unique<std::vector<BufT>>(static_cast<size_t>(length > 0 ? length : 1), 0);

    // Object is expected to be movable; a default-constructed Object is typically a null object in Poppler.
    Object dict;

    // Construct the stream.
    // NOTE: We return as BaseStream to avoid relying on more than the public interface.
    auto s = std::make_unique<BaseMemStream<BufT>>(buf->data(), start, length, std::move(dict));

    // Keep buffer alive by attaching it to the stream via a lambda-owned static store is overkill;
    // instead, we store buffers in a static list for the test process lifetime.
    // This avoids depending on any internal ownership behavior of BaseMemStream.
    static std::vector<std::unique_ptr<std::vector<BufT>>> g_buffers;
    g_buffers.push_back(std::move(buf));

    return s;
  }
};

TEST_F(BaseMemStreamTest_172, GetStartReturnsStartWhenZero_172) {
  const Goffset start = 0;
  const Goffset length = 16;

  auto stream = MakeStream(start, length);
  ASSERT_NE(stream, nullptr);

  EXPECT_EQ(stream->getStart(), start);
}

TEST_F(BaseMemStreamTest_172, GetStartReturnsStartWhenPositive_172) {
  const Goffset start = 12345;
  const Goffset length = 64;

  auto stream = MakeStream(start, length);
  ASSERT_NE(stream, nullptr);

  EXPECT_EQ(stream->getStart(), start);
}

TEST_F(BaseMemStreamTest_172, GetStartHandlesLargeAndNegativeValues_172) {
  const Goffset length = 8;

  // Large boundary-ish value
  {
    const Goffset start = (std::numeric_limits<Goffset>::max)();
    auto stream = MakeStream(start, length);
    ASSERT_NE(stream, nullptr);
    EXPECT_EQ(stream->getStart(), start);
  }

  // Negative boundary, only if Goffset is signed
  if (!std::numeric_limits<Goffset>::is_signed) {
    GTEST_SKIP() << "Goffset is unsigned on this platform; skipping negative start test.";
  } else {
    const Goffset start = static_cast<Goffset>(-1);
    auto stream = MakeStream(start, length);
    ASSERT_NE(stream, nullptr);
    EXPECT_EQ(stream->getStart(), start);
  }
}

}  // namespace