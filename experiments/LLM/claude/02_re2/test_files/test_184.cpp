#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <climits>
#include <cfloat>
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

// Test fixture
class PCREArgTest_184 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(PCREArgTest_184, DefaultConstructor_ParseNull_184) {
  PCRE::Arg arg;
  // Default constructor with no destination; parse_null should accept any string
  EXPECT_TRUE(arg.Parse("anything", 8));
}

TEST_F(PCREArgTest_184, DefaultConstructor_ParseEmptyString_184) {
  PCRE::Arg arg;
  EXPECT_TRUE(arg.Parse("", 0));
}

// ==================== Void Pointer Constructor Tests ====================

TEST_F(PCREArgTest_184, VoidPointerConstructor_ParseNull_184) {
  void* p = nullptr;
  PCRE::Arg arg(p);
  EXPECT_TRUE(arg.Parse("test", 4));
}

// ==================== String Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseString_Normal_184) {
  std::string dest;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ(dest, "hello");
}

TEST_F(PCREArgTest_184, ParseString_Empty_184) {
  std::string dest;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("", 0));
  EXPECT_EQ(dest, "");
}

TEST_F(PCREArgTest_184, ParseString_PartialLength_184) {
  std::string dest;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("hello world", 5));
  EXPECT_EQ(dest, "hello");
}

TEST_F(PCREArgTest_184, ParseString_WithNullBytes_184) {
  std::string dest;
  PCRE::Arg arg(&dest);
  const char data[] = "he\0lo";
  EXPECT_TRUE(arg.Parse(data, 5));
  EXPECT_EQ(dest.size(), 5u);
}

// ==================== StringView Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseStringView_Normal_184) {
  std::string_view dest;
  PCRE::Arg arg(&dest);
  const char* input = "hello";
  EXPECT_TRUE(arg.Parse(input, 5));
  EXPECT_EQ(dest, "hello");
  EXPECT_EQ(dest.size(), 5u);
}

TEST_F(PCREArgTest_184, ParseStringView_Empty_184) {
  std::string_view dest;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("", 0));
  EXPECT_EQ(dest.size(), 0u);
}

// ==================== Int Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseInt_Normal_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(dest, 42);
}

TEST_F(PCREArgTest_184, ParseInt_Negative_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("-123", 4));
  EXPECT_EQ(dest, -123);
}

TEST_F(PCREArgTest_184, ParseInt_Zero_184) {
  int dest = -1;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("0", 1));
  EXPECT_EQ(dest, 0);
}

TEST_F(PCREArgTest_184, ParseInt_InvalidString_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("abc", 3));
}

TEST_F(PCREArgTest_184, ParseInt_EmptyString_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("", 0));
}

TEST_F(PCREArgTest_184, ParseInt_LeadingWhitespace_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  // Leading whitespace might not be accepted
  EXPECT_FALSE(arg.Parse(" 42", 3));
}

TEST_F(PCREArgTest_184, ParseInt_TrailingGarbage_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("42abc", 5));
}

TEST_F(PCREArgTest_184, ParseInt_HexPrefix_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("0x1A", 4));
  EXPECT_EQ(dest, 0x1A);
}

TEST_F(PCREArgTest_184, ParseInt_OctalPrefix_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("010", 3));
  EXPECT_EQ(dest, 8);  // Octal 010 = 8
}

// ==================== Unsigned Int Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseUint_Normal_184) {
  unsigned int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(dest, 42u);
}

TEST_F(PCREArgTest_184, ParseUint_Negative_184) {
  unsigned int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("-1", 2));
}

TEST_F(PCREArgTest_184, ParseUint_InvalidString_184) {
  unsigned int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("xyz", 3));
}

// ==================== Long Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseLong_Normal_184) {
  long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("123456", 6));
  EXPECT_EQ(dest, 123456L);
}

TEST_F(PCREArgTest_184, ParseLong_Negative_184) {
  long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("-99999", 6));
  EXPECT_EQ(dest, -99999L);
}

// ==================== Unsigned Long Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseUlong_Normal_184) {
  unsigned long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("999999", 6));
  EXPECT_EQ(dest, 999999UL);
}

