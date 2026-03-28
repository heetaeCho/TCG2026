// File: ./TestProjects/ninja/tests/string_piece_hash_test_73.cc

#include "hash_map.h"
#include "string_piece.h"

#include <gtest/gtest.h>
#include <unordered_map>
#include <string>

// These tests assume that including "hash_map.h" provides a std::hash<StringPiece>
// specialization with operator()(StringPiece) const.

// Verifies that identical StringPiece values (constructed in different ways)
// produce the same hash value.
TEST(StringPieceHashTest_73, SameContentSameHash_73) {
  std::hash<StringPiece> hasher;

  StringPiece from_cstr("hello");
  std::string s("hello");
  StringPiece from_string(s);

  size_t h1 = hasher(from_cstr);
  size_t h2 = hasher(from_string);

  EXPECT_EQ(h1, h2);
}

// Verifies that hashing an empty StringPiece is well-defined and consistent
// across different construction forms.
TEST(StringPieceHashTest_73, EmptyStringHashConsistent_73) {
  std::hash<StringPiece> hasher;

  StringPiece empty1("");
  std::string empty_std;
  StringPiece empty2(empty_std);

  size_t h1 = hasher(empty1);
  size_t h2 = hasher(empty2);

  EXPECT_EQ(h1, h2);
}

// Verifies that hashing the same StringPiece multiple times is stable.
TEST(StringPieceHashTest_73, StableAcrossCalls_73) {
  std::hash<StringPiece> hasher;

  StringPiece key("ninja-build");

  size_t h1 = hasher(key);
  size_t h2 = hasher(key);
  size_t h3 = hasher(key);

  EXPECT_EQ(h1, h2);
  EXPECT_EQ(h2, h3);
}

// Verifies that the hash specialization is compatible with StringPiece's
// equality operator, so it can be used as a key in std::unordered_map.
TEST(StringPieceHashTest_73, UsableAsUnorderedMapKey_73) {
  std::unordered_map<StringPiece, int> map;
  std::string backing_str = "target.o";

  // Insert using a StringPiece constructed from std::string.
  StringPiece key_from_string(backing_str);
  map[key_from_string] = 123;

  // Look up using a StringPiece constructed from const char* with same content.
  StringPiece key_from_cstr(backing_str.c_str());

  auto it = map.find(key_from_cstr);
  ASSERT_NE(it, map.end());
  EXPECT_EQ(123, it->second);
}

// Verifies that different StringPiece values that are not equal according to
// operator== are treated as different keys in std::unordered_map
// (this checks observable container behavior rather than specific hash values).
TEST(StringPieceHashTest_73, DifferentKeysStoredSeparately_73) {
  std::unordered_map<StringPiece, int> map;

  std::string s1 = "file1.cc";
  std::string s2 = "file2.cc";

  StringPiece key1(s1);
  StringPiece key2(s2);

  map[key1] = 1;
  map[key2] = 2;

  auto it1 = map.find(key1);
  auto it2 = map.find(key2);

  ASSERT_NE(it1, map.end());
  ASSERT_NE(it2, map.end());

  EXPECT_EQ(1, it1->second);
  EXPECT_EQ(2, it2->second);
}
