#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    class MockValue : public Value {

    public:

        MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));

        MOCK_METHOD(int, read, (const std::string& buf), (override));

        MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

        MOCK_METHOD(const size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

        MOCK_METHOD(const size_t, count, (), (const, override));

        MOCK_METHOD(const size_t, size, (), (const, override));

        MOCK_METHOD(const std::ostream&, write, (std::ostream& os), (const, override));

        MOCK_METHOD(const std::string, toString, (), (const, override));

        MOCK_METHOD(const std::string, toString, (size_t n), (const, override));

        MOCK_METHOD(const int64_t, toInt64, (size_t n), (const, override));

        MOCK_METHOD(const uint32_t, toUint32, (size_t n), (const, override));

        MOCK_METHOD(const float, toFloat, (size_t n), (const, override));

        MOCK_METHOD(const Rational, toRational, (size_t n), (const, override));

        MOCK_METHOD(const size_t, sizeDataArea, (), (const, override));

        MOCK_METHOD(const DataBuf, dataArea, (), (const, override));



        MockValue(TypeId typeId) : Value(typeId) {}

    };

}



class XmpdatumTest_1300 : public ::testing::Test {

protected:

    Exiv2::XmpKey key;

    std::shared_ptr<Exiv2::MockValue> mockValue;



    void SetUp() override {

        mockValue = std::make_shared<Exiv2::MockValue>(Exiv2::TypeId::tString);

    }

};



TEST_F(XmpdatumTest_1300, SetValueWithNullPointer_1300) {

    Exiv2::Xmpdatum xmpDatum(key, nullptr);

    EXPECT_NO_THROW(xmpDatum.setValue(nullptr));

}



TEST_F(XmpdatumTest_1300, SetValueWithValidValue_1300) {

    Exiv2::Xmpdatum xmpDatum(key, mockValue.get());

    EXPECT_NO_THROW(xmpDatum.setValue(mockValue.get()));

}



TEST_F(XmpdatumTest_1300, CopyConstructorDoesNotAffectOriginal_1300) {

    Exiv2::Xmpdatum original(key, mockValue.get());

    Exiv2::Xmpdatum copy = original;

    EXPECT_NE(&original.value(), &copy.value());

}



TEST_F(XmpdatumTest_1300, AssignmentOperatorDoesNotAffectOriginal_1300) {

    Exiv2::Xmpdatum original(key, mockValue.get());

    Exiv2::Xmpdatum other(key, nullptr);

    other = original;

    EXPECT_NE(&original.value(), &other.value());

}



TEST_F(XmpdatumTest_1300, SetValueWithDifferentValue_1300) {

    std::shared_ptr<Exiv2::MockValue> anotherMockValue = std::make_shared<Exiv2::MockValue>(Exiv2::TypeId::tString);

    Exiv2::Xmpdatum xmpDatum(key, mockValue.get());

    EXPECT_NO_THROW(xmpDatum.setValue(anotherMockValue.get()));

}



TEST_F(XmpdatumTest_1300, SetValueWithString_1300) {

    Exiv2::Xmpdatum xmpDatum(key, nullptr);

    EXPECT_EQ(0, xmpDatum.setValue("testString"));

}
