import random

def strImagenes(cant):
    res = "/"
    for i in range(cant):
        res += (" " + str(i+1))

    res += "\n"
    return res

def generarTestsVelocidad(tipo,col,fil,cantPers,cantImgPorPer,cantCompPrin):
    strImg = strImagenes(cantImgPorPer)

    for i in range(cantPers):
        file = open("tests/testVelocidad" + tipo + str(i+1) + ".in" , "w+")

        # src col fil cantPers cantImgPorPer cantCompPrin
        # pongo 16 componentes principales
        file.write("../data/ImagenesCaras" + tipo + "/ " + str(col) + " " + str(fil) + " " + str(i+1) + 
                            " " + str(cantImgPorPer) + " " + str(cantCompPrin) + " \n\n")

        for j in range(i+1):
            file.write("s" + str(j+1) + strImg)

        # Esto lo agrego por si acaso, pero no se va a usar
        file.write("\n1\n")
        file.write("../data/ImagenesCarasRed/s1/1.pgm\n")
        file.close()
    
    return

# Imagenes grandes
generarTestsVelocidad("", 112, 92, 41, 5, 16)

# Imagenes chicas
generarTestsVelocidad("Red", 28, 23, 41, 10, 16)