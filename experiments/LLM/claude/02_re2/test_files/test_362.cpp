#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <map>
#include <string>

namespace re2 {

class CaptureNamesWalkerTest_362 : public ::testing::Test {
protected:
};

// Test that a pattern with no named capture groups returns an empty map
TEST_F(CaptureNamesWalkerTest_362, NoNamedCaptures_362) {
  RE2 re("(a)(b)(c)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_TRUE(names.empty());
}

// Test that a pattern with one named capture group returns correct mapping
TEST_F(CaptureNamesWalkerTest_362, SingleNamedCapture_362) {
  RE2 re("(?P<first>a)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 1);
  auto it = names.find("first");
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, 1);
}

// Test that a pattern with multiple named capture groups returns correct mappings
TEST_F(CaptureNamesWalkerTest_362, MultipleNamedCaptures_362) {
  RE2 re("(?P<first>a)(?P<second>b)(?P<third>c)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 3);
  
  auto it1 = names.find("first");
  ASSERT_NE(it1, names.end());
  EXPECT_EQ(it1->second, 1);
  
  auto it2 = names.find("second");
  ASSERT_NE(it2, names.end());
  EXPECT_EQ(it2->second, 2);
  
  auto it3 = names.find("third");
  ASSERT_NE(it3, names.end());
  EXPECT_EQ(it3->second, 3);
}

// Test mix of named and unnamed capture groups
TEST_F(CaptureNamesWalkerTest_362, MixedNamedAndUnnamedCaptures_362) {
  RE2 re("(a)(?P<named>b)(c)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 1);
  auto it = names.find("named");
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, 2);
}

// Test pattern with no capture groups at all
TEST_F(CaptureNamesWalkerTest_362, NoCaptureGroups_362) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_TRUE(names.empty());
}

// Test nested named capture groups
TEST_F(CaptureNamesWalkerTest_362, NestedNamedCaptures_362) {
  RE2 re("(?P<outer>a(?P<inner>b))");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 2);
  
  auto it1 = names.find("outer");
  ASSERT_NE(it1, names.end());
  EXPECT_EQ(it1->second, 1);
  
  auto it2 = names.find("inner");
  ASSERT_NE(it2, names.end());
  EXPECT_EQ(it2->second, 2);
}

// Test named capture groups with alternation
TEST_F(CaptureNamesWalkerTest_362, NamedCapturesWithAlternation_362) {
  RE2 re("(?P<alt1>a)|(?P<alt2>b)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 2);
  
  auto it1 = names.find("alt1");
  ASSERT_NE(it1, names.end());
  EXPECT_EQ(it1->second, 1);
  
  auto it2 = names.find("alt2");
  ASSERT_NE(it2, names.end());
  EXPECT_EQ(it2->second, 2);
}

// Test empty pattern
TEST_F(CaptureNamesWalkerTest_362, EmptyPattern_362) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_TRUE(names.empty());
}

// Test named capture with complex subexpression
TEST_F(CaptureNamesWalkerTest_362, NamedCaptureComplexSubexpr_362) {
  RE2 re("(?P<digits>\\d+)(?P<letters>[a-z]+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 2);
  
  auto it1 = names.find("digits");
  ASSERT_NE(it1, names.end());
  EXPECT_EQ(it1->second, 1);
  
  auto it2 = names.find("letters");
  ASSERT_NE(it2, names.end());
  EXPECT_EQ(it2->second, 2);
}

// Test CaptureNames through Regexp interface if accessible
TEST_F(CaptureNamesWalkerTest_362, NamedCaptureWithRepetition_362) {
  RE2 re("(?P<word>\\w+)(?P<sep>\\s*)(?P<num>\\d+)");
  ASSERT_TRUE(re.ok());
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 3);
  
  EXPECT_NE(names.find("word"), names.end());
  EXPECT_NE(names.find("sep"), names.end());
  EXPECT_NE(names.find("num"), names.end());
}

// Test that NumberOfCapturingGroups counts both named and unnamed
TEST_F(CaptureNamesWalkerTest_362, TotalCaptureGroupCount_362) {
  RE2 re("(a)(?P<named>b)(c)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
  const std::map<std::string, int>& names = re.NamedCapturingGroups();
  EXPECT_EQ(names.size(), 1);
}

}  // namespace re2
