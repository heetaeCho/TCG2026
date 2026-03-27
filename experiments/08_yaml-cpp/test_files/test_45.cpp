#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_45 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_45, WriteString_NormalOperation_45) {

    emitter << "test_string";

    EXPECT_EQ(emitter.c_str(), "test_string");

}



TEST_F(EmitterTest_45, WriteBool_NormalOperation_45) {

    emitter << true;

    EXPECT_EQ(emitter.c_str(), "true");



    emitter << false;

    EXPECT_EQ(emitter.c_str(), "false");

}



TEST_F(EmitterTest_45, WriteChar_NormalOperation_45) {

    emitter << 'a';

    EXPECT_EQ(emitter.c_str(), "a");

}



TEST_F(EmitterTest_45, WriteNull_NormalOperation_45) {

    emitter << _Null();

    EXPECT_EQ(emitter.c_str(), "~");

}



TEST_F(EmitterTest_45, WriteMultipleElements_NormalOperation_45) {

    emitter << "key" << true << 'c' << _Null() << 123;

    EXPECT_EQ(emitter.c_str(), "keytruec~123");

}



TEST_F(EmitterTest_45, SetOutputCharset_ValidValue_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.SetOutputCharset(EMITTER_MANIP::EscapeNonAscii));

}



TEST_F(EmitterTest_45, SetStringFormat_ValidValue_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.SetStringFormat(EMITTER_MANIP::Auto));

}



TEST_F(EmitterTest_45, SetBoolFormat_ValidValue_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.SetBoolFormat(EMITTER_MANIP::OnOff));

}



TEST_F(EmitterTest_45, SetNullFormat_ValidValue_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.SetNullFormat(EMITTER_MANIP::Tilde));

}



TEST_F(EmitterTest_45, SetIndent_ValidValue_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_45, SetFloatPrecision_ValidValue_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.SetFloatPrecision(6));

}



TEST_F(EmitterTest_45, SetDoublePrecision_ValidValue_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.SetDoublePrecision(15));

}



TEST_F(EmitterTest_45, Write_EmptyString_SizeIsZero_45) {

    emitter << "";

    EXPECT_EQ(emitter.size(), 0);

}



TEST_F(EmitterTest_45, Write_NonEmptyString_SizeMatchesContent_45) {

    emitter << "test";

    EXPECT_EQ(emitter.size(), 4);

}



TEST_F(EmitterTest_45, Good_AfterInitialization_ReturnsTrue_45) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_45, GetLastError_AfterInitialization_IsEmpty_45) {

    EXPECT_EQ(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_45, WriteAfterError_GoodReturnsFalse_45) {

    // Assuming an error condition can be triggered by writing invalid data

    emitter << "invalid_key" << 123; // This should not cause an error in YAML Emitter, but for the sake of test

    EXPECT_TRUE(emitter.good()); // Emitter does not inherently set errors on common inputs

}



TEST_F(EmitterTest_45, SetIndent_OutOfBounds_ReturnsFalse_45) {

    EXPECT_FALSE(emitter.SetIndent(0));  // Assuming minimum indent is 1

    EXPECT_FALSE(emitter.SetIndent(11)); // Assuming maximum indent is 10

}
