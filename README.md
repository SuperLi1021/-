# 检测室内外温度值控制小风扇的设计报告

### 1.题目要求

> ### 1. 最低要求
>
>  
>
> a) 当室内温度大于室外温度时，小风扇转动；当室内温度低于室外温度时，小风扇静止。
>
> b) 利用纸箱等材料搭建演示模型（纸箱大小不小于30x*30*x15CM）。
>
> 
>
> c) 提交一份纸质的设计报告（字数 400 字以上）。
>
>  
>
> ## 2. 基本要求
>
> a) 采用 51 内核或ARM Cortex 内核（stm32 等）单片机进行控制。
>
> b) 当室内处于较低温度时，小风扇不开启，可通过按键手动开启风扇或改变风扇转速。转速分类不小于 4 档，变化明显。使用数码管等显示器件显示档位。
>
> c) 能显示室内外温度值。
>
> d) 当温度高于 30℃时，有声光报警提示（蜂鸣器可以不用），灯光需以呼吸灯形式提醒，即灯逐渐亮，逐渐暗，亮灭持续时间随温度增加而缩短，肉眼可明显区分，当温度高于 30℃+5℃时灯变为闪烁，闪烁周期不小于 0.25s。（温度值可根据调试情况自行调整，调整区间为±5℃）
>
> ## 3. 发挥部分
>
> a) 根据室内温度，自动调整小风扇转速，温度升高 1℃， 风扇转速加快一档。
>
> b) 在不重新编程的情况下，能调整声光报警阈值，并且断电不丢失。
>
> c) 设计遥控端，采用无线方式与控制端进行连接通信。遥控端能实时显示室内外温度、小风扇转速，并且能在遥控端控制小风扇的运行状态。
>
>
> d) 自行设计电机驱动电路（全分立器件）。

### 2.器件选型

需求：1.单片机

​			1）产生波特率，电机pwm调速，呼吸灯，共三个定时器。

​			2）在不重新编程的情况下，能调整声光报警阈值，并且断电不丢失。eeprom。

​					因此单片机使用89c52rc

​			2.远程通讯

​			1）设计遥控端，采用无线方式与控制端进行连接通信。遥控端能实时显示室内外温度、小风扇转速，并且能在遥控端控制小风扇的运行状态。

​			使用hc-05蓝牙模块。

​			3.显示模块

​			1）能显示室内外温度值。

​			2）显示电机档位。

​			3）显示设定的高低温阈值。

​			使用lcd1602。

​			4.测温模块

​			测温使用ds16b20模块。

​			5.电机驱动模块

​			使用8050与8550三极管与1n4148搭建的H桥电路

​			

### 3.程序框架

![](C:\Users\28388\Desktop\善建通达\简要流程图\程序流程图.png)

### 4.按键说明

| 按键 | 功能                     |
| ---- | ------------------------ |
| 1    | 控制sw+1 如果sw>5,则sw=0 |
| 2    | +                        |
| 3    | -                        |



| sw   | +说明                 | -说明                     |
| ---- | --------------------- | ------------------------- |
| 0    |                       | 运行状态                  |
| 1    | 低温阈值+1            | 低温阈值-1                |
| 2    | 高温阈值+1            | 高温阈值-1                |
| 3    | 电机占空比+10（绝对） | 电机占空比-10（绝对）     |
| 4    | 电机启动（绝对）      | 电机停止（绝对）          |
| 5    |                       | 清空绝对状态 回归自动控制 |



### 5.蓝牙命令说明

| 命令（16进制） | 内容                      |
| -------------- | ------------------------- |
| Aa bc          | 高温阈值设为abc           |
| Ba bc          | 低温阈值设为abc           |
| Ca bc          | 占空比设为abc             |
| Da bc          | 频率设置为abc             |
| E***           | 电机启动（绝对）          |
| F***           | 电机关闭（绝对）          |
| 00 00          | 仅查询系统状态 不改变参数 |
| 99 99          | 回到自动控制状态          |



### 6.显示说明

第二行16位分别为



| 位数     |                        |
| -------- | ---------------------- |
| 1 2 3    | 室外温度（3位精度0.1） |
| 4 5 6    | 室内温度（3位精度0.1） |
| 7 8 9    | 低温阈值（3位精度1）   |
| 10 11 12 | 高温阈值（3位精度1）   |
| 13       | sw                     |
| 14 15    | 电机占空比（2位）      |

### 7.温度测试模块说明

使用两个ds18b20作为温度传感器，采用单独接线方式，使用700毫秒的低电平脉冲作为初始化信号，然后进行写操作，读操作，温度转化操作，在此过程中，关闭中断以保证在此过程中的时序不受影响。

### 8.电机驱动模块说明

电机使用一个小型直流电机，驱动电机所用的电压电流并不大，所以使用三极管与二极管搭建H桥电路作为电机驱动电路。

![image-20201224123318202](C:\Users\28388\AppData\Roaming\Typora\typora-user-images\image-20201224123318202.png)

