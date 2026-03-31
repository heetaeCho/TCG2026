#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include "tags_int.hpp"
#include "exif.hpp"

// We need to work with the TagDetails structure and the printTag function.
// Since printTag is a template that takes a static array of TagDetails,
// we need to define our own test arrays to exercise the function.

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define test TagDetails arrays for use with printTag
namespace {

// A simple array with a few entries
const TagDetails testTagArray[] = {
    {0, "Zero"},
    {1, "One"},
    {2, "Two"},
    {10, "Ten"},
    {100, "Hundred"},
    {-1, "NegativeOne"},
    {255, "TwoFiftyFive"},
};

// A single-element array (boundary: minimum size)
const TagDetails singleElementArray[] = {
    {42, "FortyTwo"},
};

// An array with large values
const TagDetails largeValueArray[] = {
    {0, "Start"},
    {2147483647, "MaxInt32"},
    {-2147483648LL, "MinInt32"},
};

// An array with consecutive values
const TagDetails consecutiveArray[] = {
    {0, "Val0"},
    {1, "Val1"},
    {2, "Val2"},
    {3, "Val3"},
    {4, "Val4"},
};

}  // namespace

class PrintTagTest_182 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test that a known value in the array prints its label
TEST_F(PrintTagTest_182, KnownValuePrintsLabel_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 0, nullptr);
  EXPECT_EQ(os.str(), "Zero");
}

// Test another known value
TEST_F(PrintTagTest_182, KnownValueOne_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 1, nullptr);
  EXPECT_EQ(os.str(), "One");
}

// Test known value Two
TEST_F(PrintTagTest_182, KnownValueTwo_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 2, nullptr);
  EXPECT_EQ(os.str(), "Two");
}

// Test known value Ten
TEST_F(PrintTagTest_182, KnownValueTen_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 10, nullptr);
  EXPECT_EQ(os.str(), "Ten");
}

// Test known value Hundred
TEST_F(PrintTagTest_182, KnownValueHundred_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 100, nullptr);
  EXPECT_EQ(os.str(), "Hundred");
}

// Test that an unknown value prints in the format "(value)"
TEST_F(PrintTagTest_182, UnknownValuePrintsParenthesized_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 999, nullptr);
  EXPECT_EQ(os.str(), "(999)");
}

// Test that another unknown value prints correctly
TEST_F(PrintTagTest_182, UnknownValueThree_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 3, nullptr);
  EXPECT_EQ(os.str(), "(3)");
}

// Test negative value that exists in array
TEST_F(PrintTagTest_182, NegativeKnownValue_182) {
  printTag<std::size(testTagArray), testTagArray>(os, -1, nullptr);
  EXPECT_EQ(os.str(), "NegativeOne");
}

// Test negative value that does not exist in array
TEST_F(PrintTagTest_182, NegativeUnknownValue_182) {
  printTag<std::size(testTagArray), testTagArray>(os, -5, nullptr);
  EXPECT_EQ(os.str(), "(-5)");
}

// Test with single element array - known value
TEST_F(PrintTagTest_182, SingleElementArrayKnown_182) {
  printTag<std::size(singleElementArray), singleElementArray>(os, 42, nullptr);
  EXPECT_EQ(os.str(), "FortyTwo");
}

// Test with single element array - unknown value
TEST_F(PrintTagTest_182, SingleElementArrayUnknown_182) {
  printTag<std::size(singleElementArray), singleElementArray>(os, 0, nullptr);
  EXPECT_EQ(os.str(), "(0)");
}

// Test with large positive value that exists
TEST_F(PrintTagTest_182, LargePositiveKnownValue_182) {
  printTag<std::size(largeValueArray), largeValueArray>(os, 2147483647, nullptr);
  EXPECT_EQ(os.str(), "MaxInt32");
}

