# 408-Codes

 用以记录在学习 `11408` 时所编写的代码。

### 日志
> 更早的时候  

线性顺序表、链式双向线性表（带头结点、不带头结点）、栈、队列、栈在括号匹配的应用。

> 2023/10/17 

中缀转后缀表达式、后缀表达式的计算。

**Debug**   
1. 链表中 `Node` 类的析构函数有问题，在程序中会导致 `nxt` 与 `pri` 的地址改变，从而引发段错误。因此删除此析构函数。

2. 链表的析构函数，应遍历节点逐个删除，而非只删除头节点。

> 2023/10/28

完善顺序线性表的菜单交互部分。

> 2023/10/29

字符串与KMP算法。
