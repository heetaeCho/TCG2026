#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



class XmpDataTest_1312 : public ::testing::Test {

protected:

    Exiv2::XmpData xmpData;

};



TEST_F(XmpDataTest_1312, EraseRemovesElement_1312) {

    // Add elements to the XmpData

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value);

    auto it = xmpData.begin();

    xmpData.erase(it);



    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1312, EraseBoundaryCondition_1312) {

    // Add elements to the XmpData

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value);



    auto it = xmpData.begin();

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 0);



    // Attempt to erase from an empty container, should not crash

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1312, EraseIteratorInvalidation_1312) {

    // Add elements to the XmpData

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value);



    auto it = xmpData.begin();

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 0);



    // Check if iterator is invalidated

    EXPECT_TRUE(it == xmpData.end());

}



TEST_F(XmpDataTest_1312, EraseMultipleElements_1312) {

    // Add multiple elements to the XmpData

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value);

    xmpData.add(Exiv2::XmpKey("Xmp.dc.description"), new Exiv2::Value);



    EXPECT_EQ(xmpData.count(), 2);



    // Erase one element

    auto it = xmpData.begin();

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 1);



    // Erase the remaining element

    it = xmpData.begin();

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1312, EraseIteratorPosition_1312) {

    // Add multiple elements to the XmpData

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value);

    xmpData.add(Exiv2::XmpKey("Xmp.dc.description"), new Exiv2::Value);



    auto it = xmpData.begin();

    ++it; // Move to the second element

    xmpData.erase(it);



    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(XmpDataTest_1312, EraseEmptyContainer_1312) {

    // Attempt to erase from an empty container, should not crash

    auto it = xmpData.begin();

    xmpData.erase(it);



    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1312, EraseAllElements_1312) {

    // Add multiple elements to the XmpData

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value);

    xmpData.add(Exiv2::XmpKey("Xmp.dc.description"), new Exiv2::Value);



    auto it = xmpData.begin();

    while (it != xmpData.end()) {

        it = xmpData.erase(it);

    }



    EXPECT_EQ(xmpData.count(), 0);

}
