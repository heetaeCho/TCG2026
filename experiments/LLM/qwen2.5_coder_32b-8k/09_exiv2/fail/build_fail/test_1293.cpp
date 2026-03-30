#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



// Mock classes if needed (not required in this case as there are no external collaborators)



class XmpdatumTest : public ::testing::Test {

protected:

    XmpKey key;

    Value::UniquePtr value;

    Xmpdatum xmpDatum;



    void SetUp() override {

        value = Value::create(unknown);

        xmpDatum = Xmpdatum(key, value.get());

    }

};



TEST_F(XmpdatumTest_1293, ToInt64NormalOperation_1293) {

    // Assuming the internal value is set to a known integer

    int64_t expectedValue = 12345;

    value->setDataArea(reinterpret_cast<const byte*>(&expectedValue), sizeof(expectedValue));

    EXPECT_EQ(xmpDatum.toInt64(0), expectedValue);

}



TEST_F(XmpdatumTest_1293, ToInt64BoundaryCondition_1293) {

    // Test with n = 0 (first element)

    int64_t expectedValue = 54321;

    value->setDataArea(reinterpret_cast<const byte*>(&expectedValue), sizeof(expectedValue));

    EXPECT_EQ(xmpDatum.toInt64(0), expectedValue);



    // Test with n out of bounds, should return -1

    EXPECT_EQ(xmpDatum.toInt64(1), -1);

}



TEST_F(XmpdatumTest_1293, ToInt64NullValue_1293) {

    // Test when value is not set (nullptr)

    xmpDatum.setValue(nullptr);

    EXPECT_EQ(xmpDatum.toInt64(0), -1);

}
