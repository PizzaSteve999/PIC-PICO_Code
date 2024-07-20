from machine import UART, Pin
import time

# Initialize UART0 on GPIO0 (TX) and GPIO1 (RX)
uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))
led = Pin('LED',Pin.OUT)

while True:
    if uart.any():  # Check if there's data available to read
        led.toggle()
        data = uart.read()  # Read data from UART
        print(data)
    time.sleep(0.5)  # Small delay to prevent flooding