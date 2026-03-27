#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Mock the external dependencies if needed.
namespace Exiv2 {
namespace Internal {

// Mock for the Value class
class Value {
public:
    MOCK_METHOD(size_t, size, (), (const));
    MOCK_METHOD(uint32_t, toUint32, (size_t index), (const));
};

// Mock for ExifData (currently not used in the provided code)
class ExifData {};

class Nikon3MakerNote {
public:
    std::ostream& print0x0088(std::ostream& os, const Value& value, const ExifData*) {
        if (value.size() != 4) {
            os << "(" << value << ")";
        } else {
            const uint32_t focusmetering = value.toUint32(0);
            const uint32_t focuspoint = value.toUint32(1);
            const uint32_t focusused = (value.toUint32(2) << 8) + value.toUint32(3);

            if (focusmetering == 0 && focuspoint == 0 && focusused == 0) {
                os << _("n/a");
                return os;
            }

            switch (focusmetering) {
                case 0x00: os << _("Single area"); break;
                case 0x01: os << _("Dynamic area"); break;
                case 0x02: os << _("Closest subject"); break;
                case 0x03: os << _("Group dynamic-AF"); break;
                case 0x04: os << _("Single area (wide)"); break;
                case 0x05: os << _("Dynamic area (wide)"); break;
                default: os << "(" << focusmetering << ")"; break;
            }

            char sep = ';';
            if (focusmetering != 0x02) {
                os << sep << ' ';
                if (focuspoint < nikonFocuspoints.size()) {
                    os << nikonFocuspoints[focuspoint];
                } else os << "(" << focuspoint << ")";
                sep = ',';
            }

            if (focusused == 0) os << sep << " " << _("none");
            else if (focusused != 1U << focuspoint) {
                os << sep;
                for (size_t fpid = 0; fpid < nikonFocuspoints.size(); fpid++)
                    if (focusused & 1 << fpid)
                        os << ' ' << nikonFocuspoints[fpid];
            }

            os << " " << _("used");
        }
        return os;
    }
};

} // namespace Internal
} // namespace Exiv2

// Test case for Nikon3MakerNote
TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalCase_467) {
    Exiv2::Internal::Nikon3MakerNote makerNote;
    Exiv2::Internal::Value value;

    // Mock the behavior of the 'value' object for a normal case
    EXPECT_CALL(value, size()).WillOnce(testing::Return(4));
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(0x01));  // Dynamic area
    EXPECT_CALL(value, toUint32(1)).WillOnce(testing::Return(1));  // Focus point
    EXPECT_CALL(value, toUint32(2)).WillOnce(testing::Return(0x02));  // Focus used
    EXPECT_CALL(value, toUint32(3)).WillOnce(testing::Return(0x03));  // Focus used

    std::ostringstream os;
    makerNote.print0x0088(os, value, nullptr);
    EXPECT_EQ(os.str(), "Dynamic area; 1, used");
}

TEST_F(Nikon3MakerNoteTest_468, Print0x0088_NoFocusUsed_468) {
    Exiv2::Internal::Nikon3MakerNote makerNote;
    Exiv2::Internal::Value value;

    // Mock the behavior of the 'value' object for the "no focus used" case
    EXPECT_CALL(value, size()).WillOnce(testing::Return(4));
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(0x01));  // Dynamic area
    EXPECT_CALL(value, toUint32(1)).WillOnce(testing::Return(2));  // Focus point
    EXPECT_CALL(value, toUint32(2)).WillOnce(testing::Return(0x00));  // Focus used is 0
    EXPECT_CALL(value, toUint32(3)).WillOnce(testing::Return(0x00));  // Focus used is 0

    std::ostringstream os;
    makerNote.print0x0088(os, value, nullptr);
    EXPECT_EQ(os.str(), "Dynamic area; 2, none");
}

TEST_F(Nikon3MakerNoteTest_469, Print0x0088_UnknownFocusMetering_469) {
    Exiv2::Internal::Nikon3MakerNote makerNote;
    Exiv2::Internal::Value value;

    // Mock the behavior of the 'value' object for an unknown focus metering case
    EXPECT_CALL(value, size()).WillOnce(testing::Return(4));
    EXPECT_CALL(value, toUint32(0)).WillOnce(testing::Return(0xFF));  // Unknown focus metering
    EXPECT_CALL(value, toUint32(1)).WillOnce(testing::Return(2));  // Focus point
    EXPECT_CALL(value, toUint32(2)).WillOnce(testing::Return(0x00));  // Focus used
    EXPECT_CALL(value, toUint32(3)).WillOnce(testing::Return(0x00));  // Focus used

    std::ostringstream os;
    makerNote.print0x0088(os, value, nullptr);
    EXPECT_EQ(os.str(), "(255); 2, none");
}

TEST_F(Nikon3MakerNoteTest_470, Print0x0088_SizeNot4_470) {
    Exiv2::Internal::Nikon3MakerNote makerNote;
    Exiv2::Internal::Value value;

    // Mock the behavior of the 'value' object for a size that's not 4
    EXPECT_CALL(value, size()).WillOnce(testing::Return(3));  // Invalid size
    std::ostringstream os;
    makerNote.print0x0088(os, value, nullptr);
    EXPECT_EQ(os.str(), "(<mock value>)");
}