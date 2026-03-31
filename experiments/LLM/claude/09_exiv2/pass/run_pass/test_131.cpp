#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/value.hpp>

// Test fixture for AsciiValue tests
class AsciiValueTest_131 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(AsciiValueTest_131, DefaultConstructor_131) {
  Exiv2::AsciiValue value;
  // Default constructed AsciiValue should have typeId asciiString
  EXPECT_EQ(value.typeId(), Exiv2::asciiString);
}

// Test construction with a string
TEST_F(AsciiValueTest_131, StringConstructor_131) {
  Exiv2::AsciiValue value("Hello World");
  EXPECT_EQ(value.typeId(), Exiv2::asciiString);
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "Hello World");
}

// Test construction with empty string
TEST_F(AsciiValueTest_131, EmptyStringConstructor_131) {
  Exiv2::AsciiValue value("");
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "");
}

// Test read method
TEST_F(AsciiValueTest_131, ReadMethod_131) {
  Exiv2::AsciiValue value;
  int result = value.read("Test String");
  EXPECT_EQ(result, 0);
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "Test String");
}

// Test read method with empty string
TEST_F(AsciiValueTest_131, ReadEmptyString_131) {
  Exiv2::AsciiValue value;
  int result = value.read("");
  EXPECT_EQ(result, 0);
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "");
}

// Test read overwrites previous value
TEST_F(AsciiValueTest_131, ReadOverwritesPreviousValue_131) {
  Exiv2::AsciiValue value("Initial");
  value.read("Updated");
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "Updated");
}

// Test write method
TEST_F(AsciiValueTest_131, WriteMethod_131) {
  Exiv2::AsciiValue value("Output Test");
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "Output Test");
}

// Test clone method
TEST_F(AsciiValueTest_131, CloneMethod_131) {
  Exiv2::AsciiValue value("Clone Test");
  auto cloned = value.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->typeId(), Exiv2::asciiString);
  std::ostringstream os;
  cloned->write(os);
  EXPECT_EQ(os.str(), "Clone Test");
}

// Test clone produces independent copy
TEST_F(AsciiValueTest_131, CloneIsIndependent_131) {
  Exiv2::AsciiValue value("Original");
  auto cloned = value.clone();
  value.read("Modified");
  
  std::ostringstream osOriginal;
  value.write(osOriginal);
  EXPECT_EQ(osOriginal.str(), "Modified");
  
  std::ostringstream osCloned;
  cloned->write(osCloned);
  EXPECT_EQ(osCloned.str(), "Original");
}

// Test with string containing special characters
TEST_F(AsciiValueTest_131, SpecialCharacters_131) {
  Exiv2::AsciiValue value("Hello\tWorld\n");
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "Hello\tWorld\n");
}

// Test with string containing spaces
TEST_F(AsciiValueTest_131, StringWithSpaces_131) {
  Exiv2::AsciiValue value("  spaced  ");
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "  spaced  ");
}

// Test with long string
TEST_F(AsciiValueTest_131, LongString_131) {
  std::string longStr(1000, 'A');
  Exiv2::AsciiValue value(longStr);
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), longStr);
}

// Test multiple reads
TEST_F(AsciiValueTest_131, MultipleReads_131) {
  Exiv2::AsciiValue value;
  value.read("First");
  value.read("Second");
  value.read("Third");
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "Third");
}

// Test clone of default constructed value
TEST_F(AsciiValueTest_131, CloneDefaultConstructed_131) {
  Exiv2::AsciiValue value;
  auto cloned = value.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->typeId(), Exiv2::asciiString);
}

// Test that typeId is consistent after read
TEST_F(AsciiValueTest_131, TypeIdAfterRead_131) {
  Exiv2::AsciiValue value;
  value.read("Some data");
  EXPECT_EQ(value.typeId(), Exiv2::asciiString);
}

// Test string with null-terminated character behavior
TEST_F(AsciiValueTest_131, StringWithNullChar_131) {
  std::string strWithNull("Hello");
  Exiv2::AsciiValue value(strWithNull);
  std::ostringstream os;
  value.write(os);
  EXPECT_EQ(os.str(), "Hello");
}

// Test write to stream multiple times
TEST_F(AsciiValueTest_131, WriteMultipleTimes_131) {
  Exiv2::AsciiValue value("Test");
  std::ostringstream os;
  value.write(os);
  value.write(os);
  EXPECT_EQ(os.str(), "TestTest");
}
