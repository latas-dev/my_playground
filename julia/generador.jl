# # Generador Congruencial Mixto de Números Rectangulares
# A = [1,2,3]
# # .^ = Operación Broadcast: eleva al cubo a cada número en el arreglo
# B = A .^ 3

import .Sys

using Printf


const FILE_PATH = "./resultados.txt"

struct Generador
    a::Int32    
    x0::Int32   # primer valor de entrada  
    c::Int32     
    m::Int32    # periodo 
end

function clearScreen()
    if Sys.iswindows()
        ccall(:_setmode, Cint, (Cint, Cint), STDERR_FILENO, 0x0002)
        ccall((:printf, "libc"), Cint, (Ptr{UInt8},), "\033[2J\033[1;1H")
    else
        print("\033[2J\033[1;1H")
    end
end

function crearGenerador()
    option = 0

    while option > 2 || option < 1
        clearScreen()
        Printf.@printf("Elija entre:\n
                        1> Generador Mixto.\n
                        2> Generador Multiplicativo.\n
                        Ingrese un número (1 o 2): ")
        buffer = readline()
        option = parse(Int, buffer)
    end

    if option == 1
        clearScreen()
        Printf.@printf("Ingrese el primer valor: ")
        buffer = readline()
        x0 = parse(Int, buffer)
        Printf.@printf("Ingrese el periodo: ")
        buffer = readline()
        m = parse(Int, buffer)
        Printf.@printf("Ingrese la constante multiplicativa: ")
        buffer = readline()
        a = parse(Int, buffer)
        Printf.@printf("Ingrese la constante de adición: ")
        buffer = readline()
        c = parse(Int, buffer)

        generacionMixta(Generador(a, x0, c, m))

    elseif option == 2
        clearScreen()
        Printf.@printf("Ingrese el primer valor: ")
        buffer = readline()
        x0 = parse(Int, buffer)
        Printf.@printf("Ingrese el periodo: ")
        buffer = readline()
        m = parse(Int, buffer)
        Printf.@printf("Ingrese la constante multiplicativa: ")
        buffer = readline()
        a = parse(Int, buffer)
        c = 0

        generacionMultiplicativa(Generador(a, x0, c, m))

    end
end
    

function generacionMixta(gen::Generador)
    output = open(FILE_PATH, "w")

    xn = gen.x0
    for i = 1:gen.m
        write(output, "%2d\t%2d\t", i, xn)
        xn = (gen.a * xn + gen.c) % gen.m
        write(output, "%2d\t%2d/%2d\n", xn, xn, gen.m)
        if xn == gen.x0 && i != gen.m
            write(output, "\nEl periodo es incompleto y los números rectangulares son rechazados.\n")
            return 0
        end
    end
    if xn == gen.x0
        write(output, "\nEl periodo es completo y los números rectangulares son aceptados.\n")
    else
        write(output, "\nEl periodo es incompleto y los números rectangulares son rechazados.\n")
        
    end
    close(output)
end

function generacionMultiplicativa(gen::Generador)
    output = open(FILE_PATH, "w")

    xn = gen.x0
    pe = gen.m / 4
    for i = 1:pe
        buffer = sprintf("%2d\t%2d\t", i, xn)
        write(output, buffer)
        xn = (gen.a * xn) % gen.m
        buffer = sprintf("%2d\t%2d/%2d\n", xn, xn, gen.m)
        write(output, buffer)
        if xn == gen.x0 && i != pe
            write(output, "\nEl periodo es incompleto y los números rectangulares son rechazados.")
            return 0
        end
    end
    if xn == gen.x0
        write(output, "\nEl periodo es completo y los números rectangulares son aceptados.")
    else
        write(output, "\nEl periodo es incompleto y los números rectangulares son rechazados.")

    end
    close(output)
end

# # config_1 = Generador(8, 15, 16, 100)
# config = Generador(9, 8, 13, 32)

# GeneracionMixta(config)
# # GeneracionMultiplicativa(config_2)
crearGenerador()