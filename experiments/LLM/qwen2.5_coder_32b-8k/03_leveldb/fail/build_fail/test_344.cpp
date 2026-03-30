#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/log_format.h"

#include "db/log_writer.cc"  // For InitTypeCrc function



namespace leveldb {

namespace log {



class LogWriterTest_344 : public ::testing::Test {

protected:

    uint32_t type_crc_[kMaxRecordType + 1];

};



TEST_F(LogWriterTest_344, InitTypeCrc_SetsCorrectValuesForAllTypes_344) {

    // Arrange

    memset(type_crc_, 0, sizeof(type_crc_));

    

    // Act

    InitTypeCrc(type_crc_);

    

    // Assert

    for (int i = 0; i <= kMaxRecordType; ++i) {

        EXPECT_NE(type_crc_[i], 0);

    }

}



TEST_F(LogWriterTest_344, InitTypeCrc_DoesNotModifyUnrelatedMemory_344) {

    // Arrange

    memset(type_crc_, 0xFF, sizeof(type_crc_));

    uint32_t before = type_crc_[kMaxRecordType + 1];

    

    // Act

    InitTypeCrc(type_crc_);

    

    // Assert

    EXPECT_EQ(type_crc_[kMaxRecordType + 1], before);

}



}  // namespace log

}  // namespace leveldb
