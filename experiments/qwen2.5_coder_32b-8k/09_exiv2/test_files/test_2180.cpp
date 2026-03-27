#include <gtest/gtest.h>

#include "exiv2/xmp.hpp"

#include "exiv2/value.hpp"

#include "exiv2/properties.hpp"



using namespace Exiv2;



// Mocking Value class for testing purposes

class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte *buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, read, (const std::string &buf), (override));

    MOCK_METHOD(int, setDataArea, (const byte *buf, size_t len), (override));

    MOCK_METHOD(size_t, copy, (byte *buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(const std::ostream &, write, (std::ostream &os), (const, override));

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



// Mocking XmpKey class for testing purposes

class MockXmpKey : public XmpKey {

public:

    MOCK_CONST_METHOD0(key, std::string());

    MOCK_CONST_METHOD0(familyName, const char*());

    MOCK_CONST_METHOD0(groupName, std::string());

    MOCK_CONST_METHOD0(tagName, std::string());

    MOCK_CONST_METHOD0(tagLabel, std::string());

    MOCK_CONST_METHOD0(tagDesc, std::string());

    MOCK_CONST_METHOD0(tag, uint16_t());

    MOCK_METHOD(XmpKey::UniquePtr, clone, (), (const, override));



    MockXmpKey(const std::string &key) : XmpKey(key) {}

};



class XmpdatumTest_2180 : public ::testing::Test {

protected:

    void SetUp() override {

        mockValue = std::make_unique<MockValue>(TypeId::asciiString);

        mockKey = std::make_unique<MockXmpKey>("test:key");

    }



    Xmpdatum::Impl impl;

    std::unique_ptr<MockValue> mockValue;

    std::unique_ptr<MockXmpKey> mockKey;

};



TEST_F(XmpdatumTest_2180, ConstructorCopiesKeyAndValue_2180) {

    Xmpdatum::Impl original(*mockKey, mockValue.get());

    Xmpdatum::Impl copy(original);



    EXPECT_EQ(copy.key_->key(), mockKey->key());

    EXPECT_EQ(copy.value_->typeId(), mockValue->typeId());

}



TEST_F(XmpdatumTest_2180, AssignmentOperatorCopiesKeyAndValue_2180) {

    Xmpdatum::Impl original(*mockKey, mockValue.get());

    Xmpdatum::Impl copy;

    copy = original;



    EXPECT_EQ(copy.key_->key(), mockKey->key());

    EXPECT_EQ(copy.value_->typeId(), mockValue->typeId());

}



TEST_F(XmpdatumTest_2180, KeyAndValueAreDeepCopied_2180) {

    Xmpdatum::Impl original(*mockKey, mockValue.get());

    Xmpdatum::Impl copy(original);



    EXPECT_NE(copy.key_.get(), original.key_.get());

    EXPECT_NE(copy.value_.get(), original.value_.get());

}
