// TEST_ID 607
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

class RemoteIoTest_607 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;

  void SetUp() override {
    // Treat as black box: use only public API.
    // populateFakeData() is explicitly exposed; use it to ensure we have readable content.
    io_.populateFakeData();
    (void)io_.open();
  }

  void TearDown() override {
    (void)io_.close();
  }
};

TEST_F(RemoteIoTest_607, GetbConsumesExactlySizeBytesThenReturnsEof_607) {
  const size_t n = io_.size();

  // If the implementation has no data, EOF should be immediate.
  if (n == 0) {
    EXPECT_EQ(io_.getb(), EOF);
    EXPECT_TRUE(io_.eof());
    return;
  }

  // Read exactly size() bytes: none should be EOF.
  for (size_t i = 0; i < n; ++i) {
    const int c = io_.getb();
    EXPECT_NE(c, EOF) << "Unexpected EOF at index " << i << " of " << n;
  }

  // Next byte must be EOF, and eof() should be observable as true.
  EXPECT_EQ(io_.getb(), EOF);
  EXPECT_TRUE(io_.eof());

  // Repeated reads past EOF should continue returning EOF (observable behavior).
  EXPECT_EQ(io_.getb(), EOF);
  EXPECT_TRUE(io_.eof());
}

TEST_F(RemoteIoTest_607, TellAdvancesWithGetbAndDoesNotExceedSize_607) {
  const size_t n = io_.size();

  // tell() is an observable cursor position; it should never exceed size().
  EXPECT_LE(io_.tell(), n);

  // If empty, verify EOF behavior without assuming tell() specifics beyond bounds.
  if (n == 0) {
    (void)io_.getb();
    EXPECT_LE(io_.tell(), n);
    return;
  }

  // Consume some bytes (up to a small prefix), verifying tell stays within [0, size()].
  const size_t steps = (n < 8) ? n : 8;
  for (size_t i = 0; i < steps; ++i) {
    const size_t before = io_.tell();
    const int c = io_.getb();
    ASSERT_NE(c, EOF);
    const size_t after = io_.tell();

    EXPECT_GE(after, before);
    EXPECT_LE(after, n);
  }

  // Drain to the end and verify tell does not go past size.
  while (io_.getb() != EOF) {
    EXPECT_LE(io_.tell(), n);
  }
  EXPECT_LE(io_.tell(), n);
}

TEST_F(RemoteIoTest_607, AfterReopenCanReadAgainUntilEof_607) {
  const size_t n_before = io_.size();

  // Consume everything to reach EOF (or immediate EOF if empty).
  while (io_.getb() != EOF) {
  }
  EXPECT_TRUE(io_.eof() || n_before == 0);

  // Close and reopen; do not assume it resets data content, only that the object remains usable.
  (void)io_.close();
  EXPECT_NO_THROW((void)io_.open());

  const size_t n_after = io_.size();

  // If size is non-zero after reopen, we should be able to read at least one non-EOF byte.
  if (n_after > 0) {
    const int c = io_.getb();
    EXPECT_NE(c, EOF);
  } else {
    EXPECT_EQ(io_.getb(), EOF);
  }
}

TEST_F(RemoteIoTest_607, GetbEofDoesNotChangeSize_607) {
  const size_t n = io_.size();

  // Drive to EOF.
  for (size_t i = 0; i < n; ++i) {
    const int c = io_.getb();
    if (n > 0) {
      ASSERT_NE(c, EOF);
    }
  }
  (void)io_.getb();  // one extra call to ensure EOF state is reached/observed

  // size() is an observable property; reaching EOF should not mutate it.
  EXPECT_EQ(io_.size(), n);
}

}  // namespace