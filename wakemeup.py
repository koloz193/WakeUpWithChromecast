import os

if (os.path.isfile("/usr/local/bin/castnow") != 1):
    os.system("sudo npm install castnow -g")

os.system("gcc wakemeup.c -o driver")

location = raw_input("Where is the music? ")
print("What time would you like to wake up?")
hour = raw_input("Hour (0-23): ")
minutes = raw_input("Min (0-59): ")

hour = int(hour)
minutes = int(minutes)

# Trying to offset minute delay in C program
if minutes == 0:
  minutes = 59
else:
  minutes -= 1

os.system("./d %s %d %d" % (location, hour, minutes))
