#include <gtest/gtest.h>

#include "stream.cpp"



namespace YAML {



class ReadBufferTest_178 : public ::testing::Test {

protected:

    unsigned char buffer[10];

};



TEST_F(ReadBufferTest_178, ReadBuffer_ReturnsValidPointer_178) {

    char* result = ReadBuffer(buffer);

    EXPECT_EQ(result, reinterpret_cast<char*>(buffer));

}



TEST_F(ReadBufferTest_178, ReadBuffer_HandlesNullPointer_178) {

    unsigned char* null_buffer = nullptr;

    char* result = ReadBuffer(null_buffer);

    EXPECT_EQ(result, reinterpret_cast<char*>(null_buffer));

}



}  // namespace YAML
