#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace
// Since the function is defined in nikonmn_int.cpp, we need to include appropriate headers
// or recreate the class interface for testing purposes.

// Based on the provided code, we recreate the minimal class definition for testing
#include "nikonmn_int.hpp"

// If the above header doesn't expose the class directly, we may need to work with
// what's available. Let's define a test fixture.

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_483 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_note_;
  std::ostringstream os_;

  // Helper to create an unsigned byte value with a single entry
  std::unique_ptr<Value> makeUnsignedByte(int val) {
    auto v = Value::create(unsignedByte);
    v->read(std::to_string(val));
    return v;
  }

  // Helper to create an unsigned short value with a single entry
  std::unique_ptr<Value> makeUnsignedShort(int val) {
    auto v = Value::create(unsignedShort);
    v->read(std::to_string(val));
    return v;
  }

  // Helper to create an unsigned byte value with multiple entries
  std::unique_ptr<Value> makeMultipleUnsignedBytes(const std::string& vals) {
    auto v = Value::create(unsignedByte);
    v->read(vals);
    return v;
  }
};

// Test: Value of 0 should return "n/a"
TEST_F(Nikon3MakerNoteTest_483, ZeroReturnsNA_483) {
  auto val = makeUnsignedByte(0);
  maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("n/a"), std::string::npos) 
      << "Expected 'n/a' for value 0, got: " << result;
}

// Test: Value of 255 should return "n/a"
TEST_F(Nikon3MakerNoteTest_483, Value255ReturnsNA_483) {
  auto val = makeUnsignedByte(255);
  maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("n/a"), std::string::npos) 
      << "Expected 'n/a' for value 255, got: " << result;
}

// Test: Normal value (e.g., 10) should return formatted Hz string
TEST_F(Nikon3MakerNoteTest_483, NormalValueReturnsHz_483) {
  auto val = makeUnsignedByte(10);
  maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("10"), std::string::npos) 
      << "Expected '10' in output, got: " << result;
  EXPECT_NE(result.find("Hz"), std::string::npos) 
      << "Expected 'Hz' in output, got: " << result;
}

// Test: Value of 1 (boundary, smallest non-zero non-255) should return Hz
TEST_F(Nikon3MakerNoteTest_483, Value1ReturnsHz_483) {
  auto val = makeUnsignedByte(1);
  maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("1"), std::string::npos) 
      << "Expected '1' in output, got: " << result;
  EXPECT_NE(result.find("Hz"), std::string::npos) 
      << "Expected 'Hz' in output, got: " << result;
}

// Test: Value of 254 (boundary, largest non-255 non-zero) should return Hz
TEST_F(Nikon3MakerNoteTest_483, Value254ReturnsHz_483) {
  auto val = makeUnsignedByte(254);
  maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("254"), std::string::npos) 
      << "Expected '254' in output, got: " << result;
  EXPECT_NE(result.find("Hz"), std::string::npos) 
      << "Expected 'Hz' in output, got: " << result;
}

// Test: Wrong type (unsignedShort instead of unsignedByte) should return parenthesized value
TEST_F(Nikon3MakerNoteTest_483, WrongTypeReturnsParenthesized_483) {
  auto val = makeUnsignedShort(50);
  maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("("), std::string::npos) 
      << "Expected '(' in output for wrong type, got: " << result;
  EXPECT_NE(result.find(")"), std::string::npos) 
      << "Expected ')' in output for wrong type, got: " << result;
}

// Test: Multiple values (count != 1) should return parenthesized value
TEST_F(Nikon3MakerNoteTest_483, MultipleValuesReturnsParenthesized_483) {
  auto val = makeMultipleUnsignedBytes("10 20");
  // Only if count > 1 does this test apply
  if (val->count() > 1) {
    maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos)
        << "Expected '(' in output for multiple values, got: " << result;
    EXPECT_NE(result.find(")"), std::string::npos)
        << "Expected ')' in output for multiple values, got: " << result;
  }
}

// Test: Value of 128 (mid-range) should return Hz
TEST_F(Nikon3MakerNoteTest_483, MidRangeValueReturnsHz_483) {
  auto val = makeUnsignedByte(128);
  maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("128"), std::string::npos) 
      << "Expected '128' in output, got: " << result;
  EXPECT_NE(result.find("Hz"), std::string::npos) 
      << "Expected 'Hz' in output, got: " << result;
}

// Test: Returns the ostream reference (chaining)
TEST_F(Nikon3MakerNoteTest_483, ReturnsOstreamReference_483) {
  auto val = makeUnsignedByte(50);
  std::ostream& returned = maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  EXPECT_EQ(&returned, &os_);
}

// Test: Returns the ostream reference for n/a case
TEST_F(Nikon3MakerNoteTest_483, ReturnsOstreamReferenceForNA_483) {
  auto val = makeUnsignedByte(0);
  std::ostream& returned = maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  EXPECT_EQ(&returned, &os_);
}

// Test: Returns the ostream reference for error case
TEST_F(Nikon3MakerNoteTest_483, ReturnsOstreamReferenceForError_483) {
  auto val = makeUnsignedShort(50);
  std::ostream& returned = maker_note_.printRepeatingFlashRate(os_, *val, nullptr);
  EXPECT_EQ(&returned, &os_);
}

// Test: Passing nullptr for ExifData* is handled gracefully
TEST_F(Nikon3MakerNoteTest_483, NullExifDataHandledGracefully_483) {
  auto val = makeUnsignedByte(42);
  EXPECT_NO_THROW(maker_note_.printRepeatingFlashRate(os_, *val, nullptr));
  std::string result = os_.str();
  EXPECT_NE(result.find("Hz"), std::string::npos);
}

}  // namespace
