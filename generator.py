# -*- coding:utf-8  -*-
import os
import datetime

# DEBUG = True
DEBUG = False
if DEBUG: import sys

def dir_add(padding,content,w_file):

    if DEBUG: print(sys._getframe(0).f_code.co_name)
    for i in range(padding):
        w_file.write("    ")
    w_file.write(content + "\n")

def temp_add1(padding,content,w_file):

    if DEBUG: print(sys._getframe(0).f_code.co_name)
    for i in range(padding+2):
        w_file.write("#")
    w_file.write(" " + content + "\n\n")

def temp_add2(source_file,w_file):

    if DEBUG: print(sys._getframe(0).f_code.co_name)
    with open(source_file,"r") as f:
        s = f.read().strip("\n ")
        w_file.write("~~~cpp\n" + s + "\n~~~\n\n")

def work(main_dir):

    with open("temp.md","w") as f_temp:
        def dfs(depth,dir,op):
            if DEBUG: print(depth,dir)
            fileList = os.listdir(dir)
            for file_name in fileList:
                file_path = os.path.join(dir,file_name)
                
                if os.path.isfile(file_path):
                    file_split_name = os.path.splitext(file_name)
                    if file_split_name[1] != ".cpp":
                        continue
                    
                    if DEBUG: print(file_name)
                    if op == 1:
                        dir_add(depth-1,file_split_name[0],f_temp)
                    elif op == 2:
                        temp_add1(depth-1,file_split_name[0],f_temp)
                        temp_add2(file_path,f_temp)
                else:

                    if op == 1:
                        dir_add(depth-1,file_split_name[0],f_temp)
                    dfs(depth+1,file_path,op)

        f_temp.write("# 模板\n\n")
        f_temp.write(datetime.datetime.now().strftime("%Y-%m-%d by generator.py\n\n"))
        f_temp.write("## 目录\n\n")      
        dfs(1,main_dir,1)
        f_temp.write("\n")
        dfs(1,main_dir,2)

if __name__ == "__main__":
    work("template")