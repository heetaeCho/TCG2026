#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include <memory>



using namespace Exiv2::Internal;



class TiffDirectoryTest_405 : public ::testing::Test {

protected:

    TiffDirectory* dir;

    

    void SetUp() override {

        dir = new TiffDirectory(0x123, IfdId::rootIFD, false);

    }



    void TearDown() override {

        delete dir;

    }

};



TEST_F(TiffDirectoryTest_405, DoSizeImage_NoComponents_405) {

    EXPECT_EQ(dir->doSizeImage(), 0ul);

}



TEST_F(TiffDirectoryTest_405, DoSizeImage_OneComponent_405) {

    auto component = std::make_shared<TiffComponent>(0x123, IfdId::rootIFD);

    EXPECT_CALL(*component, sizeImage()).WillOnce(::testing::Return(42ul));

    dir->doAddChild(component);

    EXPECT_EQ(dir->doSizeImage(), 42ul);

}



TEST_F(TiffDirectoryTest_405, DoSizeImage_MultipleComponents_405) {

    auto component1 = std::make_shared<TiffComponent>(0x123, IfdId::rootIFD);

    EXPECT_CALL(*component1, sizeImage()).WillOnce(::testing::Return(42ul));

    

    auto component2 = std::make_shared<TiffComponent>(0x456, IfdId::exifIFD);

    EXPECT_CALL(*component2, sizeImage()).WillOnce(::testing::Return(24ul));



    dir->doAddChild(component1);

    dir->doAddChild(component2);



    EXPECT_EQ(dir->doSizeImage(), 66ul);

}



TEST_F(TiffDirectoryTest_405, DoSizeImage_NextDirectory_405) {

    auto component = std::make_shared<TiffComponent>(0x123, IfdId::rootIFD);

    EXPECT_CALL(*component, sizeImage()).WillOnce(::testing::Return(42ul));



    TiffDirectory nextDir(0x789, IfdId::gpsIFD, false);

    EXPECT_CALL(nextDir, doSizeImage()).WillOnce(::testing::Return(15ul));

    

    dir->doAddChild(component);

    dir->doAddNext(std::make_unique<TiffDirectory>(nextDir));



    EXPECT_EQ(dir->doSizeImage(), 57ul);

}



TEST_F(TiffDirectoryTest_405, DoSizeImage_NextAndMultipleComponents_405) {

    auto component1 = std::make_shared<TiffComponent>(0x123, IfdId::rootIFD);

    EXPECT_CALL(*component1, sizeImage()).WillOnce(::testing::Return(42ul));

    

    auto component2 = std::make_shared<TiffComponent>(0x456, IfdId::exifIFD);

    EXPECT_CALL(*component2, sizeImage()).WillOnce(::testing::Return(24ul));



    TiffDirectory nextDir(0x789, IfdId::gpsIFD, false);

    EXPECT_CALL(nextDir, doSizeImage()).WillOnce(::testing::Return(15ul));

    

    dir->doAddChild(component1);

    dir->doAddChild(component2);

    dir->doAddNext(std::make_unique<TiffDirectory>(nextDir));



    EXPECT_EQ(dir->doSizeImage(), 81ul);

}



TEST_F(TiffDirectoryTest_405, DoSizeImage_ZeroSizeComponents_405) {

    auto component = std::make_shared<TiffComponent>(0x123, IfdId::rootIFD);

    EXPECT_CALL(*component, sizeImage()).WillOnce(::testing::Return(0ul));

    

    dir->doAddChild(component);



    EXPECT_EQ(dir->doSizeImage(), 0ul);

}
