﻿#pragma once
#include"基本定义/迷你.hpp"
#include"指令集/基础.hpp"

枚举 指令区间{
    立即数填充     = 0                                        , 立即数填充指令条数      = 16,
    内存读写       = 立即数填充     + 立即数填充指令条数      , 内存读写指令条数        = 16,
    减法           = 内存读写       + 内存读写指令条数        , 减法指令条数            = 16,
    除法           = 减法           + 减法指令条数            , 除法指令条数            = 16,
    左移           = 除法           + 除法指令条数            , 左移指令条数            = 16,
    右移           = 左移           + 左移指令条数            , 右移指令条数            =  8,
    算数右移       = 右移           + 右移指令条数            , 算数右移指令条数        =  8,
    加法           = 算数右移       + 算数右移指令条数        , 加法指令条数            =  8,
    乘法           = 加法           + 加法指令条数            , 乘法指令条数            =  8,
    位与           = 乘法           + 乘法指令条数            , 位与指令条数            =  4,
    位或           = 位与           + 位与指令条数            , 位或指令条数            =  4,
    位异或         = 位或           + 位或指令条数            , 位异或指令条数          =  4,
    位与非         = 位异或         + 位异或指令条数          , 位与非指令条数          =  4,
    位测试         = 位与非         + 位与非指令条数          , 位测试指令条数          =  2,
    位测试后位置位 = 位测试         + 位测试指令条数          , 位测试后位置位指令条数  =  2,
    位测试后位复位 = 位测试后位置位 + 位测试后位置位指令条数  , 位测试后位复位指令条数  =  2,
    位测试后位取反 = 位测试后位复位 + 位测试后位复位指令条数  , 位测试后位取反指令条数  =  2,
    JIA            = 位测试后位取反 + 位测试后位取反指令条数  , JIA指令条数             =  2,
    JAE            = JIA            + JIA指令条数             , JAE指令条数             =  2,
    JIG            = JAE            + JAE指令条数             , JIG指令条数             =  2,
    JGE            = JIG            + JIG指令条数             , JGE指令条数             =  2,
    JIE            = JGE            + JGE指令条数             , JIE指令条数             =  2,
    JNE            = JIE            + JIE指令条数             , JNE指令条数             =  2,
    JIC            = JNE            + JNE指令条数             , JIC指令条数             =  2,
    JNC            = JIC            + JIC指令条数             , JNC指令条数             =  2,
    JMP            = JNC            + JNC指令条数             , JMP指令条数             =  2,
    JAL            = JMP            + JMP指令条数             , JAL指令条数             =  2,
    赋值           = 位测试         + JAL指令条数             , 赋值指令条数            =  2,
    互换           = 赋值           + 赋值指令条数            , 互换指令条数            =  1,
    压栈           = 互换           + 互换指令条数            , 压栈指令条数            =  1,
    退栈           = 压栈           + 压栈指令条数            , 退栈指令条数            =  1,
    返回           = 退栈           + 退栈指令条数            , 返回指令条数            =  1,
};

结构体 内存修饰符{
    U08 包含T : 1;
    U08 位宽  : 2;
    U08 写入  : 1;
};

枚举体 F2{
    AI,
    AB,
};

枚举体 F4{
    ABI,
    AAB,
    ABT,
    TAB,
};

枚举体 F8{
    AAI,
    ABI,
    AIA,
    AIB,
    AAB,
    ABT,
    ATB,
    TAB,
};

