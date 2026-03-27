#include <gtest/gtest.h>

#include "leveldb/slice.h"

#include "util/coding.h"



class PutLengthPrefixedSliceTest_444 : public ::testing::Test {

protected:

    std::string dst;

};



TEST_F(PutLengthPrefixedSliceTest_444, EmptyString_444) {

    leveldb::Slice value("");

    leveldb::PutLengthPrefixedSlice(&dst, value);

    EXPECT_EQ(dst.size(), 1); // Only the varint for size (0)

    EXPECT_EQ(dst[0], static_cast<char>(0x00)); // Varint encoding of 0

}



TEST_F(PutLengthPrefixedSliceTest_444, SingleCharacterString_444) {

    leveldb::Slice value("a");

    leveldb::PutLengthPrefixedSlice(&dst, value);

    EXPECT_EQ(dst.size(), 2); // Varint for size (1) + character 'a'

    EXPECT_EQ(dst[0], static_cast<char>(0x01)); // Varint encoding of 1

    EXPECT_EQ(dst[1], 'a');

}



TEST_F(PutLengthPrefixedSliceTest_444, MultipleCharactersString_444) {

    leveldb::Slice value("hello");

    leveldb::PutLengthPrefixedSlice(&dst, value);

    EXPECT_EQ(dst.size(), 6); // Varint for size (5) + characters "hello"

    EXPECT_EQ(dst[0], static_cast<char>(0x05)); // Varint encoding of 5

    EXPECT_EQ(dst.substr(1), "hello");

}



TEST_F(PutLengthPrefixedSliceTest_444, LargeString_444) {

    std::string large_string(65535, 'a'); // A string with length 65535

    leveldb::Slice value(large_string);

    leveldb::PutLengthPrefixedSlice(&dst, value);

    EXPECT_EQ(dst.size(), 65540); // Varint for size (5 bytes) + characters 'a'

    EXPECT_EQ(dst[0], static_cast<char>(0xFF)); // First byte of varint encoding

    EXPECT_EQ(dst[1], static_cast<char>(0xFF)); // Second byte of varint encoding

    EXPECT_EQ(dst[2], static_cast<char>(0x7F)); // Third byte of varint encoding

    EXPECT_EQ(dst.substr(3), large_string);

}



TEST_F(PutLengthPrefixedSliceTest_444, BoundaryConditionSingleByteVarint_444) {

    std::string boundary_string(127, 'a'); // A string with length 127 (single-byte varint)

    leveldb::Slice value(boundary_string);

    leveldb::PutLengthPrefixedSlice(&dst, value);

    EXPECT_EQ(dst.size(), 128); // Varint for size (1 byte) + characters 'a'

    EXPECT_EQ(dst[0], static_cast<char>(0x7F)); // Varint encoding of 127

    EXPECT_EQ(dst.substr(1), boundary_string);

}



TEST_F(PutLengthPrefixedSliceTest_444, BoundaryConditionMultiByteVarint_444) {

    std::string boundary_string(128, 'a'); // A string with length 128 (multi-byte varint)

    leveldb::Slice value(boundary_string);

    leveldb::PutLengthPrefixedSlice(&dst, value);

    EXPECT_EQ(dst.size(), 129); // Varint for size (2 bytes) + characters 'a'

    EXPECT_EQ(dst[0], static_cast<char>(0x80)); // First byte of varint encoding

    EXPECT_EQ(dst[1], static_cast<char>(0x01)); // Second byte of varint encoding

    EXPECT_EQ(dst.substr(2), boundary_string);

}
