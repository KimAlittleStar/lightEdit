# 简易的文本查阅器
功能:
1. 打开文本文件
2. 保存文本文件
3. 指定显示文本文件中的某一行
4. 指定复制文本文件中的某一行插入到另一行
5. 指定替换字母
6. 在指定位置插入字符
7. 删除字符
-------------

## 快速开始

1. 编译程序  
    **windows**: 在命令行窗口输入:`mingw32-make.exe target=lightedit.exe`  
    **linux**: input `make target=lightedit.out`
    如编译成功将会出现以下字样  
    ```
    $ mingw32-make.exe target=lightedit.exe 
    finding D:/EclipsecCode/myGitProject/lightEdit/lightEdit.c depending head file
    finding D:/EclipsecCode/myGitProject/lightEdit/Exfunction.c depending head file
    finding D:/EclipsecCode/myGitProject/lightEdit/main.c depending head file
    finding D:/EclipsecCode/myGitProject/lightEdit/debug/memwatch.c depending head file
    finding D:/EclipsecCode/myGitProject/lightEdit/lightEdit.c depending head file
    compile D:/EclipsecCode/myGitProject/lightEdit/debug/memwatch.c
    compile D:/EclipsecCode/myGitProject/lightEdit/main.c
    compile D:/EclipsecCode/myGitProject/lightEdit/Exfunction.c
    compile D:/EclipsecCode/myGitProject/lightEdit/lightEdit.c
    bulding....
    created file: lightedit.exe
    ``` 
2. 执行程序  
   **windows**: 命令行输入 `./lightedit.exe`  
   **linux**: 命令行输入 `./lightedit.out`  
   like this
   ```
   $ ./lightedit.exe
   typing your command
   ```  

   你可以执行命令 `list` 或者 `help` 查看所有可执行命令的列表;  
   同时输入 `exit()` 即可退出程序
   ```bash
   $ ./lightedit.exe 
   typing your command
   list
   QuickComplet:"LIST","help","circle","open","close","L","D","CU","CD","RA","R",   "I","DAStr","DStr","CFB"
   
   *---------------------------------------------------------
    |    LIST();                  鍑芥暟鍒楄〃
    |--------------------------------------------------------
    |    help();If you want to support Chinese display please convert all files to GB2312
    |--------------------------------------------------------
    |    circle( %c %d);         涓插彛鏄剧ず涓€涓渾
    |--------------------------------------------------------
    |    open(%s);open [filename] open a file with name
    |--------------------------------------------------------
    |    close(%s);close [filename] close a file with name
    |--------------------------------------------------------
    |    L(%d);  L [n] show at n line context
    |--------------------------------------------------------
    |    D(%d);D [n] delete at n line context
    |--------------------------------------------------------
    |    CU(%d %d);CU [n] [m] Copy n rows above m rows
    |--------------------------------------------------------
    |    CD(%d %d);CD [n] [m] Copy n rows below m rows
    |--------------------------------------------------------
    |    RA(%s %s);RA [str1] [str2] Replace all str1  with str2  
    |--------------------------------------------------------
    |    R(%d %d %d %s %s);R [line] [row] [n] [str1] [str2] Replace str1 with str2 in n characters after the row column of line
    |--------------------------------------------------------
    |    I(%d %d %s);I [line] [row] [str1] Insert str1 in the row column of line
    |--------------------------------------------------------
    |    DAStr(%s);  DAStr [str1] Delete All str1
    |--------------------------------------------------------
    |    DStr(%d %d %d %s);DStr [line] [row] [n] [str1] delete str1 in n characters after the row column of line
    |--------------------------------------------------------
    |    CFB( %d);                   %d个乘法表
   *---------------------------------------------------------
   typing your command
   ```
   - open 命令  
  打开某个文件/win7系统以上支持 相对路径,如果打开失败则会报错  
   ```bash
   typing your command
   open ./sdfsdf
     >[Error] :open file error!!
   typing your command
   ```

   - close 命令  
  将你加载后的文件存储到硬盘当中  
  如果名字与open文件的名字不同则是新建文件

   - L 命令  
     L n 显示第n行 **n = -1 表示显示所有**
   - D 命令  
      D n 删除第年行
   - CU 命令 
      CU n m 将第n行复制到第m行上面
   - CD 命令 
      CD n m 将第n行复制到第m行下面
   - RA 命令  
      RA str1 str2 将文件中的所有str1用str2替换
   - R 命令  
      R x y n str1 str2将文件中的第x行，第y列开始的n个字符中的所有str1用str2替换。
   - I 命令  
      I x y str 在第x行，第y列字符前插入str
   - DAStr 命令  
      DAStr str 删除将文件中的所有str
   - DStr 命令  
      DStr x y n str 删除文件中的第x行，第y列开始的n个字符中的所有str。

## 注意事项  
如果您想要在中国地区的Windows上正常显示中文,请将项目中所有`*.c/*.h`文件编码格式转换为**GB2312** 即可  
在字符串参数中不允许出现 字符 `' '` ,每条命令的最大长度为499个字符;  
如果您执行 `open` 命令后并未执行 `close` 命令,那么将会存在内存泄漏,将依靠系统自动回收内存请您知悉;  

## 友情链接  
### 项目中使用了两个开源项目  
### **[vscode_c_deme](https://github.com/KimAlittleStar/vscode_c_demo)**:实现类似于linux命令行一般的调用函数;  
### **[cstd](https://github.com/KimAlittleStar/cstd)**:使用了类似于C++的代码膨胀 STL标准容器 Vector;

