#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/crwimage.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class CrwImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        crwImage = std::make_unique<CrwImage>(std::move(mockIo), false);

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<CrwImage> crwImage;

};



TEST_F(CrwImageTest_NormalOperation_1815, WriteMetadata_Success_1815) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, read(_, 1024)).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, close()).Times(1);



    crwImage->writeMetadata();

}



TEST_F(CrwImageTest_BoundaryConditions_1815, WriteMetadata_ZeroSizeFile_1815) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, read(_, 0)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, close()).Times(1);



    crwImage->writeMetadata();

}



TEST_F(CrwImageTest_ErrorCases_1815, WriteMetadata_OpenFails_1815) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));



    crwImage->writeMetadata(); // No exception expected, just internal handling

}



TEST_F(CrwImageTest_ErrorCases_1815, WriteMetadata_ReadFails_1815) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, read(_, 1024)).WillOnce(Return(0)); // Simulate read failure

    EXPECT_CALL(*mockIo, close()).Times(1);



    crwImage->writeMetadata(); // No exception expected, just internal handling

}



TEST_F(CrwImageTest_ErrorCases_1815, WriteMetadata_ErrorAfterRead_1815) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, read(_, 1024)).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(-1)); // Simulate error after read

    EXPECT_CALL(*mockIo, close()).Times(1);



    crwImage->writeMetadata(); // No exception expected, just internal handling

}



TEST_F(CrwImageTest_ErrorCases_1815, WriteMetadata_EofAfterRead_1815) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, read(_, 1024)).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(true)); // Simulate EOF after read

    EXPECT_CALL(*mockIo, close()).Times(1);



    crwImage->writeMetadata(); // No exception expected, just internal handling

}
