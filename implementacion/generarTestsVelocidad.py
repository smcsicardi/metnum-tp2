import random

def generarTestsVelocidad(tipo,col,fil):
    for i in range(41):
        file = open("tests/testVelocidad" + tipo + str(i+1) + ".in" , "w+")
        
        # src col fil cantPers cantImgPorPersonas cantCompPrin
        # pongo 16 componentes principales
        file.write("../data/ImagenesCaras" + tipo + "/ " + str(col) + " " + str(fil) + " " + str(i+1) + " 10 16 \n\n")

        for j in range(i+1):
            file.write("s" + str(j+1) + "/ 1 2 3 4 5 6 7 8 9 10\n")

        # Esto lo agrego por si acaso, pero no se va a usar
        file.write("\n1\n")
        file.write("../data/ImagenesCarasRed/s1/1.pgm\n")
        file.close()
    
    return

generarTestsVelocidad("", 112, 92)
generarTestsVelocidad("Red", 28, 23)