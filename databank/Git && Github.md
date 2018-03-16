[TOC]

# Git && Github

## Git 的使用

```shell
#下载
sudo apt -get install git
#创建版本库
git init 
#添加进git的暂存区
git add file_name
#提交进版本库
git commit -m "备注，修改内容"
#检查仓库当前状态
git status
#查看不同
git diff
#查看提交日志
git log --pretty=oneline  #只显示一行
#回退到上一个版本
git reset --hard head^   #^的个数表示上几次
#回退到指定的版本
git reset --hard 343434  #343434是指特定的commit的ID号，没必要写全
#查看命令历史，查看commit的ID
git reflog
#查看工作区和版本库里的不同
git diff HEAD --file_name
#删除工作区的所有修改
git checkout --file_name
#删除缓存区的所有修改
git reset head file_name 
#删除文件
rm  test.txt
git rm  test.txt
git commit -m "remove test"

```

## GitHub的使用

### 连接GitHub

```shell
#git 和 GitHub 之间是通过shh加密的
#step1 创建SHHkey，在用户的目录下会有id_rsa.pub和id_rsa文件
shh-keygen -t rsa -C "youremail@example.com" #一路回车，不用设置密码
#step2 登录GitHub，打开account setting "SSh Keys"页面，点击add
在文本框中粘贴【id_rsa.pub】文件的内容
```

### 添加远程库

当你已经在本地上创建了一个Git仓库后，又想在Github 创建一个仓库，并且让这两个仓库进行远程同步，这样GitHub上的仓库可以即作为备份，又可以让其他人通过该仓库来协作

- 登录GitHub，点击右上角的“Create a new repo” 创建一个新的仓库
- 在repository name 填入 与本地相同的仓库名，确认
- 在本地的仓库中运行

```shell
git remote add origin git@github.com:hubusername/reponame.git 
#hubusername 是你hub的账户名 reponame是你库的名称
#远程库的名字是origin
```

- 把本地库的所有内容推送到远程库中

```shell
git push -u origin master
#当第一次完成后你只要在本地作了提交，就可以推送到远程库上，注意不能提交空库
git push origin master
```

从零开发，最好先创建远程库再从远程库克隆

- 在GitHub上创建库，勾选init....with readme
- 克隆到本地

```shell
git clone git@git.com::hubusername/reponame.git 
```

## 分支管理

```shell
#创建Dev分支并切换
git checkout -b dev
#创建Dev分支并切换（另一种）
git branch dev
git checkout dev
#查看当前分支
git branch
#合并分支结果到master上
git merge dev
#删除分支
git branch -d dev #强行删除使用-D
#禁用Fast forward 合并分支
git merge --no-ff -m "merge with no-off" dev
#暂时储存工作区
git stash
#查看储存的工作区
git stash list
#恢复到工作区
git stash apply #储存区不删除
git stash drop  #删除stash的储存
git stash pop
#显示远程库的信息
git remote -v
#推送分支
git push origin master
#抓取分支
git clone git@github.com:blackkking/zjzhen05.git#只能看到master分支
git checkout -b dev origin/dev #创建和克隆远程库上dev的分支
git branch --set-upstream dev origin/dev #设置连接
git pull #抓取最新提交
```

## 标签管理

标签和commit是绑定在一起的

```shell
#给最近一次commit打上标签
git tag v1.0
#查看标签
git tag
#给历史commit打上标签
git log --pretty=oneline --abbrev-commit 
git tag v0.9 77777 #77777是commit ID
#查看标签信息
git show V0.9
#创建有说明的标签
git tag -a v0.1 -m "ssssss" 77777
#删除标签
git tag -d v0.1
#推送标签到远程
git push origin v0.1
#删除远程标签
git push origin :refs/tags/v0.1
```

## 忽略特殊文件

在Git工作区的根目录下创建一个特殊文件 .gitignore

有一个网址：[https://github.com/giyhub/gitignore](:hubusername/reponame.git )里面有各种配置

## 使用别名

```shell
#别名
git config --global alias.st status
git config --global alias.co checkout
#加上global是对当前用户有用的，不加就只对当前仓库有用
```

仓库配置文件在.git/config  中

用户配置文件在用户主目录下的隐藏文件.gitconfig中

## 下载地址

可视化GitHub桌面版下载：

git版本下载：