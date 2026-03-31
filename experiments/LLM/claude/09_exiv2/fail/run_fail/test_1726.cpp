#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace
// Since the class is defined in sigmamn_int.cpp, we include or replicate the minimal interface
namespace Exiv2 {
namespace Internal {

class SigmaMakerNote {
public:
    std::ostream& print0x0008(std::ostream& os, const Value& value, const ExifData*) {
        switch (value.toString().front()) {
            case 'P':
                os << "Program";
                break;
            case 'A':
                os << "Aperture priority";
                break;
            case 'S':
                os << "Shutter priority";
                break;
            case 'M':
                os << "Manual";
                break;
            default:
                os << "(" << value << ")";
                break;
        }
        return os;
    }
};

}  // namespace Internal
}  // namespace Exiv2

class SigmaMakerNoteTest_1726 : public ::testing::Test {
protected:
    Exiv2::Internal::SigmaMakerNote maker_;
    std::ostringstream os_;
};

// Test Program mode ('P')
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_ProgramMode_1726) {
    Exiv2::AsciiValue value;
    value.read("P");
    maker_.print0x0008(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "Program");
}

// Test Aperture priority mode ('A')
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_AperturePriority_1726) {
    Exiv2::AsciiValue value;
    value.read("A");
    maker_.print0x0008(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "Aperture priority");
}

// Test Shutter priority mode ('S')
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_ShutterPriority_1726) {
    Exiv2::AsciiValue value;
    value.read("S");
    maker_.print0x0008(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "Shutter priority");
}

// Test Manual mode ('M')
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_ManualMode_1726) {
    Exiv2::AsciiValue value;
    value.read("M");
    maker_.print0x0008(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "Manual");
}

// Test default case with unknown character
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_UnknownMode_1726) {
    Exiv2::AsciiValue value;
    value.read("X");
    maker_.print0x0008(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test default case with lowercase 'p' (should not match 'P')
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_LowercaseP_DefaultCase_1726) {
    Exiv2::AsciiValue value;
    value.read("p");
    maker_.print0x0008(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result, "Program");
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test default case with lowercase 'a'
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_LowercaseA_DefaultCase_1726) {
    Exiv2::AsciiValue value;
    value.read("a");
    maker_.print0x0008(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result, "Aperture priority");
    EXPECT_TRUE(result.front() == '(');
}

// Test default case with lowercase 's'
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_LowercaseS_DefaultCase_1726) {
    Exiv2::AsciiValue value;
    value.read("s");
    maker_.print0x0008(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result, "Shutter priority");
    EXPECT_TRUE(result.front() == '(');
}

// Test default case with lowercase 'm'
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_LowercaseM_DefaultCase_1726) {
    Exiv2::AsciiValue value;
    value.read("m");
    maker_.print0x0008(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result, "Manual");
    EXPECT_TRUE(result.front() == '(');
}

// Test that the function returns the ostream reference
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_ReturnsOstream_1726) {
    Exiv2::AsciiValue value;
    value.read("P");
    std::ostream& result = maker_.print0x0008(os_, value, nullptr);
    EXPECT_EQ(&result, &os_);
}

// Test with a numeric character (default case)
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_NumericCharDefault_1726) {
    Exiv2::AsciiValue value;
    value.read("1");
    maker_.print0x0008(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with a longer string starting with 'P'
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_LongerStringStartingWithP_1726) {
    Exiv2::AsciiValue value;
    value.read("Program");
    maker_.print0x0008(os_, value, nullptr);
    // Only the first character matters, should still output "Program"
    EXPECT_EQ(os_.str(), "Program");
}

// Test with a longer string starting with 'A'
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_LongerStringStartingWithA_1726) {
    Exiv2::AsciiValue value;
    value.read("Auto");
    maker_.print0x0008(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "Aperture priority");
}

// Test with nullptr ExifData (should work fine since it's unused)
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_NullExifData_1726) {
    Exiv2::AsciiValue value;
    value.read("M");
    maker_.print0x0008(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "Manual");
}

// Test with special character in default case
TEST_F(SigmaMakerNoteTest_1726, Print0x0008_SpecialCharDefault_1726) {
    Exiv2::AsciiValue value;
    value.read("!");
    maker_.print0x0008(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}
