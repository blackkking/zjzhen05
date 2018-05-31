[TOC]

# linux 操作

find . -name "*.c"| xargs grep -ni "basChar2Fl"

在当前文件夹中找到有basChar2Fl字段的.c文件

ls -lrt *bk 按时间排序后置为bk的文件

```
ls -lrt *esbSwitch* 时间倒置排序文件
```

 gzip -cd Pre-20231231-08150956.tar.gz| tar -xvf -解压文件

ls -lrt * CLRDTL * 排序

netstat -an|grep 18030 查看接口18030

grep 3012341188 *oaoa9935*log|grep "\[800303\]" 

查找有3012341188 的名字有oaoa9935的log文件 还要有"[800303]" 交易

"update TBL_PCM_SYSPRM set SP_BIZ_DATE = '20300803'"

更新数据库数据

fepadmin shut inst bos2  关闭bos2

fepadmin boot inst bos2打开bos2

env | grep BOSII_C 查看环境变量

fepadmin show all 查看进程

make clean  debug 重启

zebadmin shut server oaoa9980

zebadmin boot server oaoa9980

删除目录和里面的文件 rm -rf dirname

## 卡介质	

F22
词条：02,90
芯片：05,95
非接：07


F35磁条

F23，F55 芯片

## Card

ser_num1, cb_user_code2 from tbl_csm_crdbsc where cb_cardno='6250994087686786'"

CB_CARDNO           CB_EXPIRY_CCYYMM CB_USER_NUM1 CB_USER_CODE2
------------------- ---------------- ------------ -------------
6250994087686786    203305                     2. ACC 

db2 "select cb_cardno, cb_expiry_ccyymm, cb_pin_offset, cb_user_num1, cb_user_code2 from 

CB_CARDNO           CB_EXPIRY_CCYYMM CB_PIN_OFFSET CB_USER_NUM1 CB_USER_CODE2
------------------- ---------------- ------------- ------------ -------------
6250994087686786    203305           659992FFFFFF            2. ACC    

db2 "select cb_cardno, cb_product_cd, cb_expiry_ccyymm, cb_pin_offset, cb_user_num1, cb_u>

CB_CARDNO           CB_PRODUCT_CD CB_EXPIRY_CCYYMM CB_PIN_OFFSET CB_USER_NUM1 CB_USER_CODE2
------------------- ------------- ---------------- ------------- ------------ -------------
6250994087686786            6900. 203305           659992FFFFFF            2. ACC        

芯片卡  芯片序号  CB_USER_NUM1 TBL_CSM_CRDBSC  

磁条卡算二磁信息

卡号

有效期   CB_EXPIRY_CCYYMM  TBL_CSM_CRDBSC  失效日期

服务代码  卡产品控制表 TBL_PCM_PRDCTL  PC_TRK2_SERVICE_CD 二磁道服务信息

偏移量  CB_PIN_OFFSET  TBL_CSM_CRDBSC  密码偏移量

pin密码        卡背面的 CVV2 (绑定用的，三位安全码)

二磁信息 ：磁条的

CB_USER_CODE2   TBL_CSM_CRDBSC 第二个字符为M磁道卡C为芯片卡



### 查看短信

查看短信日志：batch里面

拼接短信的函数：com_smscom.c里

## 查看错误原因

------------------------------------------------------------------------------
信息[100001]:CVV2校验失败, result[01], cvv[098]!
------------------------------------------------------------------------------
INFO :TIME:2018-01-03_21:03:11.248:oaoa9930[53215370]:oam_util.c,2764:
信息[100001]:照会: refcd[45], onlineind[D], voiceind[D], channel[66], cInd[D]

[D]代表第一列，2代表第二列

根据照会代码去页面检查照会对应表

控制面板-风险控制参数管理-在线授权风控管理-照会原因代码管理-返回映射管理



vi，more  : 向上翻页 Ctrl + U 向下翻页 Ctrl + D ;



查看进程：

batmenu-->O 进程监控-->009 Y

ESC+K 查看上一条命令 ESC+J查看下一条命令

db2 "import from ht.del of del insert_update into  tbl_pcm_sysprm" 导入数据文件到数据库的表中 插入并更新

db2 "import from ht.del of del insert into tbl_pcm_sysprm"    只插入

db2 "export to ht.del of del select * from tbl_pcm_sysprm"  导出数据库数据到文件

文件一般放在patch目录下

vim状态下删除某个字符

```shell
g/^M/s///g #^M 在vim状态下使用“Ctrl+v+m”打印
```

查看练级交易代码检查项(照会代码)

tbl_oam_txnctl 交易控制处理表

tbl_oam_chklist 授权检查表

#### db2只显示10行

select cb_cust_id from tbl_csm_crdbsc fetch first 10 rows only

sbin/filemergelist 对照批前文件

#### debug模式

sh -x 程序名称

#### 显示内存最多的K 个进程

ps -aux | sort -k4nr |head K

top (按下大写的M)

#### 显示CUP占用最多的K个进程

ps -aux | sort -k3nr | head K

top(按下大写的P)

#### 取得ipc信息：

ipcs [-m|-q|-s]
-m 输出有关共享内存(shared memory)的信息
-q 输出有关信息队列(message queue)的信息
-s 输出有关“遮断器”(semaphore)的信息

删除ipc
ipcrm -m|-q|-s shm_id

查看共享内存的大小
cat /proc/sys/kernel/shmmax

修改共享内存大小：
临时修改：在root用户下执行# echo 268435456 > /proc/sys/kernel/shmmax把共享内存大小设置为256MB；
永久修改：在root用户下修改/etc/rc.d/rc.local文件，加入下面一行：
echo 268435456 > /proc/sys/kernel/shmmax
即可每次启动时把共享内存修改为256MB。

#### 安装rpm包

su - root

rpm -ivh rpm的软件报名

-i 安装软件

-t 测试安装

-p 显示安装进度

-v 检测是否正确安装

删除

rpm -e

#### apt 安装

su - root

apt -get install packagename 安装

apt -get remove packagename 删除

apt -get -purge remove packagename 删除并删除配置文件

apt -get clean

#### Dpkg 

dbkg -i soft.version.deb

dbkg -e soft









