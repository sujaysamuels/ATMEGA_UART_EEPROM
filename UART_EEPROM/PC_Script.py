import serial
import time


serial_port = 'COM9'
baud_rate = 2400


ser = serial.Serial(serial_port, baud_rate, timeout=1)


time.sleep(2)


string = "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs, Rajan said in the note.Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently.\n"

print("Sending Data.........")
start_time = time.time()
ser.write(string.encode())
end_time = time.time()
timeTx = end_time-start_time


print("Time Taken to Send String :",timeTx," Seconds")
print("Bits per second: ",(len(string)/timeTx)*10)
print("")


start_timeRx = time.time()
response = ser.readline().decode().strip()
end_timeRx = time.time()
timeRx = end_time-start_time


print("Time taken to Receive String :",timeRx," Seconds")
print("Bits per second: ",(len(string)/timeRx)*10)

print("")

print("Response from ATMEGA328p:", response)

if response+'\n' == string:
    print("The Transmitted String is Equal to Received String")
    print("")
    print("The Process is completed successfully")

ser.close()
