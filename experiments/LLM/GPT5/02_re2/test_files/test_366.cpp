// File: ./TestProjects/re2/re2/tests/regexp_capture_names_test_366.cc
#include "gtest/gtest.h"
#include "re2/regexp.h"

#include <map>
#include <string>

using re2::Regexp;

class CaptureNamesTest_366 : public ::testing::Test {
protected:
  // Helper that parses a pattern using public API and returns a Regexp*.
  // The caller must call Decref() on the returned pointer.
  Regexp* ParseOrNull(const std::string& pattern) {
    re2::RegexpStatus status;
    // Use a permissive, standard parse mode. This flag is part of the public API.
    return Regexp::Parse(pattern, Regexp::LikePerl, &status);
  }

  // Safe wrapper around CaptureNames() that returns nullptr or a valid pointer.
  // The caller must delete the returned map if non-null.
  std::map<int, std::string>* GetNames(Regexp* re) {
    return re ? re->CaptureNames() : nullptr;
  }
};

// No named captures → expected nullptr (no allocation when unused).
TEST_F(CaptureNamesTest_366, NoNamedCapturesReturnsNull_366) {
  Regexp* re = ParseOrNull("abc(def)ghi");  // only unnamed captures
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = GetNames(re);
  EXPECT_EQ(names, nullptr) << "Expected nullptr when there are no named groups.";

  re->Decref();
}

// Single named capture → non-null map with one {1 -> "foo"} entry.
TEST_F(CaptureNamesTest_366, SingleNamedCapture_366) {
  Regexp* re = ParseOrNull("(?P<foo>a)");
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = GetNames(re);
  ASSERT_NE(names, nullptr) << "Expected a non-null map when named groups exist.";
  EXPECT_EQ(names->size(), 1u);
  auto it = names->find(1);
  ASSERT_NE(it, names->end());
  EXPECT_EQ(it->second, "foo");

  delete names;
  re->Decref();
}

// Mixed named & unnamed captures → map only contains named entries at correct indices.
TEST_F(CaptureNamesTest_366, MixedNamedAndUnnamed_366) {
  // Capturing groups in left-to-right order:
  // 1: outer ((?P<x>a)(b))
  // 2: (?P<x>a)  ← named
  // 3: (b)
  Regexp* re = ParseOrNull("((?P<x>a)(b))");
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = GetNames(re);
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 1u);

  auto it2 = names->find(2);
  ASSERT_NE(it2, names->end());
  EXPECT_EQ(it2->second, "x");

  // Ensure unnamed groups are not added.
  EXPECT_TRUE(names->find(1) == names->end());
  EXPECT_TRUE(names->find(3) == names->end());

  delete names;
  re->Decref();
}

// Duplicate named groups → each index appears and maps to the same name string.
TEST_F(CaptureNamesTest_366, DuplicateNamesMapToEachIndex_366) {
  // Two named groups with the same name "id" at indices 1 and 2.
  Regexp* re = ParseOrNull("(?P<id>a)(?P<id>b)");
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = GetNames(re);
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);

  auto it1 = names->find(1);
  auto it2 = names->find(2);
  ASSERT_NE(it1, names->end());
  ASSERT_NE(it2, names->end());
  EXPECT_EQ(it1->second, "id");
  EXPECT_EQ(it2->second, "id");

  delete names;
  re->Decref();
}

// Non-capturing groups don't affect numbering; named capture index should be 1.
TEST_F(CaptureNamesTest_366, NonCapturingDoesNotCountTowardIndices_366) {
  Regexp* re = ParseOrNull("(?:prefix)(?P<name>a)");
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = GetNames(re);
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 1u);

  auto it = names->find(1);
  ASSERT_NE(it, names->end());
  EXPECT_EQ(it->second, "name");

  delete names;
  re->Decref();
}

// Calling CaptureNames() twice should return distinct allocations with identical content.
TEST_F(CaptureNamesTest_366, MultipleCallsReturnIndependentEquivalentMaps_366) {
  Regexp* re = ParseOrNull("(?P<a>a)(?P<b>b)");
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names1 = GetNames(re);
  std::map<int, std::string>* names2 = GetNames(re);

  ASSERT_NE(names1, nullptr);
  ASSERT_NE(names2, nullptr);
  EXPECT_NE(names1, names2) << "Each call should return a distinct map instance.";
  EXPECT_EQ(*names1, *names2) << "The maps should contain identical key/value pairs.";

  // Spot-check contents.
  ASSERT_EQ(names1->size(), 2u);
  EXPECT_EQ(names1->at(1), "a");
  EXPECT_EQ(names1->at(2), "b");

  delete names1;
  delete names2;
  re->Decref();
}
