#! /user/bin/env python3

import numpy as np

def main():
	p = np.array([1, 3, 1]).T
	Trans = T(3, 7) @ R(60) @ T(-3, -7)

	print("Transformation Matrix:\n", np.around(Trans, 3))
	print()
	print("Resultant Point:\n", np.round(Trans @ p, 3))

# Traslation
def T(tx, ty):
	return np.array([[1, 0, tx], [0, 1, ty], [0, 0, 1]])

# Rotation
def R(a, isRad = False):
	if not isRad: a = a * np.pi / 180
	sin = np.sin(a)
	cos = np.cos(a)
	return np.array([[cos, -sin, 0], [sin, cos, 0], [0, 0, 1]])

# Scale
def S(sx, sy):
	return np.array([[sx, 0, 0], [0, sy, 0], [0, 0, 1]])


if __name__ == '__main__': main()
