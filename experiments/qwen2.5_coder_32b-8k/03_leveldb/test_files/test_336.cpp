#include <gtest/gtest.h>

#include "db/filename.h"

#include "leveldb/slice.h"



namespace leveldb {



class ParseFileNameTest_336 : public ::testing::Test {

protected:

    uint64_t number;

    FileType type;



    bool CallParseFileName(const std::string& filename) {

        return ParseFileName(filename, &number, &type);

    }

};



TEST_F(ParseFileNameTest_336, CurrentFileParsing_336) {

    EXPECT_TRUE(CallParseFileName("CURRENT"));

    EXPECT_EQ(number, 0);

    EXPECT_EQ(type, kCurrentFile);

}



TEST_F(ParseFileNameTest_336, DBLockFileParsing_336) {

    EXPECT_TRUE(CallParseFileName("LOCK"));

    EXPECT_EQ(number, 0);

    EXPECT_EQ(type, kDBLockFile);

}



TEST_F(ParseFileNameTest_336, InfoLogFileParsing_336) {

    EXPECT_TRUE(CallParseFileName("LOG"));

    EXPECT_EQ(number, 0);

    EXPECT_EQ(type, kInfoLogFile);



    EXPECT_TRUE(CallParseFileName("LOG.old"));

    EXPECT_EQ(number, 0);

    EXPECT_EQ(type, kInfoLogFile);

}



TEST_F(ParseFileNameTest_336, DescriptorFileParsing_336) {

    EXPECT_TRUE(CallParseFileName("MANIFEST-12345"));

    EXPECT_EQ(number, 12345);

    EXPECT_EQ(type, kDescriptorFile);



    EXPECT_FALSE(CallParseFileName("MANIFEST-abc"));

}



TEST_F(ParseFileNameTest_336, LogFileParsing_336) {

    EXPECT_TRUE(CallParseFileName("000123.log"));

    EXPECT_EQ(number, 123);

    EXPECT_EQ(type, kLogFile);



    EXPECT_FALSE(CallParseFileName("000123.lg"));

}



TEST_F(ParseFileNameTest_336, TableFileParsing_336) {

    EXPECT_TRUE(CallParseFileName("000456.sst"));

    EXPECT_EQ(number, 456);

    EXPECT_EQ(type, kTableFile);



    EXPECT_TRUE(CallParseFileName("000456.ldb"));

    EXPECT_EQ(number, 456);

    EXPECT_EQ(type, kTableFile);



    EXPECT_FALSE(CallParseFileName("000456.stt"));

}



TEST_F(ParseFileNameTest_336, TempFileParsing_336) {

    EXPECT_TRUE(CallParseFileName("000789.dbtmp"));

    EXPECT_EQ(number, 789);

    EXPECT_EQ(type, kTempFile);



    EXPECT_FALSE(CallParseFileName("000789.tmpp"));

}



TEST_F(ParseFileNameTest_336, InvalidFileNameParsing_336) {

    EXPECT_FALSE(CallParseFileName(""));

    EXPECT_FALSE(CallParseFileName("INVALID"));

    EXPECT_FALSE(CallParseFileName("MANIFEST-"));

    EXPECT_FALSE(CallParseFileName("123.log"));

}



} // namespace leveldb
