// File: test_tiffheaderbase_print_1171.cpp
// TEST_ID: 1171

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

#include "tiffimage_int.hpp"  // Exiv2::Internal::TiffHeaderBase
#include "exiv2/types.hpp"    // Exiv2::ByteOrder

using ::testing::HasSubstr;
using ::testing::Not;

namespace {

class TiffHeaderBaseTest_1171 : public ::testing::Test {
 protected:
  static std::string PrintToString(const Exiv2::Internal::TiffHeaderBase& hdr, const char* prefix) {
    std::ostringstream os;
    hdr.print(os, prefix);
    return os.str();
  }
};

TEST_F(TiffHeaderBaseTest_1171, PrintLittleEndianIncludesOffsetAndLittleEndianText_1171) {
  const uint16_t tag = 0x1234;
  const uint32_t size = 8;
  const uint32_t offset = 0x00000010;

  Exiv2::Internal::TiffHeaderBase hdr(tag, size, Exiv2::littleEndian, offset);

  const std::string out = PrintToString(hdr, "PFX: ");

  EXPECT_THAT(out, HasSubstr("PFX: "));
  EXPECT_THAT(out, HasSubstr("0x00000010"));
  EXPECT_THAT(out, HasSubstr("little endian"));
  EXPECT_THAT(out, HasSubstr("\n"));
}

TEST_F(TiffHeaderBaseTest_1171, PrintBigEndianIncludesOffsetAndBigEndianText_1171) {
  Exiv2::Internal::TiffHeaderBase hdr(/*tag=*/0x0001, /*size=*/4, Exiv2::bigEndian, /*offset=*/0x00000020);

  const std::string out = PrintToString(hdr, "");

  EXPECT_THAT(out, HasSubstr("0x00000020"));
  EXPECT_THAT(out, HasSubstr("big endian"));
  EXPECT_THAT(out, HasSubstr("\n"));
}

TEST_F(TiffHeaderBaseTest_1171, PrintInvalidByteOrderOmitsEndianText_1171) {
  Exiv2::Internal::TiffHeaderBase hdr(/*tag=*/0x0001, /*size=*/4, Exiv2::invalidByteOrder, /*offset=*/0x00000000);

  const std::string out = PrintToString(hdr, "hdr");

  EXPECT_THAT(out, HasSubstr("0x00000000"));
  EXPECT_THAT(out, Not(HasSubstr("little endian")));
  EXPECT_THAT(out, Not(HasSubstr("big endian")));
  EXPECT_THAT(out, HasSubstr("\n"));
}

TEST_F(TiffHeaderBaseTest_1171, PrintFormatsOffsetAsEightHexDigits_BoundaryZero_1171) {
  Exiv2::Internal::TiffHeaderBase hdr(/*tag=*/0x0001, /*size=*/4, Exiv2::littleEndian, /*offset=*/0u);

  const std::string out = PrintToString(hdr, "");

  // Observable formatting: 0x{:08x}
  EXPECT_THAT(out, HasSubstr("0x00000000"));
}

TEST_F(TiffHeaderBaseTest_1171, PrintFormatsOffsetAsEightHexDigits_BoundaryMaxUint32_1171) {
  const uint32_t maxOff = std::numeric_limits<uint32_t>::max();
  Exiv2::Internal::TiffHeaderBase hdr(/*tag=*/0x0001, /*size=*/4, Exiv2::bigEndian, /*offset=*/maxOff);

  const std::string out = PrintToString(hdr, "X");

  EXPECT_THAT(out, HasSubstr("0xffffffff"));
}

TEST_F(TiffHeaderBaseTest_1171, SetOffsetAffectsPrintedOffset_ExternalObservableEffect_1171) {
  Exiv2::Internal::TiffHeaderBase hdr(/*tag=*/0x0001, /*size=*/4, Exiv2::littleEndian, /*offset=*/0x00000001);

  const std::string before = PrintToString(hdr, "");
  EXPECT_THAT(before, HasSubstr("0x00000001"));

  hdr.setOffset(0x000000AB);

  const std::string after = PrintToString(hdr, "");
  EXPECT_THAT(after, HasSubstr("0x000000ab"));
}

TEST_F(TiffHeaderBaseTest_1171, SetByteOrderAffectsPrintedEndianText_ExternalObservableEffect_1171) {
  Exiv2::Internal::TiffHeaderBase hdr(/*tag=*/0x0001, /*size=*/4, Exiv2::littleEndian, /*offset=*/0x10);

  const std::string before = PrintToString(hdr, "");
  EXPECT_THAT(before, HasSubstr("little endian"));
  EXPECT_THAT(before, Not(HasSubstr("big endian")));

  hdr.setByteOrder(Exiv2::bigEndian);

  const std::string after = PrintToString(hdr, "");
  EXPECT_THAT(after, HasSubstr("big endian"));
  EXPECT_THAT(after, Not(HasSubstr("little endian")));
}

}  // namespace