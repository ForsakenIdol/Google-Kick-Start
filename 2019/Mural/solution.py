import sys

# To run this program, type "python solution.py" inside the program folder.
# Remember that python automatically appends newline characters to print statements.
# Also remember that the double slash "//" is used for INTEGER division in python, as the single slash will return a float.

def main():
    T = int(input()) # Number of test cases
    for z in range(1, T + 1):
        N = int(input()) # Number of sections on mural
        w = str(input()) # Wall string

        wall = [] # Wall sections
        for i in range(0, len(w)):
            wall.append(int(w[i]))

        maxBeauty = 0
        muralLength = N // 2
        if (len(wall) % 2 == 1):
            muralLength += 1
        # First beauty section
        for i in range(0, muralLength):
            maxBeauty += wall[i]
        # Beauty checking routine
        currentBeauty = maxBeauty
        for i in range(1, len(wall) - muralLength + 1):
            currentBeauty -= wall[i - 1]
            currentBeauty += wall[i + muralLength - 1]
            if currentBeauty > maxBeauty:
                maxBeauty = currentBeauty
        print("Case #%d: %d" % (z, maxBeauty))
        sys.stdout.flush()

main()