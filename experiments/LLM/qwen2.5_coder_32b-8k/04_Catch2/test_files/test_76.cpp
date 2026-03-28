#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exception>



namespace Catch { namespace Detail {

    template<typename T> 

    std::enable_if_t< !std::is_enum<T>::value && std::is_base_of<std::exception, T>::value, std::string> convertUnstreamable(T const& ex) {

        return ex.what();

    }

} }



class ExceptionMock : public std::exception {

public:

    explicit ExceptionMock(const char* message) : msg_(message) {}

    const char* what() const noexcept override { return msg_; }

private:

    const char* msg_;

};



TEST_F(ConvertUnstreamableTest_76, NormalOperation_76) {

    ExceptionMock ex("Normal exception message");

    EXPECT_EQ(Catch::Detail::convertUnstreamable(ex), "Normal exception message");

}



TEST_F(ConvertUnstreamableTest_76, BoundaryConditions_EmptyMessage_76) {

    ExceptionMock ex("");

    EXPECT_EQ(Catch::Detail::convertUnstreamable(ex), "");

}



TEST_F(ConvertUnstreamableTest_76, ExceptionalCase_LongMessage_76) {

    const char* long_message = "This is a very long exception message that should be handled correctly by the convertUnstreamable function.";

    ExceptionMock ex(long_message);

    EXPECT_EQ(Catch::Detail::convertUnstreamable(ex), long_message);

}



// Since there are no external collaborators involved in this function, we do not need to use Google Mock for any verification of interactions.
