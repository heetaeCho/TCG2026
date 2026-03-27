#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



namespace Exiv2 {

namespace Internal {



class TiffFinderTest : public ::testing::Test {

protected:

    TiffComponent* createTiffComponent(uint16_t tag, IfdId group) {

        return new TiffComponent(tag, group);

    }



    void SetUp() override {

        component1 = createTiffComponent(1, ifd0);

        component2 = createTiffComponent(2, exif);

        finder = std::make_unique<TiffFinder>(1, ifd0);

    }



    void TearDown() override {

        delete component1;

        delete component2;

    }



    TiffComponent* component1;

    TiffComponent* component2;

    std::unique_ptr<TiffFinder> finder;

};



TEST_F(TiffFinderTest_1630, FindObject_MatchingTagAndGroup_1630) {

    finder->findObject(component1);

    EXPECT_EQ(finder->result(), component1);

}



TEST_F(TiffFinderTest_1630, FindObject_NonMatchingTag_1630) {

    finder->findObject(component2);

    EXPECT_EQ(finder->result(), nullptr);

}



TEST_F(TiffFinderTest_1630, FindObject_NonMatchingGroup_1630) {

    component2->setStart(reinterpret_cast<const byte*>(ifd0));

    finder->findObject(component2);

    EXPECT_EQ(finder->result(), nullptr);

}



TEST_F(TiffFinderTest_1630, FindObject_MultipleCalls_ReturnsFirstMatch_1630) {

    TiffComponent* component3 = createTiffComponent(1, ifd0);

    finder->findObject(component2); // Should not match

    finder->findObject(component3); // Should match

    EXPECT_EQ(finder->result(), component3);

    delete component3;

}



TEST_F(TiffFinderTest_1630, FindObject_AfterInit_ReturnsCorrectMatch_1630) {

    TiffComponent* component4 = createTiffComponent(2, exif);

    finder->init(2, exif);

    finder->findObject(component4); // Should match

    EXPECT_EQ(finder->result(), component4);

    delete component4;

}



TEST_F(TiffFinderTest_1630, FindObject_SetGoFalse_StopTraversal_1630) {

    TiffComponent* component5 = createTiffComponent(1, ifd0);

    finder->setGo(geTraverse, false);

    finder->findObject(component5); // Should not match due to go flag

    EXPECT_EQ(finder->result(), nullptr);

    delete component5;

}



}  // namespace Internal

}  // namespace Exiv2
