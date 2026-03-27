#include <gtest/gtest.h>

#include "db/version_set.cc"

#include "leveldb/options.h"



namespace leveldb {



class VersionSetTest_127 : public ::testing::Test {

protected:

    Options options_;

};



TEST_F(VersionSetTest_127, ExpandedCompactionByteSizeLimit_NormalOperation_127) {

    int64_t result = ExpandedCompactionByteSizeLimit(&options_);

    EXPECT_EQ(result, 25 * TargetFileSize(&options_));

}



TEST_F(VersionSetTest_127, ExpandedCompactionByteSizeLimit_BoundaryCondition_MaxFileSize_127) {

    options_.max_file_size = 0;

    int64_t result = ExpandedCompactionByteSizeLimit(&options_);

    EXPECT_EQ(result, 25 * TargetFileSize(&options_));

}



TEST_F(VersionSetTest_127, ExpandedCompactionByteSizeLimit_BoundaryCondition_TargetFileSize_127) {

    options_.max_file_size = std::numeric_limits<size_t>::max();

    int64_t result = ExpandedCompactionByteSizeLimit(&options_);

    EXPECT_EQ(result, 25 * TargetFileSize(&options_));

}



}  // namespace leveldb

```


