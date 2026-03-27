#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

    MOCK_METHOD(const bool, isBinary, (bool last), (const override));

    MOCK_METHOD(StreamKind, getKind, (), (const override));

};



class ASCII85StreamTest_182 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mock_stream_;

    std::unique_ptr<ASCII85Stream> ascii85_stream_;



    void SetUp() override {

        mock_stream_ = std::make_unique<MockStream>();

        ascii85_stream_ = std::make_unique<ASCII85Stream>(std::move(mock_stream_));

    }

};



TEST_F(ASCII85StreamTest_182, GetChar_CallsLookCharAndIncrementsIndex_182) {

    EXPECT_CALL(*mock_stream_, lookChar()).WillOnce(Return('A'));

    int result = ascii85_stream_->getChar();

    ASSERT_EQ(result, 'A');

}



TEST_F(ASCII85StreamTest_182, GetChar_ReturnsEOFWhenLookCharReturnsEOF_182) {

    EXPECT_CALL(*mock_stream_, lookChar()).WillOnce(Return(-1));

    int result = ascii85_stream_->getChar();

    ASSERT_EQ(result, -1);

}



TEST_F(ASCII85StreamTest_182, Rewind_CallsRewindOnUnderlyingStream_182) {

    EXPECT_CALL(*mock_stream_, rewind()).WillOnce(Return(true));

    bool result = ascii85_stream_->rewind();

    ASSERT_TRUE(result);

}



TEST_F(ASCII85StreamTest_182, GetPSFilter_DelegatesToUnderlyingStream_182) {

    std::optional<std::string> expected_filter = "filter";

    EXPECT_CALL(*mock_stream_, getPSFilter(_, _)).WillOnce(Return(expected_filter));

    auto result = ascii85_stream_->getPSFilter(0, "");

    ASSERT_EQ(result, expected_filter);

}



TEST_F(ASCII85StreamTest_182, IsBinary_DelegatesToUnderlyingStream_182) {

    EXPECT_CALL(*mock_stream_, isBinary(false)).WillOnce(Return(true));

    bool result = ascii85_stream_->isBinary(false);

    ASSERT_TRUE(result);

}



TEST_F(ASCII85StreamTest_182, GetKind_DelegatesToUnderlyingStream_182) {

    StreamKind expected_kind = streamString;

    EXPECT_CALL(*mock_stream_, getKind()).WillOnce(Return(expected_kind));

    auto result = ascii85_stream_->getKind();

    ASSERT_EQ(result, expected_kind);

}
