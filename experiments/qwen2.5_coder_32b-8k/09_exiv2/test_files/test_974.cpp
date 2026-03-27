#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/pngimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(size_t, size, (), (const override));

    MOCK_METHOD(bool, isopen, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class PngImageTest_974 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<MockBasicIo>();

        pngImage = std::make_unique<PngImage>(std::move(io), false);

    }



    std::unique_ptr<MockBasicIo> io;

    std::unique_ptr<PngImage> pngImage;

};



TEST_F(PngImageTest_974, OpenFailed_974) {

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(1));

    EXPECT_THROW(pngImage->readMetadata(), Error);

}



TEST_F(PngImageTest_974, NotAnImage_974) {

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*io, size()).WillOnce(testing::Return(1024));



    DataBuf data(8);

    EXPECT_CALL(*io, read(testing::_, 8)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(data.data(), data.data() + 8),

        testing::Return(8)

    ));



    std::string invalidHeader = "INVALID";

    memcpy(data.c_data(), invalidHeader.c_str(), 7);



    EXPECT_THROW(pngImage->readMetadata(), Error);

}



TEST_F(PngImageTest_974, ReadChunkExceedsSize_974) {

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*io, size()).WillOnce(testing::Return(8));



    DataBuf data(8);

    EXPECT_CALL(*io, read(testing::_, 8)).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(data.data(), data.data() + 8),

        testing::Return(8)

    ));



    std::string validHeader = "\x89PNG\r\n\x1a\n";

    memcpy(data.c_data(), validHeader.c_str(), 8);



    EXPECT_THROW(pngImage->readMetadata(), Error);

}



TEST_F(PngImageTest_974, ValidIHDRChunk_974) {

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*io, size()).WillOnce(testing::Return(24));



    DataBuf data(8);

    EXPECT_CALL(*io, read(testing::_, 8)).Times(2).WillRepeatedly(testing::DoAll(

        testing::SetArrayArgument<0>(data.data(), data.data() + 8),

        testing::Return(8)

    ));



    std::string validHeader = "\x89PNG\r\n\x1a\n";

    memcpy(data.c_data(), validHeader.c_str(), 8);



    uint32_t chunkLength = 13;

    data.write_uint32(0, chunkLength, bigEndian);

    memcpy(data.c_data() + 4, "IHDR", 4);



    EXPECT_CALL(*io, seek(chunkLength + 4, BasicIo::cur)).WillOnce(testing::Return(0));



    pngImage->readMetadata();

}



TEST_F(PngImageTest_974, ValidTXTChunks_974) {

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*io, size()).WillOnce(testing::Return(56));



    DataBuf data(8);

    EXPECT_CALL(*io, read(testing::_, 8)).Times(3).WillRepeatedly(testing::DoAll(

        testing::SetArrayArgument<0>(data.data(), data.data() + 8),

        testing::Return(8)

    ));



    std::string validHeader = "\x89PNG\r\n\x1a\n";

    memcpy(data.c_data(), validHeader.c_str(), 8);



    uint32_t chunkLengths[] = {14, 15, 6};

    const char* chunkTypes[] = {"tEXt", "zTXt", "IEND"};



    for (int i = 0; i < 3; ++i) {

        data.write_uint32(0, chunkLengths[i], bigEndian);

        memcpy(data.c_data() + 4, chunkTypes[i], 4);



        EXPECT_CALL(*io, seek(chunkLengths[i] + 4, BasicIo::cur)).WillOnce(testing::Return(0));

    }



    pngImage->readMetadata();

}



TEST_F(PngImageTest_974, ValidEXIFChunk_974) {

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*io, size()).WillOnce(testing::Return(32));



    DataBuf data(8);

    EXPECT_CALL(*io, read(testing::_, 8)).Times(2).WillRepeatedly(testing::DoAll(

        testing::SetArrayArgument<0>(data.data(), data.data() + 8),

        testing::Return(8)

    ));



    std::string validHeader = "\x89PNG\r\n\x1a\n";

    memcpy(data.c_data(), validHeader.c_str(), 8);



    uint32_t chunkLength = 16;

    data.write_uint32(0, chunkLength, bigEndian);

    memcpy(data.c_data() + 4, "eXIf", 4);



    EXPECT_CALL(*io, seek(chunkLength + 4, BasicIo::cur)).WillOnce(testing::Return(0));



    pngImage->readMetadata();

}



TEST_F(PngImageTest_974, ValidIccpChunk_974) {

    EXPECT_CALL(*io, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*io, size()).WillOnce(testing::Return(32));



    DataBuf data(8);

    EXPECT_CALL(*io, read(testing::_, 8)).Times(2).WillRepeatedly(testing::DoAll(

        testing::SetArrayArgument<0>(data.data(), data.data() + 8),

        testing::Return(8)

    ));



    std::string validHeader = "\x89PNG\r\n\x1a\n";

    memcpy(data.c_data(), validHeader.c_str(), 8);



    uint32_t chunkLength = 16;

    data.write_uint32(0, chunkLength, bigEndian);

    memcpy(data.c_data() + 4, "iCCP", 4);



    EXPECT_CALL(*io, seek(chunkLength + 4, BasicIo::cur)).WillOnce(testing::Return(0));



    pngImage->readMetadata();

}
