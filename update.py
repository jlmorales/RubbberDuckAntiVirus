import requests
r = requests.get('https://raw.githubusercontent.com/jlmorales/antivirus/master/whitelist.txt')
print(r.text)
f = open("whitelist.txt", "w")
f.write(str(r.text))

r = requests.get('https://raw.githubusercontent.com/jlmorales/antivirus/master/blacklist.txt')
f = open("blacklist.txt", "w")
f.write(str(r.text))