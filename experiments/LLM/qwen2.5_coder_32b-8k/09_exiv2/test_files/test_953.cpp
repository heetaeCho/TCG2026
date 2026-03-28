#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/value.hpp>

#include <Exiv2/exifdata.hpp>



using namespace Exiv2::Internal;

using namespace testing;



class CanonMakerNoteTest_953 : public ::testing::Test {

protected:

    CanonMakerNote canoni;

    std::ostringstream os;

};



TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_NormalOperation_953) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(1, 16); // Example value where count > 0 and type is unsignedShort



    canoni.printSi0x0001(os, value, nullptr);



    EXPECT_FLOAT_EQ(std::exp2(canonEv(value.toInt64()) / 32) * 100.0F, std::stof(os.str()));

}



TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_BoundaryCountZero_953) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 16); // Boundary case where count == 0



    canoni.printSi0x0001(os, value, nullptr);



    EXPECT_TRUE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_BoundaryCountOne_953) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(1, 16); // Boundary case where count == 1



    canoni.printSi0x0001(os, value, nullptr);



    EXPECT_FLOAT_EQ(std::exp2(canonEv(value.toInt64()) / 32) * 100.0F, std::stof(os.str()));

}



TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_WrongType_953) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString); // Wrong type case

    value.modify("test", 4);



    canoni.printSi0x0001(os, value, nullptr);



    EXPECT_TRUE(os.str().empty());

}
