#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;



class ExeNameTest : public ::testing::Test {

protected:

    ExeName exeName;

};



TEST_F(ExeNameTest_DefaultConstructor_393, DefaultNameIsExecutable_393) {

    EXPECT_EQ(exeName.name(), "<executable>");

}



TEST_F(ExeNameTest_StringReferenceConstructor_393, NameReflectsReferencedString_393) {

    std::string ref = "test_executable";

    ExeName exeNameRef(ref);

    EXPECT_EQ(exeNameRef.name(), ref);

}



TEST_F(ExeNameTest_SetNewName_393, SetUpdatesInternalName_393) {

    std::string newName = "new_test_executable";

    exeName.set(newName);

    EXPECT_EQ(exeName.name(), newName);

}



TEST_F(ExeNameTest_ParseFunction_393, ParseDoesNotAffectDefaultName_393) {

    Detail::TokenStream tokens; // Assuming TokenStream can be default constructed or is not relevant for this test

    exeName.parse("dummy", tokens);

    EXPECT_EQ(exeName.name(), "<executable>");

}



TEST_F(ExeNameTest_SetEmptyString_393, SetWithEmptyStringResultsInEmptyName_393) {

    exeName.set("");

    EXPECT_EQ(exeName.name(), "");

}
