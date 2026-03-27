#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const override));

    MOCK_METHOD(size_t, size, (), (const override));

    MOCK_METHOD(bool, isopen, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class BmffImageTest_1200 : public Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<StrictMock<MockBasicIo>>();

        bmff_image = std::make_unique<BmffImage>(std::move(mock_io), false, 10);

    }



    void TearDown() override {}



    std::unique_ptr<BmffImage> bmff_image;

    std::unique_ptr<MockBasicIo> mock_io;

};



TEST_F(BmffImageTest_1200, ReadMetadata_NormalOperation_1200) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(32)); // Simulate a file of 32 bytes

    EXPECT_CALL(*mock_io, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).WillOnce(Return(0));



    bmff_image->readMetadata();

}



TEST_F(BmffImageTest_1200, ReadMetadata_FileSizeBoundaryCondition_1200) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(0)); // Simulate a file of 0 bytes

    EXPECT_CALL(*mock_io, close()).WillOnce(Return(0));



    bmff_image->readMetadata();

}



TEST_F(BmffImageTest_1200, ReadMetadata_FileOpenFailure_1200) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(-1)); // Simulate file open failure



    bmff_image->readMetadata(); // Should handle the error gracefully

}



TEST_F(BmffImageTest_1200, ReadMetadata_SeekFailure_1200) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(32)); // Simulate a file of 32 bytes

    EXPECT_CALL(*mock_io, seek(0, BasicIo::beg)).WillOnce(Return(-1)); // Simulate seek failure

    EXPECT_CALL(*mock_io, close()).WillOnce(Return(0));



    bmff_image->readMetadata(); // Should handle the error gracefully

}



TEST_F(BmffImageTest_1200, ReadMetadata_CloseFailure_1200) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(32)); // Simulate a file of 32 bytes

    EXPECT_CALL(*mock_io, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).WillOnce(Return(-1)); // Simulate close failure



    bmff_image->readMetadata(); // Should handle the error gracefully

}
