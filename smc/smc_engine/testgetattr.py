import importlib

FUNCS_MAP = {
    'printer': {'module': 'smc_engine.testgetattr', 'class': 'MyClass', 'function': 'printer'},
}


class MyClass:
    def __init__(self):
        print('init')


def printer():
    print('printer')


def main():
    func = 'printer'

    func_module = importlib.import_module(FUNCS_MAP.get(func).get('module'))
    func_class = getattr(func_module, FUNCS_MAP.get(func).get('class'))

    func_class()

    func_function = getattr(func_module, FUNCS_MAP.get(func).get('function'))

    func_function()


if __name__ == '__main__':
    main()
