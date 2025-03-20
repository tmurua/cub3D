- [ ] **FINISH PARSING LOGIC**

  - [ ] **1. File Format Validation:**
    - [x] Ensure the file has the proper extension (.cub) and can be opened.
    - [ ] Validate that the file is not empty.

  - [ ] **2. Header Parsing:**
    - [ ] For each header line (starting with "NO ", "SO ", "WE ", "EA ", "F ", "C "):
      - [ ] Trim the line.
      - [ ] Validate the header identifier.
      - [ ] For texture lines:
        - [ ] Remove the identifier and store the path in `t_game`.
      - [ ] For color lines:
        - [ ] Parse the `"R,G,B"` string and convert it into an integer (`0xRRGGBB`).
    - [ ] Ensure no duplicate headers are present.
    - [ ] Ensure all required headers are found.

  - [ ] **3. Map Layout Parsing:**
    - [ ] After processing headers, the remaining non-empty lines form the map.
    - [ ] Trim each line and append it to `t_game->map`.
    - [ ] Validate that the map only has allowed characters
      (e.g., `'0'`, `'1'`, `'N'`, `'S'`, `'E'`, `'W'`, and spaces).

  - [ ] **4. Map Validation:**
    - [ ] Check that the map is enclosed by walls.
    - [ ] Ensure there is exactly one player starting position.
    - [ ] (Optional) Convert the map to a rectangle if needed.
    - [ ] (Optional) Run a flood fill (or similar algorithm) to confirm that the player’s spawning area is sealed.

  - [ ] **5. Error Handling:**
    - [ ] Free any allocated memory in case of errors.
    - [ ] Return `0` on failure, `1` on success.

