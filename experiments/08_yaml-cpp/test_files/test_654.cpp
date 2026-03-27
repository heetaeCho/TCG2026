#include <gtest/gtest.h>

#include <yaml-cpp/stlemitter.h>

#include <yaml-cpp/emitter.h>



using namespace YAML;



class EmitterTest_654 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_654, EmitSeq_EmptySequence_654) {

    std::vector<int> emptySeq;

    EmitSeq(emitter, emptySeq);

    EXPECT_EQ(emitter.c_str(), "[]");

}



TEST_F(EmitterTest_654, EmitSeq_SingleElement_654) {

    std::vector<int> singleElement = {1};

    EmitSeq(emitter, singleElement);

    EXPECT_EQ(emitter.c_str(), "[1]");

}



TEST_F(EmitterTest_654, EmitSeq_MultipleElements_654) {

    std::vector<int> multipleElements = {1, 2, 3};

    EmitSeq(emitter, multipleElements);

    EXPECT_EQ(emitter.c_str(), "[1, 2, 3]");

}



TEST_F(EmitterTest_654, EmitSeq_StringSequence_654) {

    std::vector<std::string> stringSeq = {"apple", "banana", "cherry"};

    EmitSeq(emitter, stringSeq);

    EXPECT_EQ(emitter.c_str(), "[\"apple\", \"banana\", \"cherry\"]");

}



TEST_F(EmitterTest_654, EmitSeq_MixedTypesSequence_654) {

    std::vector<std::string> mixedTypes = {"apple", "1", "2.5"};

    EmitSeq(emitter, mixedTypes);

    EXPECT_EQ(emitter.c_str(), "[\"apple\", \"1\", \"2.5\"]");

}



TEST_F(EmitterTest_654, EmitSeq_NestedSequence_654) {

    std::vector<std::vector<int>> nestedSeq = {{1, 2}, {3, 4}};

    EmitSeq(emitter, nestedSeq);

    EXPECT_EQ(emitter.c_str(), "[[1, 2], [3, 4]]");

}



TEST_F(EmitterTest_654, EmitSeq_SetIndentBeforeEmitting_654) {

    emitter.SetIndent(2);

    std::vector<int> seq = {1, 2, 3};

    EmitSeq(emitter, seq);

    EXPECT_EQ(emitter.c_str(), "[\n  1,\n  2,\n  3\n]");

}



TEST_F(EmitterTest_654, EmitSeq_SetSeqFormatFlowBeforeEmitting_654) {

    emitter.SetSeqFormat(Flow);

    std::vector<int> seq = {1, 2, 3};

    EmitSeq(emitter, seq);

    EXPECT_EQ(emitter.c_str(), "[1, 2, 3]");

}



TEST_F(EmitterTest_654, EmitSeq_SetSeqFormatBlockBeforeEmitting_654) {

    emitter.SetSeqFormat(Block);

    std::vector<int> seq = {1, 2, 3};

    EmitSeq(emitter, seq);

    EXPECT_EQ(emitter.c_str(), "- 1\n- 2\n- 3");

}



TEST_F(EmitterTest_654, EmitSeq_EmitterGoodStateAfterEmitting_654) {

    std::vector<int> seq = {1, 2, 3};

    EmitSeq(emitter, seq);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_654, EmitSeq_EmptyStringElements_654) {

    std::vector<std::string> emptyStrings = {"", "", ""};

    EmitSeq(emitter, emptyStrings);

    EXPECT_EQ(emitter.c_str(), "[\"\", \"\", \"\"]");

}
