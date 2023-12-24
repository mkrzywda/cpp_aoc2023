import sys
import z3

D = open(sys.argv[1]).read().strip()
L = D.split('\n')
G = [[c for c in row] for row in L]
R = len(G)
C = len(G[0])

S = []
for line in L:
    pos, vel = line.split('@')
    x, y, z = pos.split(', ')
    vx, vy, vz = vel.split(', ')
    x, y, z = int(x), int(y), int(z)
    vx, vy, vz = int(vx), int(vy), int(vz)
    S.append((x, y, z, vx, vy, vz))

n = len(S)
ans = 0
for i in range(len(S)):
    for j in range(i + 1, len(S)):
        x1, x2, x3, x4 = S[i][0], S[i][0] + S[i][3], S[j][0], S[j][0] + S[j][3]
        y1, y2, y3, y4 = S[i][1], S[i][1] + S[i][4], S[j][1], S[j][1] + S[j][4]

        den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
        if den != 0:
            px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / den
            py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / den
            validA = (px > x1) == (x2 > x1)
            validB = (px > x3) == (x4 > x3)

            if 200000000000000 <= px <= 400000000000000 and 200000000000000 <= py <= 400000000000000 and validA and validB:
                ans += 1

print(f"Part A: {ans}")

x, y, z, vx, vy, vz = z3.Real('x'), z3.Real('y'), z3.Real('z'), z3.Real('vx'), z3.Real('vy'), z3.Real('vz')
T = [z3.Real(f'T{i}') for i in range(n)]
SOLVE = z3.Solver()
for i in range(n):
    SOLVE.add(x + T[i] * vx - S[i][0] - T[i] * S[i][3] == 0)
    SOLVE.add(y + T[i] * vy - S[i][1] - T[i] * S[i][4] == 0)
    SOLVE.add(z + T[i] * vz - S[i][2] - T[i] * S[i][5] == 0)

res = SOLVE.check()
if res == z3.sat:
    M = SOLVE.model()
    print(f"Part B: {M.eval(x + y + z)}")
else:
    print("Part B: No solution found.")
