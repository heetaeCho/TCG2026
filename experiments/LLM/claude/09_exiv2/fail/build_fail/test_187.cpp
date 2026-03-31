#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "tags_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define test vocabulary arrays
static const TagVocabulary testVocab[] = {
    {"1", N_("One")},
    {"2", N_("Two")},
    {"3", N_("Three")},
    {"hello", N_("Hello Label")},
    {"world", N_("World Label")},
};

static const TagVocabulary singleVocab[] = {
    {"only", N_("Only Entry")},
};

class PrintTagVocabularyMultiTest_187 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test with empty value (count == 0)
TEST_F(PrintTagVocabularyMultiTest_187, EmptyValuePrintsParenthesized_187) {
  StringValue value;
  // StringValue with no data should have count 0
  ExifData exifData;
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test with a single value that matches vocabulary
TEST_F(PrintTagVocabularyMultiTest_187, SingleMatchingValuePrintsLabel_187) {
  StringValue value;
  value.read("1");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "One");
}

// Test with a single value that does not match vocabulary
TEST_F(PrintTagVocabularyMultiTest_187, SingleNonMatchingValuePrintsParenthesized_187) {
  StringValue value;
  value.read("unknown");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "(unknown)");
}

// Test with multiple matching values
TEST_F(PrintTagVocabularyMultiTest_187, MultipleMatchingValuesPrintCommaSeparated_187) {
  XmpArrayValue value(xmpSeq);
  value.read("1");
  value.read("2");
  value.read("3");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "One, Two, Three");
}

// Test with mix of matching and non-matching values
TEST_F(PrintTagVocabularyMultiTest_187, MixedMatchAndNonMatchValues_187) {
  XmpArrayValue value(xmpSeq);
  value.read("1");
  value.read("nonexistent");
  value.read("3");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "One, (nonexistent), Three");
}

// Test with all non-matching values
TEST_F(PrintTagVocabularyMultiTest_187, AllNonMatchingValues_187) {
  XmpArrayValue value(xmpSeq);
  value.read("x");
  value.read("y");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "(x), (y)");
}

// Test with single-entry vocabulary, matching
TEST_F(PrintTagVocabularyMultiTest_187, SingleEntryVocabularyMatch_187) {
  StringValue value;
  value.read("only");
  printTagVocabularyMulti<std::extent<decltype(singleVocab)>::value, singleVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "Only Entry");
}

// Test with single-entry vocabulary, no match
TEST_F(PrintTagVocabularyMultiTest_187, SingleEntryVocabularyNoMatch_187) {
  StringValue value;
  value.read("nope");
  printTagVocabularyMulti<std::extent<decltype(singleVocab)>::value, singleVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "(nope)");
}

// Test with nullptr ExifData
TEST_F(PrintTagVocabularyMultiTest_187, NullExifDataPtr_187) {
  StringValue value;
  value.read("2");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "Two");
}

// Test that the function returns the ostream reference
TEST_F(PrintTagVocabularyMultiTest_187, ReturnsOstreamReference_187) {
  StringValue value;
  value.read("1");
  std::ostream& returned = printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test return value for empty value case
TEST_F(PrintTagVocabularyMultiTest_187, EmptyValueReturnsOstreamReference_187) {
  StringValue value;
  std::ostream& returned = printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test with string vocabulary keys (non-numeric)
TEST_F(PrintTagVocabularyMultiTest_187, StringVocabularyKeys_187) {
  StringValue value;
  value.read("hello");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "Hello Label");
}

// Test multiple values with string keys
TEST_F(PrintTagVocabularyMultiTest_187, MultipleStringVocabularyKeys_187) {
  XmpArrayValue value(xmpSeq);
  value.read("hello");
  value.read("world");
  printTagVocabularyMulti<std::extent<decltype(testVocab)>::value, testVocab>(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result, "Hello Label, World Label");
}
