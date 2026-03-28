// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tags_int_printBitmask_1373.cpp
//
// Unit tests for Exiv2::Internal::printBitmask (./TestProjects/exiv2/src/tags_int.cpp)
//
// Constraints honored:
// - Treat implementation as black box
// - Use only public/visible interfaces (Value/ExifData + observable stream output)
// - No private state access

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Function under test (implemented in tags_int.cpp)
std::ostream& printBitmask(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class PrintBitmaskTest_1373 : public ::testing::Test {
 protected:
  static std::string Render(const Exiv2::Value& v, const Exiv2::ExifData* md = nullptr) {
    std::ostringstream os;
    Exiv2::Internal::printBitmask(os, v, md);
    return os.str();
  }

  static std::unique_ptr<Exiv2::Value> MakeValue(Exiv2::TypeId type, const std::string& input) {
    auto up = Exiv2::Value::create(type);
    EXPECT_NE(up.get(), nullptr);
    // Rely only on the public Value interface; specific parsing behavior is library-defined.
    const int rc = up->read(input);
    EXPECT_EQ(rc, 0);
    return std::unique_ptr<Exiv2::Value>(up.release());
  }

  static std::string Join0to15() {
    std::ostringstream os;
    for (int i = 0; i < 16; ++i) {
      if (i) os << ",";
      os << i;
    }
    return os.str();
  }
};

TEST_F(PrintBitmaskTest_1373, ReturnsSameStreamReference_1373) {
  auto v = MakeValue(Exiv2::unsignedShort, "1");
  std::ostringstream os;
  std::ostream& ref = Exiv2::Internal::printBitmask(os, *v, nullptr);
  EXPECT_EQ(&ref, &os);
}

TEST_F(PrintBitmaskTest_1373, UnsignedShort_ZeroBits_PrintsNone_1373) {
  // Bitmask path: unsignedShort; if no bits are set across all elements -> "(none)"
  auto v = MakeValue(Exiv2::unsignedShort, "0");
  EXPECT_EQ(Render(*v), "(none)");
}

TEST_F(PrintBitmaskTest_1373, UnsignedShort_SingleLowestBit_PrintsIndex0_1373) {
  auto v = MakeValue(Exiv2::unsignedShort, "1");  // 0b...0001
  EXPECT_EQ(Render(*v), "0");
}

TEST_F(PrintBitmaskTest_1373, UnsignedShort_TwoLowestBits_PrintsCommaSeparatedIndices_1373) {
  auto v = MakeValue(Exiv2::unsignedShort, "3");  // 0b...0011 => bits 0 and 1
  EXPECT_EQ(Render(*v), "0,1");
}

TEST_F(PrintBitmaskTest_1373, UnsignedShort_HighestBitOnly_PrintsIndex15_1373) {
  auto v = MakeValue(Exiv2::unsignedShort, "32768");  // 1 << 15
  EXPECT_EQ(Render(*v), "15");
}

TEST_F(PrintBitmaskTest_1373, UnsignedShort_TwoElements_BitIndexContinuesAcrossElements_1373) {
  // The implementation increments a global "bit" counter across all elements (16 bits each).
  // element0: bit0 set => index 0
  // element1: bit0 set => index 16
  auto v = MakeValue(Exiv2::unsignedShort, "1 1");
  EXPECT_EQ(Render(*v), "0,16");
}

TEST_F(PrintBitmaskTest_1373, UnsignedShort_TwoElements_MixedBitsAcrossElements_1373) {
  // element0: 0x0002 => index 1
  // element1: 0x8000 => index 16+15 = 31
  auto v = MakeValue(Exiv2::unsignedShort, "2 32768");
  EXPECT_EQ(Render(*v), "1,31");
}

TEST_F(PrintBitmaskTest_1373, SignedShort_NegativeOne_PrintsAllBitIndices0to15_1373) {
  // For signedShort, the implementation casts value.toInt64(i) to uint16_t.
  // -1 should become 0xFFFF => all 16 bits set.
  auto v = MakeValue(Exiv2::signedShort, "-1");
  EXPECT_EQ(Render(*v), Join0to15());
}

TEST_F(PrintBitmaskTest_1373, SignedShort_Zero_PrintsNone_1373) {
  auto v = MakeValue(Exiv2::signedShort, "0");
  EXPECT_EQ(Render(*v), "(none)");
}

TEST_F(PrintBitmaskTest_1373, UnsignedShort_EmptyValueArray_PrintsNone_1373) {
  // Boundary: count() == 0 should result in "(none)" (no bits encountered).
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  EXPECT_EQ(Render(*v), "(none)");
}

TEST_F(PrintBitmaskTest_1373, NonShortType_DelegatesToGenericPrinting_NotNoneForNonZero_1373) {
  // Else-branch: for non-(un/signed)Short types it delegates to printValue(...).
  // We only assert observable output is not the bitmask "(none)" for a non-zero value.
  auto v = MakeValue(Exiv2::unsignedLong, "1");
  const std::string out = Render(*v);
  EXPECT_NE(out, "(none)");
  EXPECT_FALSE(out.empty());
}

}  // namespace