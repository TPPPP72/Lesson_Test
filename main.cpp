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
    tester.add(q1);

    // 阅读代码题样例
    CRP q2;
    q2.set_origin_code(R"(#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b;
})");

    // 方案一
    q2.set_real_output("5");
    // 方案二
    q2.set_real_output([]() {
        int a = 2, b = 3;
        std::cout << a + b;
    });
    q2.set_input("2 3");
    q2.set_hint("cin 可以从控制台读入数据");
    q2.set_solution("输入 2 3 ，即 a = 2， b = 3，显然答案为 5");
    tester.add(q2);

    tester.test(); // 开始测试
}