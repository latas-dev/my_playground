# # Generador Congruencial Mixto de Números Rectangulares
# A = [1,2,3]
# # .^ = Operación Broadcast: eleva al cubo a cada número en el arreglo
# B = A .^ 3
using Printf

struct Generador
    a::Int32    
    x0::Int32   # primer valor de entrada  
    c::Int32     
    m::Int32    # periodo 
end

function GeneracionMixta(gen::Generador)
    xn = gen.x0
    for i = 1:gen.m
        Printf.@printf("%2d\t%2d\t", i, xn)
        xn = (gen.a * xn + gen.c) % gen.m
        Printf.@printf("%2d\t%2d/%2d\n", xn, xn, gen.m)
        if xn == gen.x0 && i != gen.m
            println("\nEl periodo es incompleto y los números rectangulares son rechazados.")
            return 0
        end
    end
    if xn == gen.x0
        println("\nEl periodo es completo y los números rectangulares son aceptados.")
    else
        println("\nEl periodo es incompleto y los números rectangulares son rechazados.")

    end
end

function GeneracionMultiplicativa(gen::Generador)
    xn = gen.x0
    pe = gen.m / 4
    for i = 1:pe
        Printf.@printf("%2d\t%2d\t", i, xn)
        xn = (gen.a * xn) % gen.m
        Printf.@printf("%2d\t%2d/%2d\n", xn, xn, gen.m)
        if xn == gen.x0 && i != pe
            println("\nEl periodo es incompleto y los números rectangulares son rechazados.")
            return 0
        end
    end
    if xn == gen.x0
        println("\nEl periodo es completo y los números rectangulares son aceptados.")
    else
        println("\nEl periodo es incompleto y los números rectangulares son rechazados.")

    end
end

# config_1 = Generador(8, 15, 16, 100)
config = Generador(9, 8, 13, 32)

GeneracionMixta(config)
# GeneracionMultiplicativa(config_2)