// =================================================================================================
// TestProjects/exiv2/tests/sonymn_int_printFocusMode2_test.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"   // Exiv2::Internal::SonyMakerNote
#include "exiv2/exif.hpp"   // Exiv2::ExifData
#include "exiv2/types.hpp"  // Exiv2::TypeId
#include "exiv2/value.hpp"  // Exiv2::Value

namespace {

using Exiv2::AsciiString;     // (not used directly, but common in this area)
using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::unsignedByte;
using Exiv2::asciiString;

class FakeValue final : public Exiv2::Value {
 public:
  FakeValue(TypeId type, size_t cnt, uint32_t v0, std::string text)
      : Exiv2::Value(type), cnt_(cnt), v0_(v0), text_(std::move(text)) {}

  size_t count() override { return cnt_; }
  uint32_t toUint32(size_t /*n*/) override { return v0_; }
  const std::ostream& write(std::ostream& os) override {
    os << text_;
    return os;
  }

 private:
  size_t cnt_;
  uint32_t v0_;
  std::string text_;
};

class SonyMakerNotePrintFocusMode2Test_1593 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote mn_;
};

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, NullMetadata_ParenthesizesValue_1593) {
  FakeValue v(unsignedByte, 1, 0, "7");
  std::ostringstream os;

  mn_.printFocusMode2(os, v, nullptr);

  EXPECT_EQ(os.str(), "(7)");
}

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, CountNotOne_ParenthesizesValue_1593) {
  FakeValue v(unsignedByte, 2, 0, "1 2");
  ExifData md;
  std::ostringstream os;

  mn_.printFocusMode2(os, v, &md);

  EXPECT_EQ(os.str(), "(1 2)");
}

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, TypeNotUnsignedByte_ParenthesizesValue_1593) {
  FakeValue v(asciiString, 1, 0, "abc");
  ExifData md;
  std::ostringstream os;

  mn_.printFocusMode2(os, v, &md);

  EXPECT_EQ(os.str(), "(abc)");
}

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, ModelMissing_ParenthesizesValue_1593) {
  FakeValue v(unsignedByte, 1, 0, "0");
  ExifData md;  // no model field set
  std::ostringstream os;

  mn_.printFocusMode2(os, v, &md);

  EXPECT_EQ(os.str(), "(0)");
}

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, ModelNotStartingWithDSC_UsesTagDetails_1593) {
  FakeValue v(unsignedByte, 1, 0, "0");
  ExifData md;
  md["Exif.Image.Model"] = "ILCE-7M3";  // does not start with "DSC-"
  std::ostringstream os;

  mn_.printFocusMode2(os, v, &md);

  // When tag-details printing is used, known mappings include 0 -> "Manual".
  EXPECT_EQ(os.str(), "Manual");
}

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, ModelInAllowedList_UsesTagDetails_1593) {
  FakeValue v(unsignedByte, 1, 2, "2");
  ExifData md;
  md["Exif.Image.Model"] = "DSC-RX100M7";  // in the allowed list
  std::ostringstream os;

  mn_.printFocusMode2(os, v, &md);

  // Known mapping includes 2 -> "AF-S".
  EXPECT_EQ(os.str(), "AF-S");
}

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, OtherDSCModel_PrintsNA_1593) {
  FakeValue v(unsignedByte, 1, 0, "0");
  ExifData md;
  md["Exif.Image.Model"] = "DSC-FOO123";  // starts with "DSC-" but not in the allowed list
  std::ostringstream os;

  mn_.printFocusMode2(os, v, &md);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNotePrintFocusMode2Test_1593, AllowedListMapping_AF_D_1593) {
  FakeValue v(unsignedByte, 1, 7, "7");
  ExifData md;
  md["Exif.Image.Model"] = "DSC-RX10M4";  // in the allowed list
  std::ostringstream os;

  mn_.printFocusMode2(os, v, &md);

  // Known mapping includes 7 -> "AF-D".
  EXPECT_EQ(os.str(), "AF-D");
}

}  // namespace