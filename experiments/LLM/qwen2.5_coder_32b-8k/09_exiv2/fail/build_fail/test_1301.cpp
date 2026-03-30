#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpdatumTest_1301 : public ::testing::Test {

protected:

    XmpKey key;

    Value::UniquePtr value;

    Xmpdatum xmpDatum;



    XmpdatumTest_1301() 

        : key("Xmp.dc.title"), 

          value(Value::create(xmpText)),

          xmpDatum(key, value.get()) {}

};



TEST_F(XmpdatumTest_1301, SetValueNormalOperation_1301) {

    std::string testValue = "Sample Title";

    int result = xmpDatum.setValue(testValue);

    EXPECT_EQ(result, 0); // Assuming read() returns 0 on success

}



TEST_F(XmpdatumTest_1301, SetValueEmptyString_1301) {

    std::string emptyValue = "";

    int result = xmpDatum.setValue(emptyValue);

    EXPECT_EQ(result, 0); // Assuming read() returns 0 on success

}



TEST_F(XmpdatumTest_1301, SetValueLongString_1301) {

    std::string longValue(1000000, 'a'); // Large string test

    int result = xmpDatum.setValue(longValue);

    EXPECT_EQ(result, 0); // Assuming read() returns 0 on success

}



TEST_F(XmpdatumTest_1301, SetValueWithoutKey_1301) {

    Xmpdatum xmpDatumWithoutKey(XmpKey(), nullptr);

    std::string testValue = "Sample Title";

    int result = xmpDatumWithoutKey.setValue(testValue);

    EXPECT_EQ(result, 0); // Assuming read() returns 0 on success

}



TEST_F(XmpdatumTest_1301, SetValueWithInvalidType_1301) {

    XmpKey invalidKey("Invalid.Key");

    Xmpdatum xmpDatumWithInvalidKey(invalidKey, nullptr);

    std::string testValue = "Sample Title";

    int result = xmpDatumWithInvalidKey.setValue(testValue);

    EXPECT_EQ(result, 0); // Assuming read() returns 0 on success

}
