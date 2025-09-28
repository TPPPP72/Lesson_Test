#include "lesson_test.h"
#include <iostream>

int main()
{
    using namespace Lesson_Test;

    InteractTester tester{"测试章节"};

    // 选择题样例
    MCQ q1;
    q1.set_question("2 ^ 3 + 2 ^ 0 = ?");
    q1.add_option("9", true);
    q1.add_option("8");
    q1.add_option("1");
    q1.set_hint("x ^ 0 = 1");
    q1.set_solution("2 ^ 3 = 8, 2 ^ 0 = 1, 8 + 1 = 9");
    tester.add(std::move(q1));

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

    tester.run(); // 开始测试
}