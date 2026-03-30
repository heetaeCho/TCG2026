#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



TEST(CompareTest_1906, NormalOperation_LessThan_1906) {

    XMP_Node leftNode(nullptr, "apple", 0);

    XMP_Node rightNode(nullptr, "banana", 0);



    EXPECT_TRUE(Compare(&leftNode, &rightNode));

}



TEST(CompareTest_1906, NormalOperation_GreaterThan_1906) {

    XMP_Node leftNode(nullptr, "cherry", 0);

    XMP_Node rightNode(nullptr, "berry", 0);



    EXPECT_FALSE(Compare(&leftNode, &rightNode));

}



TEST(CompareTest_1906, NormalOperation_EqualNames_1906) {

    XMP_Node leftNode(nullptr, "grape", 0);

    XMP_Node rightNode(nullptr, "grape", 0);



    EXPECT_FALSE(Compare(&leftNode, &rightNode));

}



TEST(CompareTest_1906, BoundaryCondition_EmptyStringLeft_1906) {

    XMP_Node leftNode(nullptr, "", 0);

    XMP_Node rightNode(nullptr, "orange", 0);



    EXPECT_TRUE(Compare(&leftNode, &rightNode));

}



TEST(CompareTest_1906, BoundaryCondition_EmptyStringRight_1906) {

    XMP_Node leftNode(nullptr, "lemon", 0);

    XMP_Node rightNode(nullptr, "", 0);



    EXPECT_FALSE(Compare(&leftNode, &rightNode));

}



TEST(CompareTest_1906, BoundaryCondition_BothEmptyStrings_1906) {

    XMP_Node leftNode(nullptr, "", 0);

    XMP_Node rightNode(nullptr, "", 0);



    EXPECT_FALSE(Compare(&leftNode, &rightNode));

}