// Test with large negative value that exists
TEST_F(PrintTagTest_182, LargeNegativeKnownValue_182) {
  printTag<std::size(largeValueArray), largeValueArray>(os, -2147483648LL, nullptr);
  EXPECT_EQ(os.str(), "MinInt32");
}

// Test with large value not in array
TEST_F(PrintTagTest_182, LargeUnknownValue_182) {
  printTag<std::size(largeValueArray), largeValueArray>(os, 999999999, nullptr);
  EXPECT_EQ(os.str(), "(999999999)");
}

// Test value 255 (boundary for byte values)
TEST_F(PrintTagTest_182, ByteBoundaryValue_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 255, nullptr);
  EXPECT_EQ(os.str(), "TwoFiftyFive");
}

// Test that printTag returns the ostream reference
TEST_F(PrintTagTest_182, ReturnsOstreamReference_182) {
  std::ostream& result = printTag<std::size(testTagArray), testTagArray>(os, 1, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test that printTag returns the ostream reference for unknown values too
TEST_F(PrintTagTest_182, ReturnsOstreamReferenceForUnknown_182) {
  std::ostream& result = printTag<std::size(testTagArray), testTagArray>(os, 9999, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test with zero value printed as unknown in single element array
TEST_F(PrintTagTest_182, ZeroUnknownInSingleElement_182) {
  printTag<std::size(singleElementArray), singleElementArray>(os, 0, nullptr);
  std::string output = os.str();
  EXPECT_EQ(output, "(0)");
}

// Test consecutive array - first element
TEST_F(PrintTagTest_182, ConsecutiveArrayFirst_182) {
  printTag<std::size(consecutiveArray), consecutiveArray>(os, 0, nullptr);
  EXPECT_EQ(os.str(), "Val0");
}

// Test consecutive array - last element
TEST_F(PrintTagTest_182, ConsecutiveArrayLast_182) {
  printTag<std::size(consecutiveArray), consecutiveArray>(os, 4, nullptr);
  EXPECT_EQ(os.str(), "Val4");
}

// Test consecutive array - middle element
TEST_F(PrintTagTest_182, ConsecutiveArrayMiddle_182) {
  printTag<std::size(consecutiveArray), consecutiveArray>(os, 2, nullptr);
  EXPECT_EQ(os.str(), "Val2");
}

// Test consecutive array - one past last (unknown)
TEST_F(PrintTagTest_182, ConsecutiveArrayOnePastLast_182) {
  printTag<std::size(consecutiveArray), consecutiveArray>(os, 5, nullptr);
  EXPECT_EQ(os.str(), "(5)");
}

// Test with nullptr ExifData (should work fine as it's not typically used by printTag)
TEST_F(PrintTagTest_182, NullExifDataPointer_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 1, nullptr);
  EXPECT_EQ(os.str(), "One");
}

// Test that unknown value zero is printed correctly when not in array
TEST_F(PrintTagTest_182, ZeroUnknown_182) {
  printTag<std::size(singleElementArray), singleElementArray>(os, 0, nullptr);
  EXPECT_EQ(os.str(), "(0)");
}

// Test very large negative unknown value
TEST_F(PrintTagTest_182, VeryLargeNegativeUnknown_182) {
  printTag<std::size(testTagArray), testTagArray>(os, -9999999, nullptr);
  std::string output = os.str();
  EXPECT_EQ(output, "(-9999999)");
}

// Test multiple writes to the same stream (cumulative)
TEST_F(PrintTagTest_182, CumulativeWrites_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 1, nullptr);
  printTag<std::size(testTagArray), testTagArray>(os, 2, nullptr);
  EXPECT_EQ(os.str(), "OneTwo");
}

// Test cumulative writes with unknown value
TEST_F(PrintTagTest_182, CumulativeWritesWithUnknown_182) {
  printTag<std::size(testTagArray), testTagArray>(os, 1, nullptr);
  printTag<std::size(testTagArray), testTagArray>(os, 999, nullptr);
  EXPECT_EQ(os.str(), "One(999)");
}
