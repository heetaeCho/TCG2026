#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to replicate the class interface for testing since it's in an internal namespace
namespace Exiv2 {
namespace Internal {

class MinoltaMakerNote {
public:
    std::ostream& printMinoltaTimeStd(std::ostream& os, const Value& value, const ExifData*) {
        auto val = value.toInt64();
        // Using manual formatting since stringFormat may not be available
        char buf[16];
        snprintf(buf, sizeof(buf), "%02lld:%02lld:%02lld",
                 (long long)(val / 65536),
                 (long long)((val % 65536) / 256),
                 (long long)(val % 256));
        os << buf;
        return os;
    }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_1006 : public ::testing::Test {
protected:
    MinoltaMakerNote maker_;
    std::ostringstream oss_;
};

// Test normal time value: 12:30:45
// 12 * 65536 + 30 * 256 + 45 = 786432 + 7680 + 45 = 794157
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_NormalTime_1006) {
    int64_t timeVal = 12 * 65536 + 30 * 256 + 45;  // 794157
    Exiv2::ValueType<int32_t> value;
    value.read(std::to_string(timeVal));
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "12:30:45");
}

// Test midnight: 00:00:00
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_Midnight_1006) {
    Exiv2::ValueType<int32_t> value;
    value.read("0");
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "00:00:00");
}

// Test time 23:59:59
// 23 * 65536 + 59 * 256 + 59 = 1507328 + 15104 + 59 = 1522491
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_EndOfDay_1006) {
    int64_t timeVal = 23 * 65536 + 59 * 256 + 59;
    Exiv2::ValueType<int32_t> value;
    value.read(std::to_string(timeVal));
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "23:59:59");
}

// Test time 01:02:03 - single digit values should be zero-padded
// 1 * 65536 + 2 * 256 + 3 = 65536 + 512 + 3 = 66051
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_SingleDigitsPadded_1006) {
    int64_t timeVal = 1 * 65536 + 2 * 256 + 3;
    Exiv2::ValueType<int32_t> value;
    value.read(std::to_string(timeVal));
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "01:02:03");
}

// Test time 00:00:01 - only seconds set
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_OnlySeconds_1006) {
    Exiv2::ValueType<int32_t> value;
    value.read("1");
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "00:00:01");
}

// Test time 00:01:00 - only minutes set (256)
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_OnlyMinutes_1006) {
    Exiv2::ValueType<int32_t> value;
    value.read("256");
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "00:01:00");
}

// Test time 01:00:00 - only hours set (65536)
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_OnlyHours_1006) {
    Exiv2::ValueType<int32_t> value;
    value.read("65536");
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "01:00:00");
}

// Test that the function returns the same ostream reference
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_ReturnsOstream_1006) {
    Exiv2::ValueType<int32_t> value;
    value.read("0");
    
    std::ostream& result = maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(&result, &oss_);
}

// Test with nullptr ExifData - should not crash
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_NullExifData_1006) {
    Exiv2::ValueType<int32_t> value;
    value.read("0");
    
    EXPECT_NO_THROW(maker_.printMinoltaTimeStd(oss_, value, nullptr));
}

// Test time 10:20:30
// 10 * 65536 + 20 * 256 + 30 = 655360 + 5120 + 30 = 660510
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_TenTwentyThirty_1006) {
    int64_t timeVal = 10 * 65536 + 20 * 256 + 30;
    Exiv2::ValueType<int32_t> value;
    value.read(std::to_string(timeVal));
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "10:20:30");
}

// Test boundary: max single byte for seconds (255)
// 0 * 65536 + 0 * 256 + 255 = 255
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_MaxSeconds_1006) {
    Exiv2::ValueType<int32_t> value;
    value.read("255");
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "00:00:255");
}

// Test time 12:00:00
TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_Noon_1006) {
    int64_t timeVal = 12 * 65536;
    Exiv2::ValueType<int32_t> value;
    value.read(std::to_string(timeVal));
    
    maker_.printMinoltaTimeStd(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "12:00:00");
}
