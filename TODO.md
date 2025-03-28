# Parsing Module TODO Checklist

1. **Command-Line & File I/O Validation**
   1.1. **Validate Command-Line Arguments**
       - [x] Ensure exactly 2 arguments are provided.
       - [x] Print a usage message if the argument count is incorrect.
   1.2. **File Extension Check**
       - [x] Implement `has_cub_extension()` to compare the last 4 characters of the filename with ".cub".
   1.3. **Open the File**
       - [x] Implement `open_cub_file()` to:
           - [x] Check that the file has a ".cub" extension.
           - [x] Open the file and return the file descriptor.
           - [x] Use `print_err()` to report errors and return -1.
   1.4. **Validate File Non-Emptiness**
       - [x] Read the first non-empty (trimmed) line.
       - [x] If no non-empty line is found, call `print_err("File is empty")` and return -1.

2. **Header Parsing (Textures & Colors)**
   2.1. **Define Valid Header Identifiers**
       - [x] Confirm allowed identifiers: `"NO "`, `"SO "`, `"WE "`, `"EA "`, `"F "`, `"C "`.
   2.2. **Header Line Check**
       - [x] Create `is_header_line()` to check if a trimmed line is a header.
   2.3. **Process Texture Lines**
       - [x] Remove the identifier (e.g., "NO ") from the header line.
       - [x] Validate that the texture file exists and has a proper extension (".xpm").
       - [x] Ensure that duplicate texture entries are not allowed.
   2.4. **Process Color Lines**
       - [x] Remove the identifier (e.g., "F " or "C ") from the line.
       - [x] Split the remainder by commas.
       - [x] Trim each resulting substring.
       - [x] Validate that there are exactly three numeric parts.
       - [x] Convert each part to an integer (each 0–255).
       - [x] Combine the three values into a single integer (0xRRGGBB).
       - [x] Ensure that duplicate color entries are not allowed.
   2.5. **Final Header Validation**
       - [x] After processing header lines, verify that all required headers (4 textures and 2 colors) are present.
       - [x] Report an error if any header is missing.

3. **Map Layout Parsing**
   3.1. **Collect Map Lines**
       - [x] In the main parsing loop, detect when header processing is complete.
       - [x] Set a flag (e.g., `found_non_empty`) when transitioning from header lines to map lines.
       - [x] For each non-header line, trim it and append it to a dynamically allocated array (`t_game->map`).
   3.2. **Validate Allowed Map Characters**
       - [x] Ensure each character in every row is one of: `'0'`, `'1'`, `'N'`, `'S'`, `'E'`, `'W'`, or space.
       - [x] Report an error if any invalid character is found.

4. **Advanced Map Validation**
   4.1. **Map Enclosure Check (Flood Fill)**
       - [x] Implement a flood-fill algorithm starting from the player’s starting position (or any '0' cell).
       - [x] Ensure the flood-fill does not leak outside the map boundaries.
       - [x] Report an error if the map is not properly enclosed.
   4.2. **Player Position Validation**
       - [x] Ensure that exactly one player starting position exists in the map.
       - [x] Store the player’s coordinates and view direction in `t_game`.
   4.3. **Map Rectangularity**
       - [x] Check if the map is rectangular.
       - [x] If not, convert the map into a rectangle (using padding) with a helper function.

5. **Error Handling & Memory Management**
   5.1. **Centralized Error Reporting**
       - [x] Create `error_utils.c` with `print_err()` (returning -1) and `malloc_error()`.
   5.2. **Standardize Return Conventions**
       - [x] Ensure functions return 1 on success and -1 on error.
   5.3. **Memory Cleanup on Error**
       - [x] Ensure that all allocated memory is freed on error (e.g., via a `clean_game()` function).

6. **Integration and Testing**
   6.1. **Unit Testing Individual Functions**
       - [x] Test file extension checking.
       - [x] Test file opening and empty file detection.
       - [x] Test header line parsing (texture and color lines) with valid and invalid inputs.
       - [ ] Test map layout parsing and character validation.
       - [ ] Test flood-fill and player position validation.
   6.2. **Integration Tests**
       - [x] Run the complete parsing flow with known valid `.cub` files.
       - [x] Run the parsing flow with various invalid files (wrong extension, missing headers, invalid map, etc.).
   6.3. **Refactor and Optimize**
       - [ ] Review and refactor code based on test results and code review.
       - [ ] Ensure code follows SRP, DRY, and KISS principles throughout.


