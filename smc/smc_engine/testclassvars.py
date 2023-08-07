class Tester:


    def __init__(self, num):
        self.created_data = []
        self.my_num = num

    def incr(self):
        self.created_data.append(self.my_num)

    def print_my_var(self):
        print(self.created_data)

a = Tester(1)
b = Tester(2)

a.incr()
a.incr()
b.incr()

a.print_my_var()
b.print_my_var()