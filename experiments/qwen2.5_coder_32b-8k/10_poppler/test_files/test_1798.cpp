#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <optional>

#include <string>

#include <filesystem>



using namespace std::filesystem;



// Mocking getenv function

char* mock_getenv(const char* name) {

    if (strcmp(name, "APPDATA") == 0) return const_cast<char*>("C:\\MockAppData");

    if (strcmp(name, "HOME") == 0) return const_cast<char*>("/mock/home");

    return nullptr;

}



// Fixture to override getenv and restore it after tests

class NSSCryptoSignBackendTest_1798 : public ::testing::Test {

protected:

    void SetUp() override {

        original_getenv = std::exchange(getenv_func, mock_getenv);

    }



    void TearDown() override {

        getenv_func = original_getenv;

    }



private:

    char* (*original_getenv)(const char*) = nullptr;

};



extern "C" {

    char* (*getenv_func)(const char*) = getenv;

    char* getenv(const char* name) {

        return getenv_func(name);

    }

}



// Test normal operation on Windows

TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_Normal_Windows_1798) {

    // Setup

    const std::string expectedPath = "C:\\MockAppData\\Mozilla\\Firefox\\Profiles\\default.default";

    create_directories(expectedPath + "\\certs");

    create_directory_symlink("certs", expectedPath + "\\cert9.db");



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, expectedPath);



    // Cleanup

    remove_all(expectedPath);

}



// Test normal operation on Unix-like systems

TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_Normal_Unix_1798) {

    // Setup

    const std::string expectedPath = "/mock/home/.mozilla/firefox/default.default";

    create_directories(expectedPath + "/certs");

    create_directory_symlink("certs", expectedPath + "/cert9.db");



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, expectedPath);



    // Cleanup

    remove_all(expectedPath);

}



// Test when no default profile is found on Windows

TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_NoDefault_Windows_1798) {

    // Setup

    const std::string basePath = "C:\\MockAppData\\Mozilla\\Firefox\\Profiles\\";

    create_directories(basePath + "other.default");

    create_directory_symlink("certs", basePath + "other.default/cert9.db");



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_FALSE(result.has_value());



    // Cleanup

    remove_all(basePath);

}



// Test when no default profile is found on Unix-like systems

TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_NoDefault_Unix_1798) {

    // Setup

    const std::string basePath = "/mock/home/.mozilla/firefox/";

    create_directories(basePath + "other.default");

    create_directory_symlink("certs", basePath + "other.default/cert9.db");



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_FALSE(result.has_value());



    // Cleanup

    remove_all(basePath);

}



// Test when APPDATA or HOME environment variables are not set

TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_NoEnvVar_Windows_1798) {

    // Setup

    getenv_func = [](const char*) -> char* { return nullptr; };



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_FALSE(result.has_value());

}



TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_NoEnvVar_Unix_1798) {

    // Setup

    getenv_func = [](const char*) -> char* { return nullptr; };



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_FALSE(result.has_value());

}



// Test when the latest profile directory has no cert9.db file on Windows

TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_NoCert9db_Windows_1798) {

    // Setup

    const std::string basePath = "C:\\MockAppData\\Mozilla\\Firefox\\Profiles\\";

    create_directories(basePath + "default.default");



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_FALSE(result.has_value());



    // Cleanup

    remove_all(basePath);

}



// Test when the latest profile directory has no cert9.db file on Unix-like systems

TEST_F(NSSCryptoSignBackendTest_1798, GetDefaultFirefoxCertDB_NoCert9db_Unix_1798) {

    // Setup

    const std::string basePath = "/mock/home/.mozilla/firefox/";

    create_directories(basePath + "default.default");



    // Act

    auto result = getDefaultFirefoxCertDB();



    // Assert

    EXPECT_FALSE(result.has_value());



    // Cleanup

    remove_all(basePath);

}
