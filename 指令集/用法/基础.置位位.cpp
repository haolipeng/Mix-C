﻿#include"指令集/基础.hpp"

定义 U32 楼层指示器;
符号常量 楼层指示器 总楼层数   = 13;
符号常量 楼层指示器 地下室层数 = 2;
符号常量 楼层指示器 总楼掩码 = (1 << 总楼层数) - 1;

楼层指示器 按下(I32 值) {
    回递 1 << 值 + 2;
}
I32 上行(楼层指示器 值, 楼层指示器 当前) {
    楼层指示器 屏蔽比当前楼层低的请求 = 总楼掩码 << (当前 + 地下室层数);
    自然数 下标 = 指令集::最低置位位索引(值 & 屏蔽比当前楼层低的请求);
    若 (下标 == 不存在) {
        回递 1;
    }
    回递 (I32)(下标) - 地下室层数;
}
I32 下行(楼层指示器 值, 楼层指示器 当前) {
    楼层指示器 屏蔽比当前楼层低的请求 = 楼层指示器(总楼掩码) >> (总楼层数 - 当前 - 地下室层数);
    自然数 下标 = 指令集::最低置位位索引(值 & 屏蔽比当前楼层低的请求);
    若 (下标 == 不存在) {
        回递 1;
    }
    回递 (I32)(下标) - 地下室层数;
}
空 清除(楼层指示器 & 值, I32 下标) {
    指令集::位测试后位复位(值, 下标 + 地下室层数);
}

主函数() {
    //故事发生在电梯中
    //起初电梯停在1楼
    楼层指示器 按钮 = 0;
    I32        楼层 = 1;
    
    //当我正要进电梯时，一波人纷纷也进了电梯 并按下楼层号
    //话说2楼的也太懒了
    按钮 |= 按下(9) | 按下(7) | 按下(6) | 按下(2);

    //然后电梯君任劳任怨的拉着这波人上去了
    //不久就到了二楼
    楼层 = 上行(按钮, 楼层);
    清除(按钮, 楼层);

    //突然有人从背后道了声：麻烦按下3楼，（是有点让人头皮些发麻而且心还有点烦）
    按钮 |= 按下(3);

    //3楼那货出去了
    楼层 = 上行(按钮, 楼层);
    清除(按钮, 楼层);

    //电梯开到了6楼
    楼层 = 上行(按钮, 楼层);
    清除(按钮, 楼层);

    //电梯开到了7楼
    楼层 = 上行(按钮, 楼层);
    清除(按钮, 楼层);

    //某些人错过了6楼
    //电梯是不会鸟TA的，哈哈，大快人心
    按钮 |= 按下(6);

    //到9楼了，该下行了
    楼层 = 上行(按钮, 楼层);
    清除(按钮, 楼层);

    //电梯开到了6楼
    //全剧终
    楼层 = 下行(按钮, 楼层);
    清除(按钮, 楼层);

    //乖巧的电梯就应该在上班前待在1楼
    楼层 = 下行(按钮, 楼层);
    清除(按钮, 楼层);
    回递 0;
}
