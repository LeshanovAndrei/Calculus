from itertools import combinations
#import colorama

def print_command() -> None:
    commands = {
        "polynomial" : "\t- settin up Lagrange polynomial via function table",
        "value"      : "\t\t- calculating function vaule in a point (only if polynomial is set)",
        "help"       : "\t\t- listing all commands (you're here!)",
        "exit"       : "\t\t- exiting the program\n"
    }
    print('')
    for key in commands.keys():
        print(key  + commands[key])

def lagrange_polynomial_point(polynomial:list, x:float) -> float:
    '''
    просчет значения функции в точке по полиному Лагранжа
    '''
    return round(sum([x**(len(polynomial) - i - 1) * coef for i, coef in enumerate(polynomial)]), 5)

def dispenser(input:str) -> list:
    '''
    This function splits the string to a list of floats
    '''
    if(type(input) is not str): 
        raise ValueError
    array = input.split() 
    for i in range(len(array)):
        array[i] = float(array[i])
    return array

def print_polynomial(polynomial:list) -> None:
    '''
    красивый вывод полинома
    '''
    print(end='')
    length = len(polynomial)
    previous_zero = True
    for i in range(length):
        if polynomial[i] != 0:
            if polynomial[i] > 0 and not previous_zero:
                print('+ ', end = '')
            elif polynomial[i] < 0:
                print('- ', end = '')
            if abs(polynomial[i]) != 1 and i != length - 1:
                print(abs(polynomial[i]), end = '')
                previous_zero = False
            if i != length - 1:
                print('x', end = '')
                if i < length - 1:
                    print('^' + str(length - i - 1) + ' ', end = '')
                else:
                    print(' ', end = '')
            else:
                print(abs(polynomial[i]), end = '')
                previous_zero = False
        else:
            previous_zero = True
    

def prod(ls:tuple) -> float:
    '''
    product of tuple elements
    '''
    acc = 1
    for elem in ls:
        acc *= -elem
    return acc

def calculate_K(i:int, xs:list, ys:list) -> float:
    '''
    constant part, y[i]/prod of (x_i - x_j), where i!=j
    '''
    res = ys[i]
    for j in range(len(xs)):
        if (j != i):
            res /= xs[i] - xs[j]
    return res

def get_product_of_combinations(input_list:list, size: int) -> float:
    '''
    перемножение элементов кортежей в подписках для каждой степени,
    и возвращение того, что домножается на K_i и потом складывается
    в ячейку для нужного коэф.
    '''
    ls = [[j for j in combinations(input_list, i)] for i in range(size)]
    result = [0] * length
    for i, sublist in enumerate(ls):
        result[i] = sum([prod(subtuple) for subtuple in sublist])
    return result

def make_it_nice(input:list) -> list:
    '''
    округляет и убирает -0.0
    '''
    polynomial = [round(j, 5) for j in input]
    for i in range(len(polynomial)):
        if polynomial[i] == -0.0:
            polynomial[i] = abs(polynomial[i])
    return polynomial

def lagrange_polynomial(xs:list, ys:list) -> list:
    '''
    основаная функция для нахождения коэф.
    полинома Лагранжа
    '''
    length = len(xs)
    polynomial = [0] * length
    ks = [calculate_K(i, xs, ys) for i in range(length)]
    for i in range(length):
        comb = [xs[j] for j in range(length) if j != i]
        tmp = get_product_of_combinations(comb, length)
        for j, val in enumerate(tmp):
            polynomial[j] += ks[i] * val
    return make_it_nice(polynomial)

def main():
    #colorama.init()
    xs = list()
    ys = list()
    length = int()

    polynomial = list()    
    print( "Welcome to Function Interpolation program!"  + "\n\nEnter \"help\" for all commands.")
    while True:
        print("Enter command: ", end = '')
        input_line = input()
        if input_line == "polynomial":
            try:
                print("Enter x values: ", end = '')
                xs = dispenser(input())
                print("Enter y values: ", end = '')
                ys = dispenser(input())
                print( end = '')
                if (len(xs) != len(ys)):
                    raise RuntimeError
                length = len(xs)
                polynomial = lagrange_polynomial(xs, ys)
                print_polynomial(polynomial)
            except ValueError:
                print("You entered non-values for X or Y. Try again.")
            except RuntimeError:
                print("You entered inequal numbers of values. Numbers of X and Y should be equal! Try again.")
            except:
                print("Unknown error happened.")
        elif input_line == "value":
            if len(polynomial) < 1:
                print("No polynomial set!")
            else:
                try:
                    print("Enter single x value: ", end = '')
                    x = float(input())
                    print(str(lagrange_polynomial_point(polynomial, x)))
                except ValueError:
                    print("You entered invalid value. Try again.")
                except:
                    print("Unknown error happened.")
        elif input_line == "help":
            print_command()
        elif input_line == "exit":
            print("Goodbye!")
            exit(0)
        else:
            print("Unknown command!")

if __name__ == "__main__":
    main()
