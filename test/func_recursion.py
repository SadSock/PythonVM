

global x

x = 0


def b():
    if x >= 5:
        return
    else:
        x = x + 1
        b()
        return


b()

print x

