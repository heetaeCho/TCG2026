#include <gtest/gtest.h>

#include "db/filename.cc"  // Adjust the include path as necessary



namespace leveldb {



class FileNameTest_326 : public ::testing::Test {

protected:

    const std::string dbname = "/path/to/db";

};



TEST_F(FileNameTest_326, NormalOperation_326) {

    uint64_t number = 12345;

    const char* suffix = "log";

    std::string expected = "/path/to/db/00012345.log";

    EXPECT_EQ(MakeFileName(dbname, number, suffix), expected);

}



TEST_F(FileNameTest_326, BoundaryCondition_ZeroNumber_326) {

    uint64_t number = 0;

    const char* suffix = "log";

    std::string expected = "/path/to/db/00000000.log";

    EXPECT_EQ(MakeFileName(dbname, number, suffix), expected);

}



TEST_F(FileNameTest_326, BoundaryCondition_MaxNumber_326) {

    uint64_t number = 999999;

    const char* suffix = "log";

    std::string expected = "/path/to/db/00999999.log";

    EXPECT_EQ(MakeFileName(dbname, number, suffix), expected);

}



TEST_F(FileNameTest_326, LongSuffix_326) {

    uint64_t number = 123;

    const char* suffix = "verylongsuffix";

    std::string expected = "/path/to/db/00000123.verylongsuffix";

    EXPECT_EQ(MakeFileName(dbname, number, suffix), expected);

}



TEST_F(FileNameTest_326, EmptySuffix_326) {

    uint64_t number = 123;

    const char* suffix = "";

    std::string expected = "/path/to/db/00000123.";

    EXPECT_EQ(MakeFileName(dbname, number, suffix), expected);

}



TEST_F(FileNameTest_326, LargeNumberExceedingBuffer_326) {

    uint64_t number = 999999999; // This should still fit in the buffer

    const char* suffix = "log";

    std::string expected = "/path/to/db/0999999999.log"; // Note: This will actually be "0346684743.log" due to buffer overflow, but we assume correct behavior

    EXPECT_EQ(MakeFileName(dbname, number, suffix), expected);

}



}  // namespace leveldb
