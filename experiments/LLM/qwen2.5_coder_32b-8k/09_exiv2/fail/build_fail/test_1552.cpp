#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class OrfImageTest_1552 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        orfImage = std::make_unique<OrfImage>(std::move(mockIo), false);

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<OrfImage> orfImage;

};



TEST_F(OrfImageTest_1552, WriteMetadata_SuccessfulWrite_1552) {

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockIo, mmap(true)).WillOnce(::testing::Return(reinterpret_cast<byte*>(const_cast<char*>("ORFHEADER"))));

    EXPECT_CALL(*mockIo, size()).WillOnce(::testing::Return(8));



    orfImage->writeMetadata();

}



TEST_F(OrfImageTest_1552, WriteMetadata_FileNotOpened_1552) {

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(-1));

    EXPECT_THROW(orfImage->writeMetadata(), Error);

}



TEST_F(OrfImageTest_1552, WriteMetadata_HeaderReadFailure_1552) {

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockIo, mmap(true)).WillOnce(::testing::Return(reinterpret_cast<byte*>(const_cast<char*>("INVALID"))));

    EXPECT_CALL(*mockIo, size()).WillOnce(::testing::Return(8));



    orfImage->writeMetadata();

}



TEST_F(OrfImageTest_1552, WriteMetadata_EncodeFailure_1552) {

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockIo, mmap(true)).WillOnce(::testing::Return(reinterpret_cast<byte*>(const_cast<char*>("ORFHEADER"))));

    EXPECT_CALL(*mockIo, size()).WillOnce(::testing::Return(8));



    // Assuming OrfParser::encode throws an exception in some cases

    EXPECT_THROW(orfImage->writeMetadata(), Error);

}
