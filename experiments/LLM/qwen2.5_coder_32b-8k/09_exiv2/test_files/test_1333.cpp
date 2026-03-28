#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags.hpp"

#include "datasets.cpp"



using namespace Exiv2;



class ExifKeyImplTest : public ::testing::Test {

protected:

    Impl* impl;

    

    void SetUp() override {

        impl = new Impl();

        impl->groupName_ = "TestGroup";

    }



    void TearDown() override {

        delete impl;

    }

};



TEST_F(ExifKeyImplTest_PutIncreasesCount_1333, MakeKey_NormalOperation_1333) {

    TagInfo tagInfo = {SectionId::internal, TypeId::asciiString, 10, nullptr};

    impl->makeKey(256, IfdId::ifd0, &tagInfo);

    

    EXPECT_EQ(impl->tag_, 256);

    EXPECT_EQ(impl->ifdId_, IfdId::ifd0);

    EXPECT_EQ(impl->tagInfo_->sectionId_, SectionId::internal);

}



TEST_F(ExifKeyImplTest_BoundaryConditions_1333, MakeKey_ZeroTagValue_1333) {

    TagInfo tagInfo = {SectionId::internal, TypeId::asciiString, 10, nullptr};

    impl->makeKey(0, IfdId::ifd0, &tagInfo);

    

    EXPECT_EQ(impl->tag_, 0);

}



TEST_F(ExifKeyImplTest_BoundaryConditions_1333, MakeKey_MaxTagValue_1333) {

    TagInfo tagInfo = {SectionId::internal, TypeId::asciiString, 10, nullptr};

    impl->makeKey(std::numeric_limits<uint16_t>::max(), IfdId::ifd0, &tagInfo);

    

    EXPECT_EQ(impl->tag_, std::numeric_limits<uint16_t>::max());

}



TEST_F(ExifKeyImplTest_ErrorHandling_1333, MakeKey_NullTagInfo_1333) {

    impl->makeKey(256, IfdId::ifd0, nullptr);

    

    EXPECT_EQ(impl->tag_, 256);

    EXPECT_EQ(impl->ifdId_, IfdId::ifd0);

    EXPECT_EQ(impl->tagInfo_, nullptr);

}



TEST_F(ExifKeyImplTest_ExternalInteractions_1333, MakeKey_VerifyGroupName_1333) {

    TagInfo tagInfo = {SectionId::internal, TypeId::asciiString, 10, nullptr};

    impl->makeKey(256, IfdId::ifd0, &tagInfo);

    

    EXPECT_EQ(impl->groupName_, "TestGroup");

}



TEST_F(ExifKeyImplTest_ExternalInteractions_1333, MakeKey_VerifyFamilyName_1333) {

    TagInfo tagInfo = {SectionId::internal, TypeId::asciiString, 10, nullptr};

    impl->makeKey(256, IfdId::ifd0, &tagInfo);

    

    EXPECT_EQ(impl->key_.substr(0, strlen(familyName_)), familyName_);

}
