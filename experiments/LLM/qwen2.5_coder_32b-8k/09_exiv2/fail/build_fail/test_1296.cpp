#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include <memory>



using namespace Exiv2;



class XmpdatumTest_1296 : public ::testing::Test {

protected:

    std::unique_ptr<Value> value;

    XmpKey key{"Xmp.dc.creator"};

    Xmpdatum xmpDatum{key, nullptr};



    void SetUp() override {

        value = Value::create(TypeId::asciiString);

        value->setValue("CreatorName");

        xmpDatum.setValue(value.get());

    }

};



TEST_F(XmpdatumTest_1296, GetValueReturnsNonNullPointer_1296) {

    EXPECT_NE(xmpDatum.getValue(), nullptr);

}



TEST_F(XmpdatumTest_1296, GetValueReturnsCorrectValue_1296) {

    auto retrievedValue = xmpDatum.getValue();

    EXPECT_EQ(retrievedValue->toString(), "CreatorName");

}



TEST_F(XmpdatumTest_1296, GetValueClonesTheValue_1296) {

    auto originalValue = xmpDatum.getValue();

    auto clonedValue = xmpDatum.getValue();

    EXPECT_NE(originalValue.get(), clonedValue.get());

    EXPECT_EQ(originalValue->toString(), clonedValue->toString());

}



TEST_F(XmpdatumTest_1296, GetValueReturnsNullWhenNoValueSet_1296) {

    Xmpdatum emptyXmpDatum{key, nullptr};

    EXPECT_EQ(emptyXmpDatum.getValue(), nullptr);

}
