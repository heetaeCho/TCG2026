// =================================================================================================
// TEST_ID: 593
// Unit tests for Exiv2::MemIo::eof()
// File: test_memio_eof_593.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstddef>
#include <cstdint>
#include <vector>

namespace {

// Small helper to build deterministic test data.
static std::vector<Exiv2::byte> MakeBytes(std::size_t n) {
  std::vector<Exiv2::byte> v(n);
  for (std::size_t i = 0; i < n; ++i) {
    v[i] = static_cast<Exiv2::byte>(i & 0xFF);
  }
  return v;
}

class MemIoEofTest_593 : public ::testing::Test {
 protected:
  // Best-effort open; tests never assert a specific return code (black-box).
  static void TryOpen(Exiv2::MemIo& io) { (void)io.open(); }
};

}  // namespace

TEST_F(MemIoEofTest_593, EofIsCallableOnConstAndIsStableAcrossCalls_593) {
  const auto data = MakeBytes(8);
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  const Exiv2::MemIo& cio = io;
  const bool e1 = cio.eof();
  const bool e2 = cio.eof();

  // Observable behavior: repeated calls without intervening operations should be consistent.
  EXPECT_EQ(e1, e2);
}

TEST_F(MemIoEofTest_593, EofBecomesTrueAfterReadPastEnd_593) {
  const auto data = MakeBytes(4);
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  std::vector<Exiv2::byte> buf(data.size());
  const std::size_t read_full = io.read(buf.data(), buf.size());
  EXPECT_EQ(read_full, buf.size());

  // Attempt to read past the end.
  Exiv2::byte one{};
  const std::size_t read_past = io.read(&one, 1);

  // Observable expectation: reading past the end should not produce data.
  EXPECT_EQ(read_past, 0u);

  // And EOF should be observable as true after the past-end read attempt.
  EXPECT_TRUE(io.eof());
}

TEST_F(MemIoEofTest_593, EofBecomesTrueAfterGetbPastEnd_593) {
  const auto data = MakeBytes(5);
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  // Read until we've consumed "size()" bytes, then do one more read.
  const std::size_t n = io.size();
  for (std::size_t i = 0; i < n; ++i) {
    (void)io.getb();
  }
  (void)io.getb();  // one past end

  // Observable behavior: EOF should be set after reading past end.
  EXPECT_TRUE(io.eof());
}

TEST_F(MemIoEofTest_593, EmptyBufferReadSetsEof_593) {
  // Boundary condition: size == 0
  Exiv2::MemIo io(nullptr, 0);
  TryOpen(io);

  Exiv2::byte b{};
  const std::size_t nread = io.read(&b, 1);

  EXPECT_EQ(nread, 0u);
  EXPECT_TRUE(io.eof());
}

TEST_F(MemIoEofTest_593, EofCanBeClearedBySeekingBackToBeginningIfSupported_593) {
  const auto data = MakeBytes(3);
  Exiv2::MemIo io(data.data(), data.size());
  TryOpen(io);

  // Drive to EOF via read-past-end.
  std::vector<Exiv2::byte> buf(data.size());
  EXPECT_EQ(io.read(buf.data(), buf.size()), buf.size());
  Exiv2::byte one{};
  (void)io.read(&one, 1);
  ASSERT_TRUE(io.eof());

  // Attempt to seek back to the beginning. Do not assert specific return code.
  // If seek succeeds, EOF should no longer be true after a successful reposition and read attempt.
  const int seek_rc = io.seek(0, Exiv2::beg);

  if (seek_rc == 0) {
    // After successful seek, attempt a valid read; EOF should not remain stuck at true.
    Exiv2::byte x{};
    const std::size_t r = io.read(&x, 1);
    EXPECT_EQ(r, 1u);
    EXPECT_FALSE(io.eof());
  } else {
    // If seeking is not supported in this state/config, at least verify EOF remains a valid boolean.
    EXPECT_TRUE(io.eof());
  }
}