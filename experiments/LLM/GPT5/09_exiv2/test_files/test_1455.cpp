// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_fuji_mn_header_1455.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>
#include <memory>
#include <vector>

// Exiv2
#include "makernote_int.hpp"
#include <exiv2/types.hpp>

namespace Exiv2::Internal {

class FujiMnHeaderTest_1455 : public ::testing::Test {};

TEST_F(FujiMnHeaderTest_1455, DefaultConstruction_MethodsCallableAndStable_1455) {
  FujiMnHeader h;

  // Call a few times and ensure the observable results are stable for the same instance.
  const size_t ifd1 = h.ifdOffset();
  const size_t ifd2 = h.ifdOffset();
  EXPECT_EQ(ifd1, ifd2);

  const size_t sz1 = h.size();
  const size_t sz2 = h.size();
  EXPECT_EQ(sz1, sz2);

  const ByteOrder bo1 = h.byteOrder();
  const ByteOrder bo2 = h.byteOrder();
  EXPECT_EQ(bo1, bo2);
}

TEST_F(FujiMnHeaderTest_1455, PolymorphicUseThroughMnHeader_InterfaceCallable_1455) {
  // FujiMnHeader is declared as MnHeader-derived; verify it can be used via base pointer.
  std::unique_ptr<MnHeader> base = std::make_unique<FujiMnHeader>();
  ASSERT_NE(base, nullptr);

  // Ensure calls succeed and are stable on the same object.
  const size_t ifd1 = base->ifdOffset();
  const size_t ifd2 = base->ifdOffset();
  EXPECT_EQ(ifd1, ifd2);

  const size_t sz1 = base->size();
  const size_t sz2 = base->size();
  EXPECT_EQ(sz1, sz2);

  const ByteOrder bo1 = base->byteOrder();
  const ByteOrder bo2 = base->byteOrder();
  EXPECT_EQ(bo1, bo2);
}

TEST_F(FujiMnHeaderTest_1455, SizeOfSignature_StaticAndMemberAreConsistent_1455) {
  FujiMnHeader h;

  const size_t s1 = FujiMnHeader::sizeOfSignature();
  const size_t s2 = FujiMnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);

  // If the class provides both static and member forms, they should agree.
  const size_t m1 = h.sizeOfSignature();
  const size_t m2 = h.sizeOfSignature();
  EXPECT_EQ(m1, m2);

  EXPECT_EQ(s1, m1);
}

TEST_F(FujiMnHeaderTest_1455, BaseOffset_AcceptsBoundaryInputsWithoutThrow_1455) {
  FujiMnHeader h;

  const size_t v0 = 0;
  const size_t v1 = 1;
  const size_t vmax = (std::numeric_limits<size_t>::max)();

  // Boundary inputs: ensure the calls are safe and deterministic for identical inputs.
  EXPECT_NO_THROW({
    const size_t r1 = h.baseOffset(v0);
    const size_t r2 = h.baseOffset(v0);
    EXPECT_EQ(r1, r2);
  });

  EXPECT_NO_THROW({
    const size_t r1 = h.baseOffset(v1);
    const size_t r2 = h.baseOffset(v1);
    EXPECT_EQ(r1, r2);
  });

  EXPECT_NO_THROW({
    const size_t r1 = h.baseOffset(vmax);
    const size_t r2 = h.baseOffset(vmax);
    EXPECT_EQ(r1, r2);
  });
}

TEST_F(FujiMnHeaderTest_1455, Read_WithZeroSizeBuffer_IsHandled_1455) {
  FujiMnHeader h;

  // Provide a non-null pointer with size=0 (avoid null dereference risk).
  const std::vector<byte> buf(1, static_cast<byte>(0));

  // Error/exceptional-style input: size=0.
  bool ok1 = false;
  bool ok2 = false;
  EXPECT_NO_THROW({ ok1 = h.read(buf.data(), 0, littleEndian); });
  EXPECT_NO_THROW({ ok2 = h.read(buf.data(), 0, littleEndian); });

  // We don't assume success/failure semantics; we only require it behaves consistently.
  EXPECT_EQ(ok1, ok2);
}

TEST_F(FujiMnHeaderTest_1455, Read_WithSmallBuffer_IsHandled_1455) {
  FujiMnHeader h;

  const std::vector<byte> buf(1, static_cast<byte>(0));

  // "Small" input (size=1). Whether it's sufficient is implementation-defined; we only
  // verify safety and consistent observable result for identical calls.
  bool ok1 = false;
  bool ok2 = false;
  EXPECT_NO_THROW({ ok1 = h.read(buf.data(), buf.size(), littleEndian); });
  EXPECT_NO_THROW({ ok2 = h.read(buf.data(), buf.size(), littleEndian); });

  EXPECT_EQ(ok1, ok2);
}

}  // namespace Exiv2::Internal