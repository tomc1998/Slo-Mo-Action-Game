# Level Spec
This file details the specification of the level files. They are written in
JSON, and contain lists of all the initial component values.

## Example file
```json
{
  "name": "My Example Level",
  "resources": {
    "player_anim": {
      "type": "animation",
      "data": {
        "path": "assets/animations/walk.json",
        "length": 400,
        "parts": [
          "assets/sprites/foot.png",
          "assets/sprites/foot.png",
          "assets/sprites/player.png"
        ]
      }
    }
  },
  "entities": [
    {
      "comp_game_entity": {
        "pos": [0.0, 0.0],
        "vel": [0.0, 0.0],
        "acc": [0.0, 0.0],
        "rot": 0.0,
        "mass": 10.0,
        "damping": 0.2
      },
      "comp_animation": {
        "animation": "player_anim"
      }
    }
  ]
}
```

## Preface
Some small notes before reading the rest of this document:

* Vectors are denoted as a JSON array of length N, where N is the length of the
* vector - for example, a 2D vector at (2.0, 1.0) would be denoted as `[2.0,
* 1.0]` in the JSON document.

## Overall structure
The level is stored as a top level JSON object. Inside this object there exists
3 keys - 'name', 'resources', and 'entities'. 

'name' is simply a string, indicating the name of the level to be displayed in
the level explorer.

'resources' is a map of resource names to data. These are referenced later on in the file.

'entities' is a list of entities and the components that make them up.

## Resource definitions
Resources are defined with a name as their key, then inside that object a
'type' and 'data' key. `type` is a string representing the type of resource -
these strings are defined below, underneath the relevant resource spec. `data`
is some type dependent attached data - these are also all defined below.

### Resource example
```json
"bullet_sprite": {
  "type": "sprite",
  "data": {
    "path": "assets/sprites/enemy_bullet.png"
  }
}
```

### Sprite resource

* Type name: `sprite`

* Data example: 
```json
{
  "path": "assets/sprites/enemy_bullet.png"
}
```

### Tileset resource

* Type name: `tileset`

* Data:
```json
{
  "path": "assets/sprites/tilesets/grass_test.png",
  "rows": 4,
  "columns": 4
}
```

### Animation resource

* Type name: `animation`

* Data:
```json
{
  "path": "assets/animations/walk.json",
  "length": 400,
  "parts": [
    "assets/sprites/foot.png",
    "assets/sprites/foot.png",
    "assets/sprites/player.png"
  ]
}
```

* Notes
  * The `length` key in the data object is the number of frames the animations
    lasts for.

  * The `parts` key in the data object is an in-order list of all the sprites
    in this animation.

## Entity definitions
The `entities` object is a list of objects, where each object represents a
collection of components relevant to that entity. The type of the component is
that component's key - for example, a game entity component would be present in
the entity component under the key `comp_game_entity`. The definitions of
components follow. For the meaning of each child in the component, refer to the
header file definitions of all these components (found in `src/engine/comp`).

### Game entity component
* Name: `comp_game_entity`

* Data example:
```json
  "pos": [0.0, 0.0],
  "vel": [0.0, 0.0],
  "acc": [0.0, 0.0],
  "rot": 0.0,
  "mass": 10.0,
  "damping": 0.2
```

### Sprite component
* Name: `comp_sprite`

* Data example:
```json
"comp_sprite": {
  "sprite": "bullet_sprite"
}
```

* Notes
The `sprite` key is a string referencing an item in the preceding `resources`
section.

### Animation component
* Name: `comp_animation`

* Data example:
```json
"comp_animation": {
  "animation": "player_anim"
}
```

* Notes
The `animation` key is a string referencing an item in the preceding
`resources` section.

### Tilemap component
* Name: `comp_tilemap`

* Data example:
```json
"comp_tilemap": {
  "tileset": "grass_tileset",
  "pos": [0.0, 0.0],
  "tile_size": [16.0, 16.0],
  "w": 4,
  "h": 4,
  "tiles": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 ]
}
```

* Notes
The `animation` key is a string referencing an item in the preceding
`resources` section.

# Player controller component
* Name: `comp_player_controlled`

* Data example:
This component contains no data, and should be denoted as `{}`.

### Wall component
* Name: `comp_wall`

* Data example:
```json
"comp_wall": {
  "edge_tex": "test_wall_tex",
  "vertices": [
    [0.0,   0.0],
    [100.0, 0.0],
    [100.0, 100.0],
    [0.0,   100.0]
  ]
}
```

* Notes
The `animation` key is a string referencing an item in the preceding
`resources` section.

### Circle collider component
* Name: `comp_circle_collider`

* Data example:
```json
"comp_circle_collider": {
  "rad": 8.0,
  "collides_with_walls": true
}
```

* Notes
The `animation` key is a string referencing an item in the preceding
`resources` section.

### Player killable component
* Name: `comp_player_killable`

* Data example:
```json
"comp_player_killable": {
  "life": 3
}
```

* Notes
The `animation` key is a string referencing an item in the preceding
`resources` section.
