#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/slice.h"

#include <string>



using namespace leveldb;



class EncodeKeyTest_356 : public ::testing::Test {

protected:

    std::string scratch;

};



TEST_F(EncodeKeyTest_356, NormalOperation_356) {

    Slice target("test_key");

    const char* result = EncodeKey(&scratch, target);

    ASSERT_EQ(scratch.size(), 8); // 4 bytes for varint size and 4 bytes for "test_key"

    ASSERT_EQ(memcmp(result, "\x08test_key", 8), 0);

}



TEST_F(EncodeKeyTest_356, EmptyString_356) {

    Slice target("");

    const char* result = EncodeKey(&scratch, target);

    ASSERT_EQ(scratch.size(), 1); // Only 1 byte for varint size (0)

    ASSERT_EQ(memcmp(result, "\x00", 1), 0);

}



TEST_F(EncodeKeyTest_356, SingleCharacter_356) {

    Slice target("a");

    const char* result = EncodeKey(&scratch, target);

    ASSERT_EQ(scratch.size(), 2); // 1 byte for varint size (1) and 1 byte for "a"

    ASSERT_EQ(memcmp(result, "\x01a", 2), 0);

}



TEST_F(EncodeKeyTest_356, LargeString_356) {

    std::string large_key(1024, 'a');

    Slice target(large_key);

    const char* result = EncodeKey(&scratch, target);

    ASSERT_EQ(scratch.size(), 1029); // 5 bytes for varint size (1024) and 1024 bytes for "a"s

    ASSERT_EQ(memcmp(result, "\x80\x08", 2), 0); // Varint representation of 1024 starts with \x80\x08

}



TEST_F(EncodeKeyTest_356, MaxVarintSize_356) {

    std::string max_key(16383, 'a'); // This will result in a 3-byte varint

    Slice target(max_key);

    const char* result = EncodeKey(&scratch, target);

    ASSERT_EQ(scratch.size(), 16386); // 3 bytes for varint size (16383) and 16383 bytes for "a"s

    ASSERT_EQ(memcmp(result, "\xff\x7f", 2), 0); // Varint representation of 16383 starts with \xff\x7f

}
