# Cub3D

First-person 3D representation of a maze using raycasting, similar to Wolfenstein 3D (1992).

## Mandatory part

The basic program that was required to pass. It only includes wall textures and a sprite ; no floor/ceiling textures, no weapons, no enemies, no game elements at all.

- git clone the repository.
- `cd` into the directory and run `make`.
- run the executable `./cub3D` with the map as an argument.
```bash
./cub3D map.cub
```
![screen](/texture/screen_mandatory.png?raw=true)

## Controls
* You can move around the maze with W A S D.

* You can also rotate the view with the directional arrows ← and →.

* You can shoot with SPACE and reload with R.

* To exit the game, press ESC or click the red cross.

## How to run the bonus part

Using make bonus will build the executable ./cub3D.

```bash
make bonus
```
run the executable `./cub3D` with the bonus map as an argument.
```bash
./Cub3D Bonus/map_bonus.cub
```

![screen](/texture/screen_bonus.png?raw=true)
