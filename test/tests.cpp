// Copyright 2026 KashinGS
#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataTest, Test1_InitialStateIsOff) {
    Automata a;
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(AutomataTest, Test2_OnTransitionsToWait) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, Test3_FirstCoinTransitionsToAccept) {
    Automata a;
    a.on();
    a.coin(10);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, Test4_SubsequentCoinStaysInAccept) {
    Automata a;
    a.on();
    a.coin(10);
    a.coin(20);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, Test5_ChoiceTransitionsToCheck) {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(1);
    EXPECT_EQ(a.getState(), STATES::CHECK);
}

TEST(AutomataTest, Test6_CheckReturnsTrueWhenEnoughMoney) {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(3);
    EXPECT_TRUE(a.check());
}

TEST(AutomataTest, Test7_CheckReturnsFalseWhenNotEnoughMoney) {
    Automata a;
    a.on();
    a.coin(20);
    a.choice(4);
    EXPECT_FALSE(a.check());
}

TEST(AutomataTest, Test8_CookTransitionsToCook) {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(2);
    a.cook();
    EXPECT_EQ(a.getState(), STATES::COOK);
}

TEST(AutomataTest, Test9_FinishTransitionsToWait) {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(2);
    a.cook();
    a.finish();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, Test10_CancelFromAcceptReturnsMoneyAndGoesToWait) {
    Automata a;
    a.on();
    a.coin(100);
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
    a.coin(10);
    a.choice(4);
    EXPECT_FALSE(a.check());
}

TEST(AutomataTest, Test11_CancelFromCheckGoesToWait) {
    Automata a;
    a.on();
    a.coin(30);
    a.choice(1);
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, Test12_ChoiceFailsInWait) {
    Automata a;
    a.on();
    EXPECT_FALSE(a.choice(1));
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, Test13_OffWorksOnlyFromWait) {
    Automata a;
    a.on();
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(AutomataTest, Test14_CookFailsWhenNotEnoughMoney) {
    Automata a;
    a.on();
    a.coin(20);
    a.choice(3);
    a.cook();
    EXPECT_EQ(a.getState(), STATES::CHECK);
}

TEST(AutomataTest, Test15_CancelWithNoMoneyDoesNothing) {
    Automata a;
    a.on();
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
    a.coin(5);
    a.choice(1);
    EXPECT_FALSE(a.check());
}
