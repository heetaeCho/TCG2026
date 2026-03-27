// SPDX-License-Identifier: GPL-2.0-or-later
// File: ./TestProjects/exiv2/src/makernote_int_test_1452.cpp

#include <gtest/gtest.h>

#include "basicio.hpp"
#include "iowrapper.hpp"
#include "makernote_int.hpp"
#include "types.hpp"

namespace {

// NOTE: We treat OMSystemMnHeader as a black box.
// We only verify observable behavior through its public interface:
// - return value from write()
// - effects on the provided IoWrapper/underlying BasicIo (MemIo)

class OMSystemMnHeaderTest_1452 : public ::testing::Test {
 protected:
  Exiv2::MemIo memIo_;
  Exiv2::Internal::IoWrapper ioWrapper_{memIo_};
  Exiv2::Internal::OMSystemMnHeader header_{};
};

}  // namespace

TEST_F(OMSystemMnHeaderTest_1452, WriteToEmptyMemIoReturnsBytesWritten_1452) {
  // Precondition: empty backing store
  EXPECT_EQ(0u, memIo_.size());

  const size_t written = header_.write(ioWrapper_, Exiv2::littleEndian);

  // Observable behavior: returns a size, and backing store grows accordingly.
  EXPECT_GT(written, 0u);
  EXPECT_EQ(written, memIo_.size());
}

TEST_F(OMSystemMnHeaderTest_1452, WriteIsConsistentAcrossByteOrders_1452) {
  const size_t writtenLE = header_.write(ioWrapper_, Exiv2::littleEndian);
  ASSERT_GT(writtenLE, 0u);

  const size_t sizeAfterLE = memIo_.size();
  ASSERT_EQ(writtenLE, sizeAfterLE);

  // Write again using a different ByteOrder. We don't assume internal logic,
  // only that it performs a write and returns a size.
  const size_t writtenBE = header_.write(ioWrapper_, Exiv2::bigEndian);
  EXPECT_GT(writtenBE, 0u);

  // We don't assume whether the second write appends or overwrites, but size
  // should not shrink and must be at least the size after the first write.
  EXPECT_GE(memIo_.size(), sizeAfterLE);

  // Return value is expected to be the number of bytes attempted to write for
  // the header. We only assert it matches the first call's returned size,
  // since the interface suggests a fixed signature size.
  EXPECT_EQ(writtenLE, writtenBE);
}