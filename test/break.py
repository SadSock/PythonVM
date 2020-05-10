i = 0


while i < 10:
    i = i + 1

    j = 0
    while j < 10:
        if(j > 6):
            break;
        print j
        j = j + 1
    
    if(i > 5):
        break

    print i
