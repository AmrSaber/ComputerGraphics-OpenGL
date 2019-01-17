#! /user/bin/env python3

import matplotlib.pyplot as plt
import argparse

__verbos__ = False
__no_draw__ = False

def main():

	# set and parse input arguments
	parser = argparse.ArgumentParser(description='Draws pixels of line or circle with given coordinates')
	parser.add_argument('-tl', action='store_true', help='Test Line: Draw sample test line')
	parser.add_argument('-tc', action='store_true', help='Test Circle: Draw sample test circle')
	parser.add_argument('-v', action='store_true', help='Verbos: Print generated points')
	parser.add_argument('-nd', action='store_true', help='No Draw: Don\'t draw the points')
	parser.add_argument('--line', nargs=4, metavar='int', required=False, type=int, help='Accepts 4 integers (x, y) of start and (x, y) of end respectivly')
	parser.add_argument('--circle', nargs=3, metavar='int', required=False, type=int, help='Accepts 3 integers (x, y) of center and radius of the circle respectivly')
	args = parser.parse_args()

	global __verbos__, __no_draw__
	__verbos__ = args.v
	__no_draw__ = args.nd

	if args.tl: drawLine([3, 5], [8, 13])
	elif args.tc: drawCircle([12, 19], 8)
	elif args.line: drawLine((args.line[0], args.line[1]), (args.line[2], args.line[3]))
	elif args.circle: drawCircle((args.circle[0], args.circle[1]), args.circle[2])
	else: parser.print_help()

# c is list of (x, y), r is int
def drawCircle(c, r):
	points = _getCirclePoints(r)
	points = [[e[0] + c[0], e[1] + c[1]] for e in points]

	myPrint(points)

	if __no_draw__: return
	xs = [e[0] for e in points]
	ys = [e[1] for e in points]

	plt.scatter(xs, ys)

	plt.gcf().canvas.set_window_title('Circle')
	plt.xticks(range(min(xs), max(xs) + 1))
	plt.yticks(range(min(ys), max(ys) + 1))
	plt.grid(True)

	plt.show()

def drawLine(start, end):
	points = _getLinePoints(start, end)

	myPrint(points)

	if __no_draw__: return
	xs = [e[0] for e in points]
	ys = [e[1] for e in points]

	plt.scatter(xs, ys)

	plt.gcf().canvas.set_window_title('Line')
	plt.xticks(range(min(xs) - 1, max(xs) + 2))
	plt.yticks(range(min(ys) - 1, max(ys) + 2))
	plt.grid(True)

	plt.show()

def _getCirclePoints(r):
	current = [0, r]
	p = 1 - r
	pnts = [current[:]]

	# this block is the core of the algoithm
	while current[0] < current[1] :
		if p >= 0 :
			current[1] -= 1
			p -= 2 * current[1]
		current[0] += 1
		p += 2 * current[0] + 1
		pnts.append(current[:])

	pntsRO = [[e[1], e[0]] for e in pnts]
	pnts += pntsRO[::-1]

	pntsRQ = [[e[0], -e[1]] for e in pnts]
	pnts += pntsRQ[::-1]

	pntsRH = [[-e[0], e[1]] for e in pnts]
	pnts += pntsRH[::-1]

	return pnts

# start and end are tuples of 2 items
def _getLinePoints(start, end):

	start, end = list(start[:]), list(end[:])

	slope = (end[1] - start[1]) / (end[0] - start[0])

	isNegative = False

	if slope < 0 :
		isNegative = True
		start[0] *= -1
		end[0] *= -1
		slope *= -1

	if slope > 1:
		end = end[::-1]
		start = start[::-1]

	if start[0] > end[0]: start, end = end, start

	dx, dy = end[0] - start[0], end[1] - start[1]
	p = 2 * dy - dx
	current = start[:]
	pnts = [start[:]]

	# this block is the core of the algoithm
	while current != end:
		if p >= 0 :
			current[1] += 1
			p -= 2 * dx
		current[0] += 1
		p += 2 * dy
		pnts.append(current[:])

	if slope > 1:
		pnts = [e[::-1] for e in pnts]

	if isNegative:
		for i in range(len(pnts)):
			pnts[i][0] *= -1

	return pnts

def myPrint(pnts):
	if not __verbos__: return
	for x, y in pnts: print('(%d, %d)' % (x, y))

if __name__ == '__main__': main()
