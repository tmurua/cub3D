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
       - [x] Validate that the texture file exists and has a proper extension (e.g., ".xpm").
       - [x] Ensure that duplicate texture entries are not allowed.
   2.4. **Process Color Lines**
       - [x] Remove the identifier (e.g., "F " or "C ") from the line and store the color (currently via ft_atoi).
       - [x] Split the remainder by commas.
       - [x] Trim each resulting substring.
       - [x] Validate that there are exactly three numeric parts.
       - [x] Convert each part to an integer and ensure it’s between 0 and 255.
       - [x] Combine the three values into a single integer (0xRRGGBB).
       - [x] Ensure that duplicate color entries are not allowed.
   2.5. **Final Header Validation**
       - [x] After processing header lines, verify that all required headers (4 textures and 2 colors) are present.
       - [x] Report an error if any header is missing.

3. **Map Layout Parsing**
   3.1. **Determine Transition from Headers to Map**
       - [x] In the main parsing loop, detect when header processing is complete (e.g., when a line starts with '1' or contains map-specific characters).
       - [x] Set a flag (e.g., `header_done`) when transitioning from header lines to map lines.
   3.2. **Extract Map Lines**
       - [ ] For each line after headers, trim the line.
       - [ ] Append the trimmed map line to a dynamically allocated array (e.g., `t_game->map->map`).
   3.3. **Validate Allowed Map Characters**
       - [ ] Iterate through the map array.
       - [x] Ensure each character is one of: `'0'`, `'1'`, `'N'`, `'S'`, `'E'`, `'W'`, or space.
       - [ ] Report an error if any invalid character is found.

4. **Advanced Map Validation**
   4.1. **Map Enclosure Check (Flood Fill)**
       - [ ] Implement a flood-fill algorithm starting from the player’s starting position (or any '0' cell).
       - [ ] Ensure the flood-fill does not reach the map boundary (indicating a leak).
       - [ ] Report an error if the map is not properly enclosed.
   4.2. **Player Position Validation**
       - [ ] Ensure that exactly one player starting position exists in the map.
       - [ ] Store the player’s coordinates and view direction in `t_game`.
   4.3. **(Optional) Map Rectangularity**
       - [ ] Check if the map is rectangular.
       - [ ] If not, convert the map into a rectangle (using padding) with a helper function.

5. **Error Handling & Memory Management**
   5.1. **Centralized Error Reporting**
       - [x] Create `error_utils.c` with `print_err()` (returning -1) and `malloc_error()`.
   5.2. **Standardize Return Conventions**
       - [x] Ensure functions return 1 on success and -1 on error.
   5.3. **Memory Cleanup**
       - [ ] Verify that all allocated memory is freed on error.
       - [ ] Implement additional cleanup functions if needed (e.g., for partially parsed data).
   5.4. **Integrate Error Functions**
       - [ ] Update all modules (parsing, file reading, header processing, map validation) to use `print_err()` and `malloc_error()` consistently.

6. **Integration and Testing**
   6.1. **Unit Testing Individual Functions**
       - [ ] Test file extension checking.
       - [ ] Test file opening and empty file detection.
       - [ ] Test header line parsing (for both texture and color lines) with valid and invalid inputs.
       - [ ] Test map layout parsing and character validation.
       - [ ] Test flood-fill and player position validation.
   6.2. **Integration Tests**
       - [ ] Run the complete parsing flow with known valid .cub files.
       - [ ] Run the parsing flow with various invalid files (wrong extension, missing headers, invalid map, etc.).
   6.3. **Refactor and Optimize**
       - [ ] Review and refactor code based on test results and code review.
       - [ ] Ensure code follows SRP, DRY, and KISS principles throughout.

7. **Future Enhancements**
   7.1. **Improve Error Messaging**
       - [ ] Add error codes or more detailed context to error messages.
   7.2. **Optimize Parsing Performance**
       - [ ] Refactor performance-critical sections as needed.
   7.3. **Extend Map Validation**
       - [ ] Enhance the flood-fill algorithm for edge cases.
       - [ ] Support more advanced map features if required by the project.

