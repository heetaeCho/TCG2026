#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class DataValueTest_797 : public ::testing::Test {

protected:

    std::vector<int> testData = {1, 2, 3, 4, 5};

    DataValue dataValue{TypeId::unsignedLong};



    void SetUp() override {

        // Simulate reading data into the value_

        dataValue.value_.resize(testData.size());

        for (size_t i = 0; i < testData.size(); ++i) {

            dataValue.value_[i] = static_cast<LARGE_INT>(testData[i]);

        }

    }

};



TEST_F(DataValueTest_797, WriteOutput_797) {

    std::ostringstream oss;

    dataValue.write(oss);

    EXPECT_EQ(oss.str(), "1 2 3 4 5");

}



TEST_F(DataValueTest_797, EmptyWriteOutput_797) {

    DataValue emptyDataValue{TypeId::unsignedLong};

    std::ostringstream oss;

    emptyDataValue.write(oss);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(DataValueTest_797, SingleElementWriteOutput_797) {

    DataValue singleElementDataValue{TypeId::unsignedLong};

    singleElementDataValue.value_.resize(1);

    singleElementDataValue.value_[0] = 42;

    std::ostringstream oss;

    singleElementDataValue.write(oss);

    EXPECT_EQ(oss.str(), "42");

}



TEST_F(DataValueTest_797, CountReturnsCorrectSize_797) {

    EXPECT_EQ(dataValue.count(), testData.size());

}



TEST_F(DataValueTest_797, EmptyCountReturnsZero_797) {

    DataValue emptyDataValue{TypeId::unsignedLong};

    EXPECT_EQ(emptyDataValue.count(), 0);

}
