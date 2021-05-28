###---------- Git开发流程常用命令 ----------
### 基本操作
#### 预备流程
+ git checkout master
+ git pull
+ git checkout local
#### 切换到local分支后， 就是修改代码
+ coding...
#### 修改完了，就正常提交代码
+ git add .
+ git commit
#### 如果有多次local分支的提交，就合并，只有一次可以不合并
+ git rebase -i HEAD~2  //合并提交 --- 2表示合并两个
#### 将master内容合并到local
+ git rebase master---->解决冲突--->git rebase --continue
#### 再起切换到master或其他目标分支
+ git checkout master
#### 将local合并到master
+ git merge local
####推送到远程仓库
+ git push
####保存git中的账号密码
+ git config --global credential.helper store

### 删除操作
#### 1. 删除已经上传到github的文件
+ git rm -r --cached fileName             
+ git commit -m '删除了文件fileName' 