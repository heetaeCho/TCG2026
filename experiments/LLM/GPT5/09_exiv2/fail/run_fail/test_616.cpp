// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_remoteio_eof_616.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace {

class RemoteIoTest_616 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoTest_616, EofIsBoolLikeAndCallableOnConst_616) {
  static_assert(std::is_convertible_v<decltype(std::declval<const Exiv2::RemoteIo&>().eof()), bool>,
                "RemoteIo::eof() must be convertible to bool");

  const Exiv2::RemoteIo& cio = io_;
  EXPECT_NO_THROW({
    (void)cio.eof();
  });
}

TEST_F(RemoteIoTest_616, EofIsStableAcrossRepeatedCalls_616) {
  const bool first = io_.eof();
  const bool second = io_.eof();
  EXPECT_EQ(first, second);
}

TEST_F(RemoteIoTest_616, ReadZeroBytesDoesNotChangeEofState_616) {
  // Use only public interface; do not assume open() is required.
  EXPECT_NO_THROW(io_.populateFakeData());

  const bool before = io_.eof();

  // DataBuf read(0)
  EXPECT_NO_THROW({
    (void)io_.read(static_cast<size_t>(0));
  });

  // size_t read(buf, 0)
  std::vector<Exiv2::byte> buf(1, 0);
  EXPECT_NO_THROW({
    (void)io_.read(buf.data(), static_cast<size_t>(0));
  });

  const bool after = io_.eof();
  EXPECT_EQ(before, after);
}

TEST_F(RemoteIoTest_616, ConsumingUntilEndEventuallySetsEofTrue_616) {
  EXPECT_NO_THROW(io_.populateFakeData());

  // If open/isopen/size are meaningful in this implementation, use them; otherwise remain black-box safe.
  (void)io_.open();

  const size_t sz = io_.size();
  if (sz == 0) {
    // Without data, we can't meaningfully drive EOF via consumption through the public API.
    GTEST_SKIP() << "RemoteIo::size() returned 0; cannot validate EOF transition via reads.";
  }

  // Drive reads via getb() up to a bounded number of iterations.
  // We do NOT assume any specific sentinel, but typical implementations return <0 at EOF.
  bool sawEndIndicator = false;
  const size_t maxIters = sz + 8;  // small cushion beyond size()
  for (size_t i = 0; i < maxIters; ++i) {
    const int v = io_.getb();
    if (v < 0) {
      sawEndIndicator = true;
      break;
    }
  }

  // Whether or not getb() uses a negative sentinel, eof() should be observable once we've exhausted data
  // (or attempted beyond it) via the public interface.
  EXPECT_TRUE(io_.eof());

  // If we observed an explicit end indicator, subsequent eof() should remain true.
  if (sawEndIndicator) {
    EXPECT_TRUE(io_.eof());
  }
}

TEST_F(RemoteIoTest_616, EofCallableAfterClose_616) {
  EXPECT_NO_THROW(io_.populateFakeData());

  (void)io_.open();
  EXPECT_NO_THROW((void)io_.close());

  // Do not assume any particular eof() value after close; only that it is callable/observable.
  EXPECT_NO_THROW({
    const bool e = io_.eof();
    (void)e;
  });
}

}  // namespace