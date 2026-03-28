#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    class MockValue : public Value {

    public:

        using Value::Value;

        MOCK_CONST_METHOD3(copy, size_t(byte* buf, ByteOrder byteOrder, int));

        MOCK_CONST_METHOD0(count, size_t());

        MOCK_CONST_METHOD0(size, size_t());

    };

}



class ExifdatumTest_752 : public ::testing::Test {

protected:

    std::unique_ptr<Exiv2::MockValue> mock_value;

    std::unique_ptr<Exiv2::ExifKey> key;

    Exiv2::Exifdatum exif_datum;



    ExifdatumTest_752() 

        : mock_value(std::make_unique<Exiv2::MockValue>(Exiv2::unsignedLong)),

          key(std::make_unique<Exiv2::ExifKey>("0th", "Image", 0x0132, "DateTime")),

          exif_datum(*key, mock_value.get()) {}

};



TEST_F(ExifdatumTest_752, CopyReturnsZeroWhenValueIsNull_752) {

    Exiv2::Exifdatum exif_datum_without_value(*key, nullptr);

    byte buf[10];

    EXPECT_EQ(exif_datum_without_value.copy(buf, Exiv2::bigEndian), 0U);

}



TEST_F(ExifdatumTest_752, CopyDelegatesToValueCopy_752) {

    byte buf[10];

    EXPECT_CALL(*mock_value, copy(buf, Exiv2::bigEndian, testing::_))

        .WillOnce(testing::Return(5));

    EXPECT_EQ(exif_datum.copy(buf, Exiv2::bigEndian), 5U);

}



TEST_F(ExifdatumTest_752, CopyHandlesLittleEndianOrder_752) {

    byte buf[10];

    EXPECT_CALL(*mock_value, copy(buf, Exiv2::littleEndian, testing::_))

        .WillOnce(testing::Return(3));

    EXPECT_EQ(exif_datum.copy(buf, Exiv2::littleEndian), 3U);

}
