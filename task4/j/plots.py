import matplotlib.pyplot as plt
import fileinput

ax = plt.gca()
ax.cla() # clear things for fresh plot
# change default range so that new circles will work
ax.set_xlim((-20,20))
ax.set_ylim((-20,20))

fig = plt.gcf()
n = int(input())
for i in range(n):
    x, y, r = map(int, input().split())
    circle = plt.Circle((x,y),r)
    fig.gca().add_artist(circle)

fig.savefig('plotcircles.png')