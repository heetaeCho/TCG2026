#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

class LangAltValueTest_853 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(LangAltValueTest_853, DefaultConstruction_853) {
  LangAltValue val;
  EXPECT_EQ(val.count(), 0u);
}

// Test construction with a string buffer
TEST_F(LangAltValueTest_853, ConstructionWithString_853) {
  LangAltValue val("Hello World");
  EXPECT_GT(val.count(), 0u);
}

// Test read with simple string (no lang qualifier)
TEST_F(LangAltValueTest_853, ReadSimpleString_853) {
  LangAltValue val;
  int result = val.read("Test value");
  EXPECT_EQ(result, 0);
  EXPECT_GT(val.count(), 0u);
}

// Test read with lang qualifier "lang=en-US value"
TEST_F(LangAltValueTest_853, ReadWithLangQualifier_853) {
  LangAltValue val;
  int result = val.read("lang=\"en-US\" A test value");
  EXPECT_EQ(result, 0);
  EXPECT_GT(val.count(), 0u);
}

// Test read with empty string
TEST_F(LangAltValueTest_853, ReadEmptyString_853) {
  LangAltValue val;
  int result = val.read("");
  // Even empty string should be accepted
  EXPECT_EQ(result, 0);
}

// Test clone creates a copy
TEST_F(LangAltValueTest_853, CloneCreatesValidCopy_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" Hello");
  auto cloned = val.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->count(), val.count());
}

// Test clone preserves data
TEST_F(LangAltValueTest_853, ClonePreservesData_853) {
  LangAltValue val("Some text");
  auto cloned = val.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->toString(0), val.toString(0));
}

// Test count after multiple reads
TEST_F(LangAltValueTest_853, CountAfterRead_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" First value");
  size_t count1 = val.count();
  EXPECT_GE(count1, 1u);
}

// Test toString with index 0
TEST_F(LangAltValueTest_853, ToStringIndex0_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" Test output");
  std::string result = val.toString(0);
  EXPECT_FALSE(result.empty());
}

// Test toString with qualifier "x-default"
TEST_F(LangAltValueTest_853, ToStringWithQualifier_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" Qualified text");
  std::string result = val.toString("x-default");
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Qualified text"), std::string::npos);
}

// Test toString with non-existent qualifier
TEST_F(LangAltValueTest_853, ToStringWithNonExistentQualifier_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" Some text");
  std::string result = val.toString("fr-FR");
  // Non-existent qualifier should return empty string
  EXPECT_TRUE(result.empty());
}

// Test write to ostream
TEST_F(LangAltValueTest_853, WriteToOstream_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" Write test");
  std::ostringstream os;
  val.write(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// Test write on empty value
TEST_F(LangAltValueTest_853, WriteEmptyValue_853) {
  LangAltValue val;
  std::ostringstream os;
  val.write(os);
  // Should not crash; output may be empty
}

// Test toInt64
TEST_F(LangAltValueTest_853, ToInt64_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" 42");
  int64_t result = val.toInt64(0);
  EXPECT_EQ(result, 42);
}

// Test toUint32
TEST_F(LangAltValueTest_853, ToUint32_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" 100");
  uint32_t result = val.toUint32(0);
  EXPECT_EQ(result, 100u);
}

// Test toFloat
TEST_F(LangAltValueTest_853, ToFloat_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" 3.14");
  float result = val.toFloat(0);
  EXPECT_NEAR(result, 3.14f, 0.01f);
}

// Test toRational
TEST_F(LangAltValueTest_853, ToRational_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" 1/2");
  Rational result = val.toRational(0);
  // Check it returns some rational value
  // Exact check depends on implementation
  EXPECT_NE(result.second, 0);
}

// Test toInt64 with non-numeric string
TEST_F(LangAltValueTest_853, ToInt64NonNumeric_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" not a number");
  int64_t result = val.toInt64(0);
  EXPECT_EQ(result, 0);
}

// Test toFloat with non-numeric string
TEST_F(LangAltValueTest_853, ToFloatNonNumeric_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" text");
  float result = val.toFloat(0);
  EXPECT_EQ(result, 0.0f);
}

// Test count on default constructed value is 0
TEST_F(LangAltValueTest_853, CountOnDefaultIsZero_853) {
  LangAltValue val;
  EXPECT_EQ(val.count(), 0u);
}

// Test reading a value without lang prefix
TEST_F(LangAltValueTest_853, ReadWithoutLangPrefix_853) {
  LangAltValue val;
  int result = val.read("Plain text without lang");
  EXPECT_EQ(result, 0);
  std::string str = val.toString(0);
  EXPECT_FALSE(str.empty());
}

// Test multiple language entries behavior via toString with qualifier
TEST_F(LangAltValueTest_853, MultipleLanguageToString_853) {
  LangAltValue val;
  val.read("lang=\"x-default\" Default text");
  // Reading again may overwrite or add
  std::string result = val.toString("x-default");
  EXPECT_NE(result.find("Default text"), std::string::npos);
}

// Test clone of default constructed value
TEST_F(LangAltValueTest_853, CloneDefaultConstructed_853) {
  LangAltValue val;
  auto cloned = val.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->count(), 0u);
}

// Test that write output contains the language qualifier info
TEST_F(LangAltValueTest_853, WriteContainsLangInfo_853) {
  LangAltValue val;
  val.read("lang=\"en-US\" English text");
  std::ostringstream os;
  val.write(os);
  std::string output = os.str();
  // The output should contain the text
  EXPECT_NE(output.find("English text"), std::string::npos);
}
