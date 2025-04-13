# TODO: Map Conversion and Static Pre-Conversion Plan

## Overview
The goal is to replace the currently hardcoded 2D integer array (used by the raycaster) with a dynamically allocated 1D pointer and then statically pre-convert the parsed map (from `t_game->map.lines`, an array of strings) into an integer grid format expected by the raycaster. This plan details each step while emphasizing robust memory management and adherence to Clean Code and Norminette standards.

## 1. Modify the `t_data` Structure

- **Action:** Replace the hardcoded 2D array with a 1D integer pointer.
- **Details:**
  - In `t_data`, change:
    ```c
    // Old declaration
    int map[mapWidth][mapHeight];
    ```
    to
    ```c
    int *map;
    int map_rows;   // Number of rows from the parsed map
    int map_cols;   // Number of columns (max row length after padding)
    ```
- **Clean Code:**
  - Use meaningful names for new fields.
  - Keep the structure clear and well-documented.

## 2. Implement Dynamic Memory Allocation & Deallocation

- **Action:** Create helper functions for map allocation and freeing.
- **Details:**
  - **Allocation Function:**
    ```c
    int *allocate_map(int rows, int cols) {
        int *map = malloc(rows * cols * sizeof(int));
        if (!map)
            return NULL; // Handle allocation failure appropriately.
        return map;
    }
    ```
  - **Deallocation Function:**
    ```c
    void free_map(int *map) {
        if (map)
            free(map);
    }
    ```
- **Clean Code:**
  - Check for `NULL` pointers.
  - Use clear, self-explanatory function names.

## 3. Create an Indexing Helper

- **Action:** Define a helper macro or inline function to convert 2D coordinates to a 1D index.
- **Details:**
  - Example macro:
    ```c
    #define MAP_INDEX(x, y, cols) ((x) * (cols) + (y))
    ```
- **Clean Code:**
  - Document the macro’s purpose so that later code remains readable.

## 4. Implement the Map Pre-Conversion Function

- **Action:** Write a function that converts the parsed map (array of strings) into a 1D integer array.
- **Details:**
  - **Prototype:** `int *convert_parsed_map(t_game *game, int *out_rows, int *out_cols);`
  - **Steps:**
    1. **Determine Dimensions:**
       - Iterate over `game->map.lines` to count rows.
       - Compute the maximum row length (after trimming and padding) as `cols`.
       - Assign these to `*out_rows` and `*out_cols`.
    2. **Allocate Memory:**
       - Use `allocate_map(*out_rows, *out_cols)`.
    3. **Convert Each Cell:**
       - Loop over each row and each character.
       - For each cell:
         - If the character is `'1'`, store `1` (wall).
         - For other valid characters (e.g., `'0'`, spaces, or player positions already handled), store `0`.
         - Handle padding by filling missing characters in shorter rows with wall values (`1`), or as defined.
- **Clean Code:**
  - Break down the function into sub-functions if needed (e.g., `convert_row()`).
  - Use descriptive variable names.
  - Add comments describing each major step.

## 5. Integrate Pre-Conversion into the Initialization Process

- **Action:** Replace the hardcoded map with a call to the conversion function.
- **Details:**
  - In `load_parsed_map(t_data *d, t_game *game)`, instead of copying from a hardcoded map:
    ```c
    int rows, cols;
    d->map = convert_parsed_map(game, &rows, &cols);
    if (!d->map)
        return; // Handle conversion error.
    d->map_rows = rows;
    d->map_cols = cols;
    ```
- **Clean Code:**
  - Ensure proper error handling.
  - Comment the integration point to explain the transition.

## 6. Refactor Raycaster and Movement Functions

- **Action:** Update all functions that previously indexed `d->map` as a 2D array.
- **Details:**
  - Replace instances of accessing `d->map[x][y]` with:
    ```c
    d->map[MAP_INDEX(x, y, d->map_cols)]
    ```
  - Functions to update include (but are not limited to):
    - `move()`
    - `strafe()`
    - `digital_differential_analyzer()`
    - `steer_car()`
- **Clean Code:**
  - Use the indexing helper to maintain DRY principles.
  - Test each function separately to ensure proper behavior.

## 7. Validate Memory Management and Edge Cases

- **Action:** Ensure all dynamic allocations are paired with proper deallocation.
- **Details:**
  - Free the 1D map pointer on game exit or re-initialization using `free_map()`.
  - Handle cases where the parsed map dimensions might be unexpected or invalid gracefully.
- **Clean Code:**
  - Keep error messages simple and informative.
  - Use consistent error-handling patterns as done in your other modules.

## 8. Code Review and Norminette Compliance

- **Action:** Run the updated code through Norminette and perform a code review.
- **Details:**
  - Fix any formatting or stylistic issues as flagged by Norminette.
  - Peer review the new code segments to ensure clarity and maintainability.
- **Clean Code:**
  - Adhere strictly to the 42 Norm standard.
  - Ensure that all variable and function names remain meaningful and concise.

## Summary
By following these detailed steps, you will:

- Replace the 2D array with a 1D pointer for map data storage.
- Implement a robust, static pre-conversion function that translates the parsed string-based map into the integer grid expected by your raycasting engine.
- Maintain clean, maintainable, and Norm-compliant code throughout the process.

This approach offers clear separation of concerns, efficient memory management, and minimal changes to your existing raycaster logic beyond the conversion of map data.
