#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



namespace Exiv2 {

namespace Internal {



class Nikon1MakerNoteTest_450 : public ::testing::Test {

protected:

    Nikon1MakerNote nikonMakerNote;

    std::ostringstream os;

};



TEST_F(Nikon1MakerNoteTest_450, Print0x0002_SingleValue_450) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedLong);

    value.modify(1UL);



    nikonMakerNote.print0x0002(os, value, nullptr);

    

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(Nikon1MakerNoteTest_450, Print0x0002_MultipleValues_450) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedLong);

    value.modify(1UL);

    value.push_back(2UL);



    nikonMakerNote.print0x0002(os, value, nullptr);

    

    EXPECT_EQ(os.str(), "2");

}



TEST_F(Nikon1MakerNoteTest_450, Print0x0002_EmptyValue_450) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedLong);



    nikonMakerNote.print0x0002(os, value, nullptr);

    

    EXPECT_EQ(os.str(), "()");

}



TEST_F(Nikon1MakerNoteTest_450, Print0x0002_LargeValue_450) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedLong);

    value.modify(static_cast<uint64_t>(std::numeric_limits<unsigned long>::max()));



    nikonMakerNote.print0x0002(os, value, nullptr);

    

    EXPECT_EQ(os.str(), "(" + std::to_string(std::numeric_limits<unsigned long>::max()) + ")");

}



TEST_F(Nikon1MakerNoteTest_450, Print0x0002_MultipleLargeValues_450) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedLong);

    value.modify(static_cast<uint64_t>(std::numeric_limits<unsigned long>::max()));

    value.push_back(static_cast<uint64_t>(std::numeric_limits<unsigned long>::max()));



    nikonMakerNote.print0x0002(os, value, nullptr);

    

    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<unsigned long>::max()));

}



} // namespace Internal

} // namespace Exiv2
