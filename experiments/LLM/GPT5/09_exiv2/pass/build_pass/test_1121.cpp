// TEST_ID 1121
#include <gtest/gtest.h>

#include <exiv2/types.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>

namespace {

class DataBufWriteUint16Test_1121 : public ::testing::Test {
 protected:
  static void ExpectBytesAt(const Exiv2::DataBuf& buf, size_t offset, uint8_t b0, uint8_t b1) {
    ASSERT_GE(buf.size(), offset + 2u);
    const Exiv2::byte* p = buf.c_data(offset);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(static_cast<uint8_t>(p[0]), b0);
    EXPECT_EQ(static_cast<uint8_t>(p[1]), b1);
  }
};

TEST_F(DataBufWriteUint16Test_1121, WritesLittleEndianAndReadBack_1121) {
  Exiv2::DataBuf buf(/*size=*/4);
  const uint16_t value = 0x1234;

  EXPECT_NO_THROW(buf.write_uint16(/*offset=*/0, value, Exiv2::littleEndian));
  EXPECT_EQ(buf.read_uint16(/*offset=*/0, Exiv2::littleEndian), value);

  // Byte-level check for an observable effect through the public c_data().
  ExpectBytesAt(buf, /*offset=*/0, /*b0=*/0x34, /*b1=*/0x12);
}

TEST_F(DataBufWriteUint16Test_1121, WritesBigEndianAndReadBack_1121) {
  Exiv2::DataBuf buf(/*size=*/4);
  const uint16_t value = 0x1234;

  EXPECT_NO_THROW(buf.write_uint16(/*offset=*/1, value, Exiv2::bigEndian));
  EXPECT_EQ(buf.read_uint16(/*offset=*/1, Exiv2::bigEndian), value);

  ExpectBytesAt(buf, /*offset=*/1, /*b0=*/0x12, /*b1=*/0x34);
}

TEST_F(DataBufWriteUint16Test_1121, WritesAtLastValidOffset_1121) {
  Exiv2::DataBuf buf(/*size=*/2);
  const uint16_t value = 0xABCD;

  // For size==2, only offset==0 is valid for a 2-byte write.
  EXPECT_NO_THROW(buf.write_uint16(/*offset=*/0, value, Exiv2::bigEndian));
  EXPECT_EQ(buf.read_uint16(/*offset=*/0, Exiv2::bigEndian), value);
  ExpectBytesAt(buf, /*offset=*/0, /*b0=*/0xAB, /*b1=*/0xCD);
}

TEST_F(DataBufWriteUint16Test_1121, ThrowsWhenBufferEmptyOrSizeOne_1121) {
  {
    Exiv2::DataBuf buf;  // default constructed: size() is observable
    EXPECT_TRUE(buf.empty());
    EXPECT_THROW(buf.write_uint16(/*offset=*/0, /*x=*/0x0001, Exiv2::littleEndian), std::out_of_range);
  }
  {
    Exiv2::DataBuf buf(/*size=*/1);
    ASSERT_EQ(buf.size(), 1u);
    EXPECT_THROW(buf.write_uint16(/*offset=*/0, /*x=*/0x0001, Exiv2::littleEndian), std::out_of_range);
  }
}

TEST_F(DataBufWriteUint16Test_1121, ThrowsWhenOffsetIsOutOfRange_1121) {
  {
    Exiv2::DataBuf buf(/*size=*/2);
    // size==2 => last valid offset is 0; offset==1 should throw.
    EXPECT_THROW(buf.write_uint16(/*offset=*/1, /*x=*/0x2222, Exiv2::littleEndian), std::out_of_range);
  }
  {
    Exiv2::DataBuf buf(/*size=*/3);
    // size==3 => last valid offset is 1; offset==2 should throw.
    EXPECT_THROW(buf.write_uint16(/*offset=*/2, /*x=*/0x3333, Exiv2::bigEndian), std::out_of_range);
  }
  {
    Exiv2::DataBuf buf(/*size=*/4);
    // Clearly out-of-range.
    EXPECT_THROW(buf.write_uint16(/*offset=*/100, /*x=*/0x4444, Exiv2::bigEndian), std::out_of_range);
  }
}

TEST_F(DataBufWriteUint16Test_1121, ThrowsWithExpectedMessageOnOverflow_1121) {
  Exiv2::DataBuf buf(/*size=*/2);

  try {
    buf.write_uint16(/*offset=*/1, /*x=*/0x9999, Exiv2::littleEndian);
    FAIL() << "Expected std::out_of_range to be thrown";
  } catch (const std::out_of_range& e) {
    EXPECT_EQ(std::string(e.what()), "Overflow in Exiv2::DataBuf::write_uint16");
  }
}

TEST_F(DataBufWriteUint16Test_1121, WorksAfterResizeToSufficientSize_1121) {
  Exiv2::DataBuf buf;
  ASSERT_TRUE(buf.empty());

  buf.resize(2);
  ASSERT_EQ(buf.size(), 2u);

  EXPECT_NO_THROW(buf.write_uint16(/*offset=*/0, /*x=*/0x0F0E, Exiv2::bigEndian));
  EXPECT_EQ(buf.read_uint16(/*offset=*/0, Exiv2::bigEndian), 0x0F0Eu);
  ExpectBytesAt(buf, /*offset=*/0, /*b0=*/0x0F, /*b1=*/0x0E);
}

}  // namespace