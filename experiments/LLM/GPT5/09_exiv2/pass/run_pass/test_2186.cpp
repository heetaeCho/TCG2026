// =================================================================================================
// TEST_ID: 2186
// Unit tests for Exiv2::Internal::OMSystemMnHeader (black-box; interface-based)
// File under test: ./TestProjects/exiv2/src/makernote_int.cpp (partial)
// Dependencies:     ./TestProjects/exiv2/src/makernote_int.hpp, exiv2/types.hpp
// =================================================================================================

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

// Exiv2 headers (expected to be available in the project include paths)
#include "makernote_int.hpp"
#include "exiv2/types.hpp"

namespace {

// Fixture name must include TEST_ID per user requirement
class OMSystemMnHeaderTest_2186 : public ::testing::Test {};

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::Internal::OMSystemMnHeader;

// Helper: create a byte buffer of arbitrary size
template <std::size_t N>
std::array<Exiv2::byte, N> MakeZeroedBuf() {
  std::array<Exiv2::byte, N> buf{};
  buf.fill(static_cast<Exiv2::byte>(0));
  return buf;
}

}  // namespace

// -------------------------------------------------------------------------------------------------
// Compile-time / interface-contract checks (no internal logic assumptions)
// -------------------------------------------------------------------------------------------------

TEST_F(OMSystemMnHeaderTest_2186, IsNotCopyableOrAssignable_2186) {
  static_assert(!std::is_copy_constructible_v<OMSystemMnHeader>,
                "OMSystemMnHeader should not be copy-constructible (inherits MnHeader copy deleted).");
  static_assert(!std::is_copy_assignable_v<OMSystemMnHeader>,
                "OMSystemMnHeader should not be copy-assignable (inherits MnHeader assignment deleted).");

  SUCCEED();  // Runtime anchor for the test runner.
}

// -------------------------------------------------------------------------------------------------
// Constructor / basic sanity
// -------------------------------------------------------------------------------------------------

TEST_F(OMSystemMnHeaderTest_2186, DefaultConstructionDoesNotThrow_2186) {
  EXPECT_NO_THROW({
    OMSystemMnHeader header;
    (void)header;
  });
}

// -------------------------------------------------------------------------------------------------
// Static signature sizing: only verify observable invariants (determinism + safe range semantics)
// -------------------------------------------------------------------------------------------------

