#include <gtest/gtest.h>

#include "db/version_edit.h"

#include "db/dbformat.h"



using namespace leveldb;



class VersionEditTest_339 : public ::testing::Test {

protected:

    VersionEdit version_edit_;

};



TEST_F(VersionEditTest_339, EncodeTo_EmptyVersionEdit_339) {

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    EXPECT_TRUE(encoded.empty());

}



TEST_F(VersionEditTest_339, EncodeTo_SetComparatorName_339) {

    version_edit_.SetComparatorName("test_comparator");

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the comparator tag and name are present

    EXPECT_EQ(encoded[0], static_cast<char>(kComparator));

}



TEST_F(VersionEditTest_339, EncodeTo_SetLogNumber_339) {

    uint64_t log_number = 12345;

    version_edit_.SetLogNumber(log_number);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the log number tag and value are present

    EXPECT_EQ(encoded[0], static_cast<char>(kLogNumber));

}



TEST_F(VersionEditTest_339, EncodeTo_SetPrevLogNumber_339) {

    uint64_t prev_log_number = 54321;

    version_edit_.SetPrevLogNumber(prev_log_number);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the previous log number tag and value are present

    EXPECT_EQ(encoded[0], static_cast<char>(kPrevLogNumber));

}



TEST_F(VersionEditTest_339, EncodeTo_SetNextFileNumber_339) {

    uint64_t next_file_number = 112233;

    version_edit_.SetNextFile(next_file_number);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the next file number tag and value are present

    EXPECT_EQ(encoded[0], static_cast<char>(kNextFileNumber));

}



TEST_F(VersionEditTest_339, EncodeTo_SetLastSequence_339) {

    SequenceNumber last_sequence = 98765;

    version_edit_.SetLastSequence(last_sequence);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the last sequence tag and value are present

    EXPECT_EQ(encoded[0], static_cast<char>(kLastSequence));

}



TEST_F(VersionEditTest_339, EncodeTo_SetCompactPointer_339) {

    int level = 2;

    InternalKey key("test_key", 12345, kTypeValue);

    version_edit_.SetCompactPointer(level, key);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the compact pointer tag and values are present

    EXPECT_EQ(encoded[0], static_cast<char>(kCompactPointer));

}



TEST_F(VersionEditTest_339, EncodeTo_AddFile_339) {

    int level = 1;

    uint64_t file_number = 1001;

    uint64_t file_size = 2048;

    InternalKey smallest("smallest_key", 12345, kTypeValue);

    InternalKey largest("largest_key", 67890, kTypeValue);

    version_edit_.AddFile(level, file_number, file_size, smallest, largest);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the new file tag and values are present

    EXPECT_EQ(encoded[0], static_cast<char>(kNewFile));

}



TEST_F(VersionEditTest_339, EncodeTo_RemoveFile_339) {

    int level = 1;

    uint64_t file_number = 2002;

    version_edit_.RemoveFile(level, file_number);

    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if the deleted file tag and values are present

    EXPECT_EQ(encoded[0], static_cast<char>(kDeletedFile));

}



TEST_F(VersionEditTest_339, EncodeTo_MultipleFieldsSet_339) {

    version_edit_.SetComparatorName("test_comparator");

    version_edit_.SetLogNumber(12345);

    version_edit_.SetPrevLogNumber(54321);

    version_edit_.SetNextFile(112233);

    version_edit_.SetLastSequence(98765);

    

    int level = 2;

    InternalKey key("test_key", 12345, kTypeValue);

    version_edit_.SetCompactPointer(level, key);



    version_edit_.AddFile(1, 1001, 2048, InternalKey("smallest_key", 12345, kTypeValue), InternalKey("largest_key", 67890, kTypeValue));

    

    version_edit_.RemoveFile(1, 2002);



    std::string encoded;

    version_edit_.EncodeTo(&encoded);

    // Check if all tags are present

    EXPECT_TRUE(encoded.find(static_cast<char>(kComparator)) != std::string::npos);

    EXPECT_TRUE(encoded.find(static_cast<char>(kLogNumber)) != std::string::npos);

    EXPECT_TRUE(encoded.find(static_cast<char>(kPrevLogNumber)) != std::string::npos);

    EXPECT_TRUE(encoded.find(static_cast<char>(kNextFileNumber)) != std::string::npos);

    EXPECT_TRUE(encoded.find(static_cast<char>(kLastSequence)) != std::string::npos);

    EXPECT_TRUE(encoded.find(static_cast<char>(kCompactPointer)) != std::string::npos);

    EXPECT_TRUE(encoded.find(static_cast<char>(kNewFile)) != std::string::npos);

    EXPECT_TRUE(encoded.find(static_cast<char>(kDeletedFile)) != std::string::npos);

}
