get_int = 0
while get_int <= 0 or get_int > 8:
    inpt = input("Height: ")
    try:
        get_int = int(inpt)
    except:
        pass


for i in range(1, get_int + 1):
    print(" " * (get_int - i), block := ("#" * i), "  ", block, sep="")
