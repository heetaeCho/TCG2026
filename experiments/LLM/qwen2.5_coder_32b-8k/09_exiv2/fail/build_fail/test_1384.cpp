#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



// Mocking Value for any interactions if necessary

class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte*, size_t, ByteOrder), (override));

    MOCK_METHOD(int, setDataArea, (const byte*, size_t), (override));

    MOCK_METHOD(size_t, copy, (byte*, ByteOrder), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(const std::ostream&, write, (std::ostream&), (const, override));

    MOCK_METHOD(std::string, toString, (), (const, override));

    MOCK_METHOD(int64_t, toInt64, (size_t), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t), (const, override));

    MOCK_METHOD(float, toFloat, (size_t), (const, override));

    MOCK_METHOD(Rational, toRational, (size_t), (const, override));

    MOCK_METHOD(size_t, sizeDataArea, (), (const, override));

    MOCK_METHOD(DataBuf, dataArea, (), (const, override));



    MockValue(TypeId typeId) : Value(typeId) {}

};



TEST(print0x0005Test_1384, NormalOperation_AboveSeaLevel_1384) {

    ExifData metadata;

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("0"));



    std::ostringstream os;

    Internal::print0x0005(os, mockValue, &metadata);



    EXPECT_EQ(os.str(), "Above sea level");

}



TEST(print0x0005Test_1384, NormalOperation_BelowSeaLevel_1384) {

    ExifData metadata;

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("1"));



    std::ostringstream os;

    Internal::print0x0005(os, mockValue, &metadata);



    EXPECT_EQ(os.str(), "Below sea level");

}



TEST(print0x0005Test_1384, BoundaryCondition_OutOfRange_1384) {

    ExifData metadata;

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("2"));



    std::ostringstream os;

    Internal::print0x0005(os, mockValue, &metadata);



    EXPECT_EQ(os.str(), "");

}



TEST(print0x0005Test_1384, BoundaryCondition_EmptyString_1384) {

    ExifData metadata;

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return(""));



    std::ostringstream os;

    Internal::print0x0005(os, mockValue, &metadata);



    EXPECT_EQ(os.str(), "");

}



TEST(print0x0005Test_1384, ExceptionalCase_NegativeValue_1384) {

    ExifData metadata;

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("-1"));



    std::ostringstream os;

    Internal::print0x0005(os, mockValue, &metadata);



    EXPECT_EQ(os.str(), "");

}



TEST(print0x0005Test_1384, ExceptionalCase_NonNumericString_1384) {

    ExifData metadata;

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("abc"));



    std::ostringstream os;

    Internal::print0x0005(os, mockValue, &metadata);



    EXPECT_EQ(os.str(), "");

}



TEST(print0x0005Test_1384, MetadataNullptrHandling_1384) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("0"));



    std::ostringstream os;

    Internal::print0x0005(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "Above sea level");

}
