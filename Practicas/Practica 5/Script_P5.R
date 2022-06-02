install.packages('tuneR', dep=TRUE)
install.packages('seewave', dep=TRUE)

library(tuneR)
library(seewave)
library(audio)


# Ejercicio 1 : Reproducir 2 archivos .mp3 diciendo mi nombre y apellidos

nombre <- readMP3('./sonidos/nombre.mp3')
nombre
listen(nombre)


apellidos <- readMP3('./sonidos/apellidos.mp3')
apellidos
listen(apellidos)

# Ejercicio 2 : Dibujar la forma de onda de ambos sonidos

plot( extractWave(apellidos, from = 1, to = length(apellidos)), main="Apellidos" )
plot( extractWave(nombre, from = 1, to = length(nombre)), main="Nombre" )

# Ejercicio 3 : Obtener la informaciÃ³n de las cabeceras de ambos sonidos.

str(apellidos)
str(nombre)

# Ejercicio 4 : Unir ambos sonidos en uno nuevo

nombre@left <- nombre@left * (max(apellidos@left)/max(nombre@left))
nombre@right <- nombre@right * (max(apellidos@right)/max(nombre@right))
nombre_apellidos <- pastew(apellidos, nombre, output="Wave")

listen(nombre_apellidos)

# Ejercicio 5 : Dibujar la forma de onda de la señal resultante

plot( extractWave(nombre_apellidos, from = 1, to = length(nombre_apellidos)), main="Nombre+Apellidos" )

export(nombre_apellidos)

# Ejercicio 6 : Pasarle un filtro de frecuencia para eliminar las frecuencias entre 10000Hz y 20000Hz

filtrofrecuencia <- bwfilter(nombre_apellidos,f=44100, channel=1, n=1, from=10000, to=20000, bandpass=TRUE, listen = FALSE, output = "Wave")
listen(filtrofrecuencia)
plot(extractWave(filtrofrecuencia, from = 1, to=393984))

# Ejercicio 7 : Almacenar la señal obtenida como un fichero WAV denominado "mezcla.wav". 

writeWave(filtrofrecuencia, file.path("./sonidos/mezcla.wav"))

# Ejercicio 8 : Cargar un nuevo archivo de sonido, aplicarle eco y a continuación darle la vuelta al sonido. Almacenar la señal obtenida como un fichero WAV denominado "alreves.wav".

nuevo <- readWave('./sonidos/perro.wav')
str(nuevo)
nuevoeco <- echo(nuevo, f=22050, amp=c(0.8,0.4,0.2), delay=c(1,2,3), output="Wave")
alreves <- revw(nuevoeco, output="Wave")
listen(alreves)
writeWave(alreves, file.path("./sonidos/alreves.wav"))
