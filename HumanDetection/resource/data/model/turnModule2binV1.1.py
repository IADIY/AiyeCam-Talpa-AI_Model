##
 # 
 # Copyright (C) 2023 NeuronBasic Co., Ltd. All rights reserved.
 # 
 # @file turnModule2bin.py
 # @author karl (karl.zhang@neuronBasic.com)
 # @version 1.0
 # @date 2023-08-05
 # @brief 将数组模型数据转成二进制
 # 
 #
import sys
import os
import re
import time

# 命令行使用: python .\turnModule2bin.py 模型文件1 模型文件2 模型文件3 ... 模型文件N
# 将生成dat文件,文件名开头的数字表明这是第几个模型
# 将module.h中用于project.ini的部分剪切到project.ini
# 将module.h include
# 开头的注释指明每个模型用到的变量

if __name__ == "__main__":
    iniConfig = ""
    module = ""
    parmas = ""
    checkSum = ""
    for  i, srcFile in enumerate(sys.argv[1:]):
        print(srcFile + ":")
        with open(srcFile, "r", encoding="utf-8") as src:
            srcFileName = os.path.split(srcFile)[1]
            # 记录当前处理的哪个模型数据
            parmas += "//{} {}\n".format(i, srcFileName)
            # 开头增加这是第几个模型,并替换后缀
            dstFileName = ("{}_{}".format(i, srcFileName))[::-1].replace(".txt"[::-1], ".dat"[::-1])[::-1]
            with open(dstFileName, "wb") as dst:
                # 每行是一个变量,读取每个变量进行处理
                for line in src:
                    # 根据开头判断需要多少位
                    if (line.startswith("int") is True):
                        bits = 32
                    elif (line.startswith("long long int") is True):
                        bits = 64
                    elif (line.startswith("signed char") is True):
                        bits = 8
                    # 将变量名部分和数据部分分开
                    linePart = line.split("=")
                    # 得到数据
                    numbers = linePart[1]
                    # 得到变量名称
                    parmaName = re.compile(r' [a-zA-Z0-9_]+').findall(linePart[0])[-1].replace(" ", "")
                    # 得到当前变量数组的每个数字
                    numbers = re.compile(r'[0-9-+]+').findall(numbers)
                    print("{}:{}".format(linePart[0], len(numbers)))
                    for number in numbers:
                        number = int(number) & ((0x01 << bits) - 1)
                        dst.write(number.to_bytes(int(bits / 8), "little", signed=False))
                    # 将变量重命名,以第几个模型作为结尾
                    newParmaName = "{}_{}".format(parmaName, i)
                    parmas += "//{}\n".format(newParmaName)
                    # 记录这个数据属于哪个文件的模型
                    module += "//{} {}\n".format(i, srcFileName)
                    # 生成改名后的变量
                    module += "{}\n".format(line.replace(parmaName, newParmaName))
                    # 添加检查用的类型
                    if (line.startswith("int") is True):
                        typeNUmber = "int"
                    elif (line.startswith("long long int") is True):
                        typeNUmber = "long long int"
                    elif (line.startswith("signed char") is True):
                        typeNUmber = "signed char"
                    module += "{} {}_check[3] = {{{}, {}, {}}};\n".format(typeNUmber, newParmaName, int(numbers[0]), int(numbers[int(len(numbers) / 2)]), int(numbers[-1]))
                    
            # 生成ini中的配置    
            iniConfig += "tdb=\"model/{} {}\"\n".format(dstFileName, i)
        with open("module.h", "w") as codeFile:
            codeFile.write(iniConfig)
            codeFile.write(parmas)
            codeFile.write(module)

