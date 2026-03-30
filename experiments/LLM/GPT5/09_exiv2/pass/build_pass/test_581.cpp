// TEST_ID 581
// File: memio_seek_test_581.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::BasicIo;
using Exiv2::MemIo;
using Exiv2::byte;

class MemIoSeekTest_581 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeData(size_t n) {
    std::vector<byte> v(n);
    for (size_t i = 0; i < n; ++i) v[i] = static_cast<byte>(i & 0xFF);
    return v;
  }
};

TEST_F(MemIoSeekTest_581, SeekBegSetsAbsolutePosition_581) {
  const auto data = MakeData(10);
  MemIo io(data.data(), data.size());

  EXPECT_EQ(0, io.seek(0, BasicIo::beg));
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(0, io.seek(5, BasicIo::beg));
  EXPECT_EQ(5u, io.tell());
  EXPECT_FALSE(io.eof());
}

TEST_F(MemIoSeekTest_581, SeekCurMovesRelativeToCurrentPosition_581) {
  const auto data = MakeData(10);
  MemIo io(data.data(), data.size());

  ASSERT_EQ(0, io.seek(3, BasicIo::beg));
  ASSERT_EQ(3u, io.tell());

  EXPECT_EQ(0, io.seek(2, BasicIo::cur));
  EXPECT_EQ(5u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(0, io.seek(-2, BasicIo::cur));
  EXPECT_EQ(3u, io.tell());
  EXPECT_FALSE(io.eof());
}

TEST_F(MemIoSeekTest_581, SeekEndMovesRelativeToEnd_581) {
  const auto data = MakeData(10);
  MemIo io(data.data(), data.size());

  EXPECT_EQ(0, io.seek(0, BasicIo::end));
  EXPECT_EQ(10u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(0, io.seek(-1, BasicIo::end));
  EXPECT_EQ(9u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(0, io.seek(-10, BasicIo::end));
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());
}

TEST_F(MemIoSeekTest_581, SeekToExactEndIsAllowedAndClearsEof_581) {
  const auto data = MakeData(4);
  MemIo io(data.data(), data.size());

  // First, force an EOF condition via a seek beyond end.
  ASSERT_EQ(0, io.seek(0, BasicIo::beg));
  const size_t before = io.tell();
  ASSERT_EQ(1, io.seek(1, BasicIo::end));  // beyond end
  EXPECT_TRUE(io.eof());
  EXPECT_EQ(before, io.tell());  // observable: position should not change on failure

  // Now seek exactly to end; should succeed and clear eof.
  EXPECT_EQ(0, io.seek(0, BasicIo::end));
  EXPECT_EQ(4u, io.tell());
  EXPECT_FALSE(io.eof());
}

TEST_F(MemIoSeekTest_581, SeekNegativeBeforeBeginningFailsAndDoesNotMove_581) {
  const auto data = MakeData(10);
  MemIo io(data.data(), data.size());

  ASSERT_EQ(0, io.seek(2, BasicIo::beg));
  const size_t before = io.tell();

  EXPECT_EQ(1, io.seek(-3, BasicIo::cur));  // would go before 0
  EXPECT_EQ(before, io.tell());             // position unchanged on failure
}

TEST_F(MemIoSeekTest_581, SeekPastEndFailsSetsEofAndDoesNotMove_581) {
  const auto data = MakeData(10);
  MemIo io(data.data(), data.size());

  ASSERT_EQ(0, io.seek(7, BasicIo::beg));
  const size_t before = io.tell();

  EXPECT_EQ(1, io.seek(100, BasicIo::beg));  // well beyond end
  EXPECT_EQ(before, io.tell());              // position unchanged on failure
  EXPECT_TRUE(io.eof());                     // observable EOF condition
}

TEST_F(MemIoSeekTest_581, Boundary_ZeroSizedBufferSeekBehavior_581) {
  MemIo io(nullptr, 0);

  // Seeking to beg/end at 0 should be valid and keep position at 0.
  EXPECT_EQ(0, io.seek(0, BasicIo::beg));
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());

  EXPECT_EQ(0, io.seek(0, BasicIo::end));
  EXPECT_EQ(0u, io.tell());
  EXPECT_FALSE(io.eof());

  // Any positive seek beyond end should fail and set eof.
  const size_t before = io.tell();
  EXPECT_EQ(1, io.seek(1, BasicIo::beg));
  EXPECT_EQ(before, io.tell());
  EXPECT_TRUE(io.eof());

  // Negative should fail (before beginning) and not move.
  const size_t before2 = io.tell();
  EXPECT_EQ(1, io.seek(-1, BasicIo::beg));
  EXPECT_EQ(before2, io.tell());
}

}  // namespace