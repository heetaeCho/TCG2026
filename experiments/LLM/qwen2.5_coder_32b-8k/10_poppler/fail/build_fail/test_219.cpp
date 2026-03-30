#include <gtest/gtest.h>

#include "Stream.h"

#include <optional>



// Mock Stream class for testing ASCII85Encoder

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char *), (override));

    MOCK_METHOD(bool, isBinary, (bool) const, (override));

};



TEST_F(StreamTest_219, IsEncoderReturnsTrue_219) {

    MockStream mockStream;

    ASCII85Encoder encoder(&mockStream);

    EXPECT_TRUE(encoder.isEncoder());

}



TEST_F(StreamTest_219, RewindDelegatesToStream_219) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, rewind()).WillOnce(::testing::Return(true));

    ASCII85Encoder encoder(&mockStream);

    EXPECT_TRUE(encoder.rewind());

}



TEST_F(StreamTest_219, GetKindDelegatesToStream_219) {

    MockStream mockStream;

    StreamKind expectedKind = strFile;

    EXPECT_CALL(mockStream, getKind()).WillOnce(::testing::Return(expectedKind));

    ASCII85Encoder encoder(&mockStream);

    EXPECT_EQ(encoder.getKind(), expectedKind);

}



TEST_F(StreamTest_219, GetCharDelegatesToStream_219) {

    MockStream mockStream;

    int expectedChar = 42;

    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(expectedChar));

    ASCII85Encoder encoder(&mockStream);

    EXPECT_EQ(encoder.getChar(), expectedChar);

}



TEST_F(StreamTest_219, LookCharDelegatesToStream_219) {

    MockStream mockStream;

    int expectedChar = 42;

    EXPECT_CALL(mockStream, lookChar()).WillOnce(::testing::Return(expectedChar));

    ASCII85Encoder encoder(&mockStream);

    EXPECT_EQ(encoder.lookChar(), expectedChar);

}



TEST_F(StreamTest_219, GetPSFilterDelegatesToStream_219) {

    MockStream mockStream;

    std::optional<std::string> expectedResult = "filter";

    EXPECT_CALL(mockStream, getPSFilter(::testing::_, ::testing::_)).WillOnce(::testing::Return(expectedResult));

    ASCII85Encoder encoder(&mockStream);

    EXPECT_EQ(encoder.getPSFilter(0, ""), expectedResult);

}



TEST_F(StreamTest_219, IsBinaryDelegatesToStream_219) {

    MockStream mockStream;

    bool expectedValue = true;

    EXPECT_CALL(mockStream, isBinary(::testing::_)).WillOnce(::testing::Return(expectedValue));

    ASCII85Encoder encoder(&mockStream);

    EXPECT_EQ(encoder.isBinary(true), expectedValue);

}



TEST_F(StreamTest_219, BoundaryConditionRewindFalse_219) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, rewind()).WillOnce(::testing::Return(false));

    ASCII85Encoder encoder(&mockStream);

    EXPECT_FALSE(encoder.rewind());

}
