#include <gtest/gtest.h>

#include "util/coding.h"



namespace leveldb {



class GetVarint32PtrFallbackTest : public ::testing::Test {};



TEST_F(GetVarint32PtrFallbackTest, NormalOperation_SingleByte_446) {

  const char data[] = {0x7F};

  uint32_t value;

  const char* result = GetVarint32PtrFallback(data, data + sizeof(data), &value);

  EXPECT_EQ(result, data + 1);

  EXPECT_EQ(value, 0x7F);

}



TEST_F(GetVarint32PtrFallbackTest, NormalOperation_TwoBytes_446) {

  const char data[] = {0xFF, 0x01};

  uint32_t value;

  const char* result = GetVarint32PtrFallback(data, data + sizeof(data), &value);

  EXPECT_EQ(result, data + 2);

  EXPECT_EQ(value, 0x7F);

}



TEST_F(GetVarint32PtrFallbackTest, NormalOperation_FiveBytes_446) {

  const char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x0F};

  uint32_t value;

  const char* result = GetVarint32PtrFallback(data, data + sizeof(data), &value);

  EXPECT_EQ(result, data + 5);

  EXPECT_EQ(value, 0x1FFFFFFF);

}



TEST_F(GetVarint32PtrFallbackTest, BoundaryCondition_ZeroValue_446) {

  const char data[] = {0x00};

  uint32_t value;

  const char* result = GetVarint32PtrFallback(data, data + sizeof(data), &value);

  EXPECT_EQ(result, data + 1);

  EXPECT_EQ(value, 0x00);

}



TEST_F(GetVarint32PtrFallbackTest, BoundaryCondition_MaxValue_446) {

  const char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x07};

  uint32_t value;

  const char* result = GetVarint32PtrFallback(data, data + sizeof(data), &value);

  EXPECT_EQ(result, data + 5);

  EXPECT_EQ(value, 0xFFFFFFFF);

}



TEST_F(GetVarint32PtrFallbackTest, ErrorCase_NotEnoughBytes_446) {

  const char data[] = {0xFF};

  uint32_t value;

  const char* result = GetVarint32PtrFallback(data, data + sizeof(data), &value);

  EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



TEST_F(GetVarint32PtrFallbackTest, ErrorCase_InvalidByteSequence_446) {

  const char data[] = {0x80};

  uint32_t value;

  const char* result = GetVarint32PtrFallback(data, data + sizeof(data), &value);

  EXPECT_EQ(result, static_cast<const char*>(nullptr));

}



} // namespace leveldb
