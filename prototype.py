#!/usr/bin/python3

import pygame
import math

W = 640
H = 480

HFOV = (0.73 * H)
VFOV = (0.2 * H)

def clamp(x, a, b):
    return min(max(a, x), b)

def linInterpolate(x, p1, p2):
    return (((x - p1[0]) / (p2[0] - p1[0])) * (p2[1] - p1[1]) + p1[1])

def cross(v1, v2):
    return (v1[0] * v2[1] - v2[0] * v1[1])

def sub(v1, v2):
    return [v1[0] - v2[0], v1[1] - v2[1]]

def intersectLines(p1, p2, p3, p4):
    x = cross([cross(p1, p2), p1[0]-p2[0]], [cross(p3, p4), p3[0] - p4[0]])
    x /= cross(sub(p1, p2), sub(p3, p4))
    y = cross([cross(p1, p2), p1[1]-p2[1]], [cross(p3, p4), p3[1] - p4[1]])
    y /= cross(sub(p1, p2), sub(p3, p4))
    return [x, y]

def rotateVertex(v, cosa, sina):
    n = [0] * 2
    n[0] = v[0] * sina - v[1] * cosa
    n[1] = v[0] * cosa + v[1] * sina
    return (n)

def perspectiveTransform(v, floor, ceil):
    try:
        scale = [HFOV / v[1], VFOV / v[1]];
    except ZeroDivisionError:
        scale = [100, 100]
    n = [0] * 2
    n[0] = W // 2 - int(v[0] * scale[0])
    floor = H // 2 - int(floor * scale[1])
    ceil = H // 2 - int(ceil * scale[1])
    return n, floor, ceil

class Player:
    def __init__(self):
        self.pos = [0, 0]
        self.angle = 0
        self.sin = math.sin(self.angle)
        self.cos = math.cos(self.angle)
        self.z = 6

    def playerCoors(self, v):
        n = []
        n.append(v[0] - self.pos[0])
        n.append(v[1] - self.pos[1])
        n = rotateVertex(n, self.cos, self.sin)
        return (n)

    def rotate(self, angle):
        self.angle += angle
        self.sin = math.sin(self.angle)
        self.cos = math.cos(self.angle)

    def move(self, amp):
        # n = [0, -amp]
        n = [self.cos * 0.2 * amp, self.sin * 0.2 * amp]
        self.pos[0] += n[0]
        self.pos[1] += n[1]

def clipWall(pv1, pv2):
    nearZ = 1e-4
    farZ = 5.0
    nearX = 1e-5
    farX = 20.0
    i1 = intersectLines(pv1, pv2, [-nearX, nearZ], [-farX, farZ])
    i2 = intersectLines(pv1, pv2, [ nearX, nearZ], [ farX, farZ])
    if pv1[1] < nearZ:
        if i1[1] > 0:
            pv1 = i1
        else:
            pv1 = i2
    if pv2[1] < nearZ:
        if i1[1] > 0:
            pv2 = i1
        else:
            pv2 = i2
    return pv1, pv2

def drawWall(screen, player, v1, v2, xLimits):
    #transform coords to player-centric coordinate system
    pv1 = player.playerCoors(v1)
    pv2 = player.playerCoors(v2)
    # wall is behid the player
    if (pv1[1] <= 0 and pv2[1] <= 0):
        return
    # wall is partially behid the player
    if (pv1[1] <= 0 or pv2[1] <= 0):
        pv1, pv2 = clipWall(pv1, pv2)
    # decrese wall size with increasing y relative map coordinate
    p1, floor1, ceil1 = perspectiveTransform(pv1, 0 - player.z, 10 - player.z) # here sectors floor and ceil
    p2, floor2, ceil2 = perspectiveTransform(pv2, 0 - player.z, 10 - player.z)
    if p1[0] > p2[0]:
        return
    begin = p1[0]
    end = p2[0]
    for x in range(begin, end + 1):
        try:
            ya = linInterpolate(x, [p1[0], ceil1], [p2[0], ceil2])
            yb = linInterpolate(x, [p1[0], floor1], [p2[0], floor2])
        except ZeroDivisionError:
            ya = yb = H
        ya, yb = [clamp(x, 0, H) for x in (ya, yb)]
        color = [0, 155,255]
        if (x == begin and x != 0) or (x == end and x != W-1):
            color = [255,155,255]
        pygame.draw.line(screen, [255,155,255], [x, ya], [x, ya+1], 1)
        pygame.draw.line(screen, color, [x, ya+1], [x, yb-1], 1)
        pygame.draw.line(screen, [255,155,255], [x, yb-1], [x, yb], 1)
    xLimits[0] = max(begin, xLimits[0])
    xLimits[1] = min(end, xLimits[0])

def initVetices():
    v = []
    v.append((10, 10))
    v.append((-10, 10))
    v.append((-10, -10))
    v.append((0, -1))
    v.append((10, -10))
    v.append((10, 10))
    return (v)

def procEvents(wasd):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_w:
                wasd[0] = 1
            elif event.key == pygame.K_s:
                wasd[1] = 1
            elif event.key == pygame.K_a:
                wasd[2] = 1
            elif event.key == pygame.K_d:
                wasd[3] = 1
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_w:
                wasd[0] = 0
            elif event.key == pygame.K_s:
                wasd[1] = 0
            elif event.key == pygame.K_a:
                wasd[2] = 0
            elif event.key == pygame.K_d:
                wasd[3] = 0

def handleEvents(player, wasd):
    if wasd[0]:
        player.move(1)
    elif wasd[1]:
        player.move(-1)
    elif wasd[2]:
        player.rotate(-5 / 90)
    elif wasd[3]:
        player.rotate(5 / 90)

def main():
    pygame.init()
    done = False
    screen = pygame.display.set_mode([W, H])
    clock = pygame.time.Clock()
    player = Player()
    vertices = initVetices()
    wasd = [0] * 4
    while not done:
        clock.tick(30)
        procEvents(wasd)
        handleEvents(player, wasd)
        screen.fill([0,0,0])

        #here drawing
        xLimits = [W-1, 0]
        for i, v in enumerate(vertices):
            if i != len(vertices) - 1:
                drawWall(screen, player, v, vertices[i + 1], xLimits)

        pygame.display.flip()
    pygame.quit()

if __name__ == "__main__":
    main()
