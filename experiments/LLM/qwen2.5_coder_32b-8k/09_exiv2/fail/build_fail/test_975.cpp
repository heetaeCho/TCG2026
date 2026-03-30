#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pngimage.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using testing::_;

using testing::Return;

using testing::Throw;



class PngImageTest_975 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> mockIo = std::make_unique<BasicIo>();

    BasicIo* rawMockIo = mockIo.get();

    PngImage pngImage{std::move(mockIo), false};



    void SetUp() override {

        ON_CALL(*rawMockIo, open()).WillByDefault(Return(0));

        ON_CALL(*rawMockIo, close()).WillByDefault(Return(0));

        ON_CALL(*rawMockIo, transfer(_)).WillByDefault(Return());

        ON_CALL(*rawMockIo, path()).WillByDefault(Return("test_path.png"));

    }

};



TEST_F(PngImageTest_975, WriteMetadata_Successful_975) {

    EXPECT_CALL(*rawMockIo, open()).Times(1);

    EXPECT_CALL(*rawMockIo, close()).Times(1);

    EXPECT_CALL(*rawMockIo, transfer(_)).Times(1);



    ASSERT_NO_THROW(pngImage.writeMetadata());

}



TEST_F(PngImageTest_975, WriteMetadata_OpenFailure_975) {

    ON_CALL(*rawMockIo, open()).WillByDefault(Return(-1));



    EXPECT_CALL(*rawMockIo, open()).Times(1);

    EXPECT_CALL(*rawMockIo, close()).Times(0);



    ASSERT_THROW(pngImage.writeMetadata(), Error);

}



TEST_F(PngImageTest_975, WriteMetadata_TransferFailure_975) {

    ON_CALL(*rawMockIo, transfer(_)).WillByDefault(Throw(Error(ErrorCode::kerTransferFailed)));



    EXPECT_CALL(*rawMockIo, open()).Times(1);

    EXPECT_CALL(*rawMockIo, close()).Times(1);



    ASSERT_THROW(pngImage.writeMetadata(), Error);

}



TEST_F(PngImageTest_975, WriteMetadata_CloseFailure_975) {

    ON_CALL(*rawMockIo, close()).WillByDefault(Return(-1));



    EXPECT_CALL(*rawMockIo, open()).Times(1);

    EXPECT_CALL(*rawMockIo, close()).Times(1);



    ASSERT_THROW(pngImage.writeMetadata(), Error);

}
