#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "port/port_stdcxx.h"



namespace leveldb {

namespace port {



class Zstd_CompressTest_39 : public ::testing::Test {};



TEST_F(Zstd_CompressTest_39, CompressReturnsTrueForValidInput_39) {

    std::string output;

    const char* input = "test";

    size_t length = 4;

    int level = 1;



    bool result = Zstd_Compress(level, input, length, &output);



    EXPECT_TRUE(result);

}



TEST_F(Zstd_CompressTest_39, CompressReturnsFalseForEmptyInput_39) {

    std::string output;

    const char* input = "";

    size_t length = 0;

    int level = 1;



    bool result = Zstd_Compress(level, input, length, &output);



    EXPECT_TRUE(result); // Assuming empty input is compressible and returns true

}



TEST_F(Zstd_CompressTest_39, CompressReturnsFalseForNullInput_39) {

    std::string output;

    const char* input = nullptr;

    size_t length = 4;

    int level = 1;



    bool result = Zstd_Compress(level, input, length, &output);



    EXPECT_FALSE(result);

}



TEST_F(Zstd_CompressTest_39, CompressReturnsFalseForNullOutput_39) {

    const char* input = "test";

    size_t length = 4;

    int level = 1;



    bool result = Zstd_Compress(level, input, length, nullptr);



    EXPECT_FALSE(result);

}



TEST_F(Zstd_CompressTest_39, CompressHandlesMaxIntLength_39) {

    std::string output;

    const char* input = "test";

    size_t length = static_cast<size_t>(-1); // max int value for size_t

    int level = 1;



    bool result = Zstd_Compress(level, input, length, &output);



    EXPECT_FALSE(result);

}



TEST_F(Zstd_CompressTest_39, CompressHandlesZeroLevel_39) {

    std::string output;

    const char* input = "test";

    size_t length = 4;

    int level = 0;



    bool result = Zstd_Compress(level, input, length, &output);



    EXPECT_TRUE(result);

}



TEST_F(Zstd_CompressTest_39, CompressHandlesHighCompressionLevel_39) {

    std::string output;

    const char* input = "test";

    size_t length = 4;

    int level = 22; // Zstandard default max compression level



    bool result = Zstd_Compress(level, input, length, &output);



    EXPECT_TRUE(result);

}



TEST_F(Zstd_CompressTest_39, CompressHandlesNegativeLevel_39) {

    std::string output;

    const char* input = "test";

    size_t length = 4;

    int level = -1;



    bool result = Zstd_Compress(level, input, length, &output);



    EXPECT_FALSE(result);

}



} // namespace port

} // namespace leveldb
