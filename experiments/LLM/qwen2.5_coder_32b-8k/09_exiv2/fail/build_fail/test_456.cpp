#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.cpp" // Assuming this is how we include the partial implementation



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class Nikon2MakerNoteTest_456 : public ::testing::Test {

protected:

    Nikon2MakerNote nikonMakerNote;

    std::ostringstream os;

};



TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NotUsedCase_456) {

    Value value; // Assuming Value is default constructible and toRational returns (0, 1)

    nikonMakerNote.print0x000a(os, value, nullptr);

    EXPECT_EQ(os.str(), "Not used");

}



TEST_F(Nikon2MakerNoteTest_456, Print0x000a_ZeroDenominatorCase_456) {

    Value value; // Assuming we can set value to return (1, 0) from toRational

    auto [r, s] = std::make_pair(1, 0);

    EXPECT_CALL(value, toRational()).WillOnce(testing::Return(std::make_pair(r, s)));

    nikonMakerNote.print0x000a(os, value, nullptr);

    EXPECT_EQ(os.str(), "(Value())"); // Assuming Value() is how it prints when default constructed

}



TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NormalCase_456) {

    Value value; // Assuming we can set value to return (3, 2) from toRational

    auto [r, s] = std::make_pair(3, 2);

    EXPECT_CALL(value, toRational()).WillOnce(testing::Return(std::make_pair(r, s)));

    nikonMakerNote.print0x000a(os, value, nullptr);

    EXPECT_EQ(os.str(), "1.5x");

}



TEST_F(Nikon2MakerNoteTest_456, Print0x000a_BoundaryCase_456) {

    Value value; // Assuming we can set value to return (1, 1) from toRational

    auto [r, s] = std::make_pair(1, 1);

    EXPECT_CALL(value, toRational()).WillOnce(testing::Return(std::make_pair(r, s)));

    nikonMakerNote.print0x000a(os, value, nullptr);

    EXPECT_EQ(os.str(), "1.0x");

}

```


