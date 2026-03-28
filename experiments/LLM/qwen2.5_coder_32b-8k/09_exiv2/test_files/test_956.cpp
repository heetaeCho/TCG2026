#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_956 : public ::testing::Test {

protected:

    CanonMakerNote makerNote_;

};



TEST_F(CanonMakerNoteTest_956, PutIncreasesCount_956) {

    std::ostringstream os;

    Value value(TypeId::unsignedShort);

    value.makeArray(1);

    *value.begin() = 1234;



    makerNote_.printSi0x0009(os, value, nullptr);



    EXPECT_EQ(os.str(), "1234");

}



TEST_F(CanonMakerNoteTest_956, PutMultipleValues_956) {

    std::ostringstream os;

    Value value(TypeId::unsignedShort);

    value.makeArray(2);

    *value.begin() = 1234;

    *(value.begin()+1) = 5678;



    makerNote_.printSi0x0009(os, value, nullptr);



    EXPECT_EQ(os.str(), "1234");

}



TEST_F(CanonMakerNoteTest_956, EmptyValue_956) {

    std::ostringstream os;

    Value value(TypeId::unsignedShort);

    value.makeArray(0);



    makerNote_.printSi0x0009(os, value, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_956, InvalidType_956) {

    std::ostringstream os;

    Value value(TypeId::undefined);

    value.makeArray(1);



    makerNote_.printSi0x0009(os, value, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_956, ValidTypeZeroCount_956) {

    std::ostringstream os;

    Value value(TypeId::unsignedShort);

    value.makeArray(0);



    makerNote_.printSi0x0009(os, value, nullptr);



    EXPECT_EQ(os.str(), "");

}
