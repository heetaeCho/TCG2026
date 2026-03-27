#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/psdimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo&), (override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class PsdImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        psdImage = std::make_unique<PsdImage>(std::move(mockIo));

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<PsdImage> psdImage;

};



TEST_F(PsdImageTest_1187, WriteMetadata_SuccessfulWrite_1187) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, close()).Times(1);

    EXPECT_CALL(*mockIo, transfer(_)).Times(1);



    psdImage->writeMetadata();

}



TEST_F(PsdImageTest_1187, WriteMetadata_OpenFailed_1187) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_THROW(psdImage->writeMetadata(), Error);

}



TEST_F(PsdImageTest_1187, WriteMetadata_TransferFailed_1187) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, close()).Times(1);

    EXPECT_CALL(*mockIo, transfer(_)).WillOnce(Return());



    psdImage->writeMetadata();

}



TEST_F(PsdImageTest_1187, WriteMetadata_CloseCalledAfterWrite_1187) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, close()).Times(1).RetiresOnSaturation();

    EXPECT_CALL(*mockIo, transfer(_)).Times(1);



    psdImage->writeMetadata();

}



TEST_F(PsdImageTest_1187, WriteMetadata_PathCalledDuringOpen_1187) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(testing::Return("test_path"));

    EXPECT_CALL(*mockIo, close()).Times(1);

    EXPECT_CALL(*mockIo, transfer(_)).Times(1);



    psdImage->writeMetadata();

}
