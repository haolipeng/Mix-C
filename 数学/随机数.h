﻿#pragma once
#include"基本定义/属性范式.h"
#include"基本定义/模板元.h"

命名空间 随机数空间{
    三体(类 哑元);

    模板<类 哑元>
    结构体 数据{
        卡诺匹斯(哑元);
        U64 X;
        U64 Y;
        数据(U64 Y);
    };

    模板<类 哑元>
    结构体 接口{
        卡诺匹斯(哑元);

        模板<类 甲>
        甲 取值小于(甲 值) {
            回递 取值介于<甲>(类型<甲>::最小值, 值 - 1);
        }

        模板<类 甲>
        甲 取值介于(甲 左闭区间, 甲 右闭区间) {
            定义 类型名称 无符号<空间量(甲)>::类型 类型;
            甲 范围 = 右闭区间 + 1 - 左闭区间;
            回递 甲(类型($O) % 类型(范围) + 类型(左闭区间));
        }
    };

    模板<类 哑元>
    结构体 运算{
        运算型卡诺匹斯(哑元);

        运算重载 U64();
        运算重载 U32();
        运算重载 U16() {
            回递 U16(运算重载 U32());
        }
        运算重载 U08() {
            回递 U08(运算重载 U32());
        }
        运算重载 I64() {
            回递 I64(运算重载 U64());
        }
        运算重载 I32() {
            回递 I32(运算重载 U32());
        }
        运算重载 I16() {
            回递 I16(运算重载 U32());
        }
        运算重载 I08() {
            回递 I08(运算重载 U32());
        }
        运算重载 布尔() {
            回递 运算重载 U32() & 1 != 0;
        }
        运算重载 F64();
        运算重载 F32();
    };
}

结构体 随机数 : 随机数空间::运算<哑元结构>{
    随机数(U64 附加种子 = 魔数): 数据(附加种子){}
私有
    随机数空间::数据<哑元结构> 数据;
};