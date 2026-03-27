#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



using namespace YAML;



class EmitterTest_516 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_516, GetLastErrorMessageInitiallyEmpty_516) {

    EXPECT_EQ(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_516, WriteStringSuccessfully_516) {

    emitter.Write("test");

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_516, WriteBoolSuccessfully_516) {

    emitter.Write(true);

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_516, SetOutputCharsetValidValue_516) {

    EXPECT_TRUE(emitter.SetOutputCharset(EMITTER_MANIP::BIN));

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_516, SetInvalidIndentBoundaryCondition_516) {

    EXPECT_FALSE(emitter.SetIndent(0));

    EXPECT_FALSE(emitter.good());

    // Assuming GetLastError provides meaningful error message

    EXPECT_NE(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_516, SetValidPrecisionBoundaryCondition_516) {

    EXPECT_TRUE(emitter.SetFloatPrecision(1));

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "");

    EXPECT_TRUE(emitter.SetDoublePrecision(1));

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_516, SetInvalidPrecisionBoundaryCondition_516) {

    EXPECT_FALSE(emitter.SetFloatPrecision(0));

    EXPECT_FALSE(emitter.good());

    // Assuming GetLastError provides meaningful error message

    EXPECT_NE(emitter.GetLastError(), "");



    EXPECT_FALSE(emitter.SetDoublePrecision(0));

    EXPECT_FALSE(emitter.good());

    // Assuming GetLastError provides meaningful error message

    EXPECT_NE(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_516, RestoreGlobalModifiedSettings_516) {

    emitter.SetFloatPrecision(5);

    emitter.RestoreGlobalModifiedSettings();

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "");

}
