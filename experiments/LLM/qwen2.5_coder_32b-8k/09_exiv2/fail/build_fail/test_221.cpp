#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "rafimage.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

};



class RafImageTest_221 : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    std::unique_ptr<BasicIo> io_ptr = std::make_unique<NiceMock<MockBasicIo>>(mock_io);

    RafImage raf_image{std::move(io_ptr), false};

};



TEST_F(RafImageTest_221, ReadMetadata_SuccessfulRead_221) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, seek(84, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 4)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{1, 0, 0, 0}.data(), std::array<byte, 4>{1, 0, 0, 0}.data() + 4),

        ::testing::Return(4)

    ));

    EXPECT_CALL(mock_io, seek(1, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 256)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{0x49, 0x49, 0x2A, 0x00}.data(), std::array<byte, 4>{0x49, 0x49, 0x2A, 0x00}.data() + 4),

        ::testing::Return(4)

    ));

    EXPECT_CALL(mock_io, seek(100, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 8)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{0x64, 0x00, 0x00, 0x00}.data(), std::array<byte, 4>{0x64, 0x00, 0x00, 0x00}.data() + 4),

        ::testing::Return(4)

    ));



    EXPECT_NO_THROW(raf_image.readMetadata());

}



TEST_F(RafImageTest_221, ReadMetadata_OpenFailed_221) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(-1));



    EXPECT_THROW(raf_image.readMetadata(), Error);

}



TEST_F(RafImageTest_221, ReadMetadata_SeekFailed_221) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, seek(84, BasicIo::beg)).WillOnce(::testing::Return(-1));



    EXPECT_THROW(raf_image.readMetadata(), Error);

}



TEST_F(RafImageTest_221, ReadMetadata_ReadFailed_221) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, seek(84, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 4)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{1, 0, 0, 0}.data(), std::array<byte, 4>{1, 0, 0, 0}.data() + 4),

        ::testing::Return(3)

    ));



    EXPECT_THROW(raf_image.readMetadata(), Error);

}



TEST_F(RafImageTest_221, ReadMetadata_NotRafType_221) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, seek(84, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 4)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{1, 0, 0, 0}.data(), std::array<byte, 4>{1, 0, 0, 0}.data() + 4),

        ::testing::Return(4)

    ));

    EXPECT_CALL(mock_io, seek(1, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 256)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{0x49, 0x49, 0x2A, 0x10}.data(), std::array<byte, 4>{0x49, 0x49, 0x2A, 0x10}.data() + 4),

        ::testing::Return(4)

    ));



    EXPECT_THROW(raf_image.readMetadata(), Error);

}



TEST_F(RafImageTest_221, ReadMetadata_CorruptedMetadata_221) {

    EXPECT_CALL(mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, seek(84, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 4)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{1, 0, 0, 0}.data(), std::array<byte, 4>{1, 0, 0, 0}.data() + 4),

        ::testing::Return(4)

    ));

    EXPECT_CALL(mock_io, seek(1, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 256)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{0x49, 0x49, 0x2A, 0x00}.data(), std::array<byte, 4>{0x49, 0x49, 0x2A, 0x00}.data() + 4),

        ::testing::Return(4)

    ));

    EXPECT_CALL(mock_io, seek(100, BasicIo::beg)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mock_io, read(_, 8)).WillRepeatedly(::testing::DoAll(

        ::testing::SetArrayArgument<0>(std::array<byte, 4>{0x64, 0x00, 0x00, 0x00}.data(), std::array<byte, 4>{0x64, 0x00, 0x00, 0x00}.data() + 4),

        ::testing::Return(4)

    ));

    EXPECT_CALL(mock_io, size()).WillOnce(::testing::Return(100));



    EXPECT_THROW(raf_image.readMetadata(), Error);

}
