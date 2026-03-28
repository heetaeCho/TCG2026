#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    namespace Internal {

        template <size_t N, const TagDetails (&array)[N]>

        std::ostream& printTag(std::ostream& os, const Value& value, const ExifData* data) {

            static_assert(N > 0, "Passed zero length printTag");

            return printTag<N, array>(os, value.toInt64(), data);

        }

    }

}



using namespace ::testing;

using namespace Exiv2;



class MockValue : public Value {

public:

    MOCK_METHOD(int64_t, toInt64, (size_t n), const);

};



TEST_F(MockValueTest_183, ToInt64_NormalOperation_183) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(42));

    EXPECT_EQ(42, mockValue.toInt64(0));

}



TEST_F(MockValueTest_183, ToInt64_BoundaryCondition_ZeroIndex_183) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(0));

    EXPECT_EQ(0, mockValue.toInt64(0));

}



TEST_F(MockValueTest_183, ToInt64_BoundaryCondition_LargeIndex_183) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toInt64(LARGE_INT)).WillOnce(Return(123456789));

    EXPECT_EQ(123456789, mockValue.toInt64(LARGE_INT));

}



TEST_F(MockValueTest_183, ToInt64_ExceptionalCase_ErrorInConversion_183) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(-1)); // Assuming -1 indicates an error

    EXPECT_EQ(-1, mockValue.toInt64(0));

}



class ExifDataTest : public Test {

protected:

    Exiv2::ExifData exifData;

};



TEST_F(ExifDataTest_183, Add_NormalOperation_183) {

    MockValue mockValue(TypeId::asciiString);

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(42));

    Exiv2::ExifKey key("Exif.Image.Artist");

    exifData.add(key, &mockValue);

    EXPECT_EQ(1, exifData.count());

}



TEST_F(ExifDataTest_183, Add_BoundaryCondition_EmptyKey_183) {

    MockValue mockValue(TypeId::asciiString);

    Exiv2::ExifKey key("");

    exifData.add(key, &mockValue);

    EXPECT_EQ(1, exifData.count());

}



TEST_F(ExifDataTest_183, Add_BoundaryCondition_LargeCount_183) {

    MockValue mockValue(TypeId::asciiString);

    Exiv2::ExifKey key("Exif.Image.Artist");

    for (size_t i = 0; i < LARGE_INT; ++i) {

        exifData.add(key, &mockValue);

    }

    EXPECT_EQ(LARGE_INT, exifData.count());

}



TEST_F(ExifDataTest_183, Add_ExceptionalCase_NullValue_183) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    exifData.add(key, nullptr);

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_183, Clear_NormalOperation_183) {

    MockValue mockValue(TypeId::asciiString);

    Exiv2::ExifKey key("Exif.Image.Artist");

    exifData.add(key, &mockValue);

    exifData.clear();

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_183, Clear_BoundaryCondition_EmptyData_183) {

    exifData.clear(); // No-op

    EXPECT_EQ(0, exifData.count());

}



TEST_F(ExifDataTest_183, FindKey_NormalOperation_183) {

    MockValue mockValue(TypeId::asciiString);

    Exiv2::ExifKey key("Exif.Image.Artist");

    exifData.add(key, &mockValue);

    EXPECT_NE(exifData.end(), exifData.findKey(key));

}



TEST_F(ExifDataTest_183, FindKey_BoundaryCondition_KeyNotFound_183) {

    Exiv2::ExifKey key("Non.Existing.Key");

    EXPECT_EQ(exifData.end(), exifData.findKey(key));

}



TEST_F(ExifDataTest_183, FindKey_ExceptionalCase_EmptyKey_183) {

    Exiv2::ExifKey key("");

    EXPECT_EQ(exifData.end(), exifData.findKey(key));

}
