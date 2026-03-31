#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the class under test
namespace Exiv2 {
namespace Internal {

class PanasonicMakerNote {
 public:
  std::ostream& printPanasonicText(std::ostream& os, const Value& value, const ExifData*) {
    if (value.size() > 0 && value.typeId() == undefined) {
      for (size_t i = 0; i < value.size(); i++) {
        if (value.toInt64(i) == 0) {
          break;
        }
        os << static_cast<char>(value.toInt64(i));
      }
      return os;
    }
    return os << value;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_713 : public ::testing::Test {
 protected:
  PanasonicMakerNote maker_;
  std::ostringstream os_;
};

// Test: Undefined type value with simple ASCII text (no null terminator in data)
TEST_F(PanasonicMakerNoteTest_713, PrintText_SimpleAsciiUndefined_713) {
  DataBuf buf(5);
  auto* data = buf.data();
  data[0] = 'H';
  data[1] = 'e';
  data[2] = 'l';
  data[3] = 'l';
  data[4] = 'o';

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Hello");
}

// Test: Undefined type value with null terminator in the middle
TEST_F(PanasonicMakerNoteTest_713, PrintText_NullTerminatedInMiddle_713) {
  DataBuf buf(8);
  auto* data = buf.data();
  data[0] = 'H';
  data[1] = 'i';
  data[2] = 0;  // null terminator
  data[3] = 'X';
  data[4] = 'Y';
  data[5] = 'Z';
  data[6] = 'W';
  data[7] = 'Q';

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Hi");
}

// Test: Undefined type value starting with null byte (empty string)
TEST_F(PanasonicMakerNoteTest_713, PrintText_StartsWithNull_713) {
  DataBuf buf(4);
  auto* data = buf.data();
  data[0] = 0;
  data[1] = 'A';
  data[2] = 'B';
  data[3] = 'C';

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "");
}

// Test: Non-undefined type value falls through to os << value
TEST_F(PanasonicMakerNoteTest_713, PrintText_NonUndefinedType_UsesDefaultOutput_713) {
  UShortValue value;
  value.read("42");

  maker_.printPanasonicText(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result, "42");
}

// Test: Undefined type value with single character
TEST_F(PanasonicMakerNoteTest_713, PrintText_SingleChar_713) {
  DataBuf buf(1);
  buf.data()[0] = 'Z';

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Z");
}

// Test: Undefined type value with single null byte
TEST_F(PanasonicMakerNoteTest_713, PrintText_SingleNullByte_713) {
  DataBuf buf(1);
  buf.data()[0] = 0;

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "");
}

// Test: Empty value with non-undefined type
TEST_F(PanasonicMakerNoteTest_713, PrintText_EmptyNonUndefinedValue_713) {
  // An AsciiValue with empty string
  AsciiValue value;

  maker_.printPanasonicText(os_, value, nullptr);
  // Should go to os << value path since size is 0 or type is not undefined
  // We just verify it doesn't crash
  // The output depends on Value's operator<< for empty value
}

// Test: Undefined type value with all printable ASCII
TEST_F(PanasonicMakerNoteTest_713, PrintText_AllPrintableAscii_713) {
  std::string text = "PANASONIC DMC-GX85";
  DataBuf buf(text.size());
  for (size_t i = 0; i < text.size(); i++) {
    buf.data()[i] = static_cast<byte>(text[i]);
  }

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), text);
}

// Test: Undefined type value with text followed by null and then garbage
TEST_F(PanasonicMakerNoteTest_713, PrintText_TextThenNullThenGarbage_713) {
  DataBuf buf(10);
  auto* data = buf.data();
  data[0] = 'T';
  data[1] = 'e';
  data[2] = 's';
  data[3] = 't';
  data[4] = 0;
  data[5] = 0xFF;
  data[6] = 0xFE;
  data[7] = 0xAB;
  data[8] = 0xCD;
  data[9] = 0xEF;

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Test");
}

// Test: Passing nullptr for ExifData (should be fine since it's unused)
TEST_F(PanasonicMakerNoteTest_713, PrintText_NullExifData_713) {
  DataBuf buf(3);
  buf.data()[0] = 'A';
  buf.data()[1] = 'B';
  buf.data()[2] = 'C';

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  EXPECT_NO_THROW(maker_.printPanasonicText(os_, value, nullptr));
  EXPECT_EQ(os_.str(), "ABC");
}

// Test: Undefined value with non-ASCII bytes (high bytes) and no null
TEST_F(PanasonicMakerNoteTest_713, PrintText_HighBytes_713) {
  DataBuf buf(3);
  buf.data()[0] = static_cast<byte>(0xC0);
  buf.data()[1] = static_cast<byte>(0xA9);
  buf.data()[2] = static_cast<byte>(0xBB);

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  // Should output 3 characters (even if non-printable), no null to break
  EXPECT_EQ(os_.str().size(), 3u);
}

// Test: Return value is the same stream reference
TEST_F(PanasonicMakerNoteTest_713, PrintText_ReturnsStreamReference_713) {
  DataBuf buf(2);
  buf.data()[0] = 'X';
  buf.data()[1] = 0;

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  std::ostream& result = maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: Long text string
TEST_F(PanasonicMakerNoteTest_713, PrintText_LongString_713) {
  std::string longText(1000, 'A');
  DataBuf buf(longText.size());
  for (size_t i = 0; i < longText.size(); i++) {
    buf.data()[i] = static_cast<byte>(longText[i]);
  }

  DataValue value(undefined);
  value.read(buf.data(), buf.size());

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), longText);
}

// Test: Integer value (not undefined type) outputs the value representation
TEST_F(PanasonicMakerNoteTest_713, PrintText_IntegerValue_713) {
  ULongValue value;
  value.read("12345");

  maker_.printPanasonicText(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "12345");
}
