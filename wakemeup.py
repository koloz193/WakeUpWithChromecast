import os

if (os.path.isfile("/usr/local/bin/castnow") != 1):
    os.system("sudo npm install castnow -g")

os.system("gcc wakemeup.c -o driver")

os.system("./driver")
