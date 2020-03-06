# !/bin/bash

# 移除非cpp文件至trash_can
function dfs(){
for file in `ls $1`
do
    if [ -d $1"/"$file ]
    then
        dfs $1"/"$file
    else
        # echo $1"/"$file
        if [[ $file != *.* ]]
        then
            mv $1"/"$file trash_can
        fi
    fi
done
} 
dfs template

git add .
git commit -m "by back_up.sh `date "+%Y-%m-%d %H:%M:%S"`"
git push origin master
