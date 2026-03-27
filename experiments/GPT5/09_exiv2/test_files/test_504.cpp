// File: test_nikon3makernote_printpicturecontrol_504.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

// Nikon3MakerNote is an internal class; in the Exiv2 tree it is typically declared here.
#include "nikonmn_int.hpp"

#include <cstdint>
#include <sstream>
#include <string>

namespace {

using Exiv2::TypeId;
using Exiv2::Value;

class Nikon3MakerNoteTest_504 : public ::testing::Test {
 protected:
  static std::string StreamValue(const Value& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }

  static Value::AutoPtr MakeValue(TypeId type, const std::string& input) {
    Value::AutoPtr v = Value::create(type);
    ASSERT_TRUE(v.get() != nullptr);
    // Value::read parses one or more components from a string.
    v->read(input);
    return v;
  }
};

}  // namespace

TEST_F(Nikon3MakerNoteTest_504, ReturnsSameStreamReference_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "128");  // count==1
  std::ostringstream os;
  std::ostream& ret = mn.printPictureControl(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(Nikon3MakerNoteTest_504, WhenCountIsNotOne_PrintsParenthesizedValue_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  // Two components => count != 1
  Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "128 129");

  std::ostringstream os;
  mn.printPictureControl(os, *v, nullptr);

  const std::string expected = "(" + StreamValue(*v) + ")";
  EXPECT_EQ(os.str(), expected);
}

TEST_F(Nikon3MakerNoteTest_504, WhenTypeIsNotUnsignedByte_PrintsParenthesizedValue_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  // Same numeric content, different type => typeId != unsignedByte
  Value::AutoPtr v = MakeValue(Exiv2::unsignedShort, "128");

  std::ostringstream os;
  mn.printPictureControl(os, *v, nullptr);

  const std::string expected = "(" + StreamValue(*v) + ")";
  EXPECT_EQ(os.str(), expected);
}

TEST_F(Nikon3MakerNoteTest_504, WhenValueRepresentsNormal_PrintsNormal_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  // 0x80 -> pcval 0
  Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "128");

  std::ostringstream os;
  mn.printPictureControl(os, *v, nullptr);

  EXPECT_EQ(os.str(), "Normal");
}

TEST_F(Nikon3MakerNoteTest_504, WhenValueRepresentsNA_PrintsNA_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  // 0xFF -> pcval 127
  Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "255");

  std::ostringstream os;
  mn.printPictureControl(os, *v, nullptr);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(Nikon3MakerNoteTest_504, WhenValueRepresentsUser_PrintsUser_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  // 0x01 -> pcval -127
  Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "1");

  std::ostringstream os;
  mn.printPictureControl(os, *v, nullptr);

  EXPECT_EQ(os.str(), "User");
}

TEST_F(Nikon3MakerNoteTest_504, WhenValueRepresentsAuto_PrintsAuto_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  // 0x00 -> pcval -128
  Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "0");

  std::ostringstream os;
  mn.printPictureControl(os, *v, nullptr);

  EXPECT_EQ(os.str(), "Auto");
}

TEST_F(Nikon3MakerNoteTest_504, WhenValueIsOther_PrintsSignedOffsetNumber_504) {
  Exiv2::Internal::Nikon3MakerNote mn;

  // 0x81 -> pcval 1
  {
    Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "129");
    std::ostringstream os;
    mn.printPictureControl(os, *v, nullptr);
    EXPECT_EQ(os.str(), "1");
  }

  // Boundary-ish negative (but not a special label): 0x7F -> pcval -1
  {
    Value::AutoPtr v = MakeValue(Exiv2::unsignedByte, "127");
    std::ostringstream os;
    mn.printPictureControl(os, *v, nullptr);
    EXPECT_EQ(os.str(), "-1");
  }
}