结构体 处理器{
    枚举{
        整数寄存器个数 = 16,
        指令个数       = 256,
        SP             = 0,
    };

    联合体 整数寄存器{
        U64 U;
        I64 I;
        整数寄存器() :I{} {}
        整数寄存器(I64 I) : I(I){}
        整数寄存器(U64 U) : U(U){}
    } R[整数寄存器个数], TMP;

    结构体 指令{
        U08     A   : 4;
        U08     B   : 4;
        结构体{
            模板<类 甲> 运算重载 甲(){
                甲 临时 {};
                转换<甲, U08>(临时) = C;
                回递 临时;
            }
            运算重载 U08(){
                回递 C;
            }
            U08 C;
        } OPC;

        静态 符号常量 U08 T = 1;
        运算重载 U16() {
            回递 *(U16 *)(此指针);
        }
    } INS;

    结构体 立即数结构{
        立即数结构(){
            位宽 = 0;
            值 = 0;
        }
        空 填充(U08 W, U16 V){
            值 |= I64(V) << 位宽;
            位宽 += W;
        }
        运算重载 I64(){
            布尔 状态 = ::指令集::位测试(U64(值), 位宽 - 1);
            I64  T = 值;
            若 (状态 == 置位态){
                值 |= U64(-1) << 位宽;
                T = 值;
            }
            值 = 0;
            位宽 = 0;
            回递 T;
        }
        I64 值;
        U08 位宽;
    } IMM;

    结构体 标志位{
        U08  CF : 1;
        U08  OF : 1;
        U08  ZF : 1;
        U08  AB : 1;
        U08  GT : 1;
        U08  整数字宽;
    } STA;

    U08 * MEM;
    U64   BYTES;
    U64   PC;
    U64   PCS;

    结构体 指令集结构{
        定义 空 (处理器::*指令)();
        指令 函数;

        模板<类 匿名函数>
        空 运算重载 = (匿名函数 回调){
            复制(函数, & 匿名函数::运算重载());
        }

        运算重载 指令 (){
            回递 函数;
        }
    } 指令集[指令个数];

    #define $M(指令)     循环(I = 指令; I < 指令 + 自然数(指令 ## 指令条数); I++) 指令集[I] = [此指针]()
    #define $X(...)      [此指针](整数寄存器 & A, 整数寄存器 常量 & B, 整数寄存器 常量 & C, U08 __VA_ARGS__)
    #define $J(条件)     IMM.填充(9, INS & 0x1ff); I64 OFFSET = IMM << 1; 若 (条件){ PC += OFFSET; }

    // FAKE
    空 内存写入(U64 & A, U64 B, U64 偏移, U08 字节数) {
        推导类型 D = (U08 *)MEM + B + 偏移;
        推导类型 S = (U08 *)& A;
        只要(字节数--) {
            D[0] = S[0];
            D   += 1;
            S   += 1;
        }
    }
    
    // FAKE
    空 内存读取(U64 & A, U64 B, U64 偏移, U08 字节数) {
        推导类型 S = (U08 *)MEM + B + 偏移;
        推导类型 D = (U08 *)& A;
        只要(字节数--) {
            D[0] = S[0];
            D   += 1;
            S   += 1;
        }
    }
    
    模板<类 运算回调>
    空 二相运算(运算回调 回调) {
        U08  F = (INS.OPC & 0x2) != 0;
        开关(F2(INS.OPC & 0x1)) {
        通向 F2::AI:  IMM.填充(4, INS.B);
                      回调(R[INS.A], 整数寄存器(IMM), 整数寄存器(0ull), F); 跳出;
        通向 F2::AB:  回调(R[INS.A], R[INS.B],        整数寄存器(0ull), F); 跳出;
        }
    }

    模板<类 运算回调>
    空 四相运算(运算回调 回调) {
        U08  F = (INS.OPC & 0x4) != 0;
        开关(F4(INS.OPC & 0x3)) {
        通向 F4::ABI: 回调(R[INS.A], R[INS.B], 整数寄存器(IMM), F); 跳出;
        通向 F4::AAB: 回调(R[INS.A], R[INS.A], R[INS.B],        F); 跳出;
        通向 F4::ABT: 回调(R[INS.A], R[INS.B], R[INS.T],        F); 跳出;
        通向 F4::TAB: 回调(R[INS.T], R[INS.A], R[INS.B],        F); 跳出;
        }
    }

    模板<类 运算回调>
    空 八相运算(运算回调 回调) {
        U08  F = (INS.OPC & 0x8) != 0;
        开关(F8(INS.OPC & 0x7)) {
        通向 F8::AAI: IMM.填充(4, INS.B);
                      回调(R[INS.A], R[INS.A],        整数寄存器(IMM), F); 跳出;
        通向 F8::ABI: 回调(R[INS.A], R[INS.B],        整数寄存器(IMM), F); 跳出;
        通向 F8::AIA: 回调(R[INS.A], 整数寄存器(IMM), R[INS.A],        F); 跳出;
        通向 F8::AIB: 回调(R[INS.A], 整数寄存器(IMM), R[INS.B],        F); 跳出;
        通向 F8::AAB: 回调(R[INS.A], R[INS.A],        R[INS.B],        F); 跳出;
        通向 F8::ABT: 回调(R[INS.A], R[INS.B],        R[INS.T],        F); 跳出;
        通向 F8::ATB: 回调(R[INS.A], R[INS.T],        R[INS.B],        F); 跳出;
        通向 F8::TAB: 回调(R[INS.T], R[INS.A],        R[INS.B],        F); 跳出;
        }
    }

    处理器(U08 * MEM, U64 BYTES){
        自然数 I = 0;
        清空(此);
        此.MEM   = MEM;
        此.BYTES = BYTES;
        $M(立即数填充){
            IMM.填充(12, INS & 0xfff);
        };
        $M(内存读写  ){
            内存修饰符 F = INS.OPC;
            U64     &  A = R[INS.A].U;
            U64        B = R[INS.B].U;
            U64        C = F.包含T ? R[INS.T].U + IMM : IMM;
            U08        字节数 = 1 << F.位宽;

            若 (F.写入){
                内存写入(A, B, C, 字节数);
            }
            非{
                A = 0;
                内存读取(A, B, C, 字节数);
            }
        };
        $M(减法      ){
            八相运算($X(带借位){
                STA.ZF = B.I == C.I;
                STA.GT = B.I >  C.I;
                STA.AB = B.U >  C.U;

                若 (带借位){
                    STA.CF = ::指令集::减法(A.U, B.U, C.U);
                }
                非{
                    STA.CF = ::指令集::减法(A.U, B.U, C.U, STA.CF);
                }
            });
        };
        $M(除法      ){
            八相运算($X(有符号){
                若 (STA.OF = (C.U == 0)){
                    回递;
                }
                若 (有符号){
                    TMP.I = ::指令集::除法(A.I, B.I, C.I);
                }
                非{
                    TMP.U = ::指令集::除法(A.U, B.U, C.U);
                }
                STA.CF = TMP.U != 0;
                STA.ZF = A.U == 0;
            });
        };
        $M(左移      ){
            八相运算($X(带进位){
                推导类型 CF = ::指令集::位测试(B.U, 比特数(C.U) - C.U);
                A.U    = (B.U << C.U) | (带进位 & STA.CF);
                STA.CF = CF;
                STA.ZF = A.U == 0;
            });
        };
        $M(右移      ){
            八相运算($X(){
                推导类型 CF = ::指令集::位测试(B.U, C.U - 1);
                A.U    = B.U >> C.U;
                STA.CF = CF;
                STA.ZF = A.U == 0;
            });
        };
        $M(算数右移  ){
            八相运算($X(){
                推导类型 CF = ::指令集::位测试(B.U, C.U - 1);
                A.I    = B.I >> C.I;
                STA.CF = CF;
                STA.ZF = A.I == 0;
            });
        };
        $M(加法      ){
            四相运算($X(带进位){
                STA.CF = ::指令集::加法(A.U, B.U, C.U, 带进位 & STA.CF);
                STA.ZF = A.U == 0;
            });
        };
        $M(乘法      ){
            四相运算($X(有符号) {
                若 (有符号){
                    TMP.I  = ::指令集::乘法(A.I, B.I, C.I);
                }
                非{
                    TMP.U  = ::指令集::乘法(A.U, B.U, C.U);
                }
                STA.CF = TMP.U != 0;
                STA.ZF = A.U == 0;
            });
        };
        $M(位与      ){
            四相运算($X() {
                A.U = B.U & C.U;
                STA.ZF = A.U == 0;
            });
        };
        $M(位或      ){
            四相运算($X() {
                A.U = B.U | C.U;
                STA.ZF = A.U == 0;
            });
        };
        $M(位异或    ){
            四相运算($X() {
                A.U = B.U ^ C.U;
                STA.ZF = A.U == 0;
            });
        };
        $M(位与非    ){
            四相运算($X() {
                A.U = ~(B.U & C.U);
                STA.ZF = A.U == 0;
            });
        };
        $M(位测试    ){
            二相运算($X() {
                STA.CF = ::指令集::位测试(A.U, B.U);
            });
        };
        $M(位测试后位置位){
            二相运算($X() {
                STA.CF = ::指令集::位测试后位置位(A.U, B.U);
            });
        };
        $M(位测试后位复位){
            二相运算($X() {
                STA.CF = ::指令集::位测试后位复位(A.U, B.U);
            });
        };
        $M(位测试后位取反){
            二相运算($X() {
                STA.CF = ::指令集::位测试后位取反(A.U, B.U);
            });
        };
        $M(JIA       ){
            $J(STA.AB);
        };
        $M(JAE       ){
            $J(STA.AB | STA.ZF);
        };
        $M(JIG       ){
            $J(STA.GT);
        };
        $M(JGE       ){
            $J(STA.GT | STA.ZF);
        };
        $M(JIE       ){
            $J(STA.ZF);
        };
        $M(JNE       ){
            $J(STA.ZF == 否);
        };
        $M(JIC       ){
            $J(STA.CF);
        };
        $M(JNC       ){
            $J(STA.CF == 否);
        };
        $M(JMP       ){
            $J(是);
        };
        $M(JAL       ){
            U32 OFFSET;
            若 (INS.OPC & 1){
                IMM.填充(8 + 1, 0 << 8 | INS & 0xff);
                OFFSET = 0xffffffff & IMM;
            }
            非{
                IMM.运算重载 I64();
                OFFSET = U32(R[INS.B].U);
            }
            内存写入(PC, PCS, 0, 空间量(PC));
            PCS += 空间量(PC);
            PC  &= U64(0xffffffff) << 32;
            PC  |= U32(OFFSET - 2);
        };
        $M(赋值      ){
            二相运算($X() {
                A.U = B.U;
            });
        };
        $M(互换      ){
            推导类型 A = R[INS.A];
            推导类型 B = R[INS.B];
            R[INS.A] = A;
            R[INS.B] = B;
        };
        $M(压栈      ){
            若 (INS.A <= INS.B) 循环(整数 I = INS.A; I <= INS.B; I++) {
                内存写入(R[I].U, R[SP].U, 0, 空间量(整数寄存器));
                R[SP].U += 空间量(整数寄存器);
            }
            非 循环(整数 I = INS.A; I >= INS.B; I--) {
                内存写入(R[I].U, R[SP].U, 0, 空间量(整数寄存器));
                R[SP].U += 空间量(整数寄存器);
            }
        };
        $M(退栈      ){
            若 (INS.A <= INS.B) 循环(整数 I = INS.A; I <= INS.B; I++) {
                R[SP].U -= 空间量(整数寄存器);
                内存写入(R[I].U, R[SP].U, 0, 空间量(整数寄存器));
            }
            非 循环(整数 I = INS.A; I >= INS.B; I--) {
                R[SP].U -= 空间量(整数寄存器);
                内存写入(R[I].U, R[SP].U, 0, 空间量(整数寄存器));
            }
        };
        $M(返回      ){
            PCS -= 空间量(PC);
            内存读取(PC, PCS, 0, 空间量(PC));
        };
    }
};

#undef $M
#undef $X
#undef $J


