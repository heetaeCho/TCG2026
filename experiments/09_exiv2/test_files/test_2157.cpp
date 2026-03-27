#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/basicio.hpp"

#include "./TestProjects/exiv2/src/tiffimage_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::MockFunction;



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



class MockOffsetWriter : public OffsetWriter {

public:

    MOCK_METHOD(void, setOrigin, (OffsetId id, uint32_t origin, ByteOrder byteOrder), (override));

    MOCK_METHOD(void, setTarget, (OffsetId id, uint32_t target), (override));

    MOCK_CONST_METHOD0(writeOffsets, void(BasicIo& io), (override));

};



class IoWrapperTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    MockOffsetWriter mock_offset_writer;

    const byte header[] = { 0x49, 0x49 }; // Example TIFF header

    size_t header_size = sizeof(header) / sizeof(byte);

    IoWrapper io_wrapper;



    IoWrapperTest() : io_wrapper(mock_io, header, header_size, &mock_offset_writer) {}

};



TEST_F(IoWrapperTest_2157, ConstructorNoHeader_2157) {

    MockBasicIo mock_io_no_header;

    MockOffsetWriter mock_offset_writer_no_header;

    IoWrapper io_wrapper_no_header(mock_io_no_header, nullptr, 0, &mock_offset_writer_no_header);

    EXPECT_TRUE(io_wrapper_no_header.wroteHeader_);

}



TEST_F(IoWrapperTest_2157, ConstructorWithHeader_2157) {

    EXPECT_FALSE(io_wrapper.wroteHeader_);

}



TEST_F(IoWrapperTest_2157, WriteData_2157) {

    const byte data[] = { 0x01, 0x02 };

    size_t data_size = sizeof(data) / sizeof(byte);

    EXPECT_CALL(mock_io, write(data, data_size)).WillOnce(::testing::Return(data_size));

    EXPECT_EQ(io_wrapper.write(data, data_size), data_size);

}



TEST_F(IoWrapperTest_2157, WriteZeroData_2157) {

    const byte* data = nullptr;

    size_t data_size = 0;

    EXPECT_CALL(mock_io, write(data, data_size)).WillOnce(::testing::Return(0));

    EXPECT_EQ(io_wrapper.write(data, data_size), 0);

}



TEST_F(IoWrapperTest_2157, PutByte_2157) {

    byte data = 0x03;

    EXPECT_CALL(mock_io, putb(data)).WillOnce(::testing::Return(1));

    EXPECT_EQ(io_wrapper.putb(data), 1);

}



TEST_F(IoWrapperTest_2157, SetTarget_2157) {

    int id = 1;

    size_t target = 100;

    EXPECT_CALL(mock_offset_writer, setTarget(id, target));

    io_wrapper.setTarget(id, target);

}
