#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



// Mocking the dependencies

extern "C" {

    __declspec(dllimport) HRESULT SHGetFolderPathA(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPSTR pszPath);

    __declspec(dllimport) UINT GetWindowsDirectoryA(LPCH lpBuffer, UINT uSize);

}



class GlobalParamsWinTest_1982 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary state or mocks

    }



    void TearDown() override {

        // Cleanup any state or mocks

    }

};



TEST_F(GlobalParamsWinTest_1982, GetWindowsFontDir_SuccessfulSHGetFolderPathA_1982) {

    char mockPath[MAX_PATH] = "C:\\Windows\\Fonts";

    EXPECT_CALL(::testing::MockFunction<HRESULT(HWND, int, HANDLE, DWORD, LPSTR)>>(), 

                Call(nullptr, CSIDL_FONTS, nullptr, SHGFP_TYPE_CURRENT, _))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<4>(mockPath, mockPath + sizeof(mockPath)),

            testing::Return(S_OK)));



    std::string result = GetWindowsFontDir();

    EXPECT_EQ(result, "C:\\Windows\\Fonts");

}



TEST_F(GlobalParamsWinTest_1982, GetWindowsFontDir_FailedSHGetFolderPathA_SuccessfulGetWindowsDirectoryA_1982) {

    char mockPath[MAX_PATH] = "C:\\Windows";

    EXPECT_CALL(::testing::MockFunction<HRESULT(HWND, int, HANDLE, DWORD, LPSTR)>>(), 

                Call(nullptr, CSIDL_FONTS, nullptr, SHGFP_TYPE_CURRENT, _))

        .WillOnce(testing::Return(E_FAIL));



    EXPECT_CALL(::testing::MockFunction<UINT(LPCH, UINT)>>(),

                Call(_, MAX_PATH))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<0>(mockPath, mockPath + sizeof(mockPath)),

            testing::Return(MAX_PATH)));



    std::string result = GetWindowsFontDir();

    EXPECT_EQ(result, "C:\\Windows\\fonts");

}



TEST_F(GlobalParamsWinTest_1982, GetWindowsFontDir_FailedSHGetFolderPathA_FailedGetWindowsDirectoryA_1982) {

    char mockPath[MAX_PATH] = "";

    EXPECT_CALL(::testing::MockFunction<HRESULT(HWND, int, HANDLE, DWORD, LPSTR)>>(), 

                Call(nullptr, CSIDL_FONTS, nullptr, SHGFP_TYPE_CURRENT, _))

        .WillOnce(testing::Return(E_FAIL));



    EXPECT_CALL(::testing::MockFunction<UINT(LPCH, UINT)>>(),

                Call(_, MAX_PATH))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<0>(mockPath, mockPath + sizeof(mockPath)),

            testing::Return(0)));



    std::string result = GetWindowsFontDir();

    EXPECT_EQ(result, "");

}



TEST_F(GlobalParamsWinTest_1982, GetWindowsFontDir_EmptySHGetFolderPathA_SuccessfulGetWindowsDirectoryA_1982) {

    char mockPath[MAX_PATH] = "C:\\Windows";

    EXPECT_CALL(::testing::MockFunction<HRESULT(HWND, int, HANDLE, DWORD, LPSTR)>>(), 

                Call(nullptr, CSIDL_FONTS, nullptr, SHGFP_TYPE_CURRENT, _))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<4>(mockPath, mockPath + sizeof(mockPath)),

            testing::Return(S_OK)));



    EXPECT_CALL(::testing::MockFunction<UINT(LPCH, UINT)>>(),

                Call(_, MAX_PATH))

        .WillOnce(testing::DoAll(

            testing::SetArrayArgument<0>(mockPath, mockPath + sizeof(mockPath)),

            testing::Return(MAX_PATH)));



    std::string result = GetWindowsFontDir();

    EXPECT_EQ(result, "C:\\Windows\\Fonts");

}
