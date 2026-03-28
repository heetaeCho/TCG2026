#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>

// Mocking the ExifData type since it's used in the function signature
namespace Exiv2 {
    class ExifData {};
    class Value {
    public:
        MOCK_METHOD(uint32_t, toUint32, (size_t index), (const));
        MOCK_METHOD(size_t, count, (), (const));
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
                        os << "No extended bracketing";
                    } else {
                        auto type = l1 >> 8;
                        auto range = static_cast<uint8_t>(l1);
                        switch (type) {
                            case 1: os << "WB-BA"; break;
                            case 2: os << "WB-GM"; break;
                            case 3: os << "Saturation"; break;
                            case 4: os << "Sharpness"; break;
                            case 5: os << "Contrast"; break;
                            default: os << "Unknown " << type; break;
                        }
                        os << " " << +range;
                    }
                    os << ")";
                }
                os.flags(f);
                return os;
            }
        };
    }
}

// Test Fixtures and Test cases
using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMakerNoteTest_199 : public ::testing::Test {
protected:
    PentaxMakerNote pentaxMakerNote;
    Value value;
    ExifData exifData;
    std::ostringstream os;
};

// Test case 1: Normal operation for values less than 10
TEST_F(PentaxMakerNoteTest_199, PrintBracketingLessThan10_199) {
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(5));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));

    pentaxMakerNote.printBracketing(os, value, &exifData);

    EXPECT_EQ(os.str(), "1.67 EV");
}

// Test case 2: Normal operation for values greater than or equal to 10
TEST_F(PentaxMakerNoteTest_199, PrintBracketingGreaterThanOrEqualTo10_199) {
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(15));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));

    pentaxMakerNote.printBracketing(os, value, &exifData);

    EXPECT_EQ(os.str(), "5.50 EV");
}

// Test case 3: Two values with no extended bracketing
TEST_F(PentaxMakerNoteTest_199, PrintBracketingWithNoExtended_199) {
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(12));
    EXPECT_CALL(value, toUint32(1)).WillOnce(testing::Return(0));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));

    pentaxMakerNote.printBracketing(os, value, &exifData);

    EXPECT_EQ(os.str(), "4.50 EV (No extended bracketing)");
}

// Test case 4: Two values with extended bracketing type 1 (WB-BA)
TEST_F(PentaxMakerNoteTest_199, PrintBracketingWithExtendedWBBA_199) {
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(12));
    EXPECT_CALL(value, toUint32(1)).WillOnce(testing::Return(0x0101)); // WB-BA with range 1
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));

    pentaxMakerNote.printBracketing(os, value, &exifData);

    EXPECT_EQ(os.str(), "4.50 EV (WB-BA 1)");
}

// Test case 5: Two values with extended bracketing with unknown type
TEST_F(PentaxMakerNoteTest_199, PrintBracketingWithExtendedUnknownType_199) {
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(12));
    EXPECT_CALL(value, toUint32(1)).WillOnce(testing::Return(0x0703)); // Unknown type 7 with range 3
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));

    pentaxMakerNote.printBracketing(os, value, &exifData);

    EXPECT_EQ(os.str(), "4.50 EV (Unknown 7 3)");
}

// Test case 6: Test edge case with count not equal to 2
TEST_F(PentaxMakerNoteTest_199, PrintBracketingWithSingleValue_199) {
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(12));
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));

    pentaxMakerNote.printBracketing(os, value, &exifData);

    EXPECT_EQ(os.str(), "4.50 EV");
}