from random import randint, sample
import string

def generateRandomMaps(numItem):
    # alphanumeric key and value
    out = "check1 check123\n"
    l = list(string.ascii_letters + string.digits)
    for i in range(numItem):
        wordLen = randint(1, 10)
        key = ''.join(sample(l, k=wordLen))
        wordLen = randint(1, 10)
        data = ''.join(sample(l, k=wordLen))
        out += key + " " + data + "\n"
    out += "check5 check567"
    return out

def main():
    f = open("./tests/unittest/dictMultipleEntries.txt", "w")
    f.write(generateRandomMaps(1000))
    f.close()

main()