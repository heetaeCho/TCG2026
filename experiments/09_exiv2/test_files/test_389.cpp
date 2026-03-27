#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary includes and namespace usage for Exiv2::Internal



using namespace ::testing;

using namespace Exiv2::Internal;



class TiffDirectoryTest : public Test {

protected:

    TiffDirectory directory{0, IfdId::IFD_0, false};

};



TEST_F(TiffDirectoryTest, DoSize_ReturnsCorrectValueForEmptyDirectory_389) {

    EXPECT_EQ(directory.doSize(), 0);

}



TEST_F(TiffDirectoryTest, DoSize_ReturnsCorrectValueWithSingleComponent_389) {

    auto component = std::make_unique<TiffComponent>(1, IfdId::IFD_0);

    component->setStart(reinterpret_cast<byte*>(new byte[4]));

    directory.doAddChild(std::move(component));

    

    EXPECT_EQ(directory.doSize(), 2 + 12 + 4); // 2 for count field, 12 for single component, 4 aligned to word boundary

}



TEST_F(TiffDirectoryTest, DoSize_ReturnsCorrectValueWithMultipleComponents_389) {

    auto component1 = std::make_unique<TiffComponent>(1, IfdId::IFD_0);

    component1->setStart(reinterpret_cast<byte*>(new byte[4]));

    directory.doAddChild(std::move(component1));



    auto component2 = std::make_unique<TiffComponent>(2, IfdId::IFD_0);

    component2->setStart(reinterpret_cast<byte*>(new byte[8]));

    directory.doAddChild(std::move(component2));



    EXPECT_EQ(directory.doSize(), 2 + (12 * 2) + 4); // 2 for count field, 24 for two components, 4 aligned to word boundary

}



TEST_F(TiffDirectoryTest, DoSize_ReturnsCorrectValueWithComponentHavingData_389) {

    auto component = std::make_unique<TiffComponent>(1, IfdId::IFD_0);

    component->setStart(reinterpret_cast<byte*>(new byte[4]));

    directory.doAddChild(std::move(component));



    EXPECT_CALL(*component.get(), size()).WillOnce(Return(6)); // 6 bytes of data

    EXPECT_CALL(*component.get(), sizeData()).WillOnce(Return(8)); // 8 bytes of metadata



    EXPECT_EQ(directory.doSize(), 2 + 12 + 4 + 6 + 8); // 2 for count field, 12 for component, 4 aligned to word boundary, 6 data, 8 metadata

}



TEST_F(TiffDirectoryTest, DoSize_ReturnsCorrectValueWithNextDirectory_389) {

    auto nextDir = std::make_unique<TiffDirectory>(0, IfdId::IFD_1, false);

    directory.doAddNext(std::move(nextDir));



    EXPECT_EQ(directory.doSize(), 2 + (12 * 0) + 4); // 2 for count field, 0 components, 4 aligned to word boundary for next dir

}



TEST_F(TiffDirectoryTest, DoSize_ReturnsCorrectValueWithComponentAndNextDirectory_389) {

    auto component = std::make_unique<TiffComponent>(1, IfdId::IFD_0);

    component->setStart(reinterpret_cast<byte*>(new byte[4]));

    directory.doAddChild(std::move(component));



    auto nextDir = std::make_unique<TiffDirectory>(0, IfdId::IFD_1, false);

    directory.doAddNext(std::move(nextDir));



    EXPECT_EQ(directory.doSize(), 2 + 12 + 4 + 4); // 2 for count field, 12 for component, 4 aligned to word boundary, 4 next dir

}
