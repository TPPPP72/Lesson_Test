#include "lesson_test.h"
#include <iostream>

int main()
{
    using namespace lesson_test;

    InteractTester tester{"测试章节"};

    // 选择题样例
    tester.add({"Which of the following functions or classes can be used for printing (multiple choice)?",
                {{"std::cout", true}, {"printf", true}, {"std::cin", false}},
                "Maybe I should not give it",
                "Absolutely, only std::cout and printf can print text on the screen"});

    // 阅读代码题样例
    CRP q2{R"(#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b;
})"};

    q2.add("2 3", "5", "cin 可以从控制台读取数据", "输入 2 3 ，即 a = 2， b = 3，显然答案为 5");
    q2.add("5 5", []() { std::cout << 5 + 5; }, "", "输入 5 5 ，即 a = 5， b = 5，显然答案为 10");
    tester.add(std::move(q2));

    tester.run(TestMode::examination); // 开始测试
}