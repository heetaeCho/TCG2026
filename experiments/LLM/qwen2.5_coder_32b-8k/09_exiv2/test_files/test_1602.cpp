#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <string>



namespace Exiv2 {

    namespace Internal {

        class SonyMakerNote {

        public:

            std::ostream& printPixelShiftInfo(std::ostream& os, const Value& value, const ExifData*) {

                if (value.count() != 6 || value.typeId() != undefined) return os << "(" << value << ")";

                if (value.toString() == "0 0 0 0 0 0") return os << _("n/a");

                auto groupID = (value.toUint32(3) << 24) + (value.toUint32(2) << 16) + (value.toUint32(1) << 8) + value.toUint32(0);

                return os << stringFormat("Group {:02}{:02}{:02}{:02}, Shot {}/{} (0x{:x})", (groupID >> 17) & 0x1f, (groupID >> 12) & 0x1f, (groupID >> 6) & 0x3f, groupID & 0x3f, value.toUint32(4), value.toUint32(5), (groupID >> 22));

            }

        };

    }

}



using namespace Exiv2::Internal;



class MockValue : public Value {

public:

    MOCK_CONST_METHOD0(count, size_t());

    MOCK_CONST_METHOD0(typeId, TypeId());

    MOCK_CONST_METHOD1(toUint32, uint32_t(size_t) const);

    MOCK_CONST_METHOD0(toString, std::string() const);

};



class SonyMakerNoteTest : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    MockValue mockValue;

};



TEST_F(SonyMakerNoteTest_1602, InvalidCount_ReturnsFormattedString_1602) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(5));

    std::ostringstream os;

    sonyMakerNote.printPixelShiftInfo(os, mockValue, nullptr);

    EXPECT_EQ("(MockValue)", os.str());

}



TEST_F(SonyMakerNoteTest_1602, InvalidTypeId_ReturnsFormattedString_1602) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(6));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(static_cast<TypeId>(1)));

    std::ostringstream os;

    sonyMakerNote.printPixelShiftInfo(os, mockValue, nullptr);

    EXPECT_EQ("(MockValue)", os.str());

}



TEST_F(SonyMakerNoteTest_1602, AllZeros_ReturnsNADescription_1602) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(6));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(undefined));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("0 0 0 0 0 0"));

    std::ostringstream os;

    sonyMakerNote.printPixelShiftInfo(os, mockValue, nullptr);

    EXPECT_EQ("n/a", os.str());

}



TEST_F(SonyMakerNoteTest_1602, ValidData_ReturnsFormattedString_1602) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(6));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(undefined));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("1 2 3 4 5 6"));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(::testing::Return(3));

    EXPECT_CALL(mockValue, toUint32(3)).WillOnce(::testing::Return(4));

    EXPECT_CALL(mockValue, toUint32(4)).WillOnce(::testing::Return(5));

    EXPECT_CALL(mockValue, toUint32(5)).WillOnce(::testing::Return(6));



    std::ostringstream os;

    sonyMakerNote.printPixelShiftInfo(os, mockValue, nullptr);

    EXPECT_EQ("Group 01000004, Shot 5/6 (0x1)", os.str());

}
