#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffCopierTest_1647 : public ::testing::Test {

protected:

    std::unique_ptr<TiffHeaderBase> pHeader_;

    PrimaryGroups pPrimaryGroups_;

    TiffComponent* pRoot_ = nullptr;

    uint32_t root_ = 0;

    std::unique_ptr<TiffMnEntry> tiffMnEntry_;



    void SetUp() override {

        pHeader_ = std::make_unique<TiffHeaderBase>();

        pPrimaryGroups_.clear();

        pRoot_ = new TiffComponent();

        root_ = 1;

        tiffMnEntry_ = std::make_unique<TiffMnEntry>(1, IfdId::rootIfd, IfdId::mnExif);

    }



    void TearDown() override {

        delete pRoot_;

    }

};



TEST_F(TiffCopierTest_1647, VisitMnEntry_CallsCopyObject_1647) {

    TiffCopier copier(pRoot_, root_, pHeader_.get(), pPrimaryGroups_);

    EXPECT_CALL(*tiffMnEntry_, doAccept(::testing::_)).WillOnce([this](TiffVisitor& visitor) {

        visitor.visitMnEntry(this->tiffMnEntry_.get());

    });



    EXPECT_CALL(copier, copyObject(::testing::_)).Times(1);

    tiffMnEntry_->accept(copier);

}



TEST_F(TiffCopierTest_1647, VisitMnEntry_NullPointer_NoCrash_1647) {

    TiffCopier copier(pRoot_, root_, pHeader_.get(), pPrimaryGroups_);

    EXPECT_NO_THROW(copier.visitMnEntry(nullptr));

}
