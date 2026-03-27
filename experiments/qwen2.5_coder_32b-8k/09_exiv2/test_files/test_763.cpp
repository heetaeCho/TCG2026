#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    std::unique_ptr<Value> mockValue;

    ExifKey mockKey;



    void SetUp() override {

        mockValue = Value::create(tByte);

    }

};



TEST_F(ExifdatumTest_763, GetValue_ReturnsNullptrWhenNoValueSet_763) {

    Exifdatum exifdatum(mockKey, nullptr);

    EXPECT_EQ(nullptr, exifdatum.getValue().get());

}



TEST_F(ExifdatumTest_763, GetValue_ReturnsClonedValueWhenValueSet_763) {

    Exifdatum exifdatum(mockKey, mockValue.get());

    Value::UniquePtr result = exifdatum.getValue();

    EXPECT_NE(nullptr, result.get());

    EXPECT_NE(mockValue.get(), result.get()); // Check that it's a clone

}



TEST_F(ExifdatumTest_763, GetValue_ReturnsSameTypeWhenValueSet_763) {

    Exifdatum exifdatum(mockKey, mockValue.get());

    Value::UniquePtr result = exifdatum.getValue();

    EXPECT_EQ(result->typeId(), mockValue->typeId());

}



TEST_F(ExifdatumTest_763, GetValue_ReturnsSameContentWhenValueSet_763) {

    Exifdatum exifdatum(mockKey, mockValue.get());

    Value::UniquePtr result = exifdatum.getValue();

    EXPECT_EQ(result->toString(), mockValue->toString());

}
