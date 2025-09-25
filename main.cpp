#include "lesson_test.h"
#include <iostream>

int main()
{
    using namespace Lesson_Test;

    InteractTester tester;
    tester.set_title("测试章节");

    MCQ mcq;
    CRP crp;
    mcq.set_question("以下哪个选项能够正常打印Hello,World？");
    mcq.add_option('A', R"(#include <iostream>

int main(){
    std::cout << "Hello,World";
})");
    mcq.set_ans('A');
    tester.add_question(mcq);

    crp.set_origin_code(R"(#include <stdio.h>

int main(){
    printf("Hello\n");
    printf("World");
})");
    crp.set_real_output([]() { std::cout << "Hello\nWorld"; });
    tester.add_question(crp);

    crp.set_origin_code(R"(#include <stdio.h>

int main(){
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", a + b);
})");
    crp.set_input(R"(2 3)");
    crp.set_real_output([]() { std::cout << "5"; });
    tester.add_question(crp);

    MCQ *m = new MCQ();
    m->set_question("哈基米叮咚鸡");
    m->add_option('A', "你说得对但是");
    m->add_option('B', "胖宝宝");
    m->add_option('C', "说的道理");
    m->set_ans('B');
    tester.add_question(*m);
    delete m;

    tester.test();
}