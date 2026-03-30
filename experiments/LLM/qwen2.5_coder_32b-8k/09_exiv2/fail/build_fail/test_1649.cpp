#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryArrayMock : public TiffBinaryArray {

public:

    using TiffBinaryArray::TiffBinaryArray;

    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));

};



class TiffCopierTest : public ::testing::Test {

protected:

    void SetUp() override {

        pRoot_ = new TiffComponent();

        pHeader_ = new TiffHeaderBase();

        primaryGroups_ = PrimaryGroups{};

        copier_ = std::make_unique<TiffCopier>(pRoot_, 0, pHeader_, primaryGroups_);

        binaryArray_ = new TiffBinaryArrayMock(0x1234, ifdId, ArrayCfg{}, nullptr, 0);

    }



    void TearDown() override {

        delete binaryArray_;

        delete pHeader_;

        delete pRoot_;

    }



    TiffComponent* pRoot_;

    const TiffHeaderBase* pHeader_;

    PrimaryGroups primaryGroups_;

    std::unique_ptr<TiffCopier> copier_;

    TiffBinaryArrayMock* binaryArray_;

};



TEST_F(TiffCopierTest_NormalOperation_1649, VisitBinaryArray_CallsDoAccept_1649) {

    EXPECT_CALL(*binaryArray_, doAccept(::testing::_)).Times(1);

    copier_->visitBinaryArray(binaryArray_);

}



TEST_F(TiffCopierTest_BoundaryConditions_1649, VisitBinaryArray_NullObject_DoesNotCrash_1649) {

    copier_->visitBinaryArray(nullptr);

}



TEST_F(TiffCopierTest_ExceptionalCases_1649, VisitBinaryArray_ExceptionInDoAccept_HandledGracefully_1649) {

    EXPECT_CALL(*binaryArray_, doAccept(::testing::_)).WillOnce(testing::Throw(std::runtime_error("test")));

    EXPECT_NO_THROW(copier_->visitBinaryArray(binaryArray_));

}
