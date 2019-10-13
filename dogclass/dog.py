class Dog:
    species = 'caniche'

    def __init__(self, name, age):
        self.name = name
        self.age = age

bambi = Dog("Bambi", 5)
mikey = Dog("Rufus", 6)

print(("{} is {} and {} is {}.").format(bambi.name, bambi.age, mikey.name, mikey.age))

# args : int array
def get_biggest_number(*args):
    argCount = len(args)
    if argCount > 0 :
        biggestAge = -1
        for elem in args :
            if(elem > biggestAge):
                biggestAge = elem
        return biggestAge
    else:
        return 0

perro_1 = Dog("Boby", 3)
perro_2 = Dog("Zar", 1)
perro_3 = Dog("Katana", 4)

print('The oldest dog is:')
print(str(get_biggest_number(perro_1.age, perro_2.age, perro_3.age)))
