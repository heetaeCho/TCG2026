#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/JPEG2000Stream.h"

#include "TestProjects/poppler/poppler/Stream.h"



class JPXStreamTest_1465 : public ::testing::Test {

protected:

    std::unique_ptr<JPXStream> jpxStream;



    void SetUp() override {

        auto mockStream = std::make_unique<MockStream>();

        jpxStream = std::make_unique<JPXStream>(std::move(mockStream));

    }

};



class MockStream : public Stream {

public:

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const override));

    MOCK_METHOD(void, getImageParams, (int * bitsPerComponent, StreamColorSpaceMode * csMode, _Bool * hasAlpha), (override));

};



TEST_F(JPXStreamTest_1465, GetKindReturnsJPX_1465) {

    EXPECT_EQ(jpxStream->getKind(), strJPX);

}



TEST_F(JPXStreamTest_1465, RewindReturnsFalseByDefault_1465) {

    EXPECT_FALSE(jpxStream->rewind());

}



TEST_F(JPXStreamTest_1465, CloseInvokesBaseClose_1465) {

    EXPECT_CALL(*dynamic_cast<MockStream*>(jpxStream.get()), close()).Times(1);

    jpxStream->close();

}



TEST_F(JPXStreamTest_1465, GetPosInvokesBaseGetPos_1465) {

    EXPECT_CALL(*dynamic_cast<MockStream*>(jpxStream.get()), getPos()).WillOnce(::testing::Return(Goffset{0}));

    EXPECT_EQ(jpxStream->getPos(), Goffset{0});

}



TEST_F(JPXStreamTest_1465, GetCharInvokesBaseGetChar_1465) {

    EXPECT_CALL(*dynamic_cast<MockStream*>(jpxStream.get()), getChar()).WillOnce(::testing::Return(0));

    EXPECT_EQ(jpxStream->getChar(), 0);

}



TEST_F(JPXStreamTest_1465, LookCharInvokesBaseLookChar_1465) {

    EXPECT_CALL(*dynamic_cast<MockStream*>(jpxStream.get()), lookChar()).WillOnce(::testing::Return(0));

    EXPECT_EQ(jpxStream->lookChar(), 0);

}



TEST_F(JPXStreamTest_1465, GetPSFilterInvokesBaseGetPSFilter_1465) {

    EXPECT_CALL(*dynamic_cast<MockStream*>(jpxStream.get()), getPSFilter(::testing::_, ::testing::_)).WillOnce(::testing::Return(std::optional<std::string>{}));

    EXPECT_FALSE(jpxStream->getPSFilter(0, "").has_value());

}



TEST_F(JPXStreamTest_1465, IsBinaryInvokesBaseIsBinary_1465) {

    EXPECT_CALL(*dynamic_cast<MockStream*>(jpxStream.get()), isBinary(::testing::_)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(jpxStream->isBinary(false));

}



TEST_F(JPXStreamTest_1465, GetImageParamsInvokesBaseGetImageParams_1465) {

    int bitsPerComponent = 0;

    StreamColorSpaceMode csMode = strCSPDeviceGray;

    _Bool hasAlpha = false;

    EXPECT_CALL(*dynamic_cast<MockStream*>(jpxStream.get()), getImageParams(::testing::_, ::testing::_, ::testing::_)).Times(1);

    jpxStream->getImageParams(&bitsPerComponent, &csMode, &hasAlpha);

}



TEST_F(JPXStreamTest_1465, SetSupportJPXtransparencySetsValue_1465) {

    jpxStream->setSupportJPXtransparency(true);

    EXPECT_TRUE(jpxStream->supportJPXtransparency());

}



TEST_F(JPXStreamTest_1465, SupportJPXtransparencyReturnsFalseByDefault_1465) {

    EXPECT_FALSE(jpxStream->supportJPXtransparency());

}
