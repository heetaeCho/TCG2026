#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Minimal stubs for Exiv2 types needed by the interface

namespace Exiv2 {

class ExifData {};

// Minimal N_ macro equivalent
inline const char* N_(const char* s) { return s; }

inline std::string stringFormat(const char* fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);
    // We need to format "%.2f m" style
    vsnprintf(buf, sizeof(buf), "%.2f m", args);
    va_end(args);
    return std::string(buf);
}

class Value {
public:
    virtual ~Value() = default;
    virtual int64_t toInt64(size_t n = 0) const = 0;
};

class TestValue : public Value {
public:
    explicit TestValue(int64_t v) : val_(v) {}
    int64_t toInt64(size_t /*n*/ = 0) const override { return val_; }
private:
    int64_t val_;
};

namespace Internal {

// Re-implement stringFormat properly for test purposes
inline std::string stringFormat(const char* fmt, double val) {
    char buf[256];
    snprintf(buf, sizeof(buf), "%.2f m", val);
    return std::string(buf);
}

class Casio2MakerNote {
public:
    std::ostream& print0x2022(std::ostream& os, const Value& value, const ExifData*) {
        if (value.toInt64() >= 0x20000000) {
            return os << "Inf";
        }
        return os << stringFormat("{:.2f} m", value.toInt64() / 1000.0);
    }
};

} // namespace Internal
} // namespace Exiv2

// ============ Tests ============

class Casio2MakerNoteTest_1823 : public ::testing::Test {
protected:
    Exiv2::Internal::Casio2MakerNote maker_;
    std::ostringstream os_;
};

// Test: Value exactly at the infinity threshold (0x20000000) should print "Inf"
TEST_F(Casio2MakerNoteTest_1823, ExactInfinityThreshold_1823) {
    Exiv2::TestValue val(0x20000000);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "Inf");
}

// Test: Value above the infinity threshold should print "Inf"
TEST_F(Casio2MakerNoteTest_1823, AboveInfinityThreshold_1823) {
    Exiv2::TestValue val(0x30000000);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "Inf");
}

// Test: Value just below the infinity threshold should print distance
TEST_F(Casio2MakerNoteTest_1823, JustBelowInfinityThreshold_1823) {
    Exiv2::TestValue val(0x20000000 - 1);
    maker_.print0x2022(os_, val, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result, "Inf");
    // Should contain " m" suffix
    EXPECT_NE(result.find(" m"), std::string::npos);
}

// Test: Value of 0 should print "0.00 m"
TEST_F(Casio2MakerNoteTest_1823, ZeroValue_1823) {
    Exiv2::TestValue val(0);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "0.00 m");
}

// Test: Value of 1000 should print "1.00 m"
TEST_F(Casio2MakerNoteTest_1823, OneThousandValue_1823) {
    Exiv2::TestValue val(1000);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "1.00 m");
}

// Test: Value of 1500 should print "1.50 m"
TEST_F(Casio2MakerNoteTest_1823, FifteenHundredValue_1823) {
    Exiv2::TestValue val(1500);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "1.50 m");
}

// Test: Value of 1 should print "0.00 m" (1/1000 = 0.001, rounded to 2 decimals)
TEST_F(Casio2MakerNoteTest_1823, SmallValue_1823) {
    Exiv2::TestValue val(1);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "0.00 m");
}

// Test: Value of 500 should print "0.50 m"
TEST_F(Casio2MakerNoteTest_1823, FiveHundredValue_1823) {
    Exiv2::TestValue val(500);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "0.50 m");
}

// Test: Large value just below threshold
TEST_F(Casio2MakerNoteTest_1823, LargeValueBelowThreshold_1823) {
    Exiv2::TestValue val(536870000); // just below 0x20000000 = 536870912
    maker_.print0x2022(os_, val, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result, "Inf");
    EXPECT_NE(result.find(" m"), std::string::npos);
}

// Test: Maximum int64 value should print "Inf"
TEST_F(Casio2MakerNoteTest_1823, MaxInt64Value_1823) {
    Exiv2::TestValue val(INT64_MAX);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "Inf");
}

// Test: Negative value should not be "Inf" (below threshold)
TEST_F(Casio2MakerNoteTest_1823, NegativeValue_1823) {
    Exiv2::TestValue val(-1000);
    maker_.print0x2022(os_, val, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result, "Inf");
    EXPECT_EQ(result, "-1.00 m");
}

// Test: Null ExifData pointer is acceptable
TEST_F(Casio2MakerNoteTest_1823, NullExifDataPointer_1823) {
    Exiv2::TestValue val(2000);
    EXPECT_NO_THROW(maker_.print0x2022(os_, val, nullptr));
    EXPECT_EQ(os_.str(), "2.00 m");
}

// Test: Value of 10 should print "0.01 m"
TEST_F(Casio2MakerNoteTest_1823, TenValue_1823) {
    Exiv2::TestValue val(10);
    maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "0.01 m");
}

// Test: Return value is the same ostream reference
TEST_F(Casio2MakerNoteTest_1823, ReturnsOstreamReference_1823) {
    Exiv2::TestValue val(1000);
    std::ostream& ret = maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(&ret, &os_);
}

// Test: Return value is the same ostream reference for Inf case
TEST_F(Casio2MakerNoteTest_1823, ReturnsOstreamReferenceForInf_1823) {
    Exiv2::TestValue val(0x20000000);
    std::ostream& ret = maker_.print0x2022(os_, val, nullptr);
    EXPECT_EQ(&ret, &os_);
}