TEST_F(PCREArgTest_184, ParseUlong_Negative_184) {
  unsigned long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("-1", 2));
}

// ==================== Short Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseShort_Normal_184) {
  short dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("100", 3));
  EXPECT_EQ(dest, 100);
}

TEST_F(PCREArgTest_184, ParseShort_Overflow_184) {
  short dest = 0;
  PCRE::Arg arg(&dest);
  // SHRT_MAX is typically 32767
  EXPECT_FALSE(arg.Parse("99999", 5));
}

// ==================== Unsigned Short Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseUshort_Normal_184) {
  unsigned short dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("500", 3));
  EXPECT_EQ(dest, 500u);
}

TEST_F(PCREArgTest_184, ParseUshort_Overflow_184) {
  unsigned short dest = 0;
  PCRE::Arg arg(&dest);
  // USHRT_MAX is typically 65535
  EXPECT_FALSE(arg.Parse("70000", 5));
}

// ==================== Long Long Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseLongLong_Normal_184) {
  long long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("1234567890123", 13));
  EXPECT_EQ(dest, 1234567890123LL);
}

TEST_F(PCREArgTest_184, ParseLongLong_Negative_184) {
  long long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("-9876543210", 11));
  EXPECT_EQ(dest, -9876543210LL);
}

// ==================== Unsigned Long Long Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseUlongLong_Normal_184) {
  unsigned long long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("18446744073709551615", 20));
  EXPECT_EQ(dest, 18446744073709551615ULL);
}

TEST_F(PCREArgTest_184, ParseUlongLong_Negative_184) {
  unsigned long long dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("-1", 2));
}

// ==================== Float Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseFloat_Normal_184) {
  float dest = 0.0f;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("3.14", 4));
  EXPECT_FLOAT_EQ(dest, 3.14f);
}

TEST_F(PCREArgTest_184, ParseFloat_Negative_184) {
  float dest = 0.0f;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("-2.5", 4));
  EXPECT_FLOAT_EQ(dest, -2.5f);
}

TEST_F(PCREArgTest_184, ParseFloat_Integer_184) {
  float dest = 0.0f;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_FLOAT_EQ(dest, 42.0f);
}

TEST_F(PCREArgTest_184, ParseFloat_Invalid_184) {
  float dest = 0.0f;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("abc", 3));
}

TEST_F(PCREArgTest_184, ParseFloat_Empty_184) {
  float dest = 0.0f;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("", 0));
}

TEST_F(PCREArgTest_184, ParseFloat_Scientific_184) {
  float dest = 0.0f;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("1.5e2", 5));
  EXPECT_FLOAT_EQ(dest, 150.0f);
}

// ==================== Double Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseDouble_Normal_184) {
  double dest = 0.0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("3.14159265", 10));
  EXPECT_DOUBLE_EQ(dest, 3.14159265);
}

TEST_F(PCREArgTest_184, ParseDouble_Negative_184) {
  double dest = 0.0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("-100.5", 6));
  EXPECT_DOUBLE_EQ(dest, -100.5);
}

TEST_F(PCREArgTest_184, ParseDouble_Invalid_184) {
  double dest = 0.0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("xyz", 3));
}

TEST_F(PCREArgTest_184, ParseDouble_Empty_184) {
  double dest = 0.0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("", 0));
}

TEST_F(PCREArgTest_184, ParseDouble_Scientific_184) {
  double dest = 0.0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("2.5e10", 6));
  EXPECT_DOUBLE_EQ(dest, 2.5e10);
}

// ==================== Char Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseChar_Normal_184) {
  char dest = '\0';
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("A", 1));
  EXPECT_EQ(dest, 'A');
}

TEST_F(PCREArgTest_184, ParseChar_MultipleChars_184) {
  char dest = '\0';
  PCRE::Arg arg(&dest);
  // Parsing multiple characters into a char should fail
  EXPECT_FALSE(arg.Parse("AB", 2));
}

TEST_F(PCREArgTest_184, ParseChar_Empty_184) {
  char dest = 'X';
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("", 0));
}

