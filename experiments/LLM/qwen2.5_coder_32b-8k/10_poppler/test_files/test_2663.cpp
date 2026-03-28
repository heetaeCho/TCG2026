#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include <string>



using namespace testing;



// Mock class for UnicodeMap

class MockUnicodeMap : public UnicodeMap {

public:

    MOCK_METHOD3(mapUnicode, int(Unicode u, char* buf, int bufSize));

};



TEST(printUCS4StringTest_2663, NormalOperation_2663) {

    std::vector<Unicode> u = {0x41, 0x42, 0x43}; // 'A', 'B', 'C'

    char expected[] = "ABC";

    char output[4] = {0};



    MockUnicodeMap mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(0x41, _, _))

        .WillOnce(DoAll(SetArg2ToCString("A"), Return(1)));

    EXPECT_CALL(mockUnicodeMap, mapUnicode(0x42, _, _))

        .WillOnce(DoAll(SetArg2ToCString("B"), Return(1)));

    EXPECT_CALL(mockUnicodeMap, mapUnicode(0x43, _, _))

        .WillOnce(DoAll(SetArg2ToCString("C"), Return(1)));



    testing::internal::CaptureStdout();

    printUCS4String(u, &mockUnicodeMap);

    std::string outputStr = testing::internal::GetCapturedStdout();



    EXPECT_EQ(outputStr, expected);

}



TEST(printUCS4StringTest_2663, BoundaryCondition_EmptyVector_2663) {

    std::vector<Unicode> u = {};

    char expected[] = "";

    char output[1] = {0};



    MockUnicodeMap mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(_, _, _)).Times(0);



    testing::internal::CaptureStdout();

    printUCS4String(u, &mockUnicodeMap);

    std::string outputStr = testing::internal::GetCapturedStdout();



    EXPECT_EQ(outputStr, expected);

}



TEST(printUCS4StringTest_2663, BoundaryCondition_MaxUnicodeValue_2663) {

    std::vector<Unicode> u = {0x10FFFF}; // Max Unicode value

    char expected[] = "\xF4\x8F\xBF\xBF"; // UTF-8 representation of U+10FFFF

    char output[5] = {0};



    MockUnicodeMap mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(0x10FFFF, _, _))

        .WillOnce(DoAll(SetArg2ToCString("\xF4\x8F\xBF\xBF"), Return(4)));



    testing::internal::CaptureStdout();

    printUCS4String(u, &mockUnicodeMap);

    std::string outputStr = testing::internal::GetCapturedStdout();



    EXPECT_EQ(outputStr, expected);

}



TEST(printUCS4StringTest_2663, ExceptionalCase_BufferTooSmall_2663) {

    std::vector<Unicode> u = {0x1F600}; // Grinning Face emoji

    char expected[] = "\xF0\x9F\x98\x80"; // UTF-8 representation of U+1F600

    char output[4] = {0};



    MockUnicodeMap mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(0x1F600, _, 3))

        .WillOnce(Return(4)); // Simulate buffer size issue



    testing::internal::CaptureStdout();

    printUCS4String(u, &mockUnicodeMap);

    std::string outputStr = testing::internal::GetCapturedStdout();



    EXPECT_EQ(outputStr, ""); // No valid output due to buffer size

}
