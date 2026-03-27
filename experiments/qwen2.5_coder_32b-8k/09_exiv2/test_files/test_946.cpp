#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/exiv2.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_946 : public ::testing::Test {

protected:

    CanonMakerNote canonMakerNote_;

};



TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_NonUnsignedShortType_946) {

    Exiv2::Value value;

    std::ostringstream os;



    canonMakerNote_.printCs0x0002(os, value, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_ZeroCount_946) {

    Exiv2::Value* value = new Exiv2::ShortValue;

    std::ostringstream os;



    canonMakerNote_.printCs0x0002(os, *value, nullptr);



    EXPECT_EQ(os.str(), "");

    delete value;

}



TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_ValueZero_946) {

    Exiv2::Value* value = new Exiv2::ShortValue(1);

    std::ostringstream os;



    (*value)[0] = 0;

    canonMakerNote_.printCs0x0002(os, *value, nullptr);



    EXPECT_EQ(os.str(), "Off");

    delete value;

}



TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_ValueNonZero_946) {

    Exiv2::Value* value = new Exiv2::ShortValue(1);

    std::ostringstream os;



    (*value)[0] = 50;

    canonMakerNote_.printCs0x0002(os, *value, nullptr);



    EXPECT_EQ(os.str(), "5 s");

    delete value;

}



TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_ValueDecimal_946) {

    Exiv2::Value* value = new Exiv2::ShortValue(1);

    std::ostringstream os;



    (*value)[0] = 35;

    canonMakerNote_.printCs0x0002(os, *value, nullptr);



    EXPECT_EQ(os.str(), "3.5 s");

    delete value;

}
