#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

#include <exiv2/properties.hpp>



namespace Exiv2 {

    class MockXmpKey : public XmpKey {

    public:

        MOCK_CONST_METHOD0(key, std::string());

        MOCK_CONST_METHOD0(familyName, const char*());

        MOCK_CONST_METHOD0(groupName, std::string());

        MOCK_CONST_METHOD0(tagName, std::string());

        MOCK_CONST_METHOD0(tagLabel, std::string());

        MOCK_CONST_METHOD0(tagDesc, std::string());

        MOCK_CONST_METHOD0(tag, uint16_t());

    };



    class MockValue : public Value {

    public:

        MOCK_CONST_METHOD0(typeId, TypeId());

        MOCK_CONST_METHOD0(typeName, const char*());

        MOCK_CONST_METHOD0(typeSize, size_t());

        MOCK_CONST_METHOD0(count, size_t());

        MOCK_CONST_METHOD0(size, size_t());

        MOCK_CONST_METHOD0(toString, std::string());

    };

}



class XmpdatumTest_1284 : public ::testing::Test {

protected:

    void SetUp() override {

        mockKey = std::make_unique<Exiv2::MockXmpKey>();

        mockValue = std::make_unique<Exiv2::MockValue>();

        xmpDatum = std::make_unique<Exiv2::Xmpdatum>(*mockKey, mockValue.get());

    }



    void TearDown() override {

        xmpDatum.reset();

        mockValue.reset();

        mockKey.reset();

    }



    std::unique_ptr<Exiv2::MockXmpKey> mockKey;

    std::unique_ptr<Exiv2::MockValue> mockValue;

    std::unique_ptr<Exiv2::Xmpdatum> xmpDatum;

};



TEST_F(XmpdatumTest_1284, TagDesc_ReturnsEmptyStringWhenKeyIsNull_1284) {

    EXPECT_CALL(*mockKey, tagDesc()).WillOnce(::testing::Return("Tag Description"));

    EXPECT_EQ(xmpDatum->tagDesc(), "Tag Description");

}



TEST_F(XmpdatumTest_1284, TagDesc_ReturnsExpectedDescription_1284) {

    xmpDatum.reset(new Exiv2::Xmpdatum(Exiv2::XmpKey("test"), mockValue.get()));

    EXPECT_EQ(xmpDatum->tagDesc(), "");

}



TEST_F(XmpdatumTest_1284, TagDesc_HandlesNullPointerGracefully_1284) {

    xmpDatum.reset(new Exiv2::Xmpdatum(Exiv2::XmpKey(""), mockValue.get()));

    EXPECT_EQ(xmpDatum->tagDesc(), "");

}
