#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/value.hpp"



namespace Exiv2 {

    class XmpArrayValue;

}



using ::testing::_;

using ::testing::Return;



class XmpArrayValueTest_846 : public ::testing::Test {

protected:

    Exiv2::XmpArrayValue xmpArrayValue{Exiv2::TypeId::xmpText};

};



TEST_F(XmpArrayValueTest_846, WriteEmptyArray_846) {

    std::ostringstream os;

    xmpArrayValue.write(os);

    EXPECT_EQ("", os.str());

}



TEST_F(XmpArrayValueTest_846, WriteSingleElementArray_846) {

    xmpArrayValue.read("single");

    std::ostringstream os;

    xmpArrayValue.write(os);

    EXPECT_EQ("single", os.str());

}



TEST_F(XmpArrayValueTest_846, WriteMultipleElementsArray_846) {

    xmpArrayValue.read("first");

    xmpArrayValue.read("second");

    xmpArrayValue.read("third");

    std::ostringstream os;

    xmpArrayValue.write(os);

    EXPECT_EQ("first, second, third", os.str());

}



TEST_F(XmpArrayValueTest_846, WriteBoundaryConditionArray_846) {

    xmpArrayValue.read("");

    std::ostringstream os;

    xmpArrayValue.write(os);

    EXPECT_EQ("", os.str());



    xmpArrayValue.read("boundary,");

    xmpArrayValue.write(os);

    EXPECT_EQ(", boundary,", os.str());

}



TEST_F(XmpArrayValueTest_846, WriteLargeNumberOfElementsArray_846) {

    for (int i = 0; i < 10; ++i) {

        xmpArrayValue.read("element" + std::to_string(i));

    }

    std::ostringstream os;

    xmpArrayValue.write(os);

    EXPECT_EQ("element0, element1, element2, element3, element4, element5, element6, element7, element8, element9", os.str());

}
