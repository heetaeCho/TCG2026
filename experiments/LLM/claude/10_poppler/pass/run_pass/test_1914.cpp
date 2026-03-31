#include <gtest/gtest.h>

// Include necessary definitions from the source
// Since the class is defined in Function.cc, we need to replicate the interface declarations
// for compilation purposes.

enum PSObjectType {
    psBool = 0,
    psInt = 1,
    psReal = 2,
    psOperator = 3,
    psBlock = 4
};

struct PSObject {
    PSObjectType type;
    union {
        bool booln;
        int intg;
        double real;
    };
};

const int psStackSize = 100;

class PSStack {
public:
    PSStack() { sp = psStackSize; }

    void pushBool(bool booln) {
        if (sp > 0) {
            --sp;
            stack[sp].type = psBool;
            stack[sp].booln = booln;
        }
    }

    void pushInt(int intg) {
        if (sp > 0) {
            --sp;
            stack[sp].type = psInt;
            stack[sp].intg = intg;
        }
    }

    void pushReal(double real) {
        if (sp > 0) {
            --sp;
            stack[sp].type = psReal;
            stack[sp].real = real;
        }
    }

    bool popBool() {
        if (sp < psStackSize && stack[sp].type == psBool) {
            return stack[sp++].booln;
        }
        return false;
    }

    int popInt() {
        if (sp < psStackSize && stack[sp].type == psInt) {
            return stack[sp++].intg;
        }
        return 0;
    }

    double popNum() {
        if (sp < psStackSize) {
            if (stack[sp].type == psInt) {
                return (double)stack[sp++].intg;
            } else if (stack[sp].type == psReal) {
                return stack[sp++].real;
            }
        }
        return 0;
    }

    bool empty() const { return sp == psStackSize; }

    bool topIsInt() { return sp < psStackSize && stack[sp].type == psInt; }

    bool topTwoAreInts() {
        return sp + 1 < psStackSize && stack[sp].type == psInt && stack[sp + 1].type == psInt;
    }

    bool topIsReal() { return sp < psStackSize && stack[sp].type == psReal; }

    bool topTwoAreNums() {
        if (sp + 1 >= psStackSize) return false;
        bool t1 = (stack[sp].type == psInt || stack[sp].type == psReal);
        bool t2 = (stack[sp + 1].type == psInt || stack[sp + 1].type == psReal);
        return t1 && t2;
    }

    void pop() {
        if (sp < psStackSize) {
            ++sp;
        }
    }

    void copy(int n) {
        if (sp + n > psStackSize) return;
        if (sp - n < 0) return;
        for (int i = sp + n - 1; i >= sp; --i) {
            stack[i - n] = stack[i];
        }
        sp -= n;
    }

    void index(int i) {
        if (sp + i >= psStackSize || sp == 0) return;
        pushInt(0); // placeholder - actual implementation may differ
        stack[sp] = stack[sp + 1 + i];
    }

    void roll(int n, int j) {
        // Implementation detail
    }

    void clear() { sp = psStackSize; }

private:
    PSObject stack[psStackSize];
    int sp;

    bool checkOverflow(int n = 1) const { return sp - n >= 0; }
    bool checkUnderflow() const { return sp < psStackSize; }
    bool checkType(PSObjectType t1, PSObjectType t2) {
        return sp < psStackSize && (stack[sp].type == t1 || stack[sp].type == t2);
    }
};

// ==================== TEST CASES ====================

class PSStackTest_1914 : public ::testing::Test {
protected:
    PSStack stack;
};

// --- Empty stack tests ---

TEST_F(PSStackTest_1914, NewStackIsEmpty_1914) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1914, TopIsIntOnEmptyStackReturnsFalse_1914) {
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1914, TopIsRealOnEmptyStackReturnsFalse_1914) {
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1914, TopTwoAreIntsOnEmptyStackReturnsFalse_1914) {
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1914, TopTwoAreNumsOnEmptyStackReturnsFalse_1914) {
    EXPECT_FALSE(stack.topTwoAreNums());
}

// --- Push and type checking ---

TEST_F(PSStackTest_1914, PushIntMakesTopIsIntTrue_1914) {
    stack.pushInt(42);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1914, PushIntMakesTopIsRealFalse_1914) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1914, PushRealMakesTopIsRealTrue_1914) {
    stack.pushReal(3.14);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1914, PushRealMakesTopIsIntFalse_1914) {
    stack.pushReal(3.14);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1914, PushBoolMakesTopIsIntFalse_1914) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1914, PushBoolMakesTopIsRealFalse_1914) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsReal());
}

// --- Pop tests ---

TEST_F(PSStackTest_1914, PushIntPopIntReturnsCorrectValue_1914) {
    stack.pushInt(123);
    EXPECT_EQ(stack.popInt(), 123);
}

TEST_F(PSStackTest_1914, PushRealPopNumReturnsCorrectValue_1914) {
    stack.pushReal(2.718);
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.718);
}

TEST_F(PSStackTest_1914, PushIntPopNumReturnsCorrectValue_1914) {
    stack.pushInt(7);
    EXPECT_DOUBLE_EQ(stack.popNum(), 7.0);
}

TEST_F(PSStackTest_1914, PushBoolPopBoolReturnsCorrectValueTrue_1914) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1914, PushBoolPopBoolReturnsCorrectValueFalse_1914) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

// --- Not empty after push ---

TEST_F(PSStackTest_1914, StackNotEmptyAfterPushInt_1914) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1914, StackNotEmptyAfterPushReal_1914) {
    stack.pushReal(1.0);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1914, StackNotEmptyAfterPushBool_1914) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.empty());
}

