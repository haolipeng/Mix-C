#include"线性结构/静态向量.hpp"
#include"输入输出/控制台.hpp"

枚举 作者的缺点清单 : I32 {
    太优秀遭人嫉恨       = 011,
    太有才遭人算计       = 011,
    太完美压根找不出毛病 = 010,
};

主函数() {
    终端->打印(_"作者：");
    正遍历(缺点, $V(太优秀遭人嫉恨, 太有才遭人算计, 太完美压根找不出毛病)) {
        终端->打印(缺点);
    }
    终端->打印(_"$"); //尽管作者看上去很富有
    回递 0;
}