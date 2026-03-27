#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Mocking necessary dependencies
namespace Exiv2 {
    namespace Internal {
        class Value {
        public:
            virtual ~Value() = default;
            virtual int count() const = 0;
            virtual int typeId() const = 0;
            virtual int64_t toInt64(int index) const = 0;
        };

        // The class to be tested
        class OlympusMakerNote {
        public:
            std::ostream& print0x0200(std::ostream& os, const Value& value, const ExifData*) {
                if (value.count() != 3 || value.typeId() != unsignedLong) {
                    return os << value;
                }
                const auto l0 = value.toInt64(0);
                switch (l0) {
                    case 0: os << _("Normal"); break;
                    case 2: os << _("Fast"); break;
                    case 3: os << _("Panorama"); break;
                    default: os << "(" << l0 << ")"; break;
                }
                if (l0 != 0) {
                    os << ", ";
                    const auto l1 = value.toInt64(1);
                    os << _("Sequence number") << " " << l1;
                }
                if (l0 != 0 && l0 != 2) {
                    os << ", ";
                    const auto l2 = value.toInt64(2);
                    switch (l2) {
                        case 1: os << _("Left to right"); break;
                        case 2: os << _("Right to left"); break;
                        case 3: os << _("Bottom to top"); break;
                        case 4: os << _("Top to bottom"); break;
                        default: os << "(" << l2 << ")"; break;
                    }
                }
                return os;
            }
        };
    }
}

// Mock the Value class for testing
class MockValue : public Exiv2::Internal::Value {
public:
    MOCK_METHOD(int, count, (), (const, override));
    MOCK_METHOD(int, typeId, (), (const, override));
    MOCK_METHOD(int64_t, toInt64, (int), (const, override));
};

// Test Fixture for OlympusMakerNote
class OlympusMakerNoteTest : public ::testing::Test {
protected:
    Exiv2::Internal::OlympusMakerNote makerNote;
};

// Test Case 1: Normal operation (value.count() == 3 and value.typeId() == unsignedLong)
TEST_F(OlympusMakerNoteTest, Print0x0200_Normal_Operation_897) {
    MockValue mockValue;
    std::ostringstream os;
    
    // Mock count() and typeId() to match expected behavior for normal operation
    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(3));
    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(1)); // unsignedLong mock

    // Mock toInt64 for valid data
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(2));  // "Fast"
    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(::testing::Return(5));  // Sequence number 5
    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(::testing::Return(3));  // "Bottom to top"

    makerNote.print0x0200(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "Fast, Sequence number 5, Bottom to top");
}

// Test Case 2: Boundary condition (value.count() != 3)
TEST_F(OlympusMakerNoteTest, Print0x0200_Boundary_Count_Not_3_897) {
    MockValue mockValue;
    std::ostringstream os;

    // Mock count() to return something other than 3
    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(2)); // Invalid count
    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(1));

    // Should output value as is
    EXPECT_CALL(mockValue, toInt64(::testing::_)).Times(0);  // No further calls to toInt64

    makerNote.print0x0200(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), ""); // Should output nothing as count() is invalid
}

// Test Case 3: Boundary condition (value.typeId() != unsignedLong)
TEST_F(OlympusMakerNoteTest, Print0x0200_Boundary_TypeId_Not_UnsignedLong_897) {
    MockValue mockValue;
    std::ostringstream os;

    // Mock count() and typeId() to return values that should trigger default behavior
    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(3));
    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(2));  // Non-unsignedLong typeId

    // Should output value as is
    EXPECT_CALL(mockValue, toInt64(::testing::_)).Times(0);  // No further calls to toInt64

    makerNote.print0x0200(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), ""); // Should output nothing due to invalid typeId
}

// Test Case 4: Exceptional case (invalid data - unknown l0 value)
TEST_F(OlympusMakerNoteTest, Print0x0200_Exceptional_Unknown_L0_897) {
    MockValue mockValue;
    std::ostringstream os;

    // Mock count() and typeId() to match expected behavior
    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(3));
    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(1)); // unsignedLong mock

    // Mock toInt64 to return an unknown value for l0
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(999));  // Invalid l0 value
    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(::testing::Return(10));   // Sequence number 10
    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(::testing::Return(2));    // "Right to left"

    makerNote.print0x0200(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "(999), Sequence number 10, Right to left");
}