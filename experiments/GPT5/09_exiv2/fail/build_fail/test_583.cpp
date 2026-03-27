// TEST_ID 583
// Unit tests for Exiv2::MemIo::munmap()
// File: test_memio_munmap_583.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

class MemIoMunmapTest_583 : public ::testing::Test {
 protected:
  Exiv2::MemIo io_;
};

TEST_F(MemIoMunmapTest_583, MunmapOnFreshInstanceReturnsZero_583) {
  // Observable behavior: return value
  EXPECT_EQ(0, io_.munmap());
}

TEST_F(MemIoMunmapTest_583, MunmapCanBeCalledRepeatedlyReturnsZero_583) {
  EXPECT_EQ(0, io_.munmap());
  EXPECT_EQ(0, io_.munmap());
  EXPECT_EQ(0, io_.munmap());
}

TEST_F(MemIoMunmapTest_583, MunmapAfterOpenCloseReturnsZero_583) {
  // We do not assume open/close semantics beyond being callable.
  (void)io_.open();
  (void)io_.close();

  EXPECT_EQ(0, io_.munmap());
}

TEST_F(MemIoMunmapTest_583, MunmapAfterMmapUnnamedFalseReturnsZero_583) {
  // We do not assert on returned pointer (may be nullptr depending on state).
  (void)io_.mmap(false);

  EXPECT_EQ(0, io_.munmap());
}

TEST_F(MemIoMunmapTest_583, MunmapAfterMmapUnnamedTrueReturnsZero_583) {
  (void)io_.mmap(true);

  EXPECT_EQ(0, io_.munmap());
}

TEST_F(MemIoMunmapTest_583, MunmapAfterMultipleMmapCallsReturnsZero_583) {
  (void)io_.mmap(false);
  (void)io_.mmap(true);
  (void)io_.mmap(false);

  EXPECT_EQ(0, io_.munmap());
}

TEST_F(MemIoMunmapTest_583, MunmapAfterMmapThenRepeatedMunmapReturnsZero_583) {
  (void)io_.mmap(false);

  EXPECT_EQ(0, io_.munmap());
  EXPECT_EQ(0, io_.munmap());  // boundary: repeated unmap
}

TEST_F(MemIoMunmapTest_583, MunmapAfterPopulateFakeDataReturnsZero_583) {
  // If supported, fake data population should not make munmap fail.
  io_.populateFakeData();

  EXPECT_EQ(0, io_.munmap());
}

TEST_F(MemIoMunmapTest_583, MunmapDoesNotThrow_583) {
  EXPECT_NO_THROW({
    (void)io_.munmap();
  });
}

}  // namespace