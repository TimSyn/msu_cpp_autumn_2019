import subprocess

def Test1():
    instance = subprocess.run(stdout=subprocess.PIPE, stderr=subprocess.STDOUT, args=['./calc', "2"])
    output = instance.stdout.decode('utf-8')
    output = output[:len(output)-1:]
    if output == "2":
        print("(./calc '2')=", output,"== 2 -> Test1 OK")
    else:
        print("(./calc '2')=", output,"!= 2 -> Test1 WRONG")

def Test2():
    instance = subprocess.run(stdout=subprocess.PIPE, stderr=subprocess.STDOUT, args=['./calc', "-1"])
    output = instance.stdout.decode('utf-8')
    output = output[:len(output)-1:]
    if output == "-1":
        print("(./calc '-1')=", output,"== -1 -> Test1 OK")
    else:
        print("(./calc '-1')=", output,"!= -1 -> Test1 WRONG")

def Test3():
    instance = subprocess.run(stdout=subprocess.PIPE, stderr=subprocess.STDOUT, args=['./calc', "2 + 2 -2 +-2"])
    output = instance.stdout.decode('utf-8')
    output = output[:len(output)-1:]
    if output == "0":
        print("(./calc '2 + 2 -2 +-2')=", output,"== 0 -> Test1 OK")
    else:
        print("(./calc '2 + 2 -2 +-2')=", output,"!= 0 -> Test1 WRONG")

def Test4():
    instance = subprocess.run(stdout=subprocess.PIPE, stderr=subprocess.STDOUT, args=['./calc', "2 + -2*4 + 2 / -1"])
    output = instance.stdout.decode('utf-8')
    output = output[:len(output)-1:]
    if output == "-8":
        print("(./calc '2 + -2*4 + 2 / -1')=", output,"== -8 -> Test1 OK")
    else:
        print("(./calc '2 + -2*4 + 2 / -1')=", output,"!= -8 -> Test1 WRONG")

Test1()
Test2()
Test3()
Test4()
