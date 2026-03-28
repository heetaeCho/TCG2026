#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/tiffimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class TiffImageTest_1732 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<MockBasicIo>();

        tiffImage = std::make_unique<TiffImage>(std::move(io), false);

    }



    std::unique_ptr<MockBasicIo> io;

    std::unique_ptr<TiffImage> tiffImage;

};



TEST_F(TiffImageTest_1732, ReadMetadata_SuccessfulRead_1732) {

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*io, size()).WillOnce(Return(1024));

    EXPECT_CALL(*io, mmap(false)).WillOnce(testing::Return(reinterpret_cast<byte*>(new byte[1024])));

    EXPECT_CALL(*io, munmap()).WillOnce(Return(0));



    tiffImage->readMetadata();

}



TEST_F(TiffImageTest_1732, ReadMetadata_OpenFileFailed_1732) {

    EXPECT_CALL(*io, open()).WillOnce(Return(-1));

    EXPECT_THROW(tiffImage->readMetadata(), Error);

}



TEST_F(TiffImageTest_1732, ReadMetadata_NotTiffType_1732) {

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*io, size()).WillOnce(Return(1024));

    EXPECT_CALL(*io, mmap(false)).WillOnce(testing::Return(reinterpret_cast<byte*>(new byte[1024])));

    EXPECT_CALL(*io, munmap()).WillOnce(Return(0));



    ON_CALL(*io, isopen()).WillByDefault(Return(true));

    ON_CALL(*io, size()).WillByDefault(Return(1024));

    ON_CALL(*io, mmap(false)).WillByDefault(testing::Return(reinterpret_cast<byte*>(new byte[1024])));

    ON_CALL(*io, munmap()).WillByDefault(Return(0));



    EXPECT_THROW(tiffImage->readMetadata(), Error);

}



TEST_F(TiffImageTest_1732, ReadMetadata_FailedToReadImageData_1732) {

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*io, size()).WillOnce(Return(1024));

    EXPECT_CALL(*io, mmap(false)).WillOnce(testing::Return(reinterpret_cast<byte*>(new byte[1024])));

    EXPECT_CALL(*io, munmap()).WillOnce(Return(0));



    ON_CALL(*io, isopen()).WillByDefault(Return(true));

    ON_CALL(*io, size()).WillByDefault(Return(1024));

    ON_CALL(*io, mmap(false)).WillByDefault(testing::Return(reinterpret_cast<byte*>(new byte[1024])));

    ON_CALL(*io, munmap()).WillByDefault(Return(0));



    EXPECT_THROW(tiffImage->readMetadata(), Error);

}



TEST_F(TiffImageTest_1732, ReadMetadata_InvalidICCProfileSize_1732) {

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*io, size()).WillOnce(Return(1024));

    EXPECT_CALL(*io, mmap(false)).WillOnce(testing::Return(reinterpret_cast<byte*>(new byte[1024])));

    EXPECT_CALL(*io, munmap()).WillOnce(Return(0));



    ON_CALL(*io, isopen()).WillByDefault(Return(true));

    ON_CALL(*io, size()).WillByDefault(Return(1024));

    ON_CALL(*io, mmap(false)).WillByDefault(testing::Return(reinterpret_cast<byte*>(new byte[1024])));

    ON_CALL(*io, munmap()).WillByDefault(Return(0));



    EXPECT_THROW(tiffImage->readMetadata(), Error);

}
