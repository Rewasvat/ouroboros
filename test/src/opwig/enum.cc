class MDEnumTest : public MDBaseTest {
protected:
};

TEST_F (MDEnumTest, SimpleEnum) {
    ASSERT_EQ(RunParse("enum name {Sup};"), 0);
    TestScopeChildNums(global_, 0u, 0u, 0u, 0u, 1u);

    vector<string> bases;
    vector<string> values = {"Sup"};
    TestEnum("name", AccessSpecifier::PUBLIC, bases, values);
}

TEST_F (MDEnumTest, AnonymousEnum) {
    RunParseThrow("enum {Sup, Dude};");
}

TEST_F (MDEnumTest, SimpleEnumWithExpressions) {
    ASSERT_EQ(RunParse("enum name {Sup = 0x123, Dude=tralala};"), 0);
    TestScopeChildNums(global_, 0u, 0u, 0u, 0u, 1u);

    vector<string> bases;
    vector<string> values = {"Sup", "Dude"};
    TestEnum("name", AccessSpecifier::PUBLIC, bases, values);
}

TEST_F (MDEnumTest, EnumWithBases) {
    ASSERT_EQ(RunParse("enum name : void {Sup, Dude};"), 0);
    TestScopeChildNums(global_, 0u, 0u, 0u, 0u, 1u);

    vector<string> bases = {"void"};
    vector<string> values = {"Sup", "Dude"};
    TestEnum("name", AccessSpecifier::PUBLIC, bases, values);
}

TEST_F (MDEnumTest, EnumInNamespace) {
    ASSERT_EQ(RunParse("namespace abc { enum name {Sup, Dude}; }"), 0);
    TestScopeChildNums(global_, 0u, 0u, 0u, 1u, 0u);

    auto abc = TestNamespace("abc", AccessSpecifier::PUBLIC, 0u, 0u, 0u, 0u, 1u);
    vector<string> bases;
    vector<string> values = {"Sup", "Dude"};
    TestEnum(abc, "name", AccessSpecifier::PUBLIC, bases, values);
}

TEST_F (MDEnumTest, EnumOutsideNamespace) {
    ASSERT_EQ(RunParse("namespace abc { } enum abc::name {Sup, Dude};"), 0);
    TestScopeChildNums(global_, 0u, 0u, 0u, 1u, 0u);

    auto abc = TestNamespace("abc", AccessSpecifier::PUBLIC, 0u, 0u, 0u, 0u, 1u);
    vector<string> bases;
    vector<string> values = {"Sup", "Dude"};
    TestEnum(abc, "name", AccessSpecifier::PUBLIC, bases, values);
}

TEST_F (MDEnumTest, EnumInAndOutsideNamespace) {
    ASSERT_EQ(RunParse("namespace abc { enum class name; } enum abc::name {Sup, Dude};"), 0);
    TestScopeChildNums(global_, 0u, 0u, 0u, 1u, 0u);

    auto abc = TestNamespace("abc", AccessSpecifier::PUBLIC, 0u, 0u, 0u, 0u, 1u);
    vector<string> bases;
    vector<string> values = {"Sup", "Dude"};
    TestEnum(abc, "name", AccessSpecifier::PUBLIC, bases, values);
}
