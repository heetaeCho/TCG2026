#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/cr2image.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class Cr2ParserTest_1746 : public Test {

protected:

    MockBasicIo mock_io;

    Cr2Parser parser;

    ExifData exif_data;

    IptcData iptc_data;

    XmpData xmp_data;



    static constexpr byte sample_data[] = {0x00, 0x01, 0x02, 0x03};

};



TEST_F(Cr2ParserTest_1746, Encode_NormalOperation_1746) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, _)).Times(AtLeast(1));



    WriteMethod result = parser.encode(mock_io, sample_data, sizeof(sample_data), bigEndian, exif_data, iptc_data, xmp_data);

    EXPECT_EQ(result, wmWrite);

}



TEST_F(Cr2ParserTest_1746, Encode_EmptyData_1746) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, _)).Times(AtLeast(1));



    WriteMethod result = parser.encode(mock_io, nullptr, 0, bigEndian, exif_data, iptc_data, xmp_data);

    EXPECT_EQ(result, wmWrite);

}



TEST_F(Cr2ParserTest_1746, Encode_FilteredIfdRemoval_1746) {

    ExifData original_exif_data;

    auto& exif_datum = original_exif_data.add(ExifKey("PanaRaw:SomeTag"), new UShortValue);

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, _)).Times(AtLeast(1));



    WriteMethod result = parser.encode(mock_io, sample_data, sizeof(sample_data), bigEndian, original_exif_data, iptc_data, xmp_data);

    EXPECT_EQ(result, wmWrite);

    EXPECT_TRUE(original_exif_data.findKey(ExifKey("PanaRaw:SomeTag")) == original_exif_data.end());

}



TEST_F(Cr2ParserTest_1746, Encode_ExceptionHandling_1746) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));



    WriteMethod result = parser.encode(mock_io, sample_data, sizeof(sample_data), bigEndian, exif_data, iptc_data, xmp_data);

    EXPECT_EQ(result, wmNone);

}



TEST_F(Cr2ParserTest_1746, Encode_WriteFailureHandling_1746) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, _)).WillOnce(Return(0));



    WriteMethod result = parser.encode(mock_io, sample_data, sizeof(sample_data), bigEndian, exif_data, iptc_data, xmp_data);

    EXPECT_EQ(result, wmNone);

}
