## MODES
- `v` : Character Visual Mode - Select individual characters.
- `V` : Line Visual Mode - Select entire lines.
- `Ctrl + v` : Block Visual Mode - Select text blocks (columns).
- `i` : Insert Mode - Switch to insert mode to start editing text.
- `a` : Append Mode - Move the cursor one character forward and enter insert mode.
- `Esc` : Return to Normal Mode - Exit any mode to return to normal mode.

## FUNCTIONS
- `p` : Paste After - Paste text after the cursor.
- `P` : Paste Before - Paste text before the cursor.
- `u` : Undo - Reverts the last action.
- `Ctrl + r` : Redo - Reapply the last undone action.
- `.` : Repeat Last Command - Repeats the most recent editing command.

## REGULAR MOTIONS

### Navigation
- `gg` : Go to the top of the file.
- `G` : Go to the end of the file.
- `0` : Go to the start of the current line.
- `$` : Go to the end of the current line.
- `w` : Jump to the beginning of the next word.
- `b` : Jump to the beginning of the previous word.
- `Ctrl + u` : Move up half a screen.
- `Ctrl + d` : Move down half a screen.
- `Ctrl + f` : Move forward (down) one full screen.
- `Ctrl + b` : Move backward (up) one full screen.

### Copying and Deleting Text
- `y` : Yank (copy) selected text.
- `yy` : Yank the entire current line.
- `d` : Delete (cut) selected text.
- `dd` : Delete the entire current line.
- `"*y` : Copy selection to system clipboard.
- `"*yy` : Copy entire line to system clipboard.

### Select All and Copy All
- `gg` : Go to the top of the file.
- `V` : Enter Line Visual Mode.
- `G` : Go to the end of the file to select all lines.
- `y` : Yank (copy) all selected text.
- `"*y` : Copy selected text to the system clipboard.

## SEARCH AND REPLACE

- `/<text>` : Search forward for text `<text>`.
- `?<text>` : Search backward for text `<text>`.
- `n` : Jump to the next search match.
- `N` : Jump to the previous search match.
- `:%s/<old>/<new>/g` : Replace all occurrences of `<old>` with `<new>` in the file.
- `:%s/<old>/<new>/gc` : Replace all occurrences of `<old>` with `<new>` with confirmation for each replacement.

## FILE MANAGEMENT

### Basic Commands
- `:e <filename>` : Open a specific file by name.
- `:w` : Save the current file.
- `:w <filename>` : Save the file with a new name.
- `:q` : Quit the current file (close buffer).
- `:q!` : Quit without saving changes.
- `:wq` : Save and quit.
- `:x` : Save and quit (alternative to `:wq`).

### Buffers and Tabs
- `:bnext` or `:bn` : Go to the next buffer.
- `:bprev` or `:bp` : Go to the previous buffer.
- `:bd` : Delete (close) the current buffer.
- `:tabnew <filename>` : Open a file in a new tab.
- `gt` : Go to the next tab.
- `gT` : Go to the previous tab.

### Exploring and Browsing
- `:Ex <directory>` : Open directory browser at specified directory.
- `:Ex` : Open directory browser in the current working directory.
- `:Sex` : Open split view of the directory browser.
- `:Vex` : Open vertical split view of the directory browser.
- `:NerdTree` : Open NerdTree (if installed, for more advanced file browsing).

## WINDOW SPLITS

- `:split` or `:sp` : Horizontal split.
- `:vsplit` or `:vsp` : Vertical split.
- `Ctrl + w, w` : Move to the next split window.
- `Ctrl + w, h` : Move to the left split.
- `Ctrl + w, j` : Move to the split below.
- `Ctrl + w, k` : Move to the split above.
- `Ctrl + w, l` : Move to the right split.
- `:close` : Close the current split.

## OTHER USEFUL COMMANDS

- `:set number` : Display line numbers.
- `:set relativenumber` : Display relative line numbers.
- `:syntax on` : Enable syntax highlighting.
- `:noh` : Clear search highlights.
- Using Vim's Netrw File Explorer to Create New Directory
1. Enter the file explorer by typing:
```vim
:Ex
```
2. Navigate to the location where you want the new directory.
3. Press `d` to open a prompt.
4. Type the new directory name and press Enter.