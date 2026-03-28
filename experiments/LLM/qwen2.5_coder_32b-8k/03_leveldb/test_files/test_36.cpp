#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "port/port_stdcxx.h"

#include <string>



using namespace leveldb::port;



class SnappyCompressTest_36 : public ::testing::Test {

protected:

    std::string output;

};



TEST_F(SnappyCompressTest_36, NormalOperation_CompressionSuccessful_36) {

    const char* input = "This is a test string.";

    size_t length = strlen(input);

    bool result = Snappy_Compress(input, length, &output);



    EXPECT_TRUE(result);

    EXPECT_FALSE(output.empty());

}



TEST_F(SnappyCompressTest_36, EmptyInput_ReturnsFalseOrEmptyOutput_36) {

    const char* input = "";

    size_t length = 0;

    bool result = Snappy_Compress(input, length, &output);



#if HAVE_SNAPPY

    EXPECT_TRUE(result);

    EXPECT_EQ(output.size(), 0U);

#else

    EXPECT_FALSE(result);

#endif // HAVE_SNAPPY

}



TEST_F(SnappyCompressTest_36, LargeInput_SuccessfulCompression_36) {

    std::string large_input(1024 * 1024, 'a'); // 1 MB of 'a'

    bool result = Snappy_Compress(large_input.data(), large_input.size(), &output);



    EXPECT_TRUE(result);

    EXPECT_FALSE(output.empty());

}



TEST_F(SnappyCompressTest_36, NoSnappySupport_ReturnsFalse_36) {

#if !HAVE_SNAPPY

    const char* input = "This is a test string.";

    size_t length = strlen(input);

    bool result = Snappy_Compress(input, length, &output);



    EXPECT_FALSE(result);

#endif // !HAVE_SNAPPY

}
