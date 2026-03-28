// TEST_ID 2191
// File: test_PentaxDngMnHeader_2191.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if __has_include("makernote_int.hpp")
#include "makernote_int.hpp"
#elif __has_include("TestProjects/exiv2/src/makernote_int.hpp")
#include "TestProjects/exiv2/src/makernote_int.hpp"
#else
// If your build uses a different include path, adjust accordingly.
#include "makernote_int.hpp"
#endif

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::MnHeader;
using Exiv2::Internal::PentaxDngMnHeader;

class PentaxDngMnHeaderTest_2191 : public ::testing::Test {};

TEST_F(PentaxDngMnHeaderTest_2191, TypeTraits_CopyIsDeleted_2191) {
  EXPECT_FALSE(std::is_copy_constructible<MnHeader>::value);
  EXPECT_FALSE(std::is_copy_assignable<MnHeader>::value);

  EXPECT_FALSE(std::is_copy_constructible<PentaxDngMnHeader>::value);
  EXPECT_FALSE(std::is_copy_assignable<PentaxDngMnHeader>::value);
}

TEST_F(PentaxDngMnHeaderTest_2191, DefaultConstructor_DoesNotThrow_2191) {
  EXPECT_NO_THROW({
    PentaxDngMnHeader h;
    (void)h;
  });
}

TEST_F(PentaxDngMnHeaderTest_2191, SizeOfSignature_IsStableAcrossCalls_2191) {
  const size_t s1 = PentaxDngMnHeader::sizeOfSignature();
  const size_t s2 = PentaxDngMnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);
}

TEST_F(PentaxDngMnHeaderTest_2191, Size_IsStableAcrossCalls_2191) {
  PentaxDngMnHeader h;

  const size_t a = h.size();
  const size_t b = h.size();
  EXPECT_EQ(a, b);

  // Boundary sanity (non-negative by type, but still useful as a guard).
  EXPECT_GE(a, static_cast<size_t>(0));
}

TEST_F(PentaxDngMnHeaderTest_2191, SetByteOrder_ThenByteOrderReflectsIt_2191) {
  PentaxDngMnHeader h;

  h.setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(h.byteOrder(), Exiv2::littleEndian);

  h.setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(h.byteOrder(), Exiv2::bigEndian);

  // Boundary-ish: setting invalid is allowed by enum; ensure it is observable.
  h.setByteOrder(Exiv2::invalidByteOrder);
  EXPECT_EQ(h.byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(PentaxDngMnHeaderTest_2191, IfdOffset_IsDeterministic_2191) {
  PentaxDngMnHeader h;

  const size_t o1 = h.ifdOffset();
  const size_t o2 = h.ifdOffset();
  EXPECT_EQ(o1, o2);
}

TEST_F(PentaxDngMnHeaderTest_2191, BaseOffset_IsDeterministic_ForSameInput_2191) {
  PentaxDngMnHeader h;

  const size_t in = 0;
  const size_t b1 = h.baseOffset(in);
  const size_t b2 = h.baseOffset(in);
  EXPECT_EQ(b1, b2);

  const size_t in2 = static_cast<size_t>(12345);
  const size_t b3 = h.baseOffset(in2);
  const size_t b4 = h.baseOffset(in2);
  EXPECT_EQ(b3, b4);
}

TEST_F(PentaxDngMnHeaderTest_2191, Read_NullDataZeroSize_DoesNotThrow_2191) {
  PentaxDngMnHeader h;

  bool r1 = false;
  bool r2 = true;

  EXPECT_NO_THROW({ r1 = h.read(nullptr, 0u, Exiv2::invalidByteOrder); });
  EXPECT_NO_THROW({ r2 = h.read(nullptr, 0u, Exiv2::invalidByteOrder); });

  // Observable behavior requirement without guessing semantics:
  // the same call should yield the same result.
  EXPECT_EQ(r1, r2);
}

TEST_F(PentaxDngMnHeaderTest_2191, Read_NullDataNonZeroSize_DoesNotThrow_2191) {
  PentaxDngMnHeader h;

  bool r1 = false;
  bool r2 = true;

  EXPECT_NO_THROW({ r1 = h.read(nullptr, 1u, Exiv2::littleEndian); });
  EXPECT_NO_THROW({ r2 = h.read(nullptr, 1u, Exiv2::littleEndian); });

  EXPECT_EQ(r1, r2);
}

TEST_F(PentaxDngMnHeaderTest_2191, Read_SmallBuffer_DoesNotThrow_2191) {
  PentaxDngMnHeader h;

  const unsigned char buf[1] = {0};
#if defined(Exiv2_byte_defined)  // unlikely; keep generic
  const Exiv2::byte* p = reinterpret_cast<const Exiv2::byte*>(buf);
#else
  // Exiv2 typically typedefs/aliases `byte` in its headers; reinterpret safely.
  const auto* p = reinterpret_cast<const unsigned char*>(buf);
#endif

  bool r1 = false;
  bool r2 = true;

  EXPECT_NO_THROW({
    r1 = h.read(reinterpret_cast<const Exiv2::byte*>(p), sizeof(buf), Exiv2::bigEndian);
  });
  EXPECT_NO_THROW({
    r2 = h.read(reinterpret_cast<const Exiv2::byte*>(p), sizeof(buf), Exiv2::bigEndian);
  });

  EXPECT_EQ(r1, r2);
}

}  // namespace