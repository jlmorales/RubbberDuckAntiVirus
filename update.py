import requests

r = requests.get('https://raw.githubusercontent.com/HeymiD/RubbberDuckAntiVirus/master/whitelist.txt')
open('whitelist.txt', 'w').write(r.content)

r = requests.get('https://raw.githubusercontent.com/HeymiD/RubbberDuckAntiVirus/master/blacklist.txt')
open('blacklist.txt', 'w').write(r.content)