TEST_F(OMSystemMnHeaderTest_2186, SizeOfSignatureIsDeterministic_2186) {
  const std::size_t s1 = OMSystemMnHeader::sizeOfSignature();
  const std::size_t s2 = OMSystemMnHeader::sizeOfSignature();
  const std::size_t s3 = OMSystemMnHeader::sizeOfSignature();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

// -------------------------------------------------------------------------------------------------
// Byte order behavior via base-class API (setByteOrder/byteOrder are part of MnHeader interface)
// -------------------------------------------------------------------------------------------------

TEST_F(OMSystemMnHeaderTest_2186, SetByteOrderRoundTrip_LittleEndian_2186) {
  OMSystemMnHeader header;

  header.setByteOrder(littleEndian);
  EXPECT_EQ(header.byteOrder(), littleEndian);
}

TEST_F(OMSystemMnHeaderTest_2186, SetByteOrderRoundTrip_BigEndian_2186) {
  OMSystemMnHeader header;

  header.setByteOrder(bigEndian);
  EXPECT_EQ(header.byteOrder(), bigEndian);
}

TEST_F(OMSystemMnHeaderTest_2186, SetByteOrderRoundTrip_InvalidByteOrder_2186) {
  OMSystemMnHeader header;

  header.setByteOrder(invalidByteOrder);
  EXPECT_EQ(header.byteOrder(), invalidByteOrder);
}

// -------------------------------------------------------------------------------------------------
// Determinism / stability checks for query-like methods (no assumptions about exact values)
// -------------------------------------------------------------------------------------------------

TEST_F(OMSystemMnHeaderTest_2186, SizeIsStableAcrossCalls_2186) {
  OMSystemMnHeader header;

  const std::size_t s1 = header.size();
  const std::size_t s2 = header.size();
  const std::size_t s3 = header.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(OMSystemMnHeaderTest_2186, IfdOffsetIsStableAcrossCalls_2186) {
  OMSystemMnHeader header;

  const std::size_t o1 = header.ifdOffset();
  const std::size_t o2 = header.ifdOffset();
  const std::size_t o3 = header.ifdOffset();

  EXPECT_EQ(o1, o2);
  EXPECT_EQ(o2, o3);
}

TEST_F(OMSystemMnHeaderTest_2186, BaseOffsetIsDeterministicForSameInput_2186) {
  OMSystemMnHeader header;

  const std::size_t in0 = 0;
  const std::size_t in1 = 1;
  const std::size_t inBig = 123456u;

  EXPECT_EQ(header.baseOffset(in0), header.baseOffset(in0));
  EXPECT_EQ(header.baseOffset(in1), header.baseOffset(in1));
  EXPECT_EQ(header.baseOffset(inBig), header.baseOffset(inBig));
}

// -------------------------------------------------------------------------------------------------
// read(...) boundary / error-oriented tests (observable: return value; avoid guessing true/false)
// -------------------------------------------------------------------------------------------------

TEST_F(OMSystemMnHeaderTest_2186, ReadWithNullptrAndZeroSize_IsSafeAndDeterministic_2186) {
  OMSystemMnHeader header;

  // Boundary inputs: nullptr + size=0 should be handled safely.
  bool r1 = false;
  bool r2 = false;

  EXPECT_NO_THROW({ r1 = header.read(nullptr, 0u, invalidByteOrder); });
  EXPECT_NO_THROW({ r2 = header.read(nullptr, 0u, invalidByteOrder); });

  // We do not assume success/failure; only that behavior is deterministic for identical inputs.
  EXPECT_EQ(r1, r2);
}

TEST_F(OMSystemMnHeaderTest_2186, ReadWithSmallBuffer_IsSafeAndDeterministic_2186) {
  OMSystemMnHeader header;

  // A tiny buffer is a classic boundary case for header parsing.
  auto buf = MakeZeroedBuf<1>();

  bool r1 = false;
  bool r2 = false;

  EXPECT_NO_THROW({ r1 = header.read(buf.data(), buf.size(), invalidByteOrder); });
  EXPECT_NO_THROW({ r2 = header.read(buf.data(), buf.size(), invalidByteOrder); });

  EXPECT_EQ(r1, r2);
}

TEST_F(OMSystemMnHeaderTest_2186, ReadWithSignatureSizedBuffer_IsSafeAndDeterministic_2186) {
  OMSystemMnHeader header;

  const std::size_t sigSize = OMSystemMnHeader::sizeOfSignature();

  // If signature size is 0, fall back to the smallest meaningful buffer.
  const std::size_t n = (sigSize == 0u) ? 1u : sigSize;

  // Use a vector-like fixed upper bound without dynamic allocation assumptions.
  // If sigSize is large, this test still remains black-box; adjust as needed by build constraints.
  // Here we cap at a reasonable compile-time size for safety in unit tests.
  constexpr std::size_t kMaxStackBuf = 256;
  ASSERT_LE(n, kMaxStackBuf) << "Signature size too large for this stack-buffer test; adjust test if needed.";

  std::array<Exiv2::byte, kMaxStackBuf> buf{};
  buf.fill(static_cast<Exiv2::byte>(0));

  bool r1 = false;
  bool r2 = false;

  EXPECT_NO_THROW({ r1 = header.read(buf.data(), n, invalidByteOrder); });
  EXPECT_NO_THROW({ r2 = header.read(buf.data(), n, invalidByteOrder); });

  EXPECT_EQ(r1, r2);
}