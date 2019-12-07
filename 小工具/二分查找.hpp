﻿#pragma once
#include"基本定义/迷你.hpp"
#include"基本定义/模板元.hpp"
#include"小工具/局部函数.hpp"

命名空间 二分查找空间{
    结构体 查找结果{
        自然数 下标;
        U08    找到         : 1;
        U08    左边大于     : 1;
        U08    右边大于     : 1;
        U08    右边到达边界 : 1;

        查找结果() {
            清空(此);
        }
    };

    模板<类 甲>
    结构体 元素{
    私有
        定义 类型名称 类型<甲>::模板 移除<引用标记 | 常量标记>::作为结果 R0;
    公有
        定义 类型名称 假如<类型<R0>::是数值>::模板
            选<R0>::模板
            否则选<R0 常量 &>::作为结果
            类型;
    };

    模板<类 随机访问类型, 类 比较函数>
    查找结果 查找(
        随机访问类型 常量 & 序列,
        自然数 起始下标,
        自然数 长度,
        类型名称 元素<解析类型(序列[0])>::类型 比对值,
        比较函数 回调) {
        查找结果 结果;
        随机访问类型 & 列表 = (随机访问类型 &)序列;
        自然数 左 = 起始下标;
        自然数 中 = 长度  >> 1;
        自然数 右 = 长度;
        整数   比较结果;

        只要(左 + 1 < 右) {
            比较结果 = 回调(列表[中], 比对值);
            若 (比较结果 > 0) {
               右 = 中;
               中 = 自然数((U64(右) + U64(左)) >> 1);
            }
            或 (比较结果 < 0) {
               左 = 中;
               中 = 自然数((U64(右) + U64(左)) >> 1);
            }
            非 {
                结果.下标 = 中;
                结果.找到 = 是;
                回递 结果;
            }
        }

        比较结果 = 回调(列表[左], 比对值);

        若 (比较结果 == 0) {
            结果.下标 = 左;
            结果.找到 = 是;
            回递 结果;
        }

        结果.左边大于 = 比较结果 > 0;
        
        若 (右 == 长度) {
            结果.下标 = 左;
            结果.右边到达边界 = 是;
            回递 结果;
        }

        比较结果 = 回调(列表[右], 比对值);

        若 (比较结果 == 0) {
            结果.下标 = 右;
            结果.找到 = 是;
            回递 结果;
        }

        结果.右边大于 = 比较结果 > 0;
        结果.下标 = 左;
        结果.找到 = 否;
        回递 结果;
    }

    模板<类 序列>
    结构体 被查对象{
    私有
        序列     &     对象;
        定义 类型名称 元素<解析类型(对象[0])>::类型 元素类型;
        定义 局部函数<整数(元素类型 常量 &, 元素类型 常量 &)> 比较类型;
        自然数         长度;
        元素类型       比对值;
        结构体{
            自然数     起始下标;
        }附加;

        推导类型 查找(比较类型 常量 & 回调) {
            查找结果 结果;
            若 (附加.起始下标 >= 长度) {
                结果.找到 = 否;
                回递 结果;
            }
            回递 二分查找空间::查找(对象, 附加.起始下标, 长度, 比对值, 回调 != 空引用 ? 回调 :
                $F[](元素类型 常量 & 左, 元素类型 常量 & 右) {
                回递 ::比较(左, 右);
            });
        }
    公有
        模板<类 序列类型>
        被查对象(序列类型 常量 & 对象, 元素类型 常量 & 比对值) :
            被查对象(对象, 对象->长度, 比对值){
        }
        
        被查对象(序列 常量 & 对象, 自然数 长度, 元素类型 常量 & 比对值) :
            对象((序列 &)对象), 长度(长度), 比对值((元素类型 &)比对值){
            附加.起始下标 = 0; 
        }

        推导类型 & 起始下标(自然数 值) {
            附加.起始下标 = 值;
            回递 此;
        }

        推导类型 运算重载->() {
            回递 此指针;
        }

        自然数 刚好匹配(比较类型 常量 & 回调 = 空引用) {
            推导类型 结果 = 查找(回调);
            回递 结果.找到 ? 结果.下标 : 不存在;
        }

        自然数 向上匹配(比较类型 常量 & 回调 = 空引用) {
            推导类型 结果 = 查找(回调);
            若 (结果.找到) {
                回递 结果.下标;
            }

            //在没有刚好匹配的情况下
            //我们需要找尽可能大且小于目标值的元素
            //右边可能比左边更大 所以右边先比较
            若 (结果.右边到达边界 == 否 && 结果.右边大于 == 否) {
                回递 结果.下标 + 1;
            }
            若 (结果.左边大于 == 否) {
                回递 结果.下标;
            }
            非{
                回递 不存在;
            }
        }

        自然数 向下匹配(比较类型 常量 & 回调 = 空引用) {
            推导类型 结果 = 查找(回调);
            若 (结果.找到) {
                回递 结果.下标;
            }

            //在没有刚好匹配的情况下
            //我们需要找尽可能小且大于目标值的元素
            //左边可能比右边更小 所以左边先比较
            若 (结果.左边大于 != 否) {
                回递 结果.下标;
            }
            若 (结果.右边到达边界 == 否 && 结果.右边大于 != 否) {
                回递 结果.下标 + 1;
            }
            非{
                回递 不存在;
            }
        }
    };
}

模板<类 序列, 类 比对类型>
二分查找空间::被查对象<序列> 二分查找(序列 常量 & 对象, 比对类型 常量 & 比对值){
    回递 二分查找空间::被查对象<序列>(对象, (比对类型 &)比对值);
};

模板<类 序列, 类 比对类型>
二分查找空间::被查对象<序列> 二分查找(序列 常量 & 对象, 自然数 长度, 比对类型 常量 & 比对值){
    回递 二分查找空间::被查对象<序列>(对象, 长度, (比对类型 &)比对值);
};

