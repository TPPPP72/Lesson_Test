#include "lesson_test.h"
#include <iostream>
#include <memory>

int main()
{
    using namespace Lesson_Test;

    InteractTester tester;
    tester.set_title("测试章节"); // 可选

    // 选择题样例
    {
        std::unique_ptr<MCQ> mcq = std::make_unique<MCQ>();
        mcq->set_question("2^3 + 2^0 = ?");               // 设置题面 必须
        mcq->add_option('A', "9");                        // 添加选项 必须
        mcq->add_option('B', "8");                        // 添加选项 必须
        mcq->add_option('C', "1");                        // 添加选项 必须
        mcq->set_ans('A');                                // 设置答案 必须
        mcq->set_hint("x^0 = 1");                         // 设置提示 可选
        mcq->set_solution("2^3 = 8, 2^0 = 1, 8 + 1 = 9"); // 设置解析 可选
        tester.add_question(*mcq);                        // 向测试器添加该题目 必须
    }

    // 阅读代码题样例
    {
        std::unique_ptr<CRP> crp = std::make_unique<CRP>();
        crp->set_origin_code(R"(#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b;
})"); // 设置源代码 必须

        // 方案一
        crp->set_real_output("5"); // 设置真实输出 必须
        // 方案二
        crp->set_real_output([]() {
            int a = 2, b = 3;
            std::cout << a + b;
        });                                                             // 设置真实输出 必须
        crp->set_input("2 3");                                          // 设置输入 可选
        crp->set_hint("cin 可以从控制台读入数据");                      // 设置提示 可选
        crp->set_solution("输入 2 3 ，即 a = 2， b = 3，显然答案为 5"); // 设置解析 可选
        tester.add_question(*crp);                                      // 向测试器添加该题目 必须
    }

    tester.test(); // 开始测试
}