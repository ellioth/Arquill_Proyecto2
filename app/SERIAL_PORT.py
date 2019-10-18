import serial
from tkinter import *
from tkinter import font
import os
arduinoData = serial.Serial('COM3',9600)

#0 hora, 1 alarma
flagClock = 0
def led_on():
    arduinoData.write(str.encode('1')) #write(b'1')

def led_off():
    arduinoData.write(str.encode('0'))

def alarm_hour():
    global flagClock
    if(flagClock==0):
        flagClock=1
        arduinoData.write(str.encode('3'))
    else:
        flagClock=0
        arduinoData.write(str.encode('2'))
    
def selectSegment():
    arduinoData.write(str.encode('1'))
def upClock():
    arduinoData.write(str.encode('0'))
def setClock():
    arduinoData.write(str.encode('9'))

##°°°°°°°°°°°°°°°°°°°°°°°°_ Funcion Cargar Imagenes Tkinter  _°°°°°°°°°°°°°°°°°°°°°°°°
def cargarImagen(nombre):
    ruta = os.path.join('img',nombre)
    imagen = PhotoImage(file=ruta)
    return imagen

## ventana inicial
ventana_inicial = Tk()
ventana_inicial.title('RELOJ')                      ##titulo de la ventana
ventana_inicial.minsize(450,283)                     ##tamaño de la ventana
ventana_inicial.resizable(width= NO, height= NO)     ##ventana no se maximize
ventana_inicial.geometry("450x283+100+0")
##imagen de fondo, con titulo 
fondo = cargarImagen('fondo.gif')
wallpaper = Label(ventana_inicial, image= fondo, cursor= 'exchange')
wallpaper.place(x= -2, y= -3)


boton_selectAlarmHour = Button(ventana_inicial, cursor= 'mouse', activebackground= '#2D7FCB',
                             relief= 'sunken', text= 'Seleccionar Hora/Alarma',
                             font= ('DigifaceWide','13','bold'), command= alarm_hour,
                             bg = '#000000', fg = '#FFFFFF', borderwidth =5)
boton_selectAlarmHour.place(x= 138, y= 50)
boton_selectSegment = Button(ventana_inicial, cursor= 'mouse', activebackground= '#2D7FCB',
                             relief= 'sunken', text= 'Seleccionar 7 Segmento',
                             font= ('DigifaceWide','13','bold'), command= selectSegment,
                             bg = '#000000', fg = '#FFFFFF', borderwidth =5)
boton_selectSegment.place(x= 140, y= 100)
boton_upClock = Button(ventana_inicial, cursor= 'mouse', activebackground= '#2D7FCB',
                       relief= 'sunken', text= 'Cambiar Hora',
                       font= ('DigifaceWide','13','bold'), command= upClock,
                       bg = '#000000', fg = '#FFFFFF', borderwidth =5)
boton_upClock.place(x= 170, y= 150)
boton_setClock = Button(ventana_inicial, cursor= 'mouse', activebackground= '#2D7FCB',
                        relief= 'sunken', text= 'Setear Hora',
                        font= ('DigifaceWide','13','bold'), command= setClock,
                        bg = '#000000', fg = '#FFFFFF', borderwidth =5)
boton_setClock.place(x= 175, y= 200)

ventana_inicial.mainloop()

"""
t=0
call = 0
while(t<200000000):
    if(t%10000000 == 0):
        if(call==1):
            call=0
            led_off()
        else:
            call=1
            led_on()
        print(t)
    t+=1  


print("done")
"""
