// base_mem_stream_rewind_167_test.cc
// Unit tests for BaseMemStream::rewind (black-box via public interface)

#include <gtest/gtest.h>

#include <cstdio>   // EOF
#include <memory>
#include <vector>

#include "poppler/Stream.h"
#include "poppler/Object.h"

namespace {

// Helper to create a null Object for dict parameter.
// (We keep this minimal; tests interact only through the public interface.)
static Object MakeNullDict() {
  Object o;
  o.initNull();
  return o;
}

class BaseMemStreamTest_167 : public ::testing::Test {
 protected:
  // Keep the backing buffer alive for the lifetime of the stream.
  std::vector<unsigned char> buf_;
};

TEST_F(BaseMemStreamTest_167, RewindReturnsTrueAndResetsToStart_167) {
  buf_ = {'A', 'B', 'C', 'D', 'E'};
  const Goffset start = 0;
  const Goffset length = static_cast<Goffset>(buf_.size());

  BaseMemStream<unsigned char> s(buf_.data(), start, length, MakeNullDict());

  // Consume a couple of bytes to move the position.
  EXPECT_EQ(s.getChar(), 'A');
  EXPECT_EQ(s.getChar(), 'B');
  const Goffset pos_after_reads = s.getPos();
  EXPECT_GT(pos_after_reads, s.getStart());

  // Rewind should be successful and reset observable state.
  EXPECT_TRUE(s.rewind());
  EXPECT_EQ(s.getPos(), s.getStart());
  EXPECT_EQ(s.lookChar(), 'A');
  EXPECT_EQ(s.getChar(), 'A');
}

TEST_F(BaseMemStreamTest_167, RewindFromNonZeroStartResetsToThatStart_167) {
  buf_ = {'A', 'B', 'C', 'D', 'E'};
  const Goffset start = 2;   // expect stream to begin at 'C'
  const Goffset length = 3;  // 'C','D','E'

  BaseMemStream<unsigned char> s(buf_.data(), start, length, MakeNullDict());

  // Verify initial read is from the configured start.
  EXPECT_EQ(s.getStart(), start);
  EXPECT_EQ(s.getPos(), s.getStart());
  EXPECT_EQ(s.lookChar(), 'C');
  EXPECT_EQ(s.getChar(), 'C');
  EXPECT_EQ(s.getChar(), 'D');
  EXPECT_EQ(s.getPos(), s.getStart() + 2);

  // Rewind should take us back to the same (non-zero) start.
  EXPECT_TRUE(s.rewind());
  EXPECT_EQ(s.getPos(), s.getStart());
  EXPECT_EQ(s.lookChar(), 'C');
  EXPECT_EQ(s.getChar(), 'C');
}

TEST_F(BaseMemStreamTest_167, RewindIsIdempotentMultipleCalls_167) {
  buf_ = {'x', 'y', 'z'};
  const Goffset start = 0;
  const Goffset length = static_cast<Goffset>(buf_.size());

  BaseMemStream<unsigned char> s(buf_.data(), start, length, MakeNullDict());

  EXPECT_EQ(s.getChar(), 'x');
  EXPECT_TRUE(s.rewind());
  EXPECT_TRUE(s.rewind());  // calling again should still succeed

  EXPECT_EQ(s.getPos(), s.getStart());
  EXPECT_EQ(s.getChar(), 'x');
}

TEST_F(BaseMemStreamTest_167, RewindWithEmptyLengthStillSucceedsAndEOF_167) {
  // Use a non-null pointer even though length is 0 to avoid undefined behavior
  // from downstream implementations that may still access bufPtr.
  buf_ = {'Q'};
  const Goffset start = 0;
  const Goffset length = 0;

  BaseMemStream<unsigned char> s(buf_.data(), start, length, MakeNullDict());

  // With zero length, reads should indicate EOF (observable behavior).
  EXPECT_EQ(s.lookChar(), EOF);
  EXPECT_EQ(s.getChar(), EOF);

  // Rewind should still return true, and EOF behavior should remain.
  EXPECT_TRUE(s.rewind());
  EXPECT_EQ(s.getPos(), s.getStart());
  EXPECT_EQ(s.lookChar(), EOF);
  EXPECT_EQ(s.getChar(), EOF);
}

}  // namespace