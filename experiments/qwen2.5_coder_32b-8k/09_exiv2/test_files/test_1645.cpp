#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffCopierTest_1645 : public ::testing::Test {

protected:

    TiffComponent* pRoot_;

    uint32_t root_;

    const TiffHeaderBase* pHeader_;

    PrimaryGroups pPrimaryGroups_;



    TiffSizeEntry* tiffSizeEntry_;



    void SetUp() override {

        pRoot_ = nullptr;

        root_ = 0;

        pHeader_ = nullptr;

        pPrimaryGroups_ = {};



        uint16_t tag = 0x0100; // Example Tag

        IfdId group = ifdExif;   // Example Group

        uint16_t dtTag = 0x0103; // Data Type Tag

        IfdId dtGroup = ifdExif; // Data Type Group



        tiffSizeEntry_ = new TiffSizeEntry(tag, group, dtTag, dtGroup);

    }



    void TearDown() override {

        delete tiffSizeEntry_;

    }

};



TEST_F(TiffCopierTest_1645, VisitSizeEntry_CallsCopyObject_1645) {

    TiffCopier copier(pRoot_, root_, pHeader_, pPrimaryGroups_);

    

    EXPECT_NO_THROW(copier.visitSizeEntry(tiffSizeEntry_));

}



TEST_F(TiffCopierTest_1645, VisitSizeEntry_NullptrHandling_1645) {

    TiffCopier copier(pRoot_, root_, pHeader_, pPrimaryGroups_);



    EXPECT_NO_THROW(copier.visitSizeEntry(nullptr));

}
