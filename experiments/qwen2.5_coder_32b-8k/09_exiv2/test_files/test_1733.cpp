#include <gtest/gtest.h>

#include "exiv2/tiffimage.hpp"

#include "exiv2/basicio.hpp"



namespace {



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class TiffImageTest_1733 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io = std::make_unique<MockBasicIo>();

    TiffImage tiff_image {std::move(mock_io), false};

};



TEST_F(TiffImageTest_1733, WriteMetadata_SuccessfulWrite_1733) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, mmap(true)).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, isopen()).WillRepeatedly(::testing::Return(true));



    tiff_image.writeMetadata();

}



TEST_F(TiffImageTest_1733, WriteMetadata_FailureOnOpen_1733) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(-1));

    EXPECT_CALL(*mock_io, mmap(true)).Times(0);



    tiff_image.writeMetadata();

}



TEST_F(TiffImageTest_1733, WriteMetadata_ReadTiffHeader_1733) {

    const byte* testData = reinterpret_cast<const byte*>("II*\0");

    size_t testSize = 4;



    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, mmap(true)).WillOnce(::testing::Return(testData));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(testSize));



    tiff_image.writeMetadata();

}



TEST_F(TiffImageTest_1733, WriteMetadata_IccProfileDefined_1733) {

    DataBuf profileData(4, 0);

    tiff_image.setIccProfile(std::move(profileData));



    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, mmap(true)).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(0));



    tiff_image.writeMetadata();

}



TEST_F(TiffImageTest_1733, WriteMetadata_WriteMethodCalled_1733) {

    EXPECT_CALL(*mock_io, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_io, mmap(true)).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(*mock_io, size()).WillOnce(::testing::Return(0));



    tiff_image.writeMetadata();

}



}  // namespace
