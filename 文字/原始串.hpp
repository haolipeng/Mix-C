﻿#pragma once
#include"文字/万国码.hpp"
#include"小工具/局部函数.hpp"
#include"基本定义/迷你.hpp"
#include"基本定义/属性范式.hpp"
#define  _                 (__原始串) u""

定义 局部函数<文字 * (自然数)> 分配回调;

命名空间{
    比较回调<文字> 忽略大小写 = $C(文字) {
        回递 整数(万国码(左)->小写格式) - 整数(万国码(右)->小写格式);
    };
}

结构体 字符串;

命名空间 原始串空间{
    三体(类 类型);
    模板<类 类型> 结构体 数据{
        卡诺匹斯(类型);
        自然数   长度;
        文字   * 元素;
        符号常量 数据(文字 常量 * 串) {
            元素 = (文字 *)串;
            只要(串[0]) {
                串++;
            }
            长度 = 串 - 元素;
        }
        数据() : 元素((文字 *)u""), 长度(0) {}
        数据(文字 常量 * 元素, 自然数 个数) :
            长度(个数), 元素((文字 *)元素) {
        }
    };
    
    模板<类 原始串> 结构体 接口{
        卡诺匹斯(原始串);
        原始串 左填充(自然数 填充长度, 分配回调 回调) {
            回递 左填充(填充长度, ' ', 回调);
        }
        
        原始串 左填充(自然数 填充长度, 文字 填充符, 分配回调 回调){
            文字 * 缓冲区 = 回调(填充长度 + 长度);
            填充<文字>(缓冲区, 填充符, 填充长度);
            复制<文字>(缓冲区 + 填充长度, 元素, 长度);
            回递 原始串(缓冲区, 填充长度 + 长度);
        }
        
        原始串 右填充(自然数 填充长度, 分配回调 回调) {
            回递 右填充(填充长度, ' ', 回调);
        }
        
        原始串 右填充(自然数 填充长度, 文字 填充符, 分配回调 回调){
            文字 * 缓冲区 = 回调(填充长度 + 长度);
            复制<文字>(缓冲区, 元素, 长度);
            填充<文字>(缓冲区 + 长度, 填充符, 填充长度);
            回递 原始串(缓冲区, 填充长度 + 长度);
        }
        
        原始串 两端填充(自然数 左填充长度, 自然数 右填充长度, 分配回调 回调) {
            回递 两端填充(左填充长度, 右填充长度, ' ', 回调);
        }

        原始串 两端填充(自然数 左填充长度, 自然数 右填充长度, 文字 填充符, 分配回调 回调){
            自然数 总长 = 左填充长度 + 右填充长度 + 长度;
            文字 * 缓冲区 = 回调(总长);
            填充<文字>(缓冲区, 填充符, 左填充长度);
            复制<文字>(缓冲区 + 左填充长度, 元素, 长度);
            填充<文字>(缓冲区 + 左填充长度 + 长度, 填充符, 右填充长度);
            回递 原始串(缓冲区, 总长);
        }

        #define $F1                                                   \
            自然数 本串宽度 = $I.总宽;                                \
            自然数 填充宽度;                                          \
            自然数 填充长度;                                          \
            自然数 左填充长度 = 0;                                    \
            自然数 右填充长度 = 0;                                    \
            自然数 总长;                                              \
            原始串 结果;                                              \
            布尔   存在半字;                                          \
            文字 * 缓冲区;                                            \
                                                                      \
            若 (本串宽度 >= 总宽){                                    \
                缓冲区 = 回调(长度);                                  \
                总长 = 长度;                                          \
                复制<文字>(缓冲区, 元素, 长度);                       \
                结果 = 原始串(缓冲区, 总长);                          \
            }                                                         \
            非{                                                       \
                填充宽度 = 总宽 - 本串宽度;                           \
                存在半字 = 填充宽度 % 万国码(填充符)->宽度;           \
                填充长度 = 填充宽度 / 万国码(填充符)->宽度 + 存在半字;

        #define $F2(填充,半字位置)                                    \
            $F1 结果 = 填充(填充长度, 填充符, 回调);                  \
                                                                      \
                若 (存在半字){                                        \
                    结果[半字位置] = ' ';                             \
                }                                                     \
            $                                                         \
            回递 结果;

        原始串 左对齐(自然数 总宽, 文字 填充符, 分配回调 回调) {
            $F2(右填充, 长度);
        }

        原始串 右对齐(自然数 总宽, 文字 填充符, 分配回调 回调) {
            $F2(左填充, 填充长度 - 1);
        }

        原始串 居中对齐(自然数 总宽, 文字 填充符, 分配回调 回调){
            $F1 左填充长度 = 填充长度 / 2;
                右填充长度 = 填充长度 - 左填充长度;
                结果 = 两端填充(左填充长度, 右填充长度, 填充符, 回调);

                若 (存在半字){
                    结果[左填充长度 + 长度] = ' ';
                }
            $
            回递 结果;
        }

        #undef  $F1
        #undef  $F2
        #define 校准(数值,...)  若 (数值 < 0) { 数值 = 长度 - -数值 __VA_ARGS__; }

        模板<类 甲, 类 乙>
        原始串 截取(甲 常量 & 起始下标, 乙 常量 & 结束下标, 分配回调 回调) {
            回递 截取((整数)(甲 &)起始下标, (整数)(乙 &)结束下标, 回调);
        }

        原始串 截取(整数 起始下标, 整数 结束下标, 分配回调 回调) {
            若 (长度 == 0) {
                回递 原始串();
            }
            校准(起始下标);
            校准(结束下标);

            自然数 目标长度;
            文字 * 缓冲区;
            文字 * 临时;

            若 (起始下标 <= 结束下标){
                目标长度 = 自然数(结束下标 - 起始下标 + 1);
                临时 = 缓冲区 = 回调(目标长度);
                只要(起始下标 <= 结束下标) {
                    临时[0] = 元素[起始下标];
                    临时 += 1;
                    起始下标 += 1;
                }
            }
            非{
                目标长度 = 自然数(起始下标 - 结束下标 + 1);
                临时 = 缓冲区 = 回调(目标长度);
                只要(起始下标 >= 结束下标) {  
                    临时[0] = 元素[起始下标];
                    临时 += 1;
                    起始下标 -= 1;
                }
            }
            回递 原始串(缓冲区, 目标长度);
        }

        模板<类 甲>
        原始串 插入(甲 常量 & 下标, 原始串 值, 分配回调 回调) {
            回递 插入((整数)(甲 &)下标, 值, 回调);
        }

        原始串 插入(整数 下标, 原始串 值, 分配回调 回调) {
            校准(下标, +1);

            自然数 目标长度 = 长度 + 值->长度;
            文字 * 缓冲区 = 回调(目标长度);

            复制<文字>(缓冲区, 元素, 下标);
            复制<文字>(缓冲区 + 下标, 值->元素, 值->长度);
            复制<文字>(缓冲区 + 下标 + 值->长度, 元素 + 下标, 长度 - 下标);
            回递 原始串(缓冲区, 目标长度);
        }

        原始串 反序(分配回调 回调) {
            回递 截取(-1, 0, 回调);
        }

        模板<类 ... 参数>
        原始串 清除串首(文字 字符, 参数 常量 & ... 列表) {
            隐式值<文字> 标记组[] = { 字符, 列表..., '\0' };
            原始串 标记((文字 *)标记组, 1 + 参数数(列表));
            自然数 I = 0;

            循环(; I < 长度; I++) {
                若 (标记->存在(元素[I]) == 否) {
                    跳出;
                }
            }
            回递 原始串(元素, 长度) + I;
        }

        模板<类 ... 参数>
        原始串 清除串尾(文字 字符, 参数 常量 & ... 列表) {
            隐式值<文字> 标记组[] = { 字符, 列表..., '\0' };
            原始串 标记((文字 *)标记组, 1 + 参数数(列表));
            自然数 I = 长度;

            循环(; I > 0; I--) {
                若 (标记->存在(元素[I - 1]) == 否) {
                    跳出;
                }
            }
            回递 原始串(元素, I);
        }

        #undef 校准下标

        模板<类 格式化回调> 
        原始串 元素变换(格式化回调 格式化, 分配回调 分配) {
            文字 * 缓冲区 = 分配(长度);
            循环(自然数 下标 = 0; 下标 < 长度; 下标++) {
                缓冲区[下标] = 格式化(元素[下标]);
            }
            回递 原始串(缓冲区, 长度);
        }

        自然数 正向匹配(文字 比对值, 比较回调<文字> 回调 = 默认比较<文字>()) {
            循环(自然数 下标 = 0; 下标 < 长度; 下标++){
                若 (回调(元素[下标], 比对值) == 0){
                    回递 下标;
                }
            }
            回递 不存在;
        }
        
        模板<类 比较回调, 类 匹配回调>
        自然数 正向匹配模板(原始串 子串, 匹配回调 匹配器, 比较回调 比较){
            自然数   不匹配下标 = 0;
            自然数   匹配下标;
            自然数   下标;
            推导类型 源串 = 原始串(元素, 长度);

                只要((匹配下标 = 匹配器(源串, 子串[不匹配下标])) != 不存在) {
                源串 += 匹配下标 - 不匹配下标;

                若 (源串->长度 < 子串->长度){
                    回递 不存在;
                }

                下标 = 0;

                只要(是) {
                    若 (下标 == 子串->长度){
                        回递 源串->元素 - 元素;
                    }
                    若 (比较(源串[下标], 子串[下标]) != 0) {
                        不匹配下标 = 下标;
                        跳出;
                    }
                    下标++;
                }
            }
            回递 不存在;
        }

        自然数 正向匹配(原始串 比对值, 比较回调<文字> 回调 = 默认比较<文字>()) {
            回递 正向匹配模板(比对值,
                [=](原始串 源串, 文字 值){
                    回递 源串->正向匹配(值, 回调);
                }, 回调
            );
        }

        自然数 正向匹配(原始串 比对值, 局部函数<布尔(自然数)> 当匹配到) {
            回递 正向匹配(比对值, 默认比较<文字>(), 当匹配到);
        }

        自然数 正向匹配(原始串 比对值, 比较回调<文字> 回调, 局部函数<布尔(自然数)> 当匹配到) {
            自然数 下标 = 0;
            自然数 当前下标 = 0;
            自然数 次数 = 0;
            原始串 临时(元素, 长度);

            只要((下标 = 临时->正向匹配(比对值, 回调)) != 不存在) {
                当前下标 += 下标;
                次数 += 1;
                临时 += 下标 + 比对值->长度;

                若 (当匹配到(当前下标) == 退出){
                    跳出;
                }
                当前下标 += 比对值->长度;
            }
            回递 次数;
        }
        
        自然数 反向匹配(文字 比对值, 比较回调<文字> 回调 = 默认比较<文字>()) {
            循环(自然数 下标 = 长度; 下标-- > 0; ){
                若 (回调(元素[下标], 比对值) == 0){
                    回递 下标;
                }
            }
            回递 不存在;
        }
        
        模板<类 比较回调, 类 匹配回调>
        自然数 反向匹配模板(原始串 子串, 匹配回调 匹配器, 比较回调 比较){
            自然数      不匹配下标 = 0;
            自然数      匹配下标;
            自然数      下标;
            推导类型    源串 = 原始串(元素, 长度);
            文字 常量 * 源元素;

            若 (源串->长度 < 子串->长度 || 源串->长度 == 0 || 子串->长度 == 0){
                回递 不存在;
            }

            //[不匹配下标] = 0
            //让[源串]匹配[子串[0]] 那么在第一个匹配的下标 
            //不能超过[源串->长度] - 子串->长度
            //因为子串还有后续元素
            //源串:"123451235"
            //子串:       "34"
            //     |---+---|
            //         |
            //    可匹配的长度
            源串->长度 = 源串->长度 - 子串->长度 + 1;

            只要((匹配下标 = 匹配器(源串, 子串[不匹配下标])) != 不存在) {
                源串->长度 = 匹配下标 - 不匹配下标;
                源元素 = 源串->元素 + 源串->长度;
                源串->长度 = 源串->长度 + 1;
                下标 = 0;

                只要(是){
                    若 (下标 == 子串->长度){
                        回递 源串->长度 - 1;
                    }
                    若 (比较(源元素[下标], 子串[下标]) != 0){
                        不匹配下标 = 下标;
                        跳出;
                    }
                    下标++;
                }
            }
            回递 不存在;
        }

        自然数 反向匹配(原始串 比对值, 局部函数<布尔(自然数)> 当匹配到) {
            回递 反向匹配(比对值, 默认比较<文字>(), 当匹配到);
        }

        自然数 反向匹配(原始串 比对值, 比较回调<文字> 回调, 局部函数<布尔(自然数)> 当匹配到) {
            自然数 下标 = 0;
            自然数 次数 = 0;
            原始串 临时(元素, 长度);

            只要((下标 = 临时->反向匹配(比对值, 回调)) != 不存在) {
                次数 += 1;
                临时->长度 = 下标;

                若 (当匹配到(下标) == 退出){
                    跳出;
                }
            }
            回递 次数;
        }

        自然数 反向匹配(原始串 比对值, 比较回调<文字> 回调 = 默认比较<文字>()) {
            回递 反向匹配模板(比对值,
                [=](原始串 源串, 文字 值){
                    回递 源串->反向匹配(值, 回调);
                }, 回调
            );
        }

        整数 等长比较(原始串 比对值, 自然数 比较长度, 比较回调<文字> 比较 = 默认比较<文字>()){
            循环(自然数 下标 = 0; 下标 < 比较长度; 下标++) {
                整数 结果 = 比较($O[下标], 比对值[下标]);
                若 (结果 != 0) {
                    回递 结果;
                }
            }
            回递 0;
        }

        整数 字典序比较(原始串 比对值, 比较回调<文字> 比较 = 默认比较<文字>()){
            若 (长度 == 0) {
                回递 比对值->长度 == 0 ? 0 : -1;
            }
            若 (比对值->长度 == 0) {
                回递 1;
            }
 
            自然数 比较长度;
            整数   最后返回;
 
            若 (长度 > 比对值->长度) {
                比较长度 = 比对值->长度;
                最后返回 = 1;
            }
            或 (长度 < 比对值->长度) {
                比较长度 = 长度;
                最后返回 = -1;
            }
            非{
                比较长度 = 长度;
                最后返回 = 0;
            }
        
            整数 比较结果 = 等长比较(比对值, 比较长度, 比较);

            若 (比较结果 == 0){
                回递 最后返回;
            }
            回递 比较结果;
        }
    
        整数 快速比较(原始串 比对值, 比较回调<文字> 比较 = 默认比较<文字>()){
            若 (长度 > 比对值->长度) {
                回递 1;
            }
            若 (长度 < 比对值->长度) {
                回递 -1;
            }
            若 (长度 == 0) {
                回递 0;
            }
            回递 等长比较(比对值, 长度, 比较);
        }

        布尔 串首存在(原始串 前缀, 比较回调<文字> 比较 = 默认比较<文字>()) {
            若 (长度 < 前缀->长度 || 长度 == 0) {
                回递 否;
            }
            回递 等长比较(前缀, 前缀->长度, 比较) == 等于;
        }

        布尔 串尾存在(原始串 后缀, 比较回调<文字> 比较 = 默认比较<文字>()) {
            若 (长度 < 后缀->长度 || 长度 == 0) {
                回递 否;
            }
            原始串 临时 = 原始串(元素, 长度);
            临时 += 后缀->长度 - 长度;
            回递 临时->等长比较(后缀, 后缀->长度, 比较) == 等于;
        }

        布尔 存在(文字 字符, 比较回调<文字> 比较 = 默认比较<文字>()) {
            回递 正向匹配(字符, 比较) != 不存在;
        }

        布尔 存在(原始串 子串, 比较回调<文字> 比较 = 默认比较<文字>()) {
            回递 正向匹配(子串, 比较) != 不存在;
        }

        属性(自然数, 长度)
            公有读 { 回递 $D.长度; }
            公有写 { $D.长度 = 值; }
        $

        属性(文字 *, 元素)
            公有读 { 回递 $D.元素; }
            公有写 { $D.元素 = 值; }
        $

        只读属性(自然数, 总宽)
            自然数 结果 = 0;
            循环(自然数 I = 0; I < $I.长度; I++) {
                结果 += 万国码(元素[I])->宽度;
            }
            回递 结果;
        $
    };
    
    模板<类 原始串> 结构体 运算{
        运算型卡诺匹斯(原始串);
        运算重载 文字 *(){
            回递 $D.元素;
        }

        整数 运算重载 - (运算 常量 & 值) {
            回递 $D.元素 - ((运算 &)值)->元素;
        }

        原始串 运算重载-- (I32) {
            原始串 临时 = $D;
            此 -= 1;
            回递 临时;
        }

        原始串 运算重载++ (I32) {
            原始串 临时 = $D;
            此 += 1;
            回递 临时;
        }

        原始串 运算重载-- () {
            此 -= 1;
            回递 此;
        }

        原始串 运算重载++ () {
            此 += 1;
            回递 此;
        }

        原始串 运算重载 - (自然数 偏移) {
            原始串 临时 = $D;
            临时 -= 偏移;
            回递 临时;
        }

        原始串 运算重载 + (自然数 偏移) {
            原始串 临时 = $D;
            临时 += 偏移;
            回递 临时;
        }

        原始串 运算重载 -= (自然数 偏移) {
            $I.长度 = $I.长度 + 偏移;
            $I.元素 = $I.元素 - 偏移;
            回递 $D;
        }

        原始串 运算重载 += (自然数 偏移) {
            $I.长度 = $I.长度 - 偏移;
            $I.元素 = $I.元素 + 偏移;
            回递 $D;
        }

        模板<类 甲, 类 乙>
        原始串 运算重载()(甲 常量 & 起始下标, 乙 常量 & 结束下标, 分配回调 回调){
            回递 $I.截取(起始下标, 结束下标, 回调);
        }
    };
}

结构体 原始串;
结构体 原始串 : 原始串空间::运算<原始串>{
    符号常量 原始串(文字 常量 * 串):
        数据(串) {
    }
    原始串(){}
    原始串(字符串 &&) = 删;
    原始串(原始串 串, 自然数 长度) :
        数据(串->元素, 长度){
    }
    原始串(原始串空间::数据<原始串> 数据) :
        数据(数据){
    }
    原始串(文字 常量 * 串, 自然数 个数) :
        数据(串, 个数){
    }
    空 运算重载=(字符串 &&) = 删;
私有
    数据类型 数据;
};

定义 原始串 __原始串;

内联链接 布尔 运算重载 == (原始串 左, 原始串 右) {
    回递 左->快速比较(右) == 等于;
}

内联链接 布尔 运算重载 != (原始串 左, 原始串 右) {
    回递 左->快速比较(右) == 不等于;
}

内联链接 布尔 运算重载 > (原始串 左, 原始串 右) {
    回递 左->快速比较(右) == 大于;
}

内联链接 布尔 运算重载 >=(原始串 左, 原始串 右) {
    回递 左->快速比较(右) == 大于等于;
}

内联链接 布尔 运算重载 < (原始串 左, 原始串 右) {
    回递 左->快速比较(右) == 小于;
}

内联链接 布尔 运算重载 <=(原始串 左, 原始串 右) {
    回递 左->快速比较(右) == 小于等于;
}
