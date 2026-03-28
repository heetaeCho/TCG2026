#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include <string>
#include <cstring>

namespace leveldb {

// Helper to create an internal key from a user key by appending 8 bytes
std::string MakeInternalKey(const std::string& user_key, uint64_t tag = 0) {
  std::string result = user_key;
  char buf[8];
  std::memcpy(buf, &tag, 8);
  result.append(buf, 8);
  return result;
}

TEST(ExtractUserKeyTest_48, BasicExtraction_48) {
  std::string internal = MakeInternalKey("hello");
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(result.ToString(), "hello");
}

TEST(ExtractUserKeyTest_48, MinimumSizeKey_48) {
  // Internal key with exactly 8 bytes means empty user key
  std::string internal(8, '\0');
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 0u);
  EXPECT_EQ(result.ToString(), "");
}

TEST(ExtractUserKeyTest_48, SingleCharUserKey_48) {
  std::string internal = MakeInternalKey("a");
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 1u);
  EXPECT_EQ(result.ToString(), "a");
}

TEST(ExtractUserKeyTest_48, LongUserKey_48) {
  std::string user_key(1000, 'x');
  std::string internal = MakeInternalKey(user_key);
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 1000u);
  EXPECT_EQ(result.ToString(), user_key);
}

TEST(ExtractUserKeyTest_48, UserKeyWithNullBytes_48) {
  std::string user_key("ab\0cd", 5);
  std::string internal = MakeInternalKey(user_key);
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(std::string(result.data(), result.size()), user_key);
}

TEST(ExtractUserKeyTest_48, DataPointerMatchesOriginal_48) {
  std::string internal = MakeInternalKey("testkey");
  Slice internal_slice(internal);
  Slice result = ExtractUserKey(internal_slice);
  // The returned slice should point to the same data as the input
  EXPECT_EQ(result.data(), internal_slice.data());
}

TEST(ExtractUserKeyTest_48, NonZeroTag_48) {
  uint64_t tag = 0x0102030405060708ULL;
  std::string internal = MakeInternalKey("mykey", tag);
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(result.ToString(), "mykey");
}

TEST(ExtractUserKeyTest_48, ExactlyNineBytesInternal_48) {
  // 9 bytes total = 1 byte user key + 8 bytes tag
  std::string internal(9, 'Z');
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 1u);
  EXPECT_EQ(result.data()[0], 'Z');
}

TEST(ExtractUserKeyTest_48, BinaryUserKey_48) {
  // User key with all possible byte values
  std::string user_key;
  for (int i = 0; i < 256; i++) {
    user_key.push_back(static_cast<char>(i));
  }
  std::string internal = MakeInternalKey(user_key);
  Slice result = ExtractUserKey(Slice(internal));
  EXPECT_EQ(result.size(), 256u);
  EXPECT_EQ(std::string(result.data(), result.size()), user_key);
}

TEST(ExtractUserKeyTest_48, MultipleCallsSameInput_48) {
  std::string internal = MakeInternalKey("consistent");
  Slice internal_slice(internal);
  Slice result1 = ExtractUserKey(internal_slice);
  Slice result2 = ExtractUserKey(internal_slice);
  EXPECT_EQ(result1.data(), result2.data());
  EXPECT_EQ(result1.size(), result2.size());
  EXPECT_EQ(result1.ToString(), result2.ToString());
}

}  // namespace leveldb
