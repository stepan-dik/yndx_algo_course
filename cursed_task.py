
def gen_brackets(string, to_open, to_close):
    if to_open == 0 and to_close == 0:
        print(string)
        return
    if to_open > 0:
        gen_brackets(string + "(", to_open-1, to_close+1)
    if to_close > 0:
        gen_brackets(string + ")", to_open, to_close-1)
    return

def main():
    num = int(input())
    string = '('
    gen_brackets(string, num - 1, 1)


if __name__ == '__main__':
    main()
