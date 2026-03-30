#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key1 = std::make_unique<ExifKey>("key1");

    std::unique_ptr<Value> value1 = Value::create(stringType);

    std::unique_ptr<ExifKey> key2 = std::make_unique<ExifKey>("key2");

    std::unique_ptr<Value> value2 = Value::create(int32Type);



    Exifdatum exifdatum1 = Exifdatum(*key1, value1.get());

    Exifdatum exifdatum2 = Exifdatum(*key2, value2.get());



    void SetUp() override {

        // Setup any state needed before each test

    }



    void TearDown() override {

        // Clean up after each test if needed

    }

};



TEST_F(ExifdatumTest_730, CopyConstructorCreatesDeepCopy_730) {

    Exifdatum copy = Exifdatum(exifdatum1);

    EXPECT_NE(copy.key_.get(), exifdatum1.key_.get());

    EXPECT_NE(copy.value_.get(), exifdatum1.value_.get());

}



TEST_F(ExifdatumTest_730, AssignmentOperatorCreatesDeepCopy_730) {

    Exifdatum assigned;

    assigned = exifdatum1;

    EXPECT_NE(assigned.key_.get(), exifdatum1.key_.get());

    EXPECT_NE(assigned.value_.get(), exifdatum1.value_.get());

}



TEST_F(ExifdatumTest_730, SelfAssignmentDoesNotChangeState_730) {

    Exifdatum selfAssigned = exifdatum1;

    void* originalKeyPtr = exifdatum1.key_.get();

    void* originalValuePtr = exifdatum1.value_.get();



    selfAssigned = exifdatum1;



    EXPECT_EQ(selfAssigned.key_.get(), originalKeyPtr);

    EXPECT_EQ(selfAssigned.value_.get(), originalValuePtr);

}



TEST_F(ExifdatumTest_730, AssignmentOperatorHandlesNullValues_730) {

    Exifdatum nullValueDatum(*key1, nullptr);

    Exifdatum assigned = exifdatum1;

    assigned = nullValueDatum;



    EXPECT_NE(assigned.key_.get(), exifdatum1.key_.get());

    EXPECT_EQ(assigned.value_.get(), nullptr);

}



TEST_F(ExifdatumTest_730, AssignmentOperatorHandlesDifferentTypes_730) {

    Exifdatum differentTypeDatum = exifdatum2;

    void* originalKeyPtr = exifdatum1.key_.get();

    void* originalValuePtr = exifdatum1.value_.get();



    exifdatum1 = differentTypeDatum;



    EXPECT_NE(exifdatum1.key_.get(), originalKeyPtr);

    EXPECT_NE(exifdatum1.value_.get(), originalValuePtr);

}



TEST_F(ExifdatumTest_730, KeyIsCopiedCorrectly_730) {

    Exifdatum copy = exifdatum1;

    EXPECT_EQ(copy.key()->key(), exifdatum1.key()->key());

    EXPECT_EQ(copy.key()->familyName(), exifdatum1.key()->familyName());

    EXPECT_EQ(copy.key()->groupName(), exifdatum1.key()->groupName());

    EXPECT_EQ(copy.key()->tagName(), exifdatum1.key()->tagName());

}



TEST_F(ExifdatumTest_730, ValueIsCopiedCorrectly_730) {

    Exifdatum copy = exifdatum1;

    EXPECT_EQ(copy.value().typeId(), exifdatum1.value().typeId());

}