// ==================== Signed Char Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseSchar_Normal_184) {
  signed char dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("A", 1));
  EXPECT_EQ(dest, 'A');
}

TEST_F(PCREArgTest_184, ParseSchar_Empty_184) {
  signed char dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("", 0));
}

// ==================== Unsigned Char Parsing Tests ====================

TEST_F(PCREArgTest_184, ParseUchar_Normal_184) {
  unsigned char dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("A", 1));
  EXPECT_EQ(dest, 'A');
}

TEST_F(PCREArgTest_184, ParseUchar_Empty_184) {
  unsigned char dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_FALSE(arg.Parse("", 0));
}

// ==================== Custom Parser Tests ====================

TEST_F(PCREArgTest_184, CustomParser_Called_184) {
  bool custom_called = false;
  int dest = 0;
  auto custom_parser = [](const char* str, size_t n, void* dest) -> bool {
    *static_cast<int*>(dest) = 999;
    return true;
  };
  PCRE::Arg arg(&dest, custom_parser);
  EXPECT_TRUE(arg.Parse("whatever", 8));
  EXPECT_EQ(dest, 999);
}

TEST_F(PCREArgTest_184, CustomParser_ReturnsFalse_184) {
  int dest = 0;
  auto custom_parser = [](const char* str, size_t n, void* dest) -> bool {
    return false;
  };
  PCRE::Arg arg(&dest, custom_parser);
  EXPECT_FALSE(arg.Parse("whatever", 8));
}

// ==================== Boundary Integer Tests ====================

TEST_F(PCREArgTest_184, ParseInt_MaxValue_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  std::string max_str = std::to_string(INT_MAX);
  EXPECT_TRUE(arg.Parse(max_str.c_str(), max_str.size()));
  EXPECT_EQ(dest, INT_MAX);
}

TEST_F(PCREArgTest_184, ParseInt_MinValue_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  std::string min_str = std::to_string(INT_MIN);
  EXPECT_TRUE(arg.Parse(min_str.c_str(), min_str.size()));
  EXPECT_EQ(dest, INT_MIN);
}

TEST_F(PCREArgTest_184, ParseDouble_Zero_184) {
  double dest = 1.0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("0.0", 3));
  EXPECT_DOUBLE_EQ(dest, 0.0);
}

TEST_F(PCREArgTest_184, ParseFloat_Zero_184) {
  float dest = 1.0f;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("0.0", 3));
  EXPECT_FLOAT_EQ(dest, 0.0f);
}

// ==================== Hex Integer Tests ====================

TEST_F(PCREArgTest_184, ParseInt_HexUpperCase_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("0xFF", 4));
  EXPECT_EQ(dest, 255);
}

TEST_F(PCREArgTest_184, ParseInt_HexLowerCase_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  EXPECT_TRUE(arg.Parse("0xff", 4));
  EXPECT_EQ(dest, 255);
}

// ==================== Null Destination with parse_null ====================

TEST_F(PCREArgTest_184, ParseNull_NullDest_AnyString_184) {
  PCRE::Arg arg(static_cast<void*>(nullptr));
  EXPECT_TRUE(arg.Parse("anything goes here", 18));
}

TEST_F(PCREArgTest_184, ParseNull_NullDest_EmptyString_184) {
  PCRE::Arg arg(static_cast<void*>(nullptr));
  EXPECT_TRUE(arg.Parse("", 0));
}

// ==================== Partial Length Parsing ====================

TEST_F(PCREArgTest_184, ParseInt_PartialLength_184) {
  int dest = 0;
  PCRE::Arg arg(&dest);
  // Only parse "12" from "12345"
  EXPECT_TRUE(arg.Parse("12345", 2));
  EXPECT_EQ(dest, 12);
}

TEST_F(PCREArgTest_184, ParseDouble_PartialLength_184) {
  double dest = 0.0;
  PCRE::Arg arg(&dest);
  // Only parse "3.1" from "3.14"
  EXPECT_TRUE(arg.Parse("3.14", 3));
  EXPECT_DOUBLE_EQ(dest, 3.1);
}

}  // namespace re2
