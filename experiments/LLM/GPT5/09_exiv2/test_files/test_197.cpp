#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Assuming that the `Value` class has a method `toInt64()` that returns an int64_t.

namespace Exiv2 { namespace Internal {

    class Value {
    public:
        explicit Value(int64_t val) : val_(val) {}
        int64_t toInt64() const { return val_; }
    private:
        int64_t val_;
    };

    class PentaxMakerNote {
    public:
        std::ostream& printTemperature(std::ostream& os, const Value& value, const ExifData*) {
            return os << stringFormat("{} C", value.toInt64());
        }
    };
}}

using namespace Exiv2::Internal;

// Helper function for formatting.
std::string stringFormat(const char* fmt, int64_t val) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), fmt, val);
    return std::string(buffer);
}

// Unit Test for printTemperature
class PentaxMakerNoteTest_197 : public ::testing::Test {
protected:
    PentaxMakerNote pentaxMakerNote;
};

TEST_F(PentaxMakerNoteTest_197, NormalTemperature_197) {
    Value value(25);  // temperature in Celsius
    std::ostringstream os;
    pentaxMakerNote.printTemperature(os, value, nullptr);
    EXPECT_EQ(os.str(), "25 C");
}

TEST_F(PentaxMakerNoteTest_197, NegativeTemperature_197) {
    Value value(-10);  // negative temperature in Celsius
    std::ostringstream os;
    pentaxMakerNote.printTemperature(os, value, nullptr);
    EXPECT_EQ(os.str(), "-10 C");
}

TEST_F(PentaxMakerNoteTest_197, ZeroTemperature_197) {
    Value value(0);  // zero temperature in Celsius
    std::ostringstream os;
    pentaxMakerNote.printTemperature(os, value, nullptr);
    EXPECT_EQ(os.str(), "0 C");
}

TEST_F(PentaxMakerNoteTest_197, LargeTemperature_197) {
    Value value(1000000);  // very large temperature
    std::ostringstream os;
    pentaxMakerNote.printTemperature(os, value, nullptr);
    EXPECT_EQ(os.str(), "1000000 C");
}

TEST_F(PentaxMakerNoteTest_197, SmallTemperature_197) {
    Value value(-1000000);  // very small temperature
    std::ostringstream os;
    pentaxMakerNote.printTemperature(os, value, nullptr);
    EXPECT_EQ(os.str(), "-1000000 C");
}