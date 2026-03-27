#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/datasets.hpp"



namespace Exiv2 {

    class MockValue : public Value {

    public:

        MOCK_METHOD(int, read, (const byte *buf, size_t len, ByteOrder byteOrder), (override));

        MOCK_METHOD(int, read, (const std::string &buf), (override));

        MOCK_METHOD(int, setDataArea, (const byte *buf, size_t len), (override));

        MOCK_METHOD(size_t, copy, (byte *buf, ByteOrder byteOrder), (const, override));

        MOCK_METHOD(size_t, count, (), (const, override));

        MOCK_METHOD(size_t, size, (), (const, override));

        MOCK_METHOD(std::ostream &, write, (std::ostream &os), (const, override));

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



using namespace Exiv2;



TEST(IptcdatumTest_686, CopyConstructorCreatesDeepCopy_686) {

    IptcKey key(1, 2);

    NiceMock<MockValue> mockValue(value::string);

    Iptcdatum original(key, &mockValue);

    Iptcdatum copy(original);



    EXPECT_NE(copy.key_.get(), original.key_.get());

}



TEST(IptcdatumTest_686, AssignmentOperatorCreatesDeepCopy_686) {

    IptcKey key(1, 2);

    NiceMock<MockValue> mockValue(value::string);

    Iptcdatum original(key, &mockValue);

    Iptcdatum copy;

    copy = original;



    EXPECT_NE(copy.key_.get(), original.key_.get());

}



TEST(IptcdatumTest_686, SelfAssignmentDoesNotChangeState_686) {

    IptcKey key(1, 2);

    NiceMock<MockValue> mockValue(value::string);

    Iptcdatum original(key, &mockValue);



    auto* originalKeyPtr = original.key_.get();

    original = original;



    EXPECT_EQ(original.key_.get(), originalKeyPtr);

}



TEST(IptcdatumTest_686, AssignmentOperatorHandlesNullptrGracefully_686) {

    IptcKey key(1, 2);

    NiceMock<MockValue> mockValue(value::string);

    Iptcdatum original(key, &mockValue);

    Iptcdatum empty;



    original = empty;

}



TEST(IptcdatumTest_686, CopyConstructorHandlesNullptrGracefully_686) {

    IptcKey key(1, 2);

    NiceMock<MockValue> mockValue(value::string);

    Iptcdatum original(key, nullptr);



    Iptcdatum copy(original);

}



TEST(IptcdatumTest_686, AssignmentOperatorWithDifferentValueTypes_686) {

    IptcKey key(1, 2);

    NiceMock<MockValue> mockValueString(value::string);

    NiceMock<MockValue> mockValueUint32(value::unsignedRational);



    Iptcdatum original(key, &mockValueString);

    Iptcdatum copy(original);



    EXPECT_NE(copy.key_.get(), original.key_.get());



    copy = Iptcdatum(key, &mockValueUint32);



    EXPECT_NE(copy.key_.get(), original.key_.get());

}
