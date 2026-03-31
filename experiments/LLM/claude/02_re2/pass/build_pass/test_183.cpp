#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

// A simple test object that implements ParseFrom for testing _PCRE_MatchObject
class MockParseable {
 public:
  bool parse_called = false;
  std::string last_str;
  size_t last_n = 0;
  bool parse_result = true;

  bool ParseFrom(const char* str, size_t n) {
    parse_called = true;
    last_str = std::string(str, n);
    last_n = n;
    return parse_result;
  }
};

// Test fixture
class PCREMatchObjectTest_183 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Parse returns true when dest is NULL
TEST_F(PCREMatchObjectTest_183, ParseReturnsTrue_WhenDestIsNull_183) {
  const char* str = "hello";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 5, nullptr);
  EXPECT_TRUE(result);
}

// Test that Parse returns true when dest is NULL and str is empty
TEST_F(PCREMatchObjectTest_183, ParseReturnsTrue_WhenDestIsNullAndStrIsEmpty_183) {
  const char* str = "";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 0, nullptr);
  EXPECT_TRUE(result);
}

// Test that Parse calls ParseFrom on the object and returns true on success
TEST_F(PCREMatchObjectTest_183, ParseCallsParseFromAndReturnsTrue_183) {
  MockParseable obj;
  obj.parse_result = true;
  const char* str = "test_data";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 9, &obj);
  EXPECT_TRUE(result);
  EXPECT_TRUE(obj.parse_called);
  EXPECT_EQ(obj.last_str, "test_data");
  EXPECT_EQ(obj.last_n, 9u);
}

// Test that Parse returns false when ParseFrom returns false
TEST_F(PCREMatchObjectTest_183, ParseReturnsFalse_WhenParseFromFails_183) {
  MockParseable obj;
  obj.parse_result = false;
  const char* str = "bad_data";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 8, &obj);
  EXPECT_FALSE(result);
  EXPECT_TRUE(obj.parse_called);
  EXPECT_EQ(obj.last_str, "bad_data");
  EXPECT_EQ(obj.last_n, 8u);
}

// Test with empty string and valid dest
TEST_F(PCREMatchObjectTest_183, ParseWithEmptyString_183) {
  MockParseable obj;
  obj.parse_result = true;
  const char* str = "";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 0, &obj);
  EXPECT_TRUE(result);
  EXPECT_TRUE(obj.parse_called);
  EXPECT_EQ(obj.last_str, "");
  EXPECT_EQ(obj.last_n, 0u);
}

// Test with partial string length (n less than actual string length)
TEST_F(PCREMatchObjectTest_183, ParseWithPartialLength_183) {
  MockParseable obj;
  obj.parse_result = true;
  const char* str = "hello world";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 5, &obj);
  EXPECT_TRUE(result);
  EXPECT_TRUE(obj.parse_called);
  EXPECT_EQ(obj.last_str, "hello");
  EXPECT_EQ(obj.last_n, 5u);
}

// Test with single character string
TEST_F(PCREMatchObjectTest_183, ParseWithSingleCharacter_183) {
  MockParseable obj;
  obj.parse_result = true;
  const char* str = "x";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 1, &obj);
  EXPECT_TRUE(result);
  EXPECT_TRUE(obj.parse_called);
  EXPECT_EQ(obj.last_str, "x");
  EXPECT_EQ(obj.last_n, 1u);
}

// Test that NULL dest with any string content always returns true
TEST_F(PCREMatchObjectTest_183, ParseNullDestWithVariousStrings_183) {
  EXPECT_TRUE(_PCRE_MatchObject<MockParseable>::Parse("abc", 3, nullptr));
  EXPECT_TRUE(_PCRE_MatchObject<MockParseable>::Parse("", 0, nullptr));
  EXPECT_TRUE(_PCRE_MatchObject<MockParseable>::Parse("long string with spaces", 23, nullptr));
}

// Test with string containing embedded null bytes
TEST_F(PCREMatchObjectTest_183, ParseWithEmbeddedNullBytes_183) {
  MockParseable obj;
  obj.parse_result = true;
  const char str[] = "he\0lo";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 5, &obj);
  EXPECT_TRUE(result);
  EXPECT_TRUE(obj.parse_called);
  EXPECT_EQ(obj.last_n, 5u);
  // The string should contain the embedded null
  EXPECT_EQ(obj.last_str, std::string(str, 5));
}

// Test that ParseFrom failure with empty string also propagates
TEST_F(PCREMatchObjectTest_183, ParseFromFailureWithEmptyString_183) {
  MockParseable obj;
  obj.parse_result = false;
  const char* str = "";
  bool result = _PCRE_MatchObject<MockParseable>::Parse(str, 0, &obj);
  EXPECT_FALSE(result);
  EXPECT_TRUE(obj.parse_called);
}

}  // namespace re2
