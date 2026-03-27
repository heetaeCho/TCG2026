#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffFinderTest : public ::testing::Test {

protected:

    uint16_t tag = 0x0100;

    IfdId group = ifdExif;

    ArrayCfg arrayCfg;

    ArrayDef arrayDef;

    size_t defSize = 10;

    std::unique_ptr<TiffBinaryArray> tiffBinaryArray;



    void SetUp() override {

        tiffBinaryArray = std::make_unique<TiffBinaryArray>(tag, group, arrayCfg, &arrayDef, defSize);

    }

};



TEST_F(TiffFinderTest_1639, VisitBinaryArray_NormalOperation_1639) {

    TiffFinder finder(tag, group);

    EXPECT_EQ(finder.result(), nullptr);

    finder.visitBinaryArray(tiffBinaryArray.get());

    EXPECT_EQ(finder.result(), tiffBinaryArray.get());

}



TEST_F(TiffFinderTest_1639, VisitBinaryArray_BoundaryCondition_TagMismatch_1639) {

    TiffFinder finder(tag + 1, group);

    finder.visitBinaryArray(tiffBinaryArray.get());

    EXPECT_EQ(finder.result(), nullptr);

}



TEST_F(TiffFinderTest_1639, VisitBinaryArray_BoundaryCondition_GroupMismatch_1639) {

    TiffFinder finder(tag, static_cast<IfdId>(group + 1));

    finder.visitBinaryArray(tiffBinaryArray.get());

    EXPECT_EQ(finder.result(), nullptr);

}



TEST_F(TiffFinderTest_1639, VisitBinaryArray_ExceptionalCase_NullObject_1639) {

    TiffFinder finder(tag, group);

    finder.visitBinaryArray(nullptr);

    EXPECT_EQ(finder.result(), nullptr);

}
