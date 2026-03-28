#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>

// Minimal stubs to satisfy the interface used in the code under test

namespace Exiv2 {

enum TypeId {
    undefined = 7,
    unsignedByte = 1,
    asciiString = 2,
    unsignedShort = 3,
    unsignedLong = 4,
    signedLong = 9,
};

class ExifData {};

class Value {
public:
    virtual ~Value() = default;
    virtual size_t size() const = 0;
    virtual TypeId typeId() const = 0;
    virtual float toFloat(size_t n = 0) const = 0;
    virtual int64_t toInt64(size_t n = 0) const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        // Simple representation for testing
        os << v.printValue();
        return os;
    }
    
    virtual std::string printValue() const = 0;
};

class MockValue : public Value {
public:
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(TypeId, typeId, (), (const, override));
    MOCK_METHOD(float, toFloat, (size_t n), (const, override));
    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));
    MOCK_METHOD(std::string, printValue, (), (const, override));
};

namespace Internal {

class Nikon3MakerNote {
public:
    std::ostream& print0x008b(std::ostream& os, const Value& value, const ExifData*) {
        if (value.size() != 4 || value.typeId() != undefined)
            return os << "(" << value << ")";
        float a = value.toFloat(0);
        const auto b = value.toInt64(1);
        const auto c = value.toInt64(2);
        if (c == 0)
            return os << "(" << value << ")";
        return os << a * b / c;
    }
};

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::Return;

class Nikon3MakerNoteTest_470 : public ::testing::Test {
protected:
    Nikon3MakerNote maker;
    std::ostringstream oss;
};

// Test normal operation: size=4, typeId=undefined, c != 0
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_NormalOperation_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(2.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(6));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(3));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "4");
}

// Test normal operation with different values
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_NormalOperationDifferentValues_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(10.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(5));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(2));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "25");
}

// Test boundary: size != 4 (too small)
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_SizeTooSmall_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(3));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, printValue()).WillRepeatedly(Return("1 2 3"));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "(1 2 3)");
}

// Test boundary: size != 4 (too large)
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_SizeTooLarge_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(5));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, printValue()).WillRepeatedly(Return("1 2 3 4 5"));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "(1 2 3 4 5)");
}

// Test boundary: size == 0
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_SizeZero_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, printValue()).WillRepeatedly(Return(""));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "()");
}

// Test: typeId is not undefined
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_WrongTypeId_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(unsignedByte));
    EXPECT_CALL(mockVal, printValue()).WillRepeatedly(Return("1 2 3 4"));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "(1 2 3 4)");
}

// Test: c == 0 (division by zero case)
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_DivisionByZero_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(5.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(10));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(0));
    EXPECT_CALL(mockVal, printValue()).WillRepeatedly(Return("5 10 0 1"));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "(5 10 0 1)");
}

// Test: both size wrong and typeId wrong
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_BothSizeAndTypeWrong_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(2));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(unsignedShort));
    EXPECT_CALL(mockVal, printValue()).WillRepeatedly(Return("1 2"));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "(1 2)");
}

// Test: a=0, b=something, c=something (result should be 0)
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_AIsZero_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(0.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(10));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(5));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test: b=0 (result should be 0)
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_BIsZero_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(3.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(0));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(5));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test: negative values
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_NegativeValues_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(-2.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(6));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(3));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "-4");
}

// Test: fractional result
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_FractionalResult_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(1.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(1));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(3));

    maker.print0x008b(oss, mockVal, nullptr);
    // 1.0 * 1 / 3 = 0.333...
    std::string result = oss.str();
    float resultVal = std::stof(result);
    EXPECT_NEAR(resultVal, 1.0f / 3.0f, 0.001f);
}

// Test: ExifData pointer is non-null (should not affect behavior)
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_NonNullExifData_470) {
    MockValue mockVal;
    ExifData exifData;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(2.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(6));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(3));

    maker.print0x008b(oss, mockVal, &exifData);
    EXPECT_EQ(oss.str(), "4");
}

// Test: large values
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_LargeValues_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(1000.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(1000));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(1));

    maker.print0x008b(oss, mockVal, nullptr);
    // 1000.0 * 1000 / 1 = 1000000
    std::string result = oss.str();
    float resultVal = std::stof(result);
    EXPECT_NEAR(resultVal, 1000000.0f, 1.0f);
}

// Test: c is negative
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_NegativeDivisor_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(4.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(3));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(-2));

    maker.print0x008b(oss, mockVal, nullptr);
    // 4.0 * 3 / -2 = -6
    std::string result = oss.str();
    float resultVal = std::stof(result);
    EXPECT_NEAR(resultVal, -6.0f, 0.001f);
}

// Test: size == 1
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_SizeOne_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, printValue()).WillRepeatedly(Return("42"));

    maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(oss.str(), "(42)");
}

// Test: returns the same ostream reference
TEST_F(Nikon3MakerNoteTest_470, Print0x008b_ReturnsSameStream_470) {
    MockValue mockVal;
    EXPECT_CALL(mockVal, size()).WillRepeatedly(Return(4));
    EXPECT_CALL(mockVal, typeId()).WillRepeatedly(Return(undefined));
    EXPECT_CALL(mockVal, toFloat(0)).WillRepeatedly(Return(2.0f));
    EXPECT_CALL(mockVal, toInt64(1)).WillRepeatedly(Return(6));
    EXPECT_CALL(mockVal, toInt64(2)).WillRepeatedly(Return(3));

    std::ostream& result = maker.print0x008b(oss, mockVal, nullptr);
    EXPECT_EQ(&result, &oss);
}