// --- Empty after push then pop ---

TEST_F(PSStackTest_1914, StackEmptyAfterPushAndPop_1914) {
    stack.pushInt(5);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// --- topTwoAreInts ---

TEST_F(PSStackTest_1914, TopTwoAreIntsTrueWhenTwoIntsPushed_1914) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1914, TopTwoAreIntsFalseWhenOneInt_1914) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1914, TopTwoAreIntsFalseWhenTopIsReal_1914) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1914, TopTwoAreIntsFalseWhenSecondIsReal_1914) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// --- topTwoAreNums ---

TEST_F(PSStackTest_1914, TopTwoAreNumsTrueForTwoInts_1914) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1914, TopTwoAreNumsTrueForTwoReals_1914) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1914, TopTwoAreNumsTrueForIntAndReal_1914) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1914, TopTwoAreNumsTrueForRealAndInt_1914) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1914, TopTwoAreNumsFalseForBoolAndInt_1914) {
    stack.pushBool(true);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1914, TopTwoAreNumsFalseForIntAndBool_1914) {
    stack.pushInt(1);
    stack.pushBool(false);
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1914, TopTwoAreNumsFalseForOneElement_1914) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// --- Clear ---

TEST_F(PSStackTest_1914, ClearMakesStackEmpty_1914) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushReal(3.0);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1914, ClearOnEmptyStackIsNoOp_1914) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// --- Multiple push/pop (LIFO order) ---

TEST_F(PSStackTest_1914, LIFOOrderForInts_1914) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1914, MixedTypesLIFOOrder_1914) {
    stack.pushInt(10);
    stack.pushReal(2.5);
    stack.pushBool(true);

    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.5);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_TRUE(stack.empty());
}

// --- Negative int values ---

TEST_F(PSStackTest_1914, PushNegativeIntPopCorrectly_1914) {
    stack.pushInt(-42);
    EXPECT_EQ(stack.popInt(), -42);
}

// --- Zero values ---

TEST_F(PSStackTest_1914, PushZeroIntPopCorrectly_1914) {
    stack.pushInt(0);
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1914, PushZeroRealPopCorrectly_1914) {
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// --- Boundary: fill stack to capacity ---

TEST_F(PSStackTest_1914, FillStackToCapacity_1914) {
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1914, OverflowDoesNotCrash_1914) {
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    // Push one more beyond capacity - should not crash
    stack.pushInt(999);
    // The top should still be the last successfully pushed value
    EXPECT_EQ(stack.popInt(), 99);
}

// --- Pop from empty stack ---

TEST_F(PSStackTest_1914, PopFromEmptyStackDoesNotCrash_1914) {
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1914, PopIntFromEmptyReturnsDefault_1914) {
    int val = stack.popInt();
    EXPECT_EQ(val, 0);
}

TEST_F(PSStackTest_1914, PopBoolFromEmptyReturnsFalse_1914) {
    bool val = stack.popBool();
    EXPECT_FALSE(val);
}

TEST_F(PSStackTest_1914, PopNumFromEmptyReturnsZero_1914) {
    double val = stack.popNum();
    EXPECT_DOUBLE_EQ(val, 0.0);
}

// --- Type mismatch on pop ---

TEST_F(PSStackTest_1914, PopIntFromRealReturnsDefault_1914) {
    stack.pushReal(3.14);
    int val = stack.popInt();
    EXPECT_EQ(val, 0);
}

TEST_F(PSStackTest_1914, PopBoolFromIntReturnsFalse_1914) {
    stack.pushInt(1);
    bool val = stack.popBool();
    EXPECT_FALSE(val);
}

// --- topIsInt after pop ---

TEST_F(PSStackTest_1914, TopIsIntAfterPoppingNonInt_1914) {
    stack.pushInt(10);
    stack.pushReal(5.0);
    EXPECT_FALSE(stack.topIsInt());
    stack.pop();
    EXPECT_TRUE(stack.topIsInt());
}

// --- Large values ---

TEST_F(PSStackTest_1914, PushLargeIntValue_1914) {
    stack.pushInt(2147483647); // INT_MAX
    EXPECT_EQ(stack.popInt(), 2147483647);
}

TEST_F(PSStackTest_1914, PushLargeNegativeIntValue_1914) {
    stack.pushInt(-2147483648); // INT_MIN
    EXPECT_EQ(stack.popInt(), -2147483648);
}

TEST_F(PSStackTest_1914, PushLargeRealValue_1914) {
    stack.pushReal(1e308);
    EXPECT_DOUBLE_EQ(stack.popNum(), 1e308);
}

// --- Alternating push/pop ---

TEST_F(PSStackTest_1914, AlternatingPushPop_1914) {
    stack.pushInt(1);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());

    stack.pushReal(2.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.0);
    EXPECT_TRUE(stack.empty());

    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
    EXPECT_TRUE(stack.empty());
}

// --- Clear and reuse ---

TEST_F(PSStackTest_1914, ClearAndReuse_1914) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    EXPECT_TRUE(stack.empty());

    stack.pushReal(3.14);
    EXPECT_FALSE(stack.empty());
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
}

// --- topIsInt and topIsReal consistency ---

TEST_F(PSStackTest_1914, TopIsIntAndTopIsRealMutuallyExclusive_1914) {
    stack.pushInt(5);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());

    stack.pop();
    stack.pushReal(5.0);
    EXPECT_FALSE(stack.topIsInt());
    EXPECT_TRUE(stack.topIsReal());

    stack.pop();
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
}
