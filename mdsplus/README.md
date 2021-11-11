# MDSPlus 

## MDSPlus stasts 码
MDSPlus API函数大都返回一个状态码,以最低位标识是否成功,(0:失败,1:成功).因此常用宏`#define statusOK(status) ((status)&1)`判断操作是否成功. 函数`char* MdsGetMsg(int status)`可以解析这一状态码,但通常十分简略,难以作为debug依据.

MDSPlus官方和社区均没有给出关于状态码的详细说明. 下表经简单测试得到,不能涵盖所有情况,可能存在错误.

| function | status    | comment             |
| -------- | --------- | ------------------- |
| MdsOpen  | 265392154 | 打开树失败,炮号错误 |
|          | 265392114 | 打开树失败,树错误   |
|          | 265389633 | 打开树成功          |

