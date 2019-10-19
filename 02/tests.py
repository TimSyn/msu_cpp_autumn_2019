import subprocess

def Test(arg, answ):
    arg = arg.split(' ')
    instance = subprocess.run(stdout=subprocess.PIPE, stderr=subprocess.STDOUT, args=arg)
    output = instance.stdout.decode('utf-8')
    output = output[:len(output)-1:].split('\n')
    answ = answ.split('\n')
    print(output)
    print(answ)
    flag = True
    for i in range(len(output)):
        print("Your:",output[i],"Test:", answ[i]) 
        if output[i] != answ[i]:
            flag = False
            break
    if flag:
         print("Test OK")
    else:
         print("Test FAILED")

Test("./allocator 100", "")
Test("./allocator 0", "")
Test("./allocator 100 a10 a90 a1 r", ("Alloc: 10 Mem used: 10\n"
                        "Alloc: 90 Mem used: 100\n"
                        "Not alloc Mem used: 100\n"
                        "Reset: 1 Memory used: 0\n"
                        ""))
Test("./allocator 0 a10", ("Not alloc Mem used: 0\n" ""))
Test("./allocator 100 a200", ("Not alloc Mem used: 0\n" ""))
