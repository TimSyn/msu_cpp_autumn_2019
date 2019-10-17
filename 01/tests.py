import subprocess

def Test(arg, answ):
    instance = subprocess.run(stdout=subprocess.PIPE, stderr=subprocess.STDOUT, args=['./calc', arg])
    output = instance.stdout.decode('utf-8')
    output = output[:len(output)-1:]
    if output == answ:
        print("(./calc '{0}')= '{1}' == '{2}' -> Test1 OK".format(arg, output, answ))
    else:
        print("(./calc '{0}')= '{1}' != {2} -> Test1 WRONG".format(arg, output, answ))

Test("2", "2")
Test("-1", "-1")
Test("2 + 2 -2 +-2", "0")
Test("2 + -2*4 + 2 / -1", "-8")
