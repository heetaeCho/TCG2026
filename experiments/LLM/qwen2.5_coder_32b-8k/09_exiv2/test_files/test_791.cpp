#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Return;



class ValueTest : public ::testing::Test {

protected:

    TypeId dummyTypeId = static_cast<TypeId>(0);

    Value* value = nullptr;



    void SetUp() override {

        value = Value::create(dummyTypeId).release();

    }



    void TearDown() override {

        delete value;

    }

};



TEST_F(ValueTest_791, DataAreaInitiallyEmpty_791) {

    auto dataBuf = value->dataArea();

    EXPECT_EQ(dataBuf.pData_, nullptr);

    EXPECT_EQ(dataBuf.size_, 0U);

}



TEST_F(ValueTest_791, SetDataAreaUpdatesDataBuffer_791) {

    byte buffer[5] = {1, 2, 3, 4, 5};

    size_t len = sizeof(buffer);

    value->setDataArea(buffer, len);



    auto dataBuf = value->dataArea();

    EXPECT_NE(dataBuf.pData_, nullptr);

    EXPECT_EQ(dataBuf.size_, len);

    for (size_t i = 0; i < len; ++i) {

        EXPECT_EQ(dataBuf.pData_[i], buffer[i]);

    }

}



TEST_F(ValueTest_791, SizeDataAreaReflectsSetSize_791) {

    byte buffer[5] = {1, 2, 3, 4, 5};

    size_t len = sizeof(buffer);

    value->setDataArea(buffer, len);



    EXPECT_EQ(value->sizeDataArea(), len);

}



TEST_F(ValueTest_791, OkInitiallyTrue_791) {

    EXPECT_TRUE(value->ok());

}



// Assuming that setting invalid data does not change the ok status based on the interface

TEST_F(ValueTest_791, SettingInvalidDataDoesNotChangeOkStatus_791) {

    byte buffer[5] = {1, 2, 3, 4, 5};

    size_t len = sizeof(buffer);

    value->setDataArea(nullptr, len); // Assuming nullptr is invalid



    EXPECT_TRUE(value->ok());

}
