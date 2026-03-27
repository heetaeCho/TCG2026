#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include <string>

#include "poppler/GlobalParams.h"

#include "utils/printencodings.cc"



using ::testing::NiceMock;

using ::testing::Return;



class MockGlobalParams : public GlobalParams {

public:

    MOCK_METHOD(std::vector<std::string>, getEncodingNames, (), (override));

};



TEST_F(PrintEncodingsTest_2718, NoEncodingsAvailable_2718) {

    NiceMock<MockGlobalParams> mockGlobalParams;

    globalParams.reset(&mockGlobalParams);

    

    EXPECT_CALL(mockGlobalParams, getEncodingNames()).WillOnce(Return(std::vector<std::string>{}));



    testing::internal::CaptureStdout();

    printEncodings();

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Available encodings are:\n");

}



TEST_F(PrintEncodingsTest_2718, SingleEncodingAvailable_2718) {

    NiceMock<MockGlobalParams> mockGlobalParams;

    globalParams.reset(&mockGlobalParams);

    

    std::vector<std::string> encNames = {"UTF-8"};

    EXPECT_CALL(mockGlobalParams, getEncodingNames()).WillOnce(Return(encNames));



    testing::internal::CaptureStdout();

    printEncodings();

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Available encodings are:\nUTF-8\n");

}



TEST_F(PrintEncodingsTest_2718, MultipleEncodingsAvailableSorted_2718) {

    NiceMock<MockGlobalParams> mockGlobalParams;

    globalParams.reset(&mockGlobalParams);

    

    std::vector<std::string> encNames = {"ISO-8859-1", "UTF-8", "Windows-1252"};

    EXPECT_CALL(mockGlobalParams, getEncodingNames()).WillOnce(Return(encNames));



    testing::internal::CaptureStdout();

    printEncodings();

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Available encodings are:\nISO-8859-1\nUTF-8\nWindows-1252\n");

}



TEST_F(PrintEncodingsTest_2718, EncodingsWithSpecialCharactersSorted_2718) {

    NiceMock<MockGlobalParams> mockGlobalParams;

    globalParams.reset(&mockGlobalParams);

    

    std::vector<std::string> encNames = {"ISO-8859-1", "UTF-8", "Windows-1252", "ASCII"};

    EXPECT_CALL(mockGlobalParams, getEncodingNames()).WillOnce(Return(encNames));



    testing::internal::CaptureStdout();

    printEncodings();

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Available encodings are:\nASCII\nISO-8859-1\nUTF-8\nWindows-1252\n");

}



TEST_F(PrintEncodingsTest_2718, LargeNumberOfEncodingsSorted_2718) {

    NiceMock<MockGlobalParams> mockGlobalParams;

    globalParams.reset(&mockGlobalParams);

    

    std::vector<std::string> encNames = {"UTF-32", "ISO-8859-1", "UTF-8", "Windows-1252", "ASCII", "UTF-16"};

    EXPECT_CALL(mockGlobalParams, getEncodingNames()).WillOnce(Return(encNames));



    testing::internal::CaptureStdout();

    printEncodings();

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Available encodings are:\nASCII\nISO-8859-1\nUTF-8\nUTF-16\nUTF-32\nWindows-1252\n");

}
