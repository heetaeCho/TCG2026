// GeneratorWrapper_get_tests_312.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

using ::testing::ReturnRef;
using ::testing::Times;
using ::testing::NiceMock;

// ---- Minimal interface scaffolding based on the provided header snippets ----
namespace Catch { namespace Generators {

template <typename T>
struct IGenerator {
    virtual ~IGenerator() = default;
    virtual T const& get() const = 0;
    virtual bool next() = 0;
};

template <typename T>
using GeneratorPtr = std::unique_ptr<IGenerator<T>>;

// Declarations/definitions match the provided interface and partial code.
template <typename T>
class GeneratorWrapper {
private:
    GeneratorPtr<T> m_generator;

public:
    explicit GeneratorWrapper(IGenerator<T>* generator) : m_generator(generator) {}
    explicit GeneratorWrapper(GeneratorPtr<T> generator) : m_generator(std::move(generator)) {}

    // From Partial Code
    T const& get() const { return m_generator->get(); }

    // Declared in Known Dependencies (not used in these tests)
    bool next();
};

}} // namespace Catch::Generators

// ---- Mock collaborator for IGenerator<int> ----
namespace Catch { namespace Generators {

class MockIntGenerator : public IGenerator<int> {
public:
    MOCK_METHOD(int const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};

}} // namespace Catch::Generators

using Catch::Generators::GeneratorWrapper;
using Catch::Generators::MockIntGenerator;

// -----------------------------------------------------------------------------

// Normal operation: get() forwards to underlying generator (raw-pointer ctor).
TEST(GeneratorWrapperTest_312, GetForwardsValue_RawPtrCtor_312) {
    auto* mock = new NiceMock<MockIntGenerator>(); // owned by wrapper
    int value = 42;

    EXPECT_CALL(*mock, get()).Times(1).WillOnce(ReturnRef(value));
    EXPECT_CALL(*mock, next()).Times(0); // get() should not advance

    GeneratorWrapper<int> wrapper(mock);

    const int& out = wrapper.get();
    EXPECT_EQ(&out, &value); // reference semantics preserved
    EXPECT_EQ(out, 42);
}

// Normal operation: get() forwards to underlying generator (unique_ptr ctor).
TEST(GeneratorWrapperTest_312, GetForwardsValue_UniquePtrCtor_312) {
    auto mock = std::make_unique<NiceMock<MockIntGenerator>>();
    int value = 7;

    EXPECT_CALL(*mock, get()).Times(1).WillOnce(ReturnRef(value));
    EXPECT_CALL(*mock, next()).Times(0);

    GeneratorWrapper<int> wrapper(std::move(mock));

    const int& out = wrapper.get();
    EXPECT_EQ(&out, &value);
    EXPECT_EQ(out, 7);
}

// Boundary-ish behavior: multiple get() calls do not call next() and keep returning the same referenced object.
TEST(GeneratorWrapperTest_312, MultipleGetCalls_DoNotAdvance_AndReturnSameRef_312) {
    auto mock = std::make_unique<NiceMock<MockIntGenerator>>();
    int value = 100;

    EXPECT_CALL(*mock, get()).Times(2).WillRepeatedly(ReturnRef(value));
    EXPECT_CALL(*mock, next()).Times(0);

    GeneratorWrapper<int> wrapper(std::move(mock));

    const int* first_addr  = &wrapper.get();
    const int* second_addr = &wrapper.get();

    EXPECT_EQ(first_addr, second_addr);
    EXPECT_EQ(*first_addr, 100);
    EXPECT_EQ(*second_addr, 100);
}

// Const-correctness: get() is callable on a const wrapper and forwards correctly.
TEST(GeneratorWrapperTest_312, GetIsConst_AndForwardsOnConstWrapper_312) {
    auto mock = std::make_unique<NiceMock<MockIntGenerator>>();
    int value = -5;

    EXPECT_CALL(*mock, get()).Times(1).WillOnce(ReturnRef(value));
    EXPECT_CALL(*mock, next()).Times(0);

    const GeneratorWrapper<int> wrapper(std::move(mock));
    const int& out = wrapper.get();

    EXPECT_EQ(&out, &value);
    EXPECT_EQ(out, -5);
}

// Observable reference semantics: if the underlying value changes between calls, get() reflects the change
// (since it returns a const reference from the collaborator).
TEST(GeneratorWrapperTest_312, GetReflectsUnderlyingChangesAcrossCalls_312) {
    auto mock = std::make_unique<NiceMock<MockIntGenerator>>();
    int value = 1;

    // First returns ref to value==1, then after we mutate `value`, second get() returns the updated ref.
    EXPECT_CALL(*mock, get()).Times(2).WillRepeatedly(ReturnRef(value));
    EXPECT_CALL(*mock, next()).Times(0);

    GeneratorWrapper<int> wrapper(std::move(mock));

    const int& first = wrapper.get();
    EXPECT_EQ(first, 1);

    value = 9; // mutate underlying storage
    const int& second = wrapper.get();
    EXPECT_EQ(second, 9);

    // Addresses remain identical since both refs target the same underlying object.
    EXPECT_EQ(&first, &second);
}
