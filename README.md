windows程序设计期末课程设计--GDI游戏开发/GDIGame：
使用C语言+GDI仿冒险岛开发的简单游戏demo

将游戏资源文件source.zip解压缩后，使用codeblocks打开cbp文件，无需第三方库，编译后即可运行

本设计采用C语言多文件编译：
（1）main.cpp - 主程序文件，程序入口，包含游戏循环的逻辑
（2）character.cpp/h - 游戏资源管理,包含全局变量以及全局函数的声明与初始化，存储游戏中的实体
（3）home.cpp/h、maphome.cpp/h - 游戏状态管理，进行地图、菜单、当前游戏状态的页面实现与跳转
（4）game.cpp/h - 游戏关卡管理，使用GDI进行游戏元素渲染与绘图。
（5）judge.cpp/h - 游戏碰撞与攻击判定管理，设计碰撞与攻击判定算法
（6）ui.cpp/h - 游戏角色与BOSS的UI管理，包含生命值(HP）、魔法值(MP)以及攻击结算后数值的数学计算
（7）replay.cpp/h - 实现游戏回放的相关逻辑，实现游戏过程中的帧数存储以及回放过程的遍历读取。

本设计采用基于游戏循环、透明贴图、双缓冲的SDK框架结构，框架原理如下所示：
（1）用透明位图去除人物背景，调用函数TransparentBlt自动进行处理。
（2）使用游戏循环，跳出消息机制，解决游戏卡顿问题：使用PeekMessage进行异步操作。
（3）使用双缓冲技术解决物体运动时屏幕闪烁问题

相关功能介绍
（1）角色控制
（2）关卡设计
（3）技能系统
（4）攻击判定
（5）死亡回放


