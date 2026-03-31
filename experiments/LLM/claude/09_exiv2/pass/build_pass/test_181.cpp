#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "tags_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define test TagDetails arrays for use in tests
static const TagDetails testTagDetails[] = {
    {1, "First"},
    {2, "Second"},
    {3, "Third"},
};

static const TagDetails singleElementArray[] = {
    {42, "FortyTwo"},
};

static const TagDetails negativeValues[] = {
    {-1, "Negative One"},
    {0, "Zero"},
    {1, "Positive One"},
};

static const TagDetails largeValues[] = {
    {0, "Zero"},
    {255, "MaxByte"},
    {65535, "MaxUShort"},
};

// Test fixture
class PrintTagNoErrorTest_181 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test with integer type - value found in array
TEST_F(PrintTagNoErrorTest_181, IntegerValueFound_181) {
  printTagNoError<3, testTagDetails>(os, 1, nullptr);
  EXPECT_EQ(os.str(), "First");
}

TEST_F(PrintTagNoErrorTest_181, IntegerValueFoundSecond_181) {
  printTagNoError<3, testTagDetails>(os, 2, nullptr);
  EXPECT_EQ(os.str(), "Second");
}

TEST_F(PrintTagNoErrorTest_181, IntegerValueFoundThird_181) {
  printTagNoError<3, testTagDetails>(os, 3, nullptr);
  EXPECT_EQ(os.str(), "Third");
}

// Test with integer type - value NOT found in array
TEST_F(PrintTagNoErrorTest_181, IntegerValueNotFound_181) {
  printTagNoError<3, testTagDetails>(os, 99, nullptr);
  EXPECT_EQ(os.str(), "99");
}

TEST_F(PrintTagNoErrorTest_181, IntegerValueNotFoundZero_181) {
  printTagNoError<3, testTagDetails>(os, 0, nullptr);
  EXPECT_EQ(os.str(), "0");
}

// Test with single element array - found
TEST_F(PrintTagNoErrorTest_181, SingleElementArrayFound_181) {
  printTagNoError<1, singleElementArray>(os, 42, nullptr);
  EXPECT_EQ(os.str(), "FortyTwo");
}

// Test with single element array - not found
TEST_F(PrintTagNoErrorTest_181, SingleElementArrayNotFound_181) {
  printTagNoError<1, singleElementArray>(os, 0, nullptr);
  EXPECT_EQ(os.str(), "0");
}

// Test with negative values in array
TEST_F(PrintTagNoErrorTest_181, NegativeValueFound_181) {
  printTagNoError<3, negativeValues>(os, -1, nullptr);
  EXPECT_EQ(os.str(), "Negative One");
}

TEST_F(PrintTagNoErrorTest_181, ZeroValueFound_181) {
  printTagNoError<3, negativeValues>(os, 0, nullptr);
  EXPECT_EQ(os.str(), "Zero");
}

TEST_F(PrintTagNoErrorTest_181, PositiveValueInNegativeArray_181) {
  printTagNoError<3, negativeValues>(os, 1, nullptr);
  EXPECT_EQ(os.str(), "Positive One");
}

// Test with Value type - value found
TEST_F(PrintTagNoErrorTest_181, ExivValueTypeFound_181) {
  auto val = Value::create(unsignedShort);
  val->read("1");
  printTagNoError<3, testTagDetails>(os, *val, nullptr);
  EXPECT_EQ(os.str(), "First");
}

// Test with Value type - value not found
TEST_F(PrintTagNoErrorTest_181, ExivValueTypeNotFound_181) {
  auto val = Value::create(unsignedShort);
  val->read("99");
  printTagNoError<3, testTagDetails>(os, *val, nullptr);
  EXPECT_EQ(os.str(), "99");
}

// Test with Value type - zero not in array
TEST_F(PrintTagNoErrorTest_181, ExivValueTypeZeroNotFound_181) {
  auto val = Value::create(unsignedShort);
  val->read("0");
  printTagNoError<3, testTagDetails>(os, *val, nullptr);
  EXPECT_EQ(os.str(), "0");
}

// Test large values
TEST_F(PrintTagNoErrorTest_181, LargeValueFound_181) {
  printTagNoError<3, largeValues>(os, 65535, nullptr);
  EXPECT_EQ(os.str(), "MaxUShort");
}

TEST_F(PrintTagNoErrorTest_181, LargeValueNotFound_181) {
  printTagNoError<3, largeValues>(os, 12345, nullptr);
  EXPECT_EQ(os.str(), "12345");
}

// Test that return value is the stream reference
TEST_F(PrintTagNoErrorTest_181, ReturnsStreamReferenceOnFound_181) {
  auto& result = printTagNoError<3, testTagDetails>(os, 1, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PrintTagNoErrorTest_181, ReturnsStreamReferenceOnNotFound_181) {
  auto& result = printTagNoError<3, testTagDetails>(os, 99, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test with ExifData pointer (non-null) - should still work the same
TEST_F(PrintTagNoErrorTest_181, NonNullExifDataFound_181) {
  ExifData exifData;
  printTagNoError<3, testTagDetails>(os, 2, &exifData);
  EXPECT_EQ(os.str(), "Second");
}

TEST_F(PrintTagNoErrorTest_181, NonNullExifDataNotFound_181) {
  ExifData exifData;
  printTagNoError<3, testTagDetails>(os, 50, &exifData);
  EXPECT_EQ(os.str(), "50");
}

// Test with Value type and signed long
TEST_F(PrintTagNoErrorTest_181, ExivSignedLongValueFound_181) {
  auto val = Value::create(signedLong);
  val->read("-1");
  printTagNoError<3, negativeValues>(os, *val, nullptr);
  EXPECT_EQ(os.str(), "Negative One");
}

// Test boundary - max byte value
TEST_F(PrintTagNoErrorTest_181, MaxByteValueFound_181) {
  printTagNoError<3, largeValues>(os, 255, nullptr);
  EXPECT_EQ(os.str(), "MaxByte");
}

// Test negative integer not in negative array
TEST_F(PrintTagNoErrorTest_181, NegativeValueNotFound_181) {
  printTagNoError<3, negativeValues>(os, -100, nullptr);
  EXPECT_EQ(os.str(), "-100");
}
