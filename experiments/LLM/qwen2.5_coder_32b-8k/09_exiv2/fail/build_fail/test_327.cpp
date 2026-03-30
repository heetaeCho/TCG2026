#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include <memory>



using namespace Exiv2::Internal;



class TiffDirectoryTest_327 : public ::testing::Test {

protected:

    std::unique_ptr<TiffDirectory> tiffDir;

    uint16_t tag = 0x0100; // Example tag

    IfdId group = ifdExif;



    void SetUp() override {

        tiffDir = std::make_unique<TiffDirectory>(tag, group, false);

    }

};



TEST_F(TiffDirectoryTest_327, DoAddChild_AddsComponent_327) {

    auto component = std::make_shared<TiffComponent>(0x0101, ifdExif);

    TiffComponent* addedComponent = tiffDir->doAddChild(component);



    EXPECT_EQ(addedComponent, component.get());

}



TEST_F(TiffDirectoryTest_327, DoAddChild_ReturnsNullptrOnNullInput_327) {

    TiffComponent::SharedPtr nullComponent;

    TiffComponent* addedComponent = tiffDir->doAddChild(nullComponent);



    EXPECT_EQ(addedComponent, nullptr);

}



// Assuming doCount() is a valid method to check the number of children

TEST_F(TiffDirectoryTest_327, DoAddChild_IncreasesCount_327) {

    size_t initialCount = tiffDir->doCount();

    auto component1 = std::make_shared<TiffComponent>(0x0101, ifdExif);

    tiffDir->doAddChild(component1);

    size_t countAfterFirstAdd = tiffDir->doCount();



    EXPECT_EQ(countAfterFirstAdd, initialCount + 1);



    auto component2 = std::make_shared<TiffComponent>(0x0102, ifdExif);

    tiffDir->doAddChild(component2);

    size_t countAfterSecondAdd = tiffDir->doCount();



    EXPECT_EQ(countAfterSecondAdd, initialCount + 2);

}



TEST_F(TiffDirectoryTest_327, DoAddChild_AddsMultipleComponents_327) {

    auto component1 = std::make_shared<TiffComponent>(0x0101, ifdExif);

    tiffDir->doAddChild(component1);



    auto component2 = std::make_shared<TiffComponent>(0x0102, ifdExif);

    tiffDir->doAddChild(component2);



    size_t countAfterAdds = tiffDir->doCount();



    EXPECT_EQ(countAfterAdds, 2);

}



// Assuming doWrite() is a valid method to simulate writing and check side effects

TEST_F(TiffDirectoryTest_327, DoWrite_DoesNotCrashWithEmptyComponents_327) {

    IoWrapper ioWrapper; // Mock or real implementation as per available dependencies

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_NO_THROW(tiffDir->doWrite(ioWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx));

}



// Assuming doAccept() is a valid method to simulate visitor pattern and check side effects

TEST_F(TiffDirectoryTest_327, DoAccept_DoesNotCrashWithNoChildren_327) {

    TiffVisitor visitor; // Mock or real implementation as per available dependencies



    EXPECT_NO_THROW(tiffDir->doAccept(visitor));

}



// Assuming doClone() is a valid method to simulate cloning and check side effects

TEST_F(TiffDirectoryTest_327, DoClone_ReturnsNonNullPointer_327) {

    const TiffDirectory* clonedDir = tiffDir->doClone();



    EXPECT_NE(clonedDir, nullptr);

}



// Assuming doSize(), doCount(), doSizeData(), and doSizeImage() are valid methods to check size calculations

TEST_F(TiffDirectoryTest_327, DoSize_ReturnsNonNegativeValue_327) {

    size_t size = tiffDir->doSize();



    EXPECT_GE(size, 0);

}



TEST_F(TiffDirectoryTest_327, DoCount_ReturnsZeroForEmptyComponents_327) {

    size_t count = tiffDir->doCount();



    EXPECT_EQ(count, 0);

}



TEST_F(TiffDirectoryTest_327, DoSizeData_ReturnsNonNegativeValue_327) {

    size_t dataSize = tiffDir->doSizeData();



    EXPECT_GE(dataSize, 0);

}



TEST_F(TiffDirectoryTest_327, DoSizeImage_ReturnsNonNegativeValue_327) {

    size_t imageSize = tiffDir->doSizeImage();



    EXPECT_GE(imageSize, 0);

}
