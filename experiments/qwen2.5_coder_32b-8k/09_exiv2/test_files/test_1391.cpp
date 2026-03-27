#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/tags_int.cpp"



namespace Exiv2 {

    class MockValue : public Value {

    public:

        using Value::Value;

        MOCK_METHOD(std::ostream&, write, (std::ostream& os), (const override));

    };

}



class Print0x001eTest_1391 : public ::testing::Test {

protected:

    Exiv2::MockValue mockValue;

    const Exiv2::ExifData* metadata = nullptr;



    Print0x001eTest_1391() : mockValue(Exiv2::undefined) {}

};



TEST_F(Print0x001eTest_1391, NormalOperation_WithoutCorrection_1391) {

    Exiv2::Internal::exifGPSDifferential[0].value_ = 0;

    EXPECT_CALL(mockValue, write(::testing::_))

        .WillOnce([](std::ostream& os) -> std::ostream& { return os << "Without correction"; });



    std::ostringstream oss;

    Exiv2::Internal::print0x001e(oss, mockValue, metadata);

    EXPECT_EQ(oss.str(), "Without correction");

}



TEST_F(Print0x001eTest_1391, NormalOperation_CorrectionApplied_1391) {

    Exiv2::Internal::exifGPSDifferential[0].value_ = 1;

    EXPECT_CALL(mockValue, write(::testing::_))

        .WillOnce([](std::ostream& os) -> std::ostream& { return os << "Correction applied"; });



    std::ostringstream oss;

    Exiv2::Internal::print0x001e(oss, mockValue, metadata);

    EXPECT_EQ(oss.str(), "Correction applied");

}



TEST_F(Print0x001eTest_1391, BoundaryCondition_ValueOutOfRange_1391) {

    Exiv2::Internal::exifGPSDifferential[0].value_ = 2;

    EXPECT_CALL(mockValue, write(::testing::_))

        .WillOnce([](std::ostream& os) -> std::ostream& { return os; });



    std::ostringstream oss;

    Exiv2::Internal::print0x001e(oss, mockValue, metadata);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(Print0x001eTest_1391, MetadataNullptr_1391) {

    metadata = nullptr;

    EXPECT_CALL(mockValue, write(::testing::_))

        .WillOnce([](std::ostream& os) -> std::ostream& { return os << "Without correction"; });



    std::ostringstream oss;

    Exiv2::Internal::print0x001e(oss, mockValue, metadata);

    EXPECT_EQ(oss.str(), "Without correction");

}
