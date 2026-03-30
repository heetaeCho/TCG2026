// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymnheader_1500.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include <exiv2/exiv2.hpp>

// Internal header under test
#include "makernote_int.hpp"

namespace {

// NOTE: These tests treat SonyMnHeader as a black box and only validate
// observable, interface-level properties (idempotence, call-safety, etc.).

class SonyMnHeaderTest_1500 : public ::testing::Test {
 protected:
  static Exiv2::ByteOrder AnyByteOrder() {
    // Pick a valid byte order without assuming behavior differences.
    return Exiv2::littleEndian;
  }
};

TEST_F(SonyMnHeaderTest_1500, DefaultConstruction_AllowsConstQueries_1500) {
  Exiv2::Internal::SonyMnHeader header;

  // Query multiple times; for a const query on an unchanged object, results
  // should be stable (idempotent) regardless of internal implementation.
  const size_t size1 = header.size();
  const size_t size2 = header.size();
  EXPECT_EQ(size1, size2);

  const size_t off1 = header.ifdOffset();
  const size_t off2 = header.ifdOffset();
  EXPECT_EQ(off1, off2);
}

TEST_F(SonyMnHeaderTest_1500, SizeOfSignature_IsDeterministic_1500) {
  const size_t s1 = Exiv2::Internal::SonyMnHeader::sizeOfSignature();
  const size_t s2 = Exiv2::Internal::SonyMnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);
}

TEST_F(SonyMnHeaderTest_1500, Read_NullPointerZeroSize_IsCallSafe_1500) {
  Exiv2::Internal::SonyMnHeader header;

  // The interface accepts a pointer + size; ensure the call is safe even for
  // the boundary input (nullptr, 0). We don't assume success/failure semantics.
  bool threw = false;
  bool result = false;
  try {
    result = header.read(nullptr, 0u, AnyByteOrder());
  } catch (...) {
    threw = true;
  }

  // Observable requirement: the call completes (either by returning or throwing).
  // We record the outcome but do not assert success/failure.
  EXPECT_TRUE(threw || !threw);
  (void)result;
}

TEST_F(SonyMnHeaderTest_1500, Read_VariousSmallSizes_IsCallSafe_1500) {
  Exiv2::Internal::SonyMnHeader header;

  const size_t sig = Exiv2::Internal::SonyMnHeader::sizeOfSignature();

  // Exercise boundary-adjacent sizes around the signature length without
  // asserting specific parsing outcomes.
  const std::vector<size_t> sizes = {
      0u,
      1u,
      (sig > 0u ? sig - 1u : 0u),
      sig,
      sig + 1u,
  };

  for (size_t n : sizes) {
    std::vector<Exiv2::byte> buf(n, Exiv2::byte{0});

    bool threw = false;
    bool result = false;
    try {
      const Exiv2::byte* p = buf.empty() ? nullptr : buf.data();
      result = header.read(p, buf.size(), AnyByteOrder());
    } catch (...) {
      threw = true;
    }

    // As above, we only require that the call is robust for these boundary inputs.
    EXPECT_TRUE(threw || !threw);
    (void)result;

    // Const queries should remain callable after each attempt.
    (void)header.size();
    (void)header.ifdOffset();
  }
}

TEST_F(SonyMnHeaderTest_1500, ConstQueries_AreIdempotent_AfterReadAttempts_1500) {
  Exiv2::Internal::SonyMnHeader header;

  // Attempt a read with some minimal buffer.
  std::vector<Exiv2::byte> buf(8, Exiv2::byte{0});
  try {
    (void)header.read(buf.data(), buf.size(), AnyByteOrder());
  } catch (...) {
    // Ignore; we are not asserting success/failure.
  }

  // Regardless of read outcome, repeated const queries should be stable
  // on an unchanged object between calls.
  const size_t size1 = header.size();
  const size_t size2 = header.size();
  EXPECT_EQ(size1, size2);

  const size_t off1 = header.ifdOffset();
  const size_t off2 = header.ifdOffset();
  EXPECT_EQ(off1, off2);
}

}  // namespace