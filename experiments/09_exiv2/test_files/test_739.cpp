#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    class MockValue : public Value {

    public:

        MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));

        MOCK_METHOD(int, read, (const std::string& buf), (override));

        MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

        MOCK_METHOD(size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

        MOCK_METHOD(size_t, count, (), (const, override));

        MOCK_METHOD(size_t, size, (), (const, override));

        MOCK_METHOD(const std::ostream&, write, (std::ostream& os), (const, override));

        MOCK_METHOD(std::string, toString, (), (const, override));

        MOCK_METHOD(std::string, toString, (size_t n), (const, override));

        MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));

        MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

        MOCK_METHOD(float, toFloat, (size_t n), (const, override));

        MOCK_METHOD(Rational, toRational, (size_t n), (const, override));

        MOCK_METHOD(size_t, sizeDataArea, (), (const, override));

        MOCK_METHOD(DataBuf, dataArea, (), (const, override));



        MockValue(TypeId typeId) : Value(typeId) {}

    };

}



class ExifdatumTest_739 : public ::testing::Test {

protected:

    std::unique_ptr<Exiv2::MockValue> mockValue;

    Exiv2::ExifKey exifKey;



    void SetUp() override {

        mockValue = std::make_unique<Exiv2::MockValue>(Exiv2::unsignedShort);

        exifKey = Exiv2::ExifKey("Exif.Image.Artist");

    }

};



TEST_F(ExifdatumTest_739, SetValueWithNullPointer_739) {

    Exiv2::Exifdatum exifDatum(exifKey, nullptr);

    exifDatum.setValue(nullptr);

}



TEST_F(ExifdatumTest_739, SetValueWithValuePointer_739) {

    EXPECT_CALL(*mockValue, clone_()).Times(1);



    Exiv2::Exifdatum exifDatum(exifKey, mockValue.get());

    exifDatum.setValue(mockValue.get());

}



TEST_F(ExifdatumTest_739, ConstructorWithNullPointer_739) {

    Exiv2::Exifdatum exifDatum(exifKey, nullptr);

}



TEST_F(ExifdatumTest_739, CopyConstructor_739) {

    EXPECT_CALL(*mockValue, clone_()).Times(1);



    Exiv2::Exifdatum original(exifKey, mockValue.get());

    Exiv2::Exifdatum copy(original);

}
