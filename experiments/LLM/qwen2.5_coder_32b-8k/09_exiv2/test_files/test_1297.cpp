#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class XmpdatumTest_1297 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpKey = std::make_unique<XmpKey>("Xmp.dc.title");

        value = std::make_unique<Value>("Sample Value");

        xmpDatum = std::make_unique<Xmpdatum>(*xmpKey, value.get());

    }



    std::unique_ptr<XmpKey> xmpKey;

    std::unique_ptr<Value> value;

    std::unique_ptr<Xmpdatum> xmpDatum;

};



TEST_F(XmpdatumTest_1297, ValueReturnsCorrectValue_1297) {

    const Value& result = xmpDatum->value();

    EXPECT_EQ(result, *value);

}



TEST_F(XmpdatumTest_1297, ValueThrowsOnUnsetValue_1297) {

    Xmpdatum emptyXmpDatum(*xmpKey, nullptr);

    EXPECT_THROW(emptyXmpDatum.value(), Error);

}



TEST_F(XmpdatumTest_1297, KeyReturnsCorrectValue_1297) {

    std::string result = xmpDatum->key();

    EXPECT_EQ(result, "Xmp.dc.title");

}
