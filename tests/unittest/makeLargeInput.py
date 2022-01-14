from random import randint, sample
import string

def generateRandomMaps(numItem):
    # alphanumeric key and value
    out = ""
    l = list(string.ascii_letters + string.digits)
    for i in range(numItem):
        wordLen = randint(1, 10)
        key = ''.join(sample(l, k=wordLen))
        wordLen = randint(1, 10)
        data = ''.join(sample(l, k=wordLen))
        out += key + ":" + data + " "
    out += "check:check123 "
    return out

def main():
    f = open("./largeInput.txt", "w")
    f.write(generateRandomMaps(10000))
    f.close()

main()