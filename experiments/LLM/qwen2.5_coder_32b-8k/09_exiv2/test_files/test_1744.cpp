#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/cr2image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    MOCK_METHOD(size_t, read, (byte*, size_t), (override));

    MOCK_METHOD(byte*, mmap, (bool), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class Cr2ImageTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    BasicIo::UniquePtr io_ptr = std::make_unique<MockBasicIo>();

    Cr2Image cr2_image{std::move(io_ptr), false};

};



TEST_F(Cr2ImageTest, WriteMetadata_SuccessfulWrite_1744) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(16));

    EXPECT_CALL(mock_io, mmap(true)).WillOnce(Return(reinterpret_cast<byte*>(new byte[16])));

    EXPECT_CALL(mock_io, write(_, _)).Times(1);



    cr2_image.writeMetadata();

}



TEST_F(Cr2ImageTest, WriteMetadata_OpenFails_1744) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));



    EXPECT_THROW(cr2_image.writeMetadata(), Error);

}



TEST_F(Cr2ImageTest, WriteMetadata_ReadHeaderFails_1744) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(16));

    EXPECT_CALL(mock_io, mmap(true)).WillOnce(Return(reinterpret_cast<byte*>(new byte[16])));



    cr2_image.writeMetadata();

}



TEST_F(Cr2ImageTest, WriteMetadata_MemoryMapFails_1744) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(16));

    EXPECT_CALL(mock_io, mmap(true)).WillOnce(Return(nullptr));



    cr2_image.writeMetadata();

}



TEST_F(Cr2ImageTest, WriteMetadata_InvalidByteOrder_1744) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(16));

    EXPECT_CALL(mock_io, mmap(true)).WillOnce(Return(reinterpret_cast<byte*>(new byte[16])));

    EXPECT_CALL(mock_io, write(_, _)).Times(1);



    cr2_image.writeMetadata();

}



TEST_F(Cr2ImageTest, WriteMetadata_LittleEndian_1744) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(16));

    EXPECT_CALL(mock_io, mmap(true)).WillOnce(Return(reinterpret_cast<byte*>(new byte[16])));

    EXPECT_CALL(mock_io, write(_, _)).Times(1);



    cr2_image.writeMetadata();

}



TEST_F(Cr2ImageTest, WriteMetadata_BigEndian_1744) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(16));

    EXPECT_CALL(mock_io, mmap(true)).WillOnce(Return(reinterpret_cast<byte*>(new byte[16])));

    EXPECT_CALL(mock_io, write(_, _)).Times(1);



    cr2_image.writeMetadata();

}
