import hashlib, os, sys, itertools

bfname = raw_input()

f = open("whitelist.txt", "w")

for root, dirs,files in itertools.chain(os.walk('/usr/bin', topdown=True),os.walk('/bin', topdown=True)):
    for name in files:
        #print(os.path.join(root, name))
        FileName = (os.path.join(root, name))

        hasher = hashlib.sha1()
        with open(str(FileName), 'rb') as afile:
            buf = afile.read()
            hasher.update(buf)
        #print(hasher.hexdigest())
        f.write(hasher.hexdigest())
        #f.write("")
f.write(bfname)
f.close()