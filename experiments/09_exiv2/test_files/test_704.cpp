#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class IptcParserTest_704 : public ::testing::Test {

protected:

    IptcData iptcData;

    Value::UniquePtr value;



    void SetUp() override {

        value.reset(Value::create(stringType));

        value->read("testValue", ByteOrder::bigEndian);

    }

};



TEST_F(IptcParserTest_704, EncodeEmptyIptcData_ReturnsEmptyBuffer_704) {

    DataBuf result = IptcParser().encode(iptcData);

    EXPECT_TRUE(result.empty());

}



TEST_F(IptcParserTest_704, EncodeSingleEntry_CorrectlyFormatsMarkerAndRecordTag_704) {

    iptcData.add(IptcKey("Iptc.Envelope.ModelVersion"), value.get());



    DataBuf result = IptcParser().encode(iptcData);

    EXPECT_EQ(result.size(), 8u); // marker (1 byte) + record (1 byte) + tag (1 byte) + dataSize (2 bytes) + data (3 bytes)

    EXPECT_EQ(result.read_uint8(0), 0x1C); // Standard IIM4 marker

    EXPECT_EQ(result.read_uint8(1), 0x01); // Record number for Envelope

    EXPECT_EQ(result.read_uint8(2), 0x00); // Tag number for ModelVersion

    EXPECT_EQ(result.read_uint16(3, ByteOrder::bigEndian), 9u); // Data size including null terminator

    EXPECT_STREQ(reinterpret_cast<const char*>(result.data(5)), "testValue"); // Data value

}



TEST_F(IptcParserTest_704, EncodeMultipleEntries_SortsByRecord_704) {

    iptcData.add(IptcKey("Iptc.Envelope.ModelVersion"), value.get());

    iptcData.add(IptcKey("Iptc.Application2.CaptionWriter"), value.get());



    DataBuf result = IptcParser().encode(iptcData);

    EXPECT_EQ(result.size(), 18u); // Two entries, each with marker (1 byte) + record (1 byte) + tag (1 byte) + dataSize (2 bytes) + data (3 bytes)

    EXPECT_EQ(result.read_uint8(0), 0x1C); // Standard IIM4 marker

    EXPECT_EQ(result.read_uint8(1), 0x01); // Record number for Envelope

    EXPECT_EQ(result.read_uint8(9), 0x1C); // Standard IIM4 marker

    EXPECT_EQ(result.read_uint8(10), 0x02); // Record number for Application2

}



TEST_F(IptcParserTest_704, EncodeLargeData_CorrectlyFormatsDataSizeAsLong_704) {

    std::string largeValue(33000, 'a');

    value->read(largeValue.c_str(), ByteOrder::bigEndian);

    iptcData.add(IptcKey("Iptc.Envelope.ModelVersion"), value.get());



    DataBuf result = IptcParser().encode(iptcData);

    EXPECT_EQ(result.size(), 33012u); // marker (1 byte) + record (1 byte) + tag (1 byte) + dataSize (4 bytes) + data (33000 bytes)

    EXPECT_EQ(result.read_uint8(0), 0x1C); // Standard IIM4 marker

    EXPECT_EQ(result.read_uint8(1), 0x01); // Record number for Envelope

    EXPECT_EQ(result.read_uint8(2), 0x00); // Tag number for ModelVersion

    EXPECT_EQ(result.read_uint16(3, ByteOrder::bigEndian), 0x8004u); // Indicating long format for data size

    EXPECT_EQ(result.read_uint32(5, ByteOrder::bigEndian), 33000u); // Actual data size

}



TEST_F(IptcParserTest_704, EncodeMultipleEntriesWithSameRecord_SortsByTag_704) {

    iptcData.add(IptcKey("Iptc.Envelope.ModelVersion"), value.get());

    iptcData.add(IptcKey("Iptc.Envelope.DateSent"), value.get());



    DataBuf result = IptcParser().encode(iptcData);

    EXPECT_EQ(result.size(), 18u); // Two entries, each with marker (1 byte) + record (1 byte) + tag (1 byte) + dataSize (2 bytes) + data (3 bytes)

    EXPECT_EQ(result.read_uint8(0), 0x1C); // Standard IIM4 marker

    EXPECT_EQ(result.read_uint8(1), 0x01); // Record number for Envelope

    EXPECT_EQ(result.read_uint8(2), 0x00); // Tag number for ModelVersion (lower than DateSent)

    EXPECT_EQ(result.read_uint8(9), 0x1C); // Standard IIM4 marker

    EXPECT_EQ(result.read_uint8(10), 0x01); // Record number for Envelope

    EXPECT_EQ(result.read_uint8(11), 0x55); // Tag number for DateSent (higher than ModelVersion)

}



TEST_F(IptcParserTest_704, EncodeWithNonStringData_CorrectlyHandlesDifferentType_704) {

    Value::UniquePtr intVal = Value::create(unsignedLongType);

    intVal->read(reinterpret_cast<const byte*>(&LARGE_INT), sizeof(LARGE_INT), ByteOrder::bigEndian);

    iptcData.add(IptcKey("Iptc.Application2.DateCreated"), intVal.get());



    DataBuf result = IptcParser().encode(iptcData);

    EXPECT_EQ(result.size(), 16u); // marker (1 byte) + record (1 byte) + tag (1 byte) + dataSize (2 bytes) + data (4 bytes)

    EXPECT_EQ(result.read_uint8(0), 0x1C); // Standard IIM4 marker

    EXPECT_EQ(result.read_uint8(1), 0x02); // Record number for Application2

    EXPECT_EQ(result.read_uint8(2), 0x37); // Tag number for DateCreated

    EXPECT_EQ(result.read_uint16(3, ByteOrder::bigEndian), 4u); // Data size

    EXPECT_EQ(result.read_uint32(5, ByteOrder::bigEndian), LARGE_INT); // Data value

}



TEST_F(IptcParserTest_704, EncodeWithNullData_DoesNotIncludeInOutput_704) {

    Value::UniquePtr nullValue = Value::create(stringType);

    iptcData.add(IptcKey("Iptc.Envelope.ModelVersion"), nullValue.get());



    DataBuf result = IptcParser().encode(iptcData);

    EXPECT_TRUE(result.empty());

}
