# cub3D
## Mandatory Part

- [ ] **0. Memory Management**
   - [ ] Ensure proper allocation and deallocation of memory to avoid leaks.
- [ ] **1. Map Parsing & Validation**
  - [ ] Parse the scene file (`*.cub`) to extract textures, floor/ceiling colors, and the 2D map.
  - [ ] Validate the map ensuring it is closed (surrounded by walls) and follows the proper format (allowed characters: `0`, `1`, `N`, `S`, `E`, `W`, and spaces).
  - [ ] Handle errors (e.g., invalid file format, missing elements) gracefully.
  - [ ] The program must take as a first argument a scene description file with the `*.cub`
extension.
  - [ ] The map must be composed of only 6 possible characters: `0` for an empty space, `1` for a wall, and `N`,`S`,`E` or `W` for the player’s start position and spawning orientation.
Example:
    ```
    111111
    100101
    101001
    1100N1
    111111
    ```
  - [ ] Except for the map content, each type of element can be separated by one or
more empty lines.
  - [ ] Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
  - [ ] Except for the map, each type of information from an element can be separated
by one or more spaces.
  - [ ] The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map.
  - [ ] Except for the map, each element must begin with its type identifier (composed
by one or two characters), followed by its specific information in a strict order:
∗ North texture:
`NO ./path_to_the_north_texture`
`· identifier: NO`
`· path to the north texture`
∗ South texture:
`SO ./path_to_the_south_texture`
`· identifier: SO`
`· path to the south texture`
∗ West texture:
`WE ./path_to_the_west_texture`
`· identifier: WE`
`· path to the west texture`
∗ East texture:
`EA ./path_to_the_east_texture`
`· identifier: EA`
`· path to the east texture`
∗ Floor color:
`F 220,100,0`
`· identifier: F`
`· R,G,B colors in range [0,255]: 0, 255, 255`
∗ Ceiling color:
`C 225,30,0`
`· identifier: C`
`· R,G,B colors in range [0,255]: 0, 255, 255`
**Example** of the mandatory part with a minimalist `.cub` scene:

```
    NO ./path_to_the_north_texture
    SO ./path_to_the_south_texture
    WE ./path_to_the_west_texture
    EA ./path_to_the_east_texture
    F 220,100,0
    C 225,30,0
    1111111111111111111111111
    1000000000110000000000001
    1011000001110000000000001
    1001000000000000000000001
    111111111011000001110000000000001
    100000000011000001110111111111111
    11110111111111011100000010001
    11110111111111011101010010001
    11000000110101011100000010001
    10000000000000001100000010001
    10000000000000001101010010001
    11000001110101011111011110N0111
    11110111 1110101 101111010001
    11111111 1111111 111111111111
```

- [ ] **2. Game Initialization**
  - [ ] Initialize the miniLibX window with proper dimensions.
  - [ ] Load textures for each wall orientation (North, South, East, West) from the provided file paths.
  - [ ] Set up floor and ceiling colors as specified in the `.cub` file.
  - [ ] Initialize player position and orientation based on the map.

- [ ] **3. Raycasting Engine**
  - [ ] Implement the raycasting algorithm to compute wall distances and detect intersections.
  - [ ] Render a 3D projection of the 2D map by drawing vertical stripes representing walls.
  - [ ] Apply correct texture mapping on walls based on the side they are facing.
  - [ ] Maintain high performance and smooth rendering (double buffering recommended).

- [ ] **4. Input & Movement**
  - [ ] Handle keyboard events:
    - [ ] **Movement:** Use `W`, `A`, `S`, `D` keys to move forward, left, backward, and right.
    - [ ] **Rotation:** Use the `left` and `right` arrow keys to rotate the player’s view.
    - [ ] **Exit:** Handle the `ESC` key and the window’s close event (clicking the red cross) for a clean exit.
  - [ ] Ensure smooth integration between input handling and the game loop.

## Bonus Part

- [ ] **Wall Collisions:** Prevent the player from moving through walls.
- [ ] **Minimap System:** Implement a minimap displaying the player's position and nearby environment.
- [ ] **Interactive Doors:** Add doors that open and close.
- [ ] **Animated Sprites:** Include animated sprites for dynamic in-game effects.
- [ ] **Mouse-Based View Rotation:** Allow the player to rotate the view using the mouse.

## Allowed Functions
- **Standard C Library:**
  `malloc`, `free`, `write`, `read`, `close`

- **Input/Output & Debugging:**
  `printf`, `perror`, `strerror`, `exit`, `gettimeofday`

- **Math Library:**
  All math functions (ensure to compile with `-lm`)

- **MinilibX Library:**
  All functions available in miniLibX for window management, image handling, etc.

- **File Operations:**
  `open`

- **Libft:**
  Authorized (copy libft sources and its Makefile into a `libft` folder)

## Common Modules & Structure
1. **Main Loop**

2. **Map Parser**
   - Reads and validates the `.cub` file.
   - Extracts textures, colors, and map data.

3. **Texture Loader**

4. **Raycaster**

5. **Input Handler**

6. **Event Handler**

7. **Error Handler**

8. **Utility Functions**

9.  **Bonus Modules**

## Git Collaboration & Workflow

**Commit Prefixes:**
- `feat:` for new features and major functionalities.
- `fix:` for bug fixes or corrections.
- `docs:` for documentation updates.
- `style:` for code style improvements and refactoring.

### Git Workflow

1. **Create a New Branch:**
    ```bash
    git checkout -b branch-name
    ```

2. **Push New Branch to GitHub:**
    ```bash
    git push -u origin branch-name
    ```

3. **Stay Updated with Main Branch:**
    ```bash
    git checkout main
    git pull
    git checkout branch-name
    git merge main
    ```

4. **Merge Branch into Main:**
    ```bash
    git checkout main
    git merge branch-name
    git push
    ```

5. **Delete a Branch:**
    ```bash
    git branch -d branch-name
    git push origin --delete branch-name
    ```

- **Resolve Conflicts:**
  In case of merge conflicts, resolve them manually by editing the affected files, then add and commit the changes.

## General Resource

[Cub3D Subject](cub3d_subject.pdf)
