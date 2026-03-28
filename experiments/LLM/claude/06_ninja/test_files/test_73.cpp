#include "gtest/gtest.h"
#include "hash_map.h"
#include "string_piece.h"
#include <string>
#include <unordered_set>
#include <unordered_map>

// The hash functor under test
using Hasher = std::hash<StringPiece>;

class HashMapTest_73 : public ::testing::Test {
 protected:
  Hasher hasher;
};

// Normal operation: hashing a simple string
TEST_F(HashMapTest_73, HashSimpleString_73) {
  StringPiece sp("hello");
  size_t h = hasher(sp);
  // Just verify it returns a value (deterministic)
  EXPECT_EQ(h, hasher(sp));
}

// Normal operation: same content produces same hash
TEST_F(HashMapTest_73, SameContentSameHash_73) {
  std::string s1 = "test_string";
  std::string s2 = "test_string";
  StringPiece sp1(s1);
  StringPiece sp2(s2);
  EXPECT_EQ(hasher(sp1), hasher(sp2));
}

// Normal operation: different strings likely produce different hashes
TEST_F(HashMapTest_73, DifferentStringsDifferentHash_73) {
  StringPiece sp1("alpha");
  StringPiece sp2("beta");
  // While hash collisions are possible, these short distinct strings should differ
  EXPECT_NE(hasher(sp1), hasher(sp2));
}

// Boundary: empty string
TEST_F(HashMapTest_73, EmptyStringHash_73) {
  StringPiece sp("", 0);
  size_t h = hasher(sp);
  // Should be deterministic
  EXPECT_EQ(h, hasher(sp));
}

// Boundary: single character
TEST_F(HashMapTest_73, SingleCharHash_73) {
  StringPiece sp("a");
  size_t h = hasher(sp);
  EXPECT_EQ(h, hasher(StringPiece("a")));
}

// Boundary: single character different chars produce different hashes
TEST_F(HashMapTest_73, SingleCharDifferentHash_73) {
  StringPiece sp_a("a");
  StringPiece sp_b("b");
  EXPECT_NE(hasher(sp_a), hasher(sp_b));
}

// Hashing with explicit length (substring)
TEST_F(HashMapTest_73, SubstringHash_73) {
  const char* data = "hello_world";
  StringPiece sp1(data, 5);  // "hello"
  StringPiece sp2("hello");
  EXPECT_EQ(hasher(sp1), hasher(sp2));
}

// Different lengths with same prefix should produce different hashes
TEST_F(HashMapTest_73, DifferentLengthsSamePrefix_73) {
  StringPiece sp1("hello");
  StringPiece sp2("hell");
  EXPECT_NE(hasher(sp1), hasher(sp2));
}

// Consistency: calling hash multiple times yields same result
TEST_F(HashMapTest_73, ConsistencyMultipleCalls_73) {
  StringPiece sp("consistency_test");
  size_t h1 = hasher(sp);
  size_t h2 = hasher(sp);
  size_t h3 = hasher(sp);
  EXPECT_EQ(h1, h2);
  EXPECT_EQ(h2, h3);
}

// Usage in unordered_map with StringPiece as key
TEST_F(HashMapTest_73, UsableInUnorderedMap_73) {
  std::unordered_map<StringPiece, int, Hasher> map;
  std::string key1 = "key1";
  std::string key2 = "key2";
  map[StringPiece(key1)] = 1;
  map[StringPiece(key2)] = 2;

  EXPECT_EQ(map.size(), 2u);
  EXPECT_EQ(map[StringPiece(key1)], 1);
  EXPECT_EQ(map[StringPiece(key2)], 2);
}

// Usage in unordered_set with StringPiece
TEST_F(HashMapTest_73, UsableInUnorderedSet_73) {
  std::unordered_set<StringPiece, Hasher> set;
  std::string s1 = "abc";
  std::string s2 = "def";
  std::string s3 = "abc";  // duplicate

  set.insert(StringPiece(s1));
  set.insert(StringPiece(s2));
  set.insert(StringPiece(s3));

  EXPECT_EQ(set.size(), 2u);
  EXPECT_NE(set.find(StringPiece(s1)), set.end());
  EXPECT_NE(set.find(StringPiece(s2)), set.end());
}

// Long string hashing
TEST_F(HashMapTest_73, LongStringHash_73) {
  std::string long_str(10000, 'x');
  StringPiece sp(long_str);
  size_t h = hasher(sp);
  EXPECT_EQ(h, hasher(StringPiece(long_str)));
}

// Long strings that differ by one character
TEST_F(HashMapTest_73, LongStringsDifferByOneChar_73) {
  std::string s1(1000, 'a');
  std::string s2(1000, 'a');
  s2[500] = 'b';
  StringPiece sp1(s1);
  StringPiece sp2(s2);
  EXPECT_NE(hasher(sp1), hasher(sp2));
}

// Constructed from std::string
TEST_F(HashMapTest_73, ConstructedFromStdString_73) {
  std::string str = "from_std_string";
  StringPiece sp(str);
  size_t h = hasher(sp);
  EXPECT_EQ(h, hasher(StringPiece(str.c_str())));
}

// Two empty strings hash to same value
TEST_F(HashMapTest_73, TwoEmptyStringsEqualHash_73) {
  StringPiece sp1("", 0);
  StringPiece sp2("", 0);
  EXPECT_EQ(hasher(sp1), hasher(sp2));
}

// Strings with embedded data (using explicit length)
TEST_F(HashMapTest_73, ExplicitLengthPartialData_73) {
  const char data[] = "abcdef";
  StringPiece sp1(data, 3);  // "abc"
  StringPiece sp2("abc");
  EXPECT_EQ(hasher(sp1), hasher(sp2));
}

// Verify hash works with special characters
TEST_F(HashMapTest_73, SpecialCharacters_73) {
  StringPiece sp1("hello\nworld");
  StringPiece sp2("hello\tworld");
  EXPECT_NE(hasher(sp1), hasher(sp2));
}

// Verify case sensitivity
TEST_F(HashMapTest_73, CaseSensitive_73) {
  StringPiece sp_lower("hello");
  StringPiece sp_upper("Hello");
  EXPECT_NE(hasher(sp_lower), hasher(sp_upper));
}
