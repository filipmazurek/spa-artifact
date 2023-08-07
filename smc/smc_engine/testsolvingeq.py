from sympy import symbols, solve
from math import ceil

proportion = 0.9
confidence = 0.9

x = symbols('x')
expr_false = - confidence + 1 - (1-proportion)**x

sol = solve(expr_false)
print(sol)

expr_true = - confidence + 1 - proportion**x
sol = solve(expr_true)
print(ceil(sol[0]))