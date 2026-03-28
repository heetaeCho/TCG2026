#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    namespace Internal {

        std::ostream& print0x9208(std::ostream& os, const Value& value, const ExifData* metadata);

    }

}



using ::testing::_;

using ::testing::Return;

using ::testing::StrEq;



class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, read, (const std::string & buf), (override));

    MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

    MOCK_METHOD(const size_t, copy, (byte* buf, ByteOrder byteOrder), (override));

    MOCK_METHOD(const size_t, count, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const std::ostream &, write, (std::ostream & os), (const override));

    MOCK_METHOD(const std::string, toString, (), (const override));

    MOCK_METHOD(const std::string, toString, (size_t n), (const override));

    MOCK_METHOD(const int64_t, toInt64, (size_t n), (const override));

    MOCK_METHOD(const uint32_t, toUint32, (size_t n), (const override));

    MOCK_METHOD(const float, toFloat, (size_t n), (const override));

    MOCK_METHOD(const Rational, toRational, (size_t n), (const override));

    MOCK_METHOD(const size_t, sizeDataArea, (), (const override));

    MOCK_METHOD(const DataBuf, dataArea, (), (const override));



    MockValue(TypeId typeId) : Value(typeId) {}

};



class Exiv2InternalPrint0x9208Test : public ::testing::Test {

protected:

    std::ostringstream oss;

    MockValue mockValue;

    ExifData exifData;



    Exiv2InternalPrint0x9208Test() : mockValue(0) {}



    void SetUp() override {

        // Initialize any necessary setup here

    }

};



TEST_F(Exiv2InternalPrint0x9208Test, PrintKnownLightSource_1405) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(1));

    Exiv2::Internal::print0x9208(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "Daylight");

}



TEST_F(Exiv2InternalPrint0x9208Test, PrintUnknownLightSource_1405) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(999));

    Exiv2::Internal::print0x9208(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "Unknown");

}



TEST_F(Exiv2InternalPrint0x9208Test, PrintOtherLightSource_1405) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(255));

    Exiv2::Internal::print0x9208(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "Other light source");

}



TEST_F(Exiv2InternalPrint0x9208Test, PrintBoundaryLightSource_1405) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(0));

    Exiv2::Internal::print0x9208(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "Unknown");



    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(255));

    Exiv2::Internal::print0x9208(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "Other light source");

}
