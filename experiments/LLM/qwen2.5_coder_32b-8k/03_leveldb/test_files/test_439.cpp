#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/coding.cc"  // Adjust the include path as necessary



namespace leveldb {



class CodingTest_439 : public ::testing::Test {

protected:

    std::string dest;

};



TEST_F(CodingTest_439, PutFixed64_NormalOperation_439) {

    uint64_t value = 0x123456789ABCDEF0;

    PutFixed64(&dest, value);

    EXPECT_EQ(dest.size(), sizeof(uint64_t));

}



TEST_F(CodingTest_439, PutFixed64_ZeroValue_439) {

    uint64_t value = 0;

    PutFixed64(&dest, value);

    std::string expected(sizeof(uint64_t), '\x00');

    EXPECT_EQ(dest, expected);

}



TEST_F(CodingTest_439, PutFixed64_MaxValue_439) {

    uint64_t value = UINT64_MAX;

    PutFixed64(&dest, value);

    std::string expected = "\xff\xff\xff\xff\xff\xff\xff\xff";

    EXPECT_EQ(dest, expected);

}



TEST_F(CodingTest_439, PutFixed64_MultipleWrites_439) {

    uint64_t value1 = 0x12345678;

    uint64_t value2 = 0x9ABCDEF0;

    PutFixed64(&dest, value1);

    PutFixed64(&dest, value2);

    EXPECT_EQ(dest.size(), sizeof(uint64_t) * 2);

}



}  // namespace leveldb
