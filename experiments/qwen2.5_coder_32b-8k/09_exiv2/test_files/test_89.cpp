#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "./TestProjects/exiv2/src/jp2image.cpp"



using namespace Exiv2;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte*, size_t), (override));

    MOCK_METHOD(int, seek, (int64_t, Position), (override));

    MOCK_METHOD(bool, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class Jp2TypeDetectionTest_89 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    const std::array<byte, 12> jp2Signature = {0, 0, 0, 12, 106, 80, 32, 32, 13, 10, 135, 10};

};



TEST_F(Jp2TypeDetectionTest_89, ValidJp2SignatureAdvanceTrue_89) {

    EXPECT_CALL(mock_io, read(_, jp2Signature.size())).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(jp2Signature.data(), jp2Signature.size()),

        Return(jp2Signature.size())));

    EXPECT_CALL(mock_io, seek(-static_cast<int64_t>(jp2Signature.size()), BasicIo::cur)).Times(0);

    EXPECT_CALL(mock_io, error()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));



    bool result = isJp2Type(mock_io, true);

    EXPECT_TRUE(result);

}



TEST_F(Jp2TypeDetectionTest_89, ValidJp2SignatureAdvanceFalse_89) {

    EXPECT_CALL(mock_io, read(_, jp2Signature.size())).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(jp2Signature.data(), jp2Signature.size()),

        Return(jp2Signature.size())));

    EXPECT_CALL(mock_io, seek(-static_cast<int64_t>(jp2Signature.size()), BasicIo::cur)).Times(1);

    EXPECT_CALL(mock_io, error()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));



    bool result = isJp2Type(mock_io, false);

    EXPECT_TRUE(result);

}



TEST_F(Jp2TypeDetectionTest_89, InvalidJp2SignatureAdvanceTrue_89) {

    std::array<byte, 12> invalidData = {0, 0, 0, 12, 106, 80, 32, 32, 13, 10, 135, 20};

    EXPECT_CALL(mock_io, read(_, jp2Signature.size())).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(invalidData.data(), invalidData.size()),

        Return(invalidData.size())));

    EXPECT_CALL(mock_io, seek(-static_cast<int64_t>(jp2Signature.size()), BasicIo::cur)).Times(1);

    EXPECT_CALL(mock_io, error()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));



    bool result = isJp2Type(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(Jp2TypeDetectionTest_89, InvalidJp2SignatureAdvanceFalse_89) {

    std::array<byte, 12> invalidData = {0, 0, 0, 12, 106, 80, 32, 32, 13, 10, 135, 20};

    EXPECT_CALL(mock_io, read(_, jp2Signature.size())).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(invalidData.data(), invalidData.size()),

        Return(invalidData.size())));

    EXPECT_CALL(mock_io, seek(-static_cast<int64_t>(jp2Signature.size()), BasicIo::cur)).Times(1);

    EXPECT_CALL(mock_io, error()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));



    bool result = isJp2Type(mock_io, false);

    EXPECT_FALSE(result);

}



TEST_F(Jp2TypeDetectionTest_89, ReadLessThanSignatureSize_89) {

    std::array<byte, 12> partialData = {0, 0, 0, 12, 106, 80};

    EXPECT_CALL(mock_io, read(_, jp2Signature.size())).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(partialData.data(), partialData.size()),

        Return(partialData.size())));

    EXPECT_CALL(mock_io, seek(-static_cast<int64_t>(jp2Signature.size()), BasicIo::cur)).Times(1);

    EXPECT_CALL(mock_io, error()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));



    bool result = isJp2Type(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(Jp2TypeDetectionTest_89, IOErrorOccurredAdvanceTrue_89) {

    std::array<byte, 12> invalidData = {0, 0, 0, 12, 106, 80, 32, 32, 13, 10, 135, 20};

    EXPECT_CALL(mock_io, read(_, jp2Signature.size())).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(invalidData.data(), invalidData.size()),

        Return(invalidData.size())));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));



    bool result = isJp2Type(mock_io, true);

    EXPECT_FALSE(result);

}



TEST_F(Jp2TypeDetectionTest_89, EndOfFileOccurredAdvanceTrue_89) {

    std::array<byte, 12> invalidData = {0, 0, 0, 12, 106, 80, 32, 32, 13, 10, 135, 20};

    EXPECT_CALL(mock_io, read(_, jp2Signature.size())).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>(invalidData.data(), invalidData.size()),

        Return(invalidData.size())));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));



    bool result = isJp2Type(mock_io, true);

    EXPECT_FALSE(result);

}
