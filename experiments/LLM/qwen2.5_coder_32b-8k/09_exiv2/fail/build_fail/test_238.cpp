#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffEntryBaseTest_238 : public ::testing::Test {

protected:

    TiffEntryBase* entry_;



    void SetUp() override {

        entry_ = new TiffEntryBase(0x1234, IfdId::IFD0, TiffType::undefined);

    }



    void TearDown() override {

        delete entry_;

    }

};



TEST_F(TiffEntryBaseTest_238, SetCountAndGetDoCount_NormalOperation_238) {

    size_t count = 10;

    entry_->setCount(count);

    EXPECT_EQ(entry_->doCount(), count);

}



TEST_F(TiffEntryBaseTest_238, SetCount_Zero_BoundaryCondition_238) {

    size_t count = 0;

    entry_->setCount(count);

    EXPECT_EQ(entry_->doCount(), count);

}



TEST_F(TiffEntryBaseTest_238, SetCount_LargeValue_BoundaryCondition_238) {

    size_t count = std::numeric_limits<size_t>::max();

    entry_->setCount(count);

    EXPECT_EQ(entry_->doCount(), count);

}



TEST_F(TiffEntryBaseTest_238, SetOffsetAndGetOffset_NormalOperation_238) {

    size_t offset = 100;

    entry_->setOffset(offset);

    EXPECT_EQ(entry_->offset(), offset);

}



TEST_F(TiffEntryBaseTest_238, SetOffset_Zero_BoundaryCondition_238) {

    size_t offset = 0;

    entry_->setOffset(offset);

    EXPECT_EQ(entry_->offset(), offset);

}



TEST_F(TiffEntryBaseTest_238, SetOffset_LargeValue_BoundaryCondition_238) {

    size_t offset = std::numeric_limits<size_t>::max();

    entry_->setOffset(offset);

    EXPECT_EQ(entry_->offset(), offset);

}
