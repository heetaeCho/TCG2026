#include "gtest/gtest.h"

#include "db/version_edit.h"

#include "leveldb/status.h"



using namespace leveldb;



TEST_F(VersionEditTest_342, DecodeFrom_EmptySlice_ReturnsOK_342) {

  Slice empty_slice;

  VersionEdit ve;

  Status status = ve.DecodeFrom(empty_slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidComparator_ReturnsOK_342) {

  std::string comparator = "leveldb.BytewiseComparator";

  std::string encoded = "\x01\x0c" + comparator; // tag 1 (varint), length of comparator (varint), comparator

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidLogNumber_ReturnsOK_342) {

  uint64_t log_number = 12345;

  std::string encoded = "\x02\x9a\xa9\x8c\x01"; // tag 2 (varint), log_number (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidPrevLogNumber_ReturnsOK_342) {

  uint64_t prev_log_number = 54321;

  std::string encoded = "\x09\xb9\xa6\x8d\x01"; // tag 9 (varint), prev_log_number (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidNextFileNumber_ReturnsOK_342) {

  uint64_t next_file_number = 98765;

  std::string encoded = "\x03\xad\xa2\x8b\x01"; // tag 3 (varint), next_file_number (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidLastSequence_ReturnsOK_342) {

  uint64_t last_sequence = 987654321;

  std::string encoded = "\x04\x91\xc2\xf2\x65\x0e"; // tag 4 (varint), last_sequence (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidCompactPointer_ReturnsOK_342) {

  InternalKey key("key1", 0x1000, kValueTypeForSeek);

  std::string key_encoded = "\x05\x04key1\x00\x10\x80\x00"; // tag 5 (varint), level (varint), key (length-prefixed)

  Slice slice(key_encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidDeletedFile_ReturnsOK_342) {

  std::string deleted_file = "\x06\x01\x9a\xa9\x8c\x01"; // tag 6 (varint), level (varint), file_number (varint)

  Slice slice(deleted_file);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_ValidNewFile_ReturnsOK_342) {

  InternalKey smallest("smallest", 0x1000, kValueTypeForSeek);

  InternalKey largest("largest", 0x1000, kValueTypeForSeek);

  std::string new_file = "\x07\x01\x9a\xa9\x8c\x01\xc8\x83\x9a\x06smallest\x00\x10\x80\x00largest\x00\x10\x80\x00"; // tag 7 (varint), level (varint), file_number (varint), file_size (varint), smallest (length-prefixed), largest (length-prefixed)

  Slice slice(new_file);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.ok());

}



TEST_F(VersionEditTest_342, DecodeFrom_UnknownTag_ReturnsCorruption_342) {

  std::string unknown_tag = "\xff"; // tag ff (unknown)

  Slice slice(unknown_tag);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedComparator_ReturnsCorruption_342) {

  std::string comparator = "leveldb.BytewiseComparator";

  std::string encoded = "\x01\x0c" + comparator.substr(0, 5); // tag 1 (varint), length of comparator (varint), truncated comparator

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedLogNumber_ReturnsCorruption_342) {

  std::string encoded = "\x02"; // tag 2 (varint), truncated log_number (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedPrevLogNumber_ReturnsCorruption_342) {

  std::string encoded = "\x09"; // tag 9 (varint), truncated prev_log_number (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedNextFileNumber_ReturnsCorruption_342) {

  std::string encoded = "\x03"; // tag 3 (varint), truncated next_file_number (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedLastSequence_ReturnsCorruption_342) {

  std::string encoded = "\x04"; // tag 4 (varint), truncated last_sequence (varint)

  Slice slice(encoded);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedCompactPointer_ReturnsCorruption_342) {

  std::string compact_pointer = "\x05\x01"; // tag 5 (varint), level (varint)

  Slice slice(compact_pointer);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedDeletedFile_ReturnsCorruption_342) {

  std::string deleted_file = "\x06\x01"; // tag 6 (varint), level (varint)

  Slice slice(deleted_file);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}



TEST_F(VersionEditTest_342, DecodeFrom_TruncatedNewFile_ReturnsCorruption_342) {

  std::string new_file = "\x07\x01\x9a\xa9\x8c\x01\xc8\x83"; // tag 7 (varint), level (varint), file_number (varint), truncated file_size (varint)

  Slice slice(new_file);

  VersionEdit ve;

  Status status = ve.DecodeFrom(slice);

  EXPECT_TRUE(status.IsCorruption());

}
