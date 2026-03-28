#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch::Detail;



// Mocking the ReusableStringStream to verify interactions

class MockReusableStringStream : public Catch::ReusableStringStream {

public:

    MOCK_METHOD0(str, std::string());

    MOCK_CONST_METHOD1(operator<<, MockReusableStringStream&(const unsigned&));

};



TEST(rawMemoryToStringTest_259, NormalOperation_259) {

    const unsigned char data[] = { 0xDE, 0xAD, 0xBE, 0xEF };

    std::string expected = "0xDEADBEEF";

    EXPECT_EQ(expected, rawMemoryToString(data, sizeof(data)));

}



TEST(rawMemoryToStringTest_259, BoundaryCondition_EmptyData_259) {

    const unsigned char data[] = {};

    std::string expected = "0x";

    EXPECT_EQ(expected, rawMemoryToString(data, 0));

}



TEST(rawMemoryToStringTest_259, BoundaryCondition_SingleByte_259) {

    const unsigned char data[] = { 0xFF };

    std::string expected = "0xFF";

    EXPECT_EQ(expected, rawMemoryToString(data, sizeof(data)));

}



TEST(rawMemoryToStringTest_259, LittleEndianBehavior_259) {

    const unsigned char data[] = { 0x01, 0x02 };

    ::testing::NiceMock<MockReusableStringStream> mockRSS;

    EXPECT_CALL(mockRSS, operator<<(static_cast<const unsigned>(0x02)))

        .WillOnce(::testing::Return(mockRSS));

    EXPECT_CALL(mockRSS, operator<<(static_cast<const unsigned>(0x01)))

        .WillOnce(::testing::Return(mockRSS));



    // Mocking the Endianness to return Little

    EXPECT_CALL(::testing::MockFunction<Endianness::Arch()>()(), ::testing::Return(Endianness::Little));

    

    rawMemoryToString(data, sizeof(data));

}



TEST(rawMemoryToStringTest_259, BigEndianBehavior_259) {

    const unsigned char data[] = { 0x01, 0x02 };

    ::testing::NiceMock<MockReusableStringStream> mockRSS;

    EXPECT_CALL(mockRSS, operator<<(static_cast<const unsigned>(0x01)))

        .WillOnce(::testing::Return(mockRSS));

    EXPECT_CALL(mockRSS, operator<<(static_cast<const unsigned>(0x02)))

        .WillOnce(::testing::Return(mockRSS));



    // Mocking the Endianness to return Big

    EXPECT_CALL(::testing::MockFunction<Endianness::Arch()>()(), ::testing::Return(Endianness::Big));

    

    rawMemoryToString(data, sizeof(data));

}
