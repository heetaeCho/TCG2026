// File: test_memio_write_577.cpp
// Unit tests for Exiv2::MemIo::write(const byte*, size_t)
//
// Constraints respected:
// - Treat implementation as black box (assert only via public API: write/seek/read/tell/size).
// - No private state access.
// - No internal logic re-implementation.

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::byte;
using Exiv2::MemIo;

class MemIoWriteTest_577 : public ::testing::Test {
 protected:
  MemIo io_;
};

TEST_F(MemIoWriteTest_577, WriteReturnsCountAndBytesAreReadable_577) {
  const std::array<byte, 3> in{{static_cast<byte>('a'), static_cast<byte>('b'), static_cast<byte>('c')}};

  const size_t written = io_.write(in.data(), in.size());
  EXPECT_EQ(written, in.size());

  ASSERT_EQ(0, io_.seek(0, Exiv2::BasicIo::beg));

  std::array<byte, 3> out{{0, 0, 0}};
  const size_t read = io_.read(out.data(), out.size());
  EXPECT_EQ(read, out.size());
  EXPECT_EQ(out, in);
}

TEST_F(MemIoWriteTest_577, WriteZeroCountDoesNotChangeTellOrSize_577) {
  const size_t tell_before = io_.tell();
  const size_t size_before = io_.size();

  const std::array<byte, 1> dummy{{static_cast<byte>('x')}};
  const size_t written = io_.write(dummy.data(), 0);
  EXPECT_EQ(written, 0u);

  EXPECT_EQ(io_.tell(), tell_before);
  EXPECT_EQ(io_.size(), size_before);
}

TEST_F(MemIoWriteTest_577, WriteNullptrWithNonzeroCountAdvancesTellAndSizeAtLeastTell_577) {
  const size_t tell_before = io_.tell();
  const size_t size_before = io_.size();

  const size_t written = io_.write(nullptr, 5);
  EXPECT_EQ(written, 5u);

  EXPECT_EQ(io_.tell(), tell_before + 5u);
  EXPECT_GE(io_.size(), io_.tell());
  EXPECT_GE(io_.size(), size_before);  // size should not shrink
}

TEST_F(MemIoWriteTest_577, MultipleWritesProduceConcatenatedStreamReadableFromBeginning_577) {
  const std::array<byte, 2> first{{static_cast<byte>('h'), static_cast<byte>('i')}};
  const std::array<byte, 1> second{{static_cast<byte>('!')}};

  EXPECT_EQ(io_.write(first.data(), first.size()), first.size());
  EXPECT_EQ(io_.write(second.data(), second.size()), second.size());

  ASSERT_EQ(0, io_.seek(0, Exiv2::BasicIo::beg));

  std::array<byte, 3> out{{0, 0, 0}};
  EXPECT_EQ(io_.read(out.data(), out.size()), out.size());

  const std::array<byte, 3> expected{{static_cast<byte>('h'), static_cast<byte>('i'), static_cast<byte>('!')}};
  EXPECT_EQ(out, expected);
}

TEST_F(MemIoWriteTest_577, WriteAfterSeekUpdatesTellToSeekPositionPlusBytesWritten_577) {
  const std::array<byte, 6> initial{
      {static_cast<byte>('a'), static_cast<byte>('b'), static_cast<byte>('c'),
       static_cast<byte>('d'), static_cast<byte>('e'), static_cast<byte>('f')}};
  ASSERT_EQ(io_.write(initial.data(), initial.size()), initial.size());

  ASSERT_EQ(0, io_.seek(2, Exiv2::BasicIo::beg));
  const std::array<byte, 2> patch{{static_cast<byte>('Z'), static_cast<byte>('Z')}};
  EXPECT_EQ(io_.write(patch.data(), patch.size()), patch.size());

  EXPECT_EQ(io_.tell(), 4u);          // observable position after seek(2) then write(2)
  EXPECT_GE(io_.size(), io_.tell());  // size should be at least current position
}

}  // namespace