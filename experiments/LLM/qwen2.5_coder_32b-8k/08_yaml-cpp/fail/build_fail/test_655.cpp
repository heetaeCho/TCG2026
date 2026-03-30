#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <sstream>

#include <vector>



using namespace YAML;



class EmitterTest_655 : public ::testing::Test {

protected:

    void SetUp() override {

        emitter.reset(new Emitter);

    }



    std::unique_ptr<Emitter> emitter;

};



TEST_F(EmitterTest_655, WriteString_NormalOperation_655) {

    emitter->Write("test_string");

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteBool_NormalOperation_655) {

    emitter->Write(true);

    emitter->Write(false);

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteChar_NormalOperation_655) {

    emitter->Write('a');

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteVectorOfInts_NormalOperation_655) {

    std::vector<int> vec = {1, 2, 3};

    *emitter << vec;

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, SetIndent_BoundaryCondition_655) {

    EXPECT_TRUE(emitter->SetIndent(0));

    EXPECT_TRUE(emitter->SetIndent(10));

    EXPECT_FALSE(emitter->SetIndent(-1)); // Assuming negative indent is not allowed

}



TEST_F(EmitterTest_655, SetPrecision_Float_NormalOperation_655) {

    EXPECT_TRUE(emitter->SetFloatPrecision(2));

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, SetPrecision_Double_NormalOperation_655) {

    EXPECT_TRUE(emitter->SetDoublePrecision(3));

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, SetSeqFormat_NormalOperation_655) {

    EXPECT_TRUE(emitter->SetSeqFormat(FmtBlock)); // Assuming FmtBlock is a valid EMITTER_MANIP value

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteAlias_NormalOperation_655) {

    emitter->Write(_Alias("test_alias"));

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteAnchor_NormalOperation_655) {

    emitter->Write(_Anchor("test_anchor"));

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteTag_NormalOperation_655) {

    emitter->Write(_Tag("test_tag"));

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteComment_NormalOperation_655) {

    emitter->Write(_Comment("test_comment"));

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteNull_NormalOperation_655) {

    emitter->Write(_Null());

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, WriteBinary_NormalOperation_655) {

    std::vector<unsigned char> binaryData = {0x01, 0x02, 0x03};

    emitter->Write(Binary(binaryData));

    EXPECT_TRUE(emitter->good());

}



TEST_F(EmitterTest_655, GetLastError_AfterError_655) {

    // Assuming an operation that would cause an error

    emitter->SetIndent(-1); // Invalid indent to trigger an error

    EXPECT_FALSE(emitter->good());

    EXPECT_FALSE(emitter->GetLastError().empty());

}
