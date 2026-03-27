#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace Clara;

using namespace Detail;



class OptTest_665 : public ::testing::Test {

protected:

    bool dummyFlag = false;

};



TEST_F(OptTest_665, Validate_NoOptionsSupplied_665) {

    Opt opt(dummyFlag);

    auto result = opt.validate();

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "No options supplied to Opt");

}



TEST_F(OptTest_665, Validate_EmptyOptionName_665) {

    Opt opt(dummyFlag);

    opt[""];

    auto result = opt.validate();

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "Option name cannot be empty");

}



#ifdef CATCH_PLATFORM_WINDOWS

TEST_F(OptTest_665, Validate_OptionNameDoesNotStartWithDashOrSlash_Windows_665) {

    Opt opt(dummyFlag);

    opt["a"];

    auto result = opt.validate();

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "Option name must begin with '-' or '/'");

}



TEST_F(OptTest_665, Validate_OptionNameStartsWithDash_Windows_665) {

    Opt opt(dummyFlag);

    opt["-a"];

    auto result = opt.validate();

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(OptTest_665, Validate_OptionNameStartsWithSlash_Windows_665) {

    Opt opt(dummyFlag);

    opt["/a"];

    auto result = opt.validate();

    EXPECT_TRUE(static_cast<bool>(result));

}

#else

TEST_F(OptTest_665, Validate_OptionNameDoesNotStartWithDash_Linux_665) {

    Opt opt(dummyFlag);

    opt["a"];

    auto result = opt.validate();

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "Option name must begin with '-'");

}



TEST_F(OptTest_665, Validate_OptionNameStartsWithDash_Linux_665) {

    Opt opt(dummyFlag);

    opt["-a"];

    auto result = opt.validate();

    EXPECT_TRUE(static_cast<bool>(result));

}

#endif



TEST_F(OptTest_665, Validate_MultipleValidOptions_665) {

    Opt opt(dummyFlag);

    opt["-a"]["-b"];

    auto result = opt.validate();

    EXPECT_TRUE(static_cast<bool>(result));

}



TEST_F(OptTest_665, Validate_ValidOptionWithHint_665) {

    Opt opt([](bool){}, StringRef("hint"));

    opt["-a"];

    auto result = opt.validate();

    EXPECT_TRUE(static_cast<bool>(result));

}
