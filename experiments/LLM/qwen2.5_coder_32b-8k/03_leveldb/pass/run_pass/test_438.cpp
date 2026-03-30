#include <gtest/gtest.h>

#include <string>

#include "util/coding.cc"



namespace leveldb {



class CodingTest_438 : public ::testing::Test {

protected:

    std::string dst;

};



TEST_F(CodingTest_438, PutFixed32AppendsCorrectValue_438) {

    uint32_t value = 0x12345678;

    PutFixed32(&dst, value);

    EXPECT_EQ(dst.size(), sizeof(value));

    EXPECT_EQ(memcmp(dst.data(), &value, sizeof(value)), 0);

}



TEST_F(CodingTest_438, PutFixed32AppendsMultipleValuesCorrectly_438) {

    uint32_t value1 = 0x12345678;

    uint32_t value2 = 0x9ABCDEF0;

    PutFixed32(&dst, value1);

    PutFixed32(&dst, value2);

    EXPECT_EQ(dst.size(), sizeof(value1) + sizeof(value2));

    EXPECT_EQ(memcmp(dst.data(), &value1, sizeof(value1)), 0);

    EXPECT_EQ(memcmp(dst.data() + sizeof(value1), &value2, sizeof(value2)), 0);

}



TEST_F(CodingTest_438, PutFixed32HandlesZeroValue_438) {

    uint32_t value = 0;

    PutFixed32(&dst, value);

    EXPECT_EQ(dst.size(), sizeof(value));

    EXPECT_EQ(memcmp(dst.data(), &value, sizeof(value)), 0);

}



TEST_F(CodingTest_438, PutFixed32HandlesMaxValue_438) {

    uint32_t value = 0xFFFFFFFF;

    PutFixed32(&dst, value);

    EXPECT_EQ(dst.size(), sizeof(value));

    EXPECT_EQ(memcmp(dst.data(), &value, sizeof(value)), 0);

}



} // namespace leveldb
