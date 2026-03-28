#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffFinderTest_1640 : public ::testing::Test {

protected:

    uint16_t tag = 1; // Example tag

    IfdId group = ifdExif; // Example group

    TiffFinder finder{tag, group};

    std::unique_ptr<TiffBinaryElement> binaryElement = std::make_unique<TiffBinaryElement>();

};



TEST_F(TiffFinderTest_1640, VisitBinaryElement_SetsResult_1640) {

    finder.visitBinaryElement(binaryElement.get());

    EXPECT_EQ(finder.result(), binaryElement.get());

}



TEST_F(TiffFinderTest_1640, FindObject_SetsResult_1640) {

    TiffComponent* component = binaryElement.get();

    finder.findObject(component);

    EXPECT_EQ(finder.result(), component);

}



TEST_F(TiffFinderTest_1640, Init_ResetsResult_1640) {

    finder.visitBinaryElement(binaryElement.get());

    EXPECT_NE(finder.result(), nullptr);



    uint16_t newTag = 2;

    IfdId newGroup = ifdGps;

    finder.init(newTag, newGroup);

    EXPECT_EQ(finder.result(), nullptr);

}



TEST_F(TiffFinderTest_1640, Result_ReturnsNullptrInitially_1640) {

    EXPECT_EQ(finder.result(), nullptr);

}
