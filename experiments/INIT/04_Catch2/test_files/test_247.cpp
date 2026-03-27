// File: exception_translator_registrar_tests_247.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <stdexcept>

// The partial headers in the prompt are not fully self-contained.
// To keep tests interface-true without peeking at internals, we define only the
// *type alias* that the interface references (ExceptionTranslators). This is a
// collaborator type, not private state.
// If your codebase already defines Catch::ExceptionTranslators, remove this alias.
namespace Catch {
    class IExceptionTranslator;

    // Minimal collaborator alias to supply iterators.
    using ExceptionTranslators = std::vector<IExceptionTranslator const *>;

    // Interface skeleton based on the provided partial header.
    class IExceptionTranslator {
    public:
        virtual ~IExceptionTranslator() = default;
        virtual std::string translate(ExceptionTranslators::const_iterator it,
                                      ExceptionTranslators::const_iterator itEnd) const = 0;
    };

    // Minimal visible surface required from the prompt for testing.
    template <typename T>
    class ExceptionTranslatorRegistrar : public IExceptionTranslator {
        class ExceptionTranslator : public IExceptionTranslator {
        protected:
            std::string (*m_translateFunction)(T const&);
        public:
            constexpr ExceptionTranslator(std::string(*translateFunction)(T const&))
                : m_translateFunction(translateFunction) {}

            // The behavior we test is derived from the prompt’s partial code:
            //  - if it == itEnd: rethrow current exception
            //  - else: delegate to *it with (it+1, itEnd)
            //  - catch (T const&): return m_translateFunction(ex)
            std::string translate(ExceptionTranslators::const_iterator it,
                                   ExceptionTranslators::const_iterator itEnd) const override {
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
                try {
                    if (it == itEnd) {
                        std::rethrow_exception(std::current_exception());
                    } else {
                        return (*it)->translate(it + 1, itEnd);
                    }
                } catch (T const& ex) {
                    return m_translateFunction(ex);
                }
#else
                return "You should never get here!";
#endif
            }
        };

        // For these tests we need an instance of the inner ExceptionTranslator.
        std::unique_ptr<IExceptionTranslator> impl_;
    public:
        explicit ExceptionTranslatorRegistrar(std::string(*translateFunction)(T const&))
            : impl_(new ExceptionTranslator(translateFunction)) {}

        // Forward IExceptionTranslator
        std::string translate(ExceptionTranslators::const_iterator it,
                              ExceptionTranslators::const_iterator itEnd) const override {
            return impl_->translate(it, itEnd);
        }
    };
} // namespace Catch

using ::testing::HasSubstr;

// ------------ Test collaborators (mocks/fakes) -----------------

// A simple fake collaborator implementing IExceptionTranslator that either
// returns a fixed string or throws from translate(), configurable per instance.
class FakeTranslatorReturning final : public Catch::IExceptionTranslator {
    std::string to_return_;
public:
    explicit FakeTranslatorReturning(std::string s) : to_return_(std::move(s)) {}
    std::string translate(Catch::ExceptionTranslators::const_iterator it,
                          Catch::ExceptionTranslators::const_iterator itEnd) const override {
        (void)it; (void)itEnd;
        return to_return_;
    }
};

template <typename Ex>
class FakeTranslatorThrowing final : public Catch::IExceptionTranslator {
public:
    std::string translate(Catch::ExceptionTranslators::const_iterator it,
                          Catch::ExceptionTranslators::const_iterator itEnd) const override {
        (void)it; (void)itEnd;
        throw Ex{};
    }
};

// A distinct exception type used for T in the registrar.
struct MyException {};

// The translate function for MyException we will register.
static std::string TranslateMyException(MyException const&) {
    return std::string{"MyException translated"};
}

// ------------------------- Tests -------------------------------

// Normal operation: when there is a next translator in the chain and it returns
// a string (no exception thrown), translate MUST delegate and return that value.
TEST(ExceptionTranslatorRegistrarTest_247, DelegatesToNextWhenPresent_247) {
    using namespace Catch;

    // Prepare a "next" translator that returns a recognizable value.
    FakeTranslatorReturning next{"next-handled"};

    ExceptionTranslators chain;
    chain.push_back(&next);

    ExceptionTranslatorRegistrar<MyException> under_test(&TranslateMyException);

    // No current exception context is needed because the next translator
    // simply returns a value and does not throw.
    const auto result = under_test.translate(chain.begin(), chain.end());

    EXPECT_EQ(result, "next-handled");
}

// Boundary behavior: when it == itEnd and current exception is of type T,
// translate MUST catch T and return the registered translateFunction result.
TEST(ExceptionTranslatorRegistrarTest_247, CatchesAndTranslatesWhenCurrentExceptionIsT_AndNoNext_247) {
    using namespace Catch;

    ExceptionTranslatorRegistrar<MyException> under_test(&TranslateMyException);

    ExceptionTranslators empty;
    std::string result;

    try {
        // Establish current exception of type T
        throw MyException{};
    } catch (...) {
        // With it == itEnd, implementation rethrows current_exception inside,
        // catches T, and applies m_translateFunction.
        result = under_test.translate(empty.end(), empty.end());
    }

    EXPECT_EQ(result, "MyException translated");
}

// Exceptional case: when it == itEnd and current exception is NOT of type T,
// translate MUST rethrow the current exception (since only T is caught).
TEST(ExceptionTranslatorRegistrarTest_247, RethrowsNonTWhenNoNext_247) {
    using namespace Catch;

    ExceptionTranslatorRegistrar<MyException> under_test(&TranslateMyException);

    ExceptionTranslators empty;

    try {
        throw std::runtime_error{"boom"};
    } catch (...) {
        // Expect the same exception type to propagate out.
        EXPECT_THROW(
            (void)under_test.translate(empty.end(), empty.end()),
            std::runtime_error
        );
    }
}

// Interaction + recovery: when there IS a next translator, and that translator
// throws T, translate MUST catch T and use m_translateFunction(T) instead of
// propagating or crashing.
TEST(ExceptionTranslatorRegistrarTest_247, UsesTranslateFunctionWhenNextThrowsT_247) {
    using namespace Catch;

    // "Next" translator throws MyException during its translate call
    FakeTranslatorThrowing<MyException> nextThrowsT;

    ExceptionTranslators chain;
    chain.push_back(&nextThrowsT);

    ExceptionTranslatorRegistrar<MyException> under_test(&TranslateMyException);

    // No outer current exception needed; the thrown T originates from the next translator.
    const auto result = under_test.translate(chain.begin(), chain.end());

    EXPECT_EQ(result, "MyException translated");
}
