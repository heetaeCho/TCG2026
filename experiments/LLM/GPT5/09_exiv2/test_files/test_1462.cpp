// =================================================================================================
// TestProjects/exiv2/tests/test_nikon2_mnheader_1462.cpp
// Unit tests for Exiv2::Internal::Nikon2MnHeader (TEST_ID: 1462)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

// Exiv2 internal header under test
#include "makernote_int.hpp"

// Some builds expose ByteOrder via types.hpp; keep this include lightweight and optional.
// If your build already brings ByteOrder in via makernote_int.hpp, this is harmless.
#include "types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::Nikon2MnHeader;

class Nikon2MnHeaderTest_1462 : public ::testing::Test {};

TEST_F(Nikon2MnHeaderTest_1462, DefaultConstruct_IfdOffsetIsStableAndConstConsistent_1462) {
  Nikon2MnHeader header;
  const Nikon2MnHeader& cheader = header;

  // Must be callable and stable (black-box observable behavior).
  const size_t off1 = header.ifdOffset();
  const size_t off2 = header.ifdOffset();
  const size_t offc = cheader.ifdOffset();

  EXPECT_EQ(off1, off2);
  EXPECT_EQ(off1, offc);
}

TEST_F(Nikon2MnHeaderTest_1462, DefaultConstruct_SizeIsStable_1462) {
  Nikon2MnHeader header;
  const Nikon2MnHeader& cheader = header;

  const size_t s1 = header.size();
  const size_t s2 = header.size();
  const size_t sc = cheader.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s1, sc);
}

TEST_F(Nikon2MnHeaderTest_1462, SizeOfSignature_IsStableAndNonZero_1462) {
  const size_t sig1 = Nikon2MnHeader::sizeOfSignature();
  const size_t sig2 = Nikon2MnHeader::sizeOfSignature();

  EXPECT_EQ(sig1, sig2);
  EXPECT_GT(sig1, 0u);
}

TEST_F(Nikon2MnHeaderTest_1462, Read_NullptrZeroSize_DoesNotThrowAndStateRemainsCallable_1462) {
  Nikon2MnHeader header;

  const size_t beforeOff = header.ifdOffset();
  const size_t beforeSize = header.size();

  bool result = false;
  EXPECT_NO_THROW({
    // We do not assume success/failure semantics; we only require it to be safe/callable.
    result = header.read(nullptr, 0u, ByteOrder::littleEndian);
    (void)result;
  });

  // Regardless of read outcome, the public API should remain callable.
  EXPECT_NO_THROW((void)header.ifdOffset());
  EXPECT_NO_THROW((void)header.size());

  // And remain stable across repeated calls.
  EXPECT_EQ(header.ifdOffset(), header.ifdOffset());
  EXPECT_EQ(header.size(), header.size());

  // Not asserting exact values, but sanity: after a no-op-ish read, offsets/sizes should still be
  // well-defined and comparable to themselves.
  (void)beforeOff;
  (void)beforeSize;
}

TEST_F(Nikon2MnHeaderTest_1462, Read_OneByteBuffer_DoesNotThrowAndApiRemainsStable_1462) {
  Nikon2MnHeader header;

  const std::vector<Exiv2::byte> buf(1u, static_cast<Exiv2::byte>(0));

  bool resultLE = false;
  EXPECT_NO_THROW({
    resultLE = header.read(buf.data(), buf.size(), ByteOrder::littleEndian);
    (void)resultLE;
  });

  // Public API remains safe and stable regardless of success/failure.
  const size_t off1 = header.ifdOffset();
  const size_t off2 = header.ifdOffset();
  EXPECT_EQ(off1, off2);

  const size_t s1 = header.size();
  const size_t s2 = header.size();
  EXPECT_EQ(s1, s2);
}

TEST_F(Nikon2MnHeaderTest_1462, Read_SmallBuffer_TryBothByteOrders_NoThrow_1462) {
  Nikon2MnHeader header;

  const std::vector<Exiv2::byte> buf(8u, static_cast<Exiv2::byte>(0));

  bool resultLE = false;
  bool resultBE = false;

  EXPECT_NO_THROW({
    resultLE = header.read(buf.data(), buf.size(), ByteOrder::littleEndian);
    (void)resultLE;
  });

  // Re-initialize a fresh instance for an independent attempt.
  Nikon2MnHeader header2;
  EXPECT_NO_THROW({
    resultBE = header2.read(buf.data(), buf.size(), ByteOrder::bigEndian);
    (void)resultBE;
  });

  // If a read happens to succeed, we can assert a minimal, interface-level invariant:
  // ifdOffset should be a meaningful offset within the header blob being described, so it should
  // not exceed the reported header size.
  if (resultLE) {
    EXPECT_LE(header.ifdOffset(), header.size());
  }
  if (resultBE) {
    EXPECT_LE(header2.ifdOffset(), header2.size());
  }
}

}  // namespace