#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



using namespace YAML;



class EmitterTest_530 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_530, SetLocalValue_BeginDoc_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(BeginDoc);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_EndDoc_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(EndDoc);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_BeginSeq_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(BeginSeq);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_EndSeq_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(EndSeq);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_BeginMap_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(BeginMap);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_EndMap_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(EndMap);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_Key_Value_Ignored_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(Key);

    EXPECT_TRUE(emitter.good());



    emitter.SetLocalValue(Value);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_TagByKind_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(TagByKind);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_Newline_NormalOperation_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(Newline);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_DefaultCase_DelegatesToState_530) {

    EXPECT_TRUE(emitter.good());

    emitter.SetLocalValue(Auto); // Assuming Auto is a valid default case

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_530, SetLocalValue_WhenNotGood_ReturnsThis_530) {

    emitter = Emitter();

    emitter.SetOutputCharset(InvalidManipulator);

    EXPECT_FALSE(emitter.good());



    auto& result = emitter.SetLocalValue(BeginDoc);

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_530, SetLocalValue_ValidBoundaryCases_530) {

    EMITTER_MANIP boundaryValues[] = {BeginDoc, EndDoc, BeginSeq, EndSeq, BeginMap, EndMap, TagByKind, Newline};



    for (auto value : boundaryValues) {

        EXPECT_TRUE(emitter.good());

        emitter.SetLocalValue(value);

        EXPECT_TRUE(emitter.good());

    }

}



TEST_F(EmitterTest_530, SetLocalValue_DefaultBoundaryCases_530) {

    EMITTER_MANIP defaultValues[] = {Auto, UpperCase, LowerCase};



    for (auto value : defaultValues) {

        EXPECT_TRUE(emitter.good());

        emitter.SetLocalValue(value);

        EXPECT_TRUE(emitter.good());

    }

}
