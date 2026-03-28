#include <gtest/gtest.h>

#include "db/filename.cc"



namespace leveldb {



class FilenameTest_330 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(FilenameTest_330, DescriptorFileName_NormalOperation_330) {

    std::string dbname = "testdb";

    uint64_t number = 123;

    std::string expected = "testdb/MANIFEST-000000123";

    EXPECT_EQ(DescriptorFileName(dbname, number), expected);

}



TEST_F(FilenameTest_330, DescriptorFileName_BoundaryCondition_MinNumber_330) {

    std::string dbname = "testdb";

    uint64_t number = 1;

    std::string expected = "testdb/MANIFEST-000000001";

    EXPECT_EQ(DescriptorFileName(dbname, number), expected);

}



TEST_F(FilenameTest_330, DescriptorFileName_BoundaryCondition_MaxNumber_330) {

    std::string dbname = "testdb";

    uint64_t number = 999999;

    std::string expected = "testdb/MANIFEST-009999999";

    EXPECT_EQ(DescriptorFileName(dbname, number), expected);

}



TEST_F(FilenameTest_330, DescriptorFileName_Exceptional_ZeroNumber_330) {

    std::string dbname = "testdb";

    uint64_t number = 0;

    // Since the function asserts that number > 0, it will not return in normal execution.

    // We cannot test this directly with Google Test without changing the behavior of assert.

    // Assuming the assert is active, this would cause a test failure if reached.

}



TEST_F(FilenameTest_330, DescriptorFileName_Exceptional_LargeNumber_330) {

    std::string dbname = "testdb";

    uint64_t number = 123456789;

    std::string expected = "testdb/MANIFEST-123456789"; // Only first 6 digits are used

    EXPECT_EQ(DescriptorFileName(dbname, number), expected);

}



} // namespace leveldb
