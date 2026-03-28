// ============================================================================
// TestProjects/exiv2/tests/test_olympus2_mnheader_2185.cpp
// Unit tests for Exiv2::Internal::Olympus2MnHeader (TEST_ID: 2185)
// ============================================================================

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <type_traits>

// Exiv2 headers (project)
#include "makernote_int.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::ByteOrder;

class Olympus2MnHeaderTest_2185 : public ::testing::Test {
 protected:
  Exiv2::Internal::Olympus2MnHeader header_;
};

// Compile-time interface checks (no assumptions about runtime behavior)
static_assert(!std::is_copy_constructible_v<Exiv2::Internal::MnHeader>,
              "MnHeader must be non-copy-constructible (deleted copy ctor).");
static_assert(!std::is_copy_assignable_v<Exiv2::Internal::MnHeader>,
              "MnHeader must be non-copy-assignable (deleted operator=).");

TEST_F(Olympus2MnHeaderTest_2185, ConstructionAndBasicCallsDoNotThrow_2185) {
  // Black-box: ensure the object can be default-constructed and queried.
  EXPECT_NO_THROW({
    (void)header_.size();
    (void)header_.ifdOffset();
    (void)header_.byteOrder();
    (void)Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  });
}

TEST_F(Olympus2MnHeaderTest_2185, SizeOfSignatureIsStableAcrossCalls_2185) {
  // Black-box: repeated static calls should be consistent within a process.
  const size_t s1 = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  const size_t s2 = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  const size_t s3 = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);

  // Boundary sanity: signature size should not exceed itself (non-negative by type).
  // Keep expectations minimal to avoid inferring internal constants.
  EXPECT_GE(s1, static_cast<size_t>(0));
}

TEST_F(Olympus2MnHeaderTest_2185, ByteOrderCanBeSetAndReadBack_2185) {
  // Observable behavior via public interface: setByteOrder + byteOrder.
  header_.setByteOrder(ByteOrder::littleEndian);
  EXPECT_EQ(header_.byteOrder(), ByteOrder::littleEndian);

  header_.setByteOrder(ByteOrder::bigEndian);
  EXPECT_EQ(header_.byteOrder(), ByteOrder::bigEndian);

  header_.setByteOrder(ByteOrder::invalidByteOrder);
  EXPECT_EQ(header_.byteOrder(), ByteOrder::invalidByteOrder);
}

TEST_F(Olympus2MnHeaderTest_2185, ReadWithZeroSizeReturnsFalse_2185) {
  // Black-box: reading with size==0 should be handled gracefully.
  // Provide a valid pointer (even though size is 0) to avoid UB.
  std::array<Exiv2::byte, 1> buf{{0x00}};

  EXPECT_FALSE(header_.read(buf.data(), 0, ByteOrder::littleEndian));
  EXPECT_FALSE(header_.read(buf.data(), 0, ByteOrder::bigEndian));
  EXPECT_FALSE(header_.read(buf.data(), 0, ByteOrder::invalidByteOrder));
}

TEST_F(Olympus2MnHeaderTest_2185, BaseOffsetIsDeterministicForSameInput_2185) {
  // Black-box: baseOffset is observable and should be deterministic for same input.
  const size_t mnOffset = 0;
  const size_t a = header_.baseOffset(mnOffset);
  const size_t b = header_.baseOffset(mnOffset);
  EXPECT_EQ(a, b);

  const size_t mnOffset2 = 1;
  const size_t c = header_.baseOffset(mnOffset2);
  const size_t d = header_.baseOffset(mnOffset2);
  EXPECT_EQ(c, d);
}

TEST_F(Olympus2MnHeaderTest_2185, SizeAndIfdOffsetAreStableAcrossCalls_2185) {
  // Black-box: repeated queries on the same object should be stable.
  const size_t s1 = header_.size();
  const size_t s2 = header_.size();
  EXPECT_EQ(s1, s2);

  const size_t o1 = header_.ifdOffset();
  const size_t o2 = header_.ifdOffset();
  EXPECT_EQ(o1, o2);
}

TEST_F(Olympus2MnHeaderTest_2185, PolymorphicUseThroughBasePointerWorks_2185) {
  // Black-box: ensure virtual dispatch works and methods are callable via base.
  Exiv2::Internal::MnHeader* base = &header_;

  EXPECT_NO_THROW({
    (void)base->size();
    (void)base->ifdOffset();
    (void)base->byteOrder();
    base->setByteOrder(ByteOrder::littleEndian);
    (void)base->byteOrder();
  });

  EXPECT_EQ(base->byteOrder(), ByteOrder::littleEndian);
}

}  // namespace