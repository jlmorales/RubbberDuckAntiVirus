import hashlib, os, sys

f = open("whitelistdigest.txt", "wb")

for root, dirs,files in os.walk('/usr/bin', topdown=True):
    for name in files:
        #print(os.path.join(root, name))
        FileName = (os.path.join(root, name))

        hasher = hashlib.sha1()
        with open(str(FileName), 'rb') as afile:
            buf = afile.read()
            hasher.update(buf)
        print(hasher.digest())
        f.write(hasher.digest())
        #f.write("")
        f.close()