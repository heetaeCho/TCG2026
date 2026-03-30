#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/exp.cpp"

#include "yaml-cpp/src/stream.h"



using namespace YAML::Exp;

using ::testing::Return;



class MockStream : public YAML::Stream {

public:

    MOCK_METHOD(char, get, (), (override));

    MOCK_METHOD(std::string, get, (int n), (override));

    MOCK_METHOD(const Mark, mark, (), (const, override));

};



TEST_F(EscapeTest_167, NormalOperationValidUnicode_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(4)).WillOnce(Return("00A9"));

    EXPECT_EQ(Escape(mockStream, 4), "\xC2\xA9");

}



TEST_F(EscapeTest_167, BoundaryConditionMinValue_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(4)).WillOnce(Return("0000"));

    EXPECT_EQ(Escape(mockStream, 4), "\x00");

}



TEST_F(EscapeTest_167, BoundaryConditionMaxValue_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(8)).WillOnce(Return("10FFFF"));

    EXPECT_EQ(Escape(mockStream, 8), "\xF4\x8F\xBF\xBF");

}



TEST_F(EscapeTest_167, ErrorCaseInvalidUnicodeRange_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(4)).WillOnce(Return("D800"));

    EXPECT_THROW(Escape(mockStream, 4), ParserException);

}



TEST_F(EscapeTest_167, ErrorCaseAboveMaxUnicodeValue_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(8)).WillOnce(Return("110000"));

    EXPECT_THROW(Escape(mockStream, 8), ParserException);

}



TEST_F(EscapeTest_167, BoundaryConditionTwoByteUnicode_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(4)).WillOnce(Return("00A0"));

    EXPECT_EQ(Escape(mockStream, 4), "\xC2\xA0");

}



TEST_F(EscapeTest_167, BoundaryConditionThreeByteUnicode_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(4)).WillOnce(Return("0800"));

    EXPECT_EQ(Escape(mockStream, 4), "\xE0\xA0\x80");

}



TEST_F(EscapeTest_167, BoundaryConditionFourByteUnicode_167) {

    MockStream mockStream;

    EXPECT_CALL(mockStream, get(8)).WillOnce(Return("20000"));

    EXPECT_EQ(Escape(mockStream, 8), "\xF0\x90\x80\x80");

}
