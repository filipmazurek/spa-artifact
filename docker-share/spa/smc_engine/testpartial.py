import functools

def giveMePartial(start_int):
    class NumberHolder:
        def __init__(self, int_1, int_2):
            self.int_1 = int_1
            self.int_2 = int_2

        def printer(self):
            print(self.int_1, self.int_2)

    return functools.partial(NumberHolder, int_2=start_int)

almostNumber = giveMePartial(1)
realNumber = almostNumber(2)
realNumber.printer()
