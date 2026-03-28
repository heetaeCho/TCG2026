#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class StringValueBaseTest : public ::testing::Test {

protected:

    TypeId dummyTypeId = static_cast<TypeId>(1);

};



TEST_F(StringValueBaseTest, ConstructorReadsString_2166) {

    std::string testString = "Hello, World!";

    StringValueBase stringValue(dummyTypeId, testString);



    EXPECT_EQ(stringValue.toString(), testString);

}



TEST_F(StringValueBaseTest, ReadUpdatesInternalState_2166) {

    std::string initialString = "Initial";

    std::string newString = "Updated";

    StringValueBase stringValue(dummyTypeId, initialString);



    stringValue.read(newString);



    EXPECT_EQ(stringValue.toString(), newString);

}



TEST_F(StringValueBaseTest, CountReturnsOneForSingleString_2166) {

    std::string testString = "Single";

    StringValueBase stringValue(dummyTypeId, testString);



    EXPECT_EQ(stringValue.count(), 1);

}



TEST_F(StringValueBaseTest, SizeMatchesStringLength_2166) {

    std::string testString = "LengthTest";

    StringValueBase stringValue(dummyTypeId, testString);



    EXPECT_EQ(stringValue.size(), testString.size());

}



TEST_F(StringValueBaseTest, ToInt64ThrowsForNonNumericString_2166) {

    std::string nonNumericString = "NotANumber";

    StringValueBase stringValue(dummyTypeId, nonNumericString);



    EXPECT_THROW(stringValue.toInt64(0), Error);

}



TEST_F(StringValueBaseTest, ToUint32ThrowsForNonNumericString_2166) {

    std::string nonNumericString = "NotANumber";

    StringValueBase stringValue(dummyTypeId, nonNumericString);



    EXPECT_THROW(stringValue.toUint32(0), Error);

}



TEST_F(StringValueBaseTest, ToFloatThrowsForNonNumericString_2166) {

    std::string nonNumericString = "NotANumber";

    StringValueBase stringValue(dummyTypeId, nonNumericString);



    EXPECT_THROW(stringValue.toFloat(0), Error);

}



TEST_F(StringValueBaseTest, ToRationalThrowsForNonNumericString_2166) {

    std::string nonNumericString = "NotANumber";

    StringValueBase stringValue(dummyTypeId, nonNumericString);



    EXPECT_THROW(stringValue.toRational(0), Error);

}



TEST_F(StringValueBaseTest, WriteOutputsCorrectString_2166) {

    std::string testString = "WriteTest";

    StringValueBase stringValue(dummyTypeId, testString);

    std::ostringstream os;



    stringValue.write(os);



    EXPECT_EQ(os.str(), testString);

}
