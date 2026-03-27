#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "value.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffDataEntryTest : public ::testing::Test {

protected:

    std::unique_ptr<Value> mockValue;

    TiffDataEntry tiffDataEntry{1, IfdId::rootIFD, TiffType::undefined};



    void SetUp() override {

        mockValue = std::make_unique<NiceMock<MockValue>>();

        EXPECT_CALL(*mockValue, sizeDataArea()).WillRepeatedly(::testing::Return(42));

        tiffDataEntry.setValue(std::move(mockValue));

    }

};



class MockValue : public Value {

public:

    using Value::Value;

    MOCK_CONST_METHOD0(sizeDataArea, size_t());

};



TEST_F(TiffDataEntryTest, DoSizeData_ReturnsCorrectSize_401) {

    EXPECT_EQ(tiffDataEntry.doSizeData(), 42);

}



TEST_F(TiffDataEntryTest, DoSizeData_ReturnsZeroWhenNoValueSet_401) {

    tiffDataEntry.setValue(nullptr);

    EXPECT_EQ(tiffDataEntry.doSizeData(), 0);

}
