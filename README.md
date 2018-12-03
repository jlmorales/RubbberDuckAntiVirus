**Recommended Running Environment:**

Labtainer VM, Ubuntu 16.04. There are known bugs with Debian and we have also experienced issues on Ubuntu 18.04.

The paths to our lists are currently hardcoded, so this repository should be cloned at home/student into home/student/RubbberDuckAntiVirus.

**Required Packages for Download:**

sudo apt-get install libssl-dev  
sudo apt-get install linux-headers-$(uname -r)  
sudo apt-get install python-dev  
sudo apt-get install python-pip  
pip install pipenv  
pipenv install requests  

**Compilation:**

Run bash make.sh inside /home/student/RubbberDuckAntiVirus.

**Execution:**

It is recommmended to run ./iterator as the root user.

