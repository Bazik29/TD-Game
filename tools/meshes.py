import json
import math


def make_polyhedron(r, n):
    angle = 2*math.pi/n

    vertices = [{"x": 0, "y": 0}]
    indices = []

    for i in range(n):
        x = r * math.cos(i*angle)
        y = r * math.sin(i*angle)

        vertices.append({
            "x": x,
            "y": y
        })

        a = i+1
        b = i+2
        if b > n:
            b = 1

        if a % 2 == 0:
            indices.append(0)
            indices.append(a)
            indices.append(b)
        else:
            indices.append(a)
            indices.append(b)
            indices.append(0)

    return {
        "vertices": vertices,
        "indices": indices
    }

def make_square(r):
    return {
    "vertices": [
        {
            "x": -r,
            "y": r
        },
        {
            "x": -r,
            "y": -r
        },
        {
            "x": r,
            "y": -r
        },
        {
            "x": r,
            "y": r
        }
    ],
    "indices": [
        0,
        1,
        2,
        2,
        3,
        0
    ]
}

def make_arrow(r):
    return {
    "vertices": [
        {
            "x": 0,
            "y": r
        },
        {
            "x": r,
            "y": -r
        },
        {
            "x": 0,
            "y": -r/2.0
        },
        {
            "x": -r,
            "y": -r
        }
    ],
    "indices": [
        0,
        1,
        2,
        2,
        3,
        0
    ]
}


enemy = make_polyhedron(0.5, 8)

with open("../resources/enemies/enemy_mesh.json", "w") as write_file:
    json.dump(enemy, write_file, indent=4)

tower = make_square(0.5)

with open("../resources/towers/tower_mesh.json", "w") as write_file:
    json.dump(tower, write_file, indent=4)

shell = make_arrow(0.5)

with open("../resources/towers/shell_mesh.json", "w") as write_file:
    json.dump(tower, write_file, indent=4)
