#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test default constructor
TEST(AsciiValueTest_814, DefaultConstructor_814) {
  AsciiValue val;
  EXPECT_EQ(val.size(), 0u);
  EXPECT_EQ(val.count(), 0u);
}

// Test constructor with string
TEST(AsciiValueTest_814, StringConstructor_814) {
  AsciiValue val("Hello");
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "Hello");
}

// Test write truncates at null character
TEST(AsciiValueTest_814, WriteStopsAtNullChar_814) {
  std::string input = "Hello";
  input += '\0';
  input += "World";
  AsciiValue val(input);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "Hello");
}

// Test write with no null character outputs entire string
TEST(AsciiValueTest_814, WriteNoNullChar_814) {
  AsciiValue val("NoNullHere");
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "NoNullHere");
}

// Test write with empty string
TEST(AsciiValueTest_814, WriteEmptyString_814) {
  AsciiValue val("");
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "");
}

// Test write with string that starts with null character
TEST(AsciiValueTest_814, WriteStartsWithNull_814) {
  std::string input(1, '\0');
  input += "After";
  AsciiValue val(input);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "");
}

// Test write with string that is only null characters
TEST(AsciiValueTest_814, WriteOnlyNulls_814) {
  std::string input(5, '\0');
  AsciiValue val(input);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "");
}

// Test read from string
TEST(AsciiValueTest_814, ReadFromString_814) {
  AsciiValue val;
  val.read("TestRead");
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "TestRead");
}

// Test read from string with embedded null
TEST(AsciiValueTest_814, ReadFromStringWithNull_814) {
  AsciiValue val;
  std::string input = "AB";
  input += '\0';
  input += "CD";
  val.read(input);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "AB");
}

// Test size returns length of internal string
TEST(AsciiValueTest_814, SizeReturnsLength_814) {
  AsciiValue val("Hello");
  // AsciiValue::read appends a null terminator, so size may be string length + 1
  // We test that size is at least the string length
  EXPECT_GE(val.size(), 5u);
}

// Test count returns expected value
TEST(AsciiValueTest_814, CountReturnsExpected_814) {
  AsciiValue val("Hello");
  EXPECT_GE(val.count(), 1u);
}

// Test clone produces equivalent object
TEST(AsciiValueTest_814, CloneProducesSameOutput_814) {
  AsciiValue val("CloneMe");
  auto cloned = val.clone();
  std::ostringstream os1, os2;
  val.write(os1);
  cloned->write(os2);
  EXPECT_EQ(os1.str(), os2.str());
}

// Test copy to byte buffer
TEST(AsciiValueTest_814, CopyToBuffer_814) {
  AsciiValue val("Copy");
  byte buf[64] = {};
  size_t copied = val.copy(buf, invalidByteOrder);
  EXPECT_GE(copied, 4u);
  // The first 4 bytes should be 'C', 'o', 'p', 'y'
  EXPECT_EQ(buf[0], 'C');
  EXPECT_EQ(buf[1], 'o');
  EXPECT_EQ(buf[2], 'p');
  EXPECT_EQ(buf[3], 'y');
}

// Test read from byte buffer
TEST(AsciiValueTest_814, ReadFromByteBuffer_814) {
  AsciiValue val;
  const byte data[] = {'T', 'e', 's', 't', '\0'};
  val.read(data, sizeof(data), invalidByteOrder);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "Test");
}

// Test write returns reference to same stream
TEST(AsciiValueTest_814, WriteReturnsStreamReference_814) {
  AsciiValue val("Stream");
  std::ostringstream os;
  std::ostream& result = val.write(os);
  EXPECT_EQ(&result, &os);
}

// Test toInt64 on numeric string
TEST(AsciiValueTest_814, ToInt64NumericString_814) {
  AsciiValue val("42");
  int64_t result = val.toInt64(0);
  EXPECT_EQ(result, 42);
}

// Test toFloat on numeric string
TEST(AsciiValueTest_814, ToFloatNumericString_814) {
  AsciiValue val("3.14");
  float result = val.toFloat(0);
  EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test write with single character
TEST(AsciiValueTest_814, WriteSingleChar_814) {
  AsciiValue val("X");
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "X");
}

// Test write with long string
TEST(AsciiValueTest_814, WriteLongString_814) {
  std::string longStr(1000, 'A');
  AsciiValue val(longStr);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), longStr);
}

// Test write with special characters (non-null)
TEST(AsciiValueTest_814, WriteSpecialCharacters_814) {
  AsciiValue val("Hello\tWorld\n");
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "Hello\tWorld\n");
}

// Test multiple null characters - should stop at first
TEST(AsciiValueTest_814, WriteMultipleNullsStopsAtFirst_814) {
  std::string input = "A";
  input += '\0';
  input += "B";
  input += '\0';
  input += "C";
  AsciiValue val(input);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "A");
}

// Test that read overwrites previous value
TEST(AsciiValueTest_814, ReadOverwritesPreviousValue_814) {
  AsciiValue val("First");
  val.read("Second");
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "Second");
}
