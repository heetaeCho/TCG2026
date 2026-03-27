#include <gtest/gtest.h>

#include <optional>

#include "Stream.h"

#include "FlateEncoder.h"



// Mock Stream class to use as a dependency in FlateEncoder tests.

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(bool, isEncoder, (), (const, override));

};



class FlateEncoderTest_1649 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mock_stream;

    std::unique_ptr<FlateEncoder> flate_encoder;



    void SetUp() override {

        mock_stream = std::make_unique<MockStream>();

        flate_encoder = std::make_unique<FlateEncoder>(mock_stream.get());

    }

};



TEST_F(FlateEncoderTest_1649, GetKind_ReturnsStrWeird_1649) {

    EXPECT_EQ(flate_encoder->getKind(), strWeird);

}



TEST_F(FlateEncoderTest_1649, Rewind_DelegatesToStream_1649) {

    EXPECT_CALL(*mock_stream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(flate_encoder->rewind());

}



TEST_F(FlateEncoderTest_1649, GetChar_DelegatesToStream_1649) {

    const int expected_char = 42;

    EXPECT_CALL(*mock_stream, getChar()).WillOnce(::testing::Return(expected_char));

    EXPECT_EQ(flate_encoder->getChar(), expected_char);

}



TEST_F(FlateEncoderTest_1649, LookChar_DelegatesToStream_1649) {

    const int expected_char = 42;

    EXPECT_CALL(*mock_stream, lookChar()).WillOnce(::testing::Return(expected_char));

    EXPECT_EQ(flate_encoder->lookChar(), expected_char);

}



TEST_F(FlateEncoderTest_1649, GetPSFilter_DelegatesToStream_1649) {

    const int psLevel = 3;

    const char* indent = "  ";

    std::optional<std::string> expected_filter = "flate";

    EXPECT_CALL(*mock_stream, getPSFilter(psLevel, indent)).WillOnce(::testing::Return(expected_filter));

    EXPECT_EQ(flate_encoder->getPSFilter(psLevel, indent), expected_filter);

}



TEST_F(FlateEncoderTest_1649, IsBinary_DelegatesToStream_1649) {

    const bool last = true;

    EXPECT_CALL(*mock_stream, isBinary(last)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(flate_encoder->isBinary(last));

}



TEST_F(FlateEncoderTest_1649, IsEncoder_ReturnsTrue_1649) {

    EXPECT_TRUE(flate_encoder->isEncoder());

}
