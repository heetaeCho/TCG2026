#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>
#include <cstdint>

// Minimal stubs/mocks for Exiv2 types needed by the code under test

// Translation stub
#define _(x) x

namespace Exiv2 {

using byte = uint8_t;

class ExifData {};

class Value {
 public:
  virtual ~Value() = default;
  virtual uint32_t toUint32(long n = 0) const = 0;
  virtual long count() const = 0;
};

// A simple concrete Value implementation for testing
class TestValue : public Value {
 public:
  explicit TestValue(const std::vector<uint32_t>& vals) : vals_(vals) {}

  uint32_t toUint32(long n = 0) const override {
    if (n < 0 || static_cast<size_t>(n) >= vals_.size())
      return 0;
    return vals_[static_cast<size_t>(n)];
  }

  long count() const override {
    return static_cast<long>(vals_.size());
  }

 private:
  std::vector<uint32_t> vals_;
};

namespace Internal {

class PentaxMakerNote {
 public:
  std::ostream& printBracketing(std::ostream& os, const Value& value, const ExifData*) {
    std::ios::fmtflags f(os.flags());
    if (auto l0 = value.toUint32(0); l0 < 10) {
      os << std::setprecision(2) << static_cast<float>(l0) / 3 << " EV";
    } else {
      os << std::setprecision(2) << static_cast<float>(l0) - 9.5F << " EV";
    }
    if (value.count() == 2) {
      const auto l1 = value.toUint32(1);
      os << " (";
      if (l1 == 0) {
        os << _("No extended bracketing");
      } else {
        auto type = l1 >> 8;
        auto range = static_cast<byte>(l1);
        switch (type) {
          case 1:
            os << _("WB-BA");
            break;
          case 2:
            os << _("WB-GM");
            break;
          case 3:
            os << _("Saturation");
            break;
          case 4:
            os << _("Sharpness");
            break;
          case 5:
            os << _("Contrast");
            break;
          default:
            os << _("Unknown ") << type;
            break;
        }
        os << " " << +range;
      }
      os << ")";
    }
    os.flags(f);
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMakerNoteTest_199 : public ::testing::Test {
 protected:
  PentaxMakerNote pmn_;
  std::ostringstream os_;
};

// ========== Single value tests (count == 1) ==========

TEST_F(PentaxMakerNoteTest_199, SingleValue_Zero_199) {
  TestValue val({0});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV");
}

TEST_F(PentaxMakerNoteTest_199, SingleValue_Three_199) {
  // 3/3 = 1.0
  TestValue val({3});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1 EV");
}

TEST_F(PentaxMakerNoteTest_199, SingleValue_Six_199) {
  // 6/3 = 2.0
  TestValue val({6});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2 EV");
}

TEST_F(PentaxMakerNoteTest_199, SingleValue_Nine_199) {
  // 9/3 = 3.0
  TestValue val({9});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "3 EV");
}

TEST_F(PentaxMakerNoteTest_199, SingleValue_One_199) {
  // 1/3 = 0.333...  with precision 2
  TestValue val({1});
  pmn_.printBracketing(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("EV") != std::string::npos);
  EXPECT_TRUE(result.find("0.3") != std::string::npos);
}

TEST_F(PentaxMakerNoteTest_199, SingleValue_Ten_UsesAlternateFormula_199) {
  // 10 >= 10, so 10 - 9.5 = 0.5
  TestValue val({10});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0.5 EV");
}

TEST_F(PentaxMakerNoteTest_199, SingleValue_Fifteen_199) {
  // 15 - 9.5 = 5.5
  TestValue val({15});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "5.5 EV");
}

TEST_F(PentaxMakerNoteTest_199, SingleValue_Twenty_199) {
  // 20 - 9.5 = 10.5 -> with precision 2 => "10"
  TestValue val({20});
  pmn_.printBracketing(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// ========== Two value tests (count == 2), second value = 0 ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_NoExtendedBracketing_199) {
  TestValue val({3, 0});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1 EV (No extended bracketing)");
}

// ========== Two value tests, type = WB-BA (type=1) ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_Type1_WBBA_199) {
  // l1 = (1 << 8) | 5 = 261; type=1, range=5
  uint32_t l1 = (1 << 8) | 5;
  TestValue val({0, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV (WB-BA 5)");
}

// ========== Two value tests, type = WB-GM (type=2) ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_Type2_WBGM_199) {
  uint32_t l1 = (2 << 8) | 10;
  TestValue val({6, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2 EV (WB-GM 10)");
}

// ========== Two value tests, type = Saturation (type=3) ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_Type3_Saturation_199) {
  uint32_t l1 = (3 << 8) | 7;
  TestValue val({3, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1 EV (Saturation 7)");
}

// ========== Two value tests, type = Sharpness (type=4) ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_Type4_Sharpness_199) {
  uint32_t l1 = (4 << 8) | 3;
  TestValue val({0, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV (Sharpness 3)");
}

// ========== Two value tests, type = Contrast (type=5) ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_Type5_Contrast_199) {
  uint32_t l1 = (5 << 8) | 2;
  TestValue val({9, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "3 EV (Contrast 2)");
}

// ========== Two value tests, unknown type ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_UnknownType_199) {
  uint32_t l1 = (6 << 8) | 1;
  TestValue val({0, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV (Unknown 6 1)");
}

TEST_F(PentaxMakerNoteTest_199, TwoValues_UnknownTypeZero_199) {
  // type=0 but l1 != 0 (range is nonzero)
  uint32_t l1 = (0 << 8) | 1;  // l1 = 1
  TestValue val({0, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV (Unknown 0 1)");
}

// ========== Boundary: l0 = 9 (just below 10) ==========

TEST_F(PentaxMakerNoteTest_199, BoundaryL0Is9_SingleValue_199) {
  // 9/3 = 3
  TestValue val({9});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "3 EV");
}

// ========== Boundary: l0 = 10 (just at 10) ==========

TEST_F(PentaxMakerNoteTest_199, BoundaryL0Is10_SingleValue_199) {
  // 10 - 9.5 = 0.5
  TestValue val({10});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0.5 EV");
}

// ========== Three values (count == 3), should not print extended bracketing ==========

TEST_F(PentaxMakerNoteTest_199, ThreeValues_NoExtendedBracketingSection_199) {
  TestValue val({3, 0, 0});
  pmn_.printBracketing(os_, val, nullptr);
  // count() != 2, so no parenthesized section
  EXPECT_EQ(os_.str(), "1 EV");
}

// ========== Verify range is only low byte ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_RangeIsByteOnly_199) {
  // l1 = (1 << 8) | 255 = 511; type=1, range=255
  uint32_t l1 = (1 << 8) | 255;
  TestValue val({0, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV (WB-BA 255)");
}

TEST_F(PentaxMakerNoteTest_199, TwoValues_RangeZeroButTypeNonZero_199) {
  // l1 = (3 << 8) | 0 = 768; type=3, range=0
  // l1 != 0 so it goes into the else branch
  uint32_t l1 = (3 << 8);
  TestValue val({0, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV (Saturation 0)");
}

// ========== Return value test ==========

TEST_F(PentaxMakerNoteTest_199, ReturnsOstream_199) {
  TestValue val({0});
  std::ostream& result = pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ========== Large l0 with two values ==========

TEST_F(PentaxMakerNoteTest_199, LargeL0WithExtendedBracketing_199) {
  // l0 = 100, 100 - 9.5 = 90.5
  uint32_t l1 = (5 << 8) | 4;
  TestValue val({100, l1});
  pmn_.printBracketing(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("EV") != std::string::npos);
  EXPECT_TRUE(result.find("Contrast 4") != std::string::npos);
}

// ========== Flags preservation test ==========

TEST_F(PentaxMakerNoteTest_199, FlagsArePreserved_199) {
  os_ << std::hex;
  std::ios::fmtflags before = os_.flags();
  TestValue val({3, 0});
  pmn_.printBracketing(os_, val, nullptr);
  std::ios::fmtflags after = os_.flags();
  EXPECT_EQ(before, after);
}

// ========== l1 with high type value ==========

TEST_F(PentaxMakerNoteTest_199, TwoValues_HighUnknownType_199) {
  uint32_t l1 = (255 << 8) | 128;
  TestValue val({0, l1});
  pmn_.printBracketing(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "0 EV (Unknown 255 128)");
}